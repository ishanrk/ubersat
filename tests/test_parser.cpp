//
// Created by kumth on 8/4/2025.
//
#include "test_parser.h"

void test_parser()
{
    Formula test = parseCNFClauses("../tests/parsing_tests/big_cnf.cnf");
    Formula test2 = parseCNFClauses("../tests/parsing_tests/simplified_duplicate.cnf");
    Formula test3 = parseCNFClauses("../tests/parsing_tests/trivial_one_line.cnf");
}