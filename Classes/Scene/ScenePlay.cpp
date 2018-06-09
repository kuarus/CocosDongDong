#include "ScenePlay.hpp"

USING_NS_CC;

Scene* ScenePlay::createScene( ) {
	Scene* scene = Scene::create( );
	Layer* layer = ScenePlay::create( );
	scene->addChild( layer );
	return scene;
}

bool ScenePlay::init( ) {
	if ( !Layer::init( ) ) {
		return false;
	}
	return true;
}
