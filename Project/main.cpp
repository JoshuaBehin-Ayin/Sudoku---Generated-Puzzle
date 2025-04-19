#include <iostream>
#include <ctime>
#include "functions.h"
using namespace std;


int main() {

//Using time 0 for generating a random
//number for the time since january 1, 1970
srand(time(0));

//Setting quit to false so code iterates 
//at least once
bool quit=false;

//Intializing variable
int removeNums;

//Keep iterating until user chooses to quit
while(!quit)
  {
    //Setting all elements in 2-d array to 0
    int answerKey[rows][cols]={0};
    string userPuzzle[rows][cols]={};

    //Get users choice
    
    int choice=menu();
    //Clear screen after every user choice
    cout << "\033[2J\033[1;1H";

    //Fill the diagnol boxes of the puzzle
    fillDiagnols(answerKey);
    //Fill the remaing boxes
    fillRemaining(answerKey);

    
    switch(choice)
      {
        case 1:
        //Output rules to console
        viewRules();
        break;
        
        case 2:
        //Removes 41 numbers from puzzle
        removeNums=41;
        break;

        case 3:
        //Removes 51 numbers from puzzle
        removeNums=51;
        break;

        case 4:
        //Removes 56 numbers from puzzle
        removeNums=56;
        break;

        case 5:
        //Ask user for nums to remove
        //Passes by reference to update variable
        customPuzzle(removeNums);
        break;
        
        case 6:
        //Set quit to true to end while loop
        quit = true;
        break; 
        
      }
        //Create unfilled puzzle and
        //ask user for input
        if(choice!=1&&!quit)
        {
        removeNumbers(answerKey,userPuzzle,removeNums);
        sudokuPrinter(userPuzzle);
        userInput(answerKey,userPuzzle);
        }//..end switch
  }//..end while
  
  cout<<"Thank you for playing Sudoku"<<endl;
  
}//..end main