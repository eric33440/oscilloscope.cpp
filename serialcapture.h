#ifndef SERIALCAPTURE_H
#define SERIALCAPTURE_H
#include <QWidget>
#include <QList>
#include <QtSerialPort/QSerialPort>
#include <QTextStream>

class SerialCapture: public QWidget
{
    Q_OBJECT
private:
    QSerialPort *m_serial;
public:
    QList<double> m_data;
    //protected:
    SerialCapture();
    void read ();
public slots:
    void handleError(QSerialPort::SerialPortError error);
signals:

};

#endif // SERIALCAPTURE_H
