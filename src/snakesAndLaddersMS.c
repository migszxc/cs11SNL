#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char staticElements[2][3];
  /* staticElements - a multidimensional array that will contain the non-moving
  elements of a cell such as snake heads/tails and ladder bottom/tops. These
  will be denoted by "H#", "T#", "B#", and "A#", respectively. The # will
  be replaced by a unique number to differ each snakeHead from each other. */
  char players[2][2];
  /* players - a multidimensional array that will contain the players of a
  cell. These will be denoted by "P#" with the # being replaced with which
  player number is in the cell. There can be a maximum of 4 players in a
  cell. (You can only have 4 players in the game)*/
}cell;

void printBoard(cell board[]);

int main() {
  // declarations and initializations:
  cell board[8][8];
  // board - an 8 x 8 multidimensional array made of datatype: "cell".
  // read board.txt file and fill up 'board' with the data gathered.
  int i, j;
  // i - counter pour for loop
  FILE *fp;
  fp = fopen("board.txt", "r");
  // if the file does not exist, create a new one.
  if ( ferror(fp) ) {
    printf("\"board.txt\" does not exist, creating a new one.\n");
    fclose(fp);
    fp = fopen("board.txt","w");
    for (j = 0; j < 8; j += 1) {
      for (i = 0; i < 8; i += 1) {
        fprintf(fp, "|  ");
      }
      fprintf(fp, "|\n");
    }
  }
  fclose(fp);
}
