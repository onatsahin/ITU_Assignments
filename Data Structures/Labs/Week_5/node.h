#define NAME_LENGTH 30
#define PHONENUM_LENGTH 15
#define TNAME_LENGTH 15


struct number{
char type[TNAME_LENGTH];
char num[PHONENUM_LENGTH];
number *next;
};

struct Phone_node{
char name[NAME_LENGTH];
number *phonenum;
Phone_node *next;
Phone_node *prev;
};
