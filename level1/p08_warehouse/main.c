#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 100
#define FILE_NAME "inventory.txt"


typedef struct {
    char model[50];
    int quantity;
} Item;

Item inventory[MAX_ITEMS];
int itemCount = 0;

void showMenu();
void displayInventory();
void stockIn();
void stockOut();
void loadData();
void saveData();

int main() {
    int choice;


    loadData();


    while (1) {
        showMenu();
        printf("请输入您的选择 (1-4): ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("输入无效，请输入数字！\n");
            continue;
        }

        switch (choice) {
            case 1:
                displayInventory();
                break;
            case 2:
                stockIn();
                break;
            case 3:
                stockOut();
                break;
            case 4:
                // 2. 退出时保存库存数据
                saveData();
                printf("数据已保存，退出程序。再见！\n");
                return 0;
            default:
                printf("无效的选择，请重新输入！\n");
        }
    }
    return 0;
}


void showMenu() {
    printf("\n=================================\n");
    printf("        简单进销存管理系统\n");
    printf("=================================\n");
    printf("  1. 显示存货列表\n");
    printf("  2. 入库\n");
    printf("  3. 出库\n");
    printf("  4. 退出程序\n");
    printf("=================================\n");
}

void displayInventory() {
    printf("\n--- 当前存货列表 ---\n");
    if (itemCount == 0) {
        printf("当前库存为空。\n");
        return;
    }

    printf("%-20s\t%s\n", "货物型号", "数量");
    printf("---------------------------------\n");
    for (int i = 0; i < itemCount; i++) {
        printf("%-20s\t%d\n", inventory[i].model, inventory[i].quantity);
    }
    printf("---------------------------------\n");
}

void stockIn() {
    char model[50];
    int qty;

    printf("\n--- 货物入库 ---\n");
    printf("请输入要入库的货物型号: ");
    scanf("%49s", model);
    printf("请输入入库数量: ");
    scanf("%d", &qty);

    if (qty <= 0) {
        printf("入库数量必须大于0！\n");
        return;
    }


    int found = 0;
    for (int i = 0; i < itemCount; i++) {
        if (strcmp(inventory[i].model, model) == 0) {
            inventory[i].quantity += qty;
            found = 1;
            printf("入库成功！%s 的现有数量为: %d\n", model, inventory[i].quantity);
            break;
        }
    }


    if (!found) {
        if (itemCount < MAX_ITEMS) {
            strcpy(inventory[itemCount].model, model);
            inventory[itemCount].quantity = qty;
            itemCount++;
            printf("入库成功！新增货物 %s，当前数量: %d\n", model, qty);
        } else {
            printf("库存已满，无法添加新货物！\n");
        }
    }
}


void stockOut() {
    char model[50];
    int qty;

    printf("\n--- 货物出库 ---\n");
    printf("请输入要出库的货物型号: ");
    scanf("%49s", model);
    printf("请输入出库数量: ");
    scanf("%d", &qty);

    if (qty <= 0) {
        printf("出库数量必须大于0！\n");
        return;
    }


    int found = -1;
    for (int i = 0; i < itemCount; i++) {
        if (strcmp(inventory[i].model, model) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("未找到该型号的货物！出库失败。\n");
        return;
    }


    if (inventory[found].quantity >= qty) {
        inventory[found].quantity -= qty;
        printf("出库成功！%s 的现有数量为: %d\n", model, inventory[found].quantity);
    } else {
        printf("库存不足！当前 %s 仅剩 %d 个。\n", model, inventory[found].quantity);
    }
}void loadData() {
    FILE *fp = fopen(FILE_NAME, "r");
    if (fp == NULL) {
        // 文件不存在（首次运行），直接返回即可
        return;
    }

    itemCount = 0;

    while (fscanf(fp, "%49s %d", inventory[itemCount].model, &inventory[itemCount].quantity) == 2) {
        itemCount++;
        if (itemCount >= MAX_ITEMS) {
            printf("警告：库存记录已达到最大限制，部分数据可能未加载。\n");
            break;
        }
    }
    fclose(fp);
    printf("已成功加载 %d 条库存记录。\n", itemCount);
}


void saveData() {
    FILE *fp = fopen(FILE_NAME, "w");
    if (fp == NULL) {
        printf("错误：无法保存文件（可能是权限问题）！\n");
        return;
    }

    for (int i = 0; i < itemCount; i++) {
        fprintf(fp, "%s %d\n", inventory[i].model, inventory[i].quantity);
    }
    fclose(fp);
}