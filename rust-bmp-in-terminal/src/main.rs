mod args;
mod bmp;
mod image;
mod render;
mod thread;

use args::Args;
use bmp::load_bmp;
use image::Image;
use thread::render_in_parallel;

fn main() {
    let args = Args::parse();

    let bmp = load_bmp(&args.filepath).expect("Failed to load BMP file");

    let image = Image::from_bmp(
        &bmp.raw_bgr_with_padding,
        bmp.width,
        bmp.height,
        bmp.channels,
    );

    let output_width = args.width.unwrap_or(image.width);
    let output_height = args.height.unwrap_or(image.height);

    let rendered_chunks = render_in_parallel(image, output_width, output_height);

    for chunk in rendered_chunks
    {
        print!("{chunk}");
    }
}
