#include <iostream>
#include <vector>
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


//两个点组成对角线，一个是往右走，一个往下走，右到了边界往下，下到了边界往右

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
		if (p1_x < n - 1) { ++p1_x; } //到达了最右边，向下走
		else { p1_y++; }
		if (p2_y < m - 1) { ++p2_y; } //到达了最下面，向右走
		else { p2_x++; }
	}

	cout << endl;
}


//打印矩阵上三角(方阵)
void UpTrianglePrintMatrix(int *mat, int n)
{
	//每条对角线
	for (int i = 0; i != n; ++i)
	{
		int start_x = 0 + i; //选定起始坐标和停止坐标
		int start_y = 0;

		int end_x = n - 1;
		int end_y = n - 1 - i;

		while (start_x <= end_x && start_y <= end_y)
		{
			cout << mat[start_y++*n + start_x++] << " ";
		}
	}

}

//程序员面试宝典上面的，生成一个zigzag矩阵
std::vector<std::vector<int>> genZigZagArray(int n)
{
	std::vector<std::vector<int>> ret_arr(n, std::vector<int>(n));

	int s = 0;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			s = i + j;
			if (s < n)
				ret_arr[i][j] = s*(s + 1) / 2 + ((i + j) % 2 == 0 ? i : j);
			else
			{
				s = (n - 1 - i) + (n - 1 - j);
				ret_arr[i][j] = n*n - s*(s + 1) / 2 - (n - (i + j) % 2 == 0 ? i : j);
			}
		}
	}

	return ret_arr;
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


	int matrix1[] = { 1, 2, 3, 4 ,
						5, 6, 7, 8 ,
						9, 10, 11, 12 ,
						13, 14, 15, 16 };
	UpTrianglePrintMatrix(matrix1, 4);


	std::cout << std::endl;
	std::cout << std::endl;
	auto ret_zigzag_arr = genZigZagArray(8);

	for (int i = 0; i < ret_zigzag_arr.size(); ++i)
	{
		for (int j = 0; j < ret_zigzag_arr[i].size(); ++j)
		{
			std::cout << ret_zigzag_arr[i][j] << " ";
		}
		std::cout << std::endl;
	}


	system("pause");
	return 0;
}

