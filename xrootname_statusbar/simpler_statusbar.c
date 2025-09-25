#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <X11/Xlib.h>

FILE *bat_percent;
FILE *bat_status;


void set_xroot_name(const char *name) {
    Display *dpy = XOpenDisplay(NULL);
    if (dpy) {
        XStoreName(dpy, DefaultRootWindow(dpy), name);
        XCloseDisplay(dpy);
    }
}

char temporary_bat_buffer[50];
time_t rawtime;              // Declare once
struct tm timeinfo;          // Actual struct, not pointer
char time_buffer[80];
char full_buffer[256];
char bat_buffer[100];
void  update_time() {
        time(&rawtime);
        localtime_r(&rawtime, &timeinfo);  // Thread-safe: writes to YOUR struct
        
        strftime(time_buffer, sizeof(time_buffer), "%H:%M:%S", &timeinfo);
        strncat( full_buffer ,  time_buffer  ,   sizeof(full_buffer) - strnlen(full_buffer,sizeof(full_buffer)) -1 );
        
}

void update_battery(){
if ( (bat_percent != NULL) && (bat_status != NULL)) {
        // Empty buffers
    strcpy(bat_buffer, "");
    strcpy(temporary_bat_buffer, "");
        // get buffers
    strncat( bat_buffer , "[" ,sizeof(bat_buffer)-strnlen(bat_buffer,sizeof(bat_buffer)-1) );
    fgets(temporary_bat_buffer,sizeof(temporary_bat_buffer),bat_percent);
    temporary_bat_buffer[strcspn(temporary_bat_buffer, "\n")] = 0;
    strncat( bat_buffer , temporary_bat_buffer ,sizeof(bat_buffer)-strnlen(bat_buffer,sizeof(bat_buffer)-1) );
    strncat( bat_buffer , "]" ,sizeof(bat_buffer)-strnlen(bat_buffer,sizeof(bat_buffer)-1) );
    strncat( bat_buffer , " " ,sizeof(bat_buffer)-strnlen(bat_buffer,sizeof(bat_buffer)-1) );


    fgets(temporary_bat_buffer,sizeof(temporary_bat_buffer),bat_status);
    temporary_bat_buffer[strcspn(temporary_bat_buffer, "\n")] = 0;
        strncat( bat_buffer , temporary_bat_buffer ,sizeof(bat_buffer)-strnlen(bat_buffer,sizeof(bat_buffer)-1) );
    strncat( full_buffer ,  bat_buffer  ,   sizeof(full_buffer) - strnlen(full_buffer,sizeof(full_buffer)) -1 );
    }
    fclose(bat_status);
    fclose(bat_percent);
}


int main(){
    while(1) {
    bat_percent = fopen("/sys/class/power_supply/BAT0/capacity", "r");
    bat_status = fopen("/sys/class/power_supply/BAT0/status","r");
    strcpy(full_buffer, "");
    update_time();
    strncat( full_buffer , " " ,sizeof(bat_buffer)-strnlen(bat_buffer,sizeof(bat_buffer)-1) );
    update_battery();
    set_xroot_name(full_buffer);
    sleep(1);
    }



    return 0;
}
