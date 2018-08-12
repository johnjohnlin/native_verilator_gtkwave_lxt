# Proof of Concepts: Supporting LXT2 file format in Verilator.
This repo shows how to change the Verilator VCD internals to support LXT2 natively,
without the `mkfifo` hacking in [this discussion](https://www.veripool.org/boards/2/topics/150?r=199#message-199).

## License
The files in `verilator/` use GPLv3 as [Verilator](https://www.veripool.org/wiki/verilator) does;
the files in `lxt2/` use GPLv2 as [GTKWave](http://gtkwave.sourceforge.net/) does.

## Steps

Compile the object file for LXT writer.

    cd lxt2
    ./compile.sh

Add flags for including these files.

    verilator --exe xxx.cpp lxt2_write.o -CFLAGS "-I xxx/lxt2/" -LDFLAGS "-lz ..."

Copying the files in `verilator/` to the `obj_dir`

    cp verilator/* obj_dir

By doing so, the default makefile will use the modified VCD dumper.
Do not overwrite the original files in standard Verilator,
since it is just a proof of concept and not fully compatible.
