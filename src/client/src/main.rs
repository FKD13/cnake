// use termion::*;
// use std::io::{Write, stdout, stdin};
// use termion::raw::IntoRawMode;
// use termion::input::TermRead;
// use termion::event::Key;

// fn main() {






    // let stdin = stdin();
    // let mut stdout = stdout().into_raw_mode().unwrap();

    // let size = termion::terminal_size().unwrap();
    // write!(stdout, "{}{}{}-{}", termion::clear::All, termion::cursor::Goto(1, 1), size.0, size.1).unwrap();
    // stdout.flush().unwrap();

    // for c in stdin.keys() {
    //     stdout.flush().unwrap();
    //     match c.unwrap() {
    //         Key::Char('q') => break,
    //         _              => continue,
    //     }
    // }
// }

use std::io::prelude::*;
use std::net::TcpStream;
use std::io;

fn main() -> std::io::Result<()> {
    let mut name = String::new();
    println!("Please choose a name:");
    io::stdin().read_line(&mut name)
        .expect("Failed to read line");

    let mut stream = TcpStream::connect("10.1.0.110:8000")?;

    read_print(&mut stream)?;
    stream.write(name.as_bytes())?;
    stream.flush()?;
    
    loop {
        read_print(&mut stream)?;
    }
}

fn read_print(stream: &mut TcpStream) -> std::io::Result<()> {
    let mut output = [0; 128];
    stream.read(&mut output)?;

    // check if connection has closed
    if output[0] == 0 {
        panic!("connection closed");
    }

    for item in output.iter() {
        print!("{}", *item as char);
    }

    Ok(())
}
