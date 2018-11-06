#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 100010
#define min(a,b) ((a)<(b) ? (a):(b))
#define max(a,b) ((a)>(b) ? (a):(b))
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

char str[MAX];
int n, Z[MAX];

void ZFunction(){ /// Z[i] = lcp of the suffix starting from i with str
    int i, j, k, l, r, p;
    Z[0] = n, l = 0, r = 0;
    for (i = 1; i < n; i++){
        if (i > r){
            k = 0;
            while ((i + k) < n && str[i + k] == str[k]) k++;
            Z[i] = k;
            if (Z[i]) l = i, r = i + Z[i] - 1;
        }
        else{
            p = i - l;
            if (Z[p] < (r - i + 1)) Z[i] = Z[p];
            else{
                k = r + 1;
                while (k < n && str[k - i] == str[k]) k++;
                l = i, r = k - 1;
                Z[i] = (r - l + 1);
            }
        }
    }
}

/// Z[i] = lcp of the suffix starting from i with str
void ZFunction(char* str){ /// hash = 998923
    int i, l, r, x;

    l = 0, r = 0;
    for (i = 1; str[i]; i++){
        Z[i] = max(0, min(Z[i - l], r - i));
        while (str[i + Z[i]] && str[Z[i]] == str[i + Z[i]]) Z[i]++;
        if ((i + Z[i]) > r) l = i, r = i + Z[i];
    }
    Z[0] = i;
}

int main(){
    scanf("%s", str);
    n = strlen(str);
    ZFunction();
    return 0;
}
