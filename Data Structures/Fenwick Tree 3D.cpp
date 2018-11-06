#define MAX 205
/// 3D Fenwick tree, Range updates and point queries
struct Fenwick3D{
    int n, m, r, tree[MAX][MAX][MAX];

    Fenwick3D(){
    }

    Fenwick3D(int a, int b, int c){
        clr(tree);
        n = a, m = b, r = c;
    }

    /// Add v to the cube from lower-right [i,j,k] to upper-left [1,1,1]
    void update(int i, int j, int k, int v){
        if ((i < 0) || (j < 0) || (i > n) || (j > m) || (k < 0) || (k > r)) return;

        while (i){
            int x = j;
            while (x){
                int y = k;
                while (y){
                    tree[i][x][y] += v;
                    y ^= (y & (-y));
                }
                x ^= (x & (-x));
            }
            i ^= (i & (-i));
        }
    }

    /// Add v to the cube from upper-left [x1,y1,z1] to lower-right [x2,y2,z2]
    void update(int x1, int y1, int z1, int x2, int y2, int z2){
        update(x2, y2, z2, 1), update(x1 - 1, y1 - 1, z2, 1);
        update(x1 - 1, y2, z1 - 1, 1), update(x2, y1 - 1, z1 - 1, 1);
        update(x1 - 1, y2, z2, -1), update(x2, y1 - 1, z2, -1);
        update(x2, y2, z1 - 1, -1), update(x1 - 1, y1 - 1, z1 - 1, -1);
    }

    /// Query for the value at index [i][j][k]
    int query(int i, int j, int k){
        int res = 0;
        while (i <= n){
            int x = j;
            while (x <= m){
                int y = k;
                while (y <= r){
                    res += tree[i][x][y];
                    y += (y & (-y));
                }
                x += (x & (-x));
            }
            i += (i & (-i));
        }
        return res;
    }
};