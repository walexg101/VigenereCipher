#include <cstdlib>
#include <iostream>
#include <string>
#include "ctype.h"

using namespace std;

const string DEFAULT_TEXT = "counterstrike";

void cleanText(string &);
void createKey(string &, string &, string &);
string vcEncrypt(string, string);
string vcDecrypt(string, string);

int main() {
    string text;
    string message;
    string key;
    string option;
    string quit;
    bool messageStatus = true;
    bool optionStatus = true;
    bool runStatus = true;
    
    do {
        cout << "Vignere Cipher Encryption / Decryption Service 1.0" 
             << endl
             << "Please enter a single key-word or press \"Enter\" to skip. "
                "(Only alphabetic characters will be accepted and all other words, "
                "spaces and characters will be removed): "
             << endl;
        
        getline(cin, text);
        
        if (text == "") {            
            cout << "Using default key-word: "
                 << DEFAULT_TEXT
                 << endl;
            
            text = DEFAULT_TEXT;
        } else {
            cout << "Cleaning text..."
                 << endl;
            
            cleanText(text);
            
            cout << "Using cleaned key-word: "
                 << text
                 << endl;
        }
        
        while (messageStatus == true) {
            cout << "Please enter a single message to encrypt, an encrypted "
                    "message to decrypt, or press \"Enter\" to restart the "
                    "session. (Only alphabetic characters will be accepted "
                    "and all other words, spaces and characters will be removed): "
                 << endl;
            
            getline(cin, message);
            
            if (message == "") {
                messageStatus = false;
                optionStatus = false;
            } else {
                cleanText(message);
                
                cout << "Message recorded: "
                     << message
                     << endl;
                
                createKey(text, message, key);
                
                messageStatus = false;
            }
        }
        
        while (optionStatus == true) {
            cout << "Enter e to encrypt, d to decrypt, or press enter to "
                    "restart the session: "
                 << endl;

            getline(cin, option);

            if (option != "") {
                cleanText(option);

                if (option == "e" || option == "encrypt") {
                    cout << "Encrypted message: "
                         << message
                         << " to "
                         << vcEncrypt(message, key)
                         << endl;
                } else if (option == "d" || option == "decrypt") {
                    cout << "Decrypted message: "
                         << message
                         << " to "
                         << vcDecrypt(message, key)
                         << endl;
                } else {
                    cout << "Please enter a valid selection."
                         << endl;
                }
            } else {
                optionStatus = false;
            }
        }
        
        cout << "Enter anything to continue or press \"Enter\" to quit: "
             << endl;
        getline(cin, quit);
        
        if (quit == "") {
            runStatus = false;
        } else {
            messageStatus = true;
            optionStatus = true;
        }
    } while (runStatus == true);
     
    return 0;
}

void cleanText(string & text) {
    char letter;
    
    for (int i = text.length() - 1; i >= 0; i--) {
        letter = text.at(i);
        
        if ((letter >= 65 && letter <= 90) || (letter >= 97 && letter <= 122)) {
            continue;
        } else {
            text.erase(i, 1);
        }
    }
    
    for (char & l : text) {
        l = tolower(l);
    }
}

void createKey(string & text, string & message, string & key) {
    int letterPos;
    
    for (int i = 0; i < message.length(); i++) {
        letterPos = i % text.length();
        
        string letter = text.substr(letterPos, 1);
        
        key.append(letter);
    }
}

string vcEncrypt(string message, string key) {
    string encryptedMessage;
    
    for (int i = 0; i < message.length(); i++) {
        encryptedMessage.push_back(((message.at(i) - 97 + key.at(i) - 97) % 26) + 97);
    }
    
    return encryptedMessage;
}

string vcDecrypt(string message, string key) {
    string decryptedMessage;
    
    for (int i = 0; i < message.length(); i++) {
        decryptedMessage.push_back(((message.at(i) - key.at(i) + 26) % 26) + 97);
    }
    
    return decryptedMessage;
}