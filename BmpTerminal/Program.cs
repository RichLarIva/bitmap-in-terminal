using System.Drawing;
using System.IO;

namespace BmpTerminal
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Console.OutputEncoding = System.Text.Encoding.UTF8;
            if (args.Length == 0)
            {
                Console.WriteLine("Usage: BmpTerminal <image_path>");
                return;
            }

            string? imagePath = args[0];

            if (!File.Exists(imagePath))
            {
                Console.WriteLine($"File not found: {imagePath}");
                return;
            }


            Bitmap? image;
            Console.Write("\u001b[?25h");


            // Retrieve the image
            image = new Bitmap(imagePath, true);


            image = Resize(image, 128, 64); // Magic numbers here are basically just what I found to be a perfect size when having a large image

            int x, y;

            for (y = 0; y < image?.Height; y++)
            {
                for (x = 0; x < image?.Width; x++)
                {
                    Color pixelColor = image.GetPixel(x, y);
                    Console.Write($"\u001b[38;2;{pixelColor.R};{pixelColor.G};{pixelColor.B}m█");
                }

                Console.Write("\u001b[0m\n");
            }


        }

        // helper method to resize
        static Bitmap Resize(Bitmap original, int width, int height)
        {
            Bitmap resized = new Bitmap(width, height);
            using (Graphics g = Graphics.FromImage(resized))
            {
                g.DrawImage(original, 0, 0, width, height);
            }

            return resized;
        }
    }
}
