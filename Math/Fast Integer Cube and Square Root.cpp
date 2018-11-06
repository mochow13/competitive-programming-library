unsigned int fast_sqrt(unsigned int n){
    unsigned int c, g;

    c = g = 0x8000;
    for (; ;){
        if ((g * g) > n) g ^= c;
        c >>= 1;
        if (!c) return g;
        g |= c;
    }
}

int fast_cbrt(int n){
    int x, r = 30, res = 0;

    for (; r >= 0; r -= 3){
        res <<= 1;
        x = (3 * res * (res + 1)) + 1;
        if ((n >> r) >= x){
            res++;
            n -= (x << r);
        }
    }

    return res;
}

unsigned long long fast_sqrt(unsigned long long n){
    unsigned long long c, g;

    c = g = 0x80000000;
    for (; ;){
        if ((g * g) > n) g ^= c;
        c >>= 1;
        if (!c) return g;
        g |= c;
    }
}

unsigned long long fast_cbrt(unsigned long long n){
    int r = 63;
    unsigned long long x, res = 0;

    for (; r >= 0; r -= 3){
        res <<= 1;
        x = (res * (res + 1) * 3) + 1;
        if ((n >> r) >= x){
            res++;
            n -= (x << r);
        }
    }

    return res;
}

int main(){

}
