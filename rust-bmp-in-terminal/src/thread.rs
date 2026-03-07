use crate::image::Image;
use crate::render::render_rows;
use std::thread;

pub fn render_in_parallel(
    image: Image,
    output_width: usize,
    output_height: usize,
) -> Vec<String> {
    let thread_count = thread::available_parallelism()
        .map(|n| n.get())
        .unwrap_or(1);

    let rows_per_thread = (output_height + thread_count - 1) / thread_count;

    let mut handles = Vec::new();

    for thread_index in 0..thread_count {
        let row_start = thread_index * rows_per_thread;
        let row_end = (row_start + rows_per_thread).min(output_height);

        if row_start >= row_end {
            continue;
        }

        let image_clone = image.clone();

        handles.push(thread::spawn(move || {
            render_rows(
                &image_clone,
                output_width,
                output_height,
                row_start,
                row_end,
            )
        }));
    }

    handles
        .into_iter()
        .map(|h| h.join().expect("Thread panicked"))
        .collect()
}
