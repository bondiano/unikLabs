#include <iostream>
/*����� � ������ ������������������ ���������� �������� ������������ ����� � ���������� � �������� ������ � ���� n1,n2c � ������ � ����� ��������� � ������, �������� abcddddddddddddedfg -> 3,12d. �� �������� ������ �������� �������. ��������� ���� �������. ���� � ������ ���� ������������������, � ����� ���������� ������� � �������� ������.*/
char del_rep_string(char *str, int &count)
{
	int n1 = 0;//������
	int temp_n1 = 0;//��������� �������� ������
	int n2 = 0;//�����
	int temp_n2 = 1;//��������� ����� ��� ���������
	char c = ' ';//������
	for (int i = 0; str[i] != '\0'; ++i)
	{
		if(str[i]==str[i+1])
		{
			temp_n1 = i;
			for (int j = i; str[j] == str[j + 1]; ++j) { temp_n2++; i = j; }
		}
		if(n2 < temp_n2)
		{
			n1 = temp_n1;
			n2 = temp_n2;
			c = str[i];
		}
		temp_n2 = 1;
	}
	count = n2;

	if (count > 1) {
		for (int i = n1; str[i] != '\0'; ++i)
		{
			str[i] = str[i + n2];
		}
		std::cout << n1 << ',' << n2 << c << '\n';
	}
	return *str;
}
int main()
{
	//std::ios::sync_with_stdio(false);
	char *str = new char[255];
	int count = 2;//������ �������
	std::cout << "������� ������:\n";
	std::cin >> str;
	for (; count > 1;){
		del_rep_string(str,count);
		for (int i = 0; str[i] != '\0'; ++i)
		{
			std::cout << str[i];
		}
	}
	for (int i = 0; str[i] != '\0'; ++i)
	{
		std::cout << str[i];
	}
	std::cout << '\n';
	//getchar();
	system("pause");
	return 0;
}