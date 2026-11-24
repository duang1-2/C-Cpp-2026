#include <stdio.h>
#include <conio.h>
#include <windows.h>


char maze[10][10] = {
    {'#','#','#','#','#','#','#','#','#','#'},
    {'#',' ',' ',' ','#',' ',' ',' ',' ','#'},
    {'#',' ','#',' ','#',' ','#','#',' ','#'},
    {'#',' ','#',' ',' ',' ',' K','#',' ','#'},
    {'#',' ','#','#','#','#',' ','#',' ','#'},
    {'#',' ',' ',' ',' ','#',' ',' ',' ','#'},
    {'#','#','#','#',' ','#','#','#',' ','#'},
    {'#',' ',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#',' ','#','#','#','#','#','#','E','#'},
    {'#','#','#','#','#','#','#','#','#','#'},
};

int player_x = 1;
int player_y = 1;


void clear() {
    system("cls");
}


void print_maze() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (i == player_x && j == player_y) {
                printf("@");
            } else {
                printf("%c", maze[i][j]);
            }
        }
        printf("\n");
    }
    printf("操作：↑ ↓ ← → 方向键移动 | 到达E出口获胜！\n");
}


void move(int dx, int dy) {
    int nx = player_x + dx;
    int ny = player_y + dy;

    if (maze[nx][ny] != '#') {
        player_x = nx;
        player_y = ny;
    }
}

int main() {
    int ch;
    while (1) {
        clear();
        print_maze();

        if (maze[player_x][player_y] == 'E') {
            printf("🎉 恭喜！你赢得游戏！\n");
            break;
        }

        ch = _getch();

        if (ch == 0xE0) {
            ch = _getch();
            switch (ch) {
                case 72: move(-1, 0); break; // ↑
                case 80: move(1, 0); break;  // ↓
                case 75: move(0, -1); break; // ←
                case 77: move(0, 1); break;  // →
            }
        }
    }
    _getch();
    return 0;
}