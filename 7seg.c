#include "Afficheur_7seg.h"  //import du header contenant la fonction mask  

//declaration des variables
unsigned short shifter, portd_index;
unsigned int digit, number;
unsigned short portd_array[4];

 //definition de la fonction interrupt pour ce programme, qui spÃ©cifie le code Ã  executer lorsque le pic rencontre une interruption 
void interrupt() {
LATA = 0; //toutes les sorties du portA Ã  0
LATD = portd_array[portd_index]; //chargement du chiffre Ã  mettre dans la partie concernÃ©e de l'afficheur 
LATA = shifter;  //on charge la valeur de shifter dans le registre, afin de selectionner la partie dans laquelle afficher le chiffre

// move shifter to next digit

shifter <<=1;  //decalage des bits de shifter vers la gauche    
if (shifter >8u)  //si shifter depasse 8 (fin du nombre actuel), il est rÃ©initialisÃ© a 1
shifter = 1;

// increment portd_index
portd_index++; //on incremente la valeur de portindex
if(portd_index > 3u)  //si portindex depasse 3(limite du tableau et donc fin du nombre actuel)
portd_index = 0; //il est reinitialisÃ© Ã  0
TMR0L = 0; //on rÃ©initialise une nouvelle fois le registre bas de TMR0 Ã  0
TMR0IF_bit = 0;  //on efface le drapeau d'interruption de TMR0, synonyme de fin du traitement de l'interruption
}

void main() {
ANSELA = 0; //desactivation de la conversion analogique-numerique du portA
ANSELD = 0;//desactivation de la conversion analogique-numerique du portD
TRISA = 0;//definition du port A en sortie numÃ©rique
LATA = 0; //on charge la valeur 0 dans le portA
TRISD = 0;//definition du port D en sortie numÃ©rique
LATD = 0; //on charge la valeur 0 dans le portD
T0CON = 0xC4; //initialisation du registre de controle du temporisateur TMR0 Ã  0xc4
TMR0L = 0; //initialisation du registre bas de TMR0 Ã  0, qui est la valeur Ã  laquelle le compteur commence 

//initialisation des variables
digit = 0;
portd_index = 0;
shifter = 1;
//number = 0000;
number = 00;
GIE_bit = 1; //activation des interrutions globales 
TMR0IE_bit = 1;  //activaion des interruptions liÃ©es au temportisateur TMRO


do { //boucle principale (infinie) du programme

digit = number / 1000u; //digit reÃ§oit la valeur de la partie millier du nombre actuel
portd_array[3] = mask(digit); //la valeur en hex des segments Ã  afficher pour le chiffre stockÃ© dans digit est assignÃ©e au dernier element du tableau

digit = (number / 100u) % 10u;  //digit reÃ§oit la valeur de la partie centaine du nombre actuel
portd_array[2] = mask(digit);   //la valeur en hex des segments Ã  afficher pour le chiffre stockÃ© dans digit est assignÃ©e au troisieme element du tableau

digit = (number / 10u) % 10u;  //digit reÃ§oit la valeur de la partie dizaine du nombre actuel
portd_array[1] = mask(digit);  //la valeur en hex des segments Ã  afficher pour le chiffre stockÃ© dans digit est assignÃ©e au deuxieme element du tableau

digit = number % 10u;   //digit reÃ§oit la valeur de la partie unitÃ© du nombre actuel
portd_array[0] = mask(digit); //la valeur en hex des segments Ã  afficher pour le chiffre stockÃ© dans digit est assignÃ©e au premier element du tableau

Delay_ms(1000); //temporisation d'une seconde 
number++; //on incremente la valeur du nombre Ã  afficher


if (number > 9999u) // si la valeur du nombre atteinds la limite possible (9999)
number = 0; //on recommence Ã  0
} while(1);

}