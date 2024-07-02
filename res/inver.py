from PIL import Image

# 图片文件路径
image_path = '0031.bmp'  # 替换为你的图片文件路径
# 输出的图片文件路径
output_path = 'inv0031.bmp'  # 你可以自定义输出文件名

# 打开图片
original_image = Image.open(image_path)

# 将图片转换为"RGB"模式，确保它有三个颜色通道
if original_image.mode != 'RGB':
    original_image = original_image.convert('RGB')

# 加载图片数据
pixels = original_image.load()

# 获取图片尺寸
width, height = original_image.size

# 遍历图片的每个像素并反转颜色
for i in range(width):
    for j in range(height):
        # 获取当前像素的颜色值
        r, g, b = pixels[i, j]
        # 反转颜色值
        pixels[i, j] = (255 - r, 255 - g, 255 - b)

# 保存反转颜色后的图片
inverted_image = Image.new('RGB', (width, height))
inverted_image.paste(original_image)
inverted_image.save(output_path)
print(f'颜色反转后的图片已保存在：{output_path}')