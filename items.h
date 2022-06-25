#ifndef ITEMS_H
#define ITEMS_H
#include <time.h>
#include "map.h"
#include "aliveobject.h"

class Items
{
public:
    Items(int objectType, map* _Map);

    //随机生成道具
    void ProduceItems();

    //定时加入道具
    void AddItems();

private:
    QTimer * AddClock; //定时加入道具时钟
    QTimer * SlowClock; //减速时钟
    QTimer * SuperClock; //超级豆时钟

    const int ObjectType; //物体类型

    map * Map; //地图指针

    MyGameScene * GameScene;
};

//道具：病毒(WeakenBean)
class SlowDownPacman
{
public:
    SlowDownPacman(int x, int y);

    //标记对象类型
    enum { Type = _SLOWVIRUS };
    int type() const override { return Type; }
};

//道具:超级豆(SuperBean)
class SuperBean
{
public:
    SuperBean(int x, int y);

    //标记对象类型
    enum { Type = _SUPERBEAN };
    int type() const override { return Type; }
};

//道具:水果(Fruit)
class Fruit
{
public:
    Fruit(int x, int y);

    //标记对象类型
    enum { Type = _FRUIT }; //(需要在config.h里添加_FRUIT)
    int type() const override { return Type; }
};

#endif // ITEMS_H
