use super::clause::Clause;
use std::collections::HashMap;

impl Formula {
    pub fn new() -> Self {
        Formula {
            clauses: Vec::new(),
            num_clauses: 0,
            num_vars: 0,
            lit_count:HashMap::new(),
            SAT:false,
            UNSAT:false,
            final_assignment : Vec::new()
        }
    }
    pub fn decrement_lit_count(&mut self, var_index: i32, phase: bool) {
        if let Some((pos, neg)) = self.lit_count.get_mut(&var_index) {
            if phase {
                // DECREMENT POSITIVE COUNT
                if *pos > 0 {
                    *pos -= 1;
                }
            } else {
                // DECREMENT NEGATIVE COUNT
                if *neg > 0 {
                    *neg -= 1;
                }
            }

            // REMOVE ENTRY IF BOTH COUNTS ARE ZERO
            if *pos == 0 && *neg == 0 {
                self.remove_unused_var(var_index);
            }
        }
    }


    // Complexity O(n^2) see if we can do any better
    pub fn pure_literal_elimination(&mut self) {
        loop {
            let mut pure_literals = Vec::new();

            // IDENTIFY PURE LITERALS
            for (&var, &(pos, neg)) in &self.lit_count {
                if pos > 0 && neg == 0 {
                    pure_literals.push((var, true));
                } else if neg > 0 && pos == 0 {
                    pure_literals.push((var, false));
                }
            }

            // NO NEW PURE LITERALS ⇒ STOP
            if pure_literals.is_empty() {
                break;
            }

            // PROCESS EACH PURE LITERAL
            for (pure_var, phase) in pure_literals {
                println!("PURE VAR {}", pure_var);
                self.final_assignment.push((pure_var, phase));

                // REMOVE CLAUSES CONTAINING THE PURE LITERAL
                let mut to_remove = Vec::new();

                for (i, clause) in self.clauses.iter().enumerate() {
                    if clause.map.get(&pure_var) == Some(&phase) {
                        to_remove.push(i as i32);
                    }
                }

                // REMOVE IN REVERSE ORDER SO THAT THE INDICES WONT GET MESSED UP
                to_remove.sort_by(|a, b| b.cmp(a));

                for index in to_remove {
                    self.remove_clause(index);
                }


            }
        }
    }


    pub fn print(&self) {
        println!("Formula with {} clauses and {} variables", self.num_clauses, self.num_vars);
        println!("{:?}", self.lit_count);

        for x in &self.clauses
        {
            println!("CLAUSE: {:?}", x);
        }
    }

    pub fn remove_clause(&mut self, clause_index: i32) {

        // SHOULDNT BE THE CASE, BUT CHECK TO SEE IF WRONG INDEX
        if clause_index >= (self.clauses.len() as i32){
            println!("WRONG INDEX");
            return;
        }
        let clause_index_usize: usize = clause_index as usize;

        // GET PROBLEM CLAUSE
        let clause = self.clauses[clause_index_usize].clone();

        // GO THRU ALL VARS AND REMOVE FROM LIT_COUNT
        for var in &clause.literals {
            let entry = self.lit_count.get_mut(&var.index);
            if let Some((pos, neg)) = entry {
                if var.phase {
                    *pos -= 1;
                } else {
                    *neg -= 1;
                }

                // Check if both counts are now 0 → remove variable
                if *pos == 0 && *neg == 0 {
                    self.remove_unused_var(var.index);
                }
            }
        }

        // REMOVE CLAUSE FROM VECTOR
        self.clauses.remove(clause_index_usize.clone());
        self.num_clauses -= 1;
    }

    pub fn remove_unused_var(&mut self, var_index: i32) {

        self.lit_count.remove(&var_index);

        self.num_vars -= 1;

        if(self.num_vars==0)
        {
            self.SAT= true;
        }
    }

    // IN Formula
    pub fn var_assign_formula(&mut self, var_index: i32, boolean_val: bool) {
        if self.final_assignment.iter().any(|(var, _)| *var == var_index) {
            println!("Var already assigned");
            return
        }
        let mut to_be_removed = Vec::new();
        self.final_assignment.push((var_index,boolean_val));
        for i in 0..self.clauses.len() {
            if self.var_assign_clause(i, var_index, boolean_val) {
                to_be_removed.push(i as i32);
            }
            else
            {


            }
        }

        to_be_removed.sort_by(|a, b| b.cmp(a));
        for index in to_be_removed {
            self.remove_clause(index);
        }
        if self.clauses.len()==0 && self.UNSAT!=true
        {
            self.SAT=true;
            self.UNSAT=false;
            println!("Satisfied");
        }
    }

    pub fn var_assign_clause(&mut self, clause_index: usize, var_index: i32, boolean_val: bool) -> bool {
        if clause_index >= self.clauses.len() {
            return false;
        }

        let clause = &mut self.clauses[clause_index];
        let mut dec_count:bool = false;
        let mut phase:bool = false;
        if let Some(&existing_phase) = clause.map.get(&var_index) {
            phase = existing_phase;
            if existing_phase == boolean_val {
                return true;
            } else {
                clause.map.remove(&var_index);
                clause.num_vars -= 1;
                clause.literals.retain(|x| x.index != var_index);
                dec_count=true;
                if clause.literals.len() == 0
                {
                    self.UNSAT= true;
                    self.SAT=false;
                    println!("UNSAT");
                }


            }
        }

        if(dec_count)
        {
            self.decrement_lit_count(var_index, phase);
            return false;
        }

        false
    }

    pub fn unit_propagate(&mut self)
    {
        loop
        {
            let mut unit_vec = Vec::new();
            for clause in self.clauses.iter()
            {
                if clause.literals.len() == 1
                {
                    println!("{}", clause.literals[0].index);
                    unit_vec.push((clause.literals[0].index,clause.literals[0].phase));
                }
            }

            if(unit_vec.len()==0)
            {
                break;
            }

            for (index,phase) in unit_vec
            {

                self.var_assign_formula(index,phase);
            }


        }
    }

}
pub struct Formula
{
    pub clauses: Vec<Clause>,
    pub  num_clauses: i32,
    pub  num_vars: i32,
    pub lit_count: HashMap<i32,(i32,i32)>,
    pub SAT:bool,
    pub UNSAT:bool,
    pub final_assignment:Vec<(i32,bool)>

}