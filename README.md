# bitmap-in-terminal
 
This is a simple C# program which renders a bitmap image in the terminal. It uses the `System.Drawing` library to load and process the image, and then outputs it using ANSI escape codes to display colors in the terminal.

## Usage
1. Clone the repository or download the source code.
2. Build the project using your preferred C# development environment (e.g., Visual Studio, .NET CLI).
3. Run the program and provide the path to the bitmap image you want to render in the terminal.
```bash
dotnet run -- path/to/your/image.bmp
```

## Example outputs
Here are some example outputs of bitmap images rendered in the terminal:
![Example Output 1](example.png)
This is a simple example of a bitmap image rendered in the terminal. The program converts the image into a series of colored characters, allowing you to see the image directly in your terminal window.
![Example Output 2](example2.png)
This is another example of a bitmap image rendered in the terminal. However this was ran inside Visual Studio Code's integrated terminal.


## Notes
This was mainly a project made out of fun due to me having watched a youtube video about rending bitmaps in the terminal, and I wanted to give my own "twist" to it.

Yeah thats pretty much it.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details