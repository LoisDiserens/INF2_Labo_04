/*
 -----------------------------------------------------------------------------------
 Laboratoire : 04
 Fichier     : main.cpp
 Auteurs     : Nicolas Ogi, Loïs Diserens
 Date        : 27.03.2020

 But         : Ce fichier permet de tester la classe Fraction avec des fonctions de
               test dédiées aux fonctionnalités que propose la classe.

 Remarque(s) : Nous avons d'abord implémenter une méthode de calcul précise pour les
               sommes de fractions demandées mais le temps de calcul était très grand
               pour les long long. Ces fonctions se trouvent toujours dans ce fichier
               et leurs appels ont été mis en commentaire.
               
               - sommeDebordementPrecisMaisLong
               - sommeDebordement2PrecisMaisLong
 
               Nous avons donc créé deux autres fonctions de somme qui elles, sont
               conformes aux explications fournies et à ce qui était demandé mais
               sont cependant bien moins précises.

               - sommeDebordement
               - sommeDebordement2

 Compilateur : MinGW-g++ 6.3.0
 -----------------------------------------------------------------------------------
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "fraction.h"

using namespace std;

//Déclarations des fonctions de test

/**
 * Fonction de test permettant de tester le constructeur de la classe Fraction.
 * Elle capture les exceptions que lancerait le constructeur.
 * 
 * Retourne la fraction 0/1 dans le cas d'une erreur
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
 * Fonction permettant de faire la première somme de fraction qui approxime PI.
 * La précision par défaut est de 20 chiffres significatifs car le résultat est
 * donné en double
 */
template <typename T>
void sommeDebordementPrecisMaisLong(T numerateur, T denominateur, unsigned precision = 20);

/*
 * Fonction permettant de faire la deuxième somme de fraction qui approxime PI.
 * La précision par défaut est de 20 chiffres significatifs car le résultat est
 * donné en double
 */
template <typename T>
void sommeDebordement2PrecisMaisLong(T numerateur, T denominateur, unsigned precision = 20);

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

   Fraction<int> frac1 = creationFraction(2,3);
   Fraction<int> frac2 = creationFraction(4,6);
   testBonFonctionnement(frac1,frac2);
   
   //Création d'une fraction avec un dénominateur négatif
   Fraction<int> fracTest = creationFraction(2,-4);
   cout << fracTest << endl;
   
   Fraction<int> frac3 = creationFraction(-5,6);
   Fraction<int> frac4 = creationFraction(3,4);
   additionFraction(frac3, frac4);        
   multiplicationFraction(frac3, frac4);
   
   //Approximation de PI avec la première somme de fractions
   //INT : 0 décimales correctes
   cout << "\nCalcul de la somme jusqu'au debordement "
           "avec la premiere somme de fractions (INT) : " << endl;
   sommeDebordement(4, 1);
   
   // sommeDebordementPrecisMaisLong(4, 1);
   
   cout << "Calcul de la somme jusqu'au debordement (LONG LONG): " << endl;
   sommeDebordement((long long)4, (long long)1);
   
   //sommeDebordementPrecisMaisLong((long long)4, (long long)1);
   
   //Approximation de PI avec la deuxième somme de fractions
   // INT : 3 décimales correctes 3.141...
   cout << "Calcul de la somme jusqu'au debordement "
           "avec la deuxieme somme de fractions (INT) : " << endl;
   sommeDebordement2(4, 2);
   
   //sommeDebordement2PrecisMaisLong(4, 2);
   
   // LONG LONG : 3 décimales correctes 3.141...
   cout << "Calcul de la somme jusqu'au debordement "
           "avec la deuxieme somme de fractions (LONG LONG) : " << endl;
   sommeDebordement2((long long)4, (long long)2);
   
   //sommeDebordement2PrecisMaisLong((long long)4, (long long)2);
   
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
   
   cout << "\nEgalite numerique de fractions : " << endl;
   cout << frac1 << " et " << frac2 << " egales ?" << endl;
   cout << boolalpha << (frac1 == frac2) << endl;
   
   cout << "\nIdenticite de fractions : " << endl;
   cout << frac1 << " et " << frac2 << " identiques ?" << endl;
   cout << boolalpha << frac1.identite(frac2) << endl;
   
   cout << "\nSimplification de fraction : " << endl;
   cout << "Avant : " << frac1;
   frac1 = frac1.simplifier();
   cout << " Apres : " << frac1 << endl;
   cout << "Avant : " << frac2;
   frac2 = frac2.simplifier();
   cout << " Apres : " << frac2 << endl;
   
   cout << "\nValeur numerique des fractions en double et float :" << endl;
   cout << frac1 << " : " << (double)frac1 << " (double)" << endl;
   cout << frac2 << " : " << float(frac2) << " (float)" << endl << endl;
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

/* 
   Première méthode qui est beaucoup plus précise car parcourt tout le type de dénom,
   de deux en deux, en sommant le résultat du calcul dans un double. Mais demande un 
   temps de calcul gigantesque en comparaison.
 
   Pour Int:
   8 décimales correctes 3.14159265...
   
   Pour Long Long:
   Tourne pendant des heures sans créer de dépassement. Plus précisemment,
   il va y avoir dépassement mais le temps de calcul est gigantesque. 
   Nous l'avons laissé tourner une nuit entière, mais le programme tournait toujours.
   Mais lorsqu'il arrive au débordement, il y a bel et bien une exception levée, 
   nous avons fait le test en entrant manuellement numerci_limits<long long> comme
   première valeur au denominateur. La fonction entrait dans la boucle une fois, puis
   après incrémentation, comme attendu, une exception de débordement fut levée.
 */
template <typename T>
void sommeDebordementPrecisMaisLong(T numerateur, T denominateur, unsigned precision)
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
      }
   } 
   catch (const exception& e) 
   {
      cout << "Nombre de termes additionnes : " << nbIterations << ", la fraction finale : " 
           << Fraction<T>(numerateur * -1, denominateur - 2) << endl
           << setprecision(precision) << "La valeur de la serie, avec une precision(" 
           << precision <<  ") : " << somme << endl
           << "La somme s'est arretee pour la cause suivante : " << e.what() << endl << endl;
   }
}

/* 
   Première méthode qui est beaucoup plus précise car parcourt tout le type de dénom,
   de deux en deux, en sommant le résultat du calcul dans un double. Mais demande un 
   temps de calcul gigantesque en comparaison.
 
   Pour Int:
   8 décimales correctes 3.14159265...
   
   Pour Long Long:
   13 décimales correctes 3.1415926535897...
 */
template <typename T>
void sommeDebordement2PrecisMaisLong(T numerateur, T denominateur, unsigned precision)
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
      }
   } 
   catch (const exception& e) 
   {
      cout << "Nombre de termes additionnes : " << nbIterations << ", la fraction finale : " 
           << Fraction<T>(numerateur * -1, (i - 2) * (j - 2) * (k - 2)) << endl
           << setprecision(precision) << "La valeur de la serie, avec une precision(" 
           << precision <<  ") : " << somme << endl
           << "La somme s'est arretee pour la cause suivante : " << e.what() << endl << endl;
   }
}

template <typename T>
void sommeDebordement(T numerateur, T denominateur, unsigned precision)
{  
   unsigned nbIterations = 1;
   Fraction<T> fracSomme(numerateur,denominateur);
   
   try
   {  
      while(true) 
      {
         // Modifications des valeurs de la fraction
         numerateur *= -1;
         denominateur += 2;
         
         fracSomme += Fraction<T>(numerateur, denominateur);
         
         nbIterations++;
      }
   } 
   catch (const exception& e) 
   {
      cout << "Nombre de termes additionnes : " << nbIterations << ", la fraction finale : " 
           << fracSomme << endl
           << setprecision(precision) << "La valeur de la serie, avec une precision(" 
           << precision <<  ") : " << (double)fracSomme << endl
           << "La somme s'est arretee pour la cause suivante : " << e.what() << endl <<endl;
   }
}

template <typename T>
void sommeDebordement2(T numerateur, T denominateur, unsigned precision)
{  
   unsigned nbIterations = 1;
   T i = denominateur, j, k;
   Fraction<T> fracSomme((T)3,(T)1);
   
   try
   {  
      while(true) 
      {
         j = i + 1;
         k = j + 1;
         fracSomme += Fraction<T>(numerateur, i * j * k);
         
         // Modifications des valeurs de la fraction de la prochaine itération
         numerateur *= -1;
         i = k;
         
         nbIterations++;
      }
   } 
   catch (const exception& e) 
   {
      cout << "Nombre de termes additionnes : " << nbIterations << ", la fraction finale : " 
           << fracSomme << endl
           << setprecision(precision) << "La valeur de la serie, avec une precision(" 
           << precision <<  ") : " << (double)fracSomme << endl
           << "La somme s'est arretee pour la cause suivante : " << e.what() << endl << endl;
   }
}