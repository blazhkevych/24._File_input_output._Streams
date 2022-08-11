/*
 2. Написать программу, которая разбивает файл любого
формата на кусочки указанного размера, а затем
восстанавливаем файл из этих кусков.
 */

#include <iostream>
#include <fstream>
#include <Windows.h>
using namespace std;

int main()
{
    SetConsoleCP(1251);
    /*
    Задает кодовую страницу ввода, используемую консолью, связанной с вызывающим процессом.
    Консоль использует страницу входного кода для преобразования ввода с клавиатуры
    в соответствующее символьное значение.
    */
    SetConsoleOutputCP(1251);
    /*
    Задает выходную кодовую страницу, используемую консолью, связанной с вызывающим процессом.
    Консоль использует свою кодовую страницу вывода для преобразования символьных значений,
    записанных различными функциями вывода, в изображения, отображаемые в окне консоли.
    */

    cout << "Введите путь: "; // 1.jpg
    string str;
    cin >> str;

    ifstream in(str, ios::binary);
    if (!in) // если открытие файла завершилось неудачей - выходим
    {
        cout << "Error!\n";
        return;
    }

    in.seekg(0, ios::end);
    int const count = in.tellg();
    in.seekg(0, ios::beg);
    cout << count << endl;

    char File[50];
    char* buf = new char[size];

    for (int number = 0; in; ++number) // цикл продолжается до тех пор, пока не наступит конец файла
    {
        sprintf(File, "f:\\File%d.txt", number);
        ofstream out(File, ios::binary);

        if (number == 0)
        {
            out.write(f, strlen(f) + 1);
        }

        in.read(buf, size);
        out.write(buf, in.gcount());
        out.close();
    }

    delete[] buf;
    in.close();

}