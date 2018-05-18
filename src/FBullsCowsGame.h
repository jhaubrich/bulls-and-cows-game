#pragma once
#include <iostream>
#include <map>

using FString = std::string;

struct FGameState {
    int bulls = 0;
    int cows  = 0;
};

enum class guessError {
    wrong_length,
    not_isogram,
    not_alphas,
    OK
};

class FBullsCowsGame
{
 public:
    FBullsCowsGame() {Reset(3);}

    void Reset(int);
    bool isIsogram(FString);
    bool isAlphas(FString);
    guessError isValid(FString);
    bool isWinner();

    int GetMaxTries();
    int GetCurrentTry() const {return currenttry;}
    int GetSecretWordLength() const {return secretWord.length();}
    FString GenerateSecretWord(int);

    FGameState GetBullsAndCows(FString);

 private:
    int currenttry;
    FString secretWord = "planet";
    FGameState sBullsCows;
    bool bWin = false;
};


void FBullsCowsGame::Reset(int difficulty) {
    currenttry = 1;
    bWin = false;
    secretWord = GenerateSecretWord(difficulty);
}

int FBullsCowsGame::GetMaxTries() {
    std::map<int,int> wordLenToMaxTries { {3,5}, {4,10}, {5,15}, {6,20} };
    return wordLenToMaxTries[secretWord.length()];
}

FString FBullsCowsGame::GenerateSecretWord(int difficulty) {
    std::map<int, FString> secretWords {
        {3, "ply"}, {4, "plan"}, {5, "plane"}, {6, "planet"}, {7, "planets"}
    };
    return secretWords[difficulty];
}


guessError FBullsCowsGame::isValid(FString guess) {
    // validate guess -- wordlength? Isogram? valid_chars?
    if (guess.length() != secretWord.length()) {
        return guessError::wrong_length;
    }
    else if (!isAlphas(guess)) {
        return guessError::not_alphas;
    }
    else if (!isIsogram(guess)) {
        return guessError::not_isogram;
    }
    else {
        return guessError::OK;
    }
};


bool FBullsCowsGame::isIsogram(std::string guess) {
    std::map<char, int> letters;

    for (auto letter : guess){
        letters[letter]++;
        if (letters[letter] > 1) {
            return false;
        }
    }
    return true;  // todo implement
}

bool FBullsCowsGame::isAlphas(FString guess) {
    // http://www.asciitable.com/
    for (auto l : guess) {
        if (tolower(l) < 97 || tolower(l) > 122) {
            return false;
        }
    }
    return true; // todo implement
}

bool FBullsCowsGame::isWinner() {
    return bWin;
}

FGameState FBullsCowsGame::GetBullsAndCows(FString vaildGuess) {
    currenttry++;
    sBullsCows.bulls = 0;
    sBullsCows.cows = 0;
    // did they win?
    // should we validate here?
    for (auto i = 0; i < vaildGuess.length(); ++i) {
        for (auto j = 0; j < secretWord.length(); ++j) {
            if (vaildGuess[i] == secretWord[j]) {
                if (i == j) {
                    sBullsCows.bulls++;
                }
                else {
                    sBullsCows.cows++;
                }
            }
        }
    }

    if (sBullsCows.bulls == secretWord.length()) {
        bWin = true;
    }
    return sBullsCows;
}
