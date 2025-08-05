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

void Clause::addVariable(Variable new_literal)
{
    if(!watchedFirst.has_value())
    {
        watchedFirst=new_literal;
        clauseLength++;
        literalContainer[watchedFirst->varIndex]=true;
        literals.push_back(new_literal);
        return;
    }
    else if(!watchedSecond.has_value())
    {
        if(!checkVariableInClause(new_literal.varIndex))
        {
            watchedSecond=new_literal;
            clauseLength++;
            literalContainer[watchedSecond->varIndex]=true;
            literals.push_back(new_literal);
            return;
        }
        else
        {
            return;
        }
    }
    else
    {
        if(!checkVariableInClause(new_literal.varIndex))
        {
            clauseLength++;
            literalContainer[new_literal.varIndex]=true;
            literals.push_back(new_literal);
            return;

        }
    }

}
