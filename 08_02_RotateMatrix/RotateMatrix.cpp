#include <iostream>
using namespace std;

#pragma region ���Լ��İ汾������һ����ı�������ķ�������������ֻ�ǿռ临�Ӷ��Ը�
//�������������������ϵ�˳����ΧһȦmatrix���ѱ����������Ž�tmp
void TraverseEdge(int mat[], int m, int n, int lt_x, int lt_y, int rb_x, int rb_y, int *tmp)
{
	//����Ƶİ汾�ǵ���������ֻ��һ�к�ֻ��һ�е��������ʵ���ô���
	int idx = 0;
	int x, y;
	x = lt_x;
	while (x < rb_x)//�ȴ�����
	{
		//cout << mat[lt_y*n + x] << " ";
		tmp[idx++] = mat[lt_y*n + x];
		x++;
	}

	y = lt_y;
	while (y < rb_y)//���ϵ���
	{
		//cout << mat[y*n + rb_x] << " ";
		tmp[idx++] = mat[y*n + rb_x];
		y++;
	}

	//���ҵ���
	x = rb_x;
	while (x > lt_x)
	{
		//cout << mat[rb_y*n + x] << " ";
		tmp[idx++] = mat[rb_y*n + x];
		--x;
	}

	//���µ���
	y = rb_y;
	while (y > lt_y)
	{
		tmp[idx++] = mat[y*n + lt_x];
		//cout << mat[y*n + lt_x] << " ";
		--y;
	}
}

//��ת90��֮��ı���������˴��ϵ��¿�ʼ,��tmp������Ż�matrix
void TraverseEdge1(int mat[], int m, int n, int lt_x, int lt_y, int rb_x, int rb_y, int *tmp)
{
	//����Ƶİ汾�ǵ���������ֻ��һ�к�ֻ��һ�е��������ʵ���ô���

	int idx = 0;
	int x, y;
	x = lt_x;

	y = lt_y;
	while (y < rb_y)//���ϵ���
	{
		//cout << mat[y*n + rb_x] << " ";
		mat[y*n + rb_x] = tmp[idx++];
		y++;
	}

	//���ҵ���
	x = rb_x;
	while (x > lt_x)
	{
		//cout << mat[rb_y*n + x] << " ";
		mat[rb_y*n + x] = tmp[idx++];
		--x;
	}

	//���µ���
	y = rb_y;
	while (y > lt_y)
	{
		mat[y*n + lt_x] = tmp[idx++];
		//cout << mat[y*n + lt_x] << " ";
		--y;
	}

	while (x < rb_x)//�ȴ�����
	{
		mat[lt_y*n + x] = tmp[idx++];
		//cout << mat[lt_y*n + x] << " ";
		x++;
	}
}

void RotateMatrix(int mat[], int m, int n)
{
	int lt_x = 0, lt_y = 0; //���Ͻ�����
	int rb_x = n - 1, rb_y = m - 1; //���½�����

	while (lt_y <= rb_y && lt_x <= rb_y)
	{
		int *tmp = new int[(rb_y - lt_y + 1) *(rb_x - lt_x + 1)]();
		TraverseEdge(mat, m, n, lt_x, lt_y, rb_x, rb_y, tmp);
		TraverseEdge1(mat, m, n, lt_x++, lt_y++, rb_x--, rb_y--, tmp);
		delete[] tmp;
	}
}
#pragma endregion

#pragma region ����Ƶİ汾�ǰ�ÿһ����Ȧ�����Ϊ�������������о�����ϻ����鷳һЩ����һά����д����Ҳ�Ƚϳ󣬾�ûд�ˣ�ֱ�ӿ�java�汾��

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
	//�������ת�����Ƿ�����鷳һЩ
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

