#include "Hash.h"

int operation_handler(char*,char*);
Node<Cdr> *  insert(Lista<Cdr>*,char*);
void find_caller(Hash<Bucket_caller> * ,char * );
void lookup_callee(Hash<Bucket_receiver> *,char*);
void indist(Hash<Bucket_caller> * ,Hash<Bucket_receiver> *, char * );
void dump(Hash<Bucket_caller> *,Hash<Bucket_receiver> *,char * );
int * get_time(char* ,char * );
int * get_year(char *,char *);
int * get_year_time(char*,char *,char *,char *);