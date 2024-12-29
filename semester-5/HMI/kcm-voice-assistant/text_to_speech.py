from utils.generation import SAMPLE_RATE, generate_audio, preload_models
import sounddevice
import time
import torch

class TextToSpeech:
    def __init__(self):
        preload_models()

    def __call__(self, text: str):
        # audio_array = generate_audio(text)
        audio_array = generate_audio(text, prompt='./audio-files/me_prompt.npz')

        sounddevice.play(audio_array, SAMPLE_RATE)
        # time.sleep(len(audio_array) / SAMPLE_RATE)
        sounddevice.wait()

import soundfile as sf

if __name__ == "__main__":
    torch.set_num_threads(20)
    start = time.time()

    text2speech = TextToSpeech()
    print(f'It took {time.time() - start:.2f} seconds to load')

    text = "I'm sorry, could you clarify your question?"

    start = time.time()
    audio_array = generate_audio(text, prompt='./audio-files/me_prompt.npz')
    print(f"Audio generation took {time.time() - start:.2f} seconds")

    save_path = "./audio-files/question_response.wav"
    sf.write(save_path, audio_array, SAMPLE_RATE)
    print(f"Audio saved to: {save_path}")
