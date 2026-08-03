#include "Geode/cocos/sprite_nodes/CCSpriteBatchNode.h"

// please dont mind clangd automatically including shit

#include <Geode/Geode.hpp>
#include <Geode/binding/ListButtonBar.hpp>
#include <Geode/binding/BoomScrollLayer.hpp>
#include <Geode/binding/ExtendedLayer.hpp>
// #include "../thing.hpp"
#include <Geode/modify/GJShopLayer.hpp>

#include <alphalaneous.alphas-ui-pack/include/API.hpp>

using namespace geode::prelude;
using namespace alpha::prelude;

class $modify(MyShopLayer, GJShopLayer) {
    bool init(ShopType shopType) {
        if (!GJShopLayer::init(shopType))
            return false;

        auto enabled = Mod::get()->getSettingValue<bool>("GJShopLayer");
        if (enabled) {
            auto listButtonBar = this->getChildByType<ListButtonBar>(0);
            if (!listButtonBar)
                return true;

            auto boomScrollLayer = listButtonBar->getChildByType<BoomScrollLayer>(0);
            auto menu = listButtonBar->getChildByType<CCMenu>(0);
            auto dots = listButtonBar->getChildByType<CCSpriteBatchNode>(0);

            if (!boomScrollLayer)
                return true;

            auto extendedLayer = boomScrollLayer->getChildByType<ExtendedLayer>(0);
            if (!extendedLayer)
                return true;

            if (menu) {
                menu->setVisible(false);
                menu->setEnabled(false);
            }

            if (dots) {
                dots->setVisible(false);
            }

            auto winSize = CCDirector::sharedDirector()->getWinSize();

            //CCSize viewportSize = boomScrollLayer->getContentSize();
            //if (viewportSize.width <= 0.f || viewportSize.height <= 0.f) {
                //viewportSize = winSize;
            //}

            // works on my machine!
            constexpr float REF_W = 568.f;
            constexpr float REF_H = 320.f;

            float sx = winSize.width  / REF_W;
            float sy = winSize.height / REF_H;

            CCSize viewportSize = {
                405.f * sx,
                268.f * sy
            };

            auto scroll = AdvancedScrollLayer::create(viewportSize);
            scroll->setAnchorPoint({0.f, 0.f});
            scroll->setPosition({
                83.f * sx,
                -99.f * sy
            });

            scroll->setHorizontalScroll(true);
            scroll->setVerticalScroll(false);
            scroll->setDraggingEnabled(true);
            scroll->setTouchPriority(-500);

            auto content = scroll->getContentLayer();
            auto layout = RowLayout::create()
                ->setAxisReverse(false)
                ->setAxisAlignment(AxisAlignment::Start)
                ->setCrossAxisAlignment(AxisAlignment::Between)
                ->setCrossAxisLineAlignment(AxisAlignment::Even)
                ->setGap(-230.0f) // was -175.0f
                ->setPadding({-113.0f, -151.0f, -434.0f, -114.0f})
                ->setAutoScale(true)
                ->setGrowCrossAxis(true)
                ->ignoreInvisibleChildren(false)
                ->setAutoGrowAxis(0.0f);

            content->setLayout(layout);

            CCArrayExt<CCNode*> childrenExt(extendedLayer->getChildren());
            std::vector<CCNode*> pages(childrenExt.begin(), childrenExt.end());

            for (auto page : pages) {
                if (!page) continue;

                page->removeFromParent();
                content->addChild(page);
            }
            content->updateLayout();
            scroll->setInnerContentSize(content->getContentSize());

            boomScrollLayer->setVisible(false);
            boomScrollLayer->setTouchEnabled(false);

            listButtonBar->addChild(scroll);
        } else {
            log::info("disabled");
        }
        
        return true;
    };
};