import cv2
import mediapipe as mp

mp_face_mesh = mp.solutions.face_mesh

def detect_happiness(image):
    with mp_face_mesh.FaceMesh(static_image_mode=True, max_num_faces=1, min_detection_confidence=0.5) as face_mesh:
        rgb_image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
        results = face_mesh.process(rgb_image)
        if not results.multi_face_landmarks:
            return "No face detected", None

        landmarks = results.multi_face_landmarks[0]

        mouth_left = landmarks.landmark[61]
        mouth_right = landmarks.landmark[291]
        mouth_center = landmarks.landmark[13]
        upper_lip = landmarks.landmark[0]
        lower_lip = landmarks.landmark[17]
        cheek_left = landmarks.landmark[234]
        cheek_right = landmarks.landmark[454]
        eye_left = landmarks.landmark[33]
        eye_right = landmarks.landmark[263]
        face_top = landmarks.landmark[10]
        face_bottom = landmarks.landmark[152]

        # normalization
        face_height = abs(face_top.y - face_bottom.y)
        mouth_corner_difference = (mouth_center.y - (mouth_left.y + mouth_right.y) / 2) / face_height
        # eye_distance = abs(eye_left.y - eye_right.y) / face_height
        lip_curvature = abs(upper_lip.y - lower_lip.y) / face_height
        cheek_difference = abs(cheek_left.y - cheek_right.y) / face_height

        # thresholds
        if mouth_corner_difference > 0.02 and lip_curvature > 0.02 and cheek_difference > 0.03:
            return "Happy", {
                "mouth_corner_difference": mouth_corner_difference,
                "eye_distance": eye_distance,
                "lip_curvature": lip_curvature,
                "cheek_difference": cheek_difference
            }
        else:
            return "Not Happy", {
                "mouth_corner_difference": mouth_corner_difference,
                "eye_distance": eye_distance,
                "lip_curvature": lip_curvature,
                "cheek_difference": cheek_difference
            }

image_paths = [
    "Anger.jpg",
    "Happy.jpg",
    "Happy2.jpg",
    "Happy3.jpg",
    "Sad.jpg",
    "Surprised.jpg"
]

for image_path in image_paths:
    print(f"Processing: {image_path}")
    image = cv2.imread(image_path)
    if image is None:
        print(f"could not read: {image_path}")
        continue

    emotion, metrics = detect_happiness(image)
    print(f"Detected emotion: {emotion}")
    if metrics:
        print(f"Details: {metrics}")

    # with mp_face_mesh.FaceMesh(static_image_mode=True, max_num_faces=1, min_detection_confidence=0.5) as face_mesh:
    #     results = face_mesh.process(cv2.cvtColor(image, cv2.COLOR_BGR2RGB))
    #     annotated_image = image.copy()
    #     for face_landmarks in results.multi_face_landmarks:
    #         mp.solutions.drawing_utils.draw_landmarks(
    #             image=annotated_image,
    #             landmark_list=face_landmarks,
    #             connections=mp_face_mesh.FACEMESH_TESSELATION,
    #             landmark_drawing_spec=mp.solutions.drawing_utils.DrawingSpec(color=(0, 255, 0), thickness=1, circle_radius=1)
    #         )
    #     cv2.imshow(f"Facial Landmarks - {image_path}", annotated_image)
    #     cv2.waitKey(0)
    #     cv2.destroyAllWindows()
