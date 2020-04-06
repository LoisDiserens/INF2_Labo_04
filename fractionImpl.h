/*
 -----------------------------------------------------------------------------------
 Laboratoire : 04
 Fichier     : fractionImpl.h
 Auteurs   : Nicolas Ogi, Loïs Diserens
 Date        : 27.03.2020

 But         : A le rôle de fraction.cpp, mais délocalisé à cause de la généricité

 Remarque(s) : Indications sur les méthodes de détection d'overflow, suivant le cours
               d'INF1, ainsi que sur : 
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
   
   if(initDenominateur == 0)
   {
      throw invalid_argument("Division par zero");
   }
   else if(initDenominateur < 0)
   {
      throw invalid_argument("Nombre negatif au denominateur");
   }
   
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
bool Fraction<T>::identite(const Fraction<T>& fractionComparee) const noexcept
{
   return numerateur == fractionComparee.numerateur && 
          denominateur == fractionComparee.denominateur;
}

template <typename T>
bool Fraction<T>::fractionNegative() const noexcept
{
   return numerateur < 0;
}

template <typename T>
bool Fraction<T>::operator==(const Fraction<T>& rhs) const noexcept
{  
   return fabs((double)*this - (double)rhs) <= numeric_limits<double>::epsilon();
}

template <typename T>
Fraction<T> Fraction<T>::operator+(const Fraction<T>& fraction) const 
{  
   Fraction<T> fractionRes = *this;
   fractionRes += fraction;
   
   return fractionRes;
}

template <typename T>
Fraction<T>& Fraction<T>::operator+=(const Fraction<T>& fraction)
{ 
   //Simplifications préalables pour limiter les débordements
   Fraction<T> fractionSimplifiee1 = this->simplifier();
   Fraction<T> fractionSimplifiee2 = fraction.simplifier();
   
   // Détection d'overflow/underflow lors du calcul pour trouver le dénominateur commun
   if(fractionSimplifiee1.denominateur > (numeric_limits<T>::max() / fractionSimplifiee2.denominateur))
   {
      throw overflow_error("Debordement du denominateur (overflow)");
   }
   else if (fractionSimplifiee1.denominateur < (numeric_limits<T>::lowest() / fractionSimplifiee2.denominateur))
   {
      throw underflow_error("Debordement du denominateur (underflow)");
   }
   
   //Calcul du dénominateur commun
   T denomFractionTemp = fractionSimplifiee1.denominateur * fractionSimplifiee2.denominateur / 
                         pgdc(fractionSimplifiee1.denominateur, fractionSimplifiee2.denominateur);
   
   // Détection d'overflow/underflow lors du calcul des nouveaux numérateurs
   if(fractionSimplifiee1.numerateur > (numeric_limits<T>::max() / (denomFractionTemp / fractionSimplifiee1.denominateur)))
   {
      throw overflow_error("Debordement du nouveau numerateur (de la fraction de gauche), apres PGDC (overflow)");
   }
   else if (fractionSimplifiee1.numerateur < (numeric_limits<T>::lowest() / (denomFractionTemp / fractionSimplifiee1.denominateur)))
   {
      throw underflow_error("Debordement du nouveau numerateur (de la fraction de gauche), apres PGDC (underflow)");
   }
   
   if(fractionSimplifiee2.numerateur > (numeric_limits<T>::max() / (denomFractionTemp / fractionSimplifiee2.denominateur)))
   {
      throw overflow_error("Debordement du nouveau numerateur (de la fraction de droite), apres PGDC (overflow)");
   }
   else if (fractionSimplifiee2.numerateur < (numeric_limits<T>::lowest() / (denomFractionTemp / fractionSimplifiee2.denominateur)))
   {
      throw underflow_error("Debordement du nouveau numerateur (de la fraction de droite), apres PGDC (underflow)");
   }
   
   // Calcul des nouveaux numérateurs (en fonction du denominateur commun)
   T nouveauNumerateurF1 = fractionSimplifiee1.numerateur * (denomFractionTemp / fractionSimplifiee1.denominateur);
   T nouveauNumerateurF2 = fractionSimplifiee2.numerateur * (denomFractionTemp / fractionSimplifiee2.denominateur);
   
   // Détection d'overflow/underflow lors de l'addition des nouveaux numérateurs
   if(nouveauNumerateurF1 > 0 && nouveauNumerateurF2 > numeric_limits<T>::max() - nouveauNumerateurF1)
   {
      throw overflow_error("Debordement du numerateur (overflow)");
   }
   else if (nouveauNumerateurF1 < 0 && nouveauNumerateurF2 < numeric_limits<T>::lowest() - nouveauNumerateurF1)
   {
      throw underflow_error("Debordement du numerateur (underflow)");
   }
   
   // Addition des numérateurs 
   T numerFractionTemp = nouveauNumerateurF1 + nouveauNumerateurF2;
   
   // Création d'une fraction temporaire, simplification et affectation des résultats
   // aux données membres (contrainte due à la consigne concernant la fonction simplifier())
   Fraction<T> fractionTemp = Fraction<T> (numerFractionTemp, denomFractionTemp);
   fractionTemp = fractionTemp.simplifier();
   
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
      
   // Détection d'overflow/underflow lors de la multiplication des numérateurs
   if(fractionSimplifiee1.numerateur > (numeric_limits<T>::max() / fractionSimplifiee2.numerateur))
   {
      throw overflow_error("Debordement du numerateur (overflow)");
   }
   else if (fractionSimplifiee1.numerateur < (numeric_limits<T>::lowest() / fractionSimplifiee2.numerateur))
   {
      throw underflow_error("Debordement du numerateur (underflow)");
   }
   
   // Détection d'overflow/underflow lors de la multiplication des dénominateurs
   if(fractionSimplifiee1.denominateur > (numeric_limits<T>::max() / fractionSimplifiee2.denominateur))
   {
      throw overflow_error("Debordement du denominateur (overflow)");
   }
   else if (fractionSimplifiee1.denominateur < (numeric_limits<T>::lowest() / fractionSimplifiee2.denominateur))
   {
      throw underflow_error("Debordement du denominateur (underflow)");
   }
   
   // Création d'une fraction temporaire, simplification et affectation des résultats
   // aux données membres (contrainte due à la consigne concernant la fonction simplifier())
   Fraction<T> fractionTemp(fractionSimplifiee1.numerateur * fractionSimplifiee2.numerateur, 
                           fractionSimplifiee1.denominateur * fractionSimplifiee2.denominateur);
   fractionTemp = fractionTemp.simplifier();
   
   numerateur = fractionTemp.numerateur;
   denominateur = fractionTemp.denominateur;
   
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
   
   // Valeur absolue pour éviter que le numérateur ou le dénominateur ne changent de
   // signe
   return abs(a); 
}

#endif /* FRACTIONIMPL_H */

