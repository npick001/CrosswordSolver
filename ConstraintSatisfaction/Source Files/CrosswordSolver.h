#pragma once
#include <deque>
#include <cstdlib>
#include "Crossword.h"

class CrosswordSolver
{
public:
	CrosswordSolver(Crossword* puzzle);
	~CrosswordSolver();

	// solve the crossword by starting with the first variable and
	// recursively calling Assign on the next variable until all
	// variables are assigned
	// we try to assign all variables based on their ID, until a variables domain
	// as been reduced to 0, then we backtrack and 
	void BacktrackingSolve();

	// using the arc consistency algorithm AC-3, we will reduce the domains of
	// the variables until we have a solution
	void ForwardCheckingSolve();

	void PrintSolution();
	void PrintSolutionPath();

protected:
	void CommitPuzzleUpdate(Variable* var, const std::string& word);
	void RevertPuzzleUpdate();

	// recursive function that assigns a word to a variable and then
	// calls itself on the next variable
	// if the assignment is invalid, it will revert the assignment and return false
	bool BacktrackSolveCrossword(Crossword* puzzle, int variableIndex);
	bool IsValidAssignment(Crossword* puzzle, Variable* var, const std::string& word);

	bool ForwardChecking(Crossword* puzzle, Variable* var, const std::string& word);
	bool ForwardCheckSolveCrossword(Crossword* puzzle, int variableIndex);

private:
	Crossword* m_puzzle;
	std::deque<Crossword> m_puzzleHistory;
	std::deque<std::string> m_wordHistory;
};

