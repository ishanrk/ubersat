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


// WILL HOLD INFORMATION ABOUT THE VARIABLE ITSELF IN THE CLAUSE AND THE LITERAL
struct Variable
{
    Assignment literal_assignment;
    int varIndex;
    bool polarity;

    // CONSTRUCTOR

    Variable(int var_index, bool polarity): varIndex(varIndex), polarity(polarity)
    {
        literal_assignment = Assignment::Unassigned;
    }

    bool operator==(const Variable& other) const {
        return varIndex == other.varIndex && polarity == other.polarity;
    }


};

#endif //UBERSAT_VARIABLE_H
