#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>


//#define DEBUG

#define ASSERT(x, fmt, ...) \
    do {\
        if(!(bool) (x)) {\
            fprintf(stderr,\
                "%s:%d:%s() Assertion(" #x") failed: " #fmt,\
                    __FILE__, __LINE__, __func__,\
                ##__VA_ARGS__);\
            while(1) sleep(1);\
        }\
    } while(0)


int main(int argc, const char **argv)
{

    Display *dpy;
    Window root_window;
    XEvent event;

    dpy = XOpenDisplay(NULL);
    ASSERT(dpy, "\n");
    root_window = DefaultRootWindow(dpy);

    memset(&event, 0x00, sizeof(event));
	
    event.type = ButtonPress;
    event.xbutton.button = 0; // which button???
    event.xbutton.same_screen = True;

    printf("\n\n");

    while(1)
    {
        // Polling like this is not good coding practice
        XQueryPointer(dpy, root_window,
            &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root,
            &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y,
            &event.xbutton.state);

        printf("   x y = %d %d   \r", event.xbutton.x, event.xbutton.y);
        fflush(stdout);
        usleep(100000);
    }



    return 0;
}
