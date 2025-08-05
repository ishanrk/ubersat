//
// Created by kumth on 8/4/2025.
//

#ifndef UBERSAT_FORMULA_H
#define UBERSAT_FORMULA_H
#include "Clause.h"
#include <vector>
#include <stack>
#include <iostream>

struct Formula
{
public:
    int numClauses = 0;
    int numVars = 0;
    std::map<int, std::pair<std::vector<int>,std::vector<int>>> watchedList;
    std::stack<std::tuple<int,int,bool>> decisionTrail;
    std::vector<Clause> clauseList;

    Formula(int vars, int clauses):numVars(vars), numClauses(clauses){}

    void addClause(Clause currClause);

    void make_decision();

    void unit_propagate();

};


#endif //UBERSAT_FORMULA_H
