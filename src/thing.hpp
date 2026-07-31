#pragma once

#include <Geode/Geode.hpp>
using namespace geode::prelude;

class CleanPause {
public: //i have to add public here
    static void resizeButton(CCNode* button, float width);
    static void scaleAndPosition(EditorPauseLayer* pauseLayer, float scale);

    static void onPause(EditorPauseLayer* pauseLayer);
};