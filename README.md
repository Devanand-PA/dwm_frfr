# dwm_frfr
A rewrite of my dwm config because the wm_setup is all over the palce and I don't want to maintain it anymore.

# Patches :
## dwm:
- focusonnetactive (for alt-tabbing)
- dwm-restartsig (For restarting the WM during config changes)

### Custom patches
- dwm remembers window positions and tags on restart
- dwm reads colors from $HOME/.cache/wal/colors when starting
- dwm's theme can be update by sending SIGUSR1 to it. By default, it reads the theme from $HOME/.cache/wal/colors (It also reads it when starting)

## dmenu
- dmenu-center
- alpha
- case-insensitive
- multi-selection

### Custom patches
- dmenu reads colors from $HOME/.cache/wal/colors when starting the program each time
