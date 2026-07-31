#pragma once

#include <Geode/Geode.hpp>
using namespace geode::prelude;

class UIScaling {
public:
    static CCPoint  getSafeOffset();
    static void     resizeButton(CCNode *button, float width);
};