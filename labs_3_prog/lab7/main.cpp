#include <iostream>
#include <sqmatrix.h>
#include <circularqueue.h>

/* Лаб 7.
 * Задание: Структура данных: циклическая очередь.
 * Способ хранения объектов: ссылки на объекты.
 * Размерность структуры данных: динамический массив.
 * Операция: включение в конец очереди.
 * Операция: исключение из очереди.
 */

using namespace std;

int main()
{
    int intValues[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    char *charValues[3] = {"Mama", "mila", "ramu"};
    CircularQueue<int> intQueue(10);
    CircularQueue<char*> charQueue(3);

    for(int i = 0; i < 10; i++){
        intQueue.pushBack(intValues[i]);
    }

    for(int i =0; i < 3; i++){
        charQueue.pushBack(charValues[i]);
    }

    for(int i = 0; i < 10; i++){
        cout << intQueue.current->data << ' ';
        intQueue.popForward();
    }
    cout << endl;
    for(int i = 0; i < 3; i++){
        cout << charQueue.current->data << ' ';
        charQueue.popForward();
    }
    cout << endl;
    return 0;
}
