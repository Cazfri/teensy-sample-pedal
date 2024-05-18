#include <vector>
#include <algorithm>

#include <SD.h>
#include <Audio.h>
#include <Bounce.h>

#include "SampleController.h"

// Pin definitions
#define FOOT_SWITCH_PIN 0

#define LED_R_PIN 1
#define LED_G_PIN 2
#define LED_B_PIN 3

#define TEENSY_AUDIO_SHIELD_SD_PIN 10

// Constants
#define BOUNCE_TIME_MS 30

// Audio setup
AudioOutputI2S headphoneOut;

AudioControlSGTL5000 audioShield;

SampleController sampleController;

AudioConnection sampleControllerOutputL(sampleController.outputStreamL(), 0, headphoneOut, 0);
AudioConnection sampleControllerOutputR(sampleController.outputStreamR(), 0, headphoneOut, 1);

// Button setup
Bounce playButton(FOOT_SWITCH_PIN, BOUNCE_TIME_MS);

// LED state
bool ledIsOn = false;

inline void setUpLedPins() {
  pinMode(LED_R_PIN, OUTPUT);
  pinMode(LED_G_PIN, OUTPUT);
  pinMode(LED_B_PIN, OUTPUT);
}

inline void setUpFootSwitchPins() {
  pinMode(FOOT_SWITCH_PIN, INPUT_PULLUP);
}

inline void ledOff() {
  analogWrite(LED_R_PIN, 0);
  analogWrite(LED_G_PIN, 0);
  analogWrite(LED_B_PIN, 0);
}

inline void ledRed() {
  analogWrite(LED_R_PIN, 256);
  analogWrite(LED_G_PIN, 0);
  analogWrite(LED_B_PIN, 0);
}

inline std::vector<File> collect_sample_files(File& directory) {
  std::vector<File> sample_files;

  while (true) {
    File f = directory.openNextFile();
    if (!f) {
      Serial.println("** no more files **");
      break;
    }

    const String filename = String(f.name());
    if (filename.endsWith(".wav") && !filename.startsWith(".")) {
      Serial.println("Found sample file " + filename);
      sample_files.push_back(f);
    }
  }

  // sort files by alphabetical order
  std::sort(sample_files.begin(), sample_files.end(), [](File i, File j) {return i.name() < j.name();});

  return sample_files;
}

// The setup() method runs once, when the sketch starts
void setup() {
  Serial.begin(38400);

  AudioMemory(10);

  audioShield.enable();
  audioShield.volume(0.5);

  setUpLedPins();
  setUpFootSwitchPins();

  if (!SD.begin(TEENSY_AUDIO_SHIELD_SD_PIN)) {
    Serial.println("SD initialization failed!");
    return;
  }

  File root = SD.open("/", FILE_READ);

  sampleController.initSamples(collect_sample_files(root));
}

// the loop() method runs over and over again
void loop() {
  sampleController.update();

  // change sampleController state when switch is pressed
  if (playButton.update()) {
    if (playButton.fallingEdge()) {
      if (sampleController.sampleIsPlaying()) {
        sampleController.stopAndRewind();
      } else {
        sampleController.play();
      }
    }
  }

  // update LED
  if (!ledIsOn && sampleController.sampleIsPlaying()) {
    ledRed();
    ledIsOn = true;
  } else if (ledIsOn && !sampleController.sampleIsPlaying()) {
    ledOff();
    ledIsOn = false;
  }
}
