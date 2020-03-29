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
   Fraction<int> frac1(-10,4);
   Fraction<int> frac2(3,4);
   
   cout << "Affichage des fractions : " << endl;
   cout << frac1 << " " << frac2 << endl;
   
   cout << "\nSimplification de fraction : " << endl;
   cout << "Avant : " << frac1;
   frac1 = frac1.simplifier();
   cout << " Apres : " << frac1 << endl;
   
   cout << "\nEgalite numerique de fractions : " << endl;
   cout << frac1 << " et " << frac2 << " egales ?" << endl;
   cout << boolalpha << (frac1 == frac2) << endl;
   
   cout << "\nIdenticite de fractions : " << endl;
   cout << frac1 << " et " << frac2 << " identiques ?" << endl;
   cout << boolalpha << frac1.identite(frac2) << endl;
   
   cout << "\nValeur numerique des fractions en double et float :" << endl;
   cout << frac1 << " : " << (double)frac1 << " (double)" << endl;
   cout << frac2 << " : " << float(frac2) << " (float)" << endl;
   
   Fraction<int> frac3(-5,6);
   Fraction<int> frac4(3,4);
   
   cout << "\nAddition de fractions : " << endl;
   cout << frac3 << " + " << frac4 << " = " << frac3 + frac4 << endl;
   
   cout << "\nMultiplication de fractions : " << endl;
   cout << frac3 << " * " << frac4 << " = " << frac3 * frac4 << endl;
   
   Fraction<int> frac5(numeric_limits<int>::max(),6);
   Fraction<int> frac6(3,4);
   cout << "---------------------------------" << endl;
   cout << frac5 << " + " << frac6 << " = " << frac5 + frac6 << endl;
   
   system("PAUSE");
   return EXIT_SUCCESS;
}
