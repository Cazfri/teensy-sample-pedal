#ifndef SAMPLE_CONTROLLER_H
#define SAMPLE_CONTROLLER_H

#include <vector>

#include <Audio.h>

class SampleController {
public:
  SampleController();

  void initSamples(std::vector<File>&&);
  AudioStream& outputStreamL();
  AudioStream& outputStreamR();

  void update();
  void play();
  bool sampleIsPlaying();
  void stopAndRewind();

private:
  // void loadSample(size_t);

  AudioAmplifier output_l, output_r;
  AudioPlaySdWav current_sample;
  AudioConnection sample_conn_l, sample_conn_r;

  std::vector<File> sample_files;
  size_t current_sample_num;

  bool was_playing_previous_update;
};

inline SampleController::SampleController()
  : sample_conn_l(current_sample, 0, output_l, 0),
    sample_conn_r(current_sample, 1, output_r, 0),
    was_playing_previous_update(false) {}

inline AudioStream& SampleController::outputStreamL() {
  return output_l;
}

inline AudioStream& SampleController::outputStreamR() {
  return output_r;
}

#endif