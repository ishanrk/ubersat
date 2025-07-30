use std::ffi::c_long;
use crate::Classes::formula::Formula;
use super::var::BoolVariable;
use std::collections;
use std::collections::HashMap;

impl Default for Clause
{
    fn default() -> Self
    {
        Clause
        {
            literals : Vec::new(),
            map: HashMap::new(),
            num_vars:0,
            activity: true
        }
    }


}
#[derive(Clone,Debug)]
pub struct Clause
{
    pub literals: Vec<BoolVariable>,
    pub map: HashMap<i32, bool>,
    pub num_vars:i32,
    pub activity: bool
}