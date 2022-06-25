#include "playerclass.h"

PlayerClass::PlayerClass(map * _Map): aliveObject(_PLAYER, _Map)
{
    //玩家初始方向为右边
    PreImages = new Movie(":/Images/Pacman_right.gif");
    //调整玩家图像大小
    PreImages->setScaledSize(QSize(PLAYER_SIZE, PLAYER_SIZE));
    //如果收到信号，就用setPixmap显示图片
    QObject::connect(PreImages, &QMovie::frameChanged, [=]() {
        setPixmap(PreImages->currentPixmap());
    });

    //死亡动画指针置空
    DieImage = nullptr;

    //初始时非超级豆时间
    IsSuperTime = false;

    //将玩家类设为可聚焦(focus),这样才能接收键盘信号
    setFlags(QGraphicsItem::ItemIsFocusable);

    //将玩家类的绘制原点进行偏移，偏移量为半个图像大小，这样玩家类的实际位置刚好处于整张图的正中央
    setOffset(-PLAYER_SIZE/2, -PLAYER_SIZE/2);

    //设置玩家的初始位置
    setPos(P_COL*BRICK_SIZE+HALF_BRICK_SIZE,P_ROW*BRICK_SIZE+HALF_BRICK_SIZE);

    //设置玩家初始的行和列
    X = P_ROW; Y = P_COL;

    //设置玩家初始速度
    SetVelocity(INIT_PLAYER_VELOCITY);

    //将玩家类的移动指令和缓存移动指令置零
    Dir_X = Dir_Y = PreX = PreY = 0;

    //初始方向为右边
    Dir = PreDir = 1;

    //最开始在方格中心，将方格中心标志设为真
    Central = true;

    //将四个键盘按下标记清零
    for(int i = 0; i < 4; ++i) ButtonPressed[i] = false;

    //初始键盘按下个数为0
    PressedKeys = 0;

    //加载右方向的图片
    Image = PreImages;
    Image->start();

}

//按压键盘
void PlayerClass::keyPressEvent(QKeyEvent * event)
{
    //如果按压指令是由第一次按下产生的（而非长按导致的重复按压与释放指令）
    //方向：   2
    //      0   1
    //        3
    if(!event->isAutoRepeat()) {
       switch(event->key()) {
          case Qt::Key_A:
                preX = 0; preY = -1; preDir = 0;
                ButtonPressed[0] = true;
                ++pressedKeys;
                break;
          case Qt::Key_D:
                preX = 0; preY = 1; preDir = 1;
                ButtonPressed[1] = true;
                ++pressedKeys;
                break;
          case Qt::Key_W:
                preX = -1; preY = 0; preDir = 2;
                ButtonPressed[2] = true;
                ++pressedKeys;
                break;
          case Qt::Key_S:
                preX = 1; preY = 0; preDir = 3;
                ButtonPressed[3] = true;
                ++pressedKeys;
                break;
       }
    }
}
//释放键盘
void PlayerClass::keyReleaseEvent(QKeyEvent * event)
{
    //如果释放指令是由第一次释放产生的（而非长按导致的重复按压与释放指令）
    //减少键盘按压个数并将对应键盘按压标记清零
    if(!event->isAutoRepeat()) {
        switch(event->key()) {
           case Qt::Key_A:
                ButtonPressed[0] = false;
                --pressedKeys;
           case Qt::Key_D:
                ButtonPressed[1] = false;
                --pressedKeys;
           case Qt::Key_W:
                ButtonPressed[2] = false;
                --pressedKeys;
           case Qt::Key_S:
                ButtonPressed[3] = false;
                --pressedKeys;
        }
        if(PressedKeys < 0) pressedKeys = 0;
        //如果按压键盘数为0， 则移动指令置零
        if(PressedKeys == 0) preX = preY = 0;
        //否则说明当前还有键盘在按压
        else {
            //将搜索到的第一个仍在按压的键盘对应
            if(ButtonPressed[0]) {
                preX = 0; preY = -1; preDir = 0;
            }
            else if(ButtonPressed[1]) {
                preX = 0; preY = 1; preDir = 1;
            }
            else if(ButtonPressed[2]) {
                preX = -1; preY = 0; preDir = 2;
            }
            else if(ButtonPressed[3]) {
                preX = 1; preY = 0; preDir = 3;
            }
        }
    }
}
void PlayerClass::Move()
{
    //如果新方向与原方向相同，或者正好在方格中心
    if((PreX == Dir_X || PreY == Dir_Y) || Central) {
        Dir_X = PreX;
        Dir_Y = PreY;

        //当正好在方格中心时，如果新方向与原方向不同， 则变向
        if(preDir != Dir) {
            switch(preDir) {
                case 0: setRotation(180); break;
                case 1: setRotation(0);   break;
                case 2: setRotation(270); break;
                case 3: setRotation(90);  break;
            }
            Dir = preDir;
        }
    }
    //调用父类aliveObject的Move函数
    aliveObject::Move();
}

PlayerClass::PlayerClass()
{
    Image->stop(); Image = nullptr;
    delete PreImages; PreImages = nullptr;
    if(DieImage!=nullptr) delete DieImage;
}

//暂停动态图
void PlayerClass::Pause()
{
    Image->setPaused(true);
}
//恢复动态图
void PlayerClass::Resume()
{
    Image->setPaused(false);
}

void PlayerClass::Die()
{
    Image->stop;
    setRotation(0);
    setOffset(-PLAYER_SIZE, -PLAYER_SIZE);
    DieImage = new QMovie(":/Images/Pacman_die.gif");
    DieImage->setSpeed(300);
    QObject::connect(DieImage, &QMovie::frameChanged, [=]()
    {
        setPixmap(DieImage->currentPixmap());
    });
    QObject::connect(DieImage, &QMovie::finished, [=]()
    {
        DieImage->stop();
    });
    DieImage->start();
}
void PlayerClass::CleanKeyPress()
{
    Dir_X = Dir_Y = PreX = PreY = 0;
    for(int i = 0; i < 4; ++i) ButtonPressed[i] = false;
    PressedKeys = 0;
}

void PlayerClass::focusOutEvent(QFocusEvent *event)
{
    setFocus();
}
