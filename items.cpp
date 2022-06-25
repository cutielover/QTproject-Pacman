#include "items.h"
#include "map.h"

Items::Items(int _objectType, map * _Map): ObjectType(_objectType), Map(_Map)
{
//    //减速时钟
//    SlowClock = new QTimer(this);
//    //超级豆时钟
//    SuperClock = new QTimer(this);
}

void Items::ProduceItems() {
    int num = qrand() % 10;
    int x = qrand() % MAPLENGTH;
    int y = qrand() % MAPLENGTH;

    //1.如果随机数大于病毒(WeakenBean)出现概率,应该出现在空地
    if(num > Map->Pr_Bean)
    {
       int cnt = 0;
       //产生的病毒(WeakenBean)不能位于豆子上,怪物专路,玩家身上,水果上
       while(Map->BeanData[x][y] || Map->RoadData[x][y]<=0 || (x==Player->X && y==Player->Y) || item_list_p.empty())
       {
            //换一个位置
            y++;
            y %= MAPLENGTH;
            cnt++;
            if(cnt > MAPLENGTH) break;
       }
       if(cnt <= MAPLENGTH)
       {
           QList<QGraphicsItem *> item_list_p = GameScene->items(QRectF(y*BRICK_SIZE,x*BRICK_SIZE,BRICK_SIZE,BRICK_SIZE), Qt::IntersectsItemShape);
           SlowDownPacman * tmp = new SlowDownPacman(x, y);
           GameScene->addItem(tmp);
           //道具在倒数第二下层
           map->BeanData[x][y]=-1;
           tmp->setZValue(1);
       }
    }
    //2.如果随机数大于超级豆(SuperBean)出现概率(Map->Pr_Bean/2)
    else if(num > map->Pr_Bean / 2)
    {
        int cnt = 0;
        //产生的超级豆(SuperBean) 应出现在豆子上
        while(Map->BeanData[x][y]<=0 || (x==Player->X && y==Player->Y))
        {
             y++;
             y %= MAPLENGTH;
             cnt++;
             if(cnt > MAPLENGTH) break;
        }
        if(cnt <= MAPLENGTH)
        {
            QList<QGraphicsItem *> item_list_p = GameScene->items(QRectF(y*BRICK_SIZE,x*BRICK_SIZE,BRICK_SIZE,BRICK_SIZE), Qt::IntersectsItemShape);

            if(!item_list_p.empty()){
                //超级豆，会把出现处的除了玩家和幽灵都清除
                if(item_list_p[0]->type() != _ENEMY && item_list_p[0]->type() != _PLAYER)
                    GameScene->removeItem(item_list_p[0]);
            }

            SuperBean * tmp = new SuperBean(x, y);
            GameScene->addItem(tmp);
            //道具在倒数第二下层
            tmp->setZValue(1);
        }
    }
    //3.如果随机数为水果出现概率
    else {
        int cnt = 0;
        //产生的水果不能位于豆子上,怪物专路,玩家身上,病毒上
        while(Map->BeanData[x][y] || Map->RoadData[x][y]<=0 || (x==Player->X && y==Player->Y) || item_list_p.empty())
        {
             y++;
             y %= MAPLENGTH;
             cnt++;
             if(cnt > MAPLENGTH) break;
        }
        if(cnt <= MAPLENGTH)
        {
            QList<QGraphicsItem *> item_list_p = GameScene->items(QRectF(y*BRICK_SIZE,x*BRICK_SIZE,BRICK_SIZE,BRICK_SIZE), Qt::IntersectsItemShape);
            Fruit * tmp = new Fruit(x, y);
            GameScene->addItem(tmp);
            //道具在倒数第二下层
            map->BeanData[x][y]=-1;
            tmp->setZValue(1);
        }
    }
}

void Items::AddItems() {
    //??(需要与GamesWindow连接,加进信号接收槽AddPropsObject)
    connect(PropsTimer, &QTimer::timeout,this,&GameWindow::AddPropsObject);
}

//------------------------------------------------------------
//以下是三种道具的绘制
SlowDownPacman::SlowDownPacman(int x, int y)
{
    //将道具类的绘制原点进行偏移，偏移量为半个图像的大小，这样道具类的实际位置刚好处于图像中央
    setOffset(-PROP_SIZE/2,-PROP_SIZE/2);

    //绘制道具
    setPixmap(QPixmap(":/Images/Virus.png").scaled(PROP_SIZE, PROP_SIZE));

    X = x; Y = y;
    //设置道具类的初始位置
    setPos(Y*BRICK_SIZE+HALF_BRICK_SIZE,X*BRICK_SIZE+HALF_BRICK_SIZE);
}

SuperBean::SuperBean(int x, int y)
{
    //将道具类的绘制原点进行偏移，偏移量为半个图像的大小，这样道具类的实际位置刚好处于图像中央
    setOffset(-PROP_SIZE/2,-PROP_SIZE/2);

    //绘制道具
    setPixmap(QPixmap(":/Images/Super_bean.png").scaled(PROP_SIZE+6, PROP_SIZE+6));

    X = x; Y = y;
    //设置道具类的初始位置
    setPos(Y*BRICK_SIZE+HALF_BRICK_SIZE,X*BRICK_SIZE+HALF_BRICK_SIZE);
}

Fruit::Fruit(int x, int y)
{
    //将道具类的绘制原点进行偏移，偏移量为半个图像的大小，这样道具类的实际位置刚好处于图像中央
    setOffset(-PROP_SIZE/2,-PROP_SIZE/2);

    //绘制道具
    setPixmap(QPixmap(":/Images/Fruit.png").scaled(PROP_SIZE+6, PROP_SIZE+6));

    X = x; Y = y;
    //设置道具类的初始位置
    setPos(Y*BRICK_SIZE+HALF_BRICK_SIZE,X*BRICK_SIZE+HALF_BRICK_SIZE);
}




