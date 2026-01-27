#!/bin/sh

git clean -dxf

CONFIGURE_PREFIX="$WORKSPACE_ROOT"/dev/install/gfxprim
CONFIGURE_PYTHON_BIN="python3"
CONFIGURE_PYTHON_CONFIG="python3-config"
LOGS_DIR="$WORKSPACE_ROOT"/dev/logs

./configure \
    --prefix="$CONFIGURE_PREFIX" \
    --PYTHON_BIN="$CONFIGURE_PYTHON_BIN" \
    --PYTHON_CONFIG="$CONFIGURE_PYTHON_CONFIG" \
        > "$LOGS_DIR"/configure.log 2>&1
# ./configure --prefix="$PREFIX" > "$LOGS_DIR"/configure.log 2>&1
make 2>&1 | sudo tee "$LOGS_DIR"/make.log
sudo make install 2>&1 | sudo tee "$LOGS_DIR"/make-install.log

# LD_LIBRARY_PATH="$PREFIX"/lib:$LD_LIBRARY_PATH
# export LD_LIBRARY_PATH