#include "mywindow.h"
#include "serialarduino.h"

mywindow::mywindow():QMainWindow() // hérite de QWidget
{
    zoneCentrale = new QWidget;
    setCentralWidget(zoneCentrale);
    comArduino = new serialarduino();
}
mywindow::mywindow(int x,int y):QMainWindow()// constructeur surchargé
{

     zoneCentrale = new QWidget;
     zoneCentrale -> setFixedSize(x, y);
     setCentralWidget(zoneCentrale);
     comArduino = new serialarduino();
}

void mywindow::MyWindowBloc()
{
    comArduino->ConfigConnect();


    layoutPrincipal = new QGridLayout;
    /**** Création des espaces ****/
    spacer1 = new QSpacerItem (200, 60, QSizePolicy::Minimum, QSizePolicy::Expanding);
    spacer2 = new QSpacerItem (200, 60, QSizePolicy::Minimum, QSizePolicy::Expanding);
    spacer3 = new QSpacerItem (200, 60, QSizePolicy::Minimum, QSizePolicy::Expanding);

    /**** Création des labels ****/
   label_motor_1 = new QLabel("Moteur 1 : 00.00%");
   label_motor_2 = new QLabel("Moteur 2 : 00.00%");
   label_motor_3 = new QLabel("Moteur 3 : 00.00%");
   label_motor_4 = new QLabel("Moteur 4 : 00.00%");
   label_motor_5 = new QLabel("ServoMoteur : 00.00%");

    /**** Création des éléments *****/
    m_start = new QPushButton("start Scan");
    m_stop = new QPushButton("stop Scan");
    m_restart = new QPushButton("remise a zero du Scan");
    m_envoi = new QPushButton("Envoie");


    /****Création de la console ****/
    m_console = new QTextEdit("|||Initialisation <br /> |||Charge ... <br /> ||| Pret ! ");
    m_console -> setReadOnly(true);

    m_enter_console = new QLineEdit("Envoye une commande");

    m_gl = new QTextEdit("Fenetre OpenGL : Start OK...");

    /**** Placement de Layout *****/
    layoutPrincipal->addWidget(m_start,0,0,1,1);
    layoutPrincipal->addWidget(m_stop,1,0,1,1);
    layoutPrincipal->addWidget(m_restart,2,0,1,1);
    layoutPrincipal->addWidget(label_motor_1,4,0,1,1);
    layoutPrincipal->addWidget(label_motor_2,5,0,1,1);
    layoutPrincipal->addWidget(label_motor_3,6,0,1,1);
    layoutPrincipal->addWidget(label_motor_4,7,0,1,1);
    layoutPrincipal->addWidget(label_motor_5,8,0,1,1);
    layoutPrincipal->addItem(spacer1, 3, 0);
    layoutPrincipal->addItem(spacer2, 9, 0);
    layoutPrincipal->addItem(spacer3, 10, 0);
    layoutPrincipal->addWidget(m_gl,0,2,11,2);
    layoutPrincipal->addWidget(m_console,11,2,1,2);
    layoutPrincipal->addWidget(m_enter_console,12,2,1,1);
    layoutPrincipal->addWidget(m_envoi,12,3,1,1);
    zoneCentrale -> setLayout(layoutPrincipal);


    m_start->setCursor(Qt::PointingHandCursor);
    m_stop->setCursor(Qt::PointingHandCursor);
    m_restart->setCursor(Qt::PointingHandCursor);
    connect(comArduino, SIGNAL(readOk()), this, SLOT(AnswerDialogueCommandeArduino()));
}


void mywindow::dialogboxmessagestart() //Slot
{
    comArduino->Connection("11111111");  // code start est 1111 1111
     recupcommand = m_console ->toPlainText()+"\n" + ">>> Start|11111111";
     m_console -> setText(recupcommand);
     QMessageBox::information(this, "Start", "Lancement du module");

}

void mywindow::dialogboxmessagestop() //Slot
{
     comArduino->Connection("00000000"); // code stop est 0000 0000
     recupcommand = m_console ->toPlainText()+"\n" + ">>> Stop|00000000";
     m_console -> setText(recupcommand);
     QMessageBox::information(this, "Stop", "Arret du module");
}


void mywindow::dialogboxmessagesdefault() //Message Box par défaut
{
     QMessageBox::information(this, "defaut", "Defaut");
}


void mywindow::dialogboxquestion() //Slot
{
    recupcommand = m_console ->toPlainText()+"\n" + ">>> Init Restart Command >>>";
    m_console -> setText(recupcommand);
    int reponse = QMessageBox::question(this, "dialogboxquestion", "Etes-vous sur de vouloir faire une Remise à zéro",QMessageBox::Yes | QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
    comArduino->Connection("00000001");
    recupcommand = m_console ->toPlainText()+"\n" + ">>> Restart|00000001"; // code de restart est 0000 0001
    m_console -> setText(recupcommand);
    QMessageBox::information(this, "Title", "La remise à zéro est effectué !");
    }
    else if (reponse == QMessageBox::No)
    {
    recupcommand = m_console ->toPlainText()+"\n" + ">>> Cancel->Restart|00001000"; // code annulation restart (ne pas envoyé à l'arduino)
    m_console -> setText(recupcommand);
    QMessageBox::critical(this, "Title", "La remise à zéro est annulé !");
    }

}

void mywindow::AddDialogueCommande() //Slot
{
    if(m_enter_console ->text() != NULL)
    {

    comArduino->Connection(m_enter_console ->text()); // On envoie à l'arduino
    recupcommand = m_enter_console ->text(); // on ajoute la commande sur l'interface
    recupcommand = m_console ->toPlainText()+"\n" + ">>>" +recupcommand;
    m_console -> setText(recupcommand);
        if(m_enter_console ->text() == "help") // test si la commande serait pas celle "d'aide"
        {
            CommandHelp();
        }
    m_enter_console -> setText("");
    }
}

void mywindow::AnswerDialogueCommande(QString reponse) // A modifié
{
   recupcommand = m_console ->toPlainText()+"\n" + "<<< Reponse du module =>" + reponse  ; // changé recupcommand par une fonction QtSerialPort
   m_console -> setText(recupcommand);
}
void mywindow::AnswerDialogueCommandeArduino() // Ecrit la réponse du module !
{
   recupcommand = m_console ->toPlainText()+"\n" + "<<< Reponse du module =>" + comArduino->getArray()  ; // Réponse du module
   m_console -> setText(recupcommand);
}

void mywindow::AnswerTest() //Test si la réponse est positive ou négative
{
// vide pour le moment !
}

void mywindow::AffichageShow() //pour lancer la fenetre
{
//this -> show();
this -> showFullScreen();
}

void mywindow::AffichageMenu() //pour afficher les menus et leur action
{
    menuFichier = menuBar()->addMenu("&Fichier");
    actionNouveau = new QAction("&Nouveau Scan", this);
       menuFichier->addAction(actionNouveau);
    actionFermerScan = new QAction("&Fermer le Scan", this);
       menuFichier->addAction(actionFermerScan);
    actionQuitter = new QAction("&Quitter", this);
       menuFichier->addAction(actionQuitter);

    menuEdition = menuBar()->addMenu("&Edition");
    actionConnect = new QAction("&Connexion", this);
    actionAucun = new QAction("&Aucun", this);
       menuEdition->addAction(actionConnect);
    menuAffichage = menuBar()->addMenu("&Affichage");
    menuAffichage->addAction(actionAucun);
    menuAide= menuBar()->addMenu("&Aide");
    menuAide->addAction(actionAucun);

    MyConnectInterface();
}

void mywindow::MyConnectInterface() //Création des connections
{
    QObject::connect(m_stop, SIGNAL(clicked()), this, SLOT(dialogboxmessagestop())); // connection avec le bouton stop
    QObject::connect(m_start, SIGNAL(clicked()), this, SLOT(dialogboxmessagestart())); // connection avec le bouton start
    QObject::connect(m_restart, SIGNAL(clicked()), this, SLOT(dialogboxquestion())); // connection avec le bouton restart
    QObject::connect(m_envoi, SIGNAL(clicked()), this, SLOT(AddDialogueCommande())); // connection pour ajout commande par le bouton
    QObject::connect(m_enter_console, SIGNAL(editingFinished()), this, SLOT(AddDialogueCommande())); // connection pour ajout commande par la touche entré
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(actionNouveau, SIGNAL(triggered()), this, SLOT(dialogboxnewscan()));
    connect(actionConnect, SIGNAL(triggered()), this, SLOT(ConnectInPort()));
}

void mywindow::dialogboxnewscan() //Slot
{
    recupcommand = m_console ->toPlainText()+"\n" + ">>> Init Restart Command >>>";
    m_console -> setText(recupcommand);
    int reponse = QMessageBox::question(this, "dialogboxquestion", "Etes-vous sur de vouloir faire une Remise à zéro",QMessageBox::Yes | QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
    comArduino->Connection("00000001");
    recupcommand = m_console ->toPlainText()+"\n" + ">>> Restart|00000001";
    m_console -> setText(recupcommand);
    QMessageBox::information(this, "Title", "La remise à zéro est effectué !");
    NewScanRaz(true);
    }
    else if (reponse == QMessageBox::No)
    {
    recupcommand = m_console ->toPlainText()+"\n" + ">>> Cancel->Restart|10000000";
    m_console -> setText(recupcommand);
    QMessageBox::critical(this, "Title", "La remise à zéro est annulé !");
    NewScanRaz(false);
    }

}

void mywindow::NewScanRaz(bool effect) // Nouveau scan, remise à zéro
{
    if (effect == true)
    {
        comArduino->Connection("11111111"); // code de nouveau scan | envoie à l'arduino
        recupcommand =">>> Nouveau scan prêt|11111111";
        m_console -> setText(recupcommand);
        QMessageBox::information(this, "Stop", "Le nouveau scan est prêt !");
    }
    else
    {
        comArduino->Connection("00000000"); // code de nouveau scan | envoie à l'arduino
        recupcommand = m_console ->toPlainText()+"\n" + ">>> Cancel -> Nouveau scan|00000000";
        m_console -> setText(recupcommand);
        QMessageBox::information(this, "Stop", "Annulation de la création du nouveau scan");
    }
}

void mywindow::setAnswer(bool effect)
{
    answer = effect;
}

bool mywindow::getAnswer() const
{
    return answer;
}

void mywindow::printAnswer()
{
    m_console -> setText("printAnswer renvoie => TRUE");
}

void mywindow::ConnectInPort() // Connection à l'Arduino avec serialarduino.cpp
{
    comArduino->connected();
}

void mywindow::CommandHelp()
{
    QList<QString> listecommande;
    listecommande.append("0000 |  Eteindre => module");
    listecommande.append("0001 |  Allumé => module");
    listecommande.append("0010 |  Non Implanté");
    listecommande.append("0011 |  Eteindre => laser");
    listecommande.append("0100 |  Allumé => laser");
    listecommande.append("0101 |  Eteindre => moteur");
    listecommande.append("0110 |  Allumé => moteur");
    listecommande.append("0111 |  Vérification série (allumage d’une LED)");
    listecommande.append("1000 |  Demande position moteur");
    listecommande.append("1001 |  Non Implanté");
    listecommande.append("1010 |  Non Implanté");
    listecommande.append("1011 |  Restart Module");
    listecommande.append("1111 |  Affichage paramètre de la connexion série");

    recupcommand = m_console ->toPlainText()+"\n" + "<<< Commande du système : ";
    m_console -> setText(recupcommand);

    for(int i = 0; i<13; i++)
    {
        recupcommand = listecommande[i];
        recupcommand = m_console ->toPlainText()+"\n" +recupcommand + " ";
        m_console -> setText(recupcommand);
    }
}
