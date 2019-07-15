// C code
// This code will compute the values of the sales ticket sales for concerts
// and sort the entries by those values
// Developer: Erick McCoy
// Date: July 8, 2019

#include <stdio.h>
#include <unistd.h>
#include <time.h>

#define MAXN 100 // max characters in a group/concert name
#define MAXG  50 // max concerts/groups
#define MAXC   4 // max categories

char group  [MAXG][MAXN];
int fans   [MAXG][MAXC];
float prices [MAXC];
float sales  [MAXG];
float total;
int selection;
int count = 0;

void clearScreen()
{
  const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}

void delay(int number_of_seconds) 
{ 
    // Converting time into milli_seconds 
    int milli_seconds = 1000 * number_of_seconds; 
    // Stroing start time 
    clock_t start_time = clock(); 
    // looping till required time is not acheived 
    while (clock() < start_time + milli_seconds); 
} 

void printArray () {
  printf ("%15s%5s%5s%5s%5s%10s\n", 
  "Concert", "s1", "s2", "s3", "s4", "Sales");
  for (int i = 0; i < count; i++) {
    printf ("%15s", group [i]);
    for (int j = 0; j < MAXC; j++) {
      printf ("%5d", fans[i][j]);
    } // end for each category
    printf ("%10.2f\n", sales [i]);
  } // end for each group
} // end function printArray

void computeSales () {
  for (int i = 0; i < count; i++) {
    sales [i] = 0;
    for (int j = 0; j < MAXC; j++) {
      sales [i] += prices [j] * fans [i][j];
    } // end for each category
  } // end for each group
} // end function computeSales

//Total Sales Function
void computeTotalSales(){
  total = 0;
  for (int i = 0; i < count; i++){
    total += sales[i];
  }
}

void switchRows (int m, int n) {
  char tc;
  int  ti;
  float v;
  // printf ("Switching %d with %d\n", m, n);
  for (int i = 0; i < MAXN; i++) {
    tc = group [m][i];
    group [m][i] = group [n][i];
    group [n][i] = tc;
  } // end for each character in a group name
  for (int i = 0; i < MAXC; i++) {
    ti = fans [m][i];
    fans [m][i] = fans [n][i];
    fans [n][i] = ti;
  } // end for each fan category
  v = sales [m];
  sales [m] = sales [n];
  sales [n] = v;
} // end switch

int findMinSales (int m) {
  float min = sales [m];
  int target = m;
  for (int i = m+1; i < count; i++)
    if (sales [i] < min) {
      min = sales [i];
      target = i;
    } // end new max found
  return target;
} // end function findMinSales

void sortBySales () {
  int target;
  for (int i = 0; i < count; i++) {
    target = findMinSales (i);
    if (target > i)
      switchRows (i, target);
  } // for each concert
} // end function sortBySales

//Function that finds the miniumum in a group
int findMinFan(int m, int n){
  int min = fans [m][n];
  int target = m;
  for(int i = m+1; i < count; i++){
    if(fans[i][n] < min){
      min = fans[i][n];
      target = i;
    }
  }
  return target;
}

//Sorts the array by first group
void sortByCatOne(){
  int target;
  for(int i = 0; i < count; i++){
    target = findMinFan(i, 0);
    if(target > 1){
      switchRows(i, target);
    }
  }
}

void getSales () {
  // for (int i = 0; i < MAXG; i++) sales [i] = 0;
  printf ("-- Enter group and fans in %d categories\n", MAXC);
  printf ("   . to finish entries:\n");
  for (int i = 0; i < MAXG; i++) {
    scanf ("%s", group[i]);
    if (group [i][0] == '.'){
      printf("Saved! Returning..."); 
      break;
    }
    count++;
    for (int j = 0; j < MAXC; j++)
      scanf ("%d", &fans[i][j]);
  } // end for each group
  computeSales();
  computeTotalSales();
} // end function getData

void getPrices(){
printf ("Enter ticket prices in each of %d categories: ", MAXC);
  
  for (int i = 0; i < MAXC; i++){
    scanf ("%f", &prices [i]);
    while(prices[i] < 0){
      printf("Invalid input: Please enter all ticket sales greater than 0\n");
      printf("The error was at: %f. Please re-enter this number now: ", prices[i]);
      scanf("%f", &prices [i]);
    }
  }
  printf("Saved!\n");  
}

int context(){
  printf("Welcome! My name is Erick, and this program is used to calculate the total sales of concerts.\n");
  printf("\n");
  printf("Current Data\n");
  printf("Ticket Prices: %.2f, %.2f, %.2f, %.2f\n", prices[0], prices[1], prices[2], prices[3]);
  if(count == 0){
    printf("Ticket Sales Entered: False\n");
  }
  else{
    printf("Ticket Sales Entered: True\n");
  }
  printf("Sales Total: $%.2f\n", total);
  printf("\n");
  printf("Please select from the following menu...\n");
  printf("1 - Enter ticket prices\n");
  printf("2 - Enter sales\n");
  printf("3 - Display Sales\n");
  printf("4 - Sort by Ascending\n");
  printf("5 - Sort by First Category\n");
  printf("6 - Exit\n");
  return 0;
}

int menu(){
  int rtn;
  context();
  scanf("%d", &selection);
  if(selection == 1){
    clearScreen();
    getPrices();
    delay(150);
  }
  if(selection == 2){
    if(prices[0] == 0){
      clearScreen();
      printf("Please enter ticket prices before you enter the sales data...\n");
      delay(1000);
      clearScreen();
      return 0;
    }
    clearScreen();
    getSales();
    delay(150);
  }
  if(selection == 3){
    clearScreen();
    printf("Here is a list of sales:\n");
    printf("\n");
    //computeSales();
    printArray();
    printf("Enter 0 to return...\n");
    scanf("%d", &rtn);
    while (rtn != 0){
      printf("Try again...\n");
      scanf("%d", &rtn);
    }
  }
  if(selection == 4){
    clearScreen();
    printf("Here is the list of sales sorted ASCENDING\n");
    //computeSales();
    sortBySales();
    printf ("\n --- Sorted ---\n");
    printArray();
    printf("Enter 0 to return...\n");
    scanf("%d", &rtn);
    while (rtn != 0){
      printf("Try again...\n");
      scanf("%d", &rtn);
    }
  }
  if(selection == 5){
    clearScreen();
    printf("Here is the data sorted by the first category.\n");
    sortByCatOne();
    printf("\n ---Sorted ---\n");
    printArray();
    printf("Enter 0 to return...\n");
    scanf("%d", &rtn);
    while(rtn != 0){
      printf("Try again...\n");
      scanf("%d", &rtn);
    }  
  }
  if(selection == 6){
    printf("Goodbye!\n");
    delay(200);
    return 1;
  } 
  clearScreen();
  return 0;
}

int main(void) {
  while(menu() == 0);
  return 0;
}
