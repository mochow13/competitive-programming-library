int extended_euclid(int a, int b, int &x, int &y) {
    int xx = y = 0;
    int yy = x = 1;
    while (b) {
        int q = a / b;
        int t = b; b = a%b; a = t;
        t = xx; xx = x - q*xx; x = t;
        t = yy; yy = y - q*yy; y = t;
    }
    return a;
}
// Linear Diophantine Equation Solution: Given, a*x+b*y=c. Find valid x and y if possible.
bool linear_diophantine (int a, int b, int c, int & x0, int & y0, int & g) {
    g = extended_euclid (abs(a), abs(b), x0, y0);
    if (c % g != 0)
        return false;
    x0 *= c / g;
    y0 *= c / g;
    if (a < 0)   x0 *= -1;
    if (b < 0)   y0 *= -1;
    return true;
}
// for each integer k,
// x1 = x + k * b/g
// y1 = y - k * a/g
// is a solution to the equation where g = gcd(a,b).
void shift_solution (int & x, int & y, int a, int b, int cnt) {
    x += cnt * b;
    y -= cnt * a;
}
// Now How many solution where x in range[x1,x2] and y in range[y1,y2] ?
int find_all_solutions(int a,int b,int c,int &minx,int &maxx,int &miny,int &maxy)
{
    int x,y,g;
    if(linear_diophantine(a,b,c,x,y,g) == 0) return 0;
    a/=g, b/=g;
    int sign_a = a>0 ? +1 : -1;
    int sign_b = b>0 ? +1 : -1;
 
    shift_solution (x, y, a, b, (minx - x) / b);
    if (x < minx)
        shift_solution (x, y, a, b, sign_b);
    if (x > maxx)
        return 0;
    int lx1 = x;
  
    shift_solution (x, y, a, b, (maxx - x) / b);
    if (x > maxx)
        shift_solution (x, y, a, b, -sign_b);
    int rx1 = x;
  
    shift_solution (x, y, a, b, - (miny - y) / a);
    if (y < miny)
        shift_solution (x, y, a, b, -sign_a);
    if (y > maxy)
        return 0;
    int lx2 = x;
  
    shift_solution (x, y, a, b, - (maxy - y) / a);
    if (y > maxy)
        shift_solution (x, y, a, b, sign_a);
    int rx2 = x;
  
    if (lx2 > rx2)
        swap (lx2, rx2);
    int lx = max (lx1, lx2);
    int rx = min (rx1, rx2);
  
    return (rx - lx) / abs(b) + 1;
}