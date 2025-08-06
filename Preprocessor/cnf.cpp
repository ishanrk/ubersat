//
// Created by kumth on 8/4/2025.
//
#include "cnf.h"



CNFHeader parseCNFHeader(const std::string& filepath) {
    std::ifstream file(filepath);
    CNFHeader header;

    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filepath << std::endl;
        return header;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == 'c') continue;

        if (line[0] == 'p') {
            std::istringstream iss(line);
            std::string tmp;
            iss >> tmp >> tmp >> header.numVars >> header.numClauses;
            break;
        }
    }

    file.close();
    return header;
}

Formula parseCNFClauses(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filepath << std::endl;
        return {-1,-1};
    }

    std::string line;
    bool headerPassed = false;
    CNFHeader header = parseCNFHeader(filepath);
    Formula currFormula(header.numVars, 0);

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == 'c') continue;

        if (!headerPassed && line[0] == 'p') {
            headerPassed = true;
            continue;
        }

        Clause currClause;

        // Parse clause
        std::istringstream iss(line);
        int literal;
        std::vector<int> clause;
        bool flag_trivial = false;
        while (iss >> literal && literal != 0)
        {
            std::cout <<"Processing literal" << literal << std::endl;

            if(literal<0)
            {
                Variable currVar(-literal,false);
                bool ans = currClause.addVariable(currVar);
                if(!ans)
                {
                    std::cout<<"TRIVIAL CLAUSE DETECTED" << std::endl;
                    flag_trivial= true;
                };
            }
            else
            {

                Variable currVar(literal,true);

                bool ans = currClause.addVariable(currVar);
                if(!ans)
                {
                    std::cout<<"TRIVIAL CLAUSE DETECTED" << std::endl;
                    flag_trivial= true;
                };
            }
        }
        if(!flag_trivial)
        {
            std::cout << "SUCCESSFULLY ADDED CLAUSE" << std::endl;
            currFormula.addClause(currClause);
            currClause.debugPrint();
        }

    }
    file.close();
    return currFormula;

}