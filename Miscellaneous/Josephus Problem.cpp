/// Josephus problem, n people numbered from 1 to n stand in a circle.
/// Counting starts from 1 and every k'th people dies
/// Returns the position of the m'th killed people
/// For example if n = 10 and k = 3, then the people killed are 3, 6, 9, 2, 7, 1, 8, 5, 10, 4 respectively

/// O(n)
int josephus(int n, int k, int m){
    int i;
    for (m = n - m, i = m + 1; i <= n; i++){
        m += k;
        if (m >= i) m %= i;
    }
    return m + 1;
}

/// O(k log(n))
long long josephus2(long long n, long long k, long long m){ /// hash = 583016
    m = n - m;
    if (k <= 1) return n - m;

    long long i = m;
    while (i < n){
        long long r = (i - m + k - 2) / (k - 1);
        if ((i + r) > n) r = n - i;
        else if (!r) r = 1;
        i += r;
        m = (m + (r * k)) % i;
    }
    return m + 1;
}

int main(){
    int n, k, m;
    printf("%d\n", josephus(10, 1, 2));
    printf("%d\n", josephus(10, 1, 10));
}
