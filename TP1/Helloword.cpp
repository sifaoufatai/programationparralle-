#include <iostream>
#include<thread>
using namespace std;

void  fonction_hello (){
   cout << "Hello world  " << std::endl;
    
}

void  fonction_word (){
  cout << " HELLEworld" << std::endl;
    
}

int main() {
   thread t1( fonction_hello);
   thread t2(fonction_word);
   t1.join();
   t2.join();
   return 0;
}