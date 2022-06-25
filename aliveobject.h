#ifndef ALIVEOBJECT_H
#define ALIVEOBJECT_H

#include <QGraphicsPixmapItem>
#include <QMovie>

#include "map.h"
#include "bobject.h"
#include "config.h"


class aliveObject: public bObject
{
public:
    aliveObject(int objectType, map* _Map); //??

    //设置速度
    void SetVelocity(int setVelocity);

    //获得速度
    int GetVelocity();

    //判断是否撞墙
    bool HitWall();

    //移动物体
    virtual void Move();

    //获得当前的行数X
    int getX(void) const{return X;}

    //获得当前的列数Y
    int getY(void) const{return Y;}

    //行列变化量
    int Dir_X, Dir_Y;
    int Dir;

//    //鼠标想要执行的变化量
//    int PreX, PreY, PreDir;

protected:
    QMovie *Image; //动态图
    map *Map;    //地图指针
    int Velocity;  //速度
    qreal Step;    //步幅(通过速度计算得到的每一步大小)

    bool Central;  //是否在方格中心

};

#endif // ALIVEOBJECT_H
