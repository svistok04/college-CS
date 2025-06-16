# Final Lab Project – STM32 Environment Monitor

This is my final embedded systems lab project using STM32CubeIDE.  
It was developed on the GlobalLogic Starter Kit with an STM32F407 MCU.  
The system simulates sensor monitoring and displays results on an LCD using a simple graphical UI.

## Features
- **FreeRTOS**: 2 tasks (basic scheduling)
  - `SensorTask`: handles sensor readings, button input, and prepares display content
  - `LcdTask`: updates the screen when needed by reading shared data
  > Note: buttons are handled in `SensorTask` due to time constraints — a design shortcut.

- **DHT Sensor**: dummy values (real integration not completed)
- **LM335Z Thermal Sensor**: temperature read via ADC and converted to °C
- **LCD Display**: UI with 3 display modes:
  - LM335Z temperature
  - DHT humidity (dummy value)
  - DHT temperature (dummy value)
- **Button Controls**:
  - `Up/Down`: switch between display modes
  - `Left/Right`: scroll text horizontally (position is saved per mode)
  - `Reset`: resets text position in the current mode

## Notes
- Time constraints limited the scope — only core logic and UI are implemented.
- The project is organized as an STM32CubeIDE project with FreeRTOS integration.
