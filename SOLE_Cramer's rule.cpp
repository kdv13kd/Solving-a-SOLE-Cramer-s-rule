#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <math.h>
using namespace std;

float deter(float** M, int n) {			// рекурсивная функция для вычисления определителя любого порядка
	if (n == 1)		return M[0][0];				//если размерность матрицы = 1, то есть матрица=число, возврат число
	else if (n == 2)	return M[0][0] * M[1][1] - M[0][1] * M[1][0];	//если размерность 2, то возврат опред-ля по формуле нахождения определителя матрицы 2 порядка
	else                        //если больше 2 размерность, то определитель считается по общей формуле разложения по строке
	{
		float** minor = new float* [n];
		for (int i = 0; i < n; i++)
			minor[i] = new float[n];
		float detA = 0;
		for (int k = 0; k < n; k++)
		{
			int ii = 0, jj = 0;
			for (int i = 0; i < n; i++)
				if (i != 0) {
					jj = 0;
					for (int j = 0; j < n; j++)
						if (j != k) {
							minor[ii][jj] = M[i][j];	//находим миноры
							jj++;
						}
					ii++;
				}
			float numb;
			if (((k + 1) % 2) == 0)	numb = -M[0][k];
			else   numb = M[0][k];
			detA = detA + numb * deter(minor, n - 1);		//рекурсия
		}
		for (int i = 0; i < n; i++)
			delete[] minor[i];
		return detA;		//возврат определителя
	}
}

void printSystem(float** m, float* v, int n)	//вывод системы
{
	cout << "Ax = b" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout.width(10);		cout << m[i][j];
		}
		cout.width(15);		cout << "x" << i + 1;
		if (i == (n / 2))
		{
			cout.width(5);		cout << "=";
		}
		else
		{
			cout.width(5);		cout << " ";
		}
		cout.width(10);		cout << v[i] << endl;
	}
}

void main()
{
	ifstream fin;
	ofstream fout;
	const double eps = 1E-10;
	setlocale(LC_ALL, "Rus");
	fin.open("input.txt");
	if (!fin.is_open())
		cout << "Ошибка открытия файла" << endl;
	else
	{
		int N;
		fin >> N;

		float** a = new float* [N];
		float** m = new float* [N];
		for (int i = 0; i < N; i++)
		{
			a[i] = new float[N];	//матрица А
			m[i] = new float[N];	//дополнительная матрица А с заменяемыми 
		}								//столбцами матрицы вектором В по методу Крамера
		float* b = new float[N];		//векто В
		float* delta = new float[N];	//массив вычисляемых определителей
		float* x = new float[N];
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
				fin >> a[i][j];
			fin >> b[i];
		}

		fin.close();

		cout << "Система в матричной форме" << endl;
		printSystem(a, b, N);
		cout << endl << endl << "Определители" << endl;


		float main_det = deter(a, N);		//вычисляем оперделитель матрицы А
		main_det = (int)main_det;
		if (main_det != 0)
		{
			cout << endl << "detA= " <<  main_det << endl;
			for (int k = 0; k < N; k++)
			{
				for (int i = 0; i < N; i++)
					for (int j = 0; j < N; j++)
						if (j == k)							//формируем доп матрицу заменяя
							m[i][j] = b[i];			//в цикле постепенно столбцы на вектор В
						else
							m[i][j] = a[i][j];

				delta[k] = deter(m, N);			//высчитываем определители дельта
				x[k] = delta[k] / main_det;			//находим решения системы
				cout << "delta" << k + 1 << "= " << delta[k] << endl;
			}

			cout << endl << endl << "Решение системы" << endl  << endl;
			for (int i = 0; i < N; i++)
				cout << "x" << i + 1 << "= " << x[i] << endl;
		}
		else
			cout << "Определитель системы должен быть отличен от 0" << endl;
	}
	system("pause");
}
