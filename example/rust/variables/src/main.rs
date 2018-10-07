fn main() {
    let a = 5;
    println!("The value of a is: {}", a);
    // cannot assign twice to immutable variable
    // a = 8;
    // println!("The value of a is: {}", a);

    let mut b = 7;
    println!("The value of b is: {}", b);
    b = 9;
    println!("The value of b is: {}", b);

    const MAX_POINTS: u32 = 100_000_000;
    println!("MAX_POINTS is {}", MAX_POINTS);

    // shadowing
    let c = 10;
    let c = c + 2;
    let c = c / 6;
    println!("The value of c is: {}", c);

    let spaces = "     ";
    let spaces = spaces.len(); // 5
    println!("spaces length: {}", spaces);
}
