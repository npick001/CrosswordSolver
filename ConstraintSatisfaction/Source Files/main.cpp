#include "Crossword.h"
#include "CrosswordSolver.h"

void PopulateStartingDomains(Crossword* puzzle);

int main()
{
	srand(static_cast<unsigned int>(time(NULL)));

	//Crossword* small_puzzle = new Crossword("Crossword Puzzles\\crossword1.txt");
	//small_puzzle->print();
	//PopulateStartingDomains(small_puzzle);

	//CrosswordSolver* small_puzzle_solver = new CrosswordSolver(small_puzzle);
	//small_puzzle_solver->BacktrackingSolve();
	//small_puzzle_solver->PrintSolutionPath();

	//// solver will delete the puzzle 
	//delete small_puzzle_solver;

	Crossword* medium_puzzle = new Crossword("Crossword Puzzles\\crossword2.txt");
	medium_puzzle->print();


	CrosswordSolver* medium_puzzle_solver = new CrosswordSolver(medium_puzzle);
	medium_puzzle_solver->ForwardCheckingSolve();
	medium_puzzle_solver->PrintSolutionPath();


	return 0;
}

void PopulateStartingDomains(Crossword* puzzle)
{
	vector<Variable*> variables = puzzle->GetVariables();

	vector<string> words_3Letters = { "AFT", "ALE", "EEL", "LEE", "TIE" };
	vector<string> words_4Letters = { "HEEL", "HIKE", "KEEL", "KNOT", "LINE" };
	vector<string> words_5Letters = { "HOSES", "LASER", "SAILS", "SHEET", "STEER" };

	// set the domains for the first puzzle
	for (int index = 0; index < variables.size(); index++)
	{
		Variable* var = variables[index];

		switch (var->GetID())
		{
		case 1:
			var->SetWordLength(5);
			var->SetDomain(words_5Letters);
			var->SetDirection(true);
			break;
		case 2:
			var->SetWordLength(5);
			var->SetDomain(words_5Letters);
			var->SetDirection(false);
			break;
		case 3:
			var->SetWordLength(5);
			var->SetDomain(words_5Letters);
			var->SetDirection(false);
			break;
		case 4:
			var->SetWordLength(4);
			var->SetDomain(words_4Letters);
			var->SetDirection(true);
			break;
		case 5:
			var->SetWordLength(4);
			var->SetDomain(words_4Letters);
			var->SetDirection(false);
			break;
		case 6:
			var->SetWordLength(3);
			var->SetDomain(words_3Letters);
			var->SetDirection(false);
			break;
		case 7:
			var->SetWordLength(3);
			var->SetDomain(words_3Letters);
			var->SetDirection(true);
			break;
		case 8:
			var->SetWordLength(5);
			var->SetDomain(words_5Letters);
			var->SetDirection(true);
			break;
		}

		cout << "Variable " << var->GetID() << " has " << var->GetDomain().size() << " words in its domain" << endl;
	}

	puzzle->SetVariables(variables);
}