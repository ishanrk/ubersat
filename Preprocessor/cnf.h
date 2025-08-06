//
// Created by kumth on 8/4/2025.
//

#ifndef UBERSAT_CNF_H
#define UBERSAT_CNF_H

#include "../solver/formula.h"
#include <string>
#include <fstream>
#include <sstream>

struct CNFHeader {
    int numVars = 0;
    int numClauses = 0;
};

Formula parseCNFClauses(const std::string& filepath);
CNFHeader parseCNFHeader(const std::string& filepath);

#endif //UBERSAT_CNF_H


