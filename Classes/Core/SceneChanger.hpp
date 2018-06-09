#pragma once
#include "define.h"

class SceneChanger {
private:
	SceneChanger( );
	virtual ~SceneChanger( );
public:
	SINGLTON_GET_INSTANCE( SceneChanger );
public:
	enum class SCENE {
		HelloWorld,
		Title,
		Play,
		Keep,
	};
public:
	void changeScene( SCENE scene );
private:
	SCENE _scene;
};
	
