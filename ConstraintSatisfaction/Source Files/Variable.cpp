#include "Variable.h"

Variable::Variable(int id)
{
    m_variableID = id;
	m_row = -1;
	m_col = -1;
	m_length = -1;
	m_isHorizontal = false;
}

Variable::Variable(int id, int row, int col, int length, bool isHorizontal, Domain domain)
{
    m_variableID = id;
    m_row = row;
    m_col = col;
    m_length = length;
    m_isHorizontal = isHorizontal;
    m_domain = domain;
}

Variable::Variable(const Variable& other)
{
    m_variableID = other.m_variableID;
    m_row = other.m_row;
    m_col = other.m_col;
    m_length = other.m_length;
    m_isHorizontal = other.m_isHorizontal;
    m_domain = other.m_domain;
    m_value = other.m_value;
}

void Variable::SetID(int id)
{
    m_variableID = id;
}

void Variable::SetWordLength(int length)
{
    m_length = length;
}

void Variable::SetPosition(int row, int col)
{
    m_row = row;
	m_col = col;
}

void Variable::SetDomain(const Domain& domain)
{
    m_domain = domain;
}

void Variable::SetDirection(bool isHorizontal)
{
	m_isHorizontal = isHorizontal;
}

void Variable::Assign(std::string value)
{
    m_value = value;
}

void Variable::Unassign()
{
    m_value = "";
}

int Variable::GetID()
{
    return m_variableID;
}

int Variable::GetLength()
{
    return m_length;
}

int Variable::GetRow()
{
    return m_row;
}

int Variable::GetCol()
{
    return m_col;
}

std::string Variable::GetWord()
{
    return m_value;
}

Domain Variable::GetDomain()
{
    return m_domain;
}

bool Variable::IsHorizontal()
{
    return m_isHorizontal;
}

void Variable::RemoveWordFromDomain(std::string word)
{
    for (int i = 0; i < m_domain.size(); i++)
    {
        if (m_domain[i] == word)
        {
			m_domain.erase(m_domain.begin() + i);
			break;
		}
	}
}

void Variable::PrintDomain()
{
    std::cout << "Domain: " << std::endl;
    for (const auto& word : m_domain)
    {
		std::cout << "\t- " << word << std::endl;
	}
}

void Variable::Print()
{

}

bool Variable::operator==(const Variable& other) const
{
    if (m_variableID == other.m_variableID &&
        m_row == other.m_row &&
        m_col == other.m_col &&
        m_length == other.m_length &&
        m_isHorizontal == other.m_isHorizontal &&
        m_domain == other.m_domain && 
        m_value == other.m_value) {
        return true;
    }
    else {
        return false;
    }
}

bool Variable::operator!=(const Variable& other) const
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
