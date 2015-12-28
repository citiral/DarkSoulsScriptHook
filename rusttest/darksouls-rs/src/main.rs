use std::boxed;
use std::io::prelude::*;
use std::fs::File;

fn main() {
    println!("Hello, world!");
    let mut f = File::create("debug.txt");
    f.unwrap().write_all(b"Getting state!");

}
