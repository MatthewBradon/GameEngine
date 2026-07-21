#include "Core/Event/EngineInput.h"

namespace EngineInput
{
    const char* ToString(int button) {
        switch (button)
        {
            case KEY_SPACE: return "Space";
            case KEY_APOSTROPHE: return "Apostrophe";
            case KEY_COMMA: return "Comma";
            case KEY_MINUS: return "Minus";
            case KEY_PERIOD: return "Period";
            case KEY_SLASH: return "Slash";
            case KEY_SEMICOLON: return "Semicolon";
            case KEY_EQUAL: return "Equal";

            case KEY_0: return "0";
            case KEY_1: return "1";
            case KEY_2: return "2";
            case KEY_3: return "3";
            case KEY_4: return "4";
            case KEY_5: return "5";
            case KEY_6: return "6";
            case KEY_7: return "7";
            case KEY_8: return "8";
            case KEY_9: return "9";

            case KEY_A: return "A";
            case KEY_B: return "B";
            case KEY_C: return "C";
            case KEY_D: return "D";
            case KEY_E: return "E";
            case KEY_F: return "F";
            case KEY_G: return "G";
            case KEY_H: return "H";
            case KEY_I: return "I";
            case KEY_J: return "J";
            case KEY_K: return "K";
            case KEY_L: return "L";
            case KEY_M: return "M";
            case KEY_N: return "N";
            case KEY_O: return "O";
            case KEY_P: return "P";
            case KEY_Q: return "Q";
            case KEY_R: return "R";
            case KEY_S: return "S";
            case KEY_T: return "T";
            case KEY_U: return "U";
            case KEY_V: return "V";
            case KEY_W: return "W";
            case KEY_X: return "X";
            case KEY_Y: return "Y";
            case KEY_Z: return "Z";

            case KEY_LSHIFT: return "Left Shift";
            case KEY_RSHIFT: return "Right Shift";
            case KEY_LCTRL: return "Left Control";
            case KEY_RCTRL: return "Right Control";
            case KEY_LALT: return "Left Alt";
            case KEY_RALT: return "Right Alt";
        
            case KEY_LEFT_BRACKET: return "Left Bracket";
            case KEY_BACKSLASH: return "Backslash";
            case KEY_RIGHT_BRACKET: return "Right Bracket";
            case KEY_GRAVEACCENT: return "Grave Accent";
            case KEY_ESCAPE: return "Escape";

            case KEY_ENTER: return "Enter";
            case KEY_TAB: return "Tab";
            case KEY_BACKSPACE: return "Backspace";
            case KEY_INSERT: return "Insert";
            case KEY_DELETE: return "Delete";
            case KEY_RIGHT: return "Right Arrow";
            case KEY_LEFT: return "Left Arrow";
            case KEY_DOWN: return "Down Arrow";
            case KEY_UP: return "Up Arrow";
            case KEY_PAGE_UP: return "Page Up";
            case KEY_PAGE_DOWN: return "Page Down";
            case KEY_HOME: return "Home";
            case KEY_END: return "End";
            case KEY_CAPS_LOCK: return "Caps Lock";

            case KEY_F1: return "F1";
            case KEY_F2: return "F2";
            case KEY_F3: return "F3";
            case KEY_F4: return "F4";
            case KEY_F5: return "F5";
            case KEY_F6: return "F6";
            case KEY_F7: return "F7";
            case KEY_F8: return "F8";
            case KEY_F9: return "F9";
            case KEY_F10: return "F10";
            case KEY_F11: return "F11";
            case KEY_F12: return "F12";

            case KEY_KP_0: return "Keypad 0";
            case KEY_KP_1: return "Keypad 1";
            case KEY_KP_2: return "Keypad 2";
            case KEY_KP_3: return "Keypad 3";
            case KEY_KP_4: return "Keypad 4";
            case KEY_KP_5: return "Keypad 5";
            case KEY_KP_6: return "Keypad 6";
            case KEY_KP_7: return "Keypad 7";
            case KEY_KP_8: return "Keypad 8";
            case KEY_KP_9: return "Keypad 9";
            case KEY_KP_DECIMAL: return "Keypad Decimal";
            case KEY_KP_DIVIDE: return "Keypad Divide";
            case KEY_KP_MULTIPLY: return "Keypad Multiply";
            case KEY_KP_SUBTRACT: return "Keypad Subtract";
            case KEY_KP_ADD: return "Keypad Add";
            case KEY_KP_ENTER: return "Keypad Enter";

            case MOUSE_LEFT: return "Mouse Left";
            case MOUSE_RIGHT: return "Mouse Right";
            case MOUSE_MIDDLE: return "Mouse Middle";

            case UNKNOWN: return "Unknown";

            default: return "Unknown";
        }
    }


}