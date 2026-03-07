
![License Badge](https://img.shields.io/badge/License-MIT-yellow.svg)

# bitmap-in-terminal

This project started as a simple C# program that renders bitmap images directly in the terminal. It loads `.bmp` files, reads them at the byte level, and then spits them out as colored characters using ANSI escape codes. No fancy graphics libraries, no shortcuts — just raw bitmap parsing and terminal output.

Since then, the project has grown a bit. What began as “hey, this looks fun” turned into “okay, now I’m rewriting it in C for speed” and eventually I felt as if I could also do it in Rust as I had the day before followed a rust OS guide.

## C# Version

The original version uses `System.Drawing` to load the bitmap, then converts each pixel into a colored block in the terminal. Pretty straightforward. Build it however you want (Visual Studio, .NET CLI, whatever) and run it like this:

```bash
dotnet run -- path/to/your/image.bmp
```

## Example Outputs

Here are some examples of what the C# version produces in the terminal:

![Example](Example.png)

![Example](Example2.png)

The second one was rendered inside VS Code’s integrated terminal, which actually handles ANSI colors surprisingly well.

## Notes

This was mainly a project made out of fun due to me having watched a youtube video about rending bitmaps in the terminal, and I wanted to give my own "twist" to it.

Yeah thats pretty much it.

## Update 1.5021y (I know this is a unique version number, but its life) 

Anyways so basically with this update I made a C-Version of this program since I felt like the need to work on my C skills. With that said the C-Version is way faster due to me having added multithreading. At first it wasn't significantly faster, for instance 450x450 would take a while to render, but after adding multithreading it was significantly faster, now basically an instant. The C version also has flags this being --height and --width which you can use to specify the height and width of the output in the terminal. It also checks the most optimal thread count to use based on the system's hardware and uses that for the multithreading.

```bash
./bmp-to-terminal path/to/your/image.bmp --height 50 --width 50
```

![Example](example3.png)

Future idea: maybe add a bitmap generator so you don’t have to go hunting for `.bmp` files. Also planning to bring multithreading and flags to the C# version at some point.

## Rust Version

And now there’s a Rust version too. This one sticks to the same low-level approach as the C version — manually reading headers, parsing bytes, handling padding, all that fun stuff but with Rust’s safety guarantees so I don’t accidentally blow my foot off with a pointer.

It supports modern BMP formats (including V5 headers), handles raw pixel buffers, and keeps everything memory-safe while still being fast. Basically, it’s the same logic expressed in a cleaner, safer way.

## License

MIT License. See the [LICENSE](LICENSE) file.

![fish](fish.bmp)

fish

