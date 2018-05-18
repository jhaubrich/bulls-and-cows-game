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
    std::cout << "  ________________________________________"          << std::endl;
    std::cout << "/ Welcome to Bulls and Cows, a fun word    \\"       << std::endl;
    std::cout << "| game! Can you guess the ";
    std::cout << Game.GetSecretWordLength() << " letter isogram |"     << std::endl;
    std::cout << "\\ I'm thinking of?                         /"       << std::endl;
    std::cout << "  ----------------------------------------"          << std::endl;
    std::cout << "         \\   ^__^ "                                 << std::endl;
    std::cout << "          \\  (oo)\\_______"                         << std::endl;
    std::cout << "             (__)\\       )\\ / \\"                  << std::endl;
    std::cout << "                 ||----w |"                          << std::endl;
    std::cout << "                 ||     ||"                          << std::endl;
    std::cout << std::endl;
    return;
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

    map<guessError, string> errorMessages {
        {guessError::OK, ""},
        {guessError::not_alphas, "Use alphabetic characters when forming your word."},
        {guessError::not_isogram, "Make sure you aren't repeating any characters."},
        {guessError::wrong_length, "Your guesses should be " + to_string(Game.GetSecretWordLength()) + " characters long."}
    };

    while (true) {
        cout << endl << "#" << Game.GetCurrentTry() << ": ";
        cin >> guess;

        if (Game.isValid(guess) == guessError::OK) {
            return guess;
        } else {
            cout << errorMessages[Game.isValid(guess)] << endl;
        }
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
