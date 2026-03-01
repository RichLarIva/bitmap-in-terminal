using System.Drawing;
using System.IO;

namespace BmpTerminal
{
    internal class Program
    {
        static void Main(string[] args)
        {
            if (args.Length == 0)
            {
                Console.WriteLine("Usage: BmpTerminal <image_path>");
                return;
            }
            string imagePath = args[0];

            if (!File.Exists(imagePath))
            {
                Console.WriteLine($"File not found: {imagePath}");
                return;
            }

            try
            {
                var bmp = new Bitmap(imagePath);
            }
        }
    }
}
