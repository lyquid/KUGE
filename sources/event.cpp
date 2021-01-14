#include "../headers/event.h"

kuge::Event::Event(kuge::EventTypes type): 
  kMessage_(std::string()),
  kName_(kuge::kEventTypesNames.at(type)),
  kType_(type), 
  kValue_(0) {}

kuge::Event::Event(kuge::EventTypes type, float value): 
  kMessage_(std::string()),
  kName_(kuge::kEventTypesNames.at(type)),
  kType_(type), 
  kValue_(value) {}

kuge::Event::Event(kuge::EventTypes type, const std::string& msg): 
  kMessage_(msg),
  kName_(kuge::kEventTypesNames.at(type)),
  kType_(type),
  kValue_(0) {}

kuge::Event::Event(kuge::EventTypes type, float value, const std::string& msg): 
  kMessage_(msg),
  kName_(kuge::kEventTypesNames.at(type)),
  kType_(type),
  kValue_(value) {}

std::ostream& kuge::operator<<(std::ostream& os, const kuge::Event& event) {
  os << '['
     << static_cast<std::underlying_type<kuge::EventTypes>::type>(event.kType_)
     << "]\t"
     << event.kName_
     << '('
     << event.kValue_
     << ", \""
     << event.kMessage_
     << "\")\n";
  return os;
}