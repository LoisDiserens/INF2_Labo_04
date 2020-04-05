/*
 -----------------------------------------------------------------------------------
 Laboratoire : 04
 Fichier     : main.cpp
 Auteurs   : Nicolas Ogi, Loïs Diserens
 Date        : 27.03.2020

 But         : Ce fichier permet de tester la classe Fraction avec des fonctions de
               test dédiées aux fonctionnalités que propose la classe.

 Remarque(s) : La première somme de fractions avec le type long long est en commentaire
               car elle tourne pendant des heures et nous n'avons pas pu obtenir de
               résultats.

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

/**
 * Fonction de test permettant de tester le constructeur de la classe Fraction.
 * Elle capture les exceptions que lancerait le constructeur.
 */
template <typename T>
Fraction<T> creationFraction(T numerateur, T denominateur);

/*
 * Fonction de test permettant de tester les fonctionnalités suivantes de la classe :
 *  - L'affichage de fraction
 *  - La simplification de fraction
 *  - Egalité numérique entre fractions
 *  - Identicité de deux fractions
 *  - Transformation de fraction en valeur numérique (double et float) via 
 *    l'opérateur de cast
 */
template <typename T>
void testBonFonctionnement(Fraction<T>& frac1, Fraction<T>& frac2);

/*
 * Fonction permettant de faire la première somme de fraction qui approxime PI.
 * La précision par défaut est de 20 chiffres significatifs car le résultat est
 * donné en double
 */
template <typename T>
void sommeDebordement(T numerateur, T denominateur, unsigned precision = 20);

/*
 * Fonction permettant de faire la deuxième somme de fraction qui approxime PI.
 * La précision par défaut est de 20 chiffres significatifs car le résultat est
 * donné en double
 */
template <typename T>
void sommeDebordement2(T numerateur, T denominateur, unsigned precision = 20);

/*
 * Fonction de test permettant de tester l'addition entre des fractions. Elle capture
 * les exceptions que lancerait l'opérateur d'addition
 */
template <typename T>
void additionFraction(Fraction<T>& lhs, Fraction<T>& rhs);

/*
 * Fonction de test permettant de tester la multiplication entre des fractions. 
 * Elle capture les exceptions que lancerait l'opérateur de multiplication
 */
template <typename T>
void multiplicationFraction(Fraction<T>& lhs, Fraction<T>& rhs);


int main() 
{
   Fraction<int> frac1 = creationFraction(-10,4);
   Fraction<int> frac2 = creationFraction(3,4);
   testBonFonctionnement(frac1,frac2);
   
   //Création d'une fraction avec un dénominateur négatif
   Fraction<int> fracTest = creationFraction(2,-4);
   cout << fracTest << endl;
   
   Fraction<int> frac3 = creationFraction(-5,6);
   Fraction<int> frac4 = creationFraction(3,4);
   additionFraction(frac3, frac4);        
   multiplicationFraction(frac3, frac4);
   
   // Approximation de PI avec la première somme de fractions
   //INT : 8 décimales correctes (3.14159265....)
   cout << "\nCalcul de la somme jusqu'au debordement "
           "avec la premiere somme de fractions (INT) : " << endl;
   sommeDebordement(4, 1);
   
   // Tourne pendant des heures sans créer de dépassement
   /*cout << "Calcul de la somme jusqu'au debordement (LONG LONG): " << endl;
   sommeDebordement((long long)4, (long long)1);*/
   
   // INT : 8 décimales correctes 3.14159265...
   cout << "\nCalcul de la somme jusqu'au debordement "
           "avec la deuxieme somme de fractions (INT) : " << endl;
   sommeDebordement2(4, 2);
   
   // LONG LONG : 13 décimales correctes 3.1415926535897...
   cout << "\nCalcul de la somme jusqu'au debordement "
           "avec la deuxieme somme de fractions (LONG LONG) : " << endl;
   sommeDebordement2((long long)4, (long long)2);
   
   system("PAUSE");
   return EXIT_SUCCESS;
}

template <typename T>
Fraction<T> creationFraction(T numerateur, T denominateur)
{
   try
   {
      return Fraction<int>(numerateur,denominateur);
   }
   catch(const exception& e)
   {
      cout << "Une erreur est survenue a la creation de fraction: " << e.what() << endl;
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
   cout << "Avant : " << frac2;
   frac2 = frac2.simplifier();
   cout << " Apres : " << frac2 << endl;
   
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
      cout << "Une erreur est survenue : " << e.what() << endl;
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
      cout << "Une erreur est survenue : " << e.what() << endl;
   }
}


template <typename T>
void sommeDebordement(T numerateur, T denominateur, unsigned precision)
{  
   double somme = 0.;
   unsigned nbIterations = 0;
   
   try
   {  
      while(true) 
      {
         somme += (double)Fraction<T>(numerateur, denominateur);
         
         // Modifications des valeurs de la fraction de la prochaine itération
         numerateur *= -1;
         denominateur += 2;
         
         nbIterations++;
         //cout << setprecision(precision) << somme << endl;
      }
   } 
   catch (const exception& e) 
   {
      cout << "Nombre de termes : " << nbIterations << ", la fraction finale : " 
           << Fraction<T>(numerateur * -1, denominateur - 2) << endl
           << setprecision(precision) << "La valeur de la serie, avec une precision(" 
           << precision <<  ") : " << somme << endl
           << "La somme s'est arretee pour la cause suivante : " << e.what() << endl;
   }
}

template <typename T>
void sommeDebordement2(T numerateur, T denominateur, unsigned precision)
{  
   double somme = 3.;
   unsigned nbIterations = 0;
   T i = denominateur, j, k;
   
   try
   {  
      while(true) 
      {
         j = i + 1;
         k = j + 1;
         somme += (double)Fraction<T>(numerateur, i * j * k);
         
         // Modifications des valeurs de la fraction de la prochaine itération
         numerateur *= -1;
         i = k;
         
         nbIterations++;
         //cout << setprecision(precision) << somme << endl;
      }
   } 
   catch (const exception& e) 
   {
      cout << "Nombre de termes : " << nbIterations << ", la fraction finale : " 
           << Fraction<T>(numerateur * -1, (i - 2) * (j - 2) * (k - 2)) << endl
           << setprecision(precision) << "La valeur de la serie, avec une precision(" 
           << precision <<  ") : " << somme << endl
           << "La somme s'est arretee pour la cause suivante : " << e.what() << endl;
   }
}


   