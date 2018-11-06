#define LEN 78777
#define MAX 1000010
#define chkbit(ar, i) (((ar[(i) >> 6]) & (1 << (((i) >> 1) & 31))))
#define setbit(ar, i) (((ar[(i) >> 6]) |= (1 << (((i) >> 1) & 31))))
#define isprime(x) (( (x) && ((x)&1) && (!chkbit(ar, (x)))) || ((x) == 2))

int p, prime[LEN];
unsigned int ar[(MAX >> 6) + 5] = {0};

void Sieve(){
    int i, j, k;
    setbit(ar, 0), setbit(ar, 1);

    for (i = 3; (i * i) < MAX; i++, i++){
        if (!chkbit(ar, i)){
            k = i << 1;
            for (j = (i * i); j < MAX; j += k) setbit(ar, j);
        }
    }

    p = 0;
    prime[p++] = 2;
    for (i = 3; i < MAX; i++, i++){
        if (isprime(i)) prime[p++] = i;
    }
}

int main(){
    Sieve();
    printf("%d\n", p);
    int i;
    for (i = 0; i < 60; i++){
        if (isprime(i)) printf("%d\n", i);
    }
}
