/*
 -----------------------------------------------------------------------------------
 Laboratoire : 04
 Fichier     : fractionImpl.h
 Auteur(s)   : Nicolas Ogi
               Loïs Diserens
 Date        : 27.03.2020

 But         : A le rôle de fraction.cpp, mais délocaliser à cause de la généricité

 Remarque(s) : Indiquations sur les méthodes de détection d'overflow, suivant le cours
               d'INF 1, ainsi que sur : http://www.cplusplus.com/articles/DE18T05o/

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
//   //Copie de this et de la fraction passée en paramètre car on ne veut pas modifier
//   //les fractions originales et pour ne pas modifier la surcharge de l'opérateur +
//   // en passant par copie et en enlevant le const à la fin par exemple
//   
//   //Simplifications préalables pour limiter les débordements
//   Fraction<T> fractionSimplifiee1 = simplifier();
//   Fraction<T> fractionSimplifiee2 = fraction.simplifier();
//   
//   //Pour trouver le dénominateur commun : den1 * den2 / pgdc(den1, den2)
//   T denomFractionRes = fractionSimplifiee1.denominateur * fractionSimplifiee2.denominateur / 
//                        pgdc(fractionSimplifiee1.denominateur, fractionSimplifiee2.denominateur);
//   
//   //Pour trouver le numérateur : num1 * (denCommun / den1) + num2 * (denCommun / den2) 
//   T numerFractionRes = fractionSimplifiee1.numerateur * (denomFractionRes / fractionSimplifiee1.denominateur) + 
//                        fractionSimplifiee2.numerateur * (denomFractionRes / fractionSimplifiee2.denominateur);
//   
//   Fraction<T> fractionRes(numerFractionRes, denomFractionRes);
//   
//   //Retourne une version simplifiée
//   return fractionRes.simplifier(); 
   
   
   Fraction<T> fractionRes = *this;
   fractionRes += fraction;
   
   return fractionRes;
}

template<typename T>
Fraction<T>& Fraction<T>::operator+=(const Fraction<T>& fractionAdditonner)
{ 
   //Simplifications préalables pour limiter les débordements
   Fraction<T> fractionSimplifiee1 = this->simplifier();
   Fraction<T> fractionSimplifiee2 = fractionAdditonner.simplifier();
   
   // Detection d'un débordement, avant le calcul
   // Cas d'overflow (voir source dans l'en-tête de fichier): a+b-R<a and a+b-R<b
//   if(is_signed<T>)
//   {
//      if(((fractionSimplifiee1.numerateur > 0 && fractionSimplifiee2.numerateur > 0) && fractionSimplifiee1.numerateur + fractionSimplifiee2.numerateur < 0)
//         or
//         ((fractionSimplifiee1.numerateur < 0 or fractionSimplifiee2.numerateur< 0) && fractionSimplifiee1.numerateur + fractionSimplifiee2.numerateur < 0))
//      {
//         
//      }
//   }
//   else 
//   {
//      if((fractionSimplifiee1.numerateur + fractionSimplifiee2.numerateur - numeric_limits<T>::max() < fractionSimplifiee1.numerateur) 
//      && 
//      (fractionSimplifiee1.numerateur + fractionSimplifiee2.numerateur - numeric_limits<T>::max() < fractionSimplifiee2.numerateur))
//      {
//         throw overflow_error("Debordement du numerateur");
//      }
//      else if ((fractionSimplifiee1.denominateur + fractionSimplifiee2.denominateur - numeric_limits<T>::max() < fractionSimplifiee1.denominateur) 
//               && 
//               (fractionSimplifiee1.denominateur + fractionSimplifiee2.denominateur - numeric_limits<T>::max() < fractionSimplifiee2.denominateur))
//      {
//         throw overflow_error("Debordement du denominateur");
//      }
//   }
   
   // Exceptions numerateur
   if((fractionSimplifiee1.numerateur > 0 ) && (fractionSimplifiee2.numerateur > numeric_limits<T>::max() - fractionSimplifiee1.numerateur))
   {
      throw overflow_error("Debordement du numerateur (overflow)");
   }
   else if ((fractionSimplifiee1.numerateur < 0 ) && (fractionSimplifiee2.numerateur < numeric_limits<T>::max() - fractionSimplifiee1.numerateur))
   {
      throw underflow_error("Debordement du numerateur (underflow)");
   }   
   
   // Exceptions denominateur
   if((fractionSimplifiee1.denominateur > 0 ) && (fractionSimplifiee2.denominateur > numeric_limits<T>::max() - fractionSimplifiee1.denominateur))
   {
      throw overflow_error("Debordement du denominateur (overflow)");
   }
   else if ((fractionSimplifiee1.denominateur < 0 ) && (fractionSimplifiee2.denominateur < numeric_limits<T>::max() - fractionSimplifiee1.denominateur))
   {
      throw underflow_error("Debordement du denominateur (underflow)");
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
   
//   //Même chose que pour l'opérateur + concernant la copie
//   
//   //Simplifications préalables pour limiter les débordements
//   Fraction<T> fractionSimplifiee1 = this->simplifier();
//   Fraction<T> fractionSimplifiee2 = fraction.simplifier();
//   
//   Fraction<T> fractionRes(fractionSimplifiee1.numerateur * fractionSimplifiee2.numerateur, 
//                           fractionSimplifiee1.denominateur * fractionSimplifiee2.denominateur);
//   
//   return fractionRes.simplifier();
   
   Fraction<T> fractionRes = *this;
   
   try
   {
      fractionRes *= fraction;
   }
   catch(const runtime_error& e)
   {
      cout << e.what() << endl;
      throw;
   }
   
   return fractionRes;
}

template<typename T>
Fraction<T>& Fraction<T>::operator*=(const Fraction<T>& fraction) 
{
   
   //Même chose que pour l'opérateur + concernant la copie
   
   //Simplifications préalables pour limiter les débordements
   Fraction<T> fractionSimplifiee1 = this->simplifier();
   Fraction<T> fractionSimplifiee2 = fraction.simplifier();
   
   // Detection d'un débordement, avant le calcul effectif
   if(fractionSimplifiee1.numerateur > (numeric_limits<T>::max() / fractionSimplifiee2.numerateur))
   {
      throw overflow_error("Debordement du numerateur");
   }
   else if (fractionSimplifiee1.denominateur > (numeric_limits<T>::max() / fractionSimplifiee2.denominateur))
   {
      throw overflow_error("Debordement du denominateur");
   }
   
   // Affectation des résultats, puis simplification via un objet temporaire (contrainte due à la consigne concernant la fonction simplifier())
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
   
   return abs(a); //Valeur absolue pour pas faire changer de signe le numérateur
}

#endif /* FRACTIONIMPL_H */

