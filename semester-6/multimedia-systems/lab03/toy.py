import numpy as np
import time
height = 3000
width = 3000
image = np.random.randint(0, 255, (height, width))
scaling_factor = 0.33

# print(np.sum(image[0:4, 0:4]))

new_height = int(np.floor(height * scaling_factor))  # 3
new_width = int(np.floor(width * scaling_factor))   # 3

X, Y = np.mgrid[0:height, 0:width]
mapped_X = (X * scaling_factor).astype(int)
mapped_Y = (Y * scaling_factor).astype(int)

print("Mapped X:\n", mapped_X)
print("Mapped Y:\n", mapped_Y)

t = time.time()
# Empty target + count
new_image = np.empty((new_height, new_width), dtype=object)
new_image[:] = [[[] for _ in range(new_width)] for _ in range(new_height)]

print(X.shape, Y.shape)
# print(image.shape)
# print(new_image.shape)
for i in range(height):
    for j in range(width):
        # print("X:\t", mapped_X[i, j])
        # print("Y:\t", mapped_Y[i, j])
        new_image[mapped_X[i, j], mapped_Y[i, j]].append(image[i, j])

print('new image')
new_image = np.array([[np.mean(el) for el in row] for row in new_image]).astype(int)
print(new_image)

print(f'it took {time.time() - t} seconds for loop')
t = time.time()
new_image = np.zeros((new_height, new_width), dtype=np.uint32)
count = np.zeros((new_height, new_width), dtype=np.uint8)

np.add.at(new_image[:, :], (mapped_X, mapped_Y), image[:, :])
np.add.at(count[:, :], (mapped_X, mapped_Y), 1)

new_image = (new_image / count).astype(np.uint8)

print(new_image)

print(f'it took {time.time() - t} seconds for numpy')

# print("Original Image:\n", image)
# print("Mean Downscaled Image:\n", mean_image)
