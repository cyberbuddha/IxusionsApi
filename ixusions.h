#ifndef _IXUSIONS_H_
#define _IXUSIONS_H_

#ifdef IXUSIONS_STATIC
    #define IXUSIONS_API
#else
    #if defined _WIN32 || defined __CYGWIN__
        #ifdef IXUSIONS_EXPORT
            #ifdef __GNUC__
                #define IXUSIONS_API __attribute__((dllexport))
            #else
                #define IXUSIONS_API __declspec(dllexport)
            #endif
        #else
            #ifdef __GNUC__
                #define IXUSIONS_API __attribute__((dllimport))
            #else
                #define IXUSIONS_API __declspec(dllimport)
            #endif
        #endif
    #else
        #if __GNUC__ >= 4
            #define IXUSIONS_API __attribute__ ((visibility("default")))
        #else
            #define IXUSIONS_API
        #endif
    #endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define IXUSIONS_MAX_KEYBOARD 10

#define IXUSIONS_MAX_MOUSE 10

#define IXUSIONS_MAX_DEVICE ((IXUSIONS_MAX_KEYBOARD) + (IXUSIONS_MAX_MOUSE))

#define IXUSIONS_KEYBOARD(index) ((index) + 1)

#define IXUSIONS_MOUSE(index) ((IXUSIONS_MAX_KEYBOARD) + (index) + 1)

typedef void *IxusionsContext;

typedef int IxusionsDevice;

typedef int IxusionsPrecedence;

typedef unsigned short IxusionsFilter;

typedef int (*IxusionsPredicate)(IxusionsDevice device);

enum IxusionsKeyState
{
    IXUSIONS_KEY_DOWN             = 0x00,
    IXUSIONS_KEY_UP               = 0x01,
    IXUSIONS_KEY_E0               = 0x02,
    IXUSIONS_KEY_E1               = 0x04,
    IXUSIONS_KEY_TERMSRV_SET_LED  = 0x08,
    IXUSIONS_KEY_TERMSRV_SHADOW   = 0x10,
    IXUSIONS_KEY_TERMSRV_VKPACKET = 0x20
};

enum IxusionsFilterKeyState
{
    IXUSIONS_FILTER_KEY_NONE             = 0x0000,
    IXUSIONS_FILTER_KEY_ALL              = 0xFFFF,
    IXUSIONS_FILTER_KEY_DOWN             = IXUSIONS_KEY_UP,
    IXUSIONS_FILTER_KEY_UP               = IXUSIONS_KEY_UP << 1,
    IXUSIONS_FILTER_KEY_E0               = IXUSIONS_KEY_E0 << 1,
    IXUSIONS_FILTER_KEY_E1               = IXUSIONS_KEY_E1 << 1,
    IXUSIONS_FILTER_KEY_TERMSRV_SET_LED  = IXUSIONS_KEY_TERMSRV_SET_LED << 1,
    IXUSIONS_FILTER_KEY_TERMSRV_SHADOW   = IXUSIONS_KEY_TERMSRV_SHADOW << 1,
    IXUSIONS_FILTER_KEY_TERMSRV_VKPACKET = IXUSIONS_KEY_TERMSRV_VKPACKET << 1
};

enum IxusionsMouseState
{
    IXUSIONS_MOUSE_LEFT_BUTTON_DOWN   = 0x001,
    IXUSIONS_MOUSE_LEFT_BUTTON_UP     = 0x002,
    IXUSIONS_MOUSE_RIGHT_BUTTON_DOWN  = 0x004,
    IXUSIONS_MOUSE_RIGHT_BUTTON_UP    = 0x008,
    IXUSIONS_MOUSE_MIDDLE_BUTTON_DOWN = 0x010,
    IXUSIONS_MOUSE_MIDDLE_BUTTON_UP   = 0x020,

    IXUSIONS_MOUSE_BUTTON_1_DOWN      = IXUSIONS_MOUSE_LEFT_BUTTON_DOWN,
    IXUSIONS_MOUSE_BUTTON_1_UP        = IXUSIONS_MOUSE_LEFT_BUTTON_UP,
    IXUSIONS_MOUSE_BUTTON_2_DOWN      = IXUSIONS_MOUSE_RIGHT_BUTTON_DOWN,
    IXUSIONS_MOUSE_BUTTON_2_UP        = IXUSIONS_MOUSE_RIGHT_BUTTON_UP,
    IXUSIONS_MOUSE_BUTTON_3_DOWN      = IXUSIONS_MOUSE_MIDDLE_BUTTON_DOWN,
    IXUSIONS_MOUSE_BUTTON_3_UP        = IXUSIONS_MOUSE_MIDDLE_BUTTON_UP,

    IXUSIONS_MOUSE_BUTTON_4_DOWN      = 0x040,
    IXUSIONS_MOUSE_BUTTON_4_UP        = 0x080,
    IXUSIONS_MOUSE_BUTTON_5_DOWN      = 0x100,
    IXUSIONS_MOUSE_BUTTON_5_UP        = 0x200,

    IXUSIONS_MOUSE_WHEEL              = 0x400,
    IXUSIONS_MOUSE_HWHEEL             = 0x800
};

enum IxusionsFilterMouseState
{
    IXUSIONS_FILTER_MOUSE_NONE               = 0x0000,
    IXUSIONS_FILTER_MOUSE_ALL                = 0xFFFF,

    IXUSIONS_FILTER_MOUSE_LEFT_BUTTON_DOWN   = IXUSIONS_MOUSE_LEFT_BUTTON_DOWN,
    IXUSIONS_FILTER_MOUSE_LEFT_BUTTON_UP     = IXUSIONS_MOUSE_LEFT_BUTTON_UP,
    IXUSIONS_FILTER_MOUSE_RIGHT_BUTTON_DOWN  = IXUSIONS_MOUSE_RIGHT_BUTTON_DOWN,
    IXUSIONS_FILTER_MOUSE_RIGHT_BUTTON_UP    = IXUSIONS_MOUSE_RIGHT_BUTTON_UP,
    IXUSIONS_FILTER_MOUSE_MIDDLE_BUTTON_DOWN = IXUSIONS_MOUSE_MIDDLE_BUTTON_DOWN,
    IXUSIONS_FILTER_MOUSE_MIDDLE_BUTTON_UP   = IXUSIONS_MOUSE_MIDDLE_BUTTON_UP,

    IXUSIONS_FILTER_MOUSE_BUTTON_1_DOWN      = IXUSIONS_MOUSE_BUTTON_1_DOWN,
    IXUSIONS_FILTER_MOUSE_BUTTON_1_UP        = IXUSIONS_MOUSE_BUTTON_1_UP,
    IXUSIONS_FILTER_MOUSE_BUTTON_2_DOWN      = IXUSIONS_MOUSE_BUTTON_2_DOWN,
    IXUSIONS_FILTER_MOUSE_BUTTON_2_UP        = IXUSIONS_MOUSE_BUTTON_2_UP,
    IXUSIONS_FILTER_MOUSE_BUTTON_3_DOWN      = IXUSIONS_MOUSE_BUTTON_3_DOWN,
    IXUSIONS_FILTER_MOUSE_BUTTON_3_UP        = IXUSIONS_MOUSE_BUTTON_3_UP,

    IXUSIONS_FILTER_MOUSE_BUTTON_4_DOWN      = IXUSIONS_MOUSE_BUTTON_4_DOWN,
    IXUSIONS_FILTER_MOUSE_BUTTON_4_UP        = IXUSIONS_MOUSE_BUTTON_4_UP,
    IXUSIONS_FILTER_MOUSE_BUTTON_5_DOWN      = IXUSIONS_MOUSE_BUTTON_5_DOWN,
    IXUSIONS_FILTER_MOUSE_BUTTON_5_UP        = IXUSIONS_MOUSE_BUTTON_5_UP,

    IXUSIONS_FILTER_MOUSE_WHEEL              = IXUSIONS_MOUSE_WHEEL,
    IXUSIONS_FILTER_MOUSE_HWHEEL             = IXUSIONS_MOUSE_HWHEEL,

    IXUSIONS_FILTER_MOUSE_MOVE               = 0x1000
};

enum IxusionsMouseFlag
{
    IXUSIONS_MOUSE_MOVE_RELATIVE      = 0x000,
    IXUSIONS_MOUSE_MOVE_ABSOLUTE      = 0x001,
    IXUSIONS_MOUSE_VIRTUAL_DESKTOP    = 0x002,
    IXUSIONS_MOUSE_ATTRIBUTES_CHANGED = 0x004,
    IXUSIONS_MOUSE_MOVE_NOCOALESCE    = 0x008,
    IXUSIONS_MOUSE_TERMSRV_SRC_SHADOW = 0x100
};

typedef struct
{
    unsigned short state;
    unsigned short flags;
    short rolling;
    int x;
    int y;
    unsigned int information;
} IxusionsMouseStroke;

typedef struct
{
    unsigned short code;
    unsigned short state;
    unsigned int information;
} IxusionsKeyStroke;

typedef char IxusionsStroke[sizeof(IxusionsMouseStroke)];

IxusionsContext IXUSIONS_API ixusions_create_context(void);

void IXUSIONS_API ixusions_destroy_context(IxusionsContext context);

IxusionsPrecedence IXUSIONS_API ixusions_get_precedence(IxusionsContext context, IxusionsDevice device);

void IXUSIONS_API ixusions_set_precedence(IxusionsContext context, IxusionsDevice device, IxusionsPrecedence precedence);

IxusionsFilter IXUSIONS_API ixusions_get_filter(IxusionsContext context, IxusionsDevice device);

void IXUSIONS_API ixusions_set_filter(IxusionsContext context, IxusionsPredicate predicate, IxusionsFilter filter);

IxusionsDevice IXUSIONS_API ixusions_wait(IxusionsContext context);

IxusionsDevice IXUSIONS_API ixusions_wait_with_timeout(IxusionsContext context, unsigned long milliseconds);

int IXUSIONS_API ixusions_send(IxusionsContext context, IxusionsDevice device, const IxusionsStroke *stroke, unsigned int nstroke);

int IXUSIONS_API ixusions_receive(IxusionsContext context, IxusionsDevice device, IxusionsStroke *stroke, unsigned int nstroke);

unsigned int IXUSIONS_API ixusions_get_hardware_id(IxusionsContext context, IxusionsDevice device, void *hardware_id_buffer, unsigned int buffer_size);

int IXUSIONS_API ixusions_is_invalid(IxusionsDevice device);

int IXUSIONS_API ixusions_is_keyboard(IxusionsDevice device);

int IXUSIONS_API ixusions_is_mouse(IxusionsDevice device);

#ifdef __cplusplus
}
#endif

#endif
