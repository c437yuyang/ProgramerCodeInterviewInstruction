#include <iostream>
using namespace std;


void printMatrix(int *p, int m, int n)
{
	for (int i = 0; i != m; ++i)
	{
		for (int j = 0; j != n; ++j)
		{
			cout << p[i*n + j] << " ";
		}
		cout << endl;
	}
}

void ZigZagPrintMatrix(int *mat, int m, int n)
{
	int p1_x = 0, p1_y = 0, p2_x = 0, p2_y = 0; //p1右上的点,p2左下的点
	bool tr2lb = false; //从右上角往左下角打印
	while (!(p1_x > n - 1 || p1_y > m - 1 || p2_x > n - 1 || p2_y > m - 1))
	{
		int x = 0, y = 0;
		if (tr2lb)
		{
			x = p1_x, y = p1_y;
			while (x > -1 && y < m)
			{
				cout << mat[y*n + x] << " ";
				--x; ++y;
			}
		}
		else
		{
			x = p2_x, y = p2_y;
			while (x < n && y>-1)
			{
				cout << mat[y*n + x] << " ";
				++x; --y;
			}
		}
		tr2lb = !tr2lb;
		if (p1_x < n-1) { ++p1_x; } //到达了最右边，向下走
		else { p1_y++; }
		if (p2_y < m-1) { ++p2_y; } //到达了最下面，向右走
		else { p2_x++; }
	}


}


int main()
{

	//int matrix[] = { 1, 2, 3, 4 ,
	//					5, 6, 7, 8 ,
	//					9, 10, 11, 12 ,
	//					13, 14, 15, 16 };

	//int matrix[] = { 1, 2, 3, 4 ,
	//				5, 6, 7, 8 ,
	//				9, 10, 11, 12 };

	int matrix[] = { 1, 2, 3 ,
		5, 6, 7 ,
		9, 10, 11 ,
		13, 14, 15 };

	//ZigZagPrintMatrix(matrix, 4, 4);
	//ZigZagPrintMatrix(matrix, 3, 4);
	ZigZagPrintMatrix(matrix, 4, 3);

	system("pause");
	return 0;
}

