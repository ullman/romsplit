/*
 * Rom splitting program to deinterlace and merge binary rom files
 * Henrik Ullman 2016
 * Licence: Public domain
 */
#include <stdio.h>
#include <stdlib.h>

void check_open(FILE* fh, char* fn);

void check_exists(char* fh);

void split_files(char* infile,char* hirom_name, char* lorom_name);

void merge_file(char* outfile,char* hirom_name, char* lorom_name);

void print_man();

void check_open(FILE* fh,char* fn){
    if(fh == NULL){
        printf("Error: Unable to open %s\n",fn);
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
    check_open(read_rom,infile);

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

void merge_file(char* outfile,char* hirom_name, char* lorom_name)
{   
    FILE* out_rom;
    FILE* hirom;
    FILE* lorom;


    unsigned char buff[1];

    hirom = fopen(hirom_name,"rb");
    lorom = fopen(lorom_name,"rb");
    check_open(hirom,hirom_name);
    check_open(lorom,lorom_name);

    check_exists(outfile);
    out_rom = fopen(outfile,"wb");

    while(fread(buff,sizeof(buff),1,hirom)!=0)
    {
        fwrite(buff,sizeof(buff),1,out_rom);
        if(fread(buff,sizeof(buff),1,lorom)!=0)
        {
        fwrite(buff,sizeof(buff),1,out_rom);
        }
    }
 
    fclose(hirom);
    fclose(lorom);
    fclose(out_rom);
    printf("Files are merged into: %s\n",outfile);
    printf("hirom: %s\n",hirom_name);
    printf("lorom: %s\n",lorom_name);


}

void print_man(){
        printf("usage:romsplit [option] romfile highrom lowrom\n");
        printf("Options:\n");
        printf("-s : split romfile into hirom and lorom\n");
        printf("-m : merge hirom and lorom into romfile\n");
}

int main(int argc, char**argv){

    if(argc!=5)
    {
        print_man();
    }
    else
    {
        if(!strcmp(argv[1],"-s"))
        {
        printf("Splitting rom...\n");
        split_files(argv[2],argv[3],argv[4]);
        }
        else if(!strcmp(argv[1],"-m"))
        {
        printf("Merging rom...\n");
        merge_file(argv[2],argv[3],argv[4]);

        }
        else
        {
            print_man();
        }
    }

    return 0;
}

