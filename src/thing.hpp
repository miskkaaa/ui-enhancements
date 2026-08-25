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
    inline bool IsOptionEnabled(std::string setting) {
        if (auto mod = Mod::get()->getSettingValue<bool>(setting)) {
            return true;
        } else {
            return false;
        }
    };
    inline bool IsCustomKeybindsInstalled() {
        if (auto mod = Loader::get()->getInstalledMod("geode.custom-keybinds")) {
            return true;
        } else {
            return false;
        }
    };

    inline bool IsFuckingModInstalled(std::string bullshit) {
        if (auto mod = Loader::get()->getInstalledMod(bullshit)) {
            return true;
        } else {
            return false;
        }
    }

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

    namespace font {
        inline constexpr auto big = "bigFont.fnt";
        inline constexpr auto gold = "goldFont.fnt";
        inline constexpr auto chat = "chatFont.fnt";
    };
    namespace bitch {
        inline constexpr auto roundest = "square04_001.png";
        inline constexpr auto round = "square02b_001.png";
    }
}