#include <iostream>
#include <thread>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <mutex>
using namespace std;

mutex m;
string text2 = "l'atiste à realiser une bonne prouesse";
vector<string> tokens;  // tolowercase
vector<string> tokensf; // without apostrophe
string text = "Le ,Tourange ;des 5  .film des 1 D'almatient à été fais sur la ville d' avignon ";
map<int, string> chiffreenlettre = {
    {0, "zéro"},
    {1, "un"},
    {2, "deux"},
    {3, "trois"},
    {4, "quatre"},
    {5, "cinq"},
    {6, "six"},
    {7, "sept"},
    {8, "huit"},
    {9, "neuf"}};

void tolowercase() {
    lock_guard<mutex> verrouillage(m);
    for (char& c : text) {
        c = std::tolower(c);
    }
}
void withoutfulpoint() {
      lock_guard<mutex> verrouillage(m);
    char tab[] = { '.', '!', '?', ';', ',' };
    
    for (char c : tab) {
        size_t position = text.find(c);
        while (position != std::string::npos) {
            text.replace(position, 1, " ");  // Remplace le caractère par un espace
            position = text.find(c, position);  // Recherche le caractère suivant
        }
    }
}
void tokeniser() {
    lock_guard<mutex> verrouillage(m);
    istringstream flux(text);

    string mot;
    char apostrophe = '\'';
    while (flux >> mot) {
        // Ajoutez chaque mot/token à un vecteur
        tokens.push_back(mot);
    }
    for (const std::string& token : tokens) {
        size_t position = token.find(apostrophe);
        if (position != std::string::npos) {

            // Divisez le mot en deux parties
            string avantApostrophe = token.substr(0, position);
            string apresApostrophe = token.substr(position + 1); // +1 pour sauter l'apostrophe
            tokensf.push_back(avantApostrophe);
            tokensf.push_back(apresApostrophe);
        }
        else
            tokensf.push_back(token);
    }
    string phrase;
    for (string& str : tokensf) {
        phrase += str + " ";
    }
    text = string(phrase);
    // Supprime l'espace en trop à la fin de la phrase
    if (!text.empty()) {
        text.pop_back();
    }
}

void numbertoletter() {
    for (int i = 0; i <= 9; i++) {
        string nombre = to_string(i);
        string lettre = chiffreenlettre[i];
        size_t position = text.find(nombre);
        while (position != string::npos) {
            text.replace(position, nombre.length(), lettre);
            position = text.find(nombre, position + lettre.length());
        }
    }
}

int main() {
    thread t0(withoutfulpoint);
     t0.join();
    thread t1(tolowercase); t1.join();
    thread t2(tokeniser); t2.join();
    thread t3(numbertoletter); t3.join();
   
    
   
   

    cout << text << endl;

    return 0;
}
