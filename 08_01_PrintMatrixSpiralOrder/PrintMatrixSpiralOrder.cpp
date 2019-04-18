#include <iostream>
using namespace std;

//����ָ��˳����ΧһȦmatrix
void printEdge(int mat[], int m, int n, int lt_x, int lt_y, int rb_x, int rb_y)
{
	int x, y;
	x = lt_x;
	//����Ƶİ汾�ǵ���������ֻ��һ�к�ֻ��һ�е��������ʵ���ô���
	while (x < rb_x)//�ȴ�����
	{
		cout << mat[lt_y*n + x] << " ";
		++x;
	}

	y = lt_y;
	while (y < rb_y)//���ϵ���
	{
		cout << mat[y*n + rb_x] << " ";
		++y;
	}

	//���ҵ���
	x = rb_x;
	while (x > lt_x)
	{
		cout << mat[rb_y*n + x] << " ";
		--x;
	}

	//���µ���
	y = rb_y;
	while (y > lt_y)
	{
		cout << mat[y*n + lt_x] << " ";
		--y;
	}
}

void spiralOrderPrint(int mat[], int m, int n)
{
	int lt_x = 0, lt_y = 0; //���Ͻ�����
	int rb_x = n - 1, rb_y = m - 1; //���½�����

	while (lt_y <= rb_y && lt_x <= rb_y)
	{
		printEdge(mat, m, n, lt_x++, lt_y++, rb_x--, rb_y--);
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
						13, 14, 15};

	//spiralOrderPrint(matrix, 4, 4);
	//spiralOrderPrint(matrix, 3, 4);
	spiralOrderPrint(matrix, 4, 3);

	system("pause");
	return 0;
}

