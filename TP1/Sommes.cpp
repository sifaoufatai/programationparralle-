
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

using namespace std ;
mutex m ;

int Tableau [10]={1,2,3,4,5,6,7,8,9,10};
int n=10 ;

int Sommseq(int * tab ){
    int  somme = 0;
        for(int i = 0; i< n ; i++){

            somme +=tab[i] ;
        }
        return somme ;

}

void  somme(int * tab,  int limit ,int&  somme , int start , int end  ){
        
          m.lock();
            int sommeperthread =0;
        for (int i =start; i< end  ;i++){
           
          
          somme+= tab[i];
            m.unlock();

        }
        //somme+= sommeperthread;
}
int sommemultithread(int * tab , int limit, int& st  ){
    
   int step = limit;

    vector<thread> Thread;
        for (int i = 0; i < n; i+=limit){
            int start = i;
            int end = min (i+limit , n);

            Thread.push_back(thread ( somme, tab , limit,ref(st), start,end));
            
        }
        for (auto& thread : Thread){



            thread.join();
        }
    return 0;

}
int main(){
int s= 0;
n = 10; // Définissez la taille du tableau
//int result1 = Sommseq(Tableau);
sommemultithread(Tableau, 2, s);
cout << s ;
//std::cout << "Somme des éléments du tableau : " << result1 << std::endl;
}