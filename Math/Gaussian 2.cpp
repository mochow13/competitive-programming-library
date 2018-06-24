const double eps = 1e-9;

// *****may return empty vector

vector<double> gauss(vector<vector<double>> &a)
{
	int n = a.size(), m = a[0].size() - 1;

	vector<int> where(m, -1);
	for(int col = 0, row = 0; col < m && row < n; col++)
    {
    	int sel = row;
        for(int i = row; i < n; i++)
        	if(abs(a[i][col]) > abs(a[sel][col]))
        		sel = i;

		if(abs(a[sel][col]) < eps) { where[col] = -1; continue; }

        for(int i = col; i <= m; i++)
			swap(a[sel][i], a[row][i]);
		where[col] = row;

		for(int i = 0; i < n; i++)
			if(i != row)
			{
				if(abs(a[i][col]) < eps) continue;
            	double c = a[i][col] / a[row][col];
            	for(int j = 0; j <= m; j++)
                    a[i][j] -= c * a[row][j];
			}

		row++;
    }

    vector<double> ans(m, 0);
    for(int i = 0; i < m; i++)
        if(where[i] != -1)
			ans[i] = a[where[i]][m] / a[where[i]][i];

	// Validity check?
	// May need to remove the following code

    for(int i = 0; i < n; i++)
	{
		double sum = a[i][m];
		for(int j = 0; j < m; j++)
			sum -= ans[j] * a[i][j];

		if(abs(sum) > eps) return vector<double>();
	}

	return ans;
}