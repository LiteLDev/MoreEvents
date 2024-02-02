#include "more_events/PlayerDropItemEvent.h"

#include "ll/api/event/EmitterBase.h"
#include "ll/api/event/ListenerBase.h"

#include <ll/api/event/Emitter.h>
#include <ll/api/event/EventBus.h>
#include <ll/api/memory/Hook.h>
#include <mc/world/actor/player/Player.h>
#include <memory>

namespace more_events {

PlayerDropItemEvent::PlayerDropItemEvent(Player& player, ItemStack& itemStack)
: Cancellable(player),
  mItemStack(itemStack) {
    // Empty
}

auto PlayerDropItemEvent::itemStack() const -> ItemStack& { return mItemStack; }

struct EventHook;
auto makeEventEmitter(ll::event::ListenerBase& /*unused*/) -> std::unique_ptr<ll::event::EmitterBase>;
class EventEmitter : public ll::event::Emitter<makeEventEmitter, PlayerDropItemEvent> {
    ll::memory::HookRegistrar<EventHook> hook;
};

// NOLINTBEGIN(modernize-use-trailing-return-type)
// NOLINTBEGIN(cppcoreguidelines-avoid-non-const-global-variables)
// NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast)

LL_TYPE_INSTANCE_HOOK(
    EventHook,
    HookPriority::Normal,
    Player,
    "?drop@Player@@UEAA_NAEBVItemStack@@_N@Z",
    bool,
    ItemStack& itemStack,
    bool       randomly
) {
    auto event = PlayerDropItemEvent(*this, itemStack);

    auto& eventBus = ll::event::EventBus::getInstance();
    eventBus.publish(event);
    if (event.isCancelled()) {
        return false;
    }

    return origin(itemStack, randomly);
}

// NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast)
// NOLINTEND(cppcoreguidelines-avoid-non-const-global-variables)
// NOLINTEND(modernize-use-trailing-return-type)

auto makeEventEmitter(ll::event::ListenerBase& /*unused*/) -> std::unique_ptr<ll::event::EmitterBase> {
    return std::make_unique<EventEmitter>();
}

} // namespace more_events
