//
// Created by kumth on 8/4/2025.
//

#ifndef UBERSAT_VARIABLE_H
#define UBERSAT_VARIABLE_H

// ASSIGNMENT ENUMS FOR LITERALS
enum class Assignment
{
    Unassigned,
    False,
    True
};


struct Variable
{
    Assignment polarity;
    int var_index;

};

#endif //UBERSAT_VARIABLE_H
