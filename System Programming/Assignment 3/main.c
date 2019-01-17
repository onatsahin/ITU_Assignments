#define FUSE_USE_VERSION 26

#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <sys/types.h>
#include <sys/statvfs.h>
#include <tidy.h>
#include <tidybuffio.h>

#include <stdlib.h>

enum{
    KEY_HELP,
};

struct Node{
    char file_name[256]; // Maximum file name allowed in Linux.
    __off64_t tidied_size;
    struct Node *next;
};
struct Node *size_keeper_head;

int add_node(const char *filename, __off64_t fsize){
    struct Node * newnode =(struct Node *) malloc(sizeof(struct Node));
    struct Node *trav;
    if(newnode){
        newnode->next = NULL;
        newnode->tidied_size = fsize;
        strcpy(newnode->file_name, filename);
        // Add to head
        if(size_keeper_head == NULL)
            size_keeper_head = newnode;
        else{
            // Add to tail
            trav = size_keeper_head;
            while(trav->next != NULL)
                trav = trav->next;
            trav->next = newnode;
        }
        return 0;
    }
    else
        return -ENOMEM;
}

void delete_list(){
    struct Node *trav = size_keeper_head;
    while(size_keeper_head){
        trav = size_keeper_head;
        size_keeper_head = trav->next;
        free(trav);
    }
    size_keeper_head = NULL;
}

__off64_t find_file_size(const char *filename){
    
    __off64_t retVal = -1;
    struct Node *trav = size_keeper_head;
    
    while(trav != NULL){
        if(strcmp(filename, trav->file_name) == 0){
            retVal = trav->tidied_size;
            break;
        }
        trav = trav->next;
    }
    return retVal;
}



// Global var to keep the path of the files.
char *files_path;

// Tidy the input and return the tidied string.
char* tidy_doc(char *input){
    // lib-tidy.
    int rc = -1;
    TidyBuffer output = {0};
    TidyBuffer errbuf = {0};
    Bool ok;
    char * tidied_doc;
    TidyDoc tdoc = tidyCreate();
    ok = tidyOptSetBool( tdoc, TidyXhtmlOut, yes ); 
    // Load config file
    tidyLoadConfig(tdoc, "/home/bekci/Desktop/System_Programming_Project_3/Codes/libtidy_config.txt");

    if ( ok )
        rc = tidySetErrorBuffer( tdoc, &errbuf );      // Capture diagnostics
    if ( rc >= 0 )
        rc = tidyParseString( tdoc, input);           // Parse the input
    if ( rc >= 0 )
        rc = tidyCleanAndRepair( tdoc );               // Tidy it up!
    if ( rc >= 0 )
        rc = tidyRunDiagnostics( tdoc );               // Kvetch
    if ( rc > 1 )                                    // If error, force output.
        rc = ( tidyOptSetBool(tdoc, TidyForceOutput, yes) ? rc : -1 );
    if ( rc >= 0 )
        rc = tidySaveBuffer( tdoc, &output );          // Pretty Print

    if(rc >= 0){
        tidied_doc = malloc(sizeof(char) * (output.size+1) );
        strcpy(tidied_doc, (char*)output.bp);
        tidied_doc[output.size] = 0;
    }
    tidyBufFree( &output );
    tidyBufFree( &errbuf );
    tidyRelease( tdoc );
    return tidied_doc;
}

char* file_type(const char *file_path){
    int index = strlen(file_path) - 1, i = 0;
    int size = 0;
    // Go back till start of the extension 
    while(file_path[index] != '.' && index > 0) index--;

    if(index == 0) return NULL;
        
    size = strlen(file_path) - index;
    
    char *extension = malloc(sizeof(char) * (size));

    extension[size - 1] = '\0';
    
    for(i = 0; i < size; i++){
        extension[i] = file_path[i + index + 1];
    }

    return extension;
}

// Combine paths to get absolute path.
static char *translate_path(const char *path){
    
    int new_size = sizeof(char) * ( strlen(path) + strlen(files_path) + 1 ) ;
    
    char *our_path = malloc( new_size );
    
    
    strcpy(our_path, files_path);
    
    // Check last character.
    if( our_path[strlen(our_path) - 1] == '/'){
         our_path[strlen(our_path) - 1] = '\0';
    }

    strcat(our_path, path);
    return our_path;
}

static int html_fs_getattr(const char *path, struct stat *st_data){
    
    int retVal, fd;
    char *cur_path = translate_path(path);
    char *file_extension = file_type(path);
    char *temp_str;
    int prior_file_size = 0;

    // Fill file infos given its path.
    retVal = lstat(cur_path, st_data);

    
    // Return appropriate error code.
    if(retVal == -1){
        return -errno;
    }

    /* The size of the hmtl files will be different from the original.
     calculate the size after tidy operation */
    if(file_extension && strcmp(file_extension, "html") == 0 ){
        
        prior_file_size = find_file_size(path);
            
        if(prior_file_size == -1){
            printf("Node added\n");
            fd = open(cur_path, O_RDONLY);
            temp_str = malloc(sizeof(char) * (st_data->st_size + 1) );
            
            retVal = pread(fd, temp_str, st_data->st_size, 0);
            temp_str[st_data->st_size] = 0;
            st_data->st_size = strlen(tidy_doc(temp_str));
            free(temp_str);
            add_node(path,st_data->st_size);
        }
        else{
            printf("List used\n");
            st_data->st_size = prior_file_size;
        }
    }
    free(cur_path);

    if(file_extension)
        free(file_extension);

    return 0;
}

// NOTE: What is the purpose of this call.
static int html_fs_readlink(const char *path, char *buffer, size_t read_size){

    int retVal;
    
    char *cur_path = translate_path(path);

    retVal = readlink(cur_path, buffer, read_size - 1);

    free(cur_path);
    // Error occured?
    if( retVal == -1 ){
        return errno;
    }
    // Finish the string with null terminator.
    buffer[retVal] = '\0';
    return 0;
}

static int html_fs_readdir(const char *path, void *buffer, fuse_fill_dir_t filler,
                            off_t offset, struct fuse_file_info *file_info)
{
    // Datatype for directory stream objects. defined in dirent.h
    DIR *dp;
    struct dirent *de;
    
    int retVal;

    (void) offset;
    (void) file_info; // Additional information is unnecessary. Read only system.

    char *cur_path = translate_path(path);
    // Open directory given by its absolute path.
    dp = opendir(cur_path);
    
    free(cur_path);

    if( dp == NULL){
        retVal = -errno;
        return retVal;
    }

    while( (de = readdir(dp)) != NULL ){
        struct stat st;
        // Clear stat info.
        memset(&st, 0, sizeof(st));   
        
        st.st_ino = de->d_ino;
        st.st_mode = de->d_type << 12;
        // Add contents.
        if(filler(buffer, de->d_name, &st, 0))
            break;
    }

    closedir(dp);
    return 0;
}

static int html_fs_mknod(const char *path, mode_t mode, dev_t dev_num){
    (void)path;
    (void)mode;
    (void)dev_num;   
    // Read only system.
    return -EROFS;
}

static int html_fs_mkdir(const char *path, mode_t mode){
    (void)path;
    (void)mode;
    // Read only system.
    return -EROFS;
}

static int html_fs_unlink(const char *path){
    (void)path;
    // Read only system.
    return -EROFS;
}

static int html_fs_rmdir(const char *path){
    (void)path;
    // Read only system.
    return -EROFS;
}

static int html_fs_symlink(const char *from, const char *to){
    (void)from;
    (void)to;
    // Read only system.
    return -EROFS;
}

static int html_fs_rename(const char *from, const char *to){
    (void)from;
    (void)to;
    // Read only system.
    return -EROFS;
}

static int html_fs_link(const char *from , const char *to){
    (void)from;
    (void)to;
    // Read only system.
    return -EROFS;
}

static int html_fs_chmod(const char *path, mode_t mode){
    (void)path;
    (void)mode;
    // Read only system.
    return -EROFS;
}
// Change file owner and group
static int html_fs_chown(const char *path, uid_t uid, gid_t gid){
    (void)path;
    (void)uid;
    (void)gid;//Group id 
    // Read only system.
    return -EROFS;
}
// Change file size to a specified length.
static int html_fs_truncate(const char *path, off_t size){
    (void)path;
    (void)size;
    // Read only system.
    return -EROFS;
}

static int html_fs_utime(const char *path, struct utimbuf *buf)
{
    (void)path;
    (void)buf;
    // Read only system.
    return -EROFS;
}

static int html_fs_open(const char *path, struct fuse_file_info  *file_info){
    int retVal;
    // Allow only read opens.
    int file_flags = file_info->flags;
    

    if ((file_flags & O_WRONLY) || (file_flags & O_RDWR) || (file_flags & O_CREAT) || (file_flags & O_EXCL) || (file_flags& O_TRUNC) || (file_flags & O_APPEND)) {
        return -EROFS;
    }

    char *cur_path = translate_path(path);
    // File descriptor is returned.
    retVal = open(cur_path, file_flags);

    free(cur_path);
    if(retVal == -1){
        return -errno;
    }
    close(retVal);

    return(0);
}

static int html_fs_read(const char *path, char  *buffer
                    , size_t size, off_t offset, struct fuse_file_info *file_info){
    int fd;
    int retVal;
    
    char *file_extension = file_type(path);
    char *cur_path = translate_path(path);
    char *temp_file;

    (void)file_info; // It is known that file is read only

    fd = open(cur_path, O_RDONLY);

    free(cur_path);


    if(fd == -1){
        retVal = -errno;
        return retVal;
    }
    retVal = pread(fd, buffer, size, offset);
    buffer[retVal] = 0;
    
    if(retVal == -1){
        retVal = -errno;
    }
    
    if(file_extension && strcmp(file_extension,"html") == 0){
        temp_file = tidy_doc(buffer);
        retVal = strlen(temp_file);
        memcpy(buffer, temp_file, retVal);
        free(temp_file);
    }

    if(file_extension)
        free(file_extension);
    
    close(fd);
    return retVal;
}

static int html_fs_write(const char *path, const char *buffer,
                         size_t size, off_t offset, struct fuse_file_info *file_info){
    (void)path;
    (void)buffer;
    (void)size;
    (void)offset;
    (void)file_info;
    return -EROFS;

}

// Get filesystem statics
static int html_fs_statfs(const char *path, struct statvfs *st_buf){
    int retVal;
    char *cur_path = translate_path(path);

    // Fill the st_buf with statics.
    retVal = statvfs(cur_path, st_buf);
    free(cur_path);
    
    if(retVal == -1){
        return -errno;
    }
    return 0;
}

static int html_fs_release(const char *path, struct fuse_file_info *file_info){
    (void)path;
    (void)file_info;
    return 0;
}

static int html_fs_fsync(const char *path, int crap, struct fuse_file_info *file_info){
    (void)path;
    (void)crap;
    (void)file_info;
    return 0;
}

static int html_fs_access(const char *path, int mode){
    int retVal;
    char  *cur_path = translate_path(path);

    // Do not allow write access
    if(mode & W_OK)
        return -EROFS;
    
    retVal = access(cur_path, mode);
    
    free(cur_path);
    if(retVal == -1)
        return -errno;

    return retVal;
}

// Return read only file system error while setting extended attributes.
static int html_fs_setxattr(const char *path, const char *name, const char *value, size_t size, int flags){
    (void)path;
    (void)name;
    (void)value;
    (void)size;
    (void)flags;
    return -EROFS;
}

static int html_fs_getxattr(const char *path, const char *name, char *value, size_t size){
    int retVal;

    char *cur_path = translate_path(path);
    // Fill the value of an extended attribute given by its name of a file in cur_path.
    retVal = lgetxattr(cur_path, name, value, size);
    
    free(cur_path);
    if(retVal == -1)
        return errno;
    
    return retVal;
}


static int html_fs_listxattr(const char *path, char *list, size_t size){
    int retVal;

    char *cur_path = translate_path(path);
    // Fill the supported extended attributes
    retVal = listxattr(cur_path, list, size);

    free(cur_path);
    if(retVal == -1){
        return -errno;
    }
    return retVal;
}

// Cannot delete an extended attribute
static int html_fs_removexattr(const char *path, const char *name){
    (void)path;
    (void)name;
    return -EROFS;
}


struct fuse_operations html_fs_oper = {
    .getattr     = html_fs_getattr,
    .readlink    = html_fs_readlink,
    .readdir     = html_fs_readdir,
    .mknod       = html_fs_mknod,
    .mkdir       = html_fs_mkdir,
    .symlink     = html_fs_symlink,
    .unlink      = html_fs_unlink,
    .rmdir       = html_fs_rmdir,
    .rename      = html_fs_rename,
    .link        = html_fs_link,
    .chmod       = html_fs_chmod,
    .chown       = html_fs_chown,
    .truncate    = html_fs_truncate,
    .utime       = html_fs_utime,
    .open        = html_fs_open,
    .read        = html_fs_read,
    .write       = html_fs_write,
    .statfs      = html_fs_statfs,
    .release     = html_fs_release,
    .fsync       = html_fs_fsync,
    .access      = html_fs_access,
    // User space fuctions (userland)
    .setxattr    = html_fs_setxattr,
    .getxattr    = html_fs_getxattr,
    .listxattr   = html_fs_listxattr,
    .removexattr = html_fs_removexattr
};

static void help_user(){
    printf("Enter the path of website directory and mount point as a argument.\nAs an example:\n\t ./tidy_html <website directory> <mount point>\n\n");
}

static int html_fs_parse_opt(void *data, const char *arg, int key,
                          struct fuse_args *outargs)
{
    (void) data;

    switch (key)
    {
    case FUSE_OPT_KEY_NONOPT:
        if (files_path == 0)
        {
            files_path = strdup(arg);
            return 0;
        }
        else
        {
            return 1;
        }
    case FUSE_OPT_KEY_OPT:
        return 1;
    case KEY_HELP:
        help_user();
        exit(0);
    default:
        help_user();
        exit(1);
    }
    return 1;
}

static struct fuse_opt html_fs_opts[] = {
    FUSE_OPT_KEY("-h",          KEY_HELP),
    FUSE_OPT_KEY("--help",      KEY_HELP),
    FUSE_OPT_END
};

int main(int argc, char *argv[]){
    
    int res;
    struct fuse_args args = FUSE_ARGS_INIT(argc, argv);
    
    res = fuse_opt_parse(&args, &files_path, html_fs_opts, html_fs_parse_opt);
    if (res != 0)
    {
        fprintf(stderr, "Invalid arguments\n");
        fprintf(stderr, "see `%s -h' for usage\n", argv[0]);
        exit(1);
    }
    if (files_path == 0)
    {
        fprintf(stderr, "Missing website directory\n");
        fprintf(stderr, "see `%s -h' for usage\n", argv[0]);
        exit(1);
    }
    
    size_keeper_head = NULL;
    fuse_main(args.argc, args.argv, &html_fs_oper, NULL);
    // Clear linked list.
    delete_list();
    
    return 0;
}
