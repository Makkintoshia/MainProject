#include <iostream>
using namespace std;
 int Laboratornaya__2  ()
{
	//ќбъ€вление переменных

	float a;
	float x;
	float xn;
	float xk;
	float dx;
	float z;

	//¬вод a,xn,xk,dx

	cout << "Write a ";
	cin >> a;
	cout << "Write xn ";
	cin >> xn;
	cout << "Write xk ";
	cin >> xk;
	cout << "Write dx ";
	cin >> dx;


	// вывод заголовка и шапки таблицы

	cout << "      TABLE OF VALUES Fnction z=f(x)" << endl;
	cout << "     |-----------------|-----------------|" << endl;
	cout << "     |        x        |     z=f(x)      |" << endl;
	cout << "     |_________________|_________________||" << endl;

	for (x = xn;x <= xk;x += dx)
	{
		cout << "     |__________" << "      " << x << '|';

		if (x < 0)
		{
			z = a * a;
		}
		else if (x >= 0 && x < 10)
		{
			z = a * x;
		}

		else if (x >= 10)
		{
			z = 5 * a;
		};
		cout << "                   ";
		if (a > 10)
		{
			cout << (int)z;
		}
		else
		{
			cout << z;
		}
		cout << '|' << endl;
	}
	cout << "     |_________________|_________________||" << endl;


	return 2;

}
