#include "Geode/ui/NineSlice.hpp"
#include "Geode/ui/SimpleAxisLayout.hpp"
#include "Geode/ui/TextInput.hpp"
#include <Geode/Geode.hpp>
#include <Geode/binding/FLAlertLayer.hpp>
using namespace geode::prelude;

#include <Geode/modify/PauseLayer.hpp>
#include <Geode/ui/SliderNode.hpp>

#include "../thing.hpp"
#include <PauseLayer.hpp>
#include <Blur.hpp>

class $modify(PauseLayer) {
    void customSetup() {
        PauseLayer::customSetup();

        auto enabled = thing::IsOptionEnabled("PauseLayer");
        if (!enabled) return;

        UIPauseLayer::onPause(this);
    }
    
    static void onModify(auto& self) {
        if (!self.setHookPriority("PauseLayer::onPause", Priority::Late)) {
            geode::log::warn("Failed to set hook priority.");
        }
    }
};

void UIPauseLayer::onPause(PauseLayer *pause) {
    auto fmod = FMODAudioEngine::get();
    auto winSize = CCDirector::get()->getWinSize();
    CCNode *layer = pause;

    auto oldMusicSlider = layer->getChildByID("music-slider");
    auto oldSfxSlider = layer->getChildByID("sfx-slider");
    auto oldMusicLabel = layer->getChildByID("music-label");
    auto oldSfxLabel = layer->getChildByID("sfx-label");

    auto bg = layer->getChildByID("background");

    if (oldMusicSlider) oldMusicSlider->setVisible(false);
    if (oldSfxSlider) oldSfxSlider->setVisible(false);
    if (oldMusicLabel) oldMusicLabel->setVisible(false);
    if (oldSfxLabel) oldSfxLabel->setVisible(false);
    if (bg) bg->setVisible(false);
    //BlurAPI::addBlur(bg);

    auto centermenu = layer->getChildByID("center-button-menu");
    if (!centermenu) return;
    // auto levelname = layer->getChildByID("level-name");
    // if (!levelname) return;

    auto plSizeX = layer->getContentSize().width;

    auto leftbuttonmenu = layer->getChildByID("left-button-menu");
    if (!leftbuttonmenu) return;
    leftbuttonmenu->setAnchorPoint({0.5f, 0.5f});
    leftbuttonmenu->setPosition({40.f, 160.f});
    leftbuttonmenu->setLayout(
        ColumnLayout::create()
            ->setAutoScale(true)
            ->setGap(5.f)
            ->setAxisReverse(true)
            ->setAxisAlignment(AxisAlignment::End)
            ->setCrossAxisAlignment(AxisAlignment::Center)
            ->setCrossAxisLineAlignment(AxisAlignment::Center)
            ->setCrossAxisOverflow(true));

    auto rightbuttonmenu = layer->getChildByID("right-button-menu");
    if (!rightbuttonmenu) return;
    rightbuttonmenu->setAnchorPoint({0.5f, 0.5f});
    rightbuttonmenu->setPosition({plSizeX - 40.f, 160.f});
    rightbuttonmenu->setLayout(
        ColumnLayout::create()
            ->setAutoScale(true)
            ->setGap(5.f)
            ->setAxisAlignment(AxisAlignment::End)
            ->setCrossAxisAlignment(AxisAlignment::Center)
            ->setCrossAxisLineAlignment(AxisAlignment::Center)
            ->setCrossAxisOverflow(true));

    auto bottombuttonmenu = layer->getChildByID("bottom-button-menu");
    if (!bottombuttonmenu) return;

    auto practicebar = layer->getChildByID("practice-progress-bar");
    auto pbsize = practicebar->getContentSize();

    // centermenu->setScale(0.750f);
    centermenu->setPositionY(centermenu->getPositionY() + 5.f); // centermenu->setPosition({centermenu->getPositionX(), centermenu->getPositionY() + 5.f});
    centermenu->setContentSize({pbsize.width, centermenu->getContentSize().height});
    centermenu->setScale(0.75f);
    centermenu->updateLayout();

    auto nineslicemenu = NineSlice::create("square04_001.png");
    auto bitchsize = centermenu->getContentSize();
    nineslicemenu->setColor({0, 0, 0});
    nineslicemenu->setOpacity(175);
    // nineslicemenu->setScaleMultiplier(0.8f);
    nineslicemenu->setID("centermenu-nineslice-sprite"_spr);
    nineslicemenu->setZOrder(-1);
    nineslicemenu->setPosition(centermenu->getPositionX(), centermenu->getPositionY());
    nineslicemenu->setContentSize({
        bitchsize.width,
        bitchsize.height * 0.8f
    });
    // nineslicemenu->setScale(0.75f);
    nineslicemenu->setScaleMultiplier(0.67f);
    layer->addChild(nineslicemenu);

    auto background = NineSlice::create(thing::bitch::round);
    background->setColor({0, 0, 0});
    background->setOpacity(20);
    background->setScaleMultiplier(0.8f);
    background->setID("background"_spr);
    background->setZOrder(bg->getZOrder() - 5);
    background->setContentSize({winSize.width, winSize.height});
    // penis
    background->setAnchorPoint({0.f,0.f});
    /*
    auto nineslicelevel = NineSlice::create("square04_001.png");
    auto leveltextsize = levelname->getContentSize();
    nineslicelevel->setColor({0,0,0});
    nineslicelevel->setOpacity(175);
    nineslicelevel->setScaleMultiplier(0.8f);
    nineslicelevel->setID("level-nineslice-sprite"_spr);
    nineslicelevel->setZOrder(-1);

    nineslicelevel->setPosition(leveltextsize / 2.f);
    levelname->addChild(nineslicelevel);
    */

    // DO NOT DOWNLOAD TWITTER
    // ITS NOT THE APP FOR YOU
    // YOU ARE KANYE WEST
    // CLOSE THE APP STORE

    // NC left
    auto ninesliceLeft = NineSlice::create(thing::bitch::roundest);
    auto leftSize = leftbuttonmenu->getScaledContentSize();
    ninesliceLeft->setColor({0,0,0});
    ninesliceLeft->setOpacity(175);
    ninesliceLeft->setScaleMultiplier(0.7f);
    ninesliceLeft->setID("left-nineslice-sprite"_spr);
    ninesliceLeft->setZOrder(-1);

    ninesliceLeft->setContentSize({
        leftSize.width + 10.f,
        leftSize.height + 10.f
    });

    // NC right
    ninesliceLeft->setPosition(leftbuttonmenu->getPosition());
    ninesliceLeft->setAnchorPoint({0.5f,0.5f});

    auto ninesliceRight = NineSlice::create(thing::bitch::roundest);
    auto rightSize = rightbuttonmenu->getScaledContentSize();
    ninesliceRight->setColor({0,0,0});
    ninesliceRight->setOpacity(175);
    ninesliceRight->setScaleMultiplier(0.7f);
    ninesliceRight->setID("right-nineslice-sprite"_spr);
    ninesliceRight->setZOrder(-1);

    ninesliceRight->setContentSize({
        rightSize.width + 10.f,
        rightSize.height + 10.f
    });

    ninesliceRight->setPosition(rightbuttonmenu->getPosition());

    // NC bottom
    auto ninesliceBottom = NineSlice::create(thing::bitch::roundest);
    auto bottomShit = bottombuttonmenu->getScaledContentSize();
    ninesliceBottom->setColor({0,0,0});
    ninesliceBottom->setOpacity(175);
    ninesliceBottom->setScaleMultiplier(0.7f);
    ninesliceBottom->setID("bottom-nineslice-sprite"_spr);
    ninesliceBottom->setZOrder(-1);

    ninesliceBottom->setContentSize({
        bottomShit.width + 10.f,
        bottomShit.height + 10.f
    });

    ninesliceBottom->setPosition(bottombuttonmenu->getPosition());
    ninesliceBottom->setAnchorPoint({0.5f,0.5f});

    auto musicLabelContainer = CCNode::create();
    musicLabelContainer->setAnchorPoint({0.5f, 0.5f});
    musicLabelContainer->setID("music-label-container"_spr);
    musicLabelContainer->setLayout(
        SimpleRowLayout::create()
            ->setGap(13.f)
            ->setMainAxisScaling(AxisScaling::Grow)
            ->setCrossAxisScaling(AxisScaling::Grow)
            ->setCrossAxisAlignment(CrossAxisAlignment::Start)
    );

    auto musicLabel = CCLabelBMFont::create("Music:", "bigFont.fnt");
    musicLabel->setID("music-label"_spr);
    //musicLabel->setScale(0.8f);
    musicLabelContainer->addChild(musicLabel);

    auto musicInput = geode::TextInput::create(50.f, "%");
    //musicInput->setScale(0.8f);
    musicLabelContainer->addChild(musicInput);

    musicLabelContainer->updateLayout();
    musicLabel->setPositionX(musicLabel->getPositionX() + 10.f);
    musicLabel->setPositionY(musicLabel->getPositionY() - 5.f);
    musicInput->setPositionY(musicInput->getPositionY() - 7.5f);
    musicInput->setPositionX(musicInput->getPositionX() + 15.f);

    auto musicSlider = SliderNode::create(
        [fmod](SliderNode *sender, float val) {
            // im actively going insane :3
            val = std::clamp(val, 0.f, 100.f);
            float vol = val / 100.f;

            fmod->m_musicVolume = vol;
            if (fmod->m_backgroundMusicChannel) {
                fmod->m_backgroundMusicChannel->setVolume(vol);
            }
        }
    );

    musicSlider->setMax(100.f);
    musicSlider->setID("music-slider"_spr);
    musicSlider->linkTextInput(musicInput, 0);
    musicSlider->setValue(fmod->m_musicVolume * 100.f);

    auto sfxLabelContainer = CCNode::create();
    sfxLabelContainer->setAnchorPoint({0.5f, 0.5f});
    sfxLabelContainer->setID("sfx-label-container"_spr);
    sfxLabelContainer->setLayout(
        SimpleRowLayout::create()
            ->setGap(10.f)
            ->setMainAxisScaling(AxisScaling::Grow)
            ->setCrossAxisScaling(AxisScaling::Grow)
            ->setCrossAxisAlignment(CrossAxisAlignment::Start)
    );

    auto sfxLabel = CCLabelBMFont::create("SFX:", "bigFont.fnt");
    sfxLabel->setID("sfx-label"_spr);
    //sfxLabel->setScale(0.8f);
    sfxLabelContainer->addChild(sfxLabel);

    auto sfxInput = geode::TextInput::create(50.f, "%");
    //sfxInput->setScale(0.8f);
    sfxLabelContainer->addChild(sfxInput);

    sfxLabelContainer->updateLayout();
    sfxLabel->setPositionX(sfxLabel->getPositionX() + 10.f);
    sfxLabel->setPositionY(sfxLabel->getPositionY() - 5.f);
    sfxInput->setPositionY(sfxInput->getPositionY() - 7.5f);
    sfxInput->setPositionX(sfxInput->getPositionX() + 15.f);

    auto sfxSlider = SliderNode::create([fmod](SliderNode* sender, float value) {
        value = std::clamp(value, 0.f, 100.f);
        float volume = value / 100.f;

        fmod->m_sfxVolume = volume;
        if (fmod->m_globalChannel) {
            fmod->m_globalChannel->setVolume(volume);
        }
    });

    sfxSlider->setMax(100.f);
    sfxSlider->setID("sfx-slider"_spr);
    sfxSlider->linkTextInput(sfxInput, 0);
    sfxSlider->setValue(fmod->m_sfxVolume * 100.f);

    CCSize contentSize = layer->getContentSize();
    CCPoint center = contentSize / 2.f;

    float leftX = center.x - 100.f;
    float rightX = center.x + 100.f;
    float sliderScale = 0.75f;
    float containerScale = 0.55f;
    float y = center.y / 2.5f; // 70.f;

    musicSlider->setScale(sliderScale);
    musicSlider->setPosition({leftX, y});

    musicLabelContainer->setScale(containerScale);
    musicLabelContainer->setPosition({leftX, y + 25.f});

    sfxSlider->setScale(sliderScale);
    sfxSlider->setPosition({rightX, y});

    sfxLabelContainer->setScale(containerScale);
    sfxLabelContainer->setPosition({rightX, y + 25.f});

    layer->addChild(musicSlider);
    layer->addChild(musicLabelContainer);
    layer->addChild(sfxSlider);
    layer->addChild(sfxLabelContainer);

    if (thing::IsOptionEnabled("thethings")) {
        layer->addChild(ninesliceLeft);
        layer->addChild(ninesliceRight);
    }
    if (thing::IsOptionEnabled("blur")) {
        BlurAPI::addBlur(background);
    }

    if (thing::IsOptionEnabled("bottombar")) {
        if (!thing::IsOptionEnabled("thethings")) return;
        if (thing::IsOptionEnabled("blur")) {
            BlurAPI::addBlur(ninesliceBottom);
            BlurAPI::getOptions(ninesliceBottom)->passes = 2;
        }
        layer->addChild(ninesliceBottom);
    }
    layer->addChild(background);
    layer->updateLayout();
}