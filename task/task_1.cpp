﻿/*
############################################ ЗАДАНИЕ ###########################################
			Файловый ввод - вывод с применением потоков
	1. Написать программу, которая подсчитывает количество строк
и количество слов в текстовом файле.
	2. Написать программу, которая разбивает файл любого
формата на кусочки указанного размера, а затем
восстанавливаем файл из этих кусков.
	3. Написать программу, которая позволяет удалить из HTML-файла все картинки, т.е.удалить значение атрибута src тега
<img>.
	4. Написать программу, выполняющую шифрование и
дешифрование текстового файла.Для шифрования
использовать операцию XOR «^ ».
	5. Написать программу, которая считывает текст из файла и
выводит в другой файл слова из этого текста, расположив
слова в порядке убывания частоты их появления.При этом
для каждого слова необходимо напечатать число его
появлений в исходном файле
################################################################################################
*/

#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
using namespace std;

// 1. Написать программу, которая подсчитывает количество строк
// и количество слов в текстовом файле.
// 1.txt

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

	cout << "Введите путь: ";
	string str;
	cin >> str;
	
	ifstream f_read(str, ios::in);

	if (!f_read.is_open()) // если открытие файла завершилось неудачей - выходим
	{
		cout << "Error!\n";
		return 0;
	}

	int line_count = 0;
	int word_count = 0;
	char buffer[1000]{};
	bool inWord = false;

	while (!f_read.eof())
	{
		line_count++;
		f_read.getline(buffer, 1000);

		for (int i = 0; i < strlen(buffer) + 1 && buffer[i] != '\0'; i++)
		{
			if (buffer[i] == ' ')
			{
				inWord = false;
			}
			else if (!inWord)
			{
				inWord = true;
				word_count++;
			}
		}
		inWord = false;
	}

	f_read.close();

	cout << "Слов в файле: " << word_count << endl;
	cout << "Строк в файле: " << line_count << endl;
	return 0;
}