#include <bits/stdtr1c++.h>
using namespace std;
/*** Manacher's algorithm to generate longest palindromic substrings for all centers ***/
/// When i is even, pal[i] = largest palindromic substring centered from str[i / 2]
/// When i is odd, pal[i] = largest palindromic substring centered between str[i / 2] and str[i / 2] + 1

vector <int> manacher(char *str){ /// hash = 784265
    int i, j, k, l = strlen(str), n = l << 1;
    vector <int> pal(n);

    for (i = 0, j = 0, k = 0; i < n; j = max(0, j - k), i += k){
        while (j <= i && (i + j + 1) < n && str[(i - j) >> 1] == str[(i + j + 1) >> 1]) j++;
        for (k = 1, pal[i] = j; k <= i && k <= pal[i] && (pal[i] - k) != pal[i - k]; k++){
            pal[i + k] = min(pal[i - k], pal[i] - k);
        }
    }

    pal.pop_back();
    return pal;
}

int main(){
    char str[100];
    while (scanf("%s", str)){
        auto v = manacher(str);
        for (auto it: v) printf("%d ", it);
        puts("");
    }
    return 0;
}
