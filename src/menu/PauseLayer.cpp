#include "Geode/ui/SimpleAxisLayout.hpp"
#include "Geode/ui/TextInput.hpp"
#include <Geode/Geode.hpp>
using namespace geode::prelude;

#include <Geode/modify/PauseLayer.hpp>
#include <Geode/ui/SliderNode.hpp>

#include "../thing.hpp"
#include <PauseLayer.hpp>

class $modify(PauseLayer) {
    void customSetup() {
        PauseLayer::customSetup();

        auto enabled = thing::IsOptionEnabled("PauseLayer");
        if (!enabled) return;

        UIPauseLayer::onPause(this);
    }
};

void UIPauseLayer::onPause(PauseLayer *pause) {
    auto fmod = FMODAudioEngine::get();
    CCNode *layer = pause;

    auto oldMusicSlider = layer->getChildByID("music-slider");
    auto oldSfxSlider = layer->getChildByID("sfx-slider");
    auto oldMusicLabel = layer->getChildByID("music-label");
    auto oldSfxLabel = layer->getChildByID("sfx-label");

    if (oldMusicSlider) oldMusicSlider->setVisible(false);
    if (oldSfxSlider) oldSfxSlider->setVisible(false);
    if (oldMusicLabel) oldMusicLabel->setVisible(false);
    if (oldSfxLabel) oldSfxLabel->setVisible(false);

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
    musicInput->setPositionY(musicInput->getPositionY() - 3.25f);
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
    sfxInput->setPositionY(sfxInput->getPositionY() - 3.25f);
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

    layer->updateLayout();
}