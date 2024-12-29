---------------------------------------------------------------------
Struktura katalogu
---------------------------------------------------------------------
Pliki zadań:
 - speech-to-text.py: plik zadania do 1
 - chatbot.py: plik do zadania 2
 - text-to-speech.py: plik do zadania 3

Katalogi z modelami:
 - checkpoints/: model biblioteki "VALL-E-X" do syntezy mowy
 - chache-dir: model do rozpoznawania mowy oraz chatboot

Pozostałe pliki i katalogi biblioteki "VALL-E-X":
 - utils/
 - modules/
 - models/
 - data/
 - macros.py

Plik z wymaganymi pakietami pythona:
 - requirements.txt

---------------------------------------------------------------------
Źródła wykorzystanych modeli
---------------------------------------------------------------------
Model rozpoznawania mowy:
https://huggingface.co/jonatasgrosman/wav2vec2-large-xlsr-53-english

Chatboot:
https://huggingface.co/microsoft/DialoGPT-medium

Kompletna biblioteka VALL-E-X:
https://github.com/Plachtaa/VALL-E-X

---------------------------------------------------------------------
Przykład konfiguracji wirtualnego środowiska python
---------------------------------------------------------------------
Zadania do laboratoriów zostały przygotowane pod Python 3.12

python3 -m venv kcm-venv
source kcm-venv/bin/activate

pip install -r requirements.txt 






