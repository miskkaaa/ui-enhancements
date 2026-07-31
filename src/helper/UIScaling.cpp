#include "UIScaling.hpp"

CCPoint UIScaling::getSafeOffset() {
    auto rect = utils::getSafeAreaRect();
    return {rect.getMinX() / 2.f, 0.f};
}


void UIScaling::resizeButton(CCNode *button, float width) {
    button->setContentWidth(width);

    auto btnSprite = button->getChildByType<ButtonSprite>(0);
    if (btnSprite) {
        btnSprite->setContentWidth(width);
        btnSprite->setPositionX(button->getContentWidth() / 2.f);
        auto scale9 = btnSprite->getChildByType<CCScale9Sprite>(0);

        if (scale9) {
            scale9->setContentWidth(width);
            scale9->setPositionX(btnSprite->getContentWidth() / 2.f);
        }

        auto label = btnSprite->getChildByType<CCLabelBMFont>(0);
        if (label) {
            label->setPositionX(btnSprite->getContentWidth() / 2.f);
        }
    }
}