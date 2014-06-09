PlusStatistics
==============

Some basic statistical methods

After clone do:

    $ git submodule update --init --recursive

To build and install, just do:

    $ make
    $ sudo make install

One can plot a histogram with gnuplot usign:

    gnuplot> plot "< pstatistics --hist [file name]" u 1:2:3 with boxes

Or calculate the mean of a file:

    $ pstatistics --mean [file name]

For more options try:

    $ pstatistics -h

Headers files are at:

    pstatistics/*

and one should add -lpstatistics to use this as a lib
