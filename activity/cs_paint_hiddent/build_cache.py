#!/usr/bin/python3

import os

from cs_paint_template_variables import CS_PAINT_TEMPLATE_FUNCTIONS
import jinja2

os.cs_paint_cache = True
print("Starting pre-caching of CS Paint Runs...")

jinja2.Template(open(
    os.path.dirname(os.path.abspath(__file__)) + '/index.html',
    'r'
).read()).render(
    **CS_PAINT_TEMPLATE_FUNCTIONS
)

os.cs_paint_cache = False
print("Pre-caching complete.")
