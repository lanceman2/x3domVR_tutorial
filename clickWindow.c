#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>

//#define DEBUG

#ifdef DEBUG
#  define FAIL() exit(1)
#else
#  define FAIL() sleep(1)
#endif

#define ASSERT(x, fmt, ...) \
    do {\
        if(!(bool) (x)) {\
            fprintf(stderr,\
                "%s:%d:%s() Assertion(" #x") failed: " #fmt,\
                    __FILE__, __LINE__, __func__,\
                ##__VA_ARGS__);\
            while(1) FAIL();\
        }\
    } while(0)


#if 0
int getPointerXY(Display *dpy, *x, *y)
{
    XEvent event;
    Window root_window;

    root_window = DefaultRootWindow(dpy);
    memset(&event, 0x00, sizeof(event));
    event.type = ButtonPress;
    event.xbutton.button = 0; // which button???
    event.xbutton.same_screen = True;

    XQueryPointer(dpy, root_window,
            &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root,
            &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y,
            &event.xbutton.state);

    *x = event.xbutton.x;
    *y = event.xbutton.y;

    return 0; // success
}
#endif


int main(int argc, const char **argv)
{

    Display *dpy;
    Window root_window;

    ASSERT(dpy = XOpenDisplay(NULL), "\n");
    root_window = DefaultRootWindow(dpy);

    XSelectInput(dpy, root_window, KeyReleaseMask);
    XWarpPointer(dpy, None, root_window, 0, 0, 0, 0, 400, 400);

    // XSendEvent() is useless given that clients can tell when events
    // come from it.

    // Send a button 1 press and release event to where the pointer is.
    XTestFakeButtonEvent(dpy, /*button*/1, /*bool down*/1, CurrentTime);
    XTestFakeButtonEvent(dpy, /*button*/1, /*bool down*/0, CurrentTime);

    XFlush(dpy);
    XCloseDisplay(dpy);

 
    return 0;
}
