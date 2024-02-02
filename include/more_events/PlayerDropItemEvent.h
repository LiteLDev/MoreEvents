#pragma once

#include "Macros.h"
#include "ll/api/event/Event.h"

#include <functional>
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/player/PlayerEvent.h>
#include <mc/world/actor/player/Player.h>
#include <mc/world/item/registry/ItemStack.h>

namespace more_events {

class PlayerDropItemEvent : public ll::event::Cancellable<ll::event::PlayerEvent> {
public:
    PlayerDropItemEvent(Player& player, ItemStack& itemStack);

    PlayerDropItemEvent(const PlayerDropItemEvent&)                    = delete;
    PlayerDropItemEvent(PlayerDropItemEvent&&)                         = delete;
    auto operator=(const PlayerDropItemEvent&) -> PlayerDropItemEvent& = delete;
    auto operator=(PlayerDropItemEvent&&) -> PlayerDropItemEvent&      = delete;

    ~PlayerDropItemEvent() override = default;

    [[nodiscard]] MORE_EVENTS_API auto itemStack() const -> ItemStack&;

private:
    std::reference_wrapper<ItemStack> mItemStack;
};

} // namespace more_events
