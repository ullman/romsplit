/*
 * Rom splitting program to deinterlace binary rom files
 * Henrik Ullman 2016
 * Licence: Public domain
 */
#include <stdio.h>
#include <stdlib.h>

void check_open(FILE* fh);

void check_exists(char* fh);

void split_files(char* infile,char* hirom_name, char* lorom_name);

void check_open(FILE* fh){
    if(fh == NULL){
        printf("Error: Unable to open romfile\n");
        exit(1);
    }
}

void check_exists(char* fn){
    FILE * test_file;
    if (test_file = fopen(fn, "r")){
        fclose(test_file);
        printf("Error: file %s exists\n", fn);
        exit(1);
    }
}

void split_files(char* infile,char* hirom_name, char* lorom_name){
    FILE* read_rom;
    FILE* hirom;
    FILE* lorom;
    unsigned char buff[1];
    int split;

    read_rom = fopen(infile, "rb");
    check_open(read_rom);

    check_exists(hirom_name);
    check_exists(lorom_name);

    hirom = fopen(hirom_name, "wb");
    lorom = fopen(lorom_name, "wb");

    split = 0;
    while(fread(buff,sizeof(buff),1,read_rom)!=0){

        if(split ==0)
        {
            fwrite(buff,sizeof(buff),1,hirom);
            split = 1;
        }
        else
        {
            fwrite(buff,sizeof(buff),1,lorom);
            split = 0;
        }
    }
    fclose(hirom);
    fclose(lorom);
    fclose(read_rom);
    printf("File %s is split into:\n",infile);
    printf("hirom: %s\n",hirom_name);
    printf("lorom: %s\n",lorom_name);

}

int main(int argc, char**argv){

    if(argc!=4)
    {
        printf("usage: romsplit inputfile output_high output_low\n");
    }
    else
    {
        printf("Splitting rom...\n");
        split_files(argv[1],argv[2],argv[3]);
    }

    return 0;
}

