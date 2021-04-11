#include <X11/XF86keysym.h>
/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int barheight = 8;

static const unsigned int gappx     = 6;        /* gaps between windows */
 
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

static const int vertpad            = 0;       /* vertical padding of bar */
static const int sidepad            = 0;       /* horizontal padding of bar */

static const char *fonts[]          = { "MesloLGS:pixelsize=14:antialias=true:autohint=true", "fontawesome:pixelsize=20:antialias=true:autohint=true" };
static const char dmenufont[]       = {"monospace:size=15"};


//static const char col_gray1[]       = "#222222";
//static const char col_gray2[]       = "#444444";
//static const char col_gray3[]       = "#bbbbbb";
//static const char col_gray4[]       = "#eeeeee";
//static const char col_cyan[]        = "#005577";

static const char col_gray1[]       = "#282828"; //background grey color in staus bar
static const char col_gray2[]       = "#444444"; //border color when not selected
static const char col_gray3[]       = "#ebdbb2"; //text color... I think
static const char col_gray4[]       = "#ebdbb2"; //text color when selected in bar
//static const char col_cyan[]        = "#98971a"; //main color in dwm bar
static const char col_cyan[]        = "#cc241d"; //main color in dwm bar

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_t,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_n,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_s,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },



	{ MODKEY,                       XK_q,      spawn,           SHCMD("qutebrowser") },
	{ MODKEY,                       XK_w,      spawn,           SHCMD("st ranger") },
	{ MODKEY,                       XK_a,      spawn,           SHCMD("sh /home/wifiengine/.scripts/dictionary/test.sh") },
    { MODKEY,                       XK_e,      spawn,           SHCMD("sh /home/wifiengine/.scripts/emojis/search.sh") },
	{ MODKEY,                       XK_u,      spawn,           SHCMD("sh /home/wifiengine/.scripts/phonetic/search.sh") },
//	{ MODKEY|ShiftMask,             XK_s,      spawn,           SHCMD("python ~/.scripts/movewindow/right.py") },
//	{ MODKEY|ShiftMask,             XK_h,      spawn,           SHCMD("python ~/.scripts/movewindow/left.py") },
//
//
//
	{0, XF86XK_AudioRaiseVolume,	        spawn,	SHCMD("amixer set 'Master' 10%+") },
	{0, XF86XK_AudioLowerVolume,	        spawn,	SHCMD("amixer set 'Master' 10%-") },
	{0, XF86XK_AudioMute,          	        spawn,	SHCMD("amixer set 'Master' 0%") },
//	{0, XF86XK_MonBrightnessUp,          	spawn,	SHCMD("xbacklight -inc 5") },
//	{0, XF86XK_MonBrightnessDown,          	spawn,	SHCMD("xbacklight -dec 5") },
	{0, XF86XK_MonBrightnessUp,          	spawn,	SHCMD("light -A 3 & sh /home/wifiengine/.scripts/brightness.sh") },
	{0, XF86XK_MonBrightnessDown,          	spawn,	SHCMD("light -U 3 & sh /home/wifiengine/.scripts/brightness.sh") },


	{ MODKEY,                       XK_grave,      spawn,       SHCMD("sh ~/.scripts/shutdown/shutdown.sh") },



};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

