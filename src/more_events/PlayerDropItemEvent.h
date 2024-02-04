#pragma once

#include "ll/api/event/Event.h"

#include <functional>
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/player/PlayerEvent.h>
#include <mc/world/actor/player/Player.h>
#include <mc/world/item/registry/ItemStack.h>

namespace more_events {

class PlayerDropItemEvent : public ll::event::Cancellable<ll::event::PlayerEvent> {
public:
    __declspec(dllexport) PlayerDropItemEvent(Player& player, ItemStack& itemStack);

    PlayerDropItemEvent(const PlayerDropItemEvent&)                    = delete;
    PlayerDropItemEvent(PlayerDropItemEvent&&)                         = delete;
    auto operator=(const PlayerDropItemEvent&) -> PlayerDropItemEvent& = delete;
    auto operator=(PlayerDropItemEvent&&) -> PlayerDropItemEvent&      = delete;

    __declspec(dllexport) ~PlayerDropItemEvent() override = default;

    [[nodiscard]] __declspec(dllexport) auto itemStack() const -> ItemStack&;

private:
    std::reference_wrapper<ItemStack> mItemStack;
};

} // namespace more_events
