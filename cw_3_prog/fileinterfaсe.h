#ifndef FILEINTERFACE_H
#define FILEINTERFACE_H
#include "item.h"
#include <iostream>

class FileInterface
{
public:
    class BadItem : public std::exception {
    public:
        BadItem();
        BadItem(char const* const _Message);
    };

    class BadOpen :public std::exception {
    public:
        BadOpen();
        BadOpen(char const* const _Message);
    };

    class BadKey :public std::exception {
    public:
        BadKey();
        BadKey(char const* const _Message);
    };

    class BadPos : public std::exception {
    public:
        BadPos();
        BadPos(char const* const _Message);
    };

    class CriticalError : public std::exception {
    public:
        CriticalError();
        CriticalError(char const* const _Message);
    };
    virtual double insertI(Item* item) = 0;
    virtual void* getI() = 0;
    virtual void deleteI(double key) = 0;
    virtual void printAll() = 0;
};

#endif // FILEINTERFACE_H
