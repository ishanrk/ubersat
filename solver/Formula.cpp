//
// Created by kumth on 8/4/2025.
//

#include "Formula.h"

void Formula::addClause(Clause currClause)
{
    numClauses++;
    currClause.clauseId = numClauses;
    clauseList.push_back(currClause);
    if(currClause.watchedFirst.has_value())
    {
        if(!currClause.watchedFirst->polarity)
        {
            watchedList[currClause.watchedFirst->varIndex].first.push_back(currClause.clauseId);
        }
        else
        {
            watchedList[currClause.watchedFirst->varIndex].second.push_back(currClause.clauseId);
        }
    }
    else
    {
        std::cout<<"INVALID CLAUSE WITH NO FIRST WATCHED VAR" << std::endl;
    }

    if(currClause.watchedSecond.has_value())
    {
        if(!currClause.watchedSecond->polarity)
        {
            watchedList[currClause.watchedSecond->varIndex].first.push_back(currClause.clauseId);
        }
        else
        {
            watchedList[currClause.watchedSecond->varIndex].second.push_back(currClause.clauseId);
        }
    }

    if(currClause.literals.size()==1)
    {
        unitQueue.push(currClause.literals.front().varIndex); // PUSH ALL UNITS IN THE QUEUE
    }
}

std::tuple<bool,int,int> Formula::unitPropagate()
{

}
