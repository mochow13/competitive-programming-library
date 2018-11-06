#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

/// Lexicographically Minimum String Rotation
int minlex(char* str){ /// Returns the 0-based index
    int i, j, k, n, len, x, y;
    len = n = strlen(str), n <<= 1, i = 0, j = 1, k = 0;

    while((i + k) < n && (j + k) < n) {
        x = i + k >= len ? str[i + k - len] : str[i + k];
        y = j + k >= len ? str[j + k - len] : str[j + k];
        if(x == y) k++;
        else if (x < y){
            j += ++k, k = 0;
            if (i >= j) j = i + 1;
        }
        else{
            i += ++k, k = 0;
            if (j >= i) i = j + 1;
        }
    }

    return (i < j) ? i : j;
}

int t;
char str[50010];

int main(){
    gets(str);
    while (gets(str)){
        printf("%d\n", minlex(str));
    }
    return 0;
}
