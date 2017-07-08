
#ifndef __controller_H__
#define __controller_h__

#define UNUSED(x) (void)(x)

enum {
	BUTTON_ON = 0,
	BUTTON_AC,
	BUTTON_OFF
};

int setupConnectivity( void );
int changeInput( int, int );

#endif
