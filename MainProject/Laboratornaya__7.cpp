#include <iostream> // Cout Cin
#include <Windows.h> // Для использования русского языка
#include <fstream>

//Проект //Свойства название_проекта//Свойства конфигурации//Препроцессор/Определения препроцессора//;_CRT_SECURE_NO_WARNINGS
using namespace std;


const int sname = 50;

struct STUDENT
{
    // Структура OCENKI
    struct OCENKI
    {
        int M, I, F; // Математика История Физика
    };
    // Структура STUDENTS
    char fio[sname]; // ФИО студента
    OCENKI ocenki; // Оценки 
    STUDENT* next; // Указатель на следующий элемент
};

const int size_struct = sizeof(STUDENT); // Размер структуры
// ПАМЯТКА
// * значение (указатель)
// & ссылка 


STUDENT WriteStruct(const int& count)
{
    // Объявление и Инициализация
    STUDENT student;

    //if(count !=0) 
    cin.get();

    cout << "[SYSTEM]: Добавление новой записи\n[SYSTEM]: Введите ФИО студента: ";

    cin.get(student.fio, sname);

    cout << "[SYSTEM]: Введите оценки от '2' до '5':\n|Математика: "; cin >> student.ocenki.M;

    cout << "|История: "; cin >> student.ocenki.I;

    cout << "|Физика: "; cin >> student.ocenki.F;

    return student;
}


STUDENT* AddFirst(int& count, STUDENT student, int mode) // Добавление первой записи. mode [0] - Не производится восстановление данных из файла [1] - Производится восстановление
{
    // Объявление и Инициализация
    STUDENT* begin = 0;

    if (mode == 0) student = WriteStruct(count); // Заполнение структуры

    if (student.fio[0] != NULL && student.ocenki.F > 1 && student.ocenki.F <= 5 && student.ocenki.I > 1 && student.ocenki.I <= 5 && student.ocenki.M > 1 && student.ocenki.M <= 5)
    {
        begin = new STUDENT; // Выделине памяти под элемент 

        *begin = student; // Присвоение значения элементу 

        begin->next = 0; // Следующий элемент после нашего 0 

        count++; // Инкремент количества записей

        if (mode == 0) // Если восстановления из файла не происходит
            cout << "[SYSTEM]: Новая запись: " << student.fio << "\t| М: " << student.ocenki.M << "\t| Ф: " << student.ocenki.F << "\t| И: " << student.ocenki.I << "\t[создана]\n";
    }
    else cout << "[SYSTEM ERROR]: Вы ввели некорректные значения. Процедура отменена\n";

    return begin; // В качестве результата возвращаем ссылку на первый элемент  
}

STUDENT* AddStructEnd(STUDENT* end, int& count, STUDENT student, int mode) // Добавление записи в конец mode [0] - Не производится восстановление данных из файла [1] - Производится восстановление
{
    // Объявление и Инициализация
    STUDENT* new_student = 0;

    char ch = '+';

    while (ch == '+')
    {
        if (mode == 0) student = WriteStruct(count); // Заполнение структуры (если mode = 0, тогда не производится восстановление данных из файла

        if (student.fio[0] != NULL && student.ocenki.F > 1 && student.ocenki.F <= 5 && student.ocenki.I > 1 && student.ocenki.I <= 5 && student.ocenki.M > 1 && student.ocenki.M <= 5)
        {
            new_student = new STUDENT;

            *new_student = student;

            new_student->next = 0;

            end->next = new_student;

            end = new_student;

            count++; // Инкремент количества записей

            if (mode == 0) // Если восстановления из файла не происходит
            {
                cout << "[SYSTEM]: Новая запись: " << student.fio << "\t| М: " << student.ocenki.M << "\t| Ф: " << student.ocenki.F << "\t| И: " << student.ocenki.I << "\t[создана]\n";

                cout << "[SYSTEM]: Продолжить заполнение данных в очередь списка? [+] - ДА [AnyKey] - НЕТ\n[CONTINUE?]: "; cin >> ch;

                if (ch != '+') break;
            }
            else break; // Если восстановление из файла происходит, то просто пропускаем диалог о продолжении заполнения данных в очередь
        }
        else
        {
            cout << "[SYSTEM ERROR]: Вы ввели некорректные значения. Процедура отменена\n";

            break;
        }
    }

    return end; // вернуть измененное значение нашей основной очереди
}


void PrintStruct(const STUDENT& student)
{
    cout << "| ФИО: " << student.fio << "\n| Математика: " << student.ocenki.M << "\n| История: " << student.ocenki.I << "\n| Физика: " << student.ocenki.F;
}

void ViewList(STUDENT* begin, const int& count)
{
    STUDENT* temp = begin;

    if (count == 0) cout << "[SYSTEM ERROR]: Очередь пустая. Нечего показывать!\n";
    else
    {
        for (int i = 1; i <= count; i++)
        {
            cout << "---------------Запись №" << i << "---------------\n";

            PrintStruct(*temp);

            cout << "\n---------------------------------------------------\n";

            temp = temp->next; // Перемещаем указатель на следующий элемент
        }
    }
}

STUDENT* DeleteLast(STUDENT* begin, STUDENT* end, int& count)
{
    STUDENT* temp; // Переменная для временного хранения (то, что будет удалятся)

    if (count == 0) cout << "[SYSTEM ERROR]: Очередь пустая. Нечего удалять!\n";
    else if (begin && begin->next != 0)
    {
        temp = begin;

        while (temp->next->next) temp = temp->next; // Ищем предпоследний элемент списка

        end = temp; // Предпоследний элемент из списка будет последним

        cout << "[SYSTEM]: Запись: " << end->next->fio << "\t| М: " << end->next->ocenki.M << "\t| Ф: " << end->next->ocenki.F << "\t| И: " << end->next->ocenki.I << "\t[удалена]\n";

        delete(end->next); // Удаляем элемент в конец

        count--; // Декремент количества записей

        end->next = 0; // После последнего никого нет
    }
    else // Если в списке только одна запись
    {
        cout << "[SYSTEM]: Запись: " << begin->fio << "\t| М: " << begin->ocenki.M << "\t| Ф: " << begin->ocenki.F << "\t| И: " << begin->ocenki.I << "\t[удалена]\n";

        delete(begin); // Удаляем один единственный элемент

        count--; // Декремент количества записей
    }

    return end;
}


void FreeMemory(STUDENT* begin, int& count) // Освобождение памяти
{
    STUDENT* temp = begin;

    if (count == 0) cout << "[SYSTEM ERROR]: Очередь пустая. Нечего удалять!\n";
    else
    {
        cout << "[SYSTEM]: Следующие записи удалены из списка:\n\n";
        while (temp != 0)
        {
            STUDENT* next = temp->next;

            cout << temp->fio << "\t| М: " << temp->ocenki.M << "\t| Ф: " << temp->ocenki.F << "\t| И: " << temp->ocenki.I << "\t[удален]\n";

            delete(temp);

            count--; // Декремент количества записей

            temp = next;
        }

        cout << "\n[SYSTEM]: Вся память была выгружена успешно!\n";
    }
}


void FileWriter(STUDENT* begin, const char* fname, const int& count) // Запись данных в файл
{
    FILE* fwriter = fopen(fname, "wb"); // Открытие бинарного файла для записи (содержимое очищается)

    STUDENT* temp = begin;

    int i = 0; // Подсчет добавленных записей

    if (count == 0) cout << "[SYSTEM ERROR]: Очередь пустая. Нечего сохранять!\n";
    else
    {
        cout << "[SYSTEM]: Следующие записи были сохранены в файле:\n\n";
        for (i = 0; i < count; i++)
        {
            fwrite(temp, size_struct, 1, fwriter); // Запись данных в файл

            //fwriter << &temp;

            cout << temp->fio << "\t| М: " << temp->ocenki.M << "\t| Ф: " << temp->ocenki.F << "\t| И: " << temp->ocenki.I << "\t[сохранен]\n";

            temp = temp->next; // Перемещаем указатель на следующий элемент
        }
        cout << endl;
    }
    fclose(fwriter);
}


void FileReader(STUDENT** begin, STUDENT** end, const char* fname, int& count) // Восстановление данных из файла
{
    FILE* freader = fopen(fname, "rb"); // Открытие бинарного файла для чтения (файл должен существовать)

    STUDENT student;

    int n = 0; // Если n < 1 - то конец файла

    if (!freader) cout << "[SYSTEM]: Нет данных для восстановления\n";
    else // Если файл существует
    {
        cout << "[SYSTEM DATA RECOVERY]:\n\n";
        while (!feof(freader))
        {
            n = fread(&student, size_struct, 1, freader); // Буффер | Размер буффера | Количество читаемых данных | Поток

            if (n < 1) break; // Если n < 1 - то конец файла

            if (*begin) // Если очередь не пустая
                *end = AddStructEnd(*end, count, student, 1); // Добавить новые элементы в конец списка
            else // Если очередь пустая
            {
                *begin = AddFirst(count, student, 1); // Добовление первого элемента

                *end = *begin;
            }

            cout << student.fio << "\t| М: " << student.ocenki.M << "\t| Ф: " << student.ocenki.F << "\t| И: " << student.ocenki.I << "\t[восстановлен]\t[добавлен в очередь]\n";

            count + 1; // Количество записей + 1
        }
        fclose(freader);

        cout << endl;

        system("pause");

        system("cls");
    }
}


int Laboratornaya__7()
{
    // Параметры русского языка
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Инициализация
    STUDENT* begin = 0, // Указатель на начало очереди
        * end = 0, // Указатель на конец очереди
        student; // Переменная структуры для передачи данных

    student.fio[1] = 'n'; student.next = 0; student.ocenki.F = 0; student.ocenki.I = 0; student.ocenki.M = 0; // Предвремеднная инициализация структуры (для корректной передачи)

    const char* fname = "main.dat"; // Имя файла (передается в функции)

    int count = 0; // Количество записей в списке

    int mode = 0; // Режим  меню

    FileReader(&begin, &end, fname, count); // Восстановление данных (если имеются)


    cout << "[1] - Организация списка (добавление первого элемента)\n[2] - Добавить новые элементы в конец списка\n[3] - Очистить экран\n[4] - Показать список\n";
    cout << "[5] - Исключить последний элемент из списка\n[6] - Удалить весь список\n[7] - Сохранить данные в файл\n[666] - Выход\n";

    while (true)
    {
        cout << "[SYSTEM MODE]: "; cin >> mode;

        switch (mode)
        {
        case 1:
            // Организация списка
            if (count > 0) // Если очередь не пустая
                cout << "[SYSTEM ERROR]: Организация списка уже была выполнена ранее! Вы можете добавить новые элементы в конец списка [2]\n";
            else // Если очередь пустая
            {
                begin = AddFirst(count, student, 0); // Добовление первого элемента

                end = begin;
            }
            break;
        case 2:
            if (count > 0) // Если очередь не пустая
                end = AddStructEnd(end, count, student, 0); // Добавить новые элементы в конец списка
            else // Очередь пустая
                cout << "[SYSTEM ERROR]: Организация списка еще не выполнена! Пожалуйста, выполните организацию списка [1]\n";
            break;
        case 3: // Очистить экран
            system("cls");
            cout << "[1] - Организация списка (добавление первого элемента)\n[2] - Добавить новые элементы в конец списка\n[3] - Очистить экран\n[4] - Показать список\n";
            cout << "[5] - Исключить последний элемент из списка\n[6] - Удалить весь список\n[7] - Сохранить данные в файл\n[666] - Выход\n";
            break;
        case 4: ViewList(begin, count); break; // Показать список
        case 5: end = DeleteLast(begin, end, count); break; // Исключить последний элемент из списка
        case 6: FreeMemory(begin, count); break; // Удалить весь список
        case 7: FileWriter(begin, fname, count); break; // Сохранить данные в файл
        case 666:
            if (count > 0)
            {
                cout << "[SYSTEM]: В очереди есть заполненные данные, Вы желаете их сохранить в файл?";
                cout << " [ПРЕДУПРЕЖДЕНИЕ!] - если файл уже существует, он будет перезаписан. Продолжить? [1] - ДА [AnyKey] - НЕТ\n[SAVE?]: ";
                cin >> mode;

                if (mode == 1) FileWriter(begin, fname, count); // Сохранить данные в файл
            }

            FreeMemory(begin, count); // Освободить память перед уходом
            return 0;
            break;
        }
    }
    return 7;
}