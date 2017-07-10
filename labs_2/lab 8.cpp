#include <iostream>
using namespace std;
/*¬ычитание  чисел  произвольной  длины, представленных непосредственно строками цифр с использованием дополнительного кода вычитаемого (в дес€тичной системе счислени€).*/
char *inputUnlimitedNumStr()
{
	char *str = (char*)malloc(sizeof(char));
	int len = 0;
	char ch;
	while(true)
	{
		ch = getchar();
		if(ch == ' ' || ch == '\n'|| ch == '-')
		{
			break;
		}
		len++;
		str = (char*)realloc(str, 8 * len);
		str[len] = ch-'0';
	}
	str[0] = len;
	return str;
}
bool biggest(char num1[], char num2[]) // true - num1, false - num2
{
	if(num1[0]>num2[0])
	{
		return 1;
	}
	if(num1[0]<num2[0])
	{
		return 0;
	}
	for (int i = 1; i <= num1[0]; i++)
	{
		if(num1[i]>num2[i])
		{
			return 1;
		}
		if (num2[i]>num1[i])
		{
			return 0;
		}
	}
	return 1;
}
void subtract(char num1[], char num2[], char result[])
{
	if(biggest(num1, num2))
	{
		int i = num1[0];
		result[0] = num1[0];
		for (int j = num2[0]; j != 0; i--,j--)
		{
			if(num1[i] < num2[j])
			{
				num1[i] += 10;
				num1[i - 1]--;
				result[i] = num1[i] + (~num2[j] + (1 << 8) + 1);
				continue;
			}
			result[i] = num1[i] + (~num2[j] + (1 << 8) + 1);
		}
		for (; i != 0;i--)
		{
			result[i] = num1[i];
		}
		i++;
		for (int j = 1; result[j] == 0;) //избавл€емс€ от нулей в первых разр€дах
		{
			for (int k = j, s = k + 1; s <= result[0];k++, s++)
			{
				result[k] = result[s];
			}
			result[0]--;
		}
	}else{
		int i = num2[0];
		result[0] = num2[0];
		for (int j = num1[0]; j != 0; i--, j--)
		{
			if (num2[i] < num1[j])
			{
				num2[i] += 10;
				num2[i - 1]--;
				result[i] = num2[i] + (~num1[j] + (1 << 8) + 1);
				continue;
			}
			result[i] = num2[i] + (~num1[j] + (1 << 8) + 1);
		}
		for (; i != 0; i--)
		{
			result[i] = num2[i];
		}
		i++;
		for (int j = 1; result[j] == 0;) //избавл€емс€ от нулей в первых разр€дах
		{
			for (int k = j, s = k + 1; s <= result[0]; k++, s++)
			{
				result[k] = result[s];
			}
			result[0]--;
		}
		result[1] = -result[1];

	}
}
int main()
{
	setlocale(0, "rus");
	cout << "¬ведите два числа произвольной длины" << endl;
	char *num1 = inputUnlimitedNumStr();
	char *num2 = inputUnlimitedNumStr();
	char *result = (char*)malloc(8 *(biggest(num1,num2) ? num1[0] : num2[0]));
	subtract(num1, num2, result);
	cout << "–езультат: ";
	for (int i = 1; i <= result[0]; i++)
	{
		cout << (int)result[i];
	}
	cout << endl;
	delete num1;
	delete num2;
	delete result;
	system("pause");
	return 0;
}