
#include <SPI.h>
#include <Mirf.h> 
#include <nRF24L01.h> 
#include <MirfHardwareSpiDriver.h> 

void setup() 
{
    Serial.begin(19200);
     
    
   
    /*** nRF24L01+ ***/
    Mirf.cePin = 8; // CE sur D8
    Mirf.csnPin = 7; // CSN sur D7
    Mirf.spi = &MirfHardwareSpi; // on utilise la surcouche de SPI 
    Mirf.init(); 
 
    Mirf.channel = 42; // canal 42 car c'est le bien (aucune raison) ...
    Mirf.payload = 2; // taille du message à transmettre (2 octects)
    Mirf.config(); 
     
    Mirf.setTADDR((byte *)"pcard"); // Le 1er module va envoyer ses info au 2eme module
    Mirf.setRADDR((byte *)"drone"); // On définit ici l'adresse du 1er module
   
}
 
void loop()
{   
    int cardispo = 0;
    int cmd = 0;
    char comp[3];
    int i = 0;

          while(i<8)
          {
            cardispo = Serial.available();
            if(Mirf.dataReady())
            { // On verifie si on a quelque chose de nouveau 
              Mirf.getData((byte *) &cmd); // on récupére ce que le l'arduino mini nous a envoyé (l'angle du servomoteur)
              Serial.println(cmd); 
            }
             if(cardispo > 0)
            {
              comp[i] = Serial.read();
              i++;
            }
          }
    long total = (comp[0]-48)*1000+(comp[1]-48)*100+(comp[2]-48)*10+(comp[3]-48); //Problème avec les caractères ASCII donc -48
    Mirf.send((byte *)&total); // On envoi la valeur de la position 
    while(Mirf.isSending()); // On boucle (attend) tant que le message n'as pas était envoyé 
    


   
    //fin du programme
}

