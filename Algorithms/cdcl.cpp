//
// Created by kumth on 8/5/2025.
//

#include "cdcl.h"

bool cdcl(Formula formula)
{
    int decisionLevel = 0;
    bool success=true;


    while(formula.decisionTrail.size()!=formula.numVars)
    {
        auto [conflict, literal,clauseIndex] = formula.unitPropagate(); // NEED TO DETECT IF FORMULA IS TRIVIALLY UNTRUE

        if(!conflict)
        {
            if(formula.decisionTrail.size()!=formula.numVars)
            {
                break;
            }
            else
            {
                decisionLevel++;
                formula.makeDecision(decisionLevel); // SELECT A VAR AND PUT IT INTO THE UNIT PROPAGATE QUEUE
            }
        }
        else
        {
            int backtrackLevel = formula.analyzeConflict(literal, clauseIndex);
            if(backtrackLevel<0)
            {
                success=false;
                break;
            }
            else
            {
                formula.backtrack(backtrackLevel);
            }
        }
    }
}