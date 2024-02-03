    #include <UART.h>


   // char counter;
    int etape;  //declaration de la variable etape qui servira a suivre les etapes du programme (debut de l'emission...) 

     void afficheChiffre(char chiffre,char position){
       //fonction afficheChiffre qui prend un chiffre à afficher et une position en paramètres. Elle configure les sorties LATD (PORTD en écriture) en fonction du chiffre et de la position (unitées, dizaines..) passés en paramètres.
      LATA = 0x01 << position;     //   les PINs de AN0 a AN3 sont des canaux analogiques????
      switch(chiffre){

       //chaque cas prends en compte le chiffre que l'on veut afficher et allume les segments correspondants
       case 0:LATD0_bit = 1;LATD1_bit = 1;LATD2_bit = 1;LATD3_bit = 1;
              LATD4_bit = 1;LATD5_bit = 1;LATD6_bit = 0;LATD7_bit = 0;
       break;
       case 1:LATD0_bit = 0;LATD1_bit = 1;LATD2_bit = 1;LATD3_bit = 0;
              LATD4_bit = 0;LATD5_bit = 0;LATD6_bit = 0;LATD7_bit = 0;
       break;

       case 2:LATD0_bit = 1;LATD1_bit = 1;LATD2_bit = 0;LATD3_bit = 1;
              LATD4_bit = 1;LATD5_bit = 0;LATD6_bit = 1;LATD7_bit = 0;
       break;
       case 3:LATD0_bit = 1;LATD1_bit = 1;LATD2_bit = 1;LATD3_bit = 1;
              LATD4_bit = 0;LATD5_bit = 0;LATD6_bit = 1;LATD7_bit = 0;
       break;
       case 4:LATD0_bit = 0;LATD1_bit = 1;LATD2_bit = 1;LATD3_bit = 0;
              LATD4_bit = 0;LATD5_bit = 1;LATD6_bit = 1;LATD7_bit = 0;
       break;
       case 5:LATD0_bit = 1;LATD1_bit = 0;LATD2_bit = 1;LATD3_bit = 1;
              LATD4_bit = 0;LATD5_bit = 1;LATD6_bit = 1;LATD7_bit = 0;
       break;
       case 6:LATD0_bit = 1;LATD1_bit = 0;LATD2_bit = 1;LATD3_bit = 1;
              LATD4_bit = 1;LATD5_bit = 1;LATD6_bit = 1;LATD7_bit = 0;
       break;
       case 7:LATD0_bit = 1;LATD1_bit = 1;LATD2_bit = 1;LATD3_bit = 0;
              LATD4_bit = 0;LATD5_bit = 0;LATD6_bit = 0;LATD7_bit = 0;
       break;
       case 8:LATD0_bit = 1;LATD1_bit = 1;LATD2_bit = 1;LATD3_bit = 1;
              LATD4_bit = 1;LATD5_bit = 1;LATD6_bit = 1;LATD7_bit = 0;
       break;
       case 9:LATD0_bit = 1;LATD1_bit = 1;LATD2_bit = 1;LATD3_bit = 1;
              LATD4_bit = 0;LATD5_bit = 1;LATD6_bit = 1;LATD7_bit = 0;
       break;
       case 10:LATD0_bit = 0;LATD1_bit = 0;LATD2_bit = 0;LATD3_bit = 0;
              LATD4_bit = 0;LATD5_bit = 0;LATD6_bit = 0;LATD7_bit = 1;
       break;
       default:
       break;
      }
     }



       void afficheNombre(float var){
              //fonction qui decompose le nombre en unites dizaines centaines et milliers puis qui fait en sorte d'afficher chaque chiffre au bon emplacement grace à la fonction affichechiffre
      char chiffre0,chiffre1,chiffre2,chiffre3;
      //recuperation du chiffre des milliers
      chiffre3 = var/1000;
      var -= chiffre3*1000;
      //recuperation du chiffre des centaines
      chiffre2 = var/100;
      var -= chiffre2*100;
      //recuperation du chiffre des dizaines
      chiffre1 = var/10;
      var -= chiffre1*10;
      //recuperation du chiffre des unités
      chiffre0 = (char)var;
      //recuperation du chiffre des milliers
      afficheChiffre(chiffre0,0);
      Delay_ms(1);
      //recuperation du chiffre des centaines
      afficheChiffre(chiffre1,1);
      Delay_ms(1);
      //recuperation du chiffre des dizaines
      afficheChiffre(chiffre2,2);
      Delay_ms(1);
      //recuperation du chiffre des unités
      afficheChiffre(chiffre3,3);
      Delay_ms(1);
     }


    void main(void) {
    //int timeout;
    int compte = 0;//initialisation à 0

      float nombreaffiche = 0;//initialisation  à 0
      ANSELB = 0x00;  ////   Configuration des broches du port B comme entrées/sorties numériques.
      TRISA = 0x00; //configuration du porta en sortie numérique
      TRISC = 0x01;
      TRISD = 0x00;//configuration du portd en sortie numérique

      LATA = 0x00;//on initialise le porta à 0
      LATC = 0x00;//on initialise le portc à 0
      LATD = 0x00;//on initialise le portd à 0
      etape = 0; //initialisation d'étape à 0
      TRISC6_bit = 0; // TX comme sortie
      TRISC7_bit = 1; // RX comme entrée

      UART1_Init(9600); // Initialiser l'UART à la vitesse de bauds de 9600 bps
      Delay_ms(100);    // Attendre un court instant pour la stabilité

      afficheNombre((int)nombreaffiche); //on affiche 0 au debut 
      while(1){ //boucle infinie qui permet au programme de continuellement basculer entre les etapes
        switch(etape) {  //chaque etape régit le comportement du programme

         case 0: // au début du programme 
         LATC1_bit = 1; //on met la broche c1 à l'état haut, on actionne donc l'ultrason
         compte = 0;
         etape++ ; //on passe à l'etape suivante au prochain tour de la boucle
         break;


         case 1: //apres activation
              Delay_ms(1); //on fait une pause d'une milliseconde
              LATC1_bit = 0; //on desactive l'emetteur
              etape++ ; 

              break;
         case 2: 

                 if(PORTC & 0x01){ //si le capteur d'écho est à l'état haut, donc on attends le retour des ondes
                    while(PORTC & 0x01){ //tant qu'on n'a pas capté le retour
                                compte++; // a chaque itération on incrémente compte
                                delay_us(10); //pause de 10ms pour la précision
                                }
                                etape++;//apres que les ondes soient revenues, on passe à l'étape suivante
                                 }
                                break;

         case 3:
          nombreaffiche = (float)compte*10/58.0;
          //ici, on cherche a convertir le temps mesuré en distance
          //on divise par 58 qui est la vitesse usuelle du son dans l'air
          // et on multiplie par 10 pour pallier au delais de raffraichissement qu'on a imposé avec delay

         Delay_ms(1);
         etape=0;
         break;

        }
        //si l'on a finit toutes les etapes et donc émit puis capté les ondes, ont affiche la distance
            if (etape == 3) {
                afficheNombre((int)nombreaffiche);

                // Envoi des données sur l'UART
                UART1_Write_Text("Distance : ");
                UART1_Write_Float(nombreaffiche);
                UART1_Write_Text(" cm\r\n");

                // atttendre un court instant pour éviter le surpeuplement du terminal
                Delay_ms(500);
            }
      }
    }