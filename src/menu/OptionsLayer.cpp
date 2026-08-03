#include <Geode/Geode.hpp>
#include <Geode/modify/OptionsLayer.hpp>
#include <Geode/ui/SliderNode.hpp>
#include "../helper/UIScaling.hpp"

// #include "../thing.hpp"

using namespace geode::prelude;

class $modify(MyOptionsLayer, OptionsLayer) {
    void customSetup() {
        OptionsLayer::customSetup();
        auto enabled = Mod::get()->getSettingValue<bool>("OptionsLayer");
        if (enabled) {
            //this->onOptionsLayer();
            auto fmod = FMODAudioEngine::get();
            auto targetLayer = m_mainLayer ? m_mainLayer : static_cast<CCNode*>(this);

            if (m_musicSlider) m_musicSlider->setVisible(false);
            if (m_sfxSlider) m_sfxSlider->setVisible(false);

            if (auto oldMusicSlider = targetLayer->getChildByID("music-slider")) oldMusicSlider->setVisible(false);
            if (auto oldSfxSlider = targetLayer->getChildByID("sfx-slider")) oldSfxSlider->setVisible(false);
            if (auto oldMusicLabel = targetLayer->getChildByID("music-label")) oldMusicLabel->setVisible(false);
            if (auto oldSfxLabel = targetLayer->getChildByID("sfx-label")) oldSfxLabel->setVisible(false);

            auto musicLabelContainer = CCNode::create();
            musicLabelContainer->setAnchorPoint({0.5f, 0.5f});
            musicLabelContainer->setID("music-label-container"_spr);
            musicLabelContainer->setLayout(
                SimpleRowLayout::create()
                    ->setGap(10.f)
                    ->setMainAxisScaling(AxisScaling::Grow)
                    ->setCrossAxisScaling(AxisScaling::Grow)
                    ->setCrossAxisAlignment(CrossAxisAlignment::Start)
            );
            targetLayer->addChild(musicLabelContainer);

            auto musicLabel = CCLabelBMFont::create("Music:", "bigFont.fnt");
            musicLabel->setID("music-label"_spr);
            //musicLabel->setScale(0.8f);
            musicLabelContainer->addChild(musicLabel);

            auto musicInput = geode::TextInput::create(50.f, "%");
            musicInput->setScale(1.2f);
            musicLabelContainer->addChild(musicInput);

            musicLabelContainer->updateLayout();

            auto musicSlider = SliderNode::create([fmod](SliderNode* sender, float value) {
                value = std::clamp(value, 0.f, 100.f);
                float volume = value / 100.f;

                fmod->m_musicVolume = volume;
                if (fmod->m_backgroundMusicChannel) {
                    fmod->m_backgroundMusicChannel->setVolume(volume);
                }
            });
            musicSlider->setMax(100.f);
            musicSlider->setID("music-slider"_spr);
            musicSlider->linkTextInput(musicInput, 0);
            musicSlider->setValue(fmod->m_musicVolume * 100.f);
            targetLayer->addChild(musicSlider);

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
            targetLayer->addChild(sfxLabelContainer);

            auto sfxLabel = CCLabelBMFont::create("SFX:", "bigFont.fnt");
            sfxLabel->setID("sfx-label"_spr);
            //sfxLabel->setScale(0.8f);
            sfxLabelContainer->addChild(sfxLabel);

            auto sfxInput = geode::TextInput::create(50.f, "%");
            sfxInput->setScale(1.2f);
            sfxLabelContainer->addChild(sfxInput);

            sfxLabelContainer->updateLayout();

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
            targetLayer->addChild(sfxSlider);

            CCSize contentSize = targetLayer->getContentSize();
            CCPoint center = contentSize / 2.f;

            float sliderScale = 0.75f;
            float containerScale = 0.55f;

            float y = center.y - 70.f;

            float leftX = center.x - 87.f;
            float rightX = center.x + 87.f;

            musicSlider->setScale(sliderScale);
            musicSlider->setPosition({leftX, y});

            musicLabelContainer->setScale(containerScale);
            musicLabelContainer->setPosition({leftX, y + 23.f});

            sfxSlider->setScale(sliderScale);
            sfxSlider->setPosition({rightX, y});

            sfxLabelContainer->setScale(containerScale);
            sfxLabelContainer->setPosition({rightX, y + 23.f});

            CCNode* musicToggle = nullptr;
            if (auto vaultMenu = targetLayer->getChildByID("vault-menu")) {
                musicToggle = vaultMenu->getChildByID("menu-music-toggle");
            }
            if (!musicToggle) {
                musicToggle = targetLayer->getChildByID("menu-music-toggle");
            }

            auto musicToggleLabelNode = targetLayer->getChildByID("menu-music-label");

            if (musicToggle) {
                musicToggle->setScale(0.75f);  
                auto winSize = CCDirector::get()->getWinSize();  

                float bottomMargin = 95.5f * 4;
                // float leftMargin = 120.f + UIScaling::getSafeOffset().x;
                // float bottomMargin = (winSize.height / 2.f);
                float leftMargin = (winSize.width / 2.f) / 2.3f;
                CCPoint toggleWorldPos = {leftMargin, bottomMargin};

                if (auto parent = musicToggle->getParent()) {
                    musicToggle->setPosition(parent->convertToNodeSpace(toggleWorldPos));
                } else {
                    musicToggle->setPosition(toggleWorldPos);
                }

                if (musicToggleLabelNode) {
                    if (auto label = typeinfo_cast<CCLabelBMFont*>(musicToggleLabelNode)) {
                        label->setString("Menu Music"); // cant do shit otherwise
                    }

                    musicToggleLabelNode->setAnchorPoint({0.f, 0.5f});
                    musicToggleLabelNode->setScale(0.35f);
                    float toggleWidth = musicToggle->getScaledContentWidth();
                    CCPoint labelWorldPos = {toggleWorldPos.x + (toggleWidth / 2.f) + 8.f, bottomMargin};

                    if (auto parent = musicToggleLabelNode->getParent()) {
                        musicToggleLabelNode->setPosition(parent->convertToNodeSpace(labelWorldPos));
                    } else {
                        musicToggleLabelNode->setPosition(labelWorldPos);
                    }
                }
            }
        } else {
            log::info("disabled");
        }
    }
};