#include <iostream>
#include <math.h>
using namespace std;

const double pi = 3.14159265;
const double e = 2.71828;
int Laboratornaya__1()
{
	double a;
	double b;
	double x;
	double z;


	//Ввод переменных с консоли

	cout << "Write a";
	cin >> a;
	cout << "Write b";
	cin >> b;
	cout << "Write x";
	cin >> x;

	//Вычесление z

	if (x <= a)
	{
		z = (1 + x * x) / (2 - 11 * sin(x)) + pow(e, sinh(x));
	}

	else if (x > a && x < b)
	{
		z = sqrt(1.57 - pow(x, 3) * pow(sin(x), 2)) + 4.1 * pow(e, (2 * x));
	}

	else if (x >= b)
	{
		z = pow((asin(x) + acos(x) + log(x)), tan(x));
	}

	cout << "z = " << z;
	return 1;
}
