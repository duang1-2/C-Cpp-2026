#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 100
#define FILENAME "inventory.txt"

typedef struct {
    char model[50];
    int quantity;


Item inventory[MAX_ITEMS];
int itemCount = 0;

void loadFromFile();
void saveToFile();
void displayMenu();
void showInventory();
void stockIn();
void stockOut();
int findItem(const char *model);


int main() {
    int choice;

    loadFromFile();

    while (1) {
        displayMenu();
        printf("请输入您的选择 (1-4): ");
        if (scanf("%d", &choice) != 1) {
            // 处理输入非数字的情况
            while (getchar() != '\n');
            printf("无效输入，请输入数字！\n");
            continue;
        }

        switch (choice) {
            case 1:
                showInventory();
                break;
            case 2:
                stockIn();
                break;
            case 3:
                stockOut();
                break;
            case 4:
                saveToFile(); // 退出前保存数据
                printf("数据已保存。感谢使用，再见！\n");
                return 0;
            default:
                printf("无效的选择，请重新输入！\n");
        }
    }
    return 0;
}



void displayMenu() {
    printf("\n");
    printf("=================================\n");
    printf("        简单进销存管理系统       \n");
    printf("=================================\n");
    printf("  1. 显示存货列表\n");
    printf("  2. 入库\n");
    printf("  3. 出库\n");
    printf("  4. 退出程序\n");
    printf("=================================\n");
}


void loadFromFile() {
    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        printf("提示：未找到数据文件 %s，将创建新的库存。\n", FILENAME);
        return;
    }

    itemCount = 0;
    while (fscanf(fp, "%s %d", inventory[itemCount].model, &inventory[itemCount].quantity) == 2) {
        itemCount++;
        if (itemCount >= MAX_ITEMS) {
            printf("警告：库存容量已达上限，部分数据未读取。\n");
            break;
        }
    }
    fclose(fp);
    printf("成功读取 %d 条库存记录。\n", itemCount);
}


void saveToFile() {
    FILE *fp = fopen(FILENAME, "w");
    if (fp == NULL) {
        printf("错误：无法保存数据文件！\n");
        return;
    }

    for (int i = 0; i < itemCount; i++) {
        fprintf(fp, "%s %d\n", inventory[i].model, inventory[i].quantity);
    }
    fclose(fp);
}


void showInventory() {
    printf("\n--- 当前存货列表 ---\n");
    if (itemCount == 0) {
        printf("（暂无库存）\n");
        return;
    }

    printf("%-20s %-10s\n", "型号", "数量");
    printf("------------------------------\n");
    for (int i = 0; i < itemCount; i++) {
        printf("%-20s %-10d\n", inventory[i].model, inventory[i].quantity);
    }
}


int findItem(const char *model) {
    for (int i = 0; i < itemCount; i++) {
        if (strcmp(inventory[i].model, model) == 0) {
            return i;
        }
    }
    return -1;
}


void stockIn() {
    char model[50];
    int qty;

    printf("\n--- 货物入库 ---\n");
    printf("请输入入库货物型号: ");
    scanf("%s", model);
    printf("请输入入库数量: ");
    scanf("%d", &qty);

    if (qty <= 0) {
        printf("入库数量必须大于0！\n");
        return;
    }

    int index = findItem(model);
    if (index != -1) {

        inventory[index].quantity += qty;
        printf("入库成功！[%s] 当前总数量: %d\n", model, inventory[index].quantity);
    } else {

        if (itemCount >= MAX_ITEMS) {
            printf("库存已满，无法添加新型号！\n");
            return;
        }
        strcpy(inventory[itemCount].model, model);
        inventory[itemCount].quantity = qty;
        itemCount++;
        printf("入库成功！已添加新型号 [%s]，数量: %d\n", model, qty);
    }

    saveToFile();
}

void stockOut() {
    char model[50];
    int qty;

    printf("\n--- 货物出库 ---\n");
    printf("请输入出库货物型号: ");
    scanf("%s", model);

    int index = findItem(model);
    if (index == -1) {
        printf("出库失败：未找到型号为 [%s] 的货物。\n", model);
        return;
    }

    printf("请输入出库数量: ");
    scanf("%d", &qty);

    if (qty <= 0) {
        printf("出库数量必须大于0！\n");
        return;
    }

    if (inventory[index].quantity < qty) {
        printf("出库失败：库存不足！当前库存只有 %d\n", inventory[index].quantity);
    } else {
        inventory[index].quantity -= qty;
        printf("出库成功！[%s] 剩余数量: %d\n", model, inventory[index].quantity);


    }

    saveToFile();
}