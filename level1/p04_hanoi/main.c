#include <stdio.h>
void hanoi(int n, char from, char temp, char to)
{
    if (n == 0)
        return;
    hanoi(n - 1, from, to, temp);
    printf("%c -> %c\n", from, to);
    hanoi(n - 1, temp, from, to);
}
int main(void)
{
    int disk_num;
    printf("请输入盘子数量：");
    scanf("%d", &disk_num);

    printf("\n移动步骤：\n");
    hanoi(disk_num, 'A', 'B', 'C');

    return 0;
}