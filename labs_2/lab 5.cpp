#include <iostream>
using namespace std;
/*7.Ќа шахматной доске имеетс€ N фигур противника. –азместить на ней минимальное количество слонов так, чтобы все фигуры противника находились Ђпод боемї.*/
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
			//провер€ем фигуры в углу
			if (chessboard[i][j] == 1 && i == 0 && j == 0 && chessboard[i + 1][j + 1] == 1) //левый верхний
			{
				return 0;
			}
			if (chessboard[i][j] == 1 && i == 0 && j == 7 && chessboard[i + 1][j - 1] == 1) //правый верхний
			{
				return 0;
			}
			if (chessboard[i][j] == 1 && i == 7 && j == 0 && chessboard[i - 1][j + 1] == 1) //левый нижний
			{
				return 0;
			}
			if (chessboard[i][j] == 1 && i == 7 && j == 7 && chessboard[i - 1][j - 1] == 1) //правый нижний
			{
				return 0;
			}
			//провер€ем фигуры на 4 диагонал€х
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
	short figureCount = 0; //узнаем количество не убитых фигур
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++) if(chessboard[i][j] == 1) figureCount++;
	}
	if (figureCount <= 0)
	{
		return **bishopMatrix;
	}
	//заполн€ем массив с диагональными "прострелами" фигур
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++) bishopMatrix[i][j] = 0;
	}
	//простреливаем диагонали
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (chessboard[i][j] == 1)
			{

				for (int k = i + 1, t = j + 1; k < 8 && t < 8; k++, t++)
				{
					if (chessboard[k][t] == 1 || chessboard[k][t] == 2) break; //если на диагонали встречаетс€ еще одна фигура, то пропускаем
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
	cout << "√лубина рекурсии: " << reqDeep << endl;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++) {
			cout << bishopMatrix[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
	//ищем точку с наибольшим прострелом
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
	//ставим туда слона
	chessboard[y][x] = 3;
	//фигуры в ауте замен€ем двойками
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
	cout << "—колько фигур будем расставл€ть?" << endl;
	cin >> count;
	cout << "¬ведите по очереди, сначала строчную букву, затем цифру, расположени€ фигуры" << endl;
	for (int i = 0; i < count; ++i)
	{
		int n = 0;
		char c = ' ';
		cin >> c;
		cin >> n;

		if(n > 8 || (c - 96) > 8)
		{
			cout << "¬ведите корректные значени€" << endl;
			--i;
			continue;
		}
		put_figure(c, n);
	}
	cout << "¬аше поле:" << endl;
	print_chessboard();
	cout << endl;
	unsigned short bishopMatrix[8][8];
	if (isNormal()){
		put_bishop(bishopMatrix);
		print_chessboard();
	}
	else cout << "≈сть фигуры закрытые по углам, слонов поставить невозможно" << endl;

	system("pause");
	return 0;
}