#ifndef _MATRICE_HPP_
#define _MATRICE_HPP_

#include <iostream>
#include <vector>

class Matrice {
public:
   
    Matrice(int rows, int cols);
    Matrice(int rows, int cols,  std::vector<std::vector<int>>& data);

    // Fonction pour calculer PIJ
    Matrice& calculePIJ(const Matrice& matrix1,const Matrice& matrix2 );

    void display(const Matrice &matrix);
    Matrice& factor(int row, int col, const Matrice &A1, const Matrice &B1);
   
   Matrice &factorPerBloc(int row, const Matrice &A1, const Matrice &B1);

   Matrice &calculePIJmultithread(const Matrice &A1, const Matrice &B1);

   Matrice &calculePIJmultithreadparbloc(const Matrice &A1, const Matrice &B1);
   ;

   private:
   int rows;
   int cols;
   std::vector<std::vector<int>> data;
    
    };

#endif // _MATRICE_HPP_
