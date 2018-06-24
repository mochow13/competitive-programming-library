void gauss(vector< vector<double> > &A) {
    
    int n = A.size();

	for(int i = 0; i < n; i++){
        int r = i;
        for(int j = i+1; j < n; j++)
            if(fabs(A[j][i]) > fabs(A[r][i]))
                r = j;
        if(fabs(A[r][i]) < EPS) continue;
        if(r != i)
            for(int j = 0; j <= n; j++)
                swap(A[r][j], A[i][j]);
        for(int k = 0; k < n; k++){
            if(k != i){
                for(int j = n; j >= i; j--)
                    A[k][j] -= A[k][i]/A[i][i]*A[i][j];
            }
        }
    }

    // solve: A[x][n]/A[x][x] for each x
}