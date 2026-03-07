use crate::image::Image;
use std::fmt::Write;

pub fn render_rows(
    image: &Image,
    output_width: usize,
    output_height: usize,
    row_start: usize,
    row_end: usize,
) -> String {
    let mut output = String::new();

    for out_y in row_start..row_end {
        let src_y = (out_y as f32 / output_height as f32 * image.height as f32) as usize;

        for out_x in 0..output_width {
            let src_x = (out_x as f32 / output_width as f32 * image.width as f32) as usize;

            let pixel_index = (src_y * image.width + src_x) * image.channels;
            let pixel = &image.pixels[pixel_index..pixel_index + image.channels];

            let r = pixel[0];
            let g = pixel[1];
            let b = pixel[2];

            let _ = write!(output, "\x1b[48;2;{};{};{}m ", r, g, b);
        }

        output.push_str("\x1b[0m\n");
    }

    output
}
