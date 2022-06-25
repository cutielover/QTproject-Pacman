#ifndef PLAYERCLASS_H
#define PLAYERCLASS_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QMovie>
#include <QTimer>

#include "config.h"
#include "aliveobject.h"


class PlayerClass: public aliveObject
{
public:
    PlayerClass(map * _Map);
    ~PlayerClass();

    //重写移动函数
    void Move() override;

    //暂停函数，让图像静止
    void Pause();

    //继续函数，让图像恢复动态
    void Resume();

    //失败时显示死亡动画
    void Die();

    //标记对象类型
    int Type = _PLAYER;
    int type() const override { return Type;}

    bool IsSuperTime; //是否是超级豆时间

    int preX, preY; //与键盘联系的Dir_x, Dir_Y
    int preDir; //与键盘联系的Dir

protected:
    void keyPressEvent(QKeyEvent * event) override; //重写键盘按下事件
    void keyReleaseEvent(QKeyEvent * event) override; //重写键盘释放事件
    void focusOutEvent(QFocusEvent * event) override;
private:
    int pressedKeys; //记录键盘按下的个数
    bool ButtonPressed[4]; //标记哪些键盘被按下
    QMovie * PreImages; //缓存四个方向的动态图
    QMovie * DieImage; //死亡动画
};


#endif // PLAYERCLASS_H
