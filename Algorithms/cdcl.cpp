//
// Created by kumth on 8/5/2025.
//

#include "cdcl.h"

bool cdcl(Formula formula)
{
    int decisionLevel = 0;
    bool success=true;

    //function to trivially find unit clauses and put them in the queue
    // if no units then no conflict and decision made

    bool firstSet = false;

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
                if(!firstSet and formula.unitQueue.empty())
                {
                    firstSet= true;
                    formula.makeDecision(decisionLevel); //NO INCREMENT IF NO UNITS FOUND ON FIRST TRY
                }
                else
                {
                    decisionLevel++;
                    formula.makeDecision(decisionLevel); // SELECT A VAR AND PUT IT INTO THE UNIT PROPAGATE QUEUE}
                }
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

    return success;
}