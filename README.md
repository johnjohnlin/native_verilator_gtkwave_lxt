# Proof of Concepts: Supporting LXT2 file format in Verilator.
This repo shows how to change the Verilator VCD internals to support LXT2 natively,
without the `mkfifo` hacking in [this discussion](https://www.veripool.org/boards/2/topics/150?r=199#message-199).

Tested on 3.922 and 3.924, ArchLinux.

## License
The files in `verilator/` use GPLv3 as [Verilator](https://www.veripool.org/wiki/verilator) does;
the files in `lxt2/` use GPLv2 as [GTKWave](http://gtkwave.sourceforge.net/) does.

## Steps

Compile the object file for LXT writer.

    cd lxt2
    ./compile.sh
    cd ..

Add flags for including these files.

    verilator --cc --trace --exe testbench.cpp `pwd`/lxt2_write.o -CFLAGS "-I `pwd`/lxt2/" -LDFLAGS "-lz" GaloisLfsr.sv

Copying the files in `verilator/` to the `obj_dir`, and then run Verilator.

    cp verilator/* obj_dir
    make -C obj_dir -f VGaloisLfsr.mk && ./obj_dir/VGaloisLfsr

You can view the signal now.

    gtkwace GaloisLfsr.lxt2

By copying the verilator vcd files, the default makefile will use the modified VCD dumper.
Do not overwrite the original files in standard Verilator,
since it is just a proof of concept and not fully compatible.
