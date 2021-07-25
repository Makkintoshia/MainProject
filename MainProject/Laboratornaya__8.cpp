#include <iostream> // Cout Cin
#include <Windows.h> // Для использования русского языка
#include <fstream>
#include <iomanip>

using namespace std;


const int sname = 50;

struct STUDENT // Описание (данные) о студенте
{
    // Структура OCENKI
    struct OCENKI
    {
        int M, I, F; // Математика История Физика
    };
    // Структура STUDENTS
    char fio[sname]; // ФИО студента
    OCENKI ocenki; // Оценки 
};

struct STUDENTNODE // Экземплер узла дерева
{
    STUDENT data; // Данные о студенте
    STUDENTNODE* left; // Указатель на левый элемент
    STUDENTNODE* right; // Указатель на правый элемент
};

const int size_struct = sizeof(STUDENT); // Размер структуры


STUDENT WriteStruct()
{
    // Объявление и Инициализация
    STUDENT student;

    cin.get(); // Читаем невидимый \n из потока, который оставил после себя предыдущий cin.get

    cout << "[SYSTEM]: Добавление новой записи\n[SYSTEM]: Введите ФИО студента: ";

    cin.get(student.fio, sname);

    cout << "[SYSTEM]: Введите оценки от '2' до '5':\n|Математика: "; cin >> student.ocenki.M;

    cout << "|История: "; cin >> student.ocenki.I;

    cout << "|Физика: "; cin >> student.ocenki.F;

    return student;
}


STUDENTNODE* WriteTreeData(STUDENTNODE* top, const STUDENT student) // Добавление узла в дерево
{
    if (!top) //если находимся на уровне листа,
    {
        top = new STUDENTNODE; //то выделить память под узел
        if (!top) {
            cout << "Не хватает памяти" << endl;
            return NULL; //выход если память не выделена
        }
        top->data = student; //запись данных в узел
        top->left = NULL; //обнуление указателей
        top->right = NULL;
    }
    else //иначе
        if (strcmp(top->data.fio, student.fio) > 0) //сравниваем значение в узле с добавляемым и
            top->left = WriteTreeData(top->left, student); //добавляем в левое
            //поддерево
        else
            top->right = WriteTreeData(top->right, student);//или правое поддерево
    return top; //возвращаем указатель на корень дерева
}


void ViewTree(STUDENTNODE* top, int inc) //просмотр сверху вниз
{
    if (top)
    {
        if (inc == 1) cout << "[SYSTEM]: Просмотр дерева сверху вниз\n";
        cout << "[" << inc << "] " << top->data.fio << setw(10) << "\t|\tФ: " << top->data.ocenki.F << "\t И: " << top->data.ocenki.I << "\t М: " << top->data.ocenki.M << endl;

        inc++;

        ViewTree(top->left, inc); //обход левого поддерева

        ViewTree(top->right, inc); //обход правого поддерева
    }
}


void DisplayTree(STUDENTNODE* top, int otstup, const bool search_mode, int count_start, string search_name)
{

    if (top)
    {
        otstup += 5; //отступ от края экрана

        //  Если режим поиска был включен
        if (search_mode && (top->data.fio) == search_name) { cout << "[SYSTEM]: " << search_name << " находится на уровне [" << count_start << "]\n"; return; }
        count_start++;

        DisplayTree(top->right, otstup, search_mode, count_start, search_name); //обход правого поддерева

        if (search_mode == false) cout << setw(otstup) << top->data.fio << endl;

        DisplayTree(top->left, otstup, search_mode, count_start, search_name); //обход левого поддерева
    }
}


void SearchElementTree(STUDENTNODE* top)
{
    char name[sname]; // ФИО студента (буффер)

    cin.get(); // Читаем невидимый \n из потока, который оставил после себя предыдущий cin.get

    cout << "[SYSTEM]: Введите ФИО студента которого нужно найти: "; cin.get(name, sname);

    DisplayTree(top, 10, true, 1, name);
}


void FileWriter(STUDENTNODE* top, const char* fname, FILE* fwriter) // Запись данных в файл
{
    if (top) //cout << "[SYSTEM ERROR]: Очередь пустая. Нечего сохранять!\n";
    {
        fwrite(&top->data, size_struct, 1, fwriter); // Запись данных в файл

        cout << setw(20) << top->data.fio << "\t| М: " << top->data.ocenki.M << "\t| Ф: " << top->data.ocenki.F << "\t| И: " << top->data.ocenki.I << "\t[сохранен]\n";

        FileWriter(top->left, fname, fwriter);
        FileWriter(top->right, fname, fwriter);
    }
}


void FileReader(STUDENTNODE*& top, const char* fname)
{
    FILE* freader = fopen(fname, "rb"); // Открытие бинарного файла для чтения (файл должен существовать)

    int n = 0; // Если n < 1 - то конец файла

    STUDENT student;

    if (!freader) cout << "[SYSTEM]: Нет данных для восстановления\n";
    else // Если файл существует
    {
        cout << "[SYSTEM DATA RECOVERY]:\n\n";
        while (!feof(freader))
        {
            n = fread(&student, size_struct, 1, freader); // Буффер | Размер буффера | Количество читаемых данных | Поток

            if (n < 1) break; // Если n < 1 - то конец файла

            cout << setw(20) << student.fio << "\t| М: " << student.ocenki.M << "\t| Ф: " << student.ocenki.F << "\t| И: " << student.ocenki.I << "\t[восстановлен]\t[добавлен в дерево]\n";

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
    // Параметры русского языка
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    const char* fname = "main.dat"; // Имя файла (передается в функции)

    int count = 0; // Количество записей в списке

    int mode = 0; // Режим работы программы (меню)

    STUDENT student;
    STUDENTNODE* top = 0;

    FILE* fwriter;// Инициализируем файл для записи

    FileReader(top, fname);

    cout << "[1] - Добавить новый элемент в дерево\n[2] - Показать структуру дерева\n[3] - Очистить экран\n[4] - Определить уровень, на котором находится элемент в дереве\n";
    cout << "[5] - Показать структуру в виде дерева\n[6] - Сохранить данные в файл\n[666] - Выход\n";

    while (true)
    {
        cout << "[SYSTEM MODE]: "; cin >> mode;

        switch (mode)
        {
        case 1: student = WriteStruct(); top = WriteTreeData(top, student); break; // Добавить новый элемент в дерево
        case 2:  ViewTree(top, 1);break; // Показать структуру дерева в столбик
        case 3:  // Очистить экран
            system("cls");
            cout << "[1] - Добавить новый элемент в дерево\n[2] - Показать структуру дерева\n[3] - Очистить экран\n[4] - Определить уровень, на котором находится элемент в дереве\n";
            cout << "[5] - Показать структуру в виде дерева\n[6] - Сохранить данные в файл\n[666] - Выход\n";
            break;
        case 4: SearchElementTree(top);break; // Найти элемент E в дереве 
        case 5: DisplayTree(top, 10, false, 1, ""); break; // Показать структуру в виде дерева
        case 6: // Сохранить данные в файл
            fwriter = fopen(fname, "wb");
            FileWriter(top, fname, fwriter);
            fclose(fwriter);
            break;
        case 666:
            if (top)
            {
                cout << "[SYSTEM]: В очереди есть заполненные данные, Вы желаете их сохранить в файл?";
                cout << " [ПРЕДУПРЕЖДЕНИЕ!] - если файл уже существует, он будет перезаписан. Продолжить? [1] - ДА [AnyKey] - НЕТ\n[SAVE?]: ";
                cin >> mode;
                if (mode == 1)
                {
                    fwriter = fopen(fname, "wb");
                    FileWriter(top, fname, fwriter); // Сохранить данные в файл
                    fclose(fwriter);
                }
            }
            return 0;
            break;
        }
    }
    return 8;
}