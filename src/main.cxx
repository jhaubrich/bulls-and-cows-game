#include <iostream>
#include "FBullsCowsGame.h"

using namespace std;

void Intro();
void PlayGame();
string AskGuess();
void Summary();
bool playAgain();

FBullsCowsGame Game;

int main() {
    do {
        Intro();
        PlayGame();
        Summary();
    } while (playAgain());
}

void Intro() {
    cout << "Welcome to Bulls and Cows!" << endl;
    cout << "I'm thinking of a " << Game.GetSecretWordLength() << " letter isogram.";
    cout <<" You have " << Game.GetMaxTries() << " attempts to guess it. Goodluck!" << endl;
}

bool playAgain() {
    char y_n;
    cout << endl << "Want to play again with the same word? (y/n)" << endl;
    cin >> y_n;
    if (tolower(y_n) == 'y') {
        return true;
    } else {
        return false;
    }

}

string AskGuess() {
    string guess;

    while (true) { // until guess is validate
        cout << endl << "#" << Game.GetCurrentTry() << ": ";
        cin >> guess;
        switch (Game.isValid(guess)) {
        case guessError::OK: {
            return guess;
        }
        case guessError::not_alphas: {
            cout << "Use alphabetic characters when forming your word." << endl;
            break;
        }
        case guessError::not_isogram: {
            cout << "Make sure you aren't repeating any characters." << endl;
            break;
        }
        case guessError::wrong_length: {
            cout << "Your guesses should be " << Game.GetSecretWordLength() << " characters long." << endl;
            break;
        }}

    }
}

void PlayGame() {
    Game.Reset();
    std::string guess;
    FGameState sBullsCows;

    do {
        guess = AskGuess();
        sBullsCows = Game.GetBullsAndCows(guess);
        cout << guess << " has " << sBullsCows.bulls << " bulls and " << sBullsCows.cows << " cows." << endl;
    } while (Game.GetCurrentTry() <= Game.GetMaxTries() && !Game.isWinner());

}

void Summary() {
    if (Game.isWinner()) {
        cout << endl << "YOU WIN!!!" << endl;
    } else {
        cout << "Better luck next time." << endl;
    }
}
