use image::{DynamicImage, GrayImage, Pixel, RgbImage};
use imageproc::{edges::canny, filter::median_filter};
use palette::{Blend, Srgb};

use lenna_core::plugins::PluginRegistrar;
use lenna_core::ProcessorConfig;
use lenna_core::{core::processor::ExifProcessor, core::processor::ImageProcessor, Processor};

extern "C" fn register(registrar: &mut dyn PluginRegistrar) {
    registrar.add_plugin(Box::new(Cartoonify));
}

#[cfg(feature = "plugin")]
lenna_core::export_plugin!(register);

#[derive(Default, Clone)]
pub struct Cartoonify;

impl ImageProcessor for Cartoonify {
    fn process_image(
        &self,
        image: &mut Box<DynamicImage>,
    ) -> Result<(), Box<dyn std::error::Error>> {
        let image_rgb = image.to_rgb8();
        let (width, height) = image_rgb.dimensions();
        let image_gray: GrayImage = image.to_luma8();
        let image_gray = median_filter(&image_gray, 7, 7);

        let edges = DynamicImage::ImageLuma8(canny(&image_gray, 10.0, 50.0));
        let edges = edges.blur(1.2);
        let edges = imageproc::contrast::threshold(&edges.to_luma8(), 60);
        let edges = DynamicImage::ImageLuma8(edges).to_rgb8();
        let image_rgb = DynamicImage::ImageRgb8(image_rgb).resize(
            width / 2,
            height / 2,
            image::imageops::FilterType::Gaussian,
        );
        let image_rgb = image_rgb.blur(2.0);
        let image_rgb = image_rgb.resize(width, height, image::imageops::FilterType::Gaussian);
        let image_rgb = image_rgb.blur(7.0);
        let mut image_rgb = image_rgb.to_rgb8();
        self.and(&mut image_rgb, &edges);
        *image = Box::new(DynamicImage::ImageRgb8(image_rgb));
        Ok(())
    }
}

impl ExifProcessor for Cartoonify {}

impl Cartoonify {
    // source: https://github.com/silvia-odwyer/photon/blob/master/crate/src/multiple.rs
    pub fn and(&self, image: &mut RgbImage, second_image: &RgbImage) {
        let (width, height) = image.dimensions();
        for y in 0..height {
            for x in 0..width {
                let p = image.get_pixel(x, y);
                let p2 = second_image.get_pixel(x, y);
                let px_data = p.channels();
                let px_data2 = p2.channels();

                let color = Srgb::new(
                    px_data[0] as f32 / 255.0,
                    px_data[1] as f32 / 255.0,
                    px_data[2] as f32 / 255.0,
                )
                .into_linear();
                let color2 = Srgb::new(
                    1.0 - px_data2[0] as f32 / 255.0,
                    1.0 - px_data2[1] as f32 / 255.0,
                    1.0 - px_data2[2] as f32 / 255.0,
                )
                .into_linear();
                let components = color.darken(color2).into_components();
                image.put_pixel(
                    x,
                    y,
                    image::Rgb([
                        (components.0 * 255.0) as u8,
                        (components.1 * 255.0) as u8,
                        (components.2 * 255.0) as u8,
                    ]),
                );
            }
        }
    }
}

#[derive(Clone, serde::Serialize, serde::Deserialize)]
struct Config {}

impl Default for Config {
    fn default() -> Self {
        Config {}
    }
}

impl Processor for Cartoonify {
    fn name(&self) -> String {
        "cartoonify".into()
    }

    fn title(&self) -> String {
        "Cartoonify".into()
    }

    fn author(&self) -> String {
        "chriamue".into()
    }

    fn description(&self) -> String {
        "Plugin to create a cartoon style.".into()
    }

    fn process(
        &mut self,
        _config: ProcessorConfig,
        image: &mut Box<lenna_core::LennaImage>,
    ) -> Result<(), Box<dyn std::error::Error>> {
        self.process_exif(&mut image.exif).unwrap();
        self.process_image(&mut image.image).unwrap();
        Ok(())
    }

    fn default_config(&self) -> serde_json::Value {
        serde_json::to_value(Config::default()).unwrap()
    }
}

#[cfg(target_arch = "wasm32")]
use wasm_bindgen::prelude::*;
#[cfg(target_arch = "wasm32")]
lenna_core::export_wasm_plugin!(Cartoonify);

#[cfg(test)]
mod tests {
    use super::*;
    use lenna_core::ProcessorConfig;

    #[test]
    fn default() {
        let mut cartoonify = Cartoonify::default();
        let config = ProcessorConfig {
            id: "cartoonify".into(),
            config: cartoonify.default_config(),
        };
        assert_eq!(cartoonify.name(), "cartoonify");
        let mut img =
            Box::new(lenna_core::io::read::read_from_file("../lenna.png".into()).unwrap());
        cartoonify.process(config, &mut img).unwrap();
        img.name = "test".to_string();
        lenna_core::io::write::write_to_file(&img, image::ImageOutputFormat::Jpeg(80)).unwrap();
    }
}
