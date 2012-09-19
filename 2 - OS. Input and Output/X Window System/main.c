#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <X11/extensions/scrnsaver.h>

#include <X11/Xproto.h>
#include <X11/extensions/dpms.h>


Display *find_x_display()
{
	int i;
	Display *dpy;
	char dname[] = ":0";
	for (i = 0; i < 10; ++i) {
		dname[1] = i + '0';
		dpy = XOpenDisplay(dname);
		if (dpy)
			return dpy;
	}
	return NULL;
}

#define print_debug printf

int main()
{
	CARD16 current_mode;
	CARD16 needed_mode;
	BOOL current_enabled;
	
	//mode is DPMSModeOn, DPMSModeStandby, DPMSModeSuspend, or DPMSModeOff
	needed_mode = DPMSModeOff;

	Display *dpy = find_x_display();
	if (dpy == NULL) {
		print_debug("couldn't open display\n");
		goto end;
	}
	
	if (!DPMSCapable(dpy)) {
		print_debug("display is not DPMS-capable");
		goto end;
	}
	if (!DPMSInfo(dpy, &current_mode, &current_enabled)) {
		print_debug("couldn't get DPMS info");
		goto end;
	}

	if (!current_enabled) {
		print_debug("DPMS not enabled");
		goto end;
	}

	if (current_mode != needed_mode) {
		sleep(1);
		if (!DPMSForceLevel(dpy, needed_mode))
			print_debug("Could not change DPMS mode");
		else 
			XSync(dpy, 0);
	}
end:
	XCloseDisplay(dpy);
	return 0;
}
