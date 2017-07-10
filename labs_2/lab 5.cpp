#include <iostream>
using namespace std;
/*7.�� ��������� ����� ������� N ����� ����������. ���������� �� ��� ����������� ���������� ������ ���, ����� ��� ������ ���������� ���������� ���� ����.*/
unsigned short chessboard[8][8];
unsigned short reqDeep = 0;
void fill_chessboard()
{
	for (int i = 0; i < 8;i++)
	{
		for (int j = 0; j < 8; j++) chessboard[i][j] = 0;
	}
}

void put_figure(char x, int y)
{
	chessboard[x- 96 -1][y-1] = 1;
}

void print_chessboard()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++) {
			if(chessboard[i][j] == 0) //empty
			{
				cout << 'O' << ' ';
			}
			if (chessboard[i][j] == 1) //enemy
			{
				cout << 'E' << ' ';
			}
			if (chessboard[i][j] == 2) //shooted enemy
			{
				cout << 'X' << ' ';
			}
			if (chessboard[i][j] == 3) //bishop
			{
				cout << 'B' << ' ';
			}
		}
		cout << endl;
	}
}
bool isNormal()
{
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			//��������� ������ � ����
			if (chessboard[i][j] == 1 && i == 0 && j == 0 && chessboard[i + 1][j + 1] == 1) //����� �������
			{
				return 0;
			}
			if (chessboard[i][j] == 1 && i == 0 && j == 7 && chessboard[i + 1][j - 1] == 1) //������ �������
			{
				return 0;
			}
			if (chessboard[i][j] == 1 && i == 7 && j == 0 && chessboard[i - 1][j + 1] == 1) //����� ������
			{
				return 0;
			}
			if (chessboard[i][j] == 1 && i == 7 && j == 7 && chessboard[i - 1][j - 1] == 1) //������ ������
			{
				return 0;
			}
			//��������� ������ �� 4 ����������
			if(chessboard[i][j] == 1 && chessboard[i - 1][j - 1] == 1 && chessboard[i - 1][j + 1] == 1 && chessboard[i + 1][j - 1] == 1 && chessboard[i + 1][j + 1] == 1)
			{
				return 0;
			}
		}
	}
	return 1;
}
unsigned short put_bishop(unsigned short bishopMatrix[8][8])
{
	short figureCount = 0; //������ ���������� �� ������ �����
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++) if(chessboard[i][j] == 1) figureCount++;
	}
	if (figureCount <= 0)
	{
		return **bishopMatrix;
	}
	//��������� ������ � ������������� "�����������" �����
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++) bishopMatrix[i][j] = 0;
	}
	//������������� ���������
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (chessboard[i][j] == 1)
			{

				for (int k = i + 1, t = j + 1; k < 8 && t < 8; k++, t++)
				{
					if (chessboard[k][t] == 1 || chessboard[k][t] == 2) break; //���� �� ��������� ����������� ��� ���� ������, �� ����������
					bishopMatrix[k][t]++;
				}
				for (int k = i - 1, t = j - 1; k >= 0 && t >= 0; k--, t--)
				{
					if (chessboard[k][t] == 1 || chessboard[k][t] == 2) break;
					bishopMatrix[k][t]++;
				}
				for (int k = i - 1, t = j + 1; k >= 0 && t < 8; --k, ++t)
				{
					if (chessboard[k][t] == 1 || chessboard[k][t] == 2) break;
					bishopMatrix[k][t]++;
				}
				for (int k = i + 1, t = j - 1; k < 8 && t >= 0; ++k, t--)
				{
					if (chessboard[k][t] == 1 || chessboard[k][t] == 2) break;
					bishopMatrix[k][t]++;
				}
			}
		}
	}
	reqDeep++;
	cout << "������� ��������: " << reqDeep << endl;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++) {
			cout << bishopMatrix[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
	//���� ����� � ���������� ����������
	unsigned short max = 0;
	unsigned short x = 0, y = 0;
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			if(bishopMatrix[i][j] > max)
			{
				max = bishopMatrix[i][j];
				x = j;
				y = i;
			}
		}
	}
	//������ ���� �����
	chessboard[y][x] = 3;
	//������ � ���� �������� ��������
	for (int k = y + 1, t = x + 1; k < 8 && t < 8; k++, t++)
	{
		if (chessboard[k][t] == 1) {
			chessboard[k][t] = 2;
			break;
		}
	}
	for (int k = y - 1, t = x - 1; k >= 0 && t >= 0; k--, t--)
	{
		if (chessboard[k][t] == 1) {
			chessboard[k][t] = 2;
			break;
		}
	}
	for (int k = y - 1, t = x + 1; k >= 0 && t < 8; --k, ++t)
	{
		if (chessboard[k][t] == 1){
			chessboard[k][t] = 2;
			break;
		}
	}
	for (int k = y + 1, t = x - 1; k < 8 && t >= 0; ++k, t--)
	{
		if (chessboard[k][t] == 1) {
			chessboard[k][t] = 2;
			break;
		}
	}
	return put_bishop(bishopMatrix);
}
int main()
{
	setlocale(0, "rus");
	fill_chessboard();
	int count = 0;
	cout << "������� ����� ����� �����������?" << endl;
	cin >> count;
	cout << "������� �� �������, ������� �������� �����, ����� �����, ������������ ������" << endl;
	for (int i = 0; i < count; ++i)
	{
		int n = 0;
		char c = ' ';
		cin >> c;
		cin >> n;

		if(n > 8 || (c - 96) > 8)
		{
			cout << "������� ���������� ��������" << endl;
			--i;
			continue;
		}
		put_figure(c, n);
	}
	cout << "���� ����:" << endl;
	print_chessboard();
	cout << endl;
	unsigned short bishopMatrix[8][8];
	if (isNormal()){
		put_bishop(bishopMatrix);
		print_chessboard();
	}
	else cout << "���� ������ �������� �� �����, ������ ��������� ����������" << endl;

	system("pause");
	return 0;
}