#pragma once
#include <string>
#include <map>
#include<vector>
#define TMap std::map

using FString = std::string;
using int32 = int;


int facCeva();

enum class EGuessSatus {
	Invalid, OK, Not_Isogram, Wrong_Length, Not_Lower_Case
};

// 2 integers initalized to 0 + 2 strings
struct FBullCowCount {
	FString RightPlacedLetters;
	FString RightLetters;
	int32 Bulls = 0;
	int32 Cows = 0;
};


class FBullCowGame
{
public:
	FBullCowGame(); //Constructor

	int32 GetMaxTries()const;
	int32 GetCurrentTry()const;
	int32 GetHiddenWordLength()const;
	EGuessSatus CheckGuessValidity(FString)const; 
	bool isGameWon()const;

	int32 GetWordSize()const;
	void SetWordSize(int wordSize);

	void Reset(); 
	

	FBullCowCount SubmitValidGuess(FString);

	~FBullCowGame();

private:
	bool isIsogram(FString)const;
	bool isLowercase(FString)const;

private:
	//see constructor for initaializare, Constructor calls Reset

			//Try Counter
	 int32 MyCurrentTry;
	 int32 MyMaxTries;
	 FString MyHiddenWord;
	 bool bGameIsWon;
	 int32 WordSize;
};

