#include <iostream>
#include <string>
#include <atomic>
#include <thread>
#include <vector>
#include <mutex>
#include "md5.h"
#include <condition_variable>

using namespace std;

mutex m1;
atomic<bool> trouve(false);
condition_variable cv;
string resultat;
string secret = "3ed7dceaf266cafef032b9d5db224717"; // Le hachage MD5 de "salut"

void fonction(int start, int end, int c) {
    // Attendez que tous les threads soient prêts
    {
        std::unique_lock<std::mutex> lock(m1);
        cv.wait(lock, [] { return !trouve; });
    }

    // Maintenant, commencez la recherche
    for (int i = start; i <= end; i++) {
        for (int j = 97; j <= 122; j++) {
            for (int k = 97; k <= 122; k++) {
                for (int l = 97; l <= 122; l++) {
                    string mot = string(1, static_cast<char>(c)) + static_cast<char>(i) + static_cast<char>(j) + static_cast<char>(k) + static_cast<char>(l);

                    std::lock_guard<std::mutex> verrouillage(m1);
                    if (md5(mot) == secret) {
                        trouve = true;
                        cv.notify_all();
                        resultat = mot;
                        cout << mot << "*hash trouvéééé bingo*** *" << md5(mot) << endl;
                        return ;
                    }
                    if(trouve) return ;
                    cout << mot << "*hash *" << md5(mot) << endl;
                }
            }
        }
    }
}

int main(int argc, char* argv[]) {
    vector<thread> threadvector;

    // Lancez un thread pour chaque lettre de 'a' à 'z' comme première lettre
    for (int i = 97; i <= 122; i++) {
        threadvector.emplace_back(fonction, 97, 122,  i);
    }

    // Attendez que tous les threads se terminent
    for (auto& t : threadvector) t.join();

    cout << "resultat : " << resultat << endl;

    return 0;
}
