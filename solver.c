#include<stdio.h>
#include<string.h>

#define ROWS 9
#define COLS 9

/* Start working on the solution. */

void printBoard(int board[ROWS][COLS]);
int fillBoard(int board[ROWS][COLS], char* filename);
int existsInSector(int board[ROWS][COLS], int row, int col, int number);
int existsInRow(int board[ROWS][COLS], int row, int col, int number);
int existsInCol(int board[ROWS][COLS], int row, int col, int number);
int numberIsValid(int board[ROWS][COLS], int row, int col, int number);

/* TODO */
int findUnassignedCell(int board[ROWS][COLS], int *row, int *col);
int solve(int board[ROWS][COLS]);

int main(int argc, char* argv[]){

  int board[ROWS][COLS];
  char filename[100];

  strcat(filename, "./");

  if(argc < 2){
    printf("Pass the filename that contains unsolved sudoku as the first parameter.\n");
    return 1;
  } else {
    strcat(filename, argv[1]);
    printf("\nReading from file '%s'...\n", filename);
  }

  if(!fillBoard(board, filename)){
    printf("Could not open file %s \n", filename);
    return 0;
  }

  printBoard(board);

  if( solve(board) ){
    printf("Solved!\n");
    printBoard(board);
  }

  return 0;
}

/* TODO */
int findUnassignedCell(int board[ROWS][COLS], int *row, int *col) {
  for(int i=0; i<9 ;i++) {
    for(int j=0; j<9 ;j++) {
      if(board[i][j] == 0) {
        *row = i;
        *col = j;
        return 1;
      }
    }
  }

  /* No unassigned cell left. */
  return 0;
}

/* TODO  TEST*/
int solve(int board[ROWS][COLS]){

  int unassignedRow;
  int unassignedCol;

  if(!findUnassignedCell(board, &unassignedRow, &unassignedCol)){
    /* Solution found. */
    return 1;
  }

  for(int newNum=1; newNum<10 ;newNum++){

    if(numberIsValid(board, unassignedRow, unassignedCol, newNum)){
      board[unassignedRow][unassignedCol] = newNum;

      if(solve(board)){
        return 1;
      }

      board[unassignedRow][unassignedCol] = 0;
    }
  }

  return 0;
}

int existsInRow(int board[ROWS][COLS], int row, int col, int number) {
  for(int i=0; i<9 ;i++){
    if(board[row][i] == number) {
      return 1;
    }
  }

  return 0;
}

int existsInCol(int board[ROWS][COLS], int row, int col, int number) {
  for(int i=0; i<9 ;i++){
    if(board[i][col] == number) {
      return 1;
    }
  }

  return 0;
}

/* Returns 1 if the number exists in the sector, 0 otherwise. */
int existsInSector(int board[ROWS][COLS], int row, int col, int number) {
  int startRow = 3 * (row/3);
  int endRow = startRow + 3;
  int startCol = 3 * (col/3);
  int endCol = startCol + 3;

  for(int i = startRow; i < endRow ;i++){
    for(int j = startCol; j < endCol ;j++){
      if(board[i][j] == number) return 1;
    }
  }

  return 0;
}

/* Returns 1 if the number can be placed in that position,
  returns 0 otherwise. */
int numberIsValid(int board[ROWS][COLS], int row, int col, int number) {
  return !(existsInCol(board, row, col, number)
        || existsInRow(board, row, col, number)
        || existsInSector(board, row, col, number));
}

int fillBoard(int board[ROWS][COLS], char* filename) {
  FILE* fp;
  fp = fopen(filename, "r");

  if(fp == NULL){
    return 0;
  }

  for(int i=0; i<ROWS ;i++){
    char line[20];
    fgets(line, 20, fp);

    for(int j=0; j<COLS ;j++) {
      board[i][j] = line[j] - '0';
    }
  }
  fclose(fp);

  return 1;
}

void printBoard(int board[ROWS][COLS]) {
  char* horizontalBar = "-------------------------";

  printf("%s\n", horizontalBar);
  for(int i=0; i<ROWS ;i++){
    printf("| ");
    for(int j=0; j<COLS ;j++){
      if(j%3 == 0 && j != 0){
        printf("| ");
      }
      printf("%d ", board[i][j]);
    }
    printf("|");
    printf("\n");
    if(i%3 == 2){
      printf("%s\n", horizontalBar);
    }
  }
}
