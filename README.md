#romsplit - splitting interlaced rom files

This is a minimal program to split binary rom files for two EPROM chips.
Splitting is done by deinterlacing, alternate writing of bytes to two binary
images.

By Henrik Ullman 2016

##compile using:
make

##usage:
./romsplit romfile hirom lorom


##Licence:
Public domain
