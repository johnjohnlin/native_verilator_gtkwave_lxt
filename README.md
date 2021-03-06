# Proof of Concepts: Supporting LXT2 file format in Verilator.
This repo shows how to change the Verilator VCD internals to support LXT2 natively,
without the `mkfifo` hacking in [this discussion](https://www.veripool.org/boards/2/topics/150?r=199#message-199).

Tested on 3.922 and 3.924, ArchLinux.

## License
The files in `verilator/` use GPLv3 as [Verilator](https://www.veripool.org/wiki/verilator) does;
the files in `lxt2/` use GPLv2 as [GTKWave](http://gtkwave.sourceforge.net/) does.

## Steps

Add flags for including these files.

    verilator --cc --trace --exe t_trace_lxt2.cpp -LDFLAGS "-lz" t_trace_lxt2.v

Copying the files in `verilator/` to the `obj_dir`.

    cp -r verilator/* obj_dir

Edit the `XXX_trace_XXX.cpp` files.

    #include "verilated_lxt2_c.h"

Edit the `XXX_classes.mk` file

    VM_GLOBAL_FAST += \
    	verilated \
    	verilated_lxt2_c \

Compile:

    make -C obj_dir -f Vt_trace_lxt2.mk && ./obj_dir/Vt_trace_lxt2

You can view the signal now.

    gtkwave t_trace_lxt2.lxt2
