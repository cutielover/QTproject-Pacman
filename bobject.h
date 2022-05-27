#ifndef BOBJECT_H
#define BOBJECT_H
#include "config.h"

#include <QGraphicsPixmapItem>

class bObject : public QGraphicsPixmapItem
{
public:
    bObject(int objectType);
    const int ObjectType;     //物体对象的类型

    int X,Y;        //逻辑位置

};

#endif // BOBJECT_H
