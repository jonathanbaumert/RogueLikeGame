#include <stdio.h>

int checkPath(int val, int path[], int curPosition);
int explorePaths(int step, int boardPosition, int boardSize, int board[][9], int path[]);
int getMove(int numRows, int numCols, int curRow, int curCol, int isCylinder);
int main(int argc, char *argv[]){
  int x = 5;//number of columns
  int y = 5;//number of rows
  int i, j, count = 0;
  int size = x*y;//number of spaces
  int board[size][9];
  int path[x*y];
  int isCylinder = 1; // change to 0 for a cylinder board
  for (i = 1; i <= y; i++)
  {
    for (j = 1; j <= x; j++)
    {
      //Assign number to current square and the numbers corresponding
      //to all of the possible moves a knight at that position can move to
      board[count][0] = (j)+((y)*(i-1));
      printf("%2d ",board[count][0]);      
      board[count][1] = getMove(y,x,i-2,j+1,isCylinder);
      board[count][2] = getMove(y,x,i-1,j+2,isCylinder);
      board[count][3] = getMove(y,x,i+1,j+2,isCylinder);
      board[count][4] = getMove(y,x,i+2,j+1,isCylinder);
      board[count][5] = getMove(y,x,i+2,j-1,isCylinder);
      board[count][6] = getMove(y,x,i+1,j-2,isCylinder);
      board[count][7] = getMove(y,x,i-1,j-2,isCylinder);
      board[count][8] = getMove(y,x,i-2,j-1,isCylinder);      
      count++;      
    }
    printf("\n");
  }
  for(int k = 0; k < (size); k++){
    path[k]=0;
  }

  //int startPos = 0;
  count = 0;
  for(i = 0; i < size; i++){
    count += explorePaths(0, i, size, board, path);
  }
  printf("\nTotal Tours: %d\n", count);
  return 0;
}


int explorePaths(int step, int boardPosition, int boardSize, int board[][9], int path[]){
  int count = 0;
  int i = 0;
  path[step] = board[boardPosition][0];  
  if(step == (boardSize - 1)){
    for(i = 0; i < boardSize; i++){
      printf("%2d ",path[i]);
    }
    printf("\n");
    return 1;
  }
  for(i = 1; i < 9; i++){
    if(checkPath((board[boardPosition][i]), path, step) == 0){
      count = count + explorePaths((step+1), board[boardPosition][i]-1,boardSize,board,path);
    }
  }
  return count;
}

int checkPath(int val, int path[], int step){
  if(val == -1){
    return 1;
  }
  for(int i = 0; i<step; i++){
    if(path[i] == val){
      return 1;
    }
  }
  return 0;
}
int getMove(int rows, int cols, int nxtRow, int nxtCol, int isCylinder){
  int returnCol, returnPos=0;
  if((nxtRow > rows) || (nxtRow < 1)){
    return -1;
  }  
  if(nxtCol > cols){
    if(isCylinder == 0){
      returnCol = nxtCol-cols;
    }
    else{
      return -1;
    }    
  }
  else if(nxtCol < 1){
    if(isCylinder == 0){
      returnCol = nxtCol + cols;
    }
    else{
      return -1;
    }
  }
  else{ returnCol = nxtCol;}
  returnPos = returnCol + rows * (nxtRow-1); 
  return returnPos;
}
