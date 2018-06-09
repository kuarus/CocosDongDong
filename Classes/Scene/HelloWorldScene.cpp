#include "HelloWorldScene.hpp"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene( ) {
	Scene* scene = Scene::create( );
	Layer* layer = HelloWorld::create( );
	scene->addChild( layer );
	return scene;
}

// filenameがロードできなかった際のエラー表示.
static void problemLoading(const char* filename) {
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
//初期化処理
bool HelloWorld::init( ) {
	if ( !Layer::init( ) ) {
        return false;
    }
	createCloseButton( ); 
	createLabel( );
	createSprite( );
    return true;
}

//終了用ボタンの作成
//作成後レイヤーに追加
void HelloWorld::createCloseButton( ) {
	//MenuItemImage::create( 通常画像, 選択時画像, 呼び出し関数 )
	MenuItem* closeItem = MenuItemImage::create( "CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1( HelloWorld::menuCloseCallback, this ) );
	bool create_success = !( closeItem == nullptr || closeItem->getContentSize().width <= 0 || closeItem->getContentSize().height <= 0 );
	if ( create_success ) {
		Size visibleSize = Director::getInstance( )->getVisibleSize( );
		Vec2 origin = Director::getInstance( )->getVisibleOrigin( );
		float x = origin.x + visibleSize.width - closeItem->getContentSize( ).width / 2;
		float y = origin.y + closeItem->getContentSize( ).height / 2;
		closeItem->setPosition( Vec2( x, y ) );
	} else {
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	//終了ボタンのメニューの作成
	Menu* menu = Menu::create(closeItem, NULL);
	menu->setPosition( Vec2::ZERO );
	addChild( menu, 1 );// ( メニュー, 描画順 )
}

//"HelloWorld"のラベルを作成
//作成後レイヤーに追加
void HelloWorld::createLabel( ) {
	Label* label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
	bool create_sucsess = label != nullptr;
	if ( create_sucsess ) {
		Size visibleSize = Director::getInstance( )->getVisibleSize( );
		Vec2 origin = Director::getInstance( )->getVisibleOrigin( );
		//画面中央
		Vec2 pos;
		pos.x = origin.x + visibleSize.width / 2;
		pos.y = origin.y + visibleSize.height - label->getContentSize( ).height;
		label->setPosition( pos );
		this->addChild(label, 1);
	} else {
		problemLoading("'fonts/Marker Felt.ttf'");
	}
}

void HelloWorld::createSprite( ) {
	SpriteBatchNode* batch_node = SpriteBatchNode::create( "HelloWorld.png" );
	bool create_sucsess = batch_node != nullptr;
	if ( !create_sucsess ) {
		problemLoading("'HelloWorld.png'");
		return;
	}
	for ( int i = 0; i < 2; i++ ) {
		Sprite* sprite = Sprite::createWithTexture( batch_node->getTexture( ) );
		Size visibleSize = Director::getInstance( )->getVisibleSize( );
		Vec2 origin = Director::getInstance( )->getVisibleOrigin( );
		Vec2 pos;
		pos.x = origin.x + visibleSize.width  / 3 * ( i + 1 );
		pos.y = origin.y + visibleSize.height / 3 * ( i + 1 );
		sprite->setPosition( pos );
		batch_node->addChild( sprite, 0);
	}
	addChild( batch_node );
};

void HelloWorld::menuCloseCallback( Ref* pSender ) {
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end( );

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
