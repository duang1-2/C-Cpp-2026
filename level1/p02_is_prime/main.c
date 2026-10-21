#include <stdio.h>
int is_prime(int n)
{
    if (n <= 1)
    {
        return 0;
    }
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            return 0;
        }
    }
    return 1;
}

int main(void)
{
    int n;
    printf("请输入一个正整数n：");
    scanf("%d", &n);

    if (is_prime(n))
    {
        printf("%d 是素数\n", n);
    }
    else
    {
        printf("%d 不是素数\n", n);
    }

    return 0;
}