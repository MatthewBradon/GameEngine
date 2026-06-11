#include "Core/Event/EngineInput.h"
#include <GLFW/glfw3.h>

namespace EngineInput
{
    const char* ToString(int button) {
        switch (button)
        {
            case SPACE: return "Space";
            case APOSTROPHE: return "Apostrophe";
            case COMMA: return "Comma";
            case MINUS: return "Minus";
            case PERIOD: return "Period";
            case SLASH: return "Slash";
            case SEMICOLON: return "Semicolon";
            case EQUAL: return "Equal";

            case NUMBER0: return "0";
            case NUMBER1: return "1";
            case NUMBER2: return "2";
            case NUMBER3: return "3";
            case NUMBER4: return "4";
            case NUMBER5: return "5";
            case NUMBER6: return "6";
            case NUMBER7: return "7";
            case NUMBER8: return "8";
            case NUMBER9: return "9";

            case A: return "A";
            case B: return "B";
            case C: return "C";
            case D: return "D";
            case E: return "E";
            case F: return "F";
            case G: return "G";
            case H: return "H";
            case I: return "I";
            case J: return "J";
            case K: return "K";
            case L: return "L";
            case M: return "M";
            case N: return "N";
            case O: return "O";
            case P: return "P";
            case Q: return "Q";
            case R: return "R";
            case S: return "S";
            case T: return "T";
            case U: return "U";
            case V: return "V";
            case W: return "W";
            case X: return "X";
            case Y: return "Y";
            case Z: return "Z";

            case LSHIFT: return "Left Shift";
            case RSHIFT: return "Right Shift";
            case LCTRL: return "Left Control";
            case RCTRL: return "Right Control";
            case LALT: return "Left Alt";
            case RALT: return "Right Alt";
        
            case LEFT_BRACKET: return "Left Bracket";
            case BACKSLASH: return "Backslash";
            case RIGHT_BRACKET: return "Right Bracket";
            case GRAVEACCENT: return "Grave Accent";
            case ESCAPE: return "Escape";

            case ENTER: return "Enter";
            case TAB: return "Tab";
            case BACKSPACE: return "Backspace";
            case INSERT: return "Insert";
            case DELETE: return "Delete";
            case RIGHT: return "Right Arrow";
            case LEFT: return "Left Arrow";
            case DOWN: return "Down Arrow";
            case UP: return "Up Arrow";
            case PAGE_UP: return "Page Up";
            case PAGE_DOWN: return "Page Down";
            case HOME: return "Home";
            case END: return "End";
            case CAPS_LOCK: return "Caps Lock";

            case F1: return "F1";
            case F2: return "F2";
            case F3: return "F3";
            case F4: return "F4";
            case F5: return "F5";
            case F6: return "F6";
            case F7: return "F7";
            case F8: return "F8";
            case F9: return "F9";
            case F10: return "F10";
            case F11: return "F11";
            case F12: return "F12";

            case KP_0: return "Keypad 0";
            case KP_1: return "Keypad 1";
            case KP_2: return "Keypad 2";
            case KP_3: return "Keypad 3";
            case KP_4: return "Keypad 4";
            case KP_5: return "Keypad 5";
            case KP_6: return "Keypad 6";
            case KP_7: return "Keypad 7";
            case KP_8: return "Keypad 8";
            case KP_9: return "Keypad 9";
            case KP_DECIMAL: return "Keypad Decimal";
            case KP_DIVIDE: return "Keypad Divide";
            case KP_MULTIPLY: return "Keypad Multiply";
            case KP_SUBTRACT: return "Keypad Subtract";
            case KP_ADD: return "Keypad Add";
            case KP_ENTER: return "Keypad Enter";

            case MOUSE_LEFT: return "Mouse Left";
            case MOUSE_RIGHT: return "Mouse Right";
            case MOUSE_MIDDLE: return "Mouse Middle";

            case UNKNOWN: return "Unknown";

            default: return "Unknown";
        }
    }


}