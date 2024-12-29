from speech_to_text import SpeechToText, VoiceActivityDetector
from text_to_speech import TextToSpeech
from chatbot import Chatboot
import time
import sounddevice, soundfile, os
import pvrecorder
import numpy as np
import torch

STOP_COMMAND = "top conversation"  # Define the stop command
DEVICE_ID = 0
SAMPLE_RATE = 16000
FRAME_LENGTH = 320
SILENCE_THRESHOLD = 2.0


if __name__ == '__main__':
    torch.set_num_threads(20)
    speech2Text = SpeechToText()
    text2Speech = TextToSpeech()
    chatbot = Chatboot()
    recorder = pvrecorder.PvRecorder(device_index=DEVICE_ID, frame_length=FRAME_LENGTH)
    vad = VoiceActivityDetector(mode=2)

    print("Chatbot is ready!\n")
    print("Chatbot: Hi! How can I help you today?\n")

    silence_reminder_interval = 5
    last_silence_reminder_time = time.time()
    user_spoke_once = False

    while True:
        print("Listening...")
        recorder.start()
        recording = []
        silence_duration = 0.0

        try:
            while True:
                # Read audio frame
                frame = recorder.read()
                frame_bytes = np.array(frame, dtype=np.int16).tobytes()

                # Detect speech using VAD
                if vad.is_speech(frame_bytes, SAMPLE_RATE):
                    recording.extend(frame)
                    silence_duration = 0.0
                    user_spoke_once = True
                else:
                    silence_duration += FRAME_LENGTH / SAMPLE_RATE

                    if silence_duration > SILENCE_THRESHOLD:
                        if not user_spoke_once:
                            current_time = time.time()
                            if current_time - last_silence_reminder_time > silence_reminder_interval:
                                print("You can start speaking whenever you're ready.")
                                last_silence_reminder_time = current_time
                            break
                        else:
                            print("Silence detected. Stopping recording...")
                            break

            recorder.stop()

            if not recording:
                # print("No speech detected. Restarting listening...\n")
                continue

            recording = np.array(recording, dtype=np.float32)
            if np.max(np.abs(recording)) > 0:
                recording /= np.max(np.abs(recording))

            user_input = speech2Text(recording)
            print(f"User: {user_input}")

            if STOP_COMMAND in user_input.lower():
                print("Stop command was heard. Exiting the conversation.")
                break

            print("Chatbot is generating a response...")
            response = chatbot(user_input)
            print(f"Chatbot: {response}")

            if response == "I'm sorry, could you clarify your question?":
                clarify_path = "./audio-files/clarify.wav"
                if os.path.exists(clarify_path):
                    audio, samplerate = soundfile.read(clarify_path)
                    sounddevice.play(audio, samplerate)
                    sounddevice.wait()
                else:
                    print(f"Audio file not found: {clarify_path}")
            else:
                print("Speaking the response...")
                text2Speech(response)

            print("Ready for the next query.\n")

        except KeyboardInterrupt:
            print("Exiting...")
            recorder.stop()
            break
