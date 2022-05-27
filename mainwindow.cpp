#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->setupUi(this);


    this->setFixedSize(1600,1400);

    this->setWindowIcon(QIcon(":/Images/Pacman_icon.png"));

    this->setWindowTitle("Pac-man");

    MainSound=new QSound(":/Sound/Sounds/Main_sound.wav",this);
    MainSound->setLoops(QSound::Infinite);
    MainSound->play();

    Background=new QLabel(this);
    Background->setGeometry(0,0,1600,1400);
    GBackground=new QMovie(":/Images/GBackground.gif",QByteArray(),this);
    Background->setMovie(GBackground);
    GBackground->start();
    Background->lower();

    ui->GameTitle->setPixmap(QPixmap(":/Images/Game_title.png").scaled(840,610,Qt::KeepAspectRatio));


    QMovie *Gif_1=new QMovie(this);
    Gif_1->setFileName(":/Images/Cartoon.gif");
    Gif_1->setScaledSize(QSize(800,400));
    ui->MainWindowGif1->setFixedSize(800,400);
    ui->MainWindowGif1->setMovie(Gif_1);
    Gif_1->start();

    ui->Begin_button->setFixedSize(200,50);
    ui->Begin_button->setStyleSheet("QPushButton{border-image: url(:/Images/Begin_text.png);}"
                                    "QPushButton:hover{border-image: url(:/Images/Begin_text_hover.png);}"
                                    "QPushButton:pressed{border-image: url(:/Images/Begin_text_press.png);}");

    ui->Rule_button->setFixedSize(200,50);
    ui->Rule_button->setStyleSheet("QPushButton{border-image: url(:/Images/Rules_text.png);}"
                                   "QPushButton:hover{border-image: url(:/Images/Rules_text_hover.png);}"
                                   "QPushButton:pressed{border-image: url(:/Images/Rules_text_press.png);}");

    ui->Setting_button->setFixedSize(200,50);
    ui->Setting_button->setStyleSheet("QPushButton{border-image: url(:/Images/Settings_text.png);}"
                                      "QPushButton:hover{border-image: url(:/Images/Settings_text_hover.png);}"
                                      "QPushButton:pressed{border-image: url(:/Images/Settings_text_press.png);}");

    ui->Exit_button->setFixedSize(200,50);
    ui->Exit_button->setStyleSheet("QPushButton{border-image: url(:/Images/Exit_text.png);}"
                                   "QPushButton:hover{border-image: url(:/Images/Exit_text_hover.png);}"
                                   "QPushButton:pressed{border-image: url(:/Images/Exit_text_press.png);}");

    QSound *ClickSound=new QSound(":/Sound/Sounds/TapButton.wav",this);

    connect(ui->Exit_button,&QPushButton::released,[=]()        //退出按钮
    {
        ClickSound->play();
        QTimer::singleShot(200,this,&QWidget::close);
    });

}

MainWindow::~MainWindow()
{

}
