#include <iostream>
using namespace std;

int writesizemassiv(int);
int writemassiv(int*, int);
int chetniyelmentsmassiv(int*, int&, int);
int minchetelmentmassiv(int*, int, int&);
int Laboratornaya__3()
{
	int* massiv;
	int n = 0;

	int size = writesizemassiv(n);

	massiv = new int[size];
	int count = 0;
	writemassiv(massiv, size);
	chetniyelmentsmassiv(massiv, count, size);

	cout << "\nNumber of chetniy elments massiv :" << count << endl;
	int minchet = 0;

	minchetelmentmassiv(massiv, size, minchet);
	cout << "Minimal chentiy element massiv :" << minchet;
	return 3;
}




//Размер массива

int writesizemassiv(int n)
{

	cout << "Write size of massiv ";
	cin >> n;

	return n;
}

// Написание массива
int writemassiv(int* massiv, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << "Write  " << i + 1 << "  element   ";
		cin >> massiv[i];
	}
	cout << "Original massiv : ";
	for (int i = 0;i < size;i++) cout << "massiv[" << i + 1 << "]=" << massiv[i] << " ";
	return *massiv;
}

//Чётные элементы массива

int chetniyelmentsmassiv(int* massiv, int& count, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (massiv[i] % 2 == 0)
		{
			count++;
		}
	}
	return count;
}

int minchetelmentmassiv(int* massiv, int size, int& minchet)
{
	bool e = false;
	for (int i = 0; i < size; i++)
	{

		if (massiv[i] % 2 == 0)
		{

			if (e == false)
			{
				minchet = massiv[i];
			}

			if (massiv[i] < minchet)
			{
				minchet = massiv[i];
			}
			e = true;
		}
	}
	return minchet;
}