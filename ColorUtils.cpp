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
const char* colorToAnsi(Color c) {
	switch (c) {
	case Color::RED:    return "\033[31m";
	case Color::BLUE:   return "\033[34m";
	case Color::YELLOW: return "\033[33m";
	case Color::BLACK:  return "\033[30;100m";
	default:            return "\033[0m";
	}
}