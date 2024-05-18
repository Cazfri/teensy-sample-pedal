# Sample Pedal

An audio sample player controlled by a switch using a Teensy4.0 and Teensy Audio Shield.

Press the switch to trigger a sample. Once finished, it will move to the next sample. If you trigger it by mistake, hit the switch while the sample is playing to stop and rewind.

Primarily intended for a guitar pedal form factor, intended to be controlled with a momentary foot switch.

## Programming Teensy

Programmed using Teensyduino and the Arduino IDE. I'm not particularly a fan of the IDE, but it makes uploading and debugging very easy.

## Wiring

This code uses the following pins for its various components.

| Component | Pin |
| -------- | ------- |
| Push-to-make momentary switch | 0 |
| RGB LED red lead | 1 |
| RGB LED green lead (currently unused) | 2 |
| RGB LED blue lead (currently unused) | 3 |
| Teensy audio shield SD port | 10 |

## Sample Files

Sample files to be played must be loaded onto the Teensy's SD card's root directory. Samples must be **8- or 16-bit WAV files only** due to limitations of the Teensy audio library. Samples will be played in alphabetical order of the filename, so it's recommended that you prefix the filename with a number to specify the order of samples (e.g. `01-mysample.wav`). This code will play all files that end in `.wav` and do not start with a `.` character.

## Usage and contribution

This is intended as a personal project and example for anyone looking to make something similar. I make no guarantees to provide development or product support, but feel free to open an issue if you have a question and I can help where possible.
