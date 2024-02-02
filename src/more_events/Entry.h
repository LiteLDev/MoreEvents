#pragma once

#include <ll/api/plugin/NativePlugin.h>

namespace more_events {

[[nodiscard]] auto getSelfPluginInstance() -> ll::plugin::NativePlugin&;

} // namespace more_events
