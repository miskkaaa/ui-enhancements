#pragma once

#include <Geode/Geode.hpp>
#include <Geode/loader/SettingV3.hpp>
using namespace geode::prelude;

class CleanPause {
public: //i have to add public here
    static void resizeButton(CCNode* button, float width);
    static void scaleAndPosition(EditorPauseLayer* pauseLayer, float scale);

    static void onPause(EditorPauseLayer* pauseLayer);
};

namespace thing {
    inline bool IsCustomKeybindsInstalled() {
        if (auto mod = Loader::get()->getInstalledMod("geode.custom-keybinds")) {
            return true;
        } else {
            return false;
        }
    };

    inline bool IsTinkerInstalled() {
        if (auto mod = Loader::get()->getInstalledMod("alphalaneous.tinker")) {
            return true;
        } else {
            return false;
        }
    }

    inline bool IsTinkerSettingEnabled(std::string setting) {
        auto mod = Loader::get()->getInstalledMod("alphalaneous.tinker");
        if (mod->getSettingValue<bool>(setting)) {
            return true;
        } else {
            return false;
        }
    }
}