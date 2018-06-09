#pragma once

#define SINGLTON_GET_INSTANCE( __TYPE__ ) \
static __TYPE__* getInstance( ) { \
	static __TYPE__* instance = new __TYPE__( ); \
	return instance; \
} \
