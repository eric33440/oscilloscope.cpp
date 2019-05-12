#include "serialcapture.h"
#include <QDebug>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QFile>
#include <QPainter>
#include <QColor>
#include <QtMath>
#include <cmath>
#include <QPushButton>
#include <QGridLayout>
#include <QApplication>
#include <QSlider>
#include <QPixmap>
#include <QFile>
#include "serialcapture.h"
#include <QDebug>



SerialCapture::SerialCapture()
{

    // configuration du port serie


    m_serial=new QSerialPort(this);
    m_serial->setPortName("/dev/ttyUSB0");
    m_serial->setBaudRate( QSerialPort::Baud115200);
    m_serial->setDataBits( QSerialPort::Data8);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);
    if(!m_serial->open(QIODevice::ReadOnly))
    {
        qDebug() <<QObject::tr("Je ne peux pas ouvrir le port série %1...").arg(m_serial->portName());
    }
    connect(m_serial,static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error), this,&SerialCapture::handleError);
    connect(m_serial,&QSerialPort::readyRead,this,&SerialCapture::read);
}

// fonction retournant une erreur, si il a un probleme avec le port serie

void SerialCapture::handleError(QSerialPort::SerialPortError error)
{
    if(error==QSerialPort::ResourceError)
    {
        qDebug() <<QObject::tr("Erreur critique : %1").arg(m_serial->errorString());
    }
}

//envoie des donnée dans le QList
void SerialCapture::read()
{
    QByteArray buf=m_serial->readAll();
    m_data.append(buf.toDouble());

}


