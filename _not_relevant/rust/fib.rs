fn fibonacci(n: u32) -> u32 {
    if n <= 1 {
        return 1;
    }
    return fibonacci(n - 1) + fibonacci(n - 2)
}

fn main() {
    let n = 5; // You can change this value to calculate a different Fibonacci number
    println!("Fibonacci number at position {} is {}", n, fibonacci(n));
}
