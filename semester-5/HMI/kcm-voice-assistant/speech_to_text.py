import torch, transformers, numpy as np, librosa, pvrecorder
import logging, warnings, pathlib, sys
import webrtcvad
import time

STOP_COMMAND = "stop conversation"
DEVICE_ID = 0
SAMPLE_RATE = 16000
FRAME_LENGTH = 320
SILENCE_THRESHOLD = 2.0

logging.getLogger('transformers').setLevel(logging.ERROR)
warnings.filterwarnings('ignore')


class SpeechToText:
    def __init__(self, cache_dir: pathlib.Path = pathlib.Path("cache-dir")):

        cache_dir.mkdir(exist_ok=True, parents=True)

        # Źródło modelu:
        # https://huggingface.co/jonatasgrosman/wav2vec2-large-xlsr-53-english

        model_name = "jonatasgrosman/wav2vec2-large-xlsr-53-english"

        self.proc = transformers.Wav2Vec2Processor.from_pretrained(
            model_name, cache_dir=cache_dir)
        self.model = transformers.Wav2Vec2ForCTC.from_pretrained(
            model_name, cache_dir=cache_dir)

    def __call__(self, speech: np.ndarray) -> str:
        input_model = self.proc(speech, sampling_rate=16000,
                                return_tensors="pt", padding=True)

        output_model = torch.argmax(
            self.model(
                input_model.input_values,
                attention_mask=input_model.attention_mask).logits, dim=-1)

        return self.proc.batch_decode(output_model)[0]

class VoiceActivityDetector:
    def __init__(self, mode=2):
        self.vad = webrtcvad.Vad()
        self.vad.set_mode(mode)

    def is_speech(self, frame: bytes, sample_rate: int = 16000) -> bool:
        return self.vad.is_speech(frame, sample_rate)


if __name__ == "__main__":
    vad = VoiceActivityDetector(mode=2)
    speech_to_text = SpeechToText()
    recorder = pvrecorder.PvRecorder(device_index=0, frame_length=FRAME_LENGTH)

    print("Voice Activity Detection Test")
    print("Say something, and I'll print what you said when you stop talking. Type CTRL+C to exit.\n")

    while True:
        print("Listening...")
        recorder.start()
        recording = []
        silence_duration = 0.0
        start_time = time.time()

        try:
            while True:
                frame = recorder.read()
                frame_bytes = np.array(frame, dtype=np.int16).tobytes()

                if vad.is_speech(frame_bytes, SAMPLE_RATE):
                    silence_duration = 0.0
                    recording.extend(frame)
                    print("Detected speech...")
                else:
                    silence_duration += FRAME_LENGTH / SAMPLE_RATE
                    if silence_duration > SILENCE_THRESHOLD:
                        print("\nSilence detected. Stopping recording...")
                        break
            recorder.stop()

            if not recording:
                print("No speech detected. Restarting listening...\n")
                continue

            recording = np.array(recording, dtype=np.float32)
            if np.max(np.abs(recording)) > 0:
                recording /= np.max(np.abs(recording))


            print("Converting speech to text...")
            user_input = speech_to_text(recording)
            print(f"User said: {user_input}\n")

        except KeyboardInterrupt:
            print("\nExiting...")
            recorder.stop()
            break
