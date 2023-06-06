#include "../Inc/key.h"
#include "stdbool.h"

static bool any_key_press = false;

extern bool check_key_press(void) {
	if (any_key_press) {
		any_key_press = false;
		return true;
	}
	return false;
}

// key inturrpt function
// if any key is pressed, change the any_key_press to false
