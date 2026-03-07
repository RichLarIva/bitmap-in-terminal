#[derive(Clone)]
pub struct Image {
    pub width: usize,
    pub height: usize,
    pub channels: usize,
    pub pixels: Vec<u8>, // RGB(A), top-to-bottom
}

impl Image {
    pub fn from_bmp(
        raw_bgr_with_padding: &[u8],
        width: usize,
        height: usize,
        channels: usize,
    ) -> Self {
        let padded_row_size = ((width * channels + 3) & !3) as usize;
        let row_size = width * channels;

        let mut pixels = vec![0u8; row_size * height];

        for row in 0..height {
            let source_row_offset = (height - 1 - row) * padded_row_size;
            let destination_row_offset = row * row_size;

            let source_row =
                &raw_bgr_with_padding[source_row_offset..source_row_offset + row_size];
            let destination_row =
                &mut pixels[destination_row_offset..destination_row_offset + row_size];

            for x in 0..width {
                let src = &source_row[x * channels..(x + 1) * channels];
                let dst = &mut destination_row[x * channels..(x + 1) * channels];

                dst[0] = src[2]; // R
                dst[1] = src[1]; // G
                dst[2] = src[0]; // B

                if channels == 4 {
                    dst[3] = src[3]; // A
                }
            }
        }

        Self {
            width,
            height,
            channels,
            pixels,
        }
    }
}
