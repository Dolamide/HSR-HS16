/*
 * Button.cpp
 *
 *  Created on: Oct 28, 2016
 *      Author: rzi
 */

#include "Button.h"

namespace w6f {

void Button::pressButton(){
	switch(state){
	case Off:
		state = On;
		break;
	case On:
		state = Blinking;
		break;
	case Blinking:
		state = Off;
		break;
	}
}

bool Button::isBlinking(){
	return state == Blinking;

}

bool Button::isOn(){
	return state != Off;
}

Button::Button()
	: state {Off} {
}
} /* namespace w6f */
