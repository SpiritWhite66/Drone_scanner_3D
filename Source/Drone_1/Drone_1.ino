#include <Servo.h>
#include <SPI.h> 
#include <Mirf.h> 
#include <nRF24L01.h> 
#include <MirfHardwareSpiDriver.h> 
 
Servo monServo;
int pos=0;
const int locker = 12;
const int clock = 10;
const int data = 11;
int binled = 0b00001111;
int comget = 0; // stock la commande reçu

void setup()
{
    monServo.attach(2, 1000, 2000); // moteur
    pinMode(locker, OUTPUT); // pin configuré en sortie pour le 74HC595
    pinMode(clock, OUTPUT);
    pinMode(data, OUTPUT);
    
    Serial.begin(9600);
   
    /*** nRF24L01+ ***/
    Mirf.cePin = 8; // CE sur D8
    Mirf.csnPin = 7; // CSN sur D7
    Mirf.spi = &MirfHardwareSpi; // on utilise la surcouche de SPI 
    Mirf.init(); 
 
    Mirf.channel = 42; // canal 42 car c'est le bien (aucune raison) ...
    Mirf.payload = 2; // taille du message à transmettre (2 octects)
    Mirf.config(); 
     
    Mirf.setTADDR((byte *)"drone"); // Le 1er module va envoyer ses info au 2eme module
    Mirf.setRADDR((byte *)"pcard"); // On définit ici l'adresse du 1er module
   
}
 
void loop()
{
  digitalWrite(locker, LOW);
  binled = change_led(data, clock, true, 1, binled); // on allume la led de fonctionnement
  digitalWrite(locker, HIGH);
        
  if(pos == 0)
  {
      for(pos = 0; pos<91;pos++)
      {
        monServo.write(pos);
        send_data(pos);
        
        if(Mirf.dataReady()){ // On verifie si on a quelque chose de nouveau 
            Mirf.getData((byte *) &comget);
            digitalWrite(locker, LOW); // on allume la led de reception
            binled = change_led(data, clock, true, 3, binled); // on envoie la nouvelle commande 
            digitalWrite(locker, HIGH); 
        }
        
        delay(10);
        
        digitalWrite(locker, LOW); // on éteint les led de reception et d'envoie
        binled = change_led(data, clock, false, 3, binled); // on envoie la nouvelle commande 
        digitalWrite(locker, HIGH); 
        digitalWrite(locker, LOW); // on met le cadenas de la 74HC595 sur 0 pour modifier les led allumé
        binled = change_led(data, clock, false, 2, binled); // on envoie la nouvelle commande 
        digitalWrite(locker, HIGH); // on rebloque
      }

  }
  else
  {
   for(pos = 90; pos>=0;pos--)
      {
        monServo.write(pos);
        send_data(pos);
        
        if(Mirf.dataReady()){ // On verifie si on a quelque chose de nouveau 
            Mirf.getData((byte *) &comget);
            digitalWrite(locker, LOW); // on allume la led de reception
            binled = change_led(data, clock, true, 3, binled); // on envoie la nouvelle commande 
            digitalWrite(locker, HIGH); 
        }
        
        delay(10);
        
        digitalWrite(locker, LOW); // on éteint les led de reception et d'envoie
        binled = change_led(data, clock, false, 3, binled); // on envoie la nouvelle commande 
        digitalWrite(locker, HIGH); 
        digitalWrite(locker, LOW); // on met le cadenas de la 74HC595 sur 0 pour modifier les led allumé
        binled = change_led(data, clock, false, 2, binled); // on envoie la nouvelle commande 
        digitalWrite(locker, HIGH); // on rebloque
      }
      pos=0;
  }
  
}

void send_data(int pos)
{
  Mirf.send((byte *)&pos); // On envoi la valeur de la position 
  while(Mirf.isSending()); // On boucle (attend) tant que le message n'as pas était envoyé
  digitalWrite(locker, LOW); // on met le cadenas de la 74GC595 sur 0 pour modifier les led allumé
  binled = change_led(data, clock, true, 2, binled); // on envoie la nouvelle commande 
  digitalWrite(locker, HIGH); // on rebloque
}
int selected(int cmd) // pour le moment c'est vide
{
  switch (cmd)
  {
     case 0001: 
       
       break;
     case 0010:
       
       break;
     case 0011:
       
       break;
     case 0100:
       
       break;
     case 0101:
       
       break;
     case 0110:
      
       break;
     case 0111:
      
       break;
     case 1000:
      
       break;

  }
}
int change_led(int dataPin, int clockPin, boolean ope, char data, int data_comp) // gestion des led et du laser
{
  
  /*** operateur utilisé : OR pour l'addition et NAND pour soustraction (principe d'un masque) ***/
  if(data == 1) // led fonctionnement
  {
    if(ope == true)
    {
    data_comp = data_comp | 0b00000010;
    }
    if(ope == false)
    {
    data_comp = data_comp & ~0b00000010;
    }
  }
  if(data == 2) // Led envoie
  {
    if(ope==true)
    {
      data_comp = data_comp | ~0b00000100;
    }
    if(ope==false)
    {
      data_comp = data_comp & ~0b00000100;
    }
      
  }
  if(data == 3) // Led reception
  {
    if(ope==true)
    {
      data_comp = data_comp | 0b00001000;
    }
    if(ope==false)
    {
      data_comp = data_comp & 0b00001000;
    }
  }
  if(data == 4) // Led moteur
  {
    if(ope==true)
    {
      data_comp = data_comp | 0b00010000;
    }
    if(ope==false)
    {
      data_comp = data_comp & 0b00010000;
    }
  }
  if(data == 5) // Laser
  {
    if(ope==true)
    {
      data_comp = data_comp | 0b01000000;
    }
    if(ope==false)
    {
      data_comp = data_comp & 0b01000000;
    }
  }
   //octet inversée avec '~' pour piloter les LED à l'état bas (arduino n'aime pas donné du courant ^^)
   shiftOut(dataPin, clockPin, LSBFIRST, ~data_comp );
   return data_comp;
}
