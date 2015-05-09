#ifndef SERIALARDUINO_H
#define SERIALARDUINO_H

#include <qextserialport.h>
#include <qextserialenumerator.h>
#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QMessageBox>
#include <QGridLayout>
#include <QTextEdit>
#include <QLineEdit>
#include <QSpacerItem>
#include <QLabel>
#include <QString>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QComboBox>
#include <string>


#include "mywindow.h"



class serialarduino : public QWidget
{
Q_OBJECT

public:
    serialarduino();
    void connected();
    bool protocol(QString cmd);
    void ConfigConnect();
    QByteArray getArray();
    void modificationPort();
    void readSerial();

public slots:
    void Connection(QString cmd);
    void readData();

signals:
    void readOk();

private:
    QWidget *widgetConnect;
    QComboBox *ComboPort;
    QPushButton *ComboConnect;
    QextSerialPort *port;
    int acceptConnect;
    QList<QextPortInfo> ports;
    QGridLayout *layout;
    int questionConfig;
    QByteArray array;
    mywindow *addtest;
    int commande;
    QString Port_variable;

};

#endif // SERIALARDUINO_H
