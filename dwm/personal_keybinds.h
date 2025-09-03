	{ ShiftMask,			XK_Print, 		spawn,          SHCMD("scrot --select - | xclip -sel clip -t image/png") },
		{ 0,		                XF86XK_AudioPlay,				spawn,        	{.v = (const char*[]){"playerctl","play-pause",NULL} } },
	{ 0,		                XF86XK_AudioPrev,				spawn,        	{.v = (const char*[]){"playerctl","previous",NULL} } },
	{ 0,		                XF86XK_AudioNext,				spawn,        	{.v = (const char*[]){"playerctl","next",NULL} } },

