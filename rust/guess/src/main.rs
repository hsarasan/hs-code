use std::io;
use rand::Rng;

fn main() {
    let ran_number=rand::thread_rng().gen_range(1..=100);
    let mut input=String::new();
    let mut attempts=0;
    while attempts<5 { 
        input.clear();
        println!("Enter your input");
        io::stdin().read_line(&mut input).expect("Failed to read line");
        let guess: i32 = match input.trim().parse() {
            Ok(num) => num,
            Err(_) => {
                println!("Invalid input. Please enter a valid integer.");
                continue; // Skip to the next iteration
            }
        };
        if guess==ran_number{
            println!("You won ");
            break;
        }
        if guess>ran_number{
            println!("You guessed higher");
        }
        else{
            println!("You guessed lower");
        }
        
        attempts+=1;
        if attempts==5 {
            println!("You lost. The number was {}", ran_number);
            break;
        }
        
    }
}
