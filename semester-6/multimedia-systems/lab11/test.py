import cv2
import matplotlib.pyplot as plt



cover1 = cv2.cvtColor(cv2.imread('logo.png'), cv2.COLOR_BGR2RGB)
plt.imshow(cover1)
plt.show()
