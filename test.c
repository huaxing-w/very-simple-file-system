#include <stdio.h>
#include <stdlib.h>
#include "fs.h"

int main()
{
    create_fs();
    sync_fs();

    // mount_fs();
    int fileNum=allocate_file("hello");

    // test set file size
    // set_file_size(0, 1000);
    // print_fs();

    
    set_file_size(0, 5000);
    char s[] = "hellhellofjkdla;fjkld;ajfkl;dajfkl;dsjkal;fjkdls;jgjkdfhbsvjkhellofjkdla;fjkld;ajfkl;dajfkl;dsjkal;fjkdls;jgjkdfhbsvjkhellofjkdla;fjkld;ajfkl;dajfkl;dsjkal;fjkdls;jgjkdfhbsvjkhellofjkdla;fjkld;ajfkl;dajfkl;dsjkal;fjkdls;jgjkdfhbsvjkhellofjkdla;fjkld;ajfkl;dajfkl;dsjkal;fjkdls;jgjkdfhbsvjkhellofjkdla;fjkld;ajfkl;dajfkl;dsjkal;fjkdls;jgjkdfhbsvjkhellofjkdla;fjkld;ajfkl;dajfkl;dsjkal;fjkdls;jgjkdfhbsvjkhellofjkdla;fjkld;ajfkl;dajfkl;dsjkal;fjkdls;jgjkdfhbsvjkhellofjkdla;fjkld;ajfkl;dajfkl;dsjkal;fjkdls;jgjkdfhbsvjkhellofjkdla;fjkld;ajfkl;dajfkl;dsjkal;fjkdls;jgjkdfhbsvjkhellofjkdla;fjkld;ajfkl;dajfkl;dsjkal;fjkdls;jgjkdfhbsvjkhellofjkdla;fjkld;ajfkl;dajfkl;dsjkal;fjkdls;jgjkdfhbsvjkhellofjkdla;fjkld;ajfkl;dajfkl;dsjkal;fjkdls;jgjkdfhbsvjkhellofjkdla;fjkld;ajfkl;dajfkl;dsjkal;fjkdls;jgjkdfhbsvjkhellofjkdla;fjkld;ajfkl;dajfkl;dsjkal;fjkdls;jgjkdfhbsvjkhellofjkdla;fjkld;ajfkl;dajfkl;dsjkal;fjkdls;jgjkdfhbsvjkhellofjkdla;fjkld;ajfkl;dajfkl;dsjkal;fjkdls;jgjkdfhbsvjkofjkdla;fjkld;ajfkl;dajfkl;dsjkal;fjkdls;jgjkdfhbsvjkdfshguierwughdfjklshgjvkfsh";
    write_data_to_file(fileNum,0,&s[0]);
    sync_fs();

    print_fs();
    read_file("hello");
    

    
    printf("done\n");

    return 0;
}