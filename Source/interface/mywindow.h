#ifndef MYWINDOW_H
#define MYWINDOW_H

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
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>



class serialarduino;

class mywindow : public QMainWindow // On hérite de QWidget
{
    Q_OBJECT


    public:
    mywindow();
    mywindow(int x, int y);
    void MyWindowBloc();
    void AnswerTest();
    void AffichageShow();
    void AffichageMenu();
    void MyConnectInterface();
    void NewScanRaz(bool effect);
    void dialogboxmessagesdefault();
    void setAnswer(bool effect); // Modifieur
    bool getAnswer() const; // Accesseur
    void printAnswer(); // Accesseur
    void CommandHelp();
    void printSerial();

    public slots:
    void AnswerDialogueCommande(QString reponse);
    void AnswerDialogueCommandeArduino();
    void dialogboxmessagestop();
    void dialogboxmessagestart();
    void dialogboxquestion();
    void dialogboxnewscan();
    void AddDialogueCommande();
    void ConnectInPort();


    private:
    /*** Variable QWdiget et menu***/
    QWidget *zoneCentrale;
    QMenu *menuFichier;
    QMenu *menuEdition;
    QMenu *menuAffichage;
    QMenu *menuAide;
    QAction *actionQuitter;
    QAction *actionNouveau;
    QAction *actionFermerScan;
    QAction *actionAucun;
    QAction *actionConnect;
    /*** Variable de bouton ***/
    QPushButton *m_start;
    QPushButton *m_stop;
    QPushButton *m_restart;
    QPushButton *m_envoi;


    QGridLayout *layoutPrincipal;
    QTextEdit *m_console;
    QTextEdit *m_gl;
    QLineEdit *m_enter_console;

    /*** Espace ***/
    QSpacerItem *spacer1;
    QSpacerItem *spacer2;
    QSpacerItem *spacer3;

   /***Affichage information Moteur***/
    QLabel *label_motor_1;
    QLabel *label_motor_2;
    QLabel *label_motor_3;
    QLabel *label_motor_4;
    QLabel *label_motor_5;

    /*** Variable de fonctionnement ***/
    QString recupcommand;
    bool answer;
    QString reponse;
    serialarduino *comArduino;
    QString commandArray;
};

#endif // MYWINDOW_H
