#include <iostream>
#include "FBullsCowsGame.h"

using namespace std;

void Intro();
void PlayGame();
int AskDifficulty();
string AskGuess();
void Summary();
bool PlayAgain();

FBullsCowsGame Game;

int main() {
    do {
        Game.Reset(AskDifficulty());
        Intro();
        PlayGame();
        Summary();
    } while (PlayAgain());
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
    std::cout << "             (__)\\       )\\/\\"                    << std::endl;
    std::cout << "                 ||----w |"                          << std::endl;
    std::cout << "                 ||     ||"                          << std::endl;
    std::cout << std::endl;
    return;
}

bool PlayAgain() {
    char y_n;
    cout << endl << "Want to play again? (y/n)" << endl;
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

int AskDifficulty() {
    int difficulty = 0;
    do {
        cout << "How big a word can you handle (3-7)? ";
        cin >> difficulty;
    } while (difficulty < 3 || difficulty > 7);
    return difficulty;
}

void PlayGame() {
    std::string guess;
    FGameState sBullsCows;

    do {
        guess = AskGuess();
        sBullsCows = Game.GetBullsAndCows(guess);
        cout << guess << " has " << sBullsCows.bulls << " bulls and "
                                 << sBullsCows.cows  << " cows." << endl;
    } while (Game.GetCurrentTry() <= Game.GetMaxTries() && !Game.isWinner());
}

void Summary() {
    if (Game.isWinner()) {
        cout <<"  ______________ "                     << endl;
        cout <<"/                \\"                     << endl;
        cout <<"|   YOU WIN!!!   |"                    << endl;
        cout <<"\\                /"                     << endl;
        cout <<"  -------------- "                     << endl;
        cout <<"        \\  \\^__^/"                   << endl;
        cout <<"         \\  (00)\\_______"            << endl;
        cout <<"            (__)\\       )\\/\\"       << endl;
        cout <<"                ||----, |"             << endl;
        cout <<"                ||     ||"             << endl;

    } else {
        cout <<" ________________________"             << endl;
        cout <<"< Better luck next time. >"            << endl;
        cout <<" ------------------------"             << endl;
        cout <<"        \\   ^__^"                     << endl;
        cout <<"         \\  (xx)\\_______"            << endl;
        cout <<"            (__)\\       )\\/\\"       << endl;
        cout <<"             U  ||----w |"             << endl;
        cout <<"                ||     ||"             << endl;

    }
}
