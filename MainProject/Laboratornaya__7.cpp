#include <iostream> // Cout Cin
#include <Windows.h> // ��� ������������� �������� �����
#include <fstream>

//������ //�������� ��������_�������//�������� ������������//������������/����������� �������������//;_CRT_SECURE_NO_WARNINGS
using namespace std;


const int sname = 50;

struct STUDENT
{
    // ��������� OCENKI
    struct OCENKI
    {
        int M, I, F; // ���������� ������� ������
    };
    // ��������� STUDENTS
    char fio[sname]; // ��� ��������
    OCENKI ocenki; // ������ 
    STUDENT* next; // ��������� �� ��������� �������
};

const int size_struct = sizeof(STUDENT); // ������ ���������
// �������
// * �������� (���������)
// & ������ 


STUDENT WriteStruct(const int& count)
{
    // ���������� � �������������
    STUDENT student;

    //if(count !=0) 
    cin.get();

    cout << "[SYSTEM]: ���������� ����� ������\n[SYSTEM]: ������� ��� ��������: ";

    cin.get(student.fio, sname);

    cout << "[SYSTEM]: ������� ������ �� '2' �� '5':\n|����������: "; cin >> student.ocenki.M;

    cout << "|�������: "; cin >> student.ocenki.I;

    cout << "|������: "; cin >> student.ocenki.F;

    return student;
}


STUDENT* AddFirst(int& count, STUDENT student, int mode) // ���������� ������ ������. mode [0] - �� ������������ �������������� ������ �� ����� [1] - ������������ ��������������
{
    // ���������� � �������������
    STUDENT* begin = 0;

    if (mode == 0) student = WriteStruct(count); // ���������� ���������

    if (student.fio[0] != NULL && student.ocenki.F > 1 && student.ocenki.F <= 5 && student.ocenki.I > 1 && student.ocenki.I <= 5 && student.ocenki.M > 1 && student.ocenki.M <= 5)
    {
        begin = new STUDENT; // �������� ������ ��� ������� 

        *begin = student; // ���������� �������� �������� 

        begin->next = 0; // ��������� ������� ����� ������ 0 

        count++; // ��������� ���������� �������

        if (mode == 0) // ���� �������������� �� ����� �� ����������
            cout << "[SYSTEM]: ����� ������: " << student.fio << "\t| �: " << student.ocenki.M << "\t| �: " << student.ocenki.F << "\t| �: " << student.ocenki.I << "\t[�������]\n";
    }
    else cout << "[SYSTEM ERROR]: �� ����� ������������ ��������. ��������� ��������\n";

    return begin; // � �������� ���������� ���������� ������ �� ������ �������  
}

STUDENT* AddStructEnd(STUDENT* end, int& count, STUDENT student, int mode) // ���������� ������ � ����� mode [0] - �� ������������ �������������� ������ �� ����� [1] - ������������ ��������������
{
    // ���������� � �������������
    STUDENT* new_student = 0;

    char ch = '+';

    while (ch == '+')
    {
        if (mode == 0) student = WriteStruct(count); // ���������� ��������� (���� mode = 0, ����� �� ������������ �������������� ������ �� �����

        if (student.fio[0] != NULL && student.ocenki.F > 1 && student.ocenki.F <= 5 && student.ocenki.I > 1 && student.ocenki.I <= 5 && student.ocenki.M > 1 && student.ocenki.M <= 5)
        {
            new_student = new STUDENT;

            *new_student = student;

            new_student->next = 0;

            end->next = new_student;

            end = new_student;

            count++; // ��������� ���������� �������

            if (mode == 0) // ���� �������������� �� ����� �� ����������
            {
                cout << "[SYSTEM]: ����� ������: " << student.fio << "\t| �: " << student.ocenki.M << "\t| �: " << student.ocenki.F << "\t| �: " << student.ocenki.I << "\t[�������]\n";

                cout << "[SYSTEM]: ���������� ���������� ������ � ������� ������? [+] - �� [AnyKey] - ���\n[CONTINUE?]: "; cin >> ch;

                if (ch != '+') break;
            }
            else break; // ���� �������������� �� ����� ����������, �� ������ ���������� ������ � ����������� ���������� ������ � �������
        }
        else
        {
            cout << "[SYSTEM ERROR]: �� ����� ������������ ��������. ��������� ��������\n";

            break;
        }
    }

    return end; // ������� ���������� �������� ����� �������� �������
}


void PrintStruct(const STUDENT& student)
{
    cout << "| ���: " << student.fio << "\n| ����������: " << student.ocenki.M << "\n| �������: " << student.ocenki.I << "\n| ������: " << student.ocenki.F;
}

void ViewList(STUDENT* begin, const int& count)
{
    STUDENT* temp = begin;

    if (count == 0) cout << "[SYSTEM ERROR]: ������� ������. ������ ����������!\n";
    else
    {
        for (int i = 1; i <= count; i++)
        {
            cout << "---------------������ �" << i << "---------------\n";

            PrintStruct(*temp);

            cout << "\n---------------------------------------------------\n";

            temp = temp->next; // ���������� ��������� �� ��������� �������
        }
    }
}

STUDENT* DeleteLast(STUDENT* begin, STUDENT* end, int& count)
{
    STUDENT* temp; // ���������� ��� ���������� �������� (��, ��� ����� ��������)

    if (count == 0) cout << "[SYSTEM ERROR]: ������� ������. ������ �������!\n";
    else if (begin && begin->next != 0)
    {
        temp = begin;

        while (temp->next->next) temp = temp->next; // ���� ������������� ������� ������

        end = temp; // ������������� ������� �� ������ ����� ���������

        cout << "[SYSTEM]: ������: " << end->next->fio << "\t| �: " << end->next->ocenki.M << "\t| �: " << end->next->ocenki.F << "\t| �: " << end->next->ocenki.I << "\t[�������]\n";

        delete(end->next); // ������� ������� � �����

        count--; // ��������� ���������� �������

        end->next = 0; // ����� ���������� ������ ���
    }
    else // ���� � ������ ������ ���� ������
    {
        cout << "[SYSTEM]: ������: " << begin->fio << "\t| �: " << begin->ocenki.M << "\t| �: " << begin->ocenki.F << "\t| �: " << begin->ocenki.I << "\t[�������]\n";

        delete(begin); // ������� ���� ������������ �������

        count--; // ��������� ���������� �������
    }

    return end;
}


void FreeMemory(STUDENT* begin, int& count) // ������������ ������
{
    STUDENT* temp = begin;

    if (count == 0) cout << "[SYSTEM ERROR]: ������� ������. ������ �������!\n";
    else
    {
        cout << "[SYSTEM]: ��������� ������ ������� �� ������:\n\n";
        while (temp != 0)
        {
            STUDENT* next = temp->next;

            cout << temp->fio << "\t| �: " << temp->ocenki.M << "\t| �: " << temp->ocenki.F << "\t| �: " << temp->ocenki.I << "\t[������]\n";

            delete(temp);

            count--; // ��������� ���������� �������

            temp = next;
        }

        cout << "\n[SYSTEM]: ��� ������ ���� ��������� �������!\n";
    }
}


void FileWriter(STUDENT* begin, const char* fname, const int& count) // ������ ������ � ����
{
    FILE* fwriter = fopen(fname, "wb"); // �������� ��������� ����� ��� ������ (���������� ���������)

    STUDENT* temp = begin;

    int i = 0; // ������� ����������� �������

    if (count == 0) cout << "[SYSTEM ERROR]: ������� ������. ������ ���������!\n";
    else
    {
        cout << "[SYSTEM]: ��������� ������ ���� ��������� � �����:\n\n";
        for (i = 0; i < count; i++)
        {
            fwrite(temp, size_struct, 1, fwriter); // ������ ������ � ����

            //fwriter << &temp;

            cout << temp->fio << "\t| �: " << temp->ocenki.M << "\t| �: " << temp->ocenki.F << "\t| �: " << temp->ocenki.I << "\t[��������]\n";

            temp = temp->next; // ���������� ��������� �� ��������� �������
        }
        cout << endl;
    }
    fclose(fwriter);
}


void FileReader(STUDENT** begin, STUDENT** end, const char* fname, int& count) // �������������� ������ �� �����
{
    FILE* freader = fopen(fname, "rb"); // �������� ��������� ����� ��� ������ (���� ������ ������������)

    STUDENT student;

    int n = 0; // ���� n < 1 - �� ����� �����

    if (!freader) cout << "[SYSTEM]: ��� ������ ��� ��������������\n";
    else // ���� ���� ����������
    {
        cout << "[SYSTEM DATA RECOVERY]:\n\n";
        while (!feof(freader))
        {
            n = fread(&student, size_struct, 1, freader); // ������ | ������ ������� | ���������� �������� ������ | �����

            if (n < 1) break; // ���� n < 1 - �� ����� �����

            if (*begin) // ���� ������� �� ������
                *end = AddStructEnd(*end, count, student, 1); // �������� ����� �������� � ����� ������
            else // ���� ������� ������
            {
                *begin = AddFirst(count, student, 1); // ���������� ������� ��������

                *end = *begin;
            }

            cout << student.fio << "\t| �: " << student.ocenki.M << "\t| �: " << student.ocenki.F << "\t| �: " << student.ocenki.I << "\t[������������]\t[�������� � �������]\n";

            count + 1; // ���������� ������� + 1
        }
        fclose(freader);

        cout << endl;

        system("pause");

        system("cls");
    }
}


int Laboratornaya__7()
{
    // ��������� �������� �����
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // �������������
    STUDENT* begin = 0, // ��������� �� ������ �������
        * end = 0, // ��������� �� ����� �������
        student; // ���������� ��������� ��� �������� ������

    student.fio[1] = 'n'; student.next = 0; student.ocenki.F = 0; student.ocenki.I = 0; student.ocenki.M = 0; // �������������� ������������� ��������� (��� ���������� ��������)

    const char* fname = "main.dat"; // ��� ����� (���������� � �������)

    int count = 0; // ���������� ������� � ������

    int mode = 0; // �����  ����

    FileReader(&begin, &end, fname, count); // �������������� ������ (���� �������)


    cout << "[1] - ����������� ������ (���������� ������� ��������)\n[2] - �������� ����� �������� � ����� ������\n[3] - �������� �����\n[4] - �������� ������\n";
    cout << "[5] - ��������� ��������� ������� �� ������\n[6] - ������� ���� ������\n[7] - ��������� ������ � ����\n[666] - �����\n";

    while (true)
    {
        cout << "[SYSTEM MODE]: "; cin >> mode;

        switch (mode)
        {
        case 1:
            // ����������� ������
            if (count > 0) // ���� ������� �� ������
                cout << "[SYSTEM ERROR]: ����������� ������ ��� ���� ��������� �����! �� ������ �������� ����� �������� � ����� ������ [2]\n";
            else // ���� ������� ������
            {
                begin = AddFirst(count, student, 0); // ���������� ������� ��������

                end = begin;
            }
            break;
        case 2:
            if (count > 0) // ���� ������� �� ������
                end = AddStructEnd(end, count, student, 0); // �������� ����� �������� � ����� ������
            else // ������� ������
                cout << "[SYSTEM ERROR]: ����������� ������ ��� �� ���������! ����������, ��������� ����������� ������ [1]\n";
            break;
        case 3: // �������� �����
            system("cls");
            cout << "[1] - ����������� ������ (���������� ������� ��������)\n[2] - �������� ����� �������� � ����� ������\n[3] - �������� �����\n[4] - �������� ������\n";
            cout << "[5] - ��������� ��������� ������� �� ������\n[6] - ������� ���� ������\n[7] - ��������� ������ � ����\n[666] - �����\n";
            break;
        case 4: ViewList(begin, count); break; // �������� ������
        case 5: end = DeleteLast(begin, end, count); break; // ��������� ��������� ������� �� ������
        case 6: FreeMemory(begin, count); break; // ������� ���� ������
        case 7: FileWriter(begin, fname, count); break; // ��������� ������ � ����
        case 666:
            if (count > 0)
            {
                cout << "[SYSTEM]: � ������� ���� ����������� ������, �� ������� �� ��������� � ����?";
                cout << " [��������������!] - ���� ���� ��� ����������, �� ����� �����������. ����������? [1] - �� [AnyKey] - ���\n[SAVE?]: ";
                cin >> mode;

                if (mode == 1) FileWriter(begin, fname, count); // ��������� ������ � ����
            }

            FreeMemory(begin, count); // ���������� ������ ����� ������
            return 0;
            break;
        }
    }
    return 7;
}