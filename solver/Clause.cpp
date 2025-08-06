//
// Created by kumth on 8/4/2025.
//

#include "Clause.h"

bool Clause::checkVariableInClause(int var_index) const
{
    if(literalContainer.count(var_index)==false)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Clause::addVariable(Variable new_literal)
{
    if(checkVariableInClause(new_literal.varIndex))
    {
        // INDICATES TWO LITERALS OF SAME VAR WITH DIFFERING POLARITY, CLAUSE TRIVIALLY TRUE
        if(literalContainer[new_literal.varIndex]*new_literal.varIndex<0)
        {
            return false;
        }
        else
        {
            return true;
        }

    }
    if(!watchedFirst.has_value())
    {

        watchedFirst=new_literal;
        clauseLength++;
        if(watchedFirst->polarity)
        {
            literalContainer[watchedFirst->varIndex]=1;
        }
        else
        {
            literalContainer[watchedFirst->varIndex]=-1;
        }

        literals.push_back(new_literal);
        return true;
    }
    else if(!watchedSecond.has_value())
    {

            watchedSecond=new_literal;
            clauseLength++;
            if(watchedSecond->polarity)
            {
                literalContainer[watchedSecond->varIndex]=1;
            }
            else
            {
                literalContainer[watchedSecond->varIndex]=-1;
            }
            literals.push_back(new_literal);
            return true;

    }
    else
    {
        if(!checkVariableInClause(new_literal.varIndex))
        {
            clauseLength++;
            if(new_literal.polarity)
            {
                literalContainer[new_literal.varIndex]=1;
            }
            else
            {
                literalContainer[new_literal.varIndex]=-1;
            }
            literals.push_back(new_literal);
            return true;

        }
    }
    return  false;
}

void Clause::debugPrint()
{
    std::cout << "Clause ID: " << clauseId << "\n";
    std::cout << "Literals: ";
    for (const auto& literal : literals) {
        std::cout << (literal.polarity ? "" : "-") << literal.varIndex << " ";
    }
    std::cout << "\n";
}
