#ifndef KUGE_COMPONENT_HPP_
#define KUGE_COMPONENT_HPP_

#include <cstdint>

namespace kuge { namespace Component {

using ComponentType = std::uint8_t;

constexpr inline ComponentType kMaxComponents {32};

} // end namespace component
} // end namespace kuge

#endif // KUGE_COMPONENT_HPP_
