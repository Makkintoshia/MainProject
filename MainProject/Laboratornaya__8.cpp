#include <iostream> // Cout Cin
#include <Windows.h> // ��� ������������� �������� �����
#include <fstream>
#include <iomanip>

using namespace std;


const int sname = 50;

struct STUDENT // �������� (������) � ��������
{
    // ��������� OCENKI
    struct OCENKI
    {
        int M, I, F; // ���������� ������� ������
    };
    // ��������� STUDENTS
    char fio[sname]; // ��� ��������
    OCENKI ocenki; // ������ 
};

struct STUDENTNODE // ��������� ���� ������
{
    STUDENT data; // ������ � ��������
    STUDENTNODE* left; // ��������� �� ����� �������
    STUDENTNODE* right; // ��������� �� ������ �������
};

const int size_struct = sizeof(STUDENT); // ������ ���������


STUDENT WriteStruct()
{
    // ���������� � �������������
    STUDENT student;

    cin.get(); // ������ ��������� \n �� ������, ������� ������� ����� ���� ���������� cin.get

    cout << "[SYSTEM]: ���������� ����� ������\n[SYSTEM]: ������� ��� ��������: ";

    cin.get(student.fio, sname);

    cout << "[SYSTEM]: ������� ������ �� '2' �� '5':\n|����������: "; cin >> student.ocenki.M;

    cout << "|�������: "; cin >> student.ocenki.I;

    cout << "|������: "; cin >> student.ocenki.F;

    return student;
}


STUDENTNODE* WriteTreeData(STUDENTNODE* top, const STUDENT student) // ���������� ���� � ������
{
    if (!top) //���� ��������� �� ������ �����,
    {
        top = new STUDENTNODE; //�� �������� ������ ��� ����
        if (!top) {
            cout << "�� ������� ������" << endl;
            return NULL; //����� ���� ������ �� ��������
        }
        top->data = student; //������ ������ � ����
        top->left = NULL; //��������� ����������
        top->right = NULL;
    }
    else //�����
        if (strcmp(top->data.fio, student.fio) > 0) //���������� �������� � ���� � ����������� �
            top->left = WriteTreeData(top->left, student); //��������� � �����
            //���������
        else
            top->right = WriteTreeData(top->right, student);//��� ������ ���������
    return top; //���������� ��������� �� ������ ������
}


void ViewTree(STUDENTNODE* top, int inc) //�������� ������ ����
{
    if (top)
    {
        if (inc == 1) cout << "[SYSTEM]: �������� ������ ������ ����\n";
        cout << "[" << inc << "] " << top->data.fio << setw(10) << "\t|\t�: " << top->data.ocenki.F << "\t �: " << top->data.ocenki.I << "\t �: " << top->data.ocenki.M << endl;

        inc++;

        ViewTree(top->left, inc); //����� ������ ���������

        ViewTree(top->right, inc); //����� ������� ���������
    }
}


void DisplayTree(STUDENTNODE* top, int otstup, const bool search_mode, int count_start, string search_name)
{

    if (top)
    {
        otstup += 5; //������ �� ���� ������

        //  ���� ����� ������ ��� �������
        if (search_mode && (top->data.fio) == search_name) { cout << "[SYSTEM]: " << search_name << " ��������� �� ������ [" << count_start << "]\n"; return; }
        count_start++;

        DisplayTree(top->right, otstup, search_mode, count_start, search_name); //����� ������� ���������

        if (search_mode == false) cout << setw(otstup) << top->data.fio << endl;

        DisplayTree(top->left, otstup, search_mode, count_start, search_name); //����� ������ ���������
    }
}


void SearchElementTree(STUDENTNODE* top)
{
    char name[sname]; // ��� �������� (������)

    cin.get(); // ������ ��������� \n �� ������, ������� ������� ����� ���� ���������� cin.get

    cout << "[SYSTEM]: ������� ��� �������� �������� ����� �����: "; cin.get(name, sname);

    DisplayTree(top, 10, true, 1, name);
}


void FileWriter(STUDENTNODE* top, const char* fname, FILE* fwriter) // ������ ������ � ����
{
    if (top) //cout << "[SYSTEM ERROR]: ������� ������. ������ ���������!\n";
    {
        fwrite(&top->data, size_struct, 1, fwriter); // ������ ������ � ����

        cout << setw(20) << top->data.fio << "\t| �: " << top->data.ocenki.M << "\t| �: " << top->data.ocenki.F << "\t| �: " << top->data.ocenki.I << "\t[��������]\n";

        FileWriter(top->left, fname, fwriter);
        FileWriter(top->right, fname, fwriter);
    }
}


void FileReader(STUDENTNODE*& top, const char* fname)
{
    FILE* freader = fopen(fname, "rb"); // �������� ��������� ����� ��� ������ (���� ������ ������������)

    int n = 0; // ���� n < 1 - �� ����� �����

    STUDENT student;

    if (!freader) cout << "[SYSTEM]: ��� ������ ��� ��������������\n";
    else // ���� ���� ����������
    {
        cout << "[SYSTEM DATA RECOVERY]:\n\n";
        while (!feof(freader))
        {
            n = fread(&student, size_struct, 1, freader); // ������ | ������ ������� | ���������� �������� ������ | �����

            if (n < 1) break; // ���� n < 1 - �� ����� �����

            cout << setw(20) << student.fio << "\t| �: " << student.ocenki.M << "\t| �: " << student.ocenki.F << "\t| �: " << student.ocenki.I << "\t[������������]\t[�������� � ������]\n";

            top = WriteTreeData(top, student);

        }
        fclose(freader);
    }

    cout << endl;

    system("pause");

    system("cls");
}


int Laboratornaya__8()
{
    // ��������� �������� �����
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    const char* fname = "main.dat"; // ��� ����� (���������� � �������)

    int count = 0; // ���������� ������� � ������

    int mode = 0; // ����� ������ ��������� (����)

    STUDENT student;
    STUDENTNODE* top = 0;

    FILE* fwriter;// �������������� ���� ��� ������

    FileReader(top, fname);

    cout << "[1] - �������� ����� ������� � ������\n[2] - �������� ��������� ������\n[3] - �������� �����\n[4] - ���������� �������, �� ������� ��������� ������� � ������\n";
    cout << "[5] - �������� ��������� � ���� ������\n[6] - ��������� ������ � ����\n[666] - �����\n";

    while (true)
    {
        cout << "[SYSTEM MODE]: "; cin >> mode;

        switch (mode)
        {
        case 1: student = WriteStruct(); top = WriteTreeData(top, student); break; // �������� ����� ������� � ������
        case 2:  ViewTree(top, 1);break; // �������� ��������� ������ � �������
        case 3:  // �������� �����
            system("cls");
            cout << "[1] - �������� ����� ������� � ������\n[2] - �������� ��������� ������\n[3] - �������� �����\n[4] - ���������� �������, �� ������� ��������� ������� � ������\n";
            cout << "[5] - �������� ��������� � ���� ������\n[6] - ��������� ������ � ����\n[666] - �����\n";
            break;
        case 4: SearchElementTree(top);break; // ����� ������� E � ������ 
        case 5: DisplayTree(top, 10, false, 1, ""); break; // �������� ��������� � ���� ������
        case 6: // ��������� ������ � ����
            fwriter = fopen(fname, "wb");
            FileWriter(top, fname, fwriter);
            fclose(fwriter);
            break;
        case 666:
            if (top)
            {
                cout << "[SYSTEM]: � ������� ���� ����������� ������, �� ������� �� ��������� � ����?";
                cout << " [��������������!] - ���� ���� ��� ����������, �� ����� �����������. ����������? [1] - �� [AnyKey] - ���\n[SAVE?]: ";
                cin >> mode;
                if (mode == 1)
                {
                    fwriter = fopen(fname, "wb");
                    FileWriter(top, fname, fwriter); // ��������� ������ � ����
                    fclose(fwriter);
                }
            }
            return 0;
            break;
        }
    }
    return 8;
}