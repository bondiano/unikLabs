/*������-���������� � �������������� ���������� �� ������ � ����� ������� ���������������� ������� � ��������� ����������.
//------------------------------------------------------------15
void F15(char *c){
for (char *p=c; *p !='\0'; p++);
for (p--; p>c; p--,c++)
{ char s; s=*p; *p=*c; *c=s; }
}*/
#include <iostream>
//-------------- ������ - ����������
int *shekerSort(int *arr, int count)
{
	//��������� �� ������� ����� � ������� ������ �������
	int *left;
	left = arr;
	int *right;
	right = &arr[count - 1];
	int *next; //��������� �������
	int flag = 0; // ���� 1, �� �� ������������
	int temp;

	while (left < right && flag > 0)//���� ����� ������ ��������� ������ ������ ������� ��������� � ���� ������������ � ����
	{
		flag = 0;

		for (arr = left; arr <= right; arr++) //!�� ��������� ���� �������� ��������� � ����� ��������� ����� ���������� �������� � ����
		{
			next = arr + 1;
			if (*arr > *next)
			{
				//�������� ������� �������� ���������� next  � p
				temp = *arr;
				*arr = *next;
				*next = temp;

				flag = 1;       
			}
		}
		right--; //������� ����� �������� ������� �������� � ����

				 //� �������� �����������
		for (arr = right; arr > left; arr--)	
		{
			next = arr - 1; //�������� ����� ���������� ���������������� ��������
			if (*next > *arr)
			{
				temp = *arr;
				*arr = *next;
				*next = temp;

				flag = 1;  //������������ ���� � ����
			}
		}
		left++;

	}
	return arr;
}
int main()
{
	using namespace std;
	setlocale(LC_ALL, "Russian");
	int arr[4] = { 8,6,4,2 };
	int *rezult; //��������� �� ��������������� ������

	rezult = shekerSort(arr, 4); //���������� ����� ����, ��� ���������

	for (int i = 0; i < 4; i++)
		std::cout << rezult[i] << ' ';
	std::cout << '\n';

	//delete rezult;
	system("pause");
	return 0;
}