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

#include "AppDelegate.h"
#include "HelloWorldScene.hpp"

#define USE_AUDIO_ENGINE 1
#define USE_SIMPLE_AUDIO_ENGINE 0

//どちらかを0にする
#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size( 1280,  720 );//解像度
static cocos2d::Size smallResolutionSize  = cocos2d::Size(  480,  320 );
static cocos2d::Size mediumResolutionSize = cocos2d::Size( 1280,  720 );
static cocos2d::Size largeResolutionSize  = cocos2d::Size( 1920, 1080 );

AppDelegate::AppDelegate( ) {
}

AppDelegate::~AppDelegate( ) {
#if USE_AUDIO_ENGINE
    AudioEngine::end( );
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end( );
#endif
}

//OpenGL初期化
//別のコンテキストが必要な場合は、glContextAttrsの値を変更
void AppDelegate::initGLContextAttrs( ) {
	//{ red, green, blue, alpha, depth, stencil, multisamplesCount }
    GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8, 0 };
    GLView::setGLContextAttrs( glContextAttrs );
}

// package manager使用時のみ使用する関数
static int register_all_packages( ) {
    return 0; //flag for packages manager
}

//アプリの初期化処理
bool AppDelegate::applicationDidFinishLaunching() {
    Director* director = Director::getInstance( );//初期化も含める
    GLView* glview = director->getOpenGLView();
    if ( !glview ) {
		//glviewを生成してdirectorへset
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("test", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("test");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats( true );

    // set FPS
    director->setAnimationInterval( 1.0f / 60 );

    //解像度のサイズをset
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    
    //フレームの大きさを解像度に合わせてサイズ調整
	Size frameSize = glview->getFrameSize();
	bool size_original = frameSize.height > mediumResolutionSize.height;
	bool size_midium = !size_original && frameSize.height > smallResolutionSize.height;
	bool size_small = !size_original && !size_midium;
	if ( size_original ) {
		float scale = MIN( largeResolutionSize.height / designResolutionSize.height, largeResolutionSize.width / designResolutionSize.width );
        director->setContentScaleFactor( scale );
    }
	if ( size_midium ) {       
		float scale = MIN( mediumResolutionSize.height / designResolutionSize.height, mediumResolutionSize.width / designResolutionSize.width );
        director->setContentScaleFactor( scale );
    }
	if ( size_small ) {
		float scale = MIN( smallResolutionSize.height / designResolutionSize.height, smallResolutionSize.width / designResolutionSize.width );
        director->setContentScaleFactor( scale );
    }

    register_all_packages();

    // create a scene. it's an autorelease object
    Scene* scene = HelloWorld::createScene( );

    // run
    director->runWithScene( scene );

    return true;
}

//アプリケーションがバックグラウンドへ行った際の処理
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

//バックグラウンドから戻った際の処理
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}
