/// Only for non-negative integers
/// Returns the immediate next number with same count of one bits, -1 on failure
long long hakmemItem175(long long n){
    if (n == 0) return -1;
    long long x = (n & -n);
    long long left = (x + n);
    long long right = ((n ^ left) / x) >> 2;
    long long res = (left | right);
    return res;
}

/// Returns the immediate previous number with same count of one bits, -1 on failure
long long lol(long long n){
    if (n == 0 || n == 1) return -1;
    long long res = ~hakmemItem175(~n);
    return (res == 0) ? -1 : res;
}
