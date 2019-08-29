#include <ctype.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

//This function is for Step 4
char * time2str(const time_t * when, long ns) {
  char * ans = malloc(128 * sizeof(*ans));
  char temp1[64];
  char temp2[32];
  const struct tm * t = localtime(when);
  strftime(temp1, 512, "%Y-%m-%d %H:%M:%S", t);
  strftime(temp2, 32, "%z", t);
  snprintf(ans, 128, "%s.%09ld %s", temp1, ns, temp2);
  return ans;
}

/* This function takes one parameter:
 *    sbp (which is a pointer to struct stat sb)
 * to find out the bit of file type in the st_mode field
 * and compare that result to several defined constants to figure out what to print.
 */
char * getmode(struct stat * sbp) {
  char * mode = NULL;  //A string to be printed in line3.
  switch (sbp->st_mode & S_IFMT) {
    case S_IFBLK:
      mode = "block special file";
      break;
    case S_IFCHR:
      mode = "character special file";
      break;
    case S_IFDIR:
      mode = "directory";
      break;
    case S_IFIFO:
      mode = "fifo";
      break;
    case S_IFLNK:
      mode = "symbolic link";
      break;
    case S_IFREG:
      mode = "regular file";
      break;
    case S_IFSOCK:
      mode = "socket";
      break;
    default:
      mode = "unknown?";
      break;
  }
  return mode;
}

/* This function takes two parameters:
 *   fname (which is the name of the file) 
 *   sbp(which is a pointer to struct stat sb)
 * and print the first three lines.
 */
void firstThreeLine(const char * fname, struct stat * sbp) {
  //To print the fisrt line.
  //If the file is a symbolic link,use this link format to print file name and link.
  if (S_ISLNK(sbp->st_mode)) {
    char linktarget[256];                            //The output string.
    ssize_t len = readlink(fname, linktarget, 256);  //Get the string length from the readlink.
    if (len == -1) {                                 //If fail to get length, exit failure.
      perror("error description:\n");
      exit(EXIT_FAILURE);
    }
    linktarget[len] = '\0';  //Add null terminator to the end.
    printf("  File: %s -> %s\n", fname, linktarget);
  }
  else {  //If the file is no a symbolic link, use this format to print file name.
    printf("  File: %s\n", fname);
  }
  //To print the second line.
  printf("  Size: %-10lu\tBlocks: %-10lu IO Block: %-6lu %s\n",
         sbp->st_size,     //The total size.
         sbp->st_blocks,   //The bumber of 512B blocks allocated to the file.
         sbp->st_blksize,  //The blocksize for the file type.
         getmode(sbp));    //A description of the file type.
  //To print the third line.
  //If the file stated is a device(either the S_ISCHR or the S_ISBLK macro returns true),using this format.
  if (S_ISCHR(sbp->st_mode) || S_ISBLK(sbp->st_mode)) {
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %-5lu Device type: %d,%d\n",
           sbp->st_dev,  //The ID of the device.
           sbp->st_dev,
           sbp->st_ino,           //The inode number.
           sbp->st_nlink,         //The number of hard links.
           major(sbp->st_rdev),   //Major numbers of the file's name.
           minor(sbp->st_rdev));  //Minor number of the file's name.
  }
  //Else use this format.
  else {
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %lu\n",
           sbp->st_dev,
           sbp->st_dev,
           sbp->st_ino,
           sbp->st_nlink);
  }
}
/* This function take one parameter:
 *     sbp(which is a pointer to struct stat sb)
 * and gets the first character of the human readable description of the permissions
 * (which always has 10 characters) 
 */
char getH0(struct stat * sbp) {
  char h0;                          //The first character of the permission.
  switch (sbp->st_mode & S_IFMT) {  //The first character depends on the file type.
    case S_IFBLK:
      h0 = 'b';
      break;
    case S_IFCHR:
      h0 = 'c';
      break;
    case S_IFDIR:
      h0 = 'd';
      break;
    case S_IFIFO:
      h0 = 'p';
      break;
    case S_IFLNK:
      h0 = 'l';
      break;
    case S_IFREG:
      h0 = '-';
      break;
    case S_IFSOCK:
      h0 = 's';
      break;
    default:
      h0 = 'u';
      break;
  }
  return h0;
}
/* This function take one parameter:
 *     sbp(which is a pointer to struct stat sb)
 * and prints the fourthline.
 */
void fourthLine(struct stat * sbp) {
  char h[11] = "";  //The human readable permission string has 10 characters.
  //Get every character of h.
  h[0] = getH0(sbp);
  h[1] = (sbp->st_mode & S_IRUSR) ? 'r' : '-';
  h[2] = (sbp->st_mode & S_IWUSR) ? 'w' : '-';
  h[3] = (sbp->st_mode & S_IXUSR) ? 'x' : '-';
  h[4] = (sbp->st_mode & S_IRGRP) ? 'r' : '-';
  h[5] = (sbp->st_mode & S_IWGRP) ? 'w' : '-';
  h[6] = (sbp->st_mode & S_IXGRP) ? 'x' : '-';
  h[7] = (sbp->st_mode & S_IROTH) ? 'r' : '-';
  h[8] = (sbp->st_mode & S_IWOTH) ? 'w' : '-';
  h[9] = (sbp->st_mode & S_IXOTH) ? 'x' : '-';
  h[10] = '\0';  //Add a null terminator at the end of the string.
  //To print the fourth line.
  printf("Access: (%04o/%s)  Uid: (%5d/%8s)   Gid: (%5d/%8s)\n",
         sbp->st_mode & ~S_IFMT,           //The permission in octal.
         h,                                //The human readable permission string.
         sbp->st_uid,                      //The user ID of the owner.
         getpwuid(sbp->st_uid)->pw_name,   //Get the name of the owner from getpwuid.
         sbp->st_gid,                      //The group ID of the owning group.
         getgrgid(sbp->st_gid)->gr_name);  //Get the group name of the owning group from getgrgid.
}
/* This function take one parameter:
 *     sbp(which is a pointer to struct stat sb)
 * and accesses time then print them out.
 */
void lastFourLine(struct stat * sbp) {
  //Get the time from the time2str.
  char * timestr_a = time2str(&sbp->st_atime, sbp->st_atim.tv_nsec);
  char * timestr_m = time2str(&sbp->st_mtime, sbp->st_mtim.tv_nsec);
  char * timestr_c = time2str(&sbp->st_ctime, sbp->st_ctim.tv_nsec);
  //To print the last four lines.
  printf("Access: %s\n", timestr_a);
  printf("Modify: %s\n", timestr_m);
  printf("Change: %s\n", timestr_c);
  printf(" Birth: -\n");
  //To free the space malloced by time2str call.
  free(timestr_a);
  free(timestr_m);
  free(timestr_c);
}

int main(int argc, char * argv[]) {
  struct stat sb;
  //If the there's no file in the argument, print usage and exit.
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  //Print information of files listed in the argument.
  for (int i = 1; i < argc; i++) {
    //If the struct cannot be accessed, print error and exit.
    if (lstat(argv[i], &sb) == -1) {
      perror("lstat");
      exit(EXIT_FAILURE);
    }
    //To print the first three line.
    firstThreeLine(argv[i], &sb);
    //To print the fourth line.
    fourthLine(&sb);
    //To print the last four lines.
    lastFourLine(&sb);
  }
  exit(EXIT_SUCCESS);
}
