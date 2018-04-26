/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interactions. For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string; // used in unreal
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintGameSummary();
bool AskToPlayAgain();

FBullCowGame BCGame; //instantiate a new game

// entry point of the appication
int main () 
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain);

	// exit application without errors
	return 0;
}

void PrintIntro ()
{
	// introduce the game
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogame I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

void PlayGame () 
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while the game is NOT won
	// and there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		// get a guess from the player
		FText Guess = GetValidGuess(); // TODO make loop check for valid guesses

		// submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}

// loop continually untill the user gives a valid guess
FText GetValidGuess()
{
	int32 CurrentTry = BCGame.GetCurrentTry();
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid;
	do
	{
		// get a guess from the player
		std::cout << "Try " << CurrentTry << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n";
			break;	
		default:
			// assume the guess is valid
			break;
		}
		std::cout << std::endl;
	} 
	while (Status != EGuessStatus::OK); // keep looping until we get no errors

	return Guess;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon()) 
	{
		std::cout << "WELL DONE - YOU WIN!\n";
	}
	else 
	{
		std::cout << "Better luck next time!\n";
	}
	std::cout << std::endl;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word? (y/n) ";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}
