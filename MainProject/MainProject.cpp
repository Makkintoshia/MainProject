
#include <iostream>
using namespace std;
int Laboratornaya__1();
int Laboratornaya__2();
int Laboratornaya__3();
int Laboratornaya__4();
int Laboratornaya__5();




int main()
{
	setlocale(LC_ALL, "Russian");
	int n;
	cout << "Введите номер лабораторной"<<endl;
	cout << "\n";
	cout << "ЛАБОРАТОРНАЯ РАБОТА №1 “Программирование линейных и разветвляющихся алгоритмов" << endl;
	cout << "\n";
	cout << "ЛАБОРАТОРНАЯ РАБОТА №2 Программирование алгоритмов циклической структуры" << endl;
	cout << "\n";
	cout << "ЛАБОРАТОРНАЯ РАБОТА №3  Программирование алгоритмов обработки одномерных массивов" << endl;
	cout << "\n";
	cout << "ЛАБОРАТОРНАЯ РАБОТА №4 Обработка двумерных массивов с помощью функций" << endl;
	cout << "\n";
	cout << "ЛАБОРАТОРНАЯ РАБОТА №5 Программирование операций над строками и файлами" << endl;
	cout << "\n";
	cin >> n;
	switch (n)
	{
	case 1:
		Laboratornaya__1();
		break;

	case 2:

		Laboratornaya__2();
		break;
	case 3:

		Laboratornaya__3();
		break;

	case 4:

		Laboratornaya__4();
		break;
	case 5:

		Laboratornaya__5();
		break;
	}


}

