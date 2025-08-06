//
// Created by kumth on 8/4/2025.
//

#ifndef UBERSAT_FORMULA_H
#define UBERSAT_FORMULA_H
#include "Clause.h"
#include <vector>
#include <stack>
#include <iostream>
#include<queue>

struct Formula
{
public:
    int numClauses = 0;
    int numVars = 0;
    std::map<int, std::pair<std::vector<int>,std::vector<int>>> watchedList;
    std::stack<std::tuple<int,int,bool>> decisionTrail;
    std::vector<Clause> clauseList;
    std::queue<int> propagationQueue; // THIS KEEPS ON GETTING UPDATED ONCE A DECISION HAS BEEN MADE, until its empty unit prop goes on.

    Formula(int vars, int clauses):numVars(vars), numClauses(clauses){}

    void addClause(Clause currClause);

    void makeDecision(int decisionLevel);

    std::tuple<bool,int,int> unitPropagate(); // CONFLICT/LITERAL/INDEX of error

    int analyzeConflict(int problemLiteral, int clauseIndex); // WILL ADD LEARNT CLAUSE TO THE CNF

    void backtrack(int level);

};


#endif //UBERSAT_FORMULA_H
