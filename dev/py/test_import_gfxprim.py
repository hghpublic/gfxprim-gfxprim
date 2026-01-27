#!/usr/bin/env python3
# PYTHONPATH=$WORKSPACE_ROOT/pylib ./dev/py/test_import_gfxprim.py
import sys

print("Importing gfxprim modules...")
print(f"sys.path: {sys.path}")

import gfxprim.backends as backends
import gfxprim.core as core
import gfxprim.filters as filters
import gfxprim.gfx as gfx
import gfxprim.grabbers as grabbers
import gfxprim.input as input
import gfxprim.loaders as loaders
import gfxprim.text as text
import gfxprim as gfxprim

print("All gfxprim modules imported successfully.")
