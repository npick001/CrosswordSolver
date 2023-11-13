#include "Crossword.h"

Crossword::Crossword(const string& filename)
{
	ifstream file(filename);

	if (file.is_open())
	{
		string line;
		int line_number = 0;
		while (getline(file, line))
		{
			vector<string> row;
			
			// each line will be either a character or a string and then a comma to separate it.
			// we are only interested in the strings, so we will ignore all commas delimiting the string separations.

			string word = "";
			string id = "";
			for (int i = 0; i < line.size(); i++)
			{
				if (line[i] == ',')
				{
					row.push_back(word);

					if (isdigit(id[0])) {
						Variable* var = new Variable(std::stoi(id));
						var->SetPosition(line_number, static_cast<int>(row.size()) - 1);
						m_variables.push_back(var);
					}

					word = "";
					id = "";
				}
				else if (isdigit(line[i]))
				{
					// create a variable and add it to the list of variables
					id += line[i];
					word += line[i];
				}
				else
				{
					word += line[i];
				}
			}

			m_width = static_cast<int>(row.size());
			m_crossword.push_back(row);
			line_number++;
		}
		m_height = line_number;
	}
	else
	{
		cout << "Unable to open file " << filename << endl;
	}
}

Crossword::Crossword(const Crossword& other)
{
	m_width = other.m_width;
	m_height = other.m_height;
	m_crossword = other.m_crossword;

	for (Variable* var : other.m_variables)
	{
		m_variables.push_back(new Variable(*var));
	}
}

Crossword::~Crossword()
{
}

Crossword* Crossword::UpdatePuzzle(Variable* var, const string& word)
{
	Crossword* new_puzzle = new Crossword(*this);

	int row = var->GetRow();
	int col = var->GetCol();
	int length = var->GetLength();
	bool horizontal = var->IsHorizontal();

	if (horizontal)
	{
		// make sure the word doesnt leave the x bounds of the puzzle
		if (col + length > m_width)
		{
			return nullptr;
		}

		for (int i = 0; i < length; i++)
		{
			new_puzzle->m_crossword[row][col + i] = word[i];
		}
	}
	else
	{
		// make sure the word doesnt leave the y bounds of the puzzle
		if (row + length > m_height)
		{
			return nullptr;
		}

		for (int i = 0; i < length; i++)
		{
			new_puzzle->m_crossword[row + i][col] = word[i];
		}
	}

	return new_puzzle;
}

void Crossword::print()
{
	for (int i = 0; i < 2 * (m_width + m_width / 2)-1; i++)
	{
		cout << "-";
	}
	cout << endl;

	// print the characters in the crossword
	for (const auto& row : m_crossword)
	{
		cout << "| ";
		for (const auto& word : row)
		{
			cout << word << " ";
		}
		cout << "|" << endl;
	}
		
	for (int i = 0; i < 2 * (m_width + m_width / 2)-1; i++)
	{
		cout << "-";
	}
	cout << endl;
}

bool Crossword::IsCellEmpty(int row, int col)
{
	if (m_crossword[row][col] == " ")
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Crossword::SetVariables(vector<Variable*> variables)
{
	m_variables = variables;
}

int Crossword::GetWidth()
{
	return m_width;
}

int Crossword::GetHeight()
{
	return m_height;
}

vector<Variable*> Crossword::GetVariables()
{
	return m_variables;
}

string Crossword::GetPosition(int row, int col)
{
	if (IsVariableStart(row, col) && IsCellEmpty(row, col))
	{
		return " ";
	}
	else {
		return m_crossword[row][col];
	}
}

vector<Variable*> Crossword::GetConnectedVariables(Variable* var)
{
	vector<int> variable_ids;
	vector<Variable*> connected_variables;
	int row = var->GetRow();
	int col = var->GetCol();

	// check the row
	for (int i = col; i < m_width; i++)
	{
		if (IsVariableStart(row, i))
		{
			variable_ids.push_back(std::stoi(m_crossword[row][i]));
		}
	}

	// check the column
	for (int i = row; i < m_height; i++)
	{
		if (IsVariableStart(i, col))
		{
			variable_ids.push_back(std::stoi(m_crossword[i][col]));
		}
	}

	// check the variables list and see if any of the ids match
	for (Variable* var : m_variables)
	{
		for (int id : variable_ids)
		{
			if (var->GetID() == id)
			{
				connected_variables.push_back(var);
			}
		}
	}

	return connected_variables;
}

bool Crossword::operator==(const Crossword& other) const
{
	if (m_width == other.m_width &&
		m_height == other.m_height &&
		m_crossword == other.m_crossword)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Crossword::operator!=(const Crossword& other) const
{
	if (*this == other)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Crossword::IsVariableStart(int row, int col)
{
	// check every variable and see if it starts at this position

	for (Variable* var : m_variables)
	{
		if (var->GetRow() == row && var->GetCol() == col)
		{
			return true;
		}
	}

	return false;
}
