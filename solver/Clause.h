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
    std::map<int, bool> literalContainer;
    std::optional<Variable> watchedFirst;
    std::optional<Variable> watchedSecond;
    int clauseLength=0;
    int clauseId;
    int clauseActivity = true;

    Clause(int clause_id): clauseId(clause_id){}

    [[nodiscard]] bool checkVariableInClause(int varIndex) const;

    void addVariable(Variable newLiteral);
};


#endif //UBERSAT_CLAUSE_H
