#include <iostream>;
int main()
{
	setlocale(LC_ALL, "rus");
	int revCube = 0;
	int cube = 0;
	bool revCubeIsPrime = true;
	for (int i = 5; i < 10; ++i) // ��� ��� � ��� 3 �����
	{
		//����� ��� i, ����������� ���, ���������, ������� �� ��� �����
		cube = i * i * i;
		while (cube != 0) //��������� �����
		{
			revCube = revCube * 10 + cube % 10;
			cube /= 10;
		}
		//������������
		cube = i * i * i;
		//������� ��������
		for (int j = 2; j <= sqrt(revCube); ++j) {
			if (revCube%j== 0) {
				revCubeIsPrime = false;
				break;
			}
		}
		//���� �������
		if(revCubeIsPrime)
		{
			std::cout << "���:" << cube << " ���: " << revCube << std::endl;
		}
		revCubeIsPrime = true;
		revCube = 0;
		cube = 0;
	}
	system("pause");
	return 0;
}