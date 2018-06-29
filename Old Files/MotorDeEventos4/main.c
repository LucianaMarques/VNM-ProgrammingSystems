#include <stdio.h>
#include <stdlib.h>
struct x {
    int a = 1;
    int b;
    int c;
};
typedef struct x data;

int main()
{
    data v;
    printf("%d",v.a);
    return 0;
}
