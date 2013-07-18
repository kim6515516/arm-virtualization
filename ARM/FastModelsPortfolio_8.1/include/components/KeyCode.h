/*!
 * \file    KeyCode.h
 * \brief   Codes for key up/down events.
 * \date    Copyright 2005-2008 ARM Limited. All rights reserved.
 *
 * Enumerate code values for all keys on the keyboard.
 */

#ifndef KEYCODE_H
#define KEYCODE_H

enum ATKeyCode
{
    KC_NONE = 0,
    KC_ESCAPE,
    KC_F1,      
    KC_F2,      
    KC_F3,      
    KC_F4,      
    KC_F5,      
    KC_F6,      
    KC_F7,          
    KC_F8,      
    KC_F9,      
    KC_F10, 
    KC_F11, 
    KC_F12, 
    KC_PRINT,
    KC_SCROLL,  
    KC_BREAK,

    KC_F13, 
    KC_F14, 
    KC_F15, 

    KC_GRAVE,       
    KC_1,   
    KC_2,       
    KC_3,   
    KC_4,       
    KC_5,       
    KC_6,       
    KC_7,
    KC_8,           
    KC_9,           
    KC_0,       
    KC_MINUS,
    KC_EQUALS,      
    KC_BACK,    
    
    KC_TAB,
    KC_Q,   
    KC_W,       
    KC_E,   
    KC_R,       
    KC_T,       
    KC_Y,           
    KC_U,       
    KC_I,       
    KC_O,       
    KC_P,       
    KC_LBRACKET,    
    KC_RBRACKET,
    KC_BACKSLASH,

    KC_LCONTROL,
    KC_A,       
    KC_S,       
    KC_D,       
    KC_F,   
    KC_G,   
    KC_H,       
    KC_J,       
    KC_K,           
    KC_L,       
    KC_SEMICOLON,   
    KC_APOSTROPHE,
    KC_RETURN,  

    KC_LSHIFT,  
    KC_Z,       
    KC_X,       
    KC_C,       
    KC_V,       
    KC_B,       
    KC_N,       
    KC_M,       
    KC_COMMA,   
    KC_PERIOD,      
    KC_SLASH,    
    KC_RSHIFT,  

    KC_CAPS,
    KC_LALT,    
    KC_SPACE,   
    KC_RALT,        
    KC_RCONTROL,

    KC_INSERT,      
    KC_HOME,          
    KC_PGUP,    

    KC_DELETE,  
    KC_END,    
    KC_PGDN,        

    KC_UP,          
    KC_LEFT,    
    KC_DOWN,    
    KC_RIGHT,   
    
    KC_NUMLOCK,
    KC_DIVIDE,  
    KC_MULTIPLY,    
    KC_HASH,

    KC_NUMPAD7,
    KC_NUMPAD8, 
    KC_NUMPAD9,
    KC_SUBTRACT,

    KC_NUMPAD4,
    KC_NUMPAD5,
    KC_NUMPAD6, 
    KC_ADD,  

    KC_NUMPAD1,  
    KC_NUMPAD2,
    KC_NUMPAD3, 
    KC_NUMPADENTER,

    KC_NUMPAD0,
    KC_DECIMAL,

    KC_MOUSEMENU,

    // multimedia keys not necessarily present
    KC_LWIN,
    KC_RWIN,
    KC_PREVTRACK,
    KC_NEXTTRACK,
    KC_MUTE,
    KC_CALCULATOR,
    KC_PLAYPAUSE,
    KC_MEDIASTOP,
    KC_VOLUMEDOWN,
    KC_VOLUMEUP,
    KC_WEBHOME,
    KC_POWER,
    KC_SLEEP,
    KC_WAKE,
    KC_WEBSEARCH,
    KC_WEBFAVORITES,
    KC_WEBREFRESH,
    KC_WEBSTOP,
    KC_WEBFORWARD,
    KC_WEBBACK,
    KC_MYCOMPUTER,
    KC_MAIL,
    KC_MEDIASELECT,

    KC_MAX
};

#endif
