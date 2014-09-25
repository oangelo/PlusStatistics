PlusStatistics
==============

Some basic statistical methods

To build and install, just do:

    $ make
    $ sudo make install

One can plot a histogram with gnuplot usign:

    gnuplot> plot "< pstatistics --hist -f [file name]" u 1:2:3 with boxes

Or calculate the mean of a file:

    $ pstatistics --mean -f [file name]
    or
    $ pstatistics --mean --stdin < cat [file name]

For more options try:

    $ pstatistics -h

Headers files are at:

    pstatistics/*

and one should add -lpstatistics to use this as a lib
