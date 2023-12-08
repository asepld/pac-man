#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define ROWS 20
#define COLS 30


char maze[ROWS][COLS] = {
    "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
    "XooooooooooooXXooooooooooooooX",
    "XoXXXXXoXXXXXoXXoXXXXXoXXXXX.X",
    "XoXXXXXoXXXXXoXXoXXXXXoXXXXXoX",
    "XoXXXXXoXXXXXoXXoXXXXXoXXXXX.X",
    "XooooooooooooooooooooooooooooX",
    "XoXXXXXoXXoXXXXXXXXoXXoXXXXXoX",
    "XoooooooXXoooooooooooXXooooooX",
    "XXXXXXoXXXXXoXXXoXoXXXXoXXXXXX",
    "X    XoXXXXXoXXXoXoXXXXooooooX",
    "XXXXXXoXXXXXoXXXoXoXXXXoXXXXXX",
    "oooooooooooooooooooooooooooooX",
    "XXXXXXoXXXXXoXXXXXoXXXXXoXXXXX",
    "     XoXXooooXXXXXoXXXoooX   X",
    "XXXXXXoXXoXXXXXXXXXoXXoXXXXXXX",
    "XooooooooooooooooooooooooooooX",
    "XoXXXXXoXXXXXXXXXXXoXXXXXoXXoX",
    "XoooooXooooooooXXooooooooooo.X",
    "XXXXXoooXXXoXXXXXXXXXoXXXoXXXX",
    "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
};

int pacman_row = 3;
int pacman_col = 13;
int score = 0;

int ghost1_row = 9;
int ghost1_col = 15;

int ghost2_row = 9;
int ghost2_col = 16;

void draw_maze();
void move_pacman(char input);
void move_ghosts();
void move_ghost(int *ghost_row, int *ghost_col);
void move_ghost2();

int main() {
    char input;

    draw_maze();

    do {
        check_collision();
        input = getch();
        move_pacman(input);
        move_ghosts();
        draw_maze();
    } while (input != 'q');

    return 0;
}

void draw_maze() {
    system("cls");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (maze[i][j] == 'X') {
                printf("%c", 219);
            } else if (i == pacman_row && j == pacman_col) {
                printf("C");
            } else if (i == ghost1_row && j == ghost1_col) {
                printf("1");
            } else if (i == ghost2_row && j == ghost2_col) {
                printf("2");
            } else if (maze[i][j] == 'o') {
                printf(".");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("Score: %d\n", score);
}

void move_pacman(char input) {
    switch (input) {
        case 'w':
            if (maze[pacman_row - 1][pacman_col] != 'X') {
                pacman_row--;
            }
            break;
        case 'a':
            if (maze[pacman_row][pacman_col - 1] != 'X') {
                pacman_col--;
            }
            break;
        case 's':
            if (maze[pacman_row + 1][pacman_col] != 'X') {
                pacman_row++;
            }
            break;
        case 'd':
            if (maze[pacman_row][pacman_col + 1] != 'X') {
                pacman_col++;
            }
            break;
        default:
            break;
    }

    // Check if pacman has eaten a dot
    if (maze[pacman_row][pacman_col] == 'o') {
        maze[pacman_row][pacman_col] = ' ';
        score++;
    }

    draw_maze();

    // Check if all points have been collected
    int points_left = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (maze[i][j] == 'o') {
                points_left = 1;
                break;
            }
        }
        if (points_left) {
            break;
        }
    }

    // End the game if all points have been collected
    if (!points_left) {
        printf("WIN\n");
        exit(0);
    }
}


void move_ghosts() {
move_ghost(&ghost1_row, &ghost1_col);
move_ghost2();
}

void move_ghost2() {
int direction = rand() % 4;
switch (direction) {
case 0:
if (maze[ghost2_row - 1][ghost2_col] != 'X') {
ghost2_row--;
}
break;
case 1:
if (maze[ghost2_row][ghost2_col + 1] != 'X') {
ghost2_col++;
}
break;
case 2:
if (maze[ghost2_row + 1][ghost2_col] != 'X') {
ghost2_row++;
}
break;
case 3:
if (maze[ghost2_row][ghost2_col - 1] != 'X') {
ghost2_col--;
}
break;
}
}

void move_ghost(int *ghost_row, int *ghost_col) {
int direction = rand() % 4;
switch (direction) {
case 0:
if (maze[*ghost_row - 1][*ghost_col] != 'X') {
(*ghost_row)--;
}
break;
case 1:
if (maze[*ghost_row][*ghost_col + 1] != 'X') {
(*ghost_col)++;
}
break;
case 2:
if (maze[*ghost_row + 1][*ghost_col] != 'X') {
(*ghost_row)++;
}
break;
case 3:
if (maze[*ghost_row][*ghost_col - 1] != 'X') {
(*ghost_col)--;
}
break;
}
}

void check_collision() {
    if (pacman_row == ghost1_row && pacman_col == ghost1_col) {
        printf("You were caught by Ghost 1!\n");
        exit(0);

    }
    if (pacman_row == ghost2_row && pacman_col == ghost2_col) {
        printf("You were caught by Ghost 2!\n");
        exit(0);
    }
}


void check_score() {
if (maze[pacman_row][pacman_col] == '.') {
maze[pacman_row][pacman_col] = ' ';
score += 10;
}
}


