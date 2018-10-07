fn main() {
    // let num = "40".parse().expect("Not a number!"); // error
    let num: u32 = "40".parse().expect("Not a number!");
    let a = 0xff;
    let b = 0o72;
    let c = b'A';

    println!("{}", num);
    println!("a is: {}; b is: {}; c is: {}", a, b, c);
}
