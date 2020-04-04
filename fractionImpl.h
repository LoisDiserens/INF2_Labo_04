/*
 -----------------------------------------------------------------------------------
 Laboratoire : 04
 Fichier     : fractionImpl.h
 Auteur(s)   : Nicolas Ogi
               Loïs Diserens
 Date        : 27.03.2020

 But         : A le rôle de fraction.cpp, mais délocaliser à cause de la généricité

 Remarque(s) : Indiquations sur les méthodes de détection d'overflow, suivant le cours
               d'INF 1, ainsi que sur : 
               http://www.cplusplus.com/articles/DE18T05o/
               https://stackoverflow.com/questions/199333/how-do-i-detect-unsigned-integer-multiply-overflow

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
T Fraction<T>::donneDenominateur() const noexcept
{
   return denominateur;
}

template <typename T>
Fraction<T> Fraction<T>::simplifier() const noexcept
{
   T divCommun = pgdc(numerateur, denominateur);
   
   return Fraction(numerateur / divCommun, denominateur / divCommun);
}

template <typename T>
bool Fraction<T>::identite(const Fraction<T>& fractionComparee) const
{
   return numerateur == fractionComparee.numerateur && denominateur == fractionComparee.denominateur;
}

template <typename T>
bool Fraction<T>::operator==(const Fraction<T>& rhs) const
{
   return (double)*this == (double)rhs;
}

template <typename T>
Fraction<T> Fraction<T>::operator+(const Fraction<T>& fraction) const 
{  
   Fraction<T> fractionRes = *this;
   fractionRes += fraction;
   
   return fractionRes;
}

template <typename T>
Fraction<T>& Fraction<T>::operator+=(const Fraction<T>& fractionAdditionnee)
{ 
   //Simplifications préalables pour limiter les débordements
   Fraction<T> fractionSimplifiee1 = this->simplifier();
   Fraction<T> fractionSimplifiee2 = fractionAdditionnee.simplifier();
   
   // Calcul du denominateur final car besoin pour les tests d'exception des numerateurs
   // Exceptions dénominateur
   if(fractionSimplifiee1.denominateur > (numeric_limits<T>::max() / fractionSimplifiee2.denominateur))
   {
      throw overflow_error("Debordement du denominateur (Overflow)");
   }
   else if (fractionSimplifiee1.denominateur < (numeric_limits<T>::lowest() / fractionSimplifiee2.denominateur))
   {
      throw underflow_error("Debordement du denominateur (Underflow)");
   }
   
   //Pour trouver le dénominateur commun : den1 * den2 / pgdc(den1, den2)
   T denomFractionTemp = fractionSimplifiee1.denominateur * fractionSimplifiee2.denominateur / 
                         pgdc(fractionSimplifiee1.denominateur, fractionSimplifiee2.denominateur);
   
   // Vérification que les nouveaux numérateurs ne vont pas subir d'overflow / underflow
   if(fractionSimplifiee1.numerateur > (numeric_limits<T>::max() / (denomFractionTemp / fractionSimplifiee1.denominateur)))
   {
      throw overflow_error("Debordement du nouveau numerateur (de la fonction de gauche), apres PGDC (Overflow)");
   }
   else if (fractionSimplifiee1.numerateur < (numeric_limits<T>::lowest() / (denomFractionTemp / fractionSimplifiee1.denominateur)))
   {
      throw underflow_error("Debordement du nouveau numerateur (de la fonction de gauche), apres PGDC (Underverflow)");
   }
   
   
   if(fractionSimplifiee2.numerateur > (numeric_limits<T>::max() / (denomFractionTemp / fractionSimplifiee2.denominateur)))
   {
      throw overflow_error("Debordement du nouveau numerateur (de la fonction de droite), apres PGDC (Overflow)");
   }
   else if (fractionSimplifiee2.numerateur < (numeric_limits<T>::lowest() / (denomFractionTemp / fractionSimplifiee2.denominateur)))
   {
      throw underflow_error("Debordement du nouveau numerateur (de la fonction de droite), apres PGDC (Underverflow)");
   }
   
   // Calcul des nouveaux numérateurs (après changement du denominateur)
   T nouveauNumerateurF1 = fractionSimplifiee1.numerateur * (denomFractionTemp / fractionSimplifiee1.denominateur);
   T nouveauNumerateurF2 = fractionSimplifiee2.numerateur * (denomFractionTemp / fractionSimplifiee2.denominateur);
   
   // Exceptions, addition des numérateurs
   if(nouveauNumerateurF1 > 0 && nouveauNumerateurF2 > numeric_limits<T>::max() - nouveauNumerateurF1)
   {
      throw overflow_error("Debordement du numerateur (overflow)");
   }
   else if (nouveauNumerateurF1 < 0 && nouveauNumerateurF2 < numeric_limits<T>::lowest() - nouveauNumerateurF1)
   {
      throw underflow_error("Debordement du numerateur (underflow)");
   }
   
   // Calcul du numérateur final
   T numerFractionTemp = nouveauNumerateurF1 + nouveauNumerateurF2;
   
   // Affectation des résultats, puis simplification via un objet temporaire (contrainte due à la consigne concernant la fonction simplifier())
   Fraction<T> fractionTemp = Fraction<T> (numerFractionTemp, denomFractionTemp).simplifier();
   numerateur = fractionTemp.numerateur;
   denominateur = fractionTemp.denominateur;
   
   return *this; 
}

template <typename T>
Fraction<T> Fraction<T>::operator*(const Fraction<T>& fraction) const 
{   
   Fraction<T> fractionRes = *this;
   fractionRes *= fraction;
   
   return fractionRes;
}

template <typename T>
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
template <typename T>
T Fraction<T>::pgdc(T a, T b) const noexcept
{
   T tmp;
   
   while (b != 0) 
   {
     tmp = b;
     b = a % b;
     a = tmp;
   }
   
   // Valeur absolue pour pas faire changer de signe le numérateur ou le dénominateur
   return abs(a); 
}

#endif /* FRACTIONIMPL_H */

