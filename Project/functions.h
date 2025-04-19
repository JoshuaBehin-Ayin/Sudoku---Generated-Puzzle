#include <iostream>
#include <ctime>
using namespace std;

//Intializing rows and colums of 2-D array
//globally so they can be used in all functions
const int rows = 9;
const int cols = 9;

// Function displays menu and asks for users choice
int menu()
{
  // Initializing choice
  int choice;
  cout<<"****Sudoku Puzzle****"<<endl;
  cout<<"1. View Rules"<<endl;
  cout<<"2. Play Easy Puzzle"<<endl;
  cout<<"3. Play Medium Puzzle"<<endl;
  cout<<"4. Play Hard Puzzle"<<endl;
  cout<<"5. Custom Puzzle"<<endl;
  cout<<"6. Quit"<<endl<<endl;

  // Do while loop used to ask user for valid choice
  do{
    cout<<"Enter your choice: ";
    cin>>choice;
    if(choice>6||choice<1)
      cout<<"Error: Invalid choice"<<endl<<endl;
  // Runs until valid choice between 1-6 is given
  }while(choice>6||choice<1);

   // Returns users choice as an integer
  return choice;
}


//Checks that the random number that
//is generated for a specific postion
//in the array is not already
//in the box
bool checkBox(int answerKey[][cols],int random,int row, int col)
{
  //Finds the start row and column
  //by eliminating the remainder
  //when divied by 3
  int startRow=row-row%3;
  int startCol=col-col%3;
  
   for(int i=startRow;i<startRow+3;i++)
    {
      for(int j=startCol;j<startCol+3;j++)
        {
          if(answerKey[i][j]==random)
            //False if number already in box
            return false;
        }
    }
  //True otherwise
  return true;
}

//Checks that the random number that
//is generated for a specific postion
//in the array is not already
//in the row of that position
bool checkRow(int answerKey[][cols],int random, int row)
{
      for(int j=0;j<cols;j++)
        {
        if(answerKey[row][j]==random)
            return false;
        }
  return true;
}

//Checks that the random number that
//is generated for a specific postion
//in the array is not already
//in the column of that position
bool checkColumn(int answerKey[][cols],int random, int col)
{
      for(int i=0;i<rows;i++)
        {
        if(answerKey[i][col]==random)
            return false;
        }   
  return true;
}

//Prints the users puzzle after every valid number entered
void sudokuPrinter(string userPuzzle[][cols])
{
 
  cout<<"-------------------------------------"<<endl;
  for(int i= 0;i<rows;i++)
    {
    for(int j= 0;j<cols;j++)
      {
      
      if(j%3==0)
        cout<<"|  ";

      cout<<userPuzzle[i][j]<<"  "; 
        
      if(j==8)
        {
        cout<<"|  "<<endl;
        if((i+1)%3==0&&i!=8)
          cout<<"|-----------|-----------|-----------|"<<endl;
        else
          if(i==8)
            cout<<"-------------------------------------"<<endl;
          else
          cout<<"|           |           |           |"<<endl;
        }
        
      }//end nested col for loop
    }//end row for loop
  
}//end function

//Fills the 3 diagnol boxes with
//random number from 1-9
void fillDiagnols(int answerKey[][cols])
{
  
  int random;
  for(int i=0;i<rows;i++)
   {
     for(int j=0;j<cols;j++)
       {
         
         if((i / 3) == (j / 3))
         {
          do {
          random=rand()%9+1; 
            //Keep looping until valid number found
          } while(!checkBox(answerKey, random,i,j));
            answerKey[i][j]=random;
         }      
       
       }
     
   }
  cout<<endl;
  
}

//Function uses recursive backtracking to 
//keep iterating through all possible number 
//combinations until valid one is found
bool fillRemaining(int puzzle[][cols])
{
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // Skip filled squares that have
            // a number other than 0
            if (puzzle[i][j] != 0) 
                continue;
            

            for (int num = 1; num <= 9; num++) 
              {
                //If number does not repeat
                //place it in the empty square
                if (checkColumn(puzzle, num, j) &&                                              checkRow(puzzle, num, i) &&
                    checkBox(puzzle, num, i, j)) 
                  { 
                    puzzle[i][j] = num;
                    
                    
                    //The recursion will take the next index
                    //and fill it with another number
                    if (fillRemaining(puzzle)) 
                        return true;
                      
                    
                    // Set the previous number back to 0
                    // if the next number not possible
                    //goes back to try next num
                    puzzle[i][j] = 0; 
                                      
                  }
              }
            //Return false to previous iteration 
            //if valid number not found 
            return false; 
        }
    }
    //Ends function when all squares are filled
    return true; 
}

//Removes a certain amount of numbers
//from the puzzle depending on the
//users input
void removeNumbers(int answerKey[][cols],string userPuzzle[][cols],int num)
{
  

  for(int i=0;i<rows;i++){
    for(int j=0;j<cols;j++)
      {
        //Storing answer key into new user array
        userPuzzle[i][j]=to_string(answerKey[i][j]);
      }
  }

  //Replaces random elements with a dot
  //and stores it into the users array
  for(int n=0;n<num;n++)
    {
      int i=rand()%9;
      int j=rand()%9;
      if(userPuzzle[i][j]==".")
        n--;
      else
      userPuzzle[i][j]=".";
    }
  
}

//Outputs rules to the console
void viewRules(){
  char ch;
        cout<<"1. A 9×9 square must be filled in with numbers"<<endl
            <<"   from 1-9 with no repeated numbers in each line,"<<endl 
            <<"   horizontally or vertically."<<endl<<endl;
          
        cout<<"2. There are also 3×3 squares marked out in the"<<endl 
            <<"   grid, and each of these squares can't have" <<endl              
            <<"   any repeating numbers either."<<endl<<endl;
          
        cout<<"3. Each dot represents an empty square where a"<<endl
            <<"   number should be placed."<<endl<<endl;
          
        cout<<"4. To choose where to place your number, enter "<<endl   
            <<"   the row and column number from 1-9 of the  "<<endl 
            <<"   position. Assume the row and column numbers  "<<endl   
            <<"   start from the top left of the 9 by 9 grid"<<endl<<endl;

        cout<<"5. You have 2 chances to make mistakes. On your"<<endl    
            <<"   third incorrect input the game is over"<<endl<<endl;

        cout<<"6. If you succesfully fill in all the empty squares"<<endl                <<"   you win"<<endl<<endl;

  cout<<"Press any character to go back to the menu: ";
  cin>>ch;
  //Clears screen
  cout << "\033[2J\033[1;1H";
}

//Checks if the sudoku is solved
bool sudokuSolved(string userPuzzle[][cols])
{
  
  for(int i=0;i<rows;i++)
    {
      for(int j=0;j<cols;j++)
        {
          //If a empty square represented by a 
          // dot is found, puzzle is not solved
          if(userPuzzle[i][j]==".")
            return false;
        }
    }
  cout<<"You solved the puzzle"<<endl;
  return true;
}

//Function ask user for a number and
//where to place it within the puzzle
//Updates puzzle if user correct
void userInput(int answerKey[][cols],string userPuzzle[][cols])
{
  
  int row, col,num;
  int chances=3;
  bool solved=false;

  //Keep asking user of input until either
  //the puzzle is solved or the user runs out of chances
  while(chances>0&&!solved)
  {
    //Do while loops used for error trapping 
    do{
      
      
      do{
        cout<<"Enter a row number: ";
        cin>>row;
        if(row>9||row<1)
          cout<<"Error: Invalid row"<<endl;
        }while(row>9||row<1);

      do{ 
        cout<<"Enter a column number: ";
        cin>>col;
        if(col>9||col<1)
          cout<<"Error: Invalid column"<<endl;
        }while(col>9||col<1);

        if(userPuzzle[row-1][col-1]!=".")
          cout<<"Error: That sqaure is already filled"<<endl<<endl;
        
        }while(userPuzzle[row-1][col-1]!=".");
  do{
    cout<<"Enter the number you would like to place: ";
    cin>>num;
    if(num>9||num<1)
      cout<<"Error: Invalid number"<<endl;
  }while(num>9||num<1);

  
  //If users number is correct
  if(num==answerKey[row-1][col-1])
  {
    //Clears screen
    cout << "\033[2J\033[1;1H";
    cout<<"Correct!"<<endl<<endl;;
    userPuzzle[row-1][col-1]=to_string(num);
    solved=sudokuSolved(userPuzzle);

    
    
  }
  
  //If user number is not correct
  else
  {
    chances--;
    //Clears screen
    cout << "\033[2J\033[1;1H";
    //If game over
    if(chances==0)
    {
      cout<<"Game Over! Solution:"<<endl<<endl;
  
      //Making unfilled puzzle equal to answer key
      for(int i=0;i<rows;i++)
        {
          for(int j=0;j<cols;j++)
            userPuzzle[i][j]=to_string(answerKey[i][j]);
        } 
    }
    else
    {
    cout<<"Incorrect! "<<chances
      //boolean used for the tense of chances
        << (chances>1 ? " chances":" chance")
        <<" left"<<endl<<endl;
    }
    
    
  }
  //Prints updated puzzle at the end of each iteration
  sudokuPrinter(userPuzzle);
  }
    
  cout<<endl;
}

//Function asks user for
//amount of numbers to be removed
//Passes value by reference
//to store back into variable
void customPuzzle(int &removeNums)
{
  
  cout<<"--------------Custom Puzzle--------------" 
      <<endl<<endl;
  do{
  cout<<"Choose an amount of numbers to remove: ";
  cin>>removeNums;
  if(removeNums<1||removeNums>80)
    cout<<"Erorr: Invalid Removal"<<endl<<endl;
  }while(removeNums<1||removeNums>80);
  cout<<endl;
  //Clears screen
  cout << "\033[2J\033[1;1H";
}