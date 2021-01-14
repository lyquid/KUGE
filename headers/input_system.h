#ifndef KUGE_HEADERS_INPUT_SYSTEM_H_
#define KUGE_HEADERS_INPUT_SYSTEM_H_

#include "./event.h"
#include "./system.h"

namespace kuge {

class InputSystem : virtual public System {
 public:
  InputSystem(EventBus& bus): System(bus) {}
  void handleEvent(const Event& event) {}
};

} // end namespace kuge

#endif // KUGE_HEADERS_INPUT_SYSTEM_H_