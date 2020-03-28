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
#include <stdexcept>

using namespace std;

//////////////// FONCTIONS  PUBLIQUES ////////////////
template <typename T>
Fraction<T>::Fraction(T initNumerateur, T initDenominateur)
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

template <typename T>
Fraction<T> Fraction<T>::simplifier() const
{
   T divCommun = pgdc(numerateur, denominateur);
   
   return Fraction(numerateur / divCommun, denominateur / divCommun);
}

template <typename T>
bool Fraction<T>::identite(const Fraction<T>& fractionCible) const
{
   return numerateur == fractionCible.numerateur && denominateur == fractionCible.denominateur;
}

template<typename T>
bool Fraction<T>::operator==(const Fraction<T>& rhs) const
{
   return (double)*this == (double)rhs;
}

//A FAIRE : GERER LES DEBORDEMENTS AVEC TRY/CATCH
template<typename T>
Fraction<T> Fraction<T>::operator +(const Fraction<T>& fraction) const { 
   
   //Copie de this et de la fraction passée en paramètre car on ne veut pas modifier
   //les fractions originales et pour ne pas modifier la surcharge de l'opérateur +
   // en passant par copie et en enlevant le const à la fin par exemple
   
   //Simplifications préalables pour limiter les débordements
   Fraction<T> fractionSimplifiee1 = this->simplifier();
   Fraction<T> fractionSimplifiee2 = fraction.simplifier();
   
   //Pour trouver le dénominateur commun : den1 * den2 / pgdc(den1, den2)
   T denomFractionRes = fractionSimplifiee1.denominateur * fractionSimplifiee2.denominateur / 
                        pgdc(fractionSimplifiee1.denominateur, fractionSimplifiee2.denominateur);
   
   //Pour trouver le numérateur : num1 * (denCommun / den1) + num2 * (denCommun / den2) 
   T numerFractionRes = fractionSimplifiee1.numerateur * (denomFractionRes / fractionSimplifiee1.denominateur) + 
                        fractionSimplifiee2.numerateur * (denomFractionRes / fractionSimplifiee2.denominateur);
   
   Fraction<T> fractionRes(numerFractionRes, denomFractionRes);
   
   //Retourne une version simplifiée
   return fractionRes.simplifier(); 
}

//A FAIRE : GERER LES DEBORDEMENTS AVEC TRY/CATCH
template<typename T>
Fraction<T> Fraction<T>::operator *(const Fraction<T>& fraction) const {
   
   //Même chose que pour l'opérateur + concernant la copie
   
   //Simplifications préalables pour limiter les débordements
   Fraction<T> fractionSimplifiee1 = this->simplifier();
   Fraction<T> fractionSimplifiee2 = fraction.simplifier();
   
   Fraction<T> fractionRes(fractionSimplifiee1.numerateur * fractionSimplifiee2.numerateur, 
                           fractionSimplifiee1.denominateur * fractionSimplifiee2.denominateur);
   
   return fractionRes.simplifier();
}


//////////////// FONCTIONS  PRIVEES ////////////////
template<typename T>
T Fraction<T>::pgdc(T a, T b) const
{
   T tmp;
   
   while (b != 0) 
   {
     tmp = b;
     b = a % b;
     a = tmp;
   }
   
   return abs(a); //Valeur absolue pour pas faire changer de signe le numérateur
}

#endif /* FRACTIONIMPL_H */

