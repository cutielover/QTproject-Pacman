#ifndef MAP_H
#define MAP_H


#include "config.h"

//抽象类GMap
class map
{

public:
    bool WallData[MAPLENGTH][MAPLENGTH];        //墙
    int BeanData[MAPLENGTH][MAPLENGTH];         //豆
    int RoadData[MAPLENGTH][MAPLENGTH];         //路
    int BeansNum;                               //豆数目
    int Pr_Bean;        //超级豆概率

};
//第一关
class Stage_1 : public map
{
public:
    static const int  initData[MAPLENGTH][MAPLENGTH];	// 地图数据
    Stage_1();
};

class Stage_2 : public map
{
public:
    static const int initData[MAPLENGTH][MAPLENGTH];

    Stage_2();
};

class Stage_3 : public map
{
public:
    static const int initData[MAPLENGTH][MAPLENGTH];

    Stage_3();
};

class Stage_4 : public map
{
public:
    static const int initData[MAPLENGTH][MAPLENGTH];

    Stage_4();
};


#endif // MAP_H
