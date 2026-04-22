// By Heltion
use std::{
    cell::RefCell,
    fmt::Debug,
    io::{BufWriter, Read, Stdout},
    str::{FromStr, SplitAsciiWhitespace},
};

thread_local! {
    static INPUT: RefCell<SplitAsciiWhitespace<'static>> = RefCell::<SplitAsciiWhitespace<'static>>::new({
        let mut input = String::new();
        std::io::stdin().read_to_string(&mut input).unwrap();
        Box::leak(input.into_boxed_str()).split_ascii_whitespace()
    });
    pub static OUTPUT: RefCell<BufWriter<Stdout>> = RefCell::new(BufWriter::new(std::io::stdout()));
}

pub fn read<T: FromStr>() -> T
where
    T::Err: Debug,
{
    INPUT.with(|input| input.borrow_mut().next().unwrap().parse().unwrap())
}

pub fn read_string() -> Vec<u8> {
    INPUT.with(|input| input.borrow_mut().next().unwrap().as_bytes().to_vec())
}

#[macro_export]
macro_rules! expand {
    ($arg:expr) => {
        $arg.into_iter()
            .map(|x| x.to_string())
            .collect::<Vec<_>>()
            .join(" ")
    };
}

#[macro_export]
macro_rules! output {
    ($($arg:expr),*) => {
        OUTPUT.with(|output| {
            use std::io::Write;
            writeln!(output.borrow_mut(), "{}", [$($arg.to_string()),*].join(" ")).unwrap();
        });
    };
}

#[macro_export]
macro_rules! debug {
    ($($arg:expr),*) => {
        #[cfg(debug_assertions)]
        eprintln!("[{}:{}] {}", file!(), line!(), [$(format!("{} = {:?}", stringify!($arg), $arg)),*].join(", "));
    };
}

fn main() {

}