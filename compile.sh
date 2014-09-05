#!/bin/sh
GladeGlue.rb tltlp
gcc tltlp.c tltlp_glade.c -o tltlp `pkg-config --cflags --libs gtk+-3.0 appindicator3-0.1` -rdynamic -Wall -Wextra -std=c89 -pedantic -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition
rm *_glade.? *~

