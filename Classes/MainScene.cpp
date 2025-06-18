/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#include "MainScene.h"
#include "ui/CocosGUI.h"
#include "base/CCEventMouse.h"

USING_NS_CC;

Scene* Main::createScene()
{
    return Main::create();
}

bool Main::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    _parallaxNode = ParallaxNode::create();
    this->addChild(_parallaxNode, -1);

    auto background = Sprite::create("background.png");
    if (background) {
        background->setAnchorPoint(Vec2(0, 0));
        background->setScaleX(visibleSize.width / background->getContentSize().width);
        background->setScaleY(visibleSize.height / background->getContentSize().height);
        _parallaxNode->addChild(background, -2, Vec2(0.1f, 0.1f), Vec2(origin.x, origin.y));
    }
    else {
        log("ERROR: Failed to load background.png! Make sure it's in Resources folder and named background.png");
    }

    auto foreground = Sprite::create("foreground.png");
    if (foreground) {
        foreground->setAnchorPoint(Vec2(0, 0));
        foreground->setScaleX(visibleSize.width / foreground->getContentSize().width);
        foreground->setScaleY(0.2f);

        _parallaxNode->addChild(foreground, 0, Vec2(1.0f, 1.0f), Vec2(origin.x, origin.y - 100));
    }
    else {
        log("ERROR: Failed to load foreground.png! Make sure it's in Resources folder and named foreground.png");
    }

    _player = Sprite::create("character.png");
    if (_player) {
        _player->setScale(0.2f);

        float playerBaseY = origin.y;
        if (foreground) {
            playerBaseY = origin.y + (foreground->getContentSize().height * foreground->getScaleY());

            playerBaseY -= 220;
        }

        _player->setPosition(Vec2(visibleSize.width / 4 + origin.x, playerBaseY + _player->getContentSize().height * _player->getScaleY() / 2));

        this->addChild(_player, 1);
    }
    else {
        log("ERROR: Failed to load character.png! Make sure it's in Resources folder and named character.png");
    }

    _scrollSpeed = 100.0f;

    auto jumpButton = ui::Button::create("jumpbutton.png");
    if (jumpButton) {
        jumpButton->setTitleText("Jump");
        jumpButton->setTitleFontSize(16);
        jumpButton->setScale(1.0f);

        jumpButton->setPosition(Vec2(origin.x + visibleSize.width - jumpButton->getContentSize().width * jumpButton->getScaleX() / 2 - 50,
            origin.y + jumpButton->getContentSize().height * jumpButton->getScaleY() / 2 + 50));
        this->addChild(jumpButton, 2);
        jumpButton->addTouchEventListener(CC_CALLBACK_2(Main::jumpButtonCallback, this));
    }
    else {
        log("ERROR: Failed to load jumpbutton.png! Make sure it's in Resources folder and named jumpbutton.png");
    }

    setupTouchHandling();

    this->scheduleUpdate();

    return true;
}

void Main::jumpButtonCallback(Ref* sender, ui::Widget::TouchEventType type)
{
    if (type == ui::Widget::TouchEventType::ENDED)
    {
        if (!_player->getNumberOfRunningActionsByTag(1))
        {
            float jumpHeight = 100.0f;
            float jumpDuration = 0.5f;

            auto jumpUp = MoveBy::create(jumpDuration / 2, Vec2(0, jumpHeight));
            auto jumpDown = jumpUp->reverse();

            auto jumpSequence = Sequence::create(jumpUp, jumpDown, nullptr);
            jumpSequence->setTag(1);
            _player->runAction(jumpSequence);
        }
    }
}

void Main::setupTouchHandling()
{
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);

    Vec2 currentDragStartLocation;

    touchListener->onTouchBegan = [&](Touch* touch, Event* event) {
        currentDragStartLocation = touch->getLocation();
        return true;
        };

    touchListener->onTouchMoved = [&](Touch* touch, Event* event) {
        Vec2 currentDragLocation = touch->getLocation();
        float deltaX = currentDragLocation.x - currentDragStartLocation.x;

        _currentScrollOffset.x += deltaX * 0.5f;

        if (_currentScrollOffset.x > 0) _currentScrollOffset.x = 0;

        _parallaxNode->setPosition(_currentScrollOffset);

        currentDragStartLocation = currentDragLocation;
        };

    touchListener->onTouchEnded = [&](Touch* touch, Event* event) {

        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    auto mouseListener = EventListenerMouse::create();

    bool isLeftMouseButtonDown = false;

    mouseListener->onMouseDown = [&](EventMouse* event) {
        if (static_cast<int>(event->getMouseButton()) == 0) {
            isLeftMouseButtonDown = true;
            currentDragStartLocation = event->getLocation();
        }
        };

    mouseListener->onMouseMove = [&](EventMouse* event) {

        if (isLeftMouseButtonDown) {
            Vec2 currentMouseLocation = event->getLocation();
            float deltaX = currentMouseLocation.x - currentDragStartLocation.x;

            _currentScrollOffset.x += deltaX * 0.5f;

            if (_currentScrollOffset.x > 0) _currentScrollOffset.x = 0;

            _parallaxNode->setPosition(_currentScrollOffset);

            currentDragStartLocation = currentMouseLocation;
        }
        };

    mouseListener->onMouseUp = [&](EventMouse* event) {
        if (static_cast<int>(event->getMouseButton()) == 0) {
            isLeftMouseButtonDown = false;
        }
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void Main::update(float dt)
{
    
    _parallaxNode->setPosition(_currentScrollOffset);
}