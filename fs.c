#include "fs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
struct superblock
{
    int num_inodes;
    int num_blocks;
    int size_blocks;
};

struct inode
{
    int size;
    char name[8];
    int blocks[10];
};

struct disk_block
{
    int next_block_num;
    char data[512];
};
*/

struct superblock sb;

struct inode *inodes;

struct disk_block *dbs;

// create a new file system
void create_fs(char *filename, int size)
{
    sb.num_inodes = 10;
    sb.num_blocks = 100;
    sb.size_blocks = sizeof(struct disk_block);

    inodes = malloc(sizeof(struct inode) * sb.num_inodes);

    int i;

    for (i = 0; i < sb.num_inodes; i++)
    {
        inodes[i].size = -1;
        inodes[i].first_block_num = -1; // -1 means empty
        strcpy(inodes[i].name, "emptyfi");
        // inodes[i].name = "";
    }

    dbs = malloc(sizeof(struct disk_block) * sb.num_blocks);

    for (i = 0; i < sb.num_blocks; i++)
    {
        dbs[i].next_block_num = -1;
    }
};

// mount an existing file system
void mount_fs()
{
    FILE *file;
    file = fopen("fs_data", "r");

    // read superblock
    fread(&sb, sizeof(struct superblock), 1, file);


    inodes = malloc(sizeof(struct inode) * sb.num_inodes);
    dbs = malloc(sizeof(struct disk_block) * sb.num_blocks);

    fread(inodes, sizeof(struct inode), sb.num_inodes, file);
    fread(dbs, sizeof(struct disk_block), sb.num_blocks, file);

    fclose(file);

    // read disk blocks
    // for (i = 0; i < sb.num_blocks; i++)
    // {
    //     fread(&dbs[i], sizeof(struct disk_block), 1, file);
    // }

}; // how do i know it's working - add print_fs()

void print_fs()
{
    printf("superblock info: num of inodes: %d num of blocls: %d block size: %d\n", sb.num_inodes, sb.num_blocks, sb.size_blocks);

    printf("inode info: \n");
    int i;
    for (i = 0; i < sb.num_inodes; i++)
    {
        printf("inode %d: size: %d, first_block_num: %d, name: %s\n", i, inodes[i].size, inodes[i].first_block_num, inodes[i].name);
    }

    printf("disk block info: \n");
    for (i = 0; i < sb.num_blocks; i++)
    {
        printf("disk block %d: next block num: %d\n", i, dbs[i].next_block_num);
    }
}

// write all dirty blocks to disk
void sync_fs()
{
    FILE *file;
    file = fopen("fs_data", "w+");

    // write the superblock
    fwrite(&sb, sizeof(struct superblock), 1, file);

    fwrite(inodes, sizeof(struct inode), sb.num_inodes, file);
    fwrite(dbs, sizeof(struct disk_block), sb.num_blocks, file);

    // inodes
    // int i;
    // for (i = 0; i < sb.num_inodes; i++)
    // {
    //     fwrite(&inodes[i], sizeof(struct inode), 1, file);
    // }

    // disk blocks
    // for (i = 0; i < sb.num_blocks; i++)
    // {
    //     fwrite(&dbs[i], sizeof(struct disk_block), 1, file);
    // }

    fclose(file);
};

// helper functions
int find_empty_inode()
{
    int i;
    for (i = 0; i < sb.num_inodes; i++)
    {
        if (inodes[i].size == -1)
        {
            return i;
        }
    }
    return -1;
}

int find_empty_disk_block()
{
    int i;
    for (i = 0; i < sb.num_blocks; i++)
    {
        if (dbs[i].next_block_num == -1)
        {
            return i;
        }
    }
    return -1;
}

int allocate_file(char filename[12])
{
    // find an empty inode
    int inode_num = find_empty_inode();

    int block_num = find_empty_disk_block();

    // claim it
    inodes[inode_num].first_block_num = block_num;
    dbs[block_num].next_block_num = -2; // -2 means end of file

    // set the name
    strcpy(inodes[inode_num].name, filename);
    // find and claim a disk block
    // return file descriptor
    return inode_num;
};

// helper functions
void shorten_file(int block_num)
{
    int next_block_num = dbs[block_num].next_block_num;
    if (next_block_num >= 0)
    {
        shorten_file(next_block_num);
    }
    dbs[block_num].next_block_num = -1;
};

// add or delete blocks as needed
void set_file_size(int file_num, int size)
{
    // how many blocks do we need?
    int tmp = size + BLOCK_SIZE - 1;
    int num = tmp / BLOCK_SIZE;
    // if (size % BLOCK_SIZE != 0)
    // {
    //     num++;
    // }

    int begin_block_num = inodes[file_num].first_block_num;
    num--;

    // grow the file if needed
    while (num > 0)
    {
        int next_block_num = dbs[begin_block_num].next_block_num;

        if (next_block_num == -2)
        {
            // need to allocate a new block
            int new_block_num = find_empty_disk_block();
            dbs[begin_block_num].next_block_num = new_block_num;
            dbs[new_block_num].next_block_num = -2;
        }

        begin_block_num = dbs[begin_block_num].next_block_num;
        num--;
    }

    // check for shrinking
    shorten_file(begin_block_num);
    dbs[begin_block_num].next_block_num = -2;
};
void write_data_to_file(int file_num, int pos, char *data){
    int begin_block_num = inodes[file_num].first_block_num;
    int len=findStringLength(&data[0]);
    int i=0;
    while(len>0){
        dbs[begin_block_num].data[pos]=data[i];
        i+=1;
        pos+=1;
        if(pos==BLOCK_SIZE){
            begin_block_num = dbs[begin_block_num].next_block_num;
            pos=0;
        }
        len-=1;
    }
}; // write data to a file

void print_char(int file_num){
    int begin_block_num = inodes[file_num].first_block_num;
    int i;
    int flag=0;
    while(dbs[begin_block_num].next_block_num!=-2){
        printf("the char in block %d is: \n",begin_block_num);
        for(i=0;i<BLOCK_SIZE;i++){
            if(!dbs[begin_block_num].data[i]){
                flag=1;
                break;
            }
            printf("%c",dbs[begin_block_num].data[i]);
        }
        if(flag==1){
            break;
        }
        begin_block_num = dbs[begin_block_num].next_block_num;
        printf("\n");
    }
};


int findStringLength(char* s){
    int offset=0;
    int count=0;
    while(*(s+offset)!='\0'){
        offset+=1;
        count+=1;
    }
    return count;
}

int checkStringEqual(char* s1, char* s2){
    int l1=findStringLength(&s1[0]);
    int l2=findStringLength(&s2[0]);
    if(l1!=l2){
        return 0;
    }
    int offset=0;
    while(*(s1+offset)==*(s2+offset)){
        offset+=1;
    }
    if(offset-1!=l1){
        return 0;
    }
    return 1;
}

int findFileByName(char *data){
    int i;
    for (i = 0; i < sb.num_inodes; i++){
        if(checkStringEqual(&inodes[i].name[0],&data[0])==1){
            return i;
        }
    }
    return -1;
}
void read_file(char *data){
    int file_num=findFileByName(&data[0]);
    int begin_block_num = inodes[file_num].first_block_num;
    int i;
    int flag=0;
    while(dbs[begin_block_num].next_block_num!=-2){
        printf("the char in block %d is: \n",begin_block_num);
        for(i=0;i<BLOCK_SIZE;i++){
            if(!dbs[begin_block_num].data[i]){
                flag=1;
                break;
            }
            printf("%c",dbs[begin_block_num].data[i]);
        }
        if(flag==1){
            break;
        }
        begin_block_num = dbs[begin_block_num].next_block_num;
        printf("\n");
    }
};




/*notes:
understand
mount as read
sync as write
*/