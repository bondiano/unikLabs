#ifndef ITEM_H
#define ITEM_H


class Item
{
public:
    virtual int sizeOf() = 0;
    virtual void* getData() = 0;
};

#endif // ITEM_H
