#include "election.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

//include any other headers you need here...

//Check the line's format.
void formatCheck(const char * line, int firstColon, int secondColon, int numColon, int length) {
  //If the number of the colons is not two, print wrong format.
  if (numColon != 2) {
    fprintf(stderr, "Wrong format: Wrong colon number!\n");
    exit(EXIT_FAILURE);
  }
  //If these two colons are connected together, print wrong format.
  if (firstColon + 1 == secondColon) {
    fprintf(stderr, "Wrong format:Two colons connected together!\n");
    exit(EXIT_FAILURE);
  }
  //If the name of the state is bigger than 64(inclusive),print wrong format.
  if (firstColon > MAX_STATE_NAME_LENGTH - 1) {
    fprintf(stderr, "Wrong format:Name is too long!\n");
    exit(EXIT_FAILURE);
  }
  //Go through characters between two colons.
  //If there are other characters which are not between'0'~'9',print wrong format.
  for (int num1 = firstColon + 1; num1 < secondColon; num1++) {
    if (line[num1] < '0' || line[num1] > '9') {
      fprintf(stderr, "Wrong format:Wrong population number!\n");
      exit(EXIT_FAILURE);
    }
  }
  //Go through characters between the second colon and the '\0'.
  //If there are other characters which are not between'0'~'9',print wrong format.
  for (int num2 = secondColon + 1; num2 < length; num2++) {
    if (line[num2] < '0' || line[num2] > '9') {
      fprintf(stderr, "Wrong format:Wrong electoralvotes number!\n");
      exit(EXIT_FAILURE);
    }
  }
}

//Get the names of states.
void getName(char * name, const char * line, int firstColon) {
  for (int i = 0; i < firstColon; i++) {
    name[i] = line[i];
  }
  name[firstColon] = '\0';
}

//Get the population of states.
uint64_t getPopulation(const char * line, int firstColon, int secondColon) {
  uint64_t population = 0;
  for (int i = firstColon + 1; i < secondColon; i++) {
    population = population * 10 + (uint64_t)(line[i] - '0');
  }
  return population;
}

//Get the electoralvotes of states.
unsigned int getElectoralVotes(const char * line, int secondColon, int length) {
  unsigned int electoralVotes = 0;
  for (int i = secondColon + 1; i < length; i++) {
    electoralVotes = electoralVotes * 10 + (unsigned int)(line[i] - '0');
  }
  return electoralVotes;
}

state_t parseLine(const char * line) {
  //STEP 1: write me

  //Check whether the line is correct.
  if (line == NULL) {
    fprintf(stderr, "Wrong line!");
  }

  //Declare variables about the line's feature.
  int numColon = 0;     //The number of colons.
  int firstColon = 0;   //The position of the first colon.
  int secondColon = 0;  //The position of the second colon.
  int length = 0;       //The length of the line.

  //Get the line's format information.
  int x = 0;
  while (line[x] != '\0') {
    //Get the position of the first colon.
    if (line[x] == ':' && numColon == 0) {
      firstColon = x;
      numColon = numColon + 1;
    }
    //Get the position of the second colon.
    if (line[x] == ':' && x > firstColon) {
      secondColon = x;
      numColon = numColon + 1;
    }
    x++;
  }
  length = x;  //Get the lenght of the line.

  //Check the format.
  formatCheck(line, firstColon, secondColon, numColon, length);
  //If format is correct,set a struct called stateInfo.
  state_t stateInfo;
  //Get the name.
  getName(stateInfo.name, line, firstColon);
  //Get the population.
  stateInfo.population = getPopulation(line, firstColon, secondColon);
  //Get the electoralVotes.
  stateInfo.electoralVotes = getElectoralVotes(line, secondColon, length);

  return stateInfo;
}

unsigned int countElectoralVotes(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 2: write me
  int candidateA = 0;
  for (size_t n = 0; n < nStates; n++) {
    //Check whether the vote is larger than half population.
    if (voteCounts[n] * 2 > stateData[n].population) {
      candidateA = candidateA + stateData[n].electoralVotes;
    }
  }
  return candidateA;
}

void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 3: write me
  double proportion = 0;
  for (size_t n = 0; n < nStates; n++) {
    //Check whether the percent is between 49.5% and 50.5%.
    proportion = (double)(voteCounts[n]) / (double)(stateData[n].population);
    if (proportion * 100 >= 49.5 && proportion * 100 <= 50.5) {
      printf("%s requires a recount (Candidate A has %.2f%% of the vote)\n",
             stateData[n].name,
             proportion * 100);
    }
  }
}

void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 4: write me
  double percent = 0;
  double max = 0;       //The max percentage.
  size_t maxState = 0;  //The number of the state with largest percentage.
  for (size_t n = 0; n < nStates; n++) {
    //Calculate the percentage.
    percent = 100 * ((double)voteCounts[n] / (double)stateData[n].population);
    if (percent >= max) {
      max = percent;
      maxState = n;
    }
  }
  printf("Candidate A won %s with %.2f%% of the vote\n", stateData[maxState].name, max);
}
