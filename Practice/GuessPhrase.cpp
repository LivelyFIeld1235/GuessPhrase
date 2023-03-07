#include <cmath>
#include <iostream>
#include <cmath>
#include <string>
#include <ctime>
#include <set>

using namespace std;

static int GuessAvailable = 6;

string generateWord() {
    srand(static_cast<unsigned int>(time(nullptr)));
    string arr[10] = {"upgrade", "health low", "boss fight", "dungeon", "enemy targeted"};
    return arr[rand() % 4];
}   

string placeholder(string word) {
    string placeholder = "";
    for (int i = 0; i < word.length();i++) {
        if (word[i] != ' ') {
            placeholder += "_ ";
        }
        else {
            placeholder += "  ";
        }
        
    }
    return placeholder;
}

int check(string* lettersGuessed, string word, char letter) {
    // -1 means letter alreay guessed, 1 means letter is in, 11 means you won, 0 means letter not in word
    set<char> LettersAlreadyGuessed;
    const int convFAC = 2;
    for (int i = 0; i < (*lettersGuessed).length(); i++) {
        if (letter == (*lettersGuessed)[i]) {
            return -1;
        } 
        if ((*lettersGuessed)[i] != ' ' && (*lettersGuessed)[i] != '_') {
            LettersAlreadyGuessed.insert((*lettersGuessed)[i]);
        }
        else if ((static_cast<double>(i) / convFAC) == (i / convFAC) && letter == word[i/ convFAC]) {
            (*lettersGuessed)[i] = word[i / convFAC];
            for (int i = 0; i < word.length(); i++) {
                if (letter == word[i]) {
                    (*lettersGuessed)[i * 2] = letter;
                }
            }
            return 1;
        
        }
    }
    GuessAvailable--;
    return 0;
}
int is_Win(string lettersGuessed) {
    if (lettersGuessed.find('_') == string::npos) {
        return 1;
    }
    else if (GuessAvailable == 0){
        return 0;
    }
    else {
        return -1;
    }

}

void drawMannequin() {
    string padding = "       ";
    switch (GuessAvailable) {
    case 5:
        cout << padding + "O" << endl;
        break;

    case 4:
        cout << padding + "O" << endl;
        cout << padding.erase(0, 1) + "-" << endl;
        break;

    case 3:
        cout << padding + "O" << endl;
        cout << padding.erase(0, 1) + "|-" << endl;
        break;

    case 2:
        cout << padding + "O" << endl;
        cout << padding.erase(0, 1) + "|-|" << endl;
        break;

    case 1:
        cout << padding + "O" << endl;
        cout << padding.erase(0, 1) + "|-|" << endl;
        cout << padding.erase(0, 1) + "_/" << endl;
        break;

    case 0:
        cout << padding + "O" << endl;
        cout << padding.erase(0, 1) + "|-|" << endl;
        cout << padding.erase(0, 1) + "_/ \\_" << endl;
        break;
    }
}

int main()
{
    string word = generateWord();
    string lettersGuessed = placeholder(generateWord());
    drawMannequin();
    while (is_Win(lettersGuessed) == -1) {
        cout << word << endl;
        cout << lettersGuessed << endl;
        char guess;
        cout << "enter a guess" << endl;
        cin >> guess;
        int is_in = check(&lettersGuessed, word, guess);

        if (is_in == -1) {
            cout << "letter has been already guessed please try again" << endl;
            drawMannequin();
        }
        else if (is_in == 0) {
            cout << "letter is not in the phrase or word, please try again " << to_string(GuessAvailable) + " guesses remaining" << endl;
            drawMannequin();
        }
        else if (is_in == 1) {
            drawMannequin();

        }
    }
    if (is_Win(lettersGuessed) == true) {
        cout << lettersGuessed << endl;
        cout << "You won" << endl;
    }
    else if (is_Win(lettersGuessed) == false) {
        cout << lettersGuessed << endl;
        cout << "you lost" << endl;
    }
    return 0;
}

