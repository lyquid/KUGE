#ifndef KUGE_HEADERS_EVENT_TYPES_H_
#define KUGE_HEADERS_EVENT_TYPES_H_

#include <map>
#include <string>

namespace kuge {

enum class EventTypes {
  InitSuccessfull,
  KeyPressed,
  StartedCleanup,
  FinishedCleanup,
  ExitGame,
  count,
};

// https://stackoverflow.com/questions/65670462/elegant-way-to-ensure-a-stdmap-has-a-concrete-size-in-compilation-time

static const std::map<EventTypes, std::string>::value_type kEventTypesNamesData[] = {
  { EventTypes::InitSuccessfull, "InitSuccessfull" },
  { EventTypes::KeyPressed,      "KeyPressed" },
  { EventTypes::StartedCleanup,  "StartedCleanup" },
  { EventTypes::FinishedCleanup, "FinishedCleanup" },
  { EventTypes::ExitGame,        "ExitGame" }
};

// Compile-time size check
static_assert(std::end(kEventTypesNamesData) - std::begin(kEventTypesNamesData) == static_cast<std::underlying_type<EventTypes>::type>(EventTypes::count));

// Construct from data
static const std::map<EventTypes, std::string> kEventTypesNames(std::begin(kEventTypesNamesData), std::end(kEventTypesNamesData));

} // end namespace kuge

#endif // KUGE_HEADERS_EVENT_TYPES_H_