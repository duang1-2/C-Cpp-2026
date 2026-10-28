#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define WIDTH  21
#define HEIGHT 15

#define WALL    '#'
#define PLAYER  '@'
#define EXIT    'E'
#define PATH    ' '


int maze[HEIGHT][WIDTH] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
    {1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1},
    {1,0,1,0,0,0,0,0,1,0,1,0,0,0,1,0,0,0,1,0,1},
    {1,0,1,1,1,1,1,0,1,0,1,1,1,0,1,0,1,1,1,0,1},
    {1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
    {1,1,1,0,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1},
    {1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,1},
    {1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,0,1,0,1},
    {1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,1},
    {1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,0,1,1,1,0,1},
    {1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1},
    {1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int playerX = 1;
int playerY = 1;
int exitX   = 19;
int exitY   = 13;


void hideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}


void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawMaze() {
    gotoxy(0, 0);
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == playerY && j == playerX)
                printf("%c", PLAYER);
            else if (i == exitY && j == exitX)
                printf("%c", EXIT);
            else if (maze[i][j] == 1)
                printf("%c", WALL);
            else
                printf("%c", PATH);
        }
        printf("\n");
    }
    printf("\n使用方向键移动，按 Q 退出\n");
}


int movePlayer(int dx, int dy) {
    int nx = playerX + dx;
    int ny = playerY + dy;


    if (nx < 0 || nx >= WIDTH || ny < 0 || ny >= HEIGHT)
        return 0;


    if (maze[ny][nx] == 1)
        return 0;

    playerX = nx;
    playerY = ny;
    return 1;

K

int isWin() {
    return (playerX == exitX && playerY == exitY);
}

int main() {

    SetConsoleOutputCP(65001);

    hideCursor();
    drawMaze();

    int running = 1;
    while (running) {
        if (_kbhit()) {
            int key = _getch();


            if (key == 0 || key == 224) {
                int arrow = _getch();
                switch (arrow) {
                    case 72: movePlayer( 0, -1); break;
                    case 80: movePlayer( 0,  1); break; 
                    case 75: movePlayer(-1,  0); break;
                    case 77: movePlayer( 1,  0); break;
                }
                drawMaze();

                if (isWin()) {
                    gotoxy(0, HEIGHT + 2);
                    printf("\n🎉 恭喜你，你赢得了游戏！🎉\n");
                    running = 0;
                }
            }

            else if (key == 'q' || key == 'Q') {
                running = 0;
            }
        }
    }

    printf("\n游戏结束，按任意键退出...\n");
    _getch();
    return 0;
}
