from PIL import Image

# 图片文件路径
image_path = '003.bmp'  # 替换为你的图片文件路径
# 输出的图片文件路径
output_path = '0031.bmp'  # 你可以自定义输出文件名

# 打开单张图片
original_image = Image.open(image_path)

# 计算新图片的尺寸
width, height = original_image.size
new_width = width
new_height = height*10

# 创建一个新的空白图片
new_image = Image.new('RGB', (new_width, new_height))

# 将原图片重复10次并拼接
for i in range(10):
    # 计算每张图片的起始位置
    position = (0, height*i)
    # 将图片粘贴到新图片中
    new_image.paste(original_image, position)

# 保存新图片
new_image.save(output_path)
print(f'图片已拼接完成，保存在：{output_path}')