#include "ColorUtils.h"


const char* colorToString(Color c) {
	switch (c) {
	case Color::YELLOW:
		return "yellow";
	case Color::RED:
		return "red";
	case Color::BLUE:
		return "blue";
	case Color::BLACK:
		return "black";
	case Color::NONE:
		return "none";
	default: "unknown";
	}
}