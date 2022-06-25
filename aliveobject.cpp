#include "aliveobject.h"

aliveObject::aliveObject(int objectType, map* _Map)
     :bObject(objectType), Map(_Map) //??
{
}

//设置移动速度 Velocity，进一步计算出实际速度 Step(减小误差)
void aliveObject::SetVelocity(int setVelocity) {

    Velocity = setVelocity;

    if(Velocity == 0) Step = 0; //防止下面被除数为0(此时速度为0，对象静止)
    else {
        int tmp = BRICK_SIZE / Velocity;
        Step = (qreal)BRICK_SIZE / (qreal)tmp;
    }
}

//获得速度
int aliveObject::GetVelocity() {
    return Velocity;
}

//移动物体
void aliveObject::Move() {

    bool PosChanged = false;

    //如果没撞墙，则移动，改变实际位置
    if(!HitWall()) { //Dir_X,Dir_Y??

        setPos(QPointF(pos().x() + Dir_Y*Step, pos().y() + Dir_X*Step));
        PosChanged = true;

        Central = false;
    }
    else
        Dir_X = Dir_Y = 0;

    if(PosChanged) {

        //计算行X，列Y(以便之后消除误差;相当于向下取整)
        X = pos().y() / BRICK_SIZE;
        Y = pos().x() / BRICK_SIZE;

        //如果走到了穿梭通道，则进行穿梭
        if(pos().x() < 0) {
            Y = MAPLENGTH - 1;
            setPos(pos().x() + BRICK_SIZE*MAPLENGTH, pos().y());
        }
        else if(pos().x() >= BRICK_SIZE*MAPLENGTH) {
            Y = 0;
            setPos(pos().x() - BRICK_SIZE*MAPLENGTH, pos().y());
        }
        if(pos().y() < 0) {
            X = MAPLENGTH - 1;
            setPos(pos().x(), pos().y() + BRICK_SIZE*MAPLENGTH);
        }
        else if(pos().y() >= BRICK_SIZE*MAPLENGTH) {
            X = 0;
            setPos(pos().x(), pos().y() - BRICK_SIZE*MAPLENGTH);
        }

        //如果实际位置离当前方块的中心小于半个步幅，则该物体实际已经在方块中央，需要消除误差
        if(qAbs(pos().y() - (BRICK_SIZE*X + HALF_BRICK_SIZE)) < Step / 2
           &&
           qAbs(pos().x() - (BRICK_SIZE*Y + HALF_BRICK_SIZE)) < Step / 2
              ) {
            setPos(BRICK_SIZE*Y + HALF_BRICK_SIZE, BRICK_SIZE*X + HALF_BRICK_SIZE);
            Central = true;
        }
    }
}

//判断是否撞墙
bool aliveObject::HitWall() {

    //如果垂直移动
    if(Dir_X) {

        //计算碰撞点(物体前进方向最前端的点)
        qreal XFront = pos().y() + (OBJECT_SIZE/2 + Step) * Dir_X;
        int XBrickNext = XFront / BRICK_SIZE;

        if(XBrickNext>=0 && XBrickNext<MAPLENGTH &&
                (Map->WallData[XBrickNext][Y] || (ObjectType==_PLAYER && Map->RoadData[XBrickNext][Y]==-1))
              &&
                qAbs(XFront-(XBrickNext*BRICK_SIZE+HALF_BRICK_SIZE-Dir_X*HALF_BRICK_SIZE)) > Step/2
           )
                return true;

        //没撞墙时，
        //如果当前类为Player,则自动转向(防止小半个身子进墙)
        if(ObjectType==_PLAYER && (int)pos().x() != BRICK_SIZE * Y + HALF_BRICK_SIZE) {
            if((int)pos().x() - (BRICK_SIZE * Y + HALF_BRICK_SIZE) < 0)
                Dir_Y = 1;
            else Dir_Y = -1;
        }
        return false;

    }

    //如果水平移动
    if(Dir_Y) {

        qreal YFront = pos().x() + (OBJECT_SIZE/2 + Step) * Dir_Y;
        int YBrickNext = YFront / BRICK_SIZE;

        if(YBrickNext>=0 && YBrickNext<MAPLENGTH &&
                (Map->WallData[X][YBrickNext] || (ObjectType==_PLAYER && Map->RoadData[X][YBrickNext]==-1))

           )
        return true;

        if(ObjectType==_PLAYER && (int)pos().y() != BRICK_SIZE * X + HALF_BRICK_SIZE) {
            if((int)pos().y() - (BRICK_SIZE * X + HALF_BRICK_SIZE) < 0)
                Dir_X = 1;
            else Dir_X = -1;
        }
        return false;

    }
    return false;
}
