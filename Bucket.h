#ifndef BUCKET_H
#define BUCKET_H
#include "Cdr.h"
#include <stdint.h>
#include "Heap.h"
template <class T> class Lista;
template <class T> class Node;

class Bucket{
private:
	int bsize;
	int counter;
	Node<Cdr> ** cdr_list_node;
public:
	Bucket(int);
	~Bucket();
	//get
	int get_bsize(){return bsize;}
	int get_counter(){return counter;}
	Node<Cdr> * get_last(){return cdr_list_node[counter-1];}
	Node<Cdr> * get_spec_ptr(int spec){return cdr_list_node[spec];}				//check <counter
	//set
	void set_counter(int to_counter){counter=to_counter;}
	void set_cdr_list_node(Node<Cdr> *to_cdr_list_node){cdr_list_node[counter++]=to_cdr_list_node;}
	void set_spec_ptr(int pos,Node<Cdr> * toset){cdr_list_node[pos]=toset;}
	/**/
	void incr_counter(){counter++;}
	void decre_counter(){counter--;}
	int is_full(){return ((counter<bsize-1)?0:1);}		//returns 0 if not full,1 if full
	int add(Node<Cdr> * );
	void nullify_spec_ptr(int pos){
		cdr_list_node[pos]=NULL;
		decre_counter();
	}
	int search_spec_id(char *);
	int deletec(char *,Bucket *);
	void print();
	void check_time(int *);
	void check_year(int*);
	//maybe change arguments with array ???
	void check_year_time(int *);
	void dump(char * ,FILE *);

};


struct caller_node{
	uint64_t key;
	Lista<Bucket> * plist;
	Heap_node * heapnode;
};

struct receiver_node{
	uint64_t key;
	Lista<Bucket> * plist;
};

class Bucket_caller{
private:
	int bsize;
	int counter;
	caller_node ** cells;
public:
	Bucket_caller(int);
	~Bucket_caller();
	//get
	int get_bsize(){return bsize;}
	int get_counter(){return counter;}
	//set
	void set_counter(int to_counter){counter=to_counter;}
	void set_cells(uint64_t,Node<Cdr> *);
	/**/
	int is_full(){return ((counter<bsize-1)?0:1);}		//returns 0 if not empty,1 if full
	void incr_counter(){counter++;}
	int add(uint64_t, Node<Cdr> *,Heap_node *);
	caller_node * searchb(uint64_t);
	void print();
	void dump(char * ,FILE *);

};

class Bucket_receiver{
private:
	int bsize;
	int counter;
	receiver_node ** cells;
public:
	Bucket_receiver(int);
	~Bucket_receiver();
	//get
	int get_bsize(){return bsize;}
	int get_counter(){return counter;}
	//set
	void set_counter(int to_counter){counter=to_counter;}
	void set_cells(uint64_t,Node<Cdr> *);
	/**/
	void incr_counter(){counter++;}
	int is_full(){return ((counter<bsize-1)?0:1);}		//returns 0 if not empty,1 if full
	Lista<Bucket> * searchb(uint64_t);
	int add(uint64_t, Node<Cdr> *);
	void print();
	void dump(char *,FILE * );


};
#endif