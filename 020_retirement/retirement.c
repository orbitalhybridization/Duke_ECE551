#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;

void retirement(int startAge,           //in months
                double initial,         //initial savings in dollars
                retire_info working,    //info about working
                retire_info retired) {  // info about being retired

  int currentAge = startAge;
  double total_savings = initial;
  for (int i = 0; i < working.months; i++) {
    printf("Age %3d month %2d you have $%.2lf\n",
           currentAge / 12,
           currentAge % 12,
           total_savings);
    double interest = total_savings * (working.rate_of_return / 12);  //calculate interest
    total_savings += (interest + working.contribution);               //add to total
    currentAge++;                                                     //age one month
  }

  for (int i = 0; i < retired.months; i++) {
    printf("Age %3d month %2d you have $%.2lf\n",
           currentAge / 12,
           currentAge % 12,
           total_savings);
    double interest = total_savings * (retired.rate_of_return / 12);
    total_savings += (interest + retired.contribution);  //add to total
    currentAge++;
  }
}

int main() {
  //enter info for calculation
  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045;

  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01;

  int startAge = 327;
  int initial = 21345;

  // do calculation
  retirement(startAge, initial, working, retired);

  return 0;
}
