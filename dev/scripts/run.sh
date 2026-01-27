#!/bin/sh

clear

LIBRARY_PATH="$WORKSPACE_ROOT"/dev/install/gfxprim/lib
LD_LIBRARY_PATH="$LIBRARY_PATH":$LD_LIBRARY_PATH
TIMEOUT=1

# bogoman

dir="$WORKSPACE_ROOT"/demos/bogoman
app="bogoman"
cd "$dir" || exit 1
printf "\nRunning %s ...\n" "$app"
timeout $TIMEOUT ./"$app"
cd - || exit 1

# c_simple

# find . -type f -exec file {} + | grep executable | awk '{print $1}'

dir="$WORKSPACE_ROOT"/demos/c_simple

# app="backend_cursor"
# cd "$dir" || exit 1
# printf "\nRunning %s ...\n" "$app"
# timeout $TIMEOUT ./"$app"
# cd - || exit 1

# app="SDL2_glue"
# cd "$dir" || exit 1
# printf "\nRunning %s ...\n" "$app"
# timeout $TIMEOUT ./"$app"
# cd - || exit 1

c_simple_apps="
    backend_cursor
    backend_example
    backend_tasks_example
    backend_timers_example
    bbox
    blittest
    convolution
    data_storage
    debug_handler
    dpi_check
    draw_glyph
    elf_note
    fileview
    filters_symmetry
    fonttest
    gaussian_noise
    gfx_koch
    input_example
    json_writer
    json_writer_file
    koch
    linetest
    loaders
    loaders_example
    loaders_register
    matrix
    memory_io
    meta_data
    pretty_print
    proxy_backend
    randomshapetest
    SDL2_glue
    shapetest
    showimage
    textaligntest
    timers
    unicodetest
    update_rect_test
    v4l2_grab
    v4l2_show
    vector
    version
    virtual_backend_example
    weighted_median
    x11_windows
    zip_container
"

for app in $c_simple_apps
do
cd "$dir" || exit 1
printf "\nRunning %s ...\n" "$app"
case $app in
    convolution)
        timeout $TIMEOUT ./"$app" ball.ppm
        ;;
    gaussian_noise)
        timeout $TIMEOUT ./"$app" -s 0.5 -m 0.5 ball.ppm gaussian_noise.out.png
        ;;
    fileview)
        timeout $TIMEOUT ./"$app" "$WORKSPACE_ROOT"/dev/resources/test.txt
        ;;
    filters_symmetry)
        timeout $TIMEOUT ./"$app" -s 90 ball.ppm filters_symmetry.out.png
        ;;
    loaders)
        timeout $TIMEOUT ./"$app" ball.ppm loaders.out.png
        ;;
    loaders_register)
        timeout $TIMEOUT ./"$app" ball.ppm
        ;;
    weighted_median)
        timeout $TIMEOUT ./"$app" ball.ppm
        ;;
    zip_container)
        timeout $TIMEOUT ./"$app" "$WORKSPACE_ROOT"/dev/resources/ball.zip
        ;;
    *)
        timeout $TIMEOUT "./$app"
        ;;
esac
cd - || exit 1
done

# grinder

dir="$WORKSPACE_ROOT"/demos/grinder
app="grinder"
cd "$dir" || exit 1
printf "\nRunning %s ...\n" "$app"
timeout $TIMEOUT ./"$app" "$WORKSPACE_ROOT"/dev/resources/images/ball.ppm
cd - || exit 1

# particle

dir="$WORKSPACE_ROOT"/demos/particle
app="particle_demo"
cd "$dir" || exit 1
printf "\nRunning %s ...\n" "$app"
timeout $TIMEOUT ./"$app"
cd - || exit 1

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

PYTHONPATH=$WORKSPACE_ROOT/pylib/:$PYTHONPATH
# ./runpytest.sh blit.py $WORKSPACE_ROOT/dev/resources/images/ball.ppm
dir="$WORKSPACE_ROOT"/demos/py_simple

for script in $py_simple_scripts
do
cd "$dir" || exit 1
printf "\nRunning %s ...\n" "$script"
case $script in
    blit.py)
        timeout 0.02 ./runpytest.sh "$script" "$WORKSPACE_ROOT"/dev/resources/images/ball.ppm
        ;;
    blur.py)
        timeout $TIMEOUT ./runpytest.sh "$script" 0.5 "$WORKSPACE_ROOT"/dev/resources/images/ball.ppm
        ;;
    convolution.py)
        timeout $TIMEOUT ./runpytest.sh "$script" "$WORKSPACE_ROOT"/dev/resources/images/ball.ppm
        ;;
    dither.py)
        timeout $TIMEOUT ./runpytest.sh "$script" "$WORKSPACE_ROOT"/dev/resources/images/ball.ppm
        ;;
    invert.py)
        timeout $TIMEOUT ./runpytest.sh "$script" "$WORKSPACE_ROOT"/dev/resources/images/ball.ppm
        ;;
    *)
        timeout $TIMEOUT ./runpytest.sh "$script"
        ;;
esac
cd - || exit 1
done


# spiv

dir="$WORKSPACE_ROOT"/demos/spiv
app="spiv"
cd "$dir" || exit 1
printf "\nRunning %s ...\n" "$app"
timeout $TIMEOUT ./"$app" "$WORKSPACE_ROOT"/dev/resources/images/ball.ppm
cd - || exit 1

# ttf2img

dir="$WORKSPACE_ROOT"/demos/ttf2img
app="ttf2img"
cd "$dir" || exit 1
printf "\nRunning %s ...\n" "$app"
timeout $TIMEOUT ./"$app" -f "$WORKSPACE_ROOT"/dev/resources/fonts/Roboto/Roboto.ttf -i Roboto.out.png 
cd - || exit 1

# widgets

dir="$WORKSPACE_ROOT"/demos/widgets

widgets_apps="
    choice
    choice_arr
    choice_json_arr
    clock
    datetime
    disable
    disk_free
    example
    file_dialogs
    focus
    graph
    grid_move_widget
    layout_switch_example
    log
    login_example
    markup_example
    message_dialog
    nested_dialogs
    overlay_example
    pixmap_example
    scroll_area_example
    show_layout
    showimage
    table_example
    tabs
    tabs_example
    todo
"

# Running show_layout ...
# usage: show_layout test_layouts/foo.json [output_image]

for app in $widgets_apps
do
cd "$dir" || exit 1
printf "\nRunning %s ...\n" "$app"
case $app in
    show_layout)
        timeout $TIMEOUT ./"$app" test_layouts/button.json "$app".out.png
        ;;
    *)
        timeout $TIMEOUT "./$app"
        ;;
esac
cd - || exit 1
done