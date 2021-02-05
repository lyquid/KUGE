#include "./sdl2_audio.h"

void ktp::SDL2_Audio::closeMixer() {
  Mix_CloseAudio();
  while (Mix_Init(0)) Mix_Quit();
}

bool ktp::SDL2_Audio::initMixer(int freq, Uint16 format, int channels, int chunk_size) {
  constexpr auto audio_flags = MIX_INIT_OGG | MIX_INIT_MOD;
  const auto initted = Mix_Init(audio_flags);
  if ((initted & audio_flags) != audio_flags) {
    ktp::logSDLError("Mix_Init");
    return false;
  }
  if (Mix_OpenAudio(freq, format, channels, chunk_size) == -1) {
    ktp::logSDLError("Mix_OpenAudio");
    while (Mix_Init(0)) Mix_Quit();
    return false;
  }
  ktp::SDL2_Audio::queryMixerVersions();
  ktp::logMessage("SDL_mixer compiled version: " +  
                    std::to_string(ktp::SDL2_Audio::mixer_compiled_version_.major) + '.' + 
                    std::to_string(ktp::SDL2_Audio::mixer_compiled_version_.minor) + '.' + 
                    std::to_string(ktp::SDL2_Audio::mixer_compiled_version_.patch));
  ktp::logMessage("SDL_mixer linked version: " + 
                    std::to_string(ktp::SDL2_Audio::mixer_linked_version_->major) + '.' + 
                    std::to_string(ktp::SDL2_Audio::mixer_linked_version_->minor) + '.' + 
                    std::to_string(ktp::SDL2_Audio::mixer_linked_version_->patch));
  return true;
}

void ktp::SDL2_Audio::queryMixerVersions() {
  SDL_MIXER_VERSION(&mixer_compiled_version_);
  mixer_linked_version_ = Mix_Linked_Version();
}