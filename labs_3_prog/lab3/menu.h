#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <sqmatrix.h>
using namespace std;

void chooseOp();
void createNew();
sqMatrix loadBin();
sqMatrix loadTxt();
void saveBin(sqMatrix *matrix);
void saveTxt(sqMatrix *matrix);

#endif // MENU_H
