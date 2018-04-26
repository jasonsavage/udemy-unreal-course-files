#include "FBullCowGame.h"
#include <cctype>
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 5;
	const FString HIDDEN_WORD = "planet";

	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) 
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (false) // if the guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) // if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	int32 GuessLength = Guess.length();
	// Treat 0 and 1 as isograms
	if (GuessLength <= 1) { return true; }
	// setup map
	TMap<char, bool> LetterSeen;
	for (auto Letter : Guess) // for all letters of the word
	{
		Letter = std::tolower(Letter);
		if (LetterSeen[Letter])
		{
			return false; // we do not have an isogram
		}
		else
		{
			LetterSeen[Letter] = true; // add the letter to the map
		}
	}

	return true;
}

// recives a VALID guess, increments turn and retuns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length();

	// loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		// compare letters against the hidden word
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				// if they're in the same place
				if (MHWChar == GChar)
				{
					// incriment bulls 
					BullCowCount.Bulls++;
				}
				else
				{
					// incriment cows 
					BullCowCount.Cows++;
				}
			}
		}
	}

	bGameIsWon = (BullCowCount.Bulls == WordLength);

	return BullCowCount;
}

