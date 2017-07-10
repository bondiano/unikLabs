#include <iostream>
#include <fstream> 
#include <algorithm> 
#include <ctime>
/*Защита:5,6
Сортировка c предварительным выбором. Из массива путем однократного просмотра выбирается последовательность элементов, находящихся в порядке возрастания и переносится очередную строку двумерного массива с заменой во входном на -1.  Этот процессс повторяется, пока в массиве не останется возрастающих последовательностей. После этого в масссиве остается последовательность в порядке убывания, которая также заносится в строку массива «задом наперед». Затем для строк производится однократное слияние. Если строрки в двумерном массиве окончатся раньше, после слияния оставшиеся элементы добавляются в выходной массив при помощи погружения.
*/
/*
	пока возрастает:
		выбирается последовательность эл-ов
		переносится в строку двумерного массива
		заменяется на -1
		повторяется, пока не останется возрастающих п-стей
	то, что осталось переносится в двумерный массив "задом наперед"
	слияние
	то что осталось, добавляется в выходной массив при помощи погружения*/

	/*
	Вставка погружением. Очередной элемент «погружается» путем ряда обменов с предыдущим до требуемой позиции в уже упорядоченную часть массива, пока «не достигнет дна», либо пока не встретит элемент, меньший себя. Наличие контекста «трех стаканов» делает его подозрительно похожим на обменную сортировку, но это не так.
	*/

using namespace std;
const int N = 50;//кол-во элементов в массиве со случайными
int T = 0; //сложность сортировки
int FnoMOne(int arr[], int size) //первый не равный -1
{
	for (int i = 0; i < size; ++i)
	{
		if (arr[i] != -1)
		{
			return arr[i];
			T++; //sort
		}
	}
	return -1;
}
bool haveGrow(int arr[], int size)
{
	int noMOne = FnoMOne(arr, size); //элемент не равный -1
	if (noMOne == -1)
		return 0;
	for (int i = 0; i < size; ++i)
	{
		T++; //sort
		if (arr[i] == -1)
		{
			continue;
		}
		if (noMOne < arr[i])
			return 1;
		noMOne = arr[i];
	}
	return 0;
}
int **create2dArr(int arr[], int size)
{
	int **input = new int*[size / 2]; //выделение памяти под двумерный массив
	int masStr = 1; //кол-во строк двумерного массива
	input[0] = new int[1];//в первой строке хранится кол-во строк
	int growSz = 0; //размерность возрастающей п-ти
	int *indexM = new int[size]; //массив индексов элементов возрастающей последовательности
	int temp = arr[0];
	int i = 0;
	/*пока есть возрастающие последовательности*/
	while(haveGrow(arr,size))
	{
		for (int k = 0; i < size; ++i)
		{
			T++;
			if(arr[i] == -1)
			{
				continue;
			}
			if (arr[i] >= temp) {
				growSz++;
				temp = arr[i];
				indexM[k++] = i;
			}
			else
			{
				break;
			}
		}
		if (growSz > 1)
		{
			/*переносим последовательность в строку двумерного массива*/
			input[masStr] = new int[growSz + 1];
			input[masStr][0] = growSz;
			for (int j = 0;j<growSz;++j)
			{
				input[masStr][j+1] = arr[indexM[j]];
				arr[indexM[j]] = -1;
			}
			masStr++;
			temp = FnoMOne(arr, size);
			i = 0;
		}else
		{
			temp = arr[i];
		}
		growSz = 0;
		/* for (int j = 0; j < size; ++j)
		{
			cout << arr[j] << ' ';
		}
		cout << endl;*/
	}
	if (FnoMOne(arr, size) != -1)
	{
		input[masStr] = new int[size]; //выделяем максимум памяти под оставшеесе
		int size_t = size - 1;
		growSz = 0;
		for (int k = 1; size_t >= 0; --size_t)
		{
			T++;//sort
			if (arr[size_t] != -1)
			{
				input[masStr][k++] = arr[size_t];
				growSz++;
				arr[size_t] = -1;
			}
		}
		input[masStr][0] = growSz;
		masStr++;
	}
	input[0][0]=masStr;
	for (int j = 1; j < masStr;++j)
	{
		input[0][j] = 1;
	}//для индексов строк
//	cout << input[0][0] << '\n';
/*	for (int t = 1; t < masStr; ++t)
	{
		for (int j = 1; j <= input[t][0]; ++j)
		{
			cout << input[t][j] << ' ';
		}
		cout << '\n';
	}*/
	return input;
}
int minIndex(int **arr)
{
	int minElIndex;
	/*ищем минимальный элемент*/
	for (int j = 1; j < arr[0][0]; ++j) 
	{
		T++;
		if (arr[0][j] > arr[j][0]) continue; //если вся строка уже вошла
		else 
		{
			minElIndex = j;
			break;
		}
	}
	for (int j = 1; j < arr[0][0]; ++j)
	{
		T++;
		if (arr[0][j]>arr[j][0]) continue; //если вся строка уже вошла
		if (arr[minElIndex][arr[0][minElIndex]] > arr[j][arr[0][j]])
		{
			minElIndex = j;
		}
	}
	return minElIndex;
}
int sort(int arr[], int size)
{
	int **input = create2dArr(arr, size);
	/*сортировочка слиянием*/
	/*остатки погружением*/
	for (int i = 0; i < size; ++i)
	{
		T++;
		arr[i] = input[minIndex(input)][input[0][minIndex(input)]];
		input[0][minIndex(input)]++;
	}
	return *arr;
}
int main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));
	int n = 0;
	cout << "Введите размерность массива\n";
	cin >> n;
	int *arr = new int[n];
	cout << "Введите массив, который отсортируем\n";
	for (int i = 0; i < n; ++i)
	{
		cin >> arr[i];
	}
	sort(arr, n);
	for (int i = 0;i < n;++i)
	{
		cout << arr[i] << ' ';
	}
	cout << endl;
	cout << "Трудоемкость(T):" << T << endl;
	cout << "Массив случайных чисел:" << endl;
	T = 0;
	int l[N];
	for (int i = 0; i < N; i++)
	{
		l[i] = rand() % 100 * pow(-1,rand()%2);
	}
	for (int i = 0; i < N; ++i)
	{
		cout << l[i] << ' ';
	}
	cout << endl;
	sort(l, N);
	for (int i = 0; i < N; ++i)
	{
		cout << l[i] << ' ';
	}
	cout << endl;
	cout << "Трудоемкость(T):" << T << endl;
	//int sz = 0;
	//int fMass = fileToMass(sz);
	system("pause");
}
