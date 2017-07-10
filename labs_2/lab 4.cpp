#include <iostream>
using namespace std;
/*Объединение двух циклических списков. 7*/
struct list
{
	list *next;
	int value;
};
void push(list *&ls,int value)
{
	list *temp = new list;
	temp->next = ls;
	temp->value = value;
	if(ls->next == ls)
	{
		ls->next = temp;
	}
	else
	{
		list *t_list = ls;
		for (; t_list->next != ls; t_list = t_list->next);
		t_list->next = temp;
	}
}
list* merge(list *ls1, list *ls2)
{
	list *out = ls1;

	for (list *t_list2 = ls2; ; t_list2 = t_list2->next)
	{
		for (list *t_list1 = out; ; t_list1 = t_list1->next)
		{
			if (t_list1->value == t_list2->value) break;
			if (t_list1->next == out)
			{
				push(out, t_list2->value);
				break;
			}
		}
		if (t_list2->next == ls2)
		{
			break;
		}
	}
	return out;
}
list* create()
{
	list *out = new list;
	out->next = out;
	int count;
	cout << "Введите, из скольки элементов вы намеренны создать список" << endl;
	cin >> count;
	cin >> out->value;
	for (int i = 1; i < count; i++)
	{
		int value;
		cin >> value;
		push(out, value);
	}
	return out;
}
void printList(list *ls)
{
	cout << "Ваш список: ";
	for (list *t_list = ls; ; t_list = t_list->next)
	{
		cout << t_list->value << " ";
		if(t_list->next == ls)
		{
			break;
		}
	}
	cout << endl;
}
int main()
{
	setlocale(0, "rus");
	cout << "Это программа для объединения двух цикличных списков"<<endl;
	list *myList1 = new list;
	myList1 = create();
	printList(myList1);
	list *myList2 = new list;
	myList2 = create();
	printList(myList2);
	list *mergedList = new list;
	mergedList = merge(myList1, myList2);
	printList(mergedList);
	system("pause");
	return 0;
}