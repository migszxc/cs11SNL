#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* playah - a structure made for each player where we can store information such
as their position in the board*/
typedef struct {
  int x;
  // x - position in the x coordinate
  int y;
  // y - position in the y coordinate
}playah;

/* cell - a structure made for each "cell" in the board that stores information
 such as players and staticElements present in that specifi cell*/
typedef struct {
  char staticElements[2][2];
  /* staticElements - a multidimensional array that will contain the non-moving
  elements of a cell such as snake heads/tails and ladder beginning/ends. These
  will be denoted by "H#", "T#", "B#", and "E#", respectively. The # will
  be replaced by a unique number to differ each snakeHead from each other.
  There can only be a maximum of two static elements per cell. */
  char players[2][2];
  /* players - a multidimensional array that will contain the players of a
  cell. These will be denoted by a symbol. There can be a maximum of 4 players
  in a cell. (You have 4 players in the game.)*/
}cell;

void printBoard(cell board[][8]);
int isPlayerPresent(cell box);
void advancePlayer(cell board[][8], int *x, int *y, int px, int py, int steps);

int main() {
  srand(time(NULL));
  // declarations and initializations:
  playah p1, p2, p3, p4;
  p1.x = 0; p1.y = 7;
  p2.x = 0; p2.y = 7;
  p3.x = 0; p3.y = 7;
  p4.x = 0; p4.y = 7;
  // setting each player's position to be on the bottom left of the board
  cell board[8][8];
  // board - an 8 x 8 multidimensional array of datatype: "cell".
  int i, j, k, l, r, tapak;
  // counters pour for loop
  char c, temp[2], plyr, pause;
  // char siu
  /* go through each cell in the board and initialize staticElements
   and players with ' ' */
  for (j = 0; j < 8; j += 1) {
    for (i = 0; i < 8; i += 1) {
      for (k = 0; k < 2; k += 1) {
        for (l = 0; l < 2; l += 1) {
          board[j][i].staticElements[k][l] = ' ';
        }
      }
      for (k = 0; k < 2; k += 1) {
        for (l = 0; l < 2; l += 1) {
          board[j][i].players[k][l] = ' ';
        }
      }
    }
  }
  // open 'board.txt' and fill up the cell array 'board' with the information
  FILE *fp;
  fp = fopen("board.txt", "r");
  // first level loop for each row
  for (j = 0; j < 8; j += 1) {
    // second level loop for the individual cells
    // top half of each cell
    for (i = 0; i < 8; i += 1) {
      c = fgetc(fp);
      if ( c == '|') {
        temp[0] = fgetc(fp);
        temp[1] = fgetc(fp);
        board[j][i].staticElements[0][0] = temp[0];
        board[j][i].staticElements[0][1] = temp[1];
      } else {
        i -= 1;
      }
    }
    // bottom half of each cell
    for (i = 0; i < 8; i += 1) {
      c = fgetc(fp);
      if ( c == '|') {
        temp[0] = fgetc(fp);
        temp[1] = fgetc(fp);
        board[j][i].staticElements[1][0] = temp[0];
        board[j][i].staticElements[1][1] = temp[1];
      } else {
        i -= 1;
      }
    }
  }
  fclose(fp);
  // prompt user to pick whatever player logo they want
  printf("Enter any ASCII character besides  '!', '@', and '#' to be your player token: ");
  scanf("%c", &plyr);
  /*set the bottom left corner to be the starting point and then place all the
  players to be there */
  board[7][0].players[0][0] = plyr;
  board[7][0].players[1][0] = '@';
  board[7][0].players[0][1] = '#';
  board[7][0].players[1][1] = '!';
  printBoard(board);
  pause = getchar();
  for (;;) {
    //printf("Enter how many steps to move forward: ");
    //scanf("%d", &tapak);
    r = rand() % 7;
    advancePlayer(board, &(p1.x), &(p1.y), 0, 0, r);
    printBoard(board);
    printf("Player 1 moves %d spaces!", r);
    pause = getchar();
    r = rand() % 7;
    advancePlayer(board, &(p2.x), &(p2.y), 1, 0, r);
    printBoard(board);
    printf("Player 2 moves %d spaces!", r);
    pause = getchar();
    r = rand() % 7;
    advancePlayer(board, &(p3.x), &(p3.y), 0, 1, r);
    printBoard(board);
    printf("Player 3 moves %d spaces!", r);
    pause = getchar();
    r = rand() % 7;
    advancePlayer(board, &(p4.x), &(p4.y), 1, 1, r);
    printBoard(board);
    printf("Player 4 moves %d spaces!", r);
    pause = getchar();
  }
}
/* function that moves a player[px][py] in cell board[*x][*y]  'steps' amount
forward */
void advancePlayer(cell board[][8], int *x, int *y, int px, int py, int steps) {
  if (steps == 0) return;
  char plyr;
  int LR, curx, cury, i;
  // LR - a variable to tell which direction the player should be moving

  plyr = board[*y][*x].players[py][px];
  // store the player character into the 'plyr' variable
  if (*y % 2 == 0) {
    LR = 0;
  } else {
    LR = 1;
  }
  // if the player is on an even numbered row, it's moving towards the left(0)
  // odd numbered row towards the right(1)
  curx = *x;
  cury = *y;
  // store current player position into 'curx' and 'cury'

  while (steps > 0) {
    // break loop if there are no more steps to be made
    if (steps == 0) break;
    // if the player is on an odd numbered row
    if (LR == 1) {
      // move the player towards the end of the row(right side)
      for (i = curx; i < 7; i += 1) {
        curx += 1;
        steps -= 1;
        // so long as there are steps to be made
        if (steps == 0) break;
      }
    // otherwise if the player is on an even numbered row
    } else if (LR == 0) {
      // move the player to the other end of the row (left side)
      for (i = curx; i > 0; i -= 1) {
        curx -= 1;
        steps -= 1;
        // so long as there are steps to be made
        if (steps == 0) break;
      }
    }
    /* if the player is on the right end of the row and it still has more steps
    to nake, move it up*/
    if (LR == 1 && curx == 7 && steps > 0) {
      cury -= 1;
      steps -= 1;
      LR = 0;
      if (steps == 0) break;
    /* if the player is on the left end of the row and it still has more steps
    to make, move it up*/
    } else if (LR == 0 && curx == 0 && steps > 0) {
      cury -= 1;
      steps -= 1;
      LR = 1;
      if (steps == 0) break;
    }
    if (steps == 0) break;
  }
  // copy plyr char into the new position
  board[cury][curx].players[py][px] = plyr;
  // clear the old position
  board[*y][*x].players[py][px] = ' ';
  // update player information in the main() function
  *x = curx;
  *y = cury;
}

/* function that returns a non-zero value if there is a player present in
cell being checked. returns 0 if there are no players in the cell */
// box - of datatype cell
int isPlayerPresent(cell box) {
  // assume there are no players present in the cell
  int presence = 0;
  if (box.players[0][0] != ' ' ||
  box.players[0][1] != ' ' ||
  box.players[1][0] != ' ' ||
  box.players[1][1] != ' ') {
    // if the cell player data is not empty the there is a player present
    presence = 1;
  }
  // return
  return presence;
}

/* function that prints out the current state of the game board */
// board - a multidimensional array of datatype cell
void printBoard(cell board[][8]) {
  // clear the screen
  system("cls");
  // declarations and initializations
  int i, j;
  // i, j - counters for for loop
  char temp[2];
  // char siu
  // print out column labelers
  printf("   ");
  for (i = 1; i <= 8; i += 1) {
    printf("|c%d", i);
  }
  printf("|\n");
  for (j = 0; j < 8; j += 1) {
    printf("|r%d", j + 1);
    // top half of the row
    for (i = 0; i < 8; i += 1) {
      if (isPlayerPresent(board[j][i])) {
        // if the cell contains players, print them out
        temp[0] = board[j][i].players[0][0];
        temp[1] = board[j][i].players[0][1];
      } else {
        // otherwise, print the staticElements in the cell
        temp[0] = board[j][i].staticElements[0][0];
        temp[1] = board[j][i].staticElements[0][1];
      }
      printf("|%c%c",temp[0],temp[1]);
    }
    printf("|\n   ");
    // bottom half of the row
    for (i = 0; i < 8; i += 1) {
      if (isPlayerPresent(board[j][i])) {
        temp[0] = board[j][i].players[1][0];
        temp[1] = board[j][i].players[1][1];
      } else {
        temp[0] = board[j][i].staticElements[1][0];
        temp[1] = board[j][i].staticElements[1][1];
      }
      printf("|%c%c",temp[0],temp[1]);
    }
    printf("|\n");
  }
  printf("Snake Heads: S#\n");
  printf("Snake Tails: T#\n");
  printf("Ladder Beginnings: B#\n");
  printf("Ladder Ends: E#\n");
}
