//
// Created by kumth on 8/4/2025.
//

#ifndef UBERSAT_FORMULA_H
#define UBERSAT_FORMULA_H
#include "Clause.h"
#include <vector>
#include <stack>

class Formula
{
    int numClauses = 0;
    std::map<int, std::pair<std::vector<int,int>,std::vector<int,int>>> watchedList;
    std::stack<std::tuple<int,int,bool>> decisionTrail;
    std::vector<Clause> clauseList;


};


#endif //UBERSAT_FORMULA_H
