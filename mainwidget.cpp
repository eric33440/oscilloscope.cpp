#include "mainwidget.h"
#include "mycanvas.h"
#include "../LCDSlider/lcdslider.h"
#include <QPushButton>
#include <QGridLayout>
#include <QApplication>
#include <QSlider>
#include <QHBoxLayout>
#include "serialcapture.h"
#include <QLabel>
#include <QtSerialPort/QSerialPort>


MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    //QLabel*lab0= new QLabel("data");
    LcdSliderWidget *lcd= new  LcdSliderWidget("zoom",0,500,100);
    LcdSliderWidget *lcd1= new  LcdSliderWidget("amplitude",0,100,50);
    LcdSliderWidget *lcd2= new  LcdSliderWidget("periode",0,100,50);
    LcdSliderWidget *lcd3= new  LcdSliderWidget("phase",0,180,0);
    LcdSliderWidget *lcd4= new  LcdSliderWidget("echantillonage",1,500,250);

    // instanciation MyCanvas + QPushButton (pointeurs);
    MyCanvas *mc=new MyCanvas();
    QPushButton *qp1 = new  QPushButton("Quitter");
    // instanciation QGridLayout + ajout widgets
    QGridLayout *qgl=new QGridLayout();
    // le QGridLayout devient le layout courant    qgl->addWidget(qp1);
    qgl->addWidget(mc,0,0,1,3);
    qgl->addWidget(lcd,1,0,1,2);
    qgl->addWidget(qp1,1,2);
    qgl->addWidget(lcd1,2,0,1,1);
    qgl->addWidget(lcd2,3,0,1,1);
    qgl->addWidget(lcd3,4,0,1,1);
    qgl->addWidget(lcd4,5,0,1,1);

    setLayout(qgl);

    // Ajouter des connexions SIGNAL -> SLOT
    QObject::connect(qp1,SIGNAL(clicked()),qApp,SLOT(quit()));
    connect(lcd,SIGNAL(valueChanged(int)),mc,SLOT(zoomchanged(int)));
    connect(lcd1,SIGNAL(valueChanged(int)),mc,SLOT(amplitudeChanged(int)));
    connect(lcd2,SIGNAL(valueChanged(int)),mc,SLOT(periodeChanged(int)));
    connect(lcd3,SIGNAL(valueChanged(int)),mc,SLOT(phaseChanged(int)));
    connect(lcd4,SIGNAL(valueChanged(int)),mc,SLOT(echantillonageChanged(int)));
    emit lcd->valueChanged(100);

    //association du signal dans la classe serialcapture à celle receivedata dans le mycanvas

}

MainWidget::~MainWidget()
{}
