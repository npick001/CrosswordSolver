#include "CrosswordSolver.h"

CrosswordSolver::CrosswordSolver(Crossword* puzzle)
{
	m_puzzle = puzzle;
}

CrosswordSolver::~CrosswordSolver()
{
}

void CrosswordSolver::BacktrackingSolve()
{
	if (m_puzzle) {
		m_puzzleHistory.clear();
		m_wordHistory.clear();
		m_wordHistory.push_back("START");

		cout << "BEGINNING CROSSWORD SOLVER..." << endl;
		bool solved = BacktrackSolveCrossword(m_puzzle, 0);

		if (solved) {
			cout << "Crossword Solved!" << endl;

		}
		else {
			cout << "Couldn't Solve!" << endl;
		}
	}
}

void CrosswordSolver::ForwardCheckingSolve()
{
	// being the implementation of the AC-3 algorithm

	// forward checking propagates information from assigned variables to unassigned variables
	// it does this by checking the domains of the unassigned variables and removing any values
	// that are inconsistent with the assigned variables


}

void CrosswordSolver::PrintSolution()
{
	cout << "Solution:" << endl;
	m_puzzle->print();
}

void CrosswordSolver::PrintSolutionPath()
{
	m_puzzleHistory.push_back(*m_puzzle);
	m_wordHistory.push_back("START");
	cout << "Solution Path:" << endl;

	int step = 0;
	for (Crossword& puzzle : m_puzzleHistory)
	{
		cout << "Step " << step << ": Added " << m_wordHistory[step] << endl;
		puzzle.print();
		cout << endl;
		step++;
	}

	PrintSolution();

	cout << "Final puzzles variables:" << endl;
	for (Variable* var : m_puzzle->GetVariables())
	{
		cout << "Variable " << var->GetID() << ": " << var->GetWord() << endl;
	}
}

bool CrosswordSolver::BacktrackSolveCrossword(Crossword* puzzle, int variableIndex)
{
	cout << "Solving variable " << variableIndex << endl;

	vector<Variable*> variables = puzzle->GetVariables();
	int size = variables.size();

	cout << "Variables size: " << size << endl;

	if (variableIndex >= size)
	{
		// we have been able to assign all the variables
		return true;
	}

	Variable* var = variables[variableIndex];
	Domain variable_domain = var->GetDomain();
	int nextVariableIndex = variableIndex + 1;

	cout << "Variable " << var->GetID() << " has " << variable_domain.size() << " words in its domain" << endl;

	while (variable_domain.size() > 0)
	{
		// get a random word from the variables domain
		int random_index = rand() % variable_domain.size();
		string word = variable_domain[random_index];

		// swap the random word with the last word in the domain to remove it
		std::swap(variable_domain[random_index], variable_domain.back());
		variable_domain.pop_back();

		cout << "Trying to assign " << word << " to variable " << var->GetID() << endl;

		// check each word in the domain to see if it's a valid assignment
		if (IsValidAssignment(m_puzzle, var, word))
		{
			var->Assign(word);
			CommitPuzzleUpdate(var, word);

			cout << "New puzzle:" << endl;
			m_puzzle->print();

			cout << "Next variable index: " << nextVariableIndex << endl;
			if (BacktrackSolveCrossword(m_puzzle, nextVariableIndex))
			{
				cout << "Assigned " << word << " to variable " << var->GetID() << endl;
				m_puzzle->print();
				return true;
			}

			// if we're here, we failed to assign the next variable this word.
			var->Unassign();
			RevertPuzzleUpdate();
		}
		else {
			cout << "Assignment " << word << " is invalid. Moving on..." << endl;
		}
	}

	return false;
}

void CrosswordSolver::CommitPuzzleUpdate(Variable* var, const std::string& word)
{
	Crossword* next_puzzle_step = m_puzzle->UpdatePuzzle(var, word);

	if (next_puzzle_step == NULL) {
		cout << "Error updating puzzle" << endl;
		return;
	}

	cout << "Committing puzzle update: (" << word << ", " << var->GetID() << ")..." << endl;

	cout << "Old puzzle:" << endl;
	m_puzzle->print();

	m_puzzleHistory.push_back(*m_puzzle);
	m_wordHistory.push_back(word);
	*m_puzzle = *next_puzzle_step;
}

void CrosswordSolver::RevertPuzzleUpdate()
{
	// pop the last puzzle off the history
	// set the current puzzle to the last puzzle
	if (m_puzzleHistory.size() > 0)
	{
		cout << "Reverting puzzle update..." << endl;

		cout << "Old puzzle:" << endl;
		m_puzzle->print();

		*m_puzzle = m_puzzleHistory.back();
		m_puzzleHistory.pop_back();
		m_wordHistory.pop_back();

		cout << "New puzzle:" << endl;
		m_puzzle->print();
	}
}

bool CrosswordSolver::IsValidAssignment(Crossword* puzzle, Variable* var, const std::string& word)
{
	// need to check the board and see if each character can fit in the board
	// if the board already has a character there, then we need to make sure it's the same

	// check direction, position, and length of the variable
	bool horizontal = var->IsHorizontal();
	int row = var->GetRow();
	int col = var->GetCol();
	int length = var->GetLength();

	// check if the word fits in the variable space
	if (word.length() != length)
	{
		cout << "Invalid assignment: " << word << " does not fit in variable " << var->GetID() << endl;
		return false;
	}

	// check if the word fits in the board
	if (horizontal) {
		if (col + length > puzzle->GetWidth())
		{
			cout << "Invalid assignment: " << word << " does not fit in variable " << var->GetID() << endl;
			return false;
		}
	}
	else
	{
		if (row + length > puzzle->GetHeight())
		{
			cout << "Invalid assignment: " << word << " does not fit in variable " << var->GetID() << endl;
			return false;
		}
	}

	int current_row = row;
	int current_col = col;

	// check if each character in the word fits in the board
	for (int character = 0; character < length; character++)
	{
		//cout << "Position for character " << character << ": (" << current_row << ", " << current_col << ")" << endl;
		string board_character = puzzle->GetPosition(current_row, current_col);
		string word_character = string(1, word[character]);

		// if the cell is empty or if the cell is the start of a variable and the board char is a number
		// then we can place the word character
		if (puzzle->IsCellEmpty(current_row, current_col) || (puzzle->IsVariableStart(current_row, current_col) && isdigit(board_character[0])))
		{
			// if the board cell is empty, then we can place the word character
			// 
			// Move to the next cell
			if (horizontal) {
				//cout << "Moving to the next column" << endl;
				current_col++;
			}
			else {
				//cout << "Moving to the next row" << endl;
				current_row++;
			}
			continue;
		}
		else if (board_character == word_character)
		{
			// if the board character is the same as the word character, then we can place the word character

			// Move to the next cell
			if (horizontal) {
				//cout << "Moving to the next column" << endl;
				current_col++;
			}
			else {
				//cout << "Moving to the next row" << endl;
				current_row++;
			}
			continue;
		}
		else
		{
			// if the board character is not the same as the word character, then we cannot place the word character
			cout << "Invalid assignment: Board character is not the same as the word character." << endl;
			cout << "Board character: " << board_character << ", Word character: " << word_character << endl;
			return false;
		}
	}

	cout << "Word " << word << " fits in variable " << var->GetID() << endl;

	return true;
}

bool CrosswordSolver::ForwardChecking(Crossword* puzzle, Variable* var, const std::string& word)
{
	for (auto& connected_var : puzzle->GetConnectedVariables(var)) {

		Domain original_domain = connected_var->GetDomain();
		for (const auto& word : original_domain) {
			if (!IsValidAssignment(puzzle, connected_var, word)) {
				connected_var->RemoveWordFromDomain(word);
			}
		}
		
		if (connected_var->GetDomain().empty()) {
			connected_var->SetDomain(original_domain);
			return false;
		}
	}

	return true;
}

bool CrosswordSolver::ForwardCheckSolveCrossword(Crossword* puzzle, int variableIndex)
{
	cout << "Solving variable " << variableIndex << endl;

	vector<Variable*> variables = puzzle->GetVariables();
	int size = variables.size();

	cout << "Variables size: " << size << endl;

	if (variableIndex >= size)
	{
		// we have been able to assign all the variables
		return true;
	}

	Variable* var = variables[variableIndex];
	Domain original_domain = var->GetDomain();
	Domain variable_domain = var->GetDomain();
	int nextVariableIndex = variableIndex + 1;

	cout << "Variable " << var->GetID() << " has " << variable_domain.size() << " words in its domain" << endl;

	while (!variable_domain.empty())
	{
		// get a random word from the variables domain
		int random_index = rand() % variable_domain.size();
		string word = variable_domain[random_index];

		// swap the random word with the last word in the domain to remove it
		std::swap(variable_domain[random_index], variable_domain.back());
		variable_domain.pop_back();

		cout << "Trying to assign " << word << " to variable " << var->GetID() << endl;

		// check each word in the domain to see if it's a valid assignment
		if (IsValidAssignment(m_puzzle, var, word))
		{
			var->Assign(word);
			CommitPuzzleUpdate(var, word);

			cout << "New puzzle:" << endl;
			m_puzzle->print();

			if (ForwardChecking(m_puzzle, var, word))
			{
				cout << "Forward checking succeeded..." << endl;
				cout << "Moving to next variable..." << endl;
				if (ForwardCheckSolveCrossword(m_puzzle, nextVariableIndex)) {
					return true;
				}
			}

			// if we're here, we failed to assign the next variable this word.
			var->Unassign();
			RevertPuzzleUpdate();
			var->SetDomain(original_domain);
		}
		else {
			cout << "Assignment " << word << " is invalid. Moving on..." << endl;
		}
	}

	return false;
}

