                FS-UAE LIBRETRO TEST/DEBUG VERSION (WIP)



Based on FS-UAE 2.7.14dev (https://fs-uae.net/)

First 'Testable' release:
* The configuration file is read but not processed.
* The input layer is the same as libretro-uae (README-libretro-puae):
  * Gamepad compatible.
  * AltL+F11: GUI screen (need to be fixed).
  * F11:      Grab mouse (default retroarch key)
  * RET: virtual keyboard.
* Audio OK now.

Misc Issues:
* Slower than libretro-uae.
* x86_64: the JIT requires a 32 bits address range for some ELF loaded symbols. My attempt with LD_PREFER_MAP_32BIT_EXEC failed, maybe a prelink may work.


------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*Test - On the local directory where 'fsuae_libretro.so' is located:
ln -snf fdd_path.adf df0.adf
ln -snf kick_path.rom kick.rom
retroarch -L ./fsuae_libretro.so /dev/null

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#Linux x86-64:
./autogen.sh
CFLAGS="-O2" ./configure --build=x86_64-pc-linux-gnu --prefix=/usr/local --enable-shared --disable-static --libdir=/usr/local/lib64 --enable-jit
make gen -j 4
make clean
make -j 4

#Linux ARM: (-mthumb or -marm mode)
./autogen.sh
CFLAGS="-O2" ./configure --build=arm-pc-linux-gnueabihf --prefix=/usr/local --enable-shared --disable-static --libdir=/usr/local/lib --disable-jit --enable-neon
make gen -j 4
make clean
make -j 4



