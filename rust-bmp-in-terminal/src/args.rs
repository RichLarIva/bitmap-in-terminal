use std::path::PathBuf;

pub struct Args {
    pub filepath: PathBuf,
    pub width: Option<usize>,
    pub height: Option<usize>,
}

impl Args {
    pub fn parse() -> Self {
        let mut args = std::env::args().skip(1).collect::<Vec<_>>();

        if args.is_empty() {
            eprintln!("Usage: bmp-terminal <file.bmp> [--width N] [--height N]");
            std::process::exit(1);
        }

        let filepath = PathBuf::from(args.remove(0));
        let mut width = None;
        let mut height = None;

        let mut i = 0;
        while i < args.len() {
            match args[i].as_str() {
                "--width" if i + 1 < args.len() => {
                    width = args[i + 1].parse().ok();
                    i += 2;
                }
                "--height" if i + 1 < args.len() => {
                    height = args[i + 1].parse().ok();
                    i += 2;
                }
                _ => i += 1,
            }
        }

        Self {
            filepath,
            width,
            height,
        }
    }
}
