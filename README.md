#romsplit - splitting interlaced rom files

This is a minimal program to split binary rom files for two EPROM chips.
Splitting is done by deinterlacing, alternate writing of bytes to two binary
images.

By Henrik Ullman 2016

##compile using:
make

##usage:
romsplit [option] romfile highrom lowrom
Options:
-s : split romfile into hirom and lorom
-m : merge hirom and lorom into romfile



##Licence:
Public domain
