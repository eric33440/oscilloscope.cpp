#ifndef MYCANVAS_H
#define MYCANVAS_H
#include <QWidget>
#include <QTextStream>
#include <QtSerialPort/QSerialPort>
#include"serialcapture.h"
#include "QList"
#include <QObject>
class MyCanvas: public SerialCapture
{
    Q_OBJECT
private:
    static const int m_largeur=1000,m_hauteur=500;
    static const int m_unite=5;
    QPointF coo(int x, int y);
    QList<double> m_datarx;
    int m_zoom;
    QTextStream flux;
     float m_echantillonage=250;
    int m_amplitude=40, m_periode=10, m_phase=0;
    double f(double x);
    double g(double x);
public:
    explicit MyCanvas(QWidget *parent = 0);
    protected:
    void paintEvent(QPaintEvent *);

public slots:
    void receivedata(QList<double>);
    void zoomchanged(int);
    void amplitudeChanged(int);
    void periodeChanged(int);
    void phaseChanged(int);
    void echantillonageChanged(int echantillon);



};

#endif // MYCANVAS_H
