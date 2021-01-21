#ifndef KTP_SDL2_WRAPPERS_SDL2_LOG_H_
#define KTP_SDL2_WRAPPERS_SDL2_LOG_H_

#include <SDL.h>
#include <iostream>
#include <string>

namespace ktp {

/* Original loggers idea from Will Usher */
/* Check it here: https://github.com/Twinklebear/TwinklebearDev-Lessons */

/**
* Log a message to the standard output stream.
* @param msg The message to write, format will be msg + '\n'.
*/
static void logMessage(const std::string& msg) {
  std::cout << msg << '\n';
}

/**
* Log a message to the output stream of our choice.
* @param os The output stream to write the message to.
* @param msg The message to write, format will be msg + '\n'.
*/
static void logMessage(std::ostream& os, const std::string& msg) {
  os << msg << '\n';
}

/**
* Log an SDL error with some error message to the standard output stream.
* @param msg The error message to write, format will be msg error: SDL_GetError() + '\n'.
*/
static void logSDLError(const std::string& msg){
	std::cerr << msg << " error: " << SDL_GetError() << '\n';
}

/**
* Log an SDL error with some error message to the output stream of our choice.
* @param os The output stream to write the message to.
* @param msg The error message to write, format will be msg error: SDL_GetError() + '\n'.
*/
static void logSDLError(std::ostream& os, const std::string& msg){
	os << msg << " error: " << SDL_GetError() << '\n';
}

} // end namespace ktp

#endif // KTP_SDL2_WRAPPERS_SDL2_LOG_H_