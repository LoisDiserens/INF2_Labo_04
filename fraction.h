/*
 -----------------------------------------------------------------------------------
 Laboratoire : 04
 Fichier     : fraction.h
 Auteur(s)   : Nicolas Ogi
               Loïs Diserens
 Date        : 27.03.2020

 But         : Ce fichier contient la classe Fraction avec ses fonctions et ses
               données membres ainsi que sa fonction amie qui est la surcharge de
               l'opérateur d'écriture sur un flux.

 Remarque(s) : -

 Compilateur : MinGW-g++ 6.3.0
 -----------------------------------------------------------------------------------
 */
#ifndef FRACTION_H
#define FRACTION_H

#include <ostream>

// Déclaration avancée de la classe 
template <typename T> class Fraction;

// Définition, façon générique, des friends
template<typename T> 
std::ostream& operator << (std::ostream& lhs, const Fraction<T>& fraction) { 
   lhs << fraction.numerateur << "/" << fraction.denominateur; 
   return lhs; 
} 

/**
 * Classe Fraction permettant de modéliser une fraction avec son numérateur et son
 * dénominateur.
 */
template <typename T>
class Fraction
{
   // Friends
   /**
   * Surcharge de l'opérateur d'écriture sur un flux permettant d'afficher une fraction
   * avec ce format : "num/den"
   */
   friend std::ostream& operator<< <T>(std::ostream& lhs, const Fraction<T>& fraction); 
   
   public:
      /**
       * Constructeur permettant d'instancier un objet Fraction en renseignant son
       * numérateur et son dénominateur
       * @param initNumerateur   | entier représentant le numérateur
       * @param initDenominateur | entier non-signé représentant le dénominateur
       * @throws std::invalid_argument si le dénominateur est nul (Division par zéro)
       * @throws std::invalid_argument si le dénominateur est négatif
       */
      Fraction<T>(T initNumerateur, T initDenominateur);
      
      // Fonctions membres publiques
      /**
       * Fonction retournant le dénominateur d'une fraction
       * @return T le dénominateur de la fraction
       * 
       * Cette fonction possède la garantie no-throw.
       */
      T donneDenominateur() const noexcept;
      
      /**
       * Fonction retournant la version irreductible de l'objet Fraction qui a 
       * appelé cette fonction
       * @return objet Fraction réprésentant la fraction sous forme irréductible
       * 
       * Cette fonction possède la garantie no-throw.
       */
      Fraction<T> simplifier() const noexcept;
      
      /**
       * Fonction permettant de savoir si deux fractions sont identiques, c.-à-d. si
       * num1 = num2 et den1 = den2
       * @param fractionComparee | objet Fraction avec lequel comparer l'identicité
       * @return booléen indiquant true si les deux fractions sont indentiques
       */
      bool identite(const Fraction<T>& fractionComparee) const;
      
      /*
       * Surcharge de l'opérateur == afin de vérifier l'égalité numérique de deux
       * fractions
       */
      bool operator==(const Fraction<T>& rhs) const;
      
      //Seulement capable de sommer des fractions. Doit être capable de sommer une fraction avec une constante ?
      /**
       * 
       * @param fraction
       * @return 
       */
      Fraction<T> operator+(const Fraction<T>& fraction) const;
      
      /**
       * 
       * @param fractionAdditionnee
       * @return 
       */
      Fraction<T>& operator+=(const Fraction<T>& fractionAdditionnee);
      
      //Même question mais pour la multiplication ?
      /**
       * 
       * @param fraction
       * @return 
       */
      Fraction<T> operator*(const Fraction<T>& fraction) const;
      
      /**
       * 
       * @param fraction
       * @return 
       */
      Fraction<T>& operator*=(const Fraction<T>& fraction);
      
      /**
       * Surcharge de l'opérateur de cast double afin de retourner la valeur 
       * numérique de la fraction en double
       */
      operator double() const { return (double)numerateur / (double)denominateur;}
      
      /**
       * Surcharge de l'opérateur de cast float afin de retourner la valeur 
       * numérique de la fraction en float
      */
      operator float() const { return (float)numerateur / (float)denominateur;}
      
   private:
      // Variables 
      T numerateur;
      T denominateur;
      
      // Fonctions membres privées
      /**
       * Fonction se basant sur l'algorithme d'Euclide afin de trouver le plus grand
       * diviseur commun entre deux nombres
       * @param a | entier 
       * @param b | entier
       * @return entier représentant le PGDC des nombres a et b
       * 
       * Cette fonction possède la garantie no-throw.
       */
      T pgdc(T a, T b) const noexcept;
};

// Inclusion des définitions de fonctions de la classe générique
#include "fractionImpl.h"

#endif /* FRACTION_H */

