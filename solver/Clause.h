//
// Created by kumth on 8/4/2025.
//

#ifndef UBERSAT_CLAUSE_H
#define UBERSAT_CLAUSE_H
#include "Variable.h"
#include <deque>
#include <optional>
#include <map>


struct Clause
{
    std::deque<Variable> literals;
    std::map<int, int> literalContainer;
    std::optional<Variable> watchedFirst;
    std::optional<Variable> watchedSecond;
    int clauseLength=0;
    int clauseId=-1;
    int clauseActivity = true;


    [[nodiscard]] bool checkVariableInClause(int varIndex) const;

    bool addVariable(Variable newLiteral);

    void debugPrint();
};


#endif //UBERSAT_CLAUSE_H
