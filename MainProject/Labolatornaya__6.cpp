#include <iostream> // Cout Cin
#include <Windows.h> // ��� ������������� �������� �����
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <iomanip> // setw � �.�.



//������ //�������� ��������_�������//�������� ������������//������������/����������� �������������//;_CRT_SECURE_NO_WARNINGS




using namespace std;

struct TIME { int ch, min; };

struct STUDENT
{
    char name[50]; // ��� ��������
    int number; // ����� ������
    int srednee;
    int type[5] = { 0,0,0,0,0 }; // ������������ 

};

const int size_aro = sizeof(STUDENT); // ������ ���������

void FileWriter(const char* fname)
{
    FILE* fwriter = fopen(fname, "ab+"); // �������� ��������� ����� ��� ������ � �����

    STUDENT aro;

    while (fwriter) // ���� ������ ��� ������ ���� ������������ �� ������� �����. ������� ���� ��� ������ � ������ � ������ ���������� 
    {
        cout << "[SYSTEM]: ��������������! ��� ������ ������� '*'.\n[SYSTEM]: ������� ��� ��������: ";
        cin >> aro.name;
        if (aro.name[0] == '*') break;

        cout << "[SYSTEM]: ������� ����� ������: ";
        cin >> aro.number;
        for (int l = 0;l < 5;l++)
        {
            cout << "[SYSTEM]: ������� ������: ";
            cin >> aro.type[l];
        }
        aro.srednee = (aro.type[0] + aro.type[1] + aro.type[2] + aro.type[3] + aro.type[4]) / 5;
        cout << "[SYSTEM]:������� ������" << aro.srednee;
        fwrite(&aro, size_aro, 1, fwriter); // ������ ������ � ����

        cout << "\n----------������ ������� ���������----------\n";

        cout << setw(14) << "| ���: " << setw(27) << aro.name << setw(14) << "\n| ����� ������: " << setw(26) << aro.number << setw(14) << "\n| ������: " << aro.type[0] << aro.type[1] << aro.type[2] << aro.type[3] << aro.type[4]
            << "\n|������� ������: " << aro.srednee;

        cout << "\n--------------------------------------------\n";
    }
    fclose(fwriter);
}


void FileReader(const char* fname)
{
    FILE* freader = fopen(fname, "rb"); // �������� ��������� ����� ��� ������ (���� ������ ������������)

    STUDENT aro;

    int n = 0; // ���� n < 1 - �� ����� �����

    int count = 0; // ���������� ������� � �����

    if (!freader) cout << "[SYSTEM]: ��� ������ ��� ������!\n";
    else // ���� ���� ����������
    {
        while (!feof(freader))
        {
            n = fread(&aro, size_aro, 1, freader); // ������ | ������ ������� | ���������� �������� ������ | �����

            if (n < 1) break; // ���� n < 1 - �� ����� �����

            count++;

            cout << "\n---------------������ �" << count << "-----------------\n";

            cout << setw(14) << "| ���: " << setw(27) << aro.name << setw(14) << "\n| ����� ������: " << setw(26) << aro.number << setw(14) << "\n| ������: " << aro.type[0] << aro.type[1] << aro.type[2] << aro.type[3] << aro.type[4]
                << "\n|������� ������: " << aro.srednee;

            cout << "\n-----------------------------------------\n";
        }
        fclose(freader);
    }
}


void Sort(const char* fname) // ���������� ������ �� ������ ������� (���������)
{
    FILE* freader = fopen(fname, "rb+"); // �������� ��������� ����� ��� ������ � ������

    STUDENT aro1, aro2;

    // ����� ����� (���������� �������)
    fseek(freader, 0, SEEK_END); // ������� � �����

    int fsize = ftell(freader) / size_aro; // �������� ���������� ������� |

    rewind(freader); // ������� � ������
    // ����� �������� �����

    if (!freader || fsize == 0) cout << "[SYSTEM]: ��� ������ ��� ������!\n";
    else
    {
        cout << "[SYSTEM]: ������ ���������� ������ �� ������� ������\n";
        for (int i = fsize - 1; i >= 1; i--)
        {
            for (int j = 0; j <= i - 1; j++)
            {
                fseek(freader, j * size_aro, SEEK_SET); //��������� �� j-�� ������

                fread(&aro1, size_aro, 1, freader); //������ ������ j � aro1

                fread(&aro2, size_aro, 1, freader); //������ ����. ������ � aro2

                if (aro1.number > aro2.number)  //���������� ������ �����
                {
                    fseek(freader, (-2) * size_aro, SEEK_CUR); //��������� �� 2 ������� �����

                    //�������� ��������
                    fwrite(&aro2, size_aro, 1, freader); //������� ���������� aro2

                    fwrite(&aro1, size_aro, 1, freader); // ����� ���������� aro1
                }
            }
        }
        cout << "[SYSTEM]: ���������� ������� ���������\n";
    }
    fclose(freader);
}


void Search(const char* fname) // ������� �� ������� ������ 4
{
    FILE* freader = fopen(fname, "rb"); // �������� ��������� ����� ��� ������ (���� ������ ������������)

    STUDENT aro;

    int n = 0; // ���� n < 1 - �� ����� �����

    int count = 0; // ���������� ������� � �����



    if (!freader) cout << "[SYSTEM]: ��� ������ ��� ������!\n";
    else // ���� ���� ����������
    {


        while (!feof(freader))
        {
            n = fread(&aro, size_aro, 1, freader); // ������ | ������ ������� | ���������� �������� ������ | �����

            if (n < 1) break; // ���� n < 1 - �� ����� �����

            if (aro.srednee >= 4)
            {
                if (count == 0)

                    count++;

                cout << "\n---------------������ �" << count << "-------------------\n";

                cout << setw(14) << "| ����� ������: " << setw(26) << aro.number << setw(14) << "\n| ������: " << setw(25) << aro.type[0] << aro.type[1] << aro.type[2] << aro.type[3] << aro.type[4]
                    << "\n|������� ������: " << aro.srednee;;

                cout << "\n-----------------------------------------\n";
            }
        }
        if (count == 0) cout << "[SYSTEM]: � ���������, �� �� ������ ����� �� ������ ����� �� ������ ������� :(\n";

        fclose(freader);
    }
}







int Laboratornaya__6()
{
    int mode = 0; // ����� ������ ��������� (����)

    const char* fname = "main.dat"; // ��� ����� (���������� � �������)

    // ��������� �������� �����
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "[1] - ��������� �������� ����\n[2] - �������� ������ � ����\n[3] - �������� �����\n[4] - ���������� ������ �� ������ ������ (���������)\n[5] - ������� �� ������� ������ ������ 4\n[666] - �����\n";
    while (true)
    {
        cout << "[SYSTEM MODE]: "; cin >> mode;

        switch (mode)
        {
        case 1: FileReader(fname); break; // ��������� ���� ���� ��
        case 2: FileWriter(fname); break; // ������� � ����
        case 3: system("cls"); cout << "[1] - ��������� �������� ����\n[2] - �������� ������ � ����\n[3] - �������� �����\n[4] - ���������� ������ �� ������ ������ (���������)\n[5] -������� �� ������� ������ ������ 4\n[666] - �����\n"; break; // �������� �������
        case 4: Sort(fname); break; // ���������� ������ �� ������ ������ (���������)
        case 5: Search(fname); break; // �������� ��������� ������ ������ 4
        case 666: return 0; break;
        }
    }
    return 6;
}