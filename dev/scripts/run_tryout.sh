#!/bin/sh

clear

LIBRARY_PATH="$WORKSPACE_ROOT"/dev/install/gfxprim/lib
LD_LIBRARY_PATH="$LIBRARY_PATH":$LD_LIBRARY_PATH
TIMEOUT=1

# py_simple


py_simple_scripts="
    backends.py
    blit.py
    blur.py
    cam_view.py
    convolution.py
    dither.py
    font_style.py
    gfx.py
    gfxprim_qt.py
    invert.py
    loaders_example.py
    progress_callback.py
    resize.py
    rotate90.py
    showimage.py
    x11_windows.py
"

PYTHONPATH=$WORKSPACE_ROOT/pylib:$PYTHONPATH
dir="$WORKSPACE_ROOT"/demos/py_simple

app="backends.py"
cd "$dir" || exit 1
printf "\nRunning %s ...\n" "$app"
./"$app"
cd - || exit 1

