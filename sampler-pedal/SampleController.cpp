#include "SampleController.h"

#include <vector>

void SampleController::initSamples(std::vector<File>&& in_sample_files) {
  sample_files = in_sample_files;
  current_sample_num = 0;
}

void SampleController::update() {
  bool sample_is_playing = sampleIsPlaying();

  if (was_playing_previous_update && !sample_is_playing) {
    current_sample_num++;
    if (current_sample_num >= sample_files.size()) {
      current_sample_num = 0;
    }
  }

  was_playing_previous_update = sample_is_playing;
}

void SampleController::play() {
  if (sampleIsPlaying()) {
    Serial.println("WARNING: play called but sample is already playing");
    return;
  }

  const char* sample_filename = sample_files[current_sample_num].name();

  if (bool ok = current_sample.play(sample_filename); ok == false) {
    Serial.printf("WARNING: Unable to play, ok=%d\n", ok);
  }
}

bool SampleController::sampleIsPlaying() {
  return current_sample.isPlaying();
}

void SampleController::stopAndRewind() {
  if (!sampleIsPlaying()) {
    Serial.print("WARNING: stopAndRewind called but sample is not playing");
    return;
  }

  current_sample.stop();
}