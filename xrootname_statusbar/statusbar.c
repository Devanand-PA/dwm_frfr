#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int main() {
    Display *display;
    Window root;
    
    // Open display ONCE
    display = XOpenDisplay(NULL);
    if (!display) {
        fprintf(stderr, "Error: Could not open X display\n");
        return 1;
    }
    
    root = DefaultRootWindow(display);
    
    // Get atoms ONCE
    Atom net_wm_name = XInternAtom(display, "_NET_WM_NAME", False);
    Atom utf8_string = XInternAtom(display, "UTF8_STRING", False);
    Atom wm_name = XInternAtom(display, "WM_NAME", False);
    Atom string_type = XInternAtom(display, "STRING", False);
    
    while (1) {
        // Generate dynamic content
        time_t now = time(NULL);
        struct tm *tm_info = localtime(&now);
        char name[256];
        strftime(name, sizeof(name), " %a %Y-%m-%d %H:%M", tm_info);
        
        // Update root name
        XChangeProperty(display, root, net_wm_name, utf8_string,
                       8, PropModeReplace, (unsigned char *)name, strlen(name));
        
        XChangeProperty(display, root, wm_name, string_type,
                       8, PropModeReplace, (unsigned char *)name, strlen(name));
        
        XFlush(display);
        
        sleep(30); // Update every second
    }
    
    // This will never be reached in this example, but normally you'd close:
    // XCloseDisplay(display);
    return 0;
}

