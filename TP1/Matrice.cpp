#include "Matrice.hpp"
#include <iostream>
#include <thread>
using namespace std;

const int n = 5;

Matrice::Matrice(int rows, int cols) : rows(rows), cols(cols) {
    data = vector<vector<int>>(rows, vector<int>(cols, 0));
}

Matrice::Matrice(int rows, int cols, vector<vector<int>>& data) : rows(rows), cols(cols), data(data) {}

void Matrice::display(const Matrice& matrix) {
    // Afficher les données de la matrice 'data'
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.cols; j++) {
            std::cout << matrix.data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

Matrice& Matrice::factor(int row, int col, const Matrice& A1, const Matrice& B1) {
    this->data[rows][cols] = 0;  // Initialisez la valeur à 0 avant d'additionner
    for (int k = 0; k < n; k++) {
        this->data[rows][cols] += A1.data[row][k] * B1.data[k][col];
    }
    return *this;
}

Matrice& Matrice::factorPerBloc(int row,  const Matrice& A1, const Matrice& B1) {


   
    for (int j = 0; j < B1.rows; j++) {
        data[row][j] = 0;  // Initialisez la valeur à 0 avant d'additionner
        for (int k = 0; k < n; k++) {
            data[row][j] += A1.data[row][k] * B1.data[k][j];
        }
    }
    return *this;
}
    
    
    
 

Matrice& Matrice::calculePIJmultithread(const Matrice& A1, const Matrice& B1) {
    vector<thread> T;
    for (int i = 0; i < A1.rows; i++) {
        for (int j = 0; j < B1.cols; j++) {
            T.push_back(thread(&Matrice::factor, this, i, j, std::ref(A1), std::ref(B1)));
        }
    }
    for (auto& thread : T) {
        thread.join();
    }
    return *this;
}

Matrice &Matrice::calculePIJmultithreadparbloc(const Matrice &A1, const Matrice &B1)
{
    vector<thread> T;
    // division par ligne
    int m = A1.cols;
    for (int i = 0; i < A1.cols; i++) {
       
            T.push_back(thread(&Matrice::factorPerBloc, this, i,  std::ref(A1), std::ref(B1)));
        }
    
    for (auto& thread : T) {
        thread.join();
    }
    return *this;
}

Matrice& Matrice::calculePIJ(const Matrice& A1, const Matrice& B1) {
    for (int i = 0; i < A1.rows; i++) {
        for (int j = 0; j < B1.cols; j++) {
            this->factor(i, j, A1, B1);
        }
    }
    return *this;
}

int main() {
    vector<vector<int>> A1(n, vector<int>(n));
    vector<vector<int>> B1(n, vector<int>(n));
    A1 = {
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20},
        {21, 22, 23, 24, 25}
    };

    B1 = {
        {4, 0, 0, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 0, 0, 1}
    };

   
    Matrice A = Matrice(n, n, A1);
    Matrice B = Matrice(n, n, B1);
    Matrice C = Matrice(n, n);
   ;  // Utilisez calculePIJmultithreadparbloc pour le calcul parallèle
 C = C.calculePIJmultithreadparbloc(A, B);  // Utilisez calculePIJmultithread pour le calcul parallèle
    C.display(C);
    
    
   /* par sequence 
    std::vector<std::vector<int>> C1(n, std::vector<int>(n, 0));

    Matrice A = Matrice(n, n, A1);
    Matrice B = Matrice(n, n, B1);
    Matrice C = Matrice (n , n , C1);  // Initialisez C en copiant les dimensions de A
    C = C.calculePIJ(A, B);
    C.display(C);*/
  /*Multithreading 
  Matrice A = Matrice(n, n, A1);
    Matrice B = Matrice(n, n, B1);
    Matrice C = Matrice(n, n);
    C = C.calculePIJmultithread(A, B);  // Utilisez calculePIJmultithread pour le calcul parallèle
    C.display(C);*/



    return 0;
}
