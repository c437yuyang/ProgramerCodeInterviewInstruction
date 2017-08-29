#include <iostream>
using namespace std;

#pragma region 我自己的版本，把上一道题的遍历矩阵的方法利用起来，只是空间复杂度略高
//按照左右上下右左下上的顺序外围一圈matrix，把遍历到的数放进tmp
void TraverseEdge(int mat[], int m, int n, int lt_x, int lt_y, int rb_x, int rb_y, int *tmp)
{
	//左程云的版本是单独处理了只有一行和只有一列的情况，其实不用处理
	int idx = 0;
	int x, y;
	x = lt_x;
	while (x < rb_x)//先从左到右
	{
		//cout << mat[lt_y*n + x] << " ";
		tmp[idx++] = mat[lt_y*n + x];
		x++;
	}

	y = lt_y;
	while (y < rb_y)//从上到下
	{
		//cout << mat[y*n + rb_x] << " ";
		tmp[idx++] = mat[y*n + rb_x];
		y++;
	}

	//从右到左
	x = rb_x;
	while (x > lt_x)
	{
		//cout << mat[rb_y*n + x] << " ";
		tmp[idx++] = mat[rb_y*n + x];
		--x;
	}

	//从下到上
	y = rb_y;
	while (y > lt_y)
	{
		tmp[idx++] = mat[y*n + lt_x];
		//cout << mat[y*n + lt_x] << " ";
		--y;
	}
}

//旋转90度之后的遍历，变成了从上到下开始,把tmp里的数放回matrix
void TraverseEdge1(int mat[], int m, int n, int lt_x, int lt_y, int rb_x, int rb_y, int *tmp)
{
	//左程云的版本是单独处理了只有一行和只有一列的情况，其实不用处理

	int idx = 0;
	int x, y;
	x = lt_x;

	y = lt_y;
	while (y < rb_y)//从上到下
	{
		//cout << mat[y*n + rb_x] << " ";
		mat[y*n + rb_x] = tmp[idx++];
		y++;
	}

	//从右到左
	x = rb_x;
	while (x > lt_x)
	{
		//cout << mat[rb_y*n + x] << " ";
		mat[rb_y*n + x] = tmp[idx++];
		--x;
	}

	//从下到上
	y = rb_y;
	while (y > lt_y)
	{
		mat[y*n + lt_x] = tmp[idx++];
		//cout << mat[y*n + lt_x] << " ";
		--y;
	}

	while (x < rb_x)//先从左到右
	{
		mat[lt_y*n + x] = tmp[idx++];
		//cout << mat[lt_y*n + x] << " ";
		x++;
	}
}

void RotateMatrix(int mat[], int m, int n)
{
	int lt_x = 0, lt_y = 0; //左上角坐标
	int rb_x = n - 1, rb_y = m - 1; //右下角坐标

	while (lt_y <= rb_y && lt_x <= rb_y)
	{
		int *tmp = new int[(rb_y - lt_y + 1) *(rb_x - lt_x + 1)]();
		TraverseEdge(mat, m, n, lt_x, lt_y, rb_x, rb_y, tmp);
		TraverseEdge1(mat, m, n, lt_x++, lt_y++, rb_x--, rb_y--, tmp);
		delete[] tmp;
	}
}
#pragma endregion

#pragma region 左程云的版本是把每一个外圈矩阵分为几组来调整，感觉理解上还会麻烦一些，用一维数组写出来也比较丑，就没写了，直接看java版本把

#pragma endregion


void printMatrix(int *p, int m, int n) 
{
	for (int i=0;i!=m;++i)
	{
		for (int j=0;j!=n;++j)
		{
			cout << p[i*n + j] << " ";
		}
		cout << endl;
	}
}

int main()
{
	//方阵的旋转，不是方阵会麻烦一些
	int matrix[] = { 1, 2, 3, 4 ,
						5, 6, 7, 8 ,
						9, 10, 11, 12 ,
						13, 14, 15, 16 };

	
	printMatrix(matrix, 4, 4);
	RotateMatrix(matrix, 4, 4);
	printMatrix(matrix, 4, 4);


	system("pause");
	return 0;
}

