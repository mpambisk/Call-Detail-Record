#ifndef HEAP_H
#define HEAP_H
#include <stdint.h>
#include <cstring>
class Heap_node{
private:
	long long int key;
	double value;					//
	Heap_node * left_child;
	Heap_node * right_child;
	Heap_node * parent;
public:
	Heap_node(long long int ,double,Heap_node *);
	~Heap_node();
	//set
	void set_left_child(Heap_node * toset){left_child=toset;}
	void set_right_child(Heap_node * toset){right_child=toset;}
	void set_parent(Heap_node * toset){parent=toset;}
	void set_key(long long int toset){key = toset;}
	void set_value(double toset){value=toset;}
	//get
	Heap_node * get_left_child(){return left_child;}
	Heap_node * get_right_child(){return right_child;}
	Heap_node * get_parent(){return parent;}
	long long int  get_key(){return key;}
	double get_value(){return value;}
	Heap_node * update(double);
	/**/

};

class Heap{
private:
	Heap_node * root;
	int height;
	uint32_t node_count;
public:
	Heap();
	~Heap();
	Heap_node * get_root(){return root;}
	void hdelete(Heap_node *);
	void print();							//prints tree
	void swap(Heap_node * , Heap_node * );
	void swap2(Heap_node * , Heap_node * );
	void sort(Heap_node *);
	Heap_node * insert(long long int,double);			//left to right top to bottom

};

#endif