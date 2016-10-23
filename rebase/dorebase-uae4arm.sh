#! /bin/bash

sed -r -i "s/(init_hz)([ \t]*[(][^,]*[)])/\11\2/" ./sources/src/custom.c
sed -r -i "s/(init_hz)1([ \t]*[(]([ \t]*|[ \t]*void[ \t]*)[)])/\1\2/" ./sources/src/custom.c; #fix (void)


sed -r -i "s/(m68k_[ad]reg[ \t]*[(][ \t]*)(regs[ \t]*,)/\1\&\2/g" sources/src/filesys.c sources/src/hardfile.c sources/src/inputdevice.c sources/src/native2amiga.c sources/src/traps.c \
    sources/src/uaelib.c ; #fix &

sed -r -i "s/(getromdatabycrc)([ \t]*[(][^,]*[)])/\11\2/" sources/src/cfgfile.c
sed -r -i "s/(exception3)([ \t]*[(][^,]*[,][^,]*[,][^,]*[,][^,]*[,][^,]*[)])/\1z\2/" sources/src/cpuemu_11.c
