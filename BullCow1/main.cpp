#include <iostream>
#include <string>
#include "FBullCowGame.h"

using namespace std;


#define cout std::cout
#define endl std::endl
#define cin std::cin
using FText = std::string;
using int32 = int;


//echivalent cu BCGame din video
FBullCowGame GameObj1;


bool AskToChangeWordLength() {
	cout << "Do you want to change the number of letters in the word Y/N ? ";
	FText ding = "";
	int32 wordLength;
	getline(cin, ding);
	if (ding[0] == 'y' || ding[0] == 'Y') {
			do {	
			cout << "Please enter a number from 3 to 8: ";
			cin >> wordLength;
			cin.ignore();
			} while (wordLength < 3 || wordLength>8);
		
		GameObj1.SetWordSize(wordLength);
		cout << "\n\n";
		return true;
	}
	else return false;
	
}




//Introduces The Game Title
void PrintIntro() {
	cout << "Welcome to Bulls and Cows, a fun word game.\n";
	cout << endl;
	cout << "          }   {                   ___ " << endl;
	cout << "          (o o)                  (o o) " << endl;
	cout << "   /-------\\ /                    \\ /-------\\ " << endl;
	cout << "  / | BULL |O                      O| COW  | \\ " << endl;
	cout << " *  |-,--- |                        |------|  * " << endl;
	cout << "    ^      ^                        ^      ^ " << endl;

	cout << endl;

	cout << "Can you guess the " << GameObj1.GetHiddenWordLength() << " letter isogram I'm thinking of?\n\n\n";
	return;
}





//Loop Until user gives a valid guess
FText GetValidGuess() { 
	FText Guess1 ;
	EGuessSatus Status = EGuessSatus::Invalid;
	do {
		//get a guess from the player
		int32 CurrentTry = GameObj1.GetCurrentTry();
		cout << endl;
		cout << "Try " << CurrentTry <<" of "<<GameObj1.GetMaxTries()<< " : Enter your guess:" ;
		getline(cin, Guess1);
		cout << endl;
		Status = GameObj1.CheckGuessValidity(Guess1);
		switch (Status) {
		case EGuessSatus::OK:

			break;
		case EGuessSatus::Not_Isogram:
			cout << "Please enter a word without repeating letters.\n ";
			break;
		case EGuessSatus::Wrong_Length:
			cout << "Please enter a " << GameObj1.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessSatus::Not_Lower_Case:
			cout << "Please enter all lower case letters. \n";
			break;
		default:
			//asume the guess is valid
			break;
		}
		cout << "\n";
	} while (Status != EGuessSatus::OK); //keep loping until we get no errors
	return Guess1;
}


//Returns True for Y, false for anything else on whant to play again?
bool AskToPlayGame() {
	cout << "\n\n\nWant to play again Y/N? " << endl;
	string Response = "";
	getline(cin, Response);
	if (Response[0] == 'y' || Response[0] == 'Y') {
		return true;
	}

	else return false;
}


void PrintGameSummary() {
	if (GameObj1.isGameWon()) {
		cout << "You WIN!!! " << "You WIN!!!" << endl << endl;
	}
	else {
		cout << "\n\nYOU LOSE!!! Better luck next time.\n\n";
	}
	
}

//PlayGame Function
void PlayGame() {
	
	AskToChangeWordLength();

	GameObj1.Reset();
	cout << "Please enter a " << GameObj1.GetHiddenWordLength() << " letter word.\n";
	int32 MaxTries = GameObj1.GetMaxTries();// turns number In a Game
	FBullCowCount BullCowCount;
		// loop for number of turns and while the game is NOT won
		while(!GameObj1.isGameWon() && GameObj1.GetCurrentTry() <= MaxTries) {

			FText Guess = GetValidGuess(); 

			//submit valid guess and recieve count number
			BullCowCount= GameObj1.SubmitValidGuess(Guess);

			if (!GameObj1.isGameWon()) {
				cout << "";
				cout << "Bulls(Right Place) =" << BullCowCount.Bulls <<" "<<BullCowCount.RightPlacedLetters << endl;
				cout << endl;
				cout << "Cows(Right Letter) =" << BullCowCount.Cows <<" "<<BullCowCount.RightLetters<< endl;
				cout << endl << endl;
			}
				
		}
		PrintGameSummary();
}

int facCeva()
{
	cout << "facem ceva";
	return 0;
}

int main() {

	
	
	PrintIntro();

	do {
		PlayGame();
	} while (AskToPlayGame());


	return 0;
}