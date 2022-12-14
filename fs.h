
#define BLOCK_SIZE 512

struct superblock
{
    int num_inodes;
    int num_blocks;
    int size_blocks;
};

struct inode
{
    int size;
    int first_block_num;
    char name[8];
    int blocks[10];
};

struct disk_block
{
    int next_block_num;
    char data[512];
};

void create_fs(); // create a new file system
void mount_fs();  // mount an existing file system
void sync_fs();   // write all dirty blocks to disk

// return file number
int allocate_file(char filename[12]);                       // allocate a new file
void set_file_size(int file_num, int size);                 // set the size of a file
void write_data_to_file(int file_num, int pos, char *data); // write data to a file
void read_file(char *data);


void print_fs(); // print the file system
void print_char(int file_num);
