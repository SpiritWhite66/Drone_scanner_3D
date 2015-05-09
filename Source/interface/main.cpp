#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QMainWindow>
#include <qextserialport.h>
#include <qextserialenumerator.h>
#include "mywindow.h"
#include "serialarduino.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    mywindow fenetre;
    fenetre.MyWindowBloc();
    fenetre.AffichageMenu();
    fenetre.AffichageShow();
    return app.exec();

}
