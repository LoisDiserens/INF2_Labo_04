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


template <typename T>
class Fraction
{
   public:
      Fraction<T> simplifier(Fraction<T>& fraction);
      Fraction<T>(T initNumerateur, T initDenominateur);
      
   private:
      T pgdc(T a, T b);
      T numerateur;
      T denominateur;
};

#endif /* FRACTION_H */

