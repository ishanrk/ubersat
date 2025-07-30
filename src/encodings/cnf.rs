use std::collections::HashMap;
use std::env;
use std::fs::File;
use std::io::{self, BufRead};
use std::ptr::read;
use crate::Classes::clause::Clause;
use crate::Classes::formula::Formula;
use crate::Classes::var::BoolVariable;
use super::super::Classes::formula;
use std::collections;
use std::collections::HashSet;

pub fn increment_literal_count(
    map: &mut HashMap<i32, (i32, i32)>,
    nindex: i32,
    nphase: bool,
) {
    match map.entry(nindex) {
        std::collections::hash_map::Entry::Occupied(mut entry) => {
            let val = entry.get_mut();
            if nphase {
                val.0 += 1;
            } else {
                val.1 += 1;
            }
        }
        std::collections::hash_map::Entry::Vacant(entry) => {
            if nphase {
                entry.insert((1, 0));
            } else {
                entry.insert((0, 1));
            }
        }
    }
}
pub fn parse_cnf(path: &str) -> Formula
{
    let cnf = File::open(path).expect("Failed to open CNF file");
    let reader = io::BufReader::new(cnf);
    let mut flag = false; // CHECKS WHETHER THE "p" LINE HAS BEEN REACHED

    // FORMULA VARIABLES
    let mut lit_map:HashMap<i32,(i32,i32)>;
    lit_map = HashMap::new();
    let mut num_var:i32;
    let mut num_clause:i32;

    // INIT NEW FORMULA
    let mut nFormula= Formula::new();

    // GO OVER EACH LINE IN THE CNF
    for line_str in reader.lines()
    {
        let unwrapped_clause = line_str.expect("error");
        let words:Vec<&str> = unwrapped_clause.split_whitespace().collect();
        if !flag
        {
            if unwrapped_clause.chars().nth(0).expect("")=='p'
            {
                flag=true;

                num_var = words[2].parse().expect("Failed to parse num vars");
                num_clause = words[3].parse().expect("Failed to parse num clauses");
                nFormula.num_vars = num_var;
                nFormula.num_clauses = num_clause;

                println!("Num vars int: {}", num_var);
                println!("Num clauses int: {}", num_clause);
                continue;

            }
        }
        else
        {
            // INIT CLAUSE INFO
            let mut nClause = Clause::default();
            let mut clause_hash: HashMap<i32,bool>;
            let mut lit_vec = Vec::new();
            clause_hash = HashMap::new();
            let mut flag_double = false;
            // ITERATE OVER ALL LITERALS
            for literal in words
            {
                // GET INDEX AND POLARITY OF THE BOOLVAR
                let mut nindex:i32 = literal.parse().expect("Failed to parse literal");
                let mut nphase:bool;

                // THE CNF HAS ENDED SO PROCESS
                if nindex==0
                {
                    if !flag_double
                    {
                        nClause.num_vars = (clause_hash.len() as i32);
                        nClause.map = clause_hash;
                        nClause.literals = lit_vec;

                        nFormula.clauses.push(nClause);
                        break;
                    }
                    else
                    {
                        nFormula.num_clauses-=1;
                        if(nFormula.num_clauses==0)
                        {
                            nFormula.SAT= true;
                        }



                        for var in &lit_vec {
                            let entry = lit_map.get_mut(&var.index);
                            if let Some((pos, neg)) = entry {
                                if var.phase {
                                    *pos -= 1;
                                } else {
                                    *neg -= 1;
                                }

                                // Check if both counts are now 0 → remove variable
                                if *pos == 0 && *neg == 0 {

                                    lit_map.remove(&var.index);

                                    nFormula.num_vars -= 1;

                                    if(nFormula.num_vars==0)
                                    {
                                        nFormula.SAT= true;
                                    }
                                }
                            }
                        }

                        break;
                    }
                }


                // SETS THE PHASE
                if nindex<0
                {
                    nindex*=-1;
                    nphase=false;
                }
                else
                {
                    nphase =true;
                }

                // MAINTAINS A COUNT OF ALL THE VARIABLES
                increment_literal_count(&mut lit_map, nindex, nphase);

                // ADD THE VARIABLE
                let mut curr_var = BoolVariable{index:nindex, phase:nphase};
                println!("The index is {nindex} and the literal is {nphase}");

                // UPDATES CLAUSE
                // RESOLVE WHETHER -x and x IN THE SAME CLAUSE AND IF SO REMOVE THEM FROM THE FORMULA
                if clause_hash.contains_key(&nindex)
                {

                    flag_double=true;
                }
                else
                {
                    clause_hash.insert(nindex, nphase);
                }
                lit_vec.push(curr_var);
            }
        }
    }
    nFormula.lit_count = lit_map;
    nFormula
}