/*
 -----------------------------------------------------------------------------------
 Laboratoire : 04
 Fichier     : fractionImpl.h
 Auteur(s)   : Nicolas Ogi
               Loïs Diserens
 Date        : 27.03.2020

 But         : A le rôle de fraction.cpp, mais délocaliser à cause de la généricité

 Remarque(s) : 

 Compilateur : MinGW-g++ 6.3.0
 -----------------------------------------------------------------------------------
 */
#ifndef FRACTIONIMPL_H
#define FRACTIONIMPL_H

#include "fraction.h"
#include <cmath>
#include <limits>
#include <type_traits>
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
Fraction<T> Fraction<T>::operator+(const Fraction<T>& fraction) const 
{  
   Fraction<T> fractionRes = *this;
   fractionRes += fraction;
   
   return fractionRes;
}

template<typename T>
Fraction<T>& Fraction<T>::operator+=(const Fraction<T>& fractionAdditionnee)
{ 
   //Simplifications préalables pour limiter les débordements
   Fraction<T> fractionSimplifiee1 = this->simplifier();
   Fraction<T> fractionSimplifiee2 = fractionAdditionnee.simplifier();
   
   // Exceptions numérateur
   if((fractionSimplifiee1.numerateur > 0 ) && (fractionSimplifiee2.numerateur 
       > numeric_limits<T>::max() - fractionSimplifiee1.numerateur))
   {
      throw overflow_error("Debordement du numerateur (overflow)");
   }
   else if ((fractionSimplifiee1.numerateur < 0 ) && (fractionSimplifiee2.numerateur 
             < numeric_limits<T>::lowest() - fractionSimplifiee1.numerateur))
   {
      throw underflow_error("Debordement du numerateur (underflow)");
   }   
   
   // Exceptions dénominateur
   if(fractionSimplifiee1.denominateur > (numeric_limits<T>::max() / fractionSimplifiee2.denominateur))
   {
      throw overflow_error("Debordement du denominateur (Overflow)");
   }
   
   //Pour trouver le dénominateur commun : den1 * den2 / pgdc(den1, den2)
   T denomFractionTemp = fractionSimplifiee1.denominateur * fractionSimplifiee2.denominateur / 
                         pgdc(fractionSimplifiee1.denominateur, fractionSimplifiee2.denominateur);
   
   //Pour trouver le numérateur : num1 * (denCommun / den1) + num2 * (denCommun / den2) 
   T numerFractionTemp = fractionSimplifiee1.numerateur * (denomFractionTemp / fractionSimplifiee1.denominateur) + 
                         fractionSimplifiee2.numerateur * (denomFractionTemp / fractionSimplifiee2.denominateur);
   
   // Affectation des résultats, puis simplification via un objet temporaire (contrainte due à la consigne concernant la fonction simplifier())
   Fraction<T> fractionTemp = Fraction<T> (numerFractionTemp, denomFractionTemp).simplifier();
   numerateur = fractionTemp.numerateur;
   denominateur = fractionTemp.denominateur;
   
   return *this; 
}

//A FAIRE : GERER LES DEBORDEMENTS AVEC TRY/CATCH
template<typename T>
Fraction<T> Fraction<T>::operator*(const Fraction<T>& fraction) const 
{   
   Fraction<T> fractionRes = *this;
   
   //Bloc try/catch à enlever car sera géré dans le main
//   try
//   {
//      
//   }
//   catch(const runtime_error& e)
//   {
//      cout << e.what() << endl;
//      throw;
//   }
   
   fractionRes *= fraction;
   
   return fractionRes;
}

template<typename T>
Fraction<T>& Fraction<T>::operator*=(const Fraction<T>& fraction) 
{
   
   //Simplifications préalables pour limiter les débordements
   Fraction<T> fractionSimplifiee1 = this->simplifier();
   Fraction<T> fractionSimplifiee2 = fraction.simplifier();
      
   // Numerateur
   if(fractionSimplifiee1.numerateur > (numeric_limits<T>::max() / fractionSimplifiee2.numerateur))
   {
      throw overflow_error("Debordement du numerateur (Overflow)");
   }
   else if (fractionSimplifiee1.numerateur < (numeric_limits<T>::lowest() / fractionSimplifiee2.numerateur))
   {
      throw underflow_error("Debordement du numerateur (Underverflow)");
   }
   // Denominateur
   if(fractionSimplifiee1.denominateur > (numeric_limits<T>::max() / fractionSimplifiee2.denominateur))
   {
      throw overflow_error("Debordement du denominateur (Overflow)");
   }
   
   
   // Affectation des résultats, puis simplification via un objet temporaire 
   // (contrainte due à la consigne concernant la fonction simplifier())
   Fraction<T> fractionRes(fractionSimplifiee1.numerateur * fractionSimplifiee2.numerateur, 
                           fractionSimplifiee1.denominateur * fractionSimplifiee2.denominateur);
   
   fractionRes = fractionRes.simplifier();
   
   numerateur = fractionRes.numerateur;
   denominateur = fractionRes.denominateur;
   
   return *this;
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
   
   //Valeur absolue pour pas faire changer de signe le numérateur ou le dénominateur
   return abs(a); 
}

#endif /* FRACTIONIMPL_H */

