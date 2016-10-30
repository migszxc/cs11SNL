#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char staticElements[2][2];
  /* staticElements - a multidimensional array that will contain the non-moving
  elements of a cell such as snake heads/tails and ladder bottom/tops. These
  will be denoted by "H#", "T#", "B#", and "A#", respectively. The # will
  be replaced by a unique number to differ each snakeHead from each other.
  There can only be a maximum of two static elements per cell. */
  char players[2][2];
  /* players - a multidimensional array that will contain the players of a
  cell. These will be denoted by a symbol. There can be a maximum of 4 players
  in a cell. (You can only have 4 players in the game.)*/
}cell;

void printBoard(cell board[][8]);

int main() {
  // declarations and initializations:
  cell board[8][8];
  // board - an 8 x 8 multidimensional array made of datatype: "cell".
  // read board.txt file and fill up 'board' with the data gathered.
  int i, j, k;
  // counters pour for loop
  char c, temp[2];
  // char siu
  FILE *fp;
  fp = fopen("rip.txt", "r");
  // every two lines in the .txt file is a row
  for (j = 0; j < 8; j += 1) {
    for (i = 0; i < 8; i += 1) {
      c = fgetc(fp);
      if ( c == '|') {
        temp[0] = fgetc(fp);
        temp[1] = fgetc(fp);
        board[j][i].staticElements[0][0] = temp[0];
        board[j][i].staticElements[0][1] = temp[1];
      } else {
        i -= 1;
        c = fgetc(fp);
      }
    }
    for (i = 0; i < 8; i += 1) {
      c = fgetc(fp);
      if ( c == '|') {
        temp[0] = fgetc(fp);
        temp[1] = fgetc(fp);
        board[j][i].staticElements[1][0] = temp[0];
        board[j][i].staticElements[1][1] = temp[1];
      } else {
        i -= 1;
        c = fgetc(fp);
      }
    }
  }
  // printf("wtf");
  printBoard(board);
  fclose(fp);
}

void printBoard(cell board[][8]) {
  int i, j;
  char temp[2];
  printf("   ");
  for (i = 0; i < 8; i += 1) {
    printf("|c%d", i);
  }
  printf("|\n");
  for (j = 0; j < 8; j += 1) {
    printf("|r%d", j);
    for (i = 0; i < 8; i += 1) {
      temp[0] = board[j][i].staticElements[0][0];
      temp[1] = board[j][i].staticElements[0][1];
      printf("|%c%c",temp[0],temp[1]);
    }
    printf("|\n   ");
    for (i = 0; i < 8; i += 1) {
      temp[0] = board[j][i].staticElements[1][0];
      temp[1] = board[j][i].staticElements[1][1];
      printf("|%c%c",temp[0],temp[1]);
    }
    printf("|\n");
  }
}
