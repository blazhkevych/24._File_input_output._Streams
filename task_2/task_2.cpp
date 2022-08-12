/*
############################################ ЗАДАНИЕ ###########################################
			Файловый ввод - вывод с применением потоков
	2. Написать программу, которая разбивает файл любого
формата на кусочки указанного размера, а затем
восстанавливаем файл из этих кусков.
################################################################################################
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

	cout << "Введите путь к исходному файлу: "; // 1.jpg
	string sourcePath{};
	cin >> sourcePath;

	cout << "Введите размер 1 кусочка в байтах: ";
	long long onePieceSizeInBytes{};
	cin >> onePieceSizeInBytes;

	ifstream readSourceFile(sourcePath, ios::binary | ios::in); // открывается  файл на чтение в бинарном режиме : при этом файл должен существовать
	if (!readSourceFile) // если открытие файла завершилось неудачей - выходим
	{
		cout << "Error!\n";
		return 0;
	}

	readSourceFile.seekg(0, ios::end); // смещение файлового указателя на 0 от конца
	long long sourceFileSize = readSourceFile.tellg(); // размер исходного файла
	readSourceFile.seekg(0, ios::beg); // смещение файлового указателя на 0 от начала

	char* bufForDataPiece = new char[onePieceSizeInBytes] {}; // буфер на 1 кусочек

	int i{ 0 };
	int countParts{};
	while (!readSourceFile.eof())
	{
		char bufferFileName[50];
		snprintf(bufferFileName, sizeof(bufferFileName), "file_%d.bin", i++);
		// открывается  файл на запись в бинарном режиме : если файл не существует - он будет создан, если файл существует - он будет усечён до нулевой длины
		ofstream writePieces(bufferFileName, ios::binary | ios::out);
		readSourceFile.read(bufForDataPiece, onePieceSizeInBytes); // из входящего потока считывается в буфер блок данных (4096 байт)
		writePieces.write(bufForDataPiece, readSourceFile.gcount()); // в выходной поток записывается считанный блок данных. При этом gcount возвращает реальное число считанных байт
		writePieces.close();
		countParts++;
	}
	readSourceFile.close();
	delete[] bufForDataPiece;
	cout << "Файл разобран !" << endl;

	char* resultBuffer = new char[onePieceSizeInBytes + 1]; // память под результирующий файл в размере заданной части файла

	cout << "Введите путь к исходному файлу: "; // 1.jpg
	string resultPath{};
	cin >> resultPath;

	ofstream resultOfParts_write(resultPath, ios::binary | ios::out);

	for (int j = 0; j < countParts; j++)
	{
		char partName[50]{};
		snprintf(partName, sizeof(partName), "file_%d.bin", j);
		ifstream read(partName, ios::binary | ios::in); // открывается  файл на чтение в бинарном режиме : при этом файл должен существовать

		read.read(resultBuffer, onePieceSizeInBytes);
		resultOfParts_write.write(resultBuffer, read.gcount()); // в выходной поток записывается считанный блок данных. При этом gcount возвращает реальное число считанных байт

		read.close();
	}
	resultOfParts_write.close();
	cout << "Файл собран !" << endl;
	delete[]resultBuffer;
}