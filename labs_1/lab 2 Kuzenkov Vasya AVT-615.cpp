#include <iostream>
using namespace std;
/* cprog zadanie - informatika sem 1
*/
int num_menu();
int mass_menu();
int full_menu();
int main()
{
	setlocale(LC_ALL, "rus");
	int c;
	cout << "Введите 1 для работы с числами" << endl << "Введите 2 для работы с массивами" << endl << "Введите 3 для вывода всех заданий"<< endl << "Для выхода введите любой символ"<<"\n";
	cin >> c;
	switch(c){
	case 1:
		num_menu();
		return 0;
	case 2:
		mass_menu();	
		return 0;
	case 3: 
		full_menu();
		return 0;
	};
	return 0;
}
//7
int LD(int a) //наименьший делитель
{
	int n = 2;
	while (a%n != 0) {
		if (n == a) return 1;
		n++;
	}
	return n;
}
//15
int rev_num(int a) //переворот числа
{
	int n;
	int s;
	int k;
	for (n = a, s = 0; n != 0; n = n / 10)
	{
		k = n % 10;
		s = s * 10 + k;
	}
	return s;
}
//24
int mass_prime_num(int n, int *A, int el) //из массива A в B попадпют простые и отрицательные числа
{
	int j, i, s, m;
	int *B = new int[n];

	for (j = 0, i = 0; i<n; i++) {
		for (s = 0, m = 2; m< A[i]; m++)
			if (A[i] % m == 0) { s = 1; break; }
		if (s == 0) B[j++] = A[i];
	}
	B[j] = 0;

	return B[el];
}
//32
int eql_num_mass(int n, int *c) { //количество повторяющихся елементов в массиве
	int s, i, k, j, b;
	for (s = 0, i = 0; i < n; i++) {
		for (k = 0, j = 0; j < n; j++)
			if (c[i] == c[j]) { k++; }
		if (k > s) s = k, b = i;
	}
	return k;
}
//40
int summ_to_first_negative(int n, int *A) { //сумма элементов массива до первого отрицательного
	int i, s;
	for (s = 0, i = 0; i < n && A[i]>0; i++)
		s = s + A[i];
	return s;
}
//48
int del_reuse_el(int Num, int *M, int el)
{
	for (int i = 0; i < Num; ++i)
	{
		for (int j = i + 1; j < Num; ++j)
		{
			if (M[j] == M[i])
			{
				M[j] = 0;
			}
		}
	}
	for (int k = 0; k < Num; ++k) {
		for (int i = 0; i < Num; ++i)
		{
			if (M[i] == 0)
			{
				for (int j = i; j < Num; ++j)
				{
					if (M[j] != 0)
					{
						M[i] = M[j];
						break;
					}
				}
			}
			if (M[i] == M[i - 1]) {
				for (int j = i; j < Num; ++j)
				{
					if (M[i] != M[j])
					{
						M[i] = M[j];
						break;
					}
				}
			}
		}
	}
	return M[el];
}
int old_del_reuse_el(int Num, int *M,int el) {  //удаляются одинаковые элементы
	for (int Ar = 0; Ar < Num; Ar++)
	{
		for (int ElAr = Ar + 1; ElAr<Num; ElAr++)
		{
			if (M[ElAr] == M[Ar])
			{
				M[ElAr] = M[Num - 1];
				Num--;
			}
		}
	}
	//M[Num + 1] = 0;
	return M[el];
}
//56 
int count_of_shift(int *A) { //Находит количество чередований положительных/отрицательных элементов
	int i, s;
	for (i = 1, s = 0; i < 10; i++)
		if (A[i]>0 && A[i - 1] < 0) s++;
	return s;
}
//64
int divisor_count_or_prime(int a) { //количество делителей(s) нацело числа а, если а простое, то в вывод записывается Good
	int n, s;
	for (s = 0, n = 2; n < a; n++)
	{
		if (a%n == 0) s++;
	}
	if (s == 0) puts("Good");
	return s;
}
//21
int prime_num(int v, int *A) { //простые числа до v с костылем на последнее число(приравнивается 0)
	int a, i, n, s;
	//int *A = new int[v];
	for (i = 0, a = 2; a<v; a++) {
		for (s = 0, n = 2; n<a; n++)
			if (a%n == 0) { s = 1; break; }
		if (s == 0) A[i++] = a;
	}
	A[i] = 0;

	return *A;
}
//28
int mas_GD(int n, int v, int *A) { //поиск наибольшего общего делителя массива не больше v
	int i;
	for (i = 0; i<n; i++)
		if (A[i] % v != 0) { v--; i = -1; }
	return v;
}
int num_menu()
{
	system("cls");
	int num, c;
	c = 0;
	cout << "Введите число: ";
	cin >> num;
	system("cls");
	cout << "Выберите действие, введя его номер " << endl << "1) Узнать наименьший делитель" << endl << "2) Перевернуть число" << endl << "3) Узнать количество делителей нацело" << endl << "0) Выйти" << endl;
	cin >> c;
	switch (c)
	{
	case 1:
		system("cls");
		cout << "Наименьший делитель " << num << ": " << LD(num) << endl << "Введите 1 для перехода к вводу числа, любое другое для выхода" << endl;
		cin >> c;
		if (c == 1)
		{
			return num_menu();
		}
		return 0;
	case 2:
		system("cls");
		cout << "Перевернутое число " << num << ": " << rev_num(num) << endl << "Введите 1 для перехода к вводу числа, любое другое для выхода" << endl;
		cin >> c;
		if (c == 1)
		{
			return num_menu();
		}
		return 0;;
	case 3:
		system("cls");
		divisor_count_or_prime(num) ? cout << "Количество делителей нацело " << num << ": " << divisor_count_or_prime(num) << endl << "Введите 1 для перехода к вводу числа, любое другое для выхода" << endl : cout << "Это простое чисто" << endl << "Введите 1 для перехода к вводу числа, любое другое для выхода" << endl; //conditional expression
		cin >> c;
		if (c == 1)
		{
			return num_menu();
		}
		return 0;;
	case 0:
		return 0;;
	}
	//while (1);
	return 0;
}
int mass_menu()
{
	system("cls");
	int mas_len, c;
	cout << "Введите размер массива, затем сам массив, записав цифры через пробел: " << endl;
	cin >> mas_len;
	int *mass = new int[mas_len];
	for (int i = 0; i < mas_len; i++)
	{
		cin >> mass[i];
	}
	int i = 0;
	//system("cls");
	cout << "Выберите действие, введя его номер " << endl << "1) Узнать количество повторяющихся чисел в массиве" << endl << "2) Вывести только простые числа массива" << endl << "3) Cумма элементов массива до первого отрицательного" << endl << "4) Удаляются одинаковые элементы" << endl << "5) Количество чередований положительных/отрицательных элементов" << endl << "0) Выйти" << endl;
	cin >> c;
	switch (c) {
	case 1:
		//system("cls");
		cout << "Повторяющихся чисел в массиве: " << eql_num_mass(mas_len, mass) - 1;
		cout << endl << "Введите 1 для перехода к вводу числа, любое другое для выхода" << endl;
		cin >> c;
		if (c == 1)
		{
			return mass_menu();
		}
		return 0;
	case 2:
		//system("cls");
		cout << "Простые чисела массива: " << endl;
		for (int i = 0, nul = 1; i < mas_len, nul != 0; i++)
		{
			nul = mass_prime_num(mas_len, mass, i);
			cout << nul << ' ';
		}
		cout << endl << "Введите 1 для перехода к вводу числа, любое другое для выхода" << endl;
		cin >> c;
		if (c == 1)
		{
			return mass_menu();
		}
		return 0;
	case 3:
		//system("cls");
		cout << "Cумма элементов массива до первого отрицательного: " << summ_to_first_negative(mas_len, mass);
		cout << endl << "Введите 1 для перехода к вводу числа, любое другое для выхода" << endl;
		cin >> c;
		if (c == 1)
		{
			return mass_menu();
		}
		return 0;
	case 4:
		//system("cls");
		cout << "Итоговый массив: " << endl;
		while(i < mas_len){
			//if (del_reuse_el(mas_len, mass, i) == 0) break;
			cout << del_reuse_el(mas_len, mass,i) << ' ';
			i++;
		}
		cout << endl << "Введите 1 для перехода к вводу числа, любое другое для выхода" << endl;
		cin >> c;
		if (c == 1)
		{
			return mass_menu();
		}
		return 0;
	case 5:
		//system("cls");
		mas_len <= 10 ? cout << "Количество чередований положительных/отрицательных элементов: " << count_of_shift(mass) : cout << "Данная функция не может работать с массивами в которых больше 10 элементов";
		cout << endl << "Введите 1 для перехода к вводу числа, любое другое для выхода" << endl;
		cin >> c;
		if (c == 1)
		{
			return mass_menu();
		}
		return 0;
	case 0:
		return 0;
	}
	//while (1);
	return 0;
}
int full_menu()
{
	int one[3] = { 1,2,3 };
	int two[6] = { 100,200,300,-100,-200,-300 };
	int three[7] = { 2,2,3,3,5,5,10 };
	system("cls");
	cout << "Проверочные массивы: {1,2,3}, {100,200,300,-100,-200,-300}, {2,2,3,3,5,5,10}"<<endl;
	cout << "Проверочные числа: 1002, 500, 666"<<endl;
	cout << "F7(наименьший делитель) - 1 " << LD(1002) << endl;
	cout << "F7(наименьший делитель) - 2 " << LD(500) << endl;
	cout << "F7(наименьший делитель) - 3 " << LD(666) << endl;
	cout << "F15(переворот числа) - 1 " << rev_num(1002) << endl;
	cout << "F15(переворот числа) - 2 " << rev_num(500) << endl;
	cout << "F15(переворот числа) - 3 " << rev_num(666) << endl;
	cout << "24(из массива только и отрицательные простые числа) - 1 " << endl;
	for (int i = 0, nul = 1; i < 3, nul != 0; i++)
	{
		nul =  mass_prime_num(3, one, i);
		cout << nul << ' ';
	}
	cout << endl << "24(из массива простые и отрицательные числа) - 2 " << endl;
	for (int i = 0, nul = 1; i < 6, nul != 0; i++)
	{
		nul = mass_prime_num(6, two, i);
		cout << nul << ' ';
	}
	cout << endl << "24(из массива только простые и отрицательные числа) - 3 " << endl;
	for (int i = 0, nul = 1; i < 7, nul != 0; i++)
	{
		nul = mass_prime_num(7, three, i);
		cout << nul << ' ';
	}
	cout << endl << " ";
	cout << "64(количество делителей нацело числа , если а простое, то в вывод записывается Good) - 1: " << divisor_count_or_prime(1002) << endl;
	cout << "64(количество делителей нацело числа , если а простое, то в вывод записывается Good) - 2: " << divisor_count_or_prime(500) << endl;
	cout << "64(количество делителей нацело числа , если а простое, то в вывод записывается Good) - 3: " << divisor_count_or_prime(666) << endl;
	cout << endl << "32(количество повторяющихся елементов в массиве) - 1: " << eql_num_mass(3, one) << endl;
	cout << endl << "32(количество повторяющихся елементов в массиве) - 2: " << eql_num_mass(6, two) << endl;
	cout << endl << "32(количество повторяющихся елементов в массиве) - 3: " << eql_num_mass(7, three) << endl;
	cout << endl << "40(сумма элементов массива до первого отрицательного) - 1: " << summ_to_first_negative(3, one) << endl;
	cout << endl << "40(сумма элементов массива до первого отрицательного) - 2: " << summ_to_first_negative(6, two) << endl;
	cout << endl << "40(сумма элементов массива до первого отрицательного) - 3: " << summ_to_first_negative(7, three) << endl;
	cout << endl << "56(Находит количество чередований положительных/отрицательных элементов) - 1: " << count_of_shift(one) << endl;
	cout << endl << "56(Находит количество чередований положительных/отрицательных элементов) - 1: " << count_of_shift(two) << endl;
	cout << endl << "56(Находит количество чередований положительных/отрицательных элементов) - 1: " << count_of_shift(three) << endl;
	cout << endl << "48(элементы в такой ряд, чтобы не шли подряд одинаковые элементы) - 1" << endl;
	return 0;
};