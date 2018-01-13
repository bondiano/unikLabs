#include <iostream>
#include <stack>
#include <set>
#include <iterator>
#include "sqmatrix.h"
#include <chrono>

using namespace std;
typedef chrono::high_resolution_clock Clock;

/* Для встроенного типа и класса из лабораторной работы №1 провести временной анализ заданных шаблонных классов на основных операциях:
 * добавление, удаление, поиск, сортировка.
 * Использовать итераторы для работы с контейнерами.
 * Для получения времени выполнения операции засекать системное время начала и окончания операции и автоматически генерировать большое количество данных.
 *
    • стек;
    • множество с дубликатами.
 */

int main()
{
    multiset<sqMatrix> matrixSet;
    stack<sqMatrix> matrixStack;
    const int nVal1 = 10;
    float **values1 = new float*[nVal1];
    for(int i = 0; i < nVal1; i++) {
        values1[i] = new float[nVal1];
        for(unsigned int j = 0; j < nVal1; j++) {
            values1[i][j] = rand()%100;
        }
    }

    float **values2 = new float*[100];
    for(int i = 0; i < 100; i++){
        values2[i] = new float[100];
        for(unsigned int j = 0; j < 100; j++) {
            values2[i][j] = rand()%100;
        }
    }

    float **values3 = new float*[100];
    for(int i = 0; i < 100; i++) {
        values3[i] = new float[100];
        for(unsigned int j = 0; j < 100; j++) {
            values3[i][j] = rand()%100;
        }
    }

    auto t1 = Clock::now();
    // Добавление в стэк
    for(int i = 0; i < 10000; i++) {
        if(i % 3 == 0) {
            matrixStack.push(sqMatrix(nVal1, values1));
        } else if (i % 3 == 1){
            matrixStack.push(sqMatrix(100, values2));
        } else {
            matrixStack.push(sqMatrix(100, values3));
        }
    }
    cout << "Matrix stack size: " << matrixStack.size() << endl;
    auto t2 = Clock::now();
    std::cout << "Delta push to stack t2-t1: "
                  << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count()
                  << " milliseconds" << std::endl;

    t1 = Clock::now();
    // Удаление из стека
    while(!matrixStack.empty()) {
        matrixStack.pop();
    }
    cout << "Matrix stack after pop all elements size: " << matrixStack.size() << endl;
    t2 = Clock::now();
        std::cout << "Delta pop from stack t2-t1: "
                      << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count()
                      << " milliseconds" << std::endl;

    t1 = Clock::now();
    multiset<sqMatrix>::iterator i;
    // Добавление в множество с дубликатами
    for(int i = 0; i < 10000; i++) {
        if(i % 3 == 0) {
            matrixSet.insert(sqMatrix(nVal1, values1));
        } else if (i % 3 == 1){
            matrixSet.insert(sqMatrix(100, values2));
        } else {
            matrixSet.insert(sqMatrix(100, values2));
        }
    }
    cout << "Matrix multyset size: " << matrixSet.size() << endl;

    cout << "First matrix value:" << endl;
    i = matrixSet.begin();
    i->print();

    cout << "Last matrix value:" << endl;
    i = matrixSet.end();
    i--;
    i->print();
    t2 = Clock::now();
        std::cout << "Delta add and show multiset t2-t1: "
                      << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count()
                      << " milliseconds" << std::endl;

    t1 = Clock::now();
    // Отчистка множества
    matrixSet.clear();

    cout << "Matrix multyset size after clear(): " << matrixSet.size() << endl;
    t2 = Clock::now();
        std::cout << "Delta clear multiset t2-t1: "
                      << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count()
                      << " milliseconds" << std::endl;

    for (unsigned int i = 0; i < 100; i++) {
        delete[] values1[i];
    }
    delete[] values1;

    for (unsigned int i = 0; i < 100; i++) {
        delete[] values2[i];
    }
    delete[] values2;

    for (unsigned int i = 0; i < 100; i++) {
        delete[] values3[i];
    }
    delete[] values3;

    return 0;
}
