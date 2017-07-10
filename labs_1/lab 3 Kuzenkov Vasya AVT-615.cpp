#include<iostream>;
int one[3] = { 1,2,3 };
int two[6] = { 100,200,300,-100,-200,-300 };
int three[7] = { 2,2,3,3,5,5,10 };
int * prime = new int[100];
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
int mass_prime_num(int n, int *A) //из массива A в B попадпют простые
{
	int j, i, s, m;
	int *B = new int[n];

	for (j = 0, i = 0; i<n; i++) {
		for (s = 0, m = 2; m< A[i]; m++)
			if (A[i] % m == 0) { s = 1; break; }
		if (s == 0) B[j++] = A[i];
	}
	B[j] = 0;
	for (size_t i = 0; i < j; ++i)
	{
		A[i] = B[i];
	}
	A[j] = 0;
	return *A;
}
//32
int eql_num_mass(int n, int *c) { //количество повторяющихся елементов в массиве
	int s, i, k, j, b;
	for (s = 0, i = 0; i < n; i++) {
		for (k = 0, j = 0; j < n; j++)
			if (c[i] == c[j]) { k++; }
		if (k > s) s = k, b = i;
	}
	return s;
}
//40
int summ_to_first_negative(int n, int *A) { //сумма элементов массива до первого отрицательного
	int i, s;
	for (s = 0, i = 0; i < n && A[i]>0; i++)
		s = s + A[i];
	return s;
}
//48
int del_reuse_el(int Num, int *M)
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
	return *M;
}
int old_del_reuse_el(int Num, int *M, int el) {  //удаляются одинаковые элементы
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
int prime_num(int v) { //простые числа до v с костылем на последнее число(приравнивается 0)
	int a, i, n, s;
	for (i = 0, a = 2; a<v; a++) {
		for (s = 0, n = 2; n<a; n++)
			if (a%n == 0) { s = 1; break; }
		if (s == 0) prime[i++] = a;
	}
	prime[i] = 0;

	return *prime;
}
//28
int mas_GD(int n, int v, int *A) { //поиск наибольшего общего делителя массива не больше v
	int i;
	for (i = 0; i<n; i++)
		if (A[i] % v != 0) { v--; i = -1; }
	return v;
}
int main()
{
	setlocale(LC_ALL, "rus");
	//system("cls");
	std::cout << "Проверочные массивы: {1,2,3}, {100,200,300,-100,-200,-300}, {2,2,3,3,5,5,10}" << std::endl;
	std::cout << "Проверочные числа: 1002, 500, 666" << std::endl;
	std::cout << "F7(наименьший делитель) - 1 " << LD(1002) << std::endl;
	std::cout << "F7(наименьший делитель) - 2 " << LD(500) << std::endl;
	std::cout << "F7(наименьший делитель) - 3 " << LD(666) << std::endl;
	std::cout << "F15(переворот числа) - 1 " << rev_num(1002) << std::endl;
	std::cout << "F15(переворот числа) - 2 " << rev_num(500) << std::endl;
	std::cout << "F15(переворот числа) - 3 " << rev_num(666) << std::endl;
	std::cout << "24(из массива только простые числа) - 1 " << std::endl;
	mass_prime_num(3,one);
	for (int i = 0; i < 3 && one[i] != 0; i++)
	{
		if (one[i] <= 0)
		{
			continue;
		}
		std::cout << one[i] << ' ';
	}
	std::cout << std::endl << "24(из массива только простые числа) - 2 " << std::endl;
	mass_prime_num(6, two);
	for (int i = 0; i < 6 && two[i] != 0; i++)
	{
		if (two[i] <= 0)
		{
			continue;
		}
		std::cout << two[i] << ' ';
	}
	mass_prime_num(7, three);
	std::cout << std::endl << "24(из массива только простые числа) - 3 " << std::endl;
	for (size_t i = 0; i < 7 && three[i] != 0; i++)
	{
		if (three[i] <= 0)
		{
			continue;
		}
		std::cout << three[i] << ' ';
	}
	std::cout << std::endl << "64(количество делителей нацело числа , если а простое, то в вывод записывается Good) - 1: " << divisor_count_or_prime(1002) << std::endl;
	std::cout << "64(количество делителей нацело числа , если а простое, то в вывод записывается Good) - 2: " << divisor_count_or_prime(500) << std::endl;
	std::cout << "64(количество делителей нацело числа , если а простое, то в вывод записывается Good) - 3: " << divisor_count_or_prime(666) << std::endl;
	int t_one[3] = { 1,2,3 };
	int t_two[6] = { 100,200,300,-100,-200,-300 };
	int t_three[7] = { 2,2,3,3,5,5,10 };
	std::cout << std::endl << "32(количество повторяющихся елементов в массиве) - 1: " << eql_num_mass(3, t_one)-1 << std::endl;
	std::cout << std::endl << "32(количество повторяющихся елементов в массиве) - 2: " << eql_num_mass(6, t_two)-1 << std::endl;
	std::cout << std::endl << "32(количество повторяющихся елементов в массиве) - 3: " << eql_num_mass(7, t_three)+1 << std::endl;
	std::cout << std::endl << "40(сумма элементов массива до первого отрицательного) - 1: " << summ_to_first_negative(3, t_one) << std::endl;
	std::cout << std::endl << "40(сумма элементов массива до первого отрицательного) - 2: " << summ_to_first_negative(6, t_two) << std::endl;
	std::cout << std::endl << "40(сумма элементов массива до первого отрицательного) - 3: " << summ_to_first_negative(7, t_three) << std::endl;
	std::cout << std::endl << "56(Находит количество чередований положительных/отрицательных элементов) - 1: " << count_of_shift(one) << std::endl;
	std::cout << std::endl << "56(Находит количество чередований положительных/отрицательных элементов) - 1: " << count_of_shift(two) << std::endl;
	std::cout << std::endl << "56(Находит количество чередований положительных/отрицательных элементов) - 1: " << count_of_shift(three) << std::endl;
	std::cout << std::endl << "48(Удалить использованные элементы) - 1" << std::endl;
	del_reuse_el(3, t_one);
	for (size_t i = 0; i < 3 && t_one[i] != 0; i++)
	{
		std::cout << t_one[i] << ' ';
		if (t_one[i] == t_one[i + 1])
		{
			break;
		}
	}
	std::cout << std::endl << "48(Удалить использованные элементы) - 2" << std::endl;
	del_reuse_el(6, t_two);
	for (size_t i = 0; i < 6 && t_two[i] != 0; i++)
	{
		std::cout << t_two[i] << ' ';
		if (t_two[i] == t_two[i + 1])
		{
			break;
		}
	}
	std::cout << std::endl << "48(Удалить использованные элементы) - 3" << std::endl;
	del_reuse_el(7, t_three);
	for (size_t i = 0; i < 7; ++i)
	{
		std::cout << t_three[i] << ' ';
		if(t_three[i] == t_three[i+1])
		{
			break;
		}
	}

	std::cout << std::endl << "21(простые числа до числа, не считая единицы) - 1" << std::endl;
	prime_num(1002);
	for (size_t i = 0; i < 1002 && prime[i]!=0; ++i)
	{
		std::cout << prime[i] << ' ';
	}
	std::cout << std::endl << "21(простые числа до числа, не считая единицы) - 2" << std::endl;
	prime_num(500);
	for (size_t i = 0; i < 500 && prime[i] != 0; ++i)
	{
		std::cout << prime[i] << ' ';
	}
	std::cout << std::endl << "21(простые числа до числа, не считая единицы) - 3" << std::endl;
	prime_num(666);
	for (size_t i = 0; i < 666 && prime[i] != 0; ++i)
	{
		std::cout << prime[i] << ' ';
	}
	int s_one[3] = { 1,2,3 };
	int s_two[6] = { 100,200,300,-100,-200,-300 };
	int s_three[7] = { 2,2,3,3,5,5,10 };
	system("pause");
	return 0;
}