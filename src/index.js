const pkg = import("../pkg");
export const processor = pkg;
import cartoonifyIcon from '../assets/cartoonify.png';

export const name = () => "cartoonify";
export const description = () => "Creates a cartoon style.";
export const process = async (config, image) => {
  return import("../pkg").then((processor) => processor.process(config, image));
};
export const defaultConfig = async () => {
  return { };
};
export const icon = () => {
  return cartoonifyIcon;
}
