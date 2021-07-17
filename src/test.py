from PIL import Image
from numpy import asarray
import lenna_cartoonify_plugin
print(lenna_cartoonify_plugin.description())

image = Image.open('assets/cartoonify.png')
data = asarray(image)
print(data.shape)

config = lenna_cartoonify_plugin.default_config()
print(config)
processed = lenna_cartoonify_plugin.process(config, data)
print(processed.shape)
Image.fromarray(processed).save('lenna_test_out.png')
