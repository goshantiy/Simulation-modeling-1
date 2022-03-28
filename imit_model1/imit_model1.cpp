#include <iostream>
#include <random>
#include <math.h>


int main()
{
	//Критерий согласия хи-квадрат
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> rg(0.00001, 1.0);//равномерное распределение на интервале [0.00001, 1.0)
	double N = 30;
	double* X = new double[N];
	int k = 1 + 3.3 * log10(double(N));//число интервалов
	int* ni = new int[k];//массив хранящий число попаданий в отрезки
	for (int i = 0; i < k; ni[i] = 0, i++);	
	for (int i = 0; i < N; X[i] = rg(rd), i++);	//генерируем выборку
	std::sort(X, X + (int)N);//сортировка для удобства
	double step = (double)1 / k;
	double buf = 0;
	for (int i = 0, ix=0; i < k; i++)//подсчитываем "попадания" чисел в интервалы
	{
		while (X[ix] > buf && X[ix] < (buf + step))
		{
			ni[i]++;
			ix++;
		}
		buf += step;
	}
	std::cout << "Count intervals = ";
	for (int i=0;i<k;i++)
		std::cout << ni[i]<<" ";//вывод "попаданий" в интервалы на экран
	std::cout << std::endl;
	double xi_2=0;
	double Nk = N / k;
	for (int i = 0; i < k; i++)//подсчёт значения критерия
		xi_2 += pow(ni[i]-Nk,2)/Nk;
	std::cout <<"Xi_2_emperical = "<< xi_2;
	double xi_2_critical = 7.77944;
	std::cout << "\nXi_2_critical = " << xi_2_critical;
	if (xi_2 < xi_2_critical)
		std::cout << "\nXi_2_emperical < Xi_2_critical. Accepted";
	else std::cout << "\nXi_2_emperical>Xi_2_critical. Not accepted";
}
