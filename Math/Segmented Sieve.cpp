#define MAX 1000010

#define BASE_SQR 216
#define BASE_LEN 10010
#define BASE_MAX 46656
#define chkbit(ar, i) (((ar[(i) >> 6]) & (1 << (((i) >> 1) & 31))))
#define setbit(ar, i) (((ar[(i) >> 6]) |= (1 << (((i) >> 1) & 31))))

int p, primes[BASE_LEN];
unsigned int base[(BASE_MAX >> 6) + 5], isprime[(MAX >> 6) + 5];

void Sieve(){
    clr(base);
    int i, j, k;

    for (i = 3; i < BASE_SQR; i++, i++){
        if (!chkbit(base, i)){
            k = i << 1;
            for (j = (i * i); j < BASE_MAX; j += k){
                setbit(base, j);
            }
        }
    }

    p = 0;
    for (i = 3; i < BASE_MAX; i++, i++){
        if (!chkbit(base, i)){
            primes[p++] = i;
        }
    }
}

int SegmentedSieve(long long a, long long b){
    long long j, k, x;
    int i, d, counter = 0;

    if (a <= 2 && 2 <= b) counter = 1; /// 2 is counted separately if in range
    if (!(a & 1)) a++;
    if (!(b & 1)) b--;
    if (a > b) return counter;

    clr(isprime);
    for (i = 0; i < p; i++){
        x = primes[i];
        if ((x * x) > b) break;

        k = x << 1;
        j = x * ((a + x - 1) / x);
        if (!(j & 1)) j += x;
        else if (j == x) j += k;

        while (j <= b){
            setbit(isprime, j - a);
            j += k;
        }
    }

    /// Other primes in the range except 2 are added here
    d = (b - a + 1);
    for (i = 0; i < d; i++, i++){
        if (!chkbit(isprime, i) && (a + i) != 1) counter++;
    }

    return counter;
}

int main(){
    Sieve();
    int T = 0, t, i, j, a, b;

    scanf("%d", &t);
    while (t--){
        scanf("%d %d", &a, &b);
        printf("Case %d: %d\n", ++T, SegmentedSieve(a, b));
    }
    return 0;
}
