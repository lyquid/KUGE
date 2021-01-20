/* Original idea from Will Usher */
/* Check it here: https://github.com/Twinklebear/TwinklebearDev-Lessons */

#ifndef KUGE_INCLUDE_LOG_H_
#define KUGE_INCLUDE_LOG_H_

#include <iostream>
#include <SDL.h>

namespace ktp {

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


} // namespace ktp

#endif // KUGE_INCLUDE_LOG_H_