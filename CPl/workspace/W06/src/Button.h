/*
 * Button.h
 *
 *  Created on: Oct 28, 2016
 *      Author: rzi
 */

#ifndef SRC_BUTTON_H_
#define SRC_BUTTON_H_

namespace w6f {

enum button_state {
	On,
	Off,
	Blinking
};


class Button {
button_state state{};

public:
	Button();
	void pressButton();
	bool isOn();
	bool isBlinking();
};

} /* namespace w6f */

#endif /* SRC_BUTTON_H_ */
