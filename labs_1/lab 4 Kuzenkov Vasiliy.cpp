#include <iostream>;
int main()
{
	setlocale(LC_ALL, "rus");
	int revCube = 0;
	int cube = 0;
	bool revCubeIsPrime = true;
	for (int i = 5; i < 10; ++i) // так как в КУБ 3 числа
	{
		//найти куб i, перевернуть его, проверить, простое ли это число
		cube = i * i * i;
		while (cube != 0) //переворот числа
		{
			revCube = revCube * 10 + cube % 10;
			cube /= 10;
		}
		//переобявляем
		cube = i * i * i;
		//условия простоты
		for (int j = 2; j <= sqrt(revCube); ++j) {
			if (revCube%j== 0) {
				revCubeIsPrime = false;
				break;
			}
		}
		//если простое
		if(revCubeIsPrime)
		{
			std::cout << "КУБ:" << cube << " БУК: " << revCube << std::endl;
		}
		revCubeIsPrime = true;
		revCube = 0;
		cube = 0;
	}
	system("pause");
	return 0;
}