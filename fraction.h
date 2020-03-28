/*
 -----------------------------------------------------------------------------------
 Laboratoire : 04
 Fichier     : fraction.h
 Auteur(s)   : Nicolas Ogi
               Loïs Diserens
 Date        : 27.03.2020

 But         : <à compléter>

 Remarque(s) : <à compléter>

 Compilateur : MinGW-g++ 6.3.0
 -----------------------------------------------------------------------------------
 */
#ifndef FRACTION_H
#define FRACTION_H

#include <ostream>

// Déclaration avancée de la classe 
template <typename T> class Fraction;

// Définition, facon générique, des friends
template<typename T> 
std::ostream& operator << (std::ostream& lhs, const Fraction<T>& fraction) { 
   lhs << fraction.numerateur << "/" << fraction.denominateur; 
   return lhs; 
} 


template <typename T>
class Fraction
{
   // Friends
   
   public:
      // Constructeur
      Fraction<T>(T initNumerateur, T initDenominateur);
      
      // Fonctions membres publiques
      Fraction<T> simplifier();
      bool identite(const Fraction<T>& fractionCible) const;
      bool operator==(const Fraction<T>& rhs) const;
      friend std::ostream& operator<< <T>(std::ostream& lhs, const Fraction<T>& fraction); 
      operator double() const { return (double)numerateur / (double)denominateur;}
      operator float() const { return (float)numerateur / (float)denominateur;}
      
   private:
      // Variables 
      T numerateur;
      T denominateur;
      
      // Fonctions membres privées
      T pgdc(T a, T b);
};

// Inclusion des définitions de fonctions de la classe générique
#include "fractionImpl.h"

#endif /* FRACTION_H */

