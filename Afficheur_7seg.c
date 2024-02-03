unsigned short mask(unsigned short num){    //fonction qui prend en parametre un unsigned
//la fonction masque dÃ©finit le code hex nÃ©cessaire Ã  l'allumage des segments reprÃ©sentant le code du chiffre passÃ© en parametres
         switch(num){
         case 0 : return 0x3F; //la valeur nen hexadecimal pour allumer les segments correpondants Ã  0
         case 1 : return 0x06;   //la valeur nen hexadecimal pour allumer les segments correpondants Ã  1
         case 2 : return 0x5B;     //la valeur nen hexadecimal pour allumer les segments correpondants Ã  2
         case 3 : return 0x4F;     //la valeur nen hexadecimal pour allumer les segments correpondants Ã  3
         case 4 : return 0x66;      //la valeur nen hexadecimal pour allumer les segments correpondants Ã  4
         case 5 : return 0x6D;       //la valeur nen hexadecimal pour allumer les segments correpondants Ã  5
         case 6 : return 0x7D;       //la valeur nen hexadecimal pour allumer les segments correpondants Ã  6
         case 7 : return 0x07;        //la valeur nen hexadecimal pour allumer les segments correpondants Ã  7
         case 8 : return 0x7F;       //la valeur nen hexadecimal pour allumer les segments correpondants Ã  8
         case 9 : return 0x6f;        //la valeur nen hexadecimal pour allumer les segments correpondants Ã  9
         }}