#include "serialarduino.h"

serialarduino::serialarduino():QWidget()
{
questionConfig = 0;
}

void serialarduino::connected()
{
    widgetConnect = new QWidget;
    widgetConnect -> setWindowTitle(tr("Configuration de Connexion"));
    layout = new QGridLayout;
    ComboConnect = new QPushButton("Connexion");

    ComboPort = new QComboBox();
    layout->addWidget(ComboPort, 0, 0);
    layout->addWidget(ComboConnect, 0, 1);
    widgetConnect->setLayout(layout);

    /*** Signal de connection ***/
   QObject::connect(ComboConnect, SIGNAL(clicked()), this, SLOT(Connection()));

       QextSerialEnumerator enumerateur;
       ports = enumerateur.getPorts();//on met ces infos dans une liste
       for(int i=0; i<ports.size(); i++)    {  // on fait une boucle pour ajouter tout les ports
                acceptConnect = i;
                ComboPort->addItem(ports.at(i).physName);
        }
   widgetConnect -> setFixedSize(200, 150);
   widgetConnect->show();
   widgetConnect->activateWindow();
}

bool serialarduino::protocol(QString cmd) // vérification commande
{                                         // Faire la désignation de commande
    if(cmd == "0000")
    {
        return true;
    }
    if(cmd == "0001")
    {
        return true;
    }
    if(cmd == "0010")
    {
        return true;
    }
    if(cmd == "0011")
    {
        return true;
    }
    if(cmd == "0100")
    {
        return true;
    }
    if(cmd == "0101")
    {
        return true;
    }
    if(cmd == "0110") // commande modifié jusqu'ici
    {
        return true;
    }
    if(cmd == "0111")
    {
        return true;
    }
    if(cmd == "1000")
    {
        return true;
    }
    if(cmd == "1001")
    {
        return true;
    }
    if(cmd == "1010")
    {
        return true;
    }
    if(cmd == "1011")
    {
        return true;
    }
    if(cmd == "1100")
    {
        return true;
    }
    if(cmd == "1101")
    {
        return true;
    }
    if(cmd == "1110")
    {
        return true;
    }
    if(cmd == "1111")
    {
        return true;
    }
    else
    {
        return false;
    }
}

void serialarduino::ConfigConnect()// Configuration de la liaison
{
    port = new QextSerialPort();
    port->setPortName("/dev/ttyACM0"); // Uniquement Linux | à modifier | "COM3" ou "/ dev/ttyACM0".
    port->setBaudRate(BAUD19200);
    port->setParity(PAR_NONE);
    port->setStopBits(STOP_1);
    port->setDataBits(DATA_8);
    port->setFlowControl(FLOW_OFF);
    port->open(QextSerialPort::ReadWrite);
    QObject::connect(port, SIGNAL(readyRead()), this, SLOT(readData())); // connection pour ajout commande par la touche entré
}

void serialarduino::Connection(QString cmd) //envoie l'information vers l'arduino
{
    if (protocol(cmd) == true)
    {
     questionConfig = 0;
     if(port != NULL)
         port->write(cmd.toUtf8());
    }

}

void serialarduino::readData() //Message Box par défaut
{
    emit readOk();
}

QByteArray serialarduino::getArray() //Message Box par défaut
{
    array = port->readAll();
    return array;
}

void serialarduino::modificationPort()
{
    Port_variable = port->readAll();
}

void serialarduino::readSerial()
{

}
