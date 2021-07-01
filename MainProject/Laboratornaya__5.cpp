#include <iostream>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <vector>

using namespace std;



int Laboratornaya__5()
{
	ifstream fin("D:\\textin.txt", ios::in);
	if (!fin)
	{
		cout << "Can'n open file" << endl;
		return 1;
	}



	fin.seekg(0, ios::end);
	int len = fin.tellg();
	char* buf = new char[len + 1];
	char* buffer = new char[len + 1];


	// неформатированное чтение текстового файла

	fin.seekg(0, ios::beg); //указатель в начало файла
	fin.read(buf, len); //скопировать len символов из fin в буфер
	buf[len] = '\0'; //поместить в буфер нуль-литеру



	int n = 0;
	int i = 0;
	int j = 0;
	int m = 0;
	int cnt = 0;


	int k = 0;

	vector <char> vector_first;
	vector <char> vector_second;
	vector <char> vector_third;

	int x;
	int y;
	int z;

	while (buf[i])
	{
		if (buf[i] == '?' || (buf[i]) == '!' || (buf[i]) == '.')
		{
			for (j = n, m = 0;j <= i;j++)//Перенёс счетчик m++ в 64 строку
			{
				if (buf[j] != '\n')   //   Добавил условие 
				{


					buffer[m] = buf[j];
					m++;
				}


			}
			buffer[m] = '\0';

			if (k == 0)
			{

				vector_first.assign(buffer, buffer + m);

				x = m;
			}
			else if (k == 1)
			{

				vector_second.assign(buffer, buffer + m);
				y = m;
			}
			else
			{

				vector_third.assign(buffer, buffer + m);;
				z = m;
			}
			k = k + 1;
			n = i + 1;

		}
		i++;
	}
	for (int l = 0; l < z; l++)
	{

		cout << vector_third[l];

	}
	for (int l = 0; l < y; l++)
	{

		cout << vector_second[l];

	}
	for (int l = 0; l < x; l++)
	{

		cout << vector_first[l];

	}
	return 5;
}
