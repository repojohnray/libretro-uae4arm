#! /bin/bash

aclocal -I m4 -I /usr/share/aclocal -I /usr/X11R6/share/aclocal -I /usr/local/share/aclocal --force;autoheader -f;libtoolize --copy --force;automake --add-missing --copy --foreign;autoconf --force;
