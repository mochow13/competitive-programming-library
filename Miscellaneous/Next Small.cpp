#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 250010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

int ar[MAX], L[MAX], R[MAX], stack[MAX], time[MAX];

void next_small(int n, int* ar, int* L){
    int i, j, k, l, x, top = 0;

    for (i = 0; i < n; i++){
        x = ar[i];
        if (top && stack[top] >= x){
            while (top && stack[top] >= x) k = time[top--];
            L[i] = (i - k + 2);
            stack[++top] = x;
            time[top] = k;
        }
        else{
            L[i] = 1;
            stack[++top] = x;
            time[top] = i + 1;
        }
    }
}
/*** L[i] contains maximum length of the range from i to the left such that the minimum of this range
     is not less than ar[i].
     Similarly, R[i] contains maximum length of the range from i to the right such that the minimum
     of this range is not less than ar[i]

     For example, ar[] = 5 3 4 3 1 2 6
                  L[]  = 1 2 1 4 5 1 1
                  R[]  = 1 3 1 1 3 2 1
***/

void fill(int n, int* ar, int* L, int* R){
    int i, j, k;
    for (i = 0; i < n; i++) L[i] = ar[n - i - 1];

    next_small(n, L, R);
    next_small(n, ar, L);

    i = 0, j = n - 1;
    while (i < j){
        k = R[i], R[i] = R[j], R[j] = k;
        i++, j--;
    }
}

int main(){
    int n, i, j, k;

    scanf("%d", &n);
    for (i = 0; i < n; i++) scanf("%d", &ar[i]);

    fill(n, ar, L, R);
    for (i = 0; i < n; i++) printf("%d ", ar[i]);
    puts("");
    for (i = 0; i < n; i++) printf("%d ", R[i]);
    puts("");
    for (i = 0; i < n; i++) printf("%d ", L[i]);
    puts("");
    return 0;
}
