#pragma once
#include <string>
#include <vector>
#include <iostream>

typedef std::vector<std::string> Domain;

class Variable
{
public:
	Variable(int id);
	Variable(int id, int row, int col, int length, bool isHorizontal, Domain domain);
	Variable(const Variable& other);
	~Variable() = default;

	void Assign(std::string value);
	void Unassign();
	bool IsHorizontal();
	void RemoveWordFromDomain(std::string word);

	void PrintDomain();
	void Print();

	void SetID(int id);
	void SetWordLength(int length);
	void SetPosition(int row, int col);
	void SetDomain(const Domain& domain);
	void SetDirection(bool isHorizontal);

	int GetID();
	int GetLength();
	int GetRow();
	int GetCol();
	std::string GetWord();
	Domain GetDomain();

	bool operator==(const Variable& other) const;
	bool operator!=(const Variable& other) const;

protected:
	int m_variableID;
	int m_row;
	int m_col;
	int m_length;
	bool m_isHorizontal;
	Domain m_domain;
	std::string m_value;
};
