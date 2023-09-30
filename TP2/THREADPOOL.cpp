#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <mutex>
using namespace std;
mutex m;

int n =10; 
int k=3;int threadactif =0;
 vector< int >task ; 
double somme = 0.0;

  double  calculfactoriel (int i ){
    if(i==0 || i==1) {

            return 1;
        }
    else {
       
            return (i*calculfactoriel(i-1));
    }
   

 }
 void calculepartiel(int i) {
    double termePartiel = 0.0;

      m.lock();
    threadactif++;
    m.unlock();

    if (i % 2 == 0) {
        termePartiel = 1.0 / calculfactoriel(i);
    } else {
        termePartiel = -1.0 / calculfactoriel(i);
    }

    // Verrouillage pour mettre à jour la somme
    m.lock();
    cout<< "je suis sle thread " <<i << "****"<< "terme   "<< termePartiel << endl ;
    somme += termePartiel;
    threadactif--;

    m.unlock();
 }

void myunction(int i){
      m.lock();
    threadactif++;
    m.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    cout << "je suis le thread " << i << endl;
    cout << endl;; 
    m.lock();
    threadactif--;
    m.unlock();

}
void threadpool(){
for (int i =0; i< n ; i++){
    task.push_back(i);
}
vector < thread > threadvector(k);
for (int i =0; i< k ; i++){
    int current_task =-1; 
    if(!task.empty()){
        m.lock();
        current_task= task.back();
        task.pop_back();
       
        m.unlock();
    }
    if(current_task !=-1){
        threadvector[i]= thread(calculepartiel, current_task);
        threadvector[i].detach();
    }
   // for (auto& t: threadvector ) t.detach();
   
}

while (1) {
    int next=-1;
    m.lock();
  if (!task.empty() && threadactif < k){
      
        next= task.back();
        task.pop_back();
  }  
        m.unlock();
        if(next != -1){
            thread t (calculepartiel, next);
            t.detach();
        

    }
else if (task.empty()|| next ==-1) break ;
}

}

int main(){

threadpool();
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "Somme finale : " << somme << endl;
    return 0;



}
