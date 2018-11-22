#ifndef MANUFACTURY_KEY_CODES_H
#define MANUFACTURY_KEY_CODES_H

#ifdef KEY_BACKSPACE
# undef KEY_BACKSPACE
#endif
#define KEY_BACKSPACE 8

#ifdef KEY_HOME
# undef KEY_HOME
#endif
#define KEY_HOME 60609

#ifdef KEY_END
# undef KEY_END
#endif
#define KEY_END 60615

#ifdef KEY_ENTER
# undef KEY_ENTER
#endif
#define KEY_ENTER 10

#ifdef KEY_TAB
# undef KEY_TAB
#endif
#define KEY_TAB 9

#ifdef KEY_PGDOWN
# undef KEY_PGDOWN
#endif
#define KEY_PGDOWN 60617

#ifdef KEY_PGUP
# undef KEY_PGUP
#endif
#define KEY_PGUP 60611

#ifdef KEY_ESC
# undef KEY_ESC
#endif
#define KEY_ESC 27

#define KEY_DELETE KEY_DC
#define KEY_INSERT KEY_IC
#define KEY_CTRL PDC_KEY_MODIFIER_CONTROL
#define KEY_SHIFT PDC_KEY_MODIFIER_SHIFT
#define KEY_ALT PDC_KEY_MODIFIER_ALT

#endif //MANUFACTURY_KEY_CODES_H
