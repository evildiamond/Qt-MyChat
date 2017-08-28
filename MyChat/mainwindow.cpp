#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QTextEdit>
#include<QLabel>
#include<QScrollArea>
/*
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
*/
MainWindow::MainWindow(unsigned int id,QWidget *parent) :
    id(id),
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    udpServer=new UdpServer(id,&chatWindows);//udp

    this->setCentralWidget(ui->widget);

    myInfo = new UsrInfo(this);//设置头像
    myInfo->init(this,id,&chatWindows);
    friendsBox=new QToolBox();//好友列表

    QVBoxLayout*layout=new QVBoxLayout();//添加进gui中
    layout->addWidget(myInfo);
    layout->addWidget(friendsBox);
    ui->widget->setLayout(layout);

    addFirends();//生成好友
    initFriendsList();//导入好友

    chatWindows[id]=nullptr;
}

void MainWindow::initFriendsList(){
    for(const auto&group:friends){
        const QString&name=group.first;
        QWidget*groupWidget=new QWidget();
        friendsBox->addItem(groupWidget,name);
        QVBoxLayout*layout=new QVBoxLayout();
        for(int id:*group.second){
            UsrInfo*usr=new UsrInfo(this);
            usr->init(this,id,&chatWindows);
            layout->addWidget(usr);
        }
        groupWidget->setLayout(layout);
    }
}

void MainWindow::addFirends(){
    friends.push_back({QString("同学"),new QLinkedList<int>()});
    QLinkedList<int>*ls=friends.back().second;
    int idx=10000;
    for(int i=0;i<3;++i){
        if(idx==id){
            ++idx;
        }
        ls->push_back(idx++);
    }

    friends.push_back({QString("家人"),new QLinkedList<int>()});
    ls=friends.back().second;
    for(int i=0;i<5;++i){
        if(idx==id){
            ++idx;
        }
        ls->push_back(idx++);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

unsigned int MainWindow::getId(){
    return id;
}

UdpServer* MainWindow::getUdpServer(){
    return udpServer;
}
