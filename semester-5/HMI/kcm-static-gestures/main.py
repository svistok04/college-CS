import cv2
import numpy as np
from skimage.measure import label, regionprops

def process_image_with_noise_removal(image_path, output_name, min_area=11111, offset = 20):
    # Load the image
    image = cv2.imread(image_path)
    if image is None:
        return

    hsv_image = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
    hsv_image = hsv_image.astype(np.float32) / 255.0  # normalization

    skin_mask = np.zeros((hsv_image.shape[0], hsv_image.shape[1]), dtype=np.uint8)
    for i in range(hsv_image.shape[0]):
        for j in range(hsv_image.shape[1]):
            H, S, V = hsv_image[i, j]
            if (H <= 0.2 or H >= 0.9) and (0.2 <= S <= 0.5) and (V >= 0.4):
                skin_mask[i, j] = 255

    # create a labeled mask of objects
    labeled_mask, num_labels = label(skin_mask, connectivity=2, return_num=True)

    props = regionprops(labeled_mask)

    large_objects_mask = np.zeros_like(skin_mask)
    object_count = 0
    max_area = 0
    hand_centroid = (0, 0)
    equiv_diameter = 0

    # keep large objects only
    for prop in props:
        if prop.area >= min_area:
            large_objects_mask[labeled_mask == prop.label] = 255
            object_count += 1

        if prop.area > max_area:
                max_area = prop.area
                hand_centroid = prop.centroid
                equiv_diameter = prop.equivalent_diameter

    # find centroid and radius
    skin_mask_with_centroid = cv2.cvtColor(large_objects_mask, cv2.COLOR_GRAY2BGR)
    centroid_x, centroid_y = int(hand_centroid[1]), int(hand_centroid[0])
    radius = int(equiv_diameter / 2) + offset

    # draw a circle mask
    circle_mask = np.zeros_like(large_objects_mask, dtype=np.uint8)
    cv2.circle(circle_mask, (centroid_x, centroid_y), radius, 255, thickness=-1)

    # apply the circle mask
    masked_fingers = cv2.bitwise_and(large_objects_mask, cv2.bitwise_not(circle_mask))

    # count fingers
    _, finger_count = label(masked_fingers, connectivity=2, return_num=True)

    cv2.imwrite(f"{output_name}_filtered_mask.png", large_objects_mask)
    cv2.imwrite(f"{output_name}_centroid.png", skin_mask_with_centroid)
    cv2.imwrite(f"{output_name}_fingers.png", masked_fingers)

    print(f"image: {output_name}, number of objects after filtering: {object_count}, finger count: {finger_count-1}")

image_files = ["gest0.jpg", "gest1.jpg", "gest2.jpg", "gest3.jpg", "gest4.jpg", "gest5.jpg"]

for image_file in image_files:
    process_image_with_noise_removal(image_file, image_file.split('.')[0])
