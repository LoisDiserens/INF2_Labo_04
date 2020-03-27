/*
 -----------------------------------------------------------------------------------
 Laboratoire : 04
 Fichier     : fractionImpl.h
 Auteur(s)   : Nicolas Ogi
               Loïs Diserens
 Date        : 27.03.2020

 But         : A le rôle de fraction.cpp, mais délocaliser à cause de la généricité

 Remarque(s) : -

 Compilateur : MinGW-g++ 6.3.0
 -----------------------------------------------------------------------------------
 */
#ifndef FRACTIONIMPL_H
#define FRACTIONIMPL_H

#include "fraction.h"
#include <cmath>

using namespace std;

template <typename T>
Fraction::Fraction(T initNumerateur, T initDenominateur)
{
   // Exceptions
   if(initDenominateur == 0)
   {
      throw invalid_argument("Division par zero");
   }
   else if(initDenominateur < 0)
   {
      throw invalid_argument("Nombre negatif au denominateur");
   }
   
   // Affectation des variables
   numerateur = initNumerateur;
   denominateur = initDenominateur;
}

template<typename T>
T Fraction<T>::pgdc(T a, T b){
   T tmp;
   while (b != 0) {
     tmp = b;
     b = a % b;
     a = tmp;
   }
   return abs(a); //Valeur absolue pour pas faire changer de signe le numérateur
}

Fraction<T> Fraction<T>::simplifier(Fraction<T>& fraction) {
   T pgdc = pgdc(fraction.numerateur, fraction.denominateur);
   return Fraction(fraction.numerateur / pgdc, fraction.denominateur / pgdc);
}


#endif /* FRACTIONIMPL_H */

