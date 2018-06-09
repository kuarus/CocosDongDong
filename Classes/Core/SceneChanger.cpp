#include "SceneChanger.hpp"
#include "ScenePlay.hpp"
#include "SceneTitle.hpp"
#include "HelloWorldScene.hpp"
#include "cocos2d.h"

USING_NS_CC;

SceneChanger::SceneChanger( ) :
_scene( SCENE::HelloWorld ) {
}

SceneChanger::~SceneChanger( ) { 
}

void SceneChanger::changeScene( SCENE scene ) {
	if ( scene == SCENE::Keep ) {
		return;
	}
	cocos2d::Scene* scene_ptr = nullptr;
	switch ( scene ) {
		case SCENE::HelloWorld:
			scene_ptr = HelloWorld::createScene( );
			break;
		case SCENE::Play:						
			scene_ptr = ScenePlay::create( );
			break;
		case SCENE::Title:
			scene_ptr = SceneTitle::create( );
			break;
	};
	
	if ( scene_ptr != nullptr ) {
		Director::getInstance( )->replaceScene( TransitionSlideInL::create( 1.0f, scene_ptr ) );
		_scene = scene;
	}
}
