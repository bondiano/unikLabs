#include <cmath>;
#include <iostream>

/*16
cos(x)-cos(2x)/2+cos(3x)/3+…+(-1)n+1cos(nx)/n
ln(2cos(x/2))*/
double sum(double x, double eps, int &n)
{
	double sum = 0;
	double sumN = 0;
	n = 2;
	for (sumN = cos(x); fabs(sumN) > eps; ++n)
	{
		sum += sumN;
		sumN = sumN * -((n-1)*cos(n*x)*(1/cos((n-1)*x))) /n; //выведенная рекурентная формула
	}
	return sum;
}
int main()
{
	int n = 0;
	setlocale(LC_ALL, "rus");
	double eps = 0;
	double x = 0.1;
	std::cout << "Введите епсилон:" << std::endl;
	std::cin >> eps; //меньше эпсилона последнее слогаемое
	for (;x<0.9;x+=0.1)
	{

		std::cout << "x: " << x << " n: " << n << " f(x): " << log(2 * cos(x / 2)) << " sum: " <<  sum(x, eps,n) << ' ' << std::endl;
	}
	system("pause");
	return 0;
}