#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "Variable.h"

using namespace std;

class Crossword
{
public:
	Crossword(const string& filename);
	Crossword(const Crossword& other);
	~Crossword();

	void print();
	bool IsCellEmpty(int row, int col);
	bool IsVariableStart(int row, int col);

	// this function will update the puzzle with the new word
	// IF THE WORD DOES NOT FIT, THIS FUNCTION WILL RETURN NULL
	Crossword* UpdatePuzzle(Variable* var, const string& word);

	void SetVariables(vector<Variable*> variables);

	int GetWidth();
	int GetHeight();
	vector<Variable*> GetVariables();
	string GetPosition(int row, int col);
	vector<Variable*> GetConnectedVariables(Variable* var);

	bool operator==(const Crossword& other) const;
	bool operator!=(const Crossword& other) const;

protected:

private:
	int m_width;
	int m_height;
	vector<vector<string>> m_crossword;
	vector<Variable*> m_variables;
};

