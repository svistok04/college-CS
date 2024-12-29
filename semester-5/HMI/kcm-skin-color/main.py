import cv2
import numpy as np

def process_image(image_path, output_name):
    image = cv2.imread(image_path)
    if image is None:
        return

    hsv_image = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
    hsv_image = hsv_image.astype(np.float32) / 255.0 # normalization

    skin_mask = np.zeros((hsv_image.shape[0], hsv_image.shape[1]), dtype=np.uint8)
    for i in range(hsv_image.shape[0]):
        for j in range(hsv_image.shape[1]):
            H, S, V = hsv_image[i, j]
            if (H <= 0.1 or H >= 0.9) and (0.2 <= S <= 0.6) and (V >= 0.4):
                skin_mask[i, j] = 255 # white

    non_zero_coords = np.argwhere(skin_mask > 0)
    if non_zero_coords.size != 0:
        centroid = np.mean(non_zero_coords, axis=0).astype(int)
        center_x, center_y = centroid[1], centroid[0]

        skin_mask_with_dot = cv2.cvtColor(skin_mask, cv2.COLOR_GRAY2BGR)
        cv2.circle(skin_mask_with_dot, (center_x, center_y), 15, (0, 0, 255), -1)
        cv2.imwrite(f"{output_name}_center.png", skin_mask_with_dot)

    skin_mask_bgr = cv2.cvtColor(skin_mask, cv2.COLOR_GRAY2BGR)
    combined_image = np.hstack((image, skin_mask_bgr))
    cv2.imwrite(f"{output_name}_output.png", combined_image)

image_files = ["hand.png", "hand2.png", "reporter.png", "reporter_black.png"]

for image_file in image_files:
    process_image(image_file, image_file.split('.')[0])
