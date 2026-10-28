#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define MAX_ROWS 20
#define MAX_COLS 30
#define MAX_LEVELS 10


/* 地图字符常量 */
#define WALL    '#'
#define FLOOR   ' '
#define GOAL    '.'
#define BOX     '$'
#define BOX_ON  '*'
#define PLAYER  '@'
#define PLAYER_ON '+'

typedef struct {
    char map[MAX_ROWS][MAX_COLS];
    int rows;
    int cols;
    int player_r, player_c;
    int box_count;
    int goal_count;
    int boxes_on_goal;
} Game;

/* 读取关卡文件 */
int load_level(const char *filename, Game *g) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("无法打开关卡文件: %s\n", filename);
        return 0;
    }

    g->rows = 0; g->cols = 0;
    g->box_count = 0; g->goal_count = 0; g->boxes_on_goal = 0;
    char line[MAX_COLS];

    while (fgets(line, sizeof(line), fp)) {
        /* 去掉换行符 */
        int len = strlen(line);
        while (len > 0 && (line[len-1] == '\n' || line[len-1] == '\r'))
            line[--len] = '\0';
        if (len == 0) continue;
        if (g->rows >= MAX_ROWS) break;

        strncpy(g->map[g->rows], line, MAX_COLS - 1);
        g->map[g->rows][MAX_COLS - 1] = '\0';
        if (len > g->cols) g->cols = len;
        g->rows++;
    }
    fclose(fp);

    /* 填充空格，统计信息 */
    for (int r = 0; r < g->rows; r++) {
        int len = strlen(g->map[r]);
        for (int c = len; c < g->cols; c++)
            g->map[r][c] = ' ';
        g->map[r][g->cols] = '\0';

        for (int c = 0; c < g->cols; c++) {
            char ch = g->map[r][c];
            if (ch == PLAYER || ch == PLAYER_ON) {
                g->player_r = r; g->player_c = c;
            }
            if (ch == BOX || ch == BOX_ON) g->box_count++;
            if (ch == GOAL || ch == PLAYER_ON) g->goal_count++;
            if (ch == BOX_ON) g->boxes_on_goal++;
        }
    }
    return 1;
}

/* 打印地图 */
void print_map(Game *g, int level, int steps) {
    system("cls");  /* Windows；Linux/Mac 用 "clear" */
    printf("======== 推箱子 - 第 %d 关 ========\n", level);
    printf("步数: %d\n\n", steps);
    for (int r = 0; r < g->rows; r++) {
        printf("%s\n", g->map[r]);
    }
    printf("\n操作: W/A/S/D 移动, R 重玩, Q 退出\n");
}

/* 判断是否胜利 */
int check_win(Game *g) {
    int cnt = 0;
    for (int r = 0; r < g->rows; r++)
        for (int c = 0; c < g->cols; c++)
            if (g->map[r][c] == BOX_ON) cnt++;
    return cnt == g->box_count && g->box_count > 0;
}

/* 移动逻辑 */
int try_move(Game *g, int dr, int dc, int *steps) {
    int nr = g->player_r + dr;
    int nc = g->player_c + dc;
    if (nr < 0 || nr >= g->rows || nc < 0 || nc >= g->cols) return 0;

    char target = g->map[nr][nc];
    if (target == WALL) return 0;

    /* 目标位置为箱子，尝试推箱子 */
    if (target == BOX || target == BOX_ON) {
        int br = nr + dr, bc = nc + dc;
        if (br < 0 || br >= g->rows || bc < 0 || bc >= g->cols) return 0;
        char behind = g->map[br][bc];
        if (behind == WALL || behind == BOX || behind == BOX_ON) return 0;

        /* 移动箱子 */
        g->map[br][bc] = (behind == GOAL) ? BOX_ON : BOX;
        /* 玩家原位置 */
        char under = g->map[g->player_r][g->player_c];
        g->map[g->player_r][g->player_c] = (under == PLAYER_ON) ? GOAL : FLOOR;
        /* 玩家新位置 */
        g->map[nr][nc] = (target == BOX_ON) ? PLAYER_ON : PLAYER;
        g->player_r = nr; g->player_c = nc;
        (*steps)++;
        return 1;
    }

    /* 目标位置为地板或目标 */
    if (target == FLOOR || target == GOAL) {
        char under = g->map[g->player_r][g->player_c];
        g->map[g->player_r][g->player_c] = (under == PLAYER_ON) ? GOAL : FLOOR;
        g->map[nr][nc] = (target == GOAL) ? PLAYER_ON : PLAYER;
        g->player_r = nr; g->player_c = nc;
        (*steps)++;
        return 1;
    }

    return 0;
}

/* 保存分数 */
void save_score(int level, int steps) {
    FILE *fp = fopen("scores.txt", "a");
    if (!fp) {
        printf("无法保存分数!\n");
        return;
    }
    fprintf(fp, "Level %d: %d 步\n", level, steps);
    fclose(fp);
    printf("\n本关得分（步数）: %d，已记录到 scores.txt\n", steps);
}

/* 主程序 */
int main() {
    int total_levels = 0;
    char level_files[MAX_LEVELS][64];

    /* 自动搜索关卡文件 level1..levelN */
    for (int i = 1; i <= MAX_LEVELS; i++) {
        char name[64];
        sprintf(name, "levels/level%d.txt", i);
        FILE *fp = fopen(name, "r");
        if (fp) {
            fclose(fp);
            strcpy(level_files[total_levels], name);
            total_levels++;
        } else {
            break;
        }
    }

    if (total_levels == 0) {
        printf("未找到任何关卡文件！请将 level1.txt 等放入 levels 目录。\n");
        return 1;
    }

    printf("共发现 %d 个关卡，按任意键开始...\n", total_levels);
    _getch();

    int total_steps = 0;
    for (int lv = 0; lv < total_levels; lv++) {
        Game g;
        if (!load_level(level_files[lv], &g)) {
            printf("加载关卡失败: %s\n", level_files[lv]);
            return 1;
        }


        int steps = 0;
        int running = 1;

        while (running) {
            print_map(&g, lv + 1, steps);

            if (check_win(&g)) {
                printf("\n*** 恭喜！第 %d 关通关！用了 %d 步 ***\n", lv + 1, steps);
                save_score(lv + 1, steps);
                total_steps += steps;
                printf("按任意键进入下一关...\n");
                _getch();
                break;
            }

            int ch = _getch();
            if (ch == 0 || ch == 224) ch = _getch();  /* 方向键 */

            switch (ch) {
                case 'w': case 'W': case 72: try_move(&g, -1, 0, &steps); break;
                case 's': case 'S': case 80: try_move(&g,  1, 0, &steps); break;
                case 'a': case 'A': case 75: try_move(&g,  0,-1, &steps); break;
                case 'd': case 'D': case 77: try_move(&g,  0, 1, &steps); break;
                case 'r': case 'R': {
                    char fname[64];
                    strcpy(fname, level_files[lv]);
                    load_level(fname, &g);
                    steps = 0;
                    break;
                }
                case 'q': case 'Q': running = 0; break;
            }
        }
    }

    printf("\n========== 全部通关！总步数: %d ==========\n", total_steps);
    printf("分数记录见 scores.txt\n");
    system("pause");
    return 0;
}