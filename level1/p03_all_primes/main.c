#include <stdio.h>
#include <time.h>

#define MAX 1000

int main(void)
{
    char is_p[MAX+1];
    clock_t t_start = clock();
    for(int i = 0; i <= MAX; i++)
        is_p[i] = 1;
    is_p[0] = is_p[1] = 0;

    for(int i = 2; i*i <= MAX; i++)
    {
        if(is_p[i])
        {
            for(int j = i*i; j <= MAX; j += i)
            {
                is_p[j] = 0;
            }
        }
    }


    printf("2 ~ 1000 的所有素数：\n");
    int count = 0;
    for(int i = 2; i <= MAX; i++)
    {
        if(is_p[i])
        {
            printf("%d ", i);
            count++;
        }
    }

    clock_t t_end = clock();
    double time_used = (double)(t_end - t_start)/CLOCKS_PER_SEC;

    printf("\n\n素数总数：%d\n", count);
    printf("耗时：%.7f 秒\n", time_used);

    return 0;
}