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
#include <iomanip>
#include <stdexcept>
#include "fraction.h"

using namespace std;

// Déclaration des fonctions de test
template <typename T>
Fraction<T> creationFraction(T numerateur, T denominateur);
template <typename T>
void testBonFonctionnement(Fraction<T>& frac1, Fraction<T>& frac2);
template <typename T>
void additionFraction(Fraction<T>& lhs, Fraction<T>& rhs);
template <typename T>
void multiplicationFraction(Fraction<T>& lhs, Fraction<T>& rhs);


int main() 
{
   Fraction<int> frac1(-10,4);
   Fraction<int> frac2(3,4);
   
   testBonFonctionnement(frac1,frac2);
//   cout << "Affichage des fractions : " << endl;
//   cout << frac1 << " " << frac2 << endl;
//   
//   cout << "\nSimplification de fraction : " << endl;
//   cout << "Avant : " << frac1;
//   frac1 = frac1.simplifier();
//   cout << " Apres : " << frac1 << endl;
//   
//   cout << "\nEgalite numerique de fractions : " << endl;
//   cout << frac1 << " et " << frac2 << " egales ?" << endl;
//   cout << boolalpha << (frac1 == frac2) << endl;
//   
//   cout << "\nIdenticite de fractions : " << endl;
//   cout << frac1 << " et " << frac2 << " identiques ?" << endl;
//   cout << boolalpha << frac1.identite(frac2) << endl;
//   
//   cout << "\nValeur numerique des fractions en double et float :" << endl;
//   cout << frac1 << " : " << (double)frac1 << " (double)" << endl;
//   cout << frac2 << " : " << float(frac2) << " (float)" << endl;
   
   Fraction<int> fracT = creationFraction(2,-4);
   cout << fracT<< endl;
   
   Fraction<int> frac3(-5,6);
   Fraction<int> frac4(3,4);
   additionFraction(frac3, frac4);        
   multiplicationFraction(frac3, frac4);
   
   Fraction<int> frac5(2,2);
   Fraction<int> frac6(3,4);
   additionFraction(frac5, frac6);
   
   double somme = 0;
   
//   try{
//         int signe = 1;
//         int j = 1;
//         
//         while(true) {
//            double frac = (double)Fraction<int>(signe * 4, j);
//            somme += frac;
//            signe *= -1;
//            j += 2;
//         }
//   } catch (exception& e) {
//      cout << setprecision(15) << somme << endl;
//   }
   
   
   
   
   system("PAUSE");
   return EXIT_SUCCESS;
}

template <typename T>
Fraction<T> creationFraction(T numerateur, T denominateur)
{
   cout << "\nCreation de fraction : " << endl;
   try
   {
      return Fraction<int>(numerateur,denominateur);
   }
   catch(const exception& e)
   {
      cout << "Une erreur est survenue: " << e.what() << endl;
   }
   
   // Dans le cas où une erreur à la création survient, retourne une fraction égale à 0
   return Fraction<int>(0,1);
}

template <typename T>
void testBonFonctionnement(Fraction<T>& frac1, Fraction<T>& frac2)
{
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
}

template <typename T>
void additionFraction(Fraction<T>& lhs, Fraction<T>& rhs)
{
   cout << "\nAddition de fractions : " << endl;
   try
   {
      cout << lhs << " + " << rhs << " = " << lhs + rhs << endl;
      cout << lhs << " += " << rhs << " = ";
      lhs += rhs;
      cout << lhs << endl;
   }
   catch(const exception& e)
   {
      cout << "Une erreur est survenue: " << e.what() << endl;
   }
}

template <typename T>
void multiplicationFraction(Fraction<T>& lhs, Fraction<T>& rhs)
{
   cout << "\nMultiplication de fractions : " << endl;
   try
   {
      cout << lhs << " * " << rhs << " = " << lhs * rhs << endl;
      cout << lhs << " *= " << rhs << " = ";
      lhs *= rhs;
      cout << lhs << endl;
   }
   catch(const exception& e)
   {
      cout << "Une erreur est survenue: " << e.what() << endl;
   }
}
   
   