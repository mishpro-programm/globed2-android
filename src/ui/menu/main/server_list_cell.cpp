#include "server_list_cell.hpp"

#include <UIBuilder.hpp>

using namespace geode::prelude;

bool ServerListCell::init(const GameServerView& gsview, bool active) {
    if (!CCLayer::init()) return false;

    Build<CCLayer>::create()
        .layout(RowLayout::create()
                    ->setAxisAlignment(AxisAlignment::Start)
                    ->setAutoScale(false)
        )
        .anchorPoint(0.f, 0.5f)
        .pos(10.f, CELL_HEIGHT / 3 * 2)
        .parent(this)
        .store(namePingLayer);

    Build<CCLabelBMFont>::create("", "bigFont.fnt")
        .anchorPoint(0.f, 0.f)
        .scale(0.7f)
        .parent(namePingLayer)
        .store(labelName);

    Build<CCLabelBMFont>::create("", "goldFont.fnt")
        .anchorPoint(0.f, 0.5f)
        .scale(0.4f)
        .parent(namePingLayer)
        .store(labelPing);

    Build<CCLabelBMFont>::create("", "bigFont.fnt")
        .anchorPoint(0.f, 0.5f)
        .pos(10, CELL_HEIGHT * 0.25f)
        .scale(0.25f)
        .parent(this)
        .store(labelExtra);

    Build<CCMenu>::create()
        .pos(CELL_WIDTH - 40.f, CELL_HEIGHT / 2)
        .parent(this)
        .store(btnMenu);

    this->updateWith(gsview, active);

    return true;
}

void ServerListCell::updateWith(const GameServerView& gsview, bool active) {
    bool btnChanged = (active != this->active);

    this->gsview = gsview;
    this->active = active;

    // log::debug("list cell name: {}", gsview.name);

    labelName->setString(gsview.name.c_str());
    labelPing->setString(fmt::format("{} ms", gsview.ping).c_str());
    labelExtra->setString(fmt::format("Region: {}, players: {}", gsview.region, gsview.playerCount).c_str());

    labelName->setColor(active ? ACTIVE_COLOR : INACTIVE_COLOR);
    labelExtra->setColor(active ? ACTIVE_COLOR : INACTIVE_COLOR);

    namePingLayer->updateLayout();

    if (btnChanged && btnConnect) {
        btnConnect->removeFromParent();

        Build<ButtonSprite>::create(active ? "Leave" : "Join", "bigFont.fnt", active ? "GJ_button_03.png" : "GJ_button_01.png", 0.8f)
            .intoMenuItem([this](auto) {

            })
            .anchorPoint(1.0f, 0.5f)
            .pos(34.f, 0.f)
            .parent(btnMenu)
            .store(btnConnect);
    }
}