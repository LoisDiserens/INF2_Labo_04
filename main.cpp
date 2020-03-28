/*
 -----------------------------------------------------------------------------------
 Laboratoire : 04
 Fichier     : main.cpp
 Auteur(s)   : Nicolas Ogi
               Loïs Diserens
 Date        : 27.03.2020

 But         : <à compléter>

 Remarque(s) : <à compléter>

 Compilateur : MinGW-g++ 6.3.0
 -----------------------------------------------------------------------------------
 */

#include <cstdlib>
#include <iostream>
#include "fraction.h"

using namespace std;


int main() 
{
   Fraction<int> frac1(1,2);
   Fraction<int> frac2(1,2);
   
   cout << (frac1 == frac2) << endl;
   
   system("PAUSE");
   return EXIT_SUCCESS;
}
