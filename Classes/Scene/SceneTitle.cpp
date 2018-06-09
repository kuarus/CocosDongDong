#include "SceneTitle.hpp"

USING_NS_CC;

Scene* SceneTitle::createScene( ) {
	Scene* scene = Scene::create( );
	Layer* layer = SceneTitle::create( );
	scene->addChild( layer );
	return scene;
}

bool SceneTitle::init( ) {
	if ( !Layer::init( ) ) {
		return false;
	}
	MoveBy* move = MoveBy::create( 1.0f, Vec2::ZERO );
	Sprite sprite;
	sprite->runAction( move );
	return true;
}

void SceneTitle::update( ) {
}
