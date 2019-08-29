#include <stdio.h>
#include <stdlib.h>

struct retire_info_tag {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct retire_info_tag retire_info_t;


void retirement(int startAge, double initial, retire_info_t working, retire_info_t retired){
  double money = initial;
  for(int x = startAge; x < startAge + working.months; x++){   
    printf("Age %3d month %2d you have $%.2lf\n", x/12, x%12, money);
    money = money *(1 + working.rate_of_return) + working.contribution; 
  }
  for(int y = startAge + working.months; y < startAge + working.months + retired.months; y++){ 
    printf("Age %3d month %2d you have $%.2lf\n", y/12, y%12, money);
    money = money *(1 + retired.rate_of_return) + retired.contribution;
  }
}


int main(void) {
  retire_info_t Working;
  Working.months = 489;
  Working.contribution=1000;
  Working.rate_of_return=0.045/12; 
  
  retire_info_t Retired;
  Retired.months = 384;
  Retired.contribution= -4000;
  Retired.rate_of_return=0.01/12;  
    
  retirement(327,21345,Working,Retired);
  
  return 0;
}
