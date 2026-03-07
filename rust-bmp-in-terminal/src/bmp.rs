use std::fs::File;
use std::io::{self, Read, Seek, SeekFrom};
use std::path::Path;

fn read_u16_le<R: Read>(reader: &mut R) -> io::Result<u16> {
    let mut bytes = [0u8; 2];
    reader.read_exact(&mut bytes)?;
    Ok(u16::from_le_bytes(bytes))
}

fn read_u32_le<R: Read>(reader: &mut R) -> io::Result<u32> {
    let mut bytes = [0u8; 4];
    reader.read_exact(&mut bytes)?;
    Ok(u32::from_le_bytes(bytes))
}

fn read_i32_le<R: Read>(reader: &mut R) -> io::Result<i32> {
    let mut bytes = [0u8; 4];
    reader.read_exact(&mut bytes)?;
    Ok(i32::from_le_bytes(bytes))
}

pub struct BmpData {
    pub width: usize,
    pub height: usize,
    pub channels: usize,
    pub raw_bgr_with_padding: Vec<u8>,
}

pub fn load_bmp<P: AsRef<Path>>(path: P) -> io::Result<BmpData> {
    let mut file = File::open(path)?;

    let file_type = read_u16_le(&mut file)?;
    let _file_size = read_u32_le(&mut file)?;
    let _reserved_1 = read_u16_le(&mut file)?;
    let _reserved_2 = read_u16_le(&mut file)?;
    let pixel_data_offset = read_u32_le(&mut file)?;

    if file_type != 0x4D42 {
        return Err(io::Error::new(
            io::ErrorKind::InvalidData,
            "Not a BMP file (missing 'BM' signature')",
        ));
    }

    let header_size = read_u32_le(&mut file)?;

    if header_size < 40 {
        return Err(io::Error::new(
            io::ErrorKind::InvalidData,
            "BMP header too small",
        ));
    }

    let width = read_i32_le(&mut file)? as usize;
    let height_signed = read_i32_le(&mut file)?;
    let height = height_signed.unsigned_abs() as usize;

    let _color_planes = read_u16_le(&mut file)?; // ignored
    let bits_per_pixel = read_u16_le(&mut file)?;
    let channels = (bits_per_pixel / 8) as usize;

    if channels != 3 && channels != 4 {
        return Err(io::Error::new(
            io::ErrorKind::InvalidData,
            format!("Unsupported BMP bit depth: {} bits per pixel", bits_per_pixel),
        ));
    }

    // Skip the rest of the header BEFORE reading compression
    if header_size > 40 {
        file.seek(SeekFrom::Current((header_size - 40) as i64))?;
    }

    let compression_method = read_u32_le(&mut file)?;
    let _image_size = read_u32_le(&mut file)?;
    let _x_pixels_per_meter = read_i32_le(&mut file)?;
    let _y_pixels_per_meter = read_i32_le(&mut file)?;
    let _colors_used = read_u32_le(&mut file)?;
    let _important_colors = read_u32_le(&mut file)?;

    if compression_method != 0 {
        return Err(io::Error::new(
            io::ErrorKind::InvalidData,
            format!("Compressed BMP not supported (compression={compression_method})"),
        ));
    }

    file.seek(SeekFrom::Start(pixel_data_offset as u64))?;

    let padded_row_size = ((width * channels + 3) & !3) as usize;
    let total_pixel_data_size = padded_row_size * height;

    let mut raw_bgr_with_padding = vec![0u8; total_pixel_data_size];
    file.read_exact(&mut raw_bgr_with_padding)?;

    Ok(BmpData {
        width,
        height,
        channels,
        raw_bgr_with_padding,
    })
}
