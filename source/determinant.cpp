typedef long double Num;

Num determinant(vector< vector<Num> > A) {
	int n = A.size();
	Num det = 1;
	for(int i = 0; i < n; i ++) {
		int pivot = i;
		for(int j = i+1; j < n; j ++)
			if(abs(A[pivot][i]) < abs(A[j][i])) pivot = j;
		swap(A[i], A[pivot]);
		det *= A[i][i];
		if(i != pivot) det = -det;
		if(det == 0) break;
		Num r = Num(1) / A[i][i];
		for(int j = i+1; j < n; j ++) {
			Num u = A[j][i] * r;
			for(int k = n-1; k >= i; k --)
				A[j][k] -= u * A[i][k];
		}
	}
	return det;
}
