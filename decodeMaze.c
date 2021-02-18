#include <stdio.h>

//Function that prints an encoded maze, 2 parameters - an array of integers and char x representing the dimension of array
void printEncodedMaze(int array[], unsigned char x){
  //y is a variable to store the bit that has been extracted
  int y;
  // nested for loop that iterates through each bit of each int in the array to check if bit is set to 1 or 0
  for(int i=0; i<x ; i++){
    printf("\n");
    for(int j=x; j>=0  ; j--){
      y = ((array[i] & (1 << j)) >> j);
      if(y == 1){
        printf("@ ");
      }else if(y == 0){
        printf("  ");
      }
    }
  }
}

//Function that prints maze with the path, similar to the function above, takes in two int arrays and dimension of array x
void printEncodedMazeWithPath(int mainArray[], int pathMaze[], unsigned char x){
  //y stores bit extracted of the ints in the maze array
  int y;
  //z stores the bit extracted of the ints in the path array
  int z;
  for(int i=0; i<x ; i++){
    printf("\n");
    for(int j=x; j>=0; j--){
      y = ((mainArray[i] & (1 << j)) >> j);
      z = ((pathMaze[i] & (1 << j)) >> j);
      if(y == 1){
        printf("@ ");
      }else if(z == 1){
        printf(". ");
      }else if( y == 0){
        printf("  ");
      }
    }
  }
}

//function that takes in an 8X8 array and encodes it into an array of ints in the size 8 int array
void encode8by8Maze(char inputMaze[8][8], int encodedMaze[8]){
  //sets all the values in the int array to zero to initialize
  for(int i =0; i<8; i++){
    encodedMaze[i]= 0;
  }
  //nested for loop that iterates through each element in the array of chars, checks if it is a 1 and sets that bit in the int array
  for(int j=0; j<8; j++){
    for(int k=0; k<8; k++){
      if(inputMaze[j][k] == 1){
        encodedMaze[j]=encodedMaze[j] | (1 << (7 - k));
      }
    }
  }  
}

//the merged maze function
void merge8by8Mazes(int topLeft[8], int topRight[8],int bottomLeft[8], int bottomRight[8],int finalMaze[14]) {
  //iterates through final size 14 maze and initializes values to 0
  for(int i =0; i<14; i++){
    finalMaze[i]=0;
  }
  //iterates 7 times but handles the top and bottom half of the merged maze at the same time
  for(int i =0; i<7; i++){
    //applies a series of bitwise operators to cut off the columns not required and do bit addition and shifting
    //handles the top left and right of the maze
    finalMaze[i] = ( ((finalMaze[i] + (topLeft[i] & (~(1 << 0))))<<6)+ (topRight[i] & (~(1 << 7))) );

    //handles the bottom left and right of the maze
    finalMaze[i+7] = ( ((finalMaze[i+7] + (bottomLeft[i+1] & (~(1 << 0))))<<6)+ (bottomRight[i+1] & (~(1 << 7))) );
  } 
}

//function to check if the path lies in the maze, takes in encoded maze, the encoded path and the array dimension
char isPathInMaze(int encodedMaze[], int encodedPath[], unsigned char x){
  //y stores bit extracted of the ints in the maze array
  int y;
  //z stores the bit extracted of the ints in the path array
  int z;
  //goes through the array and exposes each bit and then checks if its a 1 in both the maze and path to see if it fits
  for(int i=0; i<x ; i++){
    for(int j=x; j>=0; j--){
      y = ((encodedMaze[i] & (1 << j)) >> j);
      z = ((encodedPath[i] & (1 << j)) >> j);
      if(y == 1 && z == 1){
        return 0;
      }
    }
  }
  return 1;

}



int main() {
  //array of 32 ints storing the maze
  int mainArray[32] = {-1,-2146430423,-1109928277,-1525661045,-1602496045,-1358950569,-1451509759,-1927115297,-1578180479,-1354977603,-1476294999,-2084818261,-1163749757,-1964319689,-1341614619,-1750141691,-1256060947,-1515522751,-1204136611,-1955867371,-1190652827,-1553272339,-1100839163,-1999963019,-631368865,-1882138047,-1172944163,-1412279803,-1567107339,-164346691,-2138762879,-1};

  //calls the print maze function
  printEncodedMaze(mainArray, 32 );

  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");

  //array of the path maze
  int pathMaze[32]= {0, 0, 0, 0, 12, 8, 56, 32, 8032, 4416, 134115648, 67354944, 67109184,
  67109312, 133169152, 1048576, 1835008, 262144, 262144, 262144, 458752,
  65536, 65536, 65536, 65536, 983040, 67633152, 67633152, 201850880,
  164102144, 259522560, 0};

  //calls the print maze with path function
  printEncodedMazeWithPath(mainArray,pathMaze ,32);

  printf("\n");
  printf("\n");

  //calls the isPathInMaze function and, using the return value checks if the path fits in the maze
  if(isPathInMaze(mainArray,pathMaze, 32) == 1 ){
    printf("The path fits in the maze");
  } else if(isPathInMaze(mainArray,pathMaze, 32) == 0 ){
    printf("The path does not fit in the maze.");
  }
  
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");

  //stores the 4 8X8 arrays containing 1's or 0's

  char arrayEight1[8][8] = 
  {{1,1,1,1,1,1,1,1},
  {1,0,0,0,1,0,0,1},
  {1,0,1,0,1,1,0,1},
  {1,0,1,0,0,0,0,1},
  {1,0,1,1,1,1,0,1},
  {1,0,0,0,0,0,0,1},
  {1,0,1,0,1,0,1,1},
  {1,1,1,1,1,1,1,1}};

  char arrayEight2[8][8]= 
  {{1,1,1,1,1,1,1,1},
  {1,0,0,0,0,1,0,1},
  {1,1,1,1,0,1,0,1},
  {1,0,0,1,0,1,1,1},
  {1,1,0,0,0,0,0,1},
  {1,1,1,1,0,1,1,1},
  {1,0,0,0,0,1,0,1},
  {1,1,1,1,1,1,1,1}};

  char arrayEight3[8][8]=
  {{1,1,1,1,1,1,1,1},
  {1,0,1,0,0,0,1,1},
  {1,0,1,0,1,0,0,1},
  {1,0,1,0,1,0,1,1},
  {1,0,1,0,1,0,1,1},
  {1,0,1,0,1,0,1,1},
  {1,0,0,0,1,0,0,1},
  {1,1,1,1,1,1,1,1}};

  char arrayEight4[8][8]=
  {{1,1,1,1,1,1,1,1},
  {1,0,1,0,1,0,1,1},
  {1,0,1,0,0,0,0,1},
  {1,0,0,0,1,1,1,1},
  {1,1,1,0,1,0,0,1},
  {1,0,0,0,0,0,1,1},
  {1,1,0,1,1,0,0,1},
  {1,1,1,1,1,1,1,1}};
  
  //declaration of the 4 int array of size 8, it is passed into the encode8by8Maze function, 4 different ones used as each will be used by the mergeMazes function
  int encodedMaze1[8];
  int encodedMaze2[8];
  int encodedMaze3[8];
  int encodedMaze4[8];

  //calls the encode8by8Maze function on all 4 arrays and then calls the printEncodedMaze function to print

  encode8by8Maze(arrayEight1, encodedMaze1);
  printEncodedMaze(encodedMaze1, 8);
  printf("\n");
  printf("\n");
  printf("\n");

  encode8by8Maze(arrayEight2, encodedMaze2);
  printEncodedMaze(encodedMaze2, 8);
  printf("\n");
  printf("\n");
  printf("\n");

  encode8by8Maze(arrayEight3, encodedMaze3);
  printEncodedMaze(encodedMaze3, 8);
  printf("\n");
  printf("\n");
  printf("\n");
  
  encode8by8Maze(arrayEight4, encodedMaze4);
  printEncodedMaze(encodedMaze4, 8);
  printf("\n");
  printf("\n");
  printf("\n");

  //stores the path for checking if path is in the maze for the 14X14 maze
  int pathForSize14[] = {0, 4096, 4096, 4096, 4096, 7936, 256, 256, 448, 112, 16, 28, 6, 0};

  //stores the encoded mazes of size 8 in an array to make permutations easier in question 6
  int* arrayofEncodedMazes[4] = {encodedMaze1, encodedMaze2, encodedMaze3, encodedMaze4};

  //prints out all the 256 combination of the mazes
  //Uses 4 for loops to go through all combinations
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
      for(int k=0; k<4; k++){
        for(int l=0; l<4; l++){
          //finalMazePermutations is the array that stores the merged maze for each permutation
          int finalMazePermutations[14];
          printf("Printing merged maze using mazes- %d, %d, %d, %d",i+1,j+1,k+1,l+1);
          printf("\n");
          //calls the merge8by8Mazes function taking in 4 encoded arrays and the finalMazePermutations array
          merge8by8Mazes(arrayofEncodedMazes[i],arrayofEncodedMazes[j],arrayofEncodedMazes[k],arrayofEncodedMazes[l],finalMazePermutations);
          //prints the different merged mazes
          printEncodedMaze(finalMazePermutations, 14);
          printf("\n");
          printf("\n");
          
          //uses isPathInMaze to check if path fits and then prints out a confirmation
          if(isPathInMaze(finalMazePermutations,pathForSize14, 14) == 1 ){
            printf("THE PATH FITS IN THE MAZE\n");
          }else if(isPathInMaze(finalMazePermutations,pathForSize14, 32) == 0 ){}
          
          printf("\n");
          printf("\n");
        }
      }
    }
  }
  
}