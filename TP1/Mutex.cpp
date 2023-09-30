
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

using namespace std ; 
mutex mpaire , mimpaire ;


void affiche (int i ){

    cout << i << endl; 
}

void display( int start , int end  ){
   ;
    for ( int i =start ; i< end; i+=2){

       affiche(i);
    }
    
}
void displayPair(){
        for (int i =0  ; i< 1001 ; i+=2){
            mpaire.lock();
        cout << "pair"  << " : " << i << endl; 
        mimpaire.unlock();

    }


}



void displayImpair (){
       
    for (int i =1  ; i< 1000 ; i+=2){
         mimpaire.lock();
        cout << "impair" <<  " : " <<i << endl; 
        mpaire.unlock();
    }


}
int main(){
    //1er question 
   /*  thread t2 ; 
    thread t1;

    t2= thread(display, 0, 1001);
   
   

    t1= thread(display,1,1001 );


   t2.join();
   t1.join();*/

   // 2 e question 
  thread t2 ; 
    thread t1;
    //mpaire.lock();
    mimpaire.lock();
    t2=thread(displayImpair);
    t1=thread(displayPair);
   
     t1.join();
     t2.join();
     cout<<"bonjjour";




    return 0;
}
    
