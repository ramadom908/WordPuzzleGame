#include "FBullCowGame.h"


FBullCowGame::FBullCowGame()
{
	SetWordSize(4);
	Reset();
}

//getters implemented inline

int32 FBullCowGame::GetCurrentTry()const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::isGameWon()const { return bGameIsWon; }

int32 FBullCowGame::GetWordSize() const {
	return WordSize;
}

void FBullCowGame::SetWordSize(int wordSize) {
	WordSize=wordSize;
}



int32 FBullCowGame::GetMaxTries()const { 
	
	TMap<int32, int32>WordLengthMaxTries{ {3, 6}, {4, 7}, {5, 8}, {6, 10}, {7, 15}, {8,20} };
	return WordLengthMaxTries[MyHiddenWord.length()];
	

}


void FBullCowGame::Reset()
{

	TMap<int32, FString> dictionary{ {3, "ant"}, {4, "body"}, {5, "mouse"}, {6, "planet"}, {7, "kingdom"}, {8, "confused"} };
	MyHiddenWord = dictionary.at(GetWordSize());
	constexpr int32 MaxTries = 5; // to prevent magic numbers
	constexpr int32 CurrentTry = 1; // to prevent magic numbers

	MyCurrentTry = CurrentTry;
	MyMaxTries = MaxTries;
	bGameIsWon = false;
	return;
}


EGuessSatus FBullCowGame::CheckGuessValidity(FString Guess)const
{

	if (!isIsogram(Guess)) //if not isogram
	{ 
		return EGuessSatus::Not_Isogram;
	}
	else if(!isLowercase(Guess)) // not all lowercase
	{ 
		return EGuessSatus::Not_Lower_Case;
	}
	else if(Guess.length()!=GetHiddenWordLength()) //guess length wrong
	{ 
		return EGuessSatus::Wrong_Length;
	}
	else 
	{
		return EGuessSatus::OK;
	}
}

//recives a valid Guess, increments turn and returns count number
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	int32 WordLength = MyHiddenWord.length();// assuming same length as guess

	//loop through all letters in the HiddenWord
	for (int32 i = 0; i < WordLength; i++) {
		bool noBullsFound = true;
		//loop through all letters in the guess
		for (int32 j = 0; j < WordLength; j++) {
			if (MyHiddenWord[i] == Guess[j])
				if (i == j) {
					BullCowCount.Bulls++;
					BullCowCount.RightPlacedLetters.push_back(Guess[j]);
					noBullsFound = false;
				}
				else {
					BullCowCount.RightPlacedLetters.push_back('-');
					BullCowCount.RightLetters.push_back(Guess[j]);
					BullCowCount.Cows++;
					noBullsFound = false;
				}
		}
		if(noBullsFound) // if no bulls found put a " - " in place of a letter
			BullCowCount.RightPlacedLetters.push_back('-');
		
	}
	if (WordLength == BullCowCount.Bulls)
		bGameIsWon = true;
	else
		bGameIsWon = false;

	return BullCowCount;
}


//destructor empty
FBullCowGame::~FBullCowGame()
{
}

bool FBullCowGame::isIsogram(FString word) const {

	if (word.length() <= 1)
		return true;

	TMap <char, bool> LetterSeen;

	//ranged base for 
	for (auto letter :word ) {
		// converts letters to lowecase
		letter = tolower(letter);
		//if letter has been seen before
		if (LetterSeen[letter]==true)
			return false; // meaning is not isogram;
		else {
			LetterSeen[letter] = true; // meaning is isogram
		}
	}

	return true;
}

bool FBullCowGame::isLowercase(FString word) const {

	if (word.length() <= 1)
		return true;

	//ranged base for 
	for (auto letter : word) {
		if (!islower(letter))
			return false;
	}
	return true;
}


