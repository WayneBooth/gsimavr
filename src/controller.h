
#ifndef __controller_H__
#define __controller_h__

enum {
	BUTTON_ON = 0,
	BUTTON_AC,
	BUTTON_OFF
};

int setupConnectivity( void );
int changeInput( int, int );

#endif
