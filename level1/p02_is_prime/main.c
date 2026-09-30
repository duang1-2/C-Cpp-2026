#include <stdio.h>
int main(void)
{
    int n;
    printf("请输入一个正整数n：");
    scanf("%d", &n);
    int a= 1;
    if(n <= 1)
    {
       a = 0;
    }
    else
    {
        for(int i = 2; i*i <= n; i++)
        {
            if(n % i == 0)
            {
                a = 0;
                break;
            }
        }
    }
    if(a== 1)
    {
        printf("%d 是素数\n", n);
    }
    else
    {
        printf("%d 不是素数\n", n);
    }
    return 0;