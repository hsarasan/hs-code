use std::io;
use rand::Rng;

fn main(){
    let mut rng=rand::thread_rng{};
    let mut num=rng.gen_range(1..=100);
    println!("random number generted ={}",num);
}