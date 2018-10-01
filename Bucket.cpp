#include <iostream>
#include "Bucket.h"
#include "List.h"
#include <cstdlib>
using namespace std;

Bucket::Bucket(int to_bsize){
	bsize=to_bsize;
	counter=0;
	cdr_list_node=new Node<Cdr> * [bsize];
	for(int i=0;i<bsize;i++)
		cdr_list_node[i]=NULL;
	//cout<<"Bucket constructor"<<endl;
}
Bucket::~Bucket(){
	delete[] cdr_list_node;
	//cout<<"Bucket destructor"<<endl;
}
int Bucket::add(Node <Cdr> * nodeptr){
	cdr_list_node[counter]=nodeptr;
	counter++;
}

int Bucket::search_spec_id(char * cdrid){
	for(int i=0;i<counter;i++){
		if(strcmp(cdrid,((cdr_list_node[i]->getData())->get_cdr_uniq_id()))==0){
			return i;
		}
	}
	return -1;
}
void Bucket::print(){
	cout<<"max bucket size : "<<bsize;
	cout<<" current bucket size "<<counter<< endl;
	for(int i=0;i<counter;i++){
		cdr_list_node[i]->getData()->print();
		cout<<endl;
	}
}
void Bucket::dump(char * filen,FILE * dfile){
	for(int i=0;i<counter;i++){
		cdr_list_node[i]->getData()->dump(filen,dfile);
	}
}
int Bucket::deletec(char * cdrid,Bucket * tail){
	if(counter==0)
		return counter;
	for(int i=0;i<counter;i++){
		Cdr * data = cdr_list_node[i]->getData();
		if(strcmp(data->get_cdr_uniq_id(),cdrid)==0){
			if(is_full()==0){
				if(i==(counter-1)){									//last node
					cdr_list_node[i]=NULL;
					counter--;
					return counter;
				}
				else{
					cdr_list_node[i]=cdr_list_node[counter-1];
					cdr_list_node[counter-1]=NULL;
					counter--;
					return counter;
				}
			}
		}
	}
}
void Bucket::check_time(int *argum){
	for(int i=0;i<counter;i++){
		Cdr * cdr_ptr=cdr_list_node[i]->getData();
		Cdr * temp = cdr_ptr->check_time(argum);
		if(temp!=NULL){
			//temp->print();
		}
	}
}
void Bucket::check_year(int *argum){
	for(int i=0;i<counter;i++){
		Cdr * cdr_ptr=cdr_list_node[i]->getData();
		Cdr * temp = cdr_ptr->check_year(argum);
		if(temp!=NULL){
			//temp->print();
		}
	}
}
void Bucket::check_year_time(int * argum){
	for(int i=0;i<counter;i++){
		Cdr * cdr_ptr=cdr_list_node[i]->getData();
		Cdr * temp = cdr_ptr->check_year(argum);
		if(temp!=NULL)
			temp = temp->check_time(argum+6);
			if(temp!=NULL){
				//temp->print();
			}
	}
}
Bucket_caller::Bucket_caller(int to_bsize){
	bsize=to_bsize;
	cells=new caller_node*[bsize];
	counter=0;
	for(int i=0;i<bsize;i++)
		cells[i]=NULL;
	//cout<<"Bucket caller constructor"<<endl;
}
Bucket_caller::~Bucket_caller(){
	for(int i=0;i<bsize;i++){
		if(cells[i]!=NULL){
			delete cells[i]->plist;
			delete cells[i];
		}
	}
	delete [] cells;
	//cout<<"Bucket caller destructor"<<endl;
}
caller_node * Bucket_caller::searchb(uint64_t key){
	if(counter==0)
		return NULL;
	for(int i=0;i<counter;i++){
		if((cells[i]->key)==key){
			//cout<<"from searchb key = "<<cells[i]->key<<endl;
			return cells[i];
		}
	}
	return NULL;
}
int Bucket_caller::add(uint64_t key, Node<Cdr> * nodeptr,Heap_node * hnode){
	cells[counter]=new caller_node;
	cells[counter]->key=key;
	cells[counter]->heapnode = hnode;
	Lista <Bucket> * temp;
	temp=new Lista<Bucket>;
	temp->add_to_buck(nodeptr);				//add to List<Bucket>
	cells[counter]->plist=temp;
	counter++;
}

void Bucket_caller::print(){
	cout<<"max bucket_caller size : "<<bsize;
	cout<<" current bucket_caller size "<<counter<< endl;
	for(int i=0;i<counter;i++){
		cout<<"Bucket key "<<cells[i]->key<<endl;
		cells[i]->plist->printList();
	}
}
void Bucket_caller::dump(char * filen,FILE * dfile){
	for(int i=0;i<counter;i++){
		cells[i]->plist->dumpList(filen,dfile);
	}
}

Bucket_receiver::Bucket_receiver(int to_bsize){
	bsize=to_bsize;
	cells=new receiver_node*[bsize];
	counter=0;
	for(int i=0;i<bsize;i++)
		cells[i]=NULL;
	//cout<<"Bucket receiver constructor"<<endl;
}

Bucket_receiver::~Bucket_receiver(){
	for(int i=0;i<bsize;i++){
		if(cells[i]!=NULL){
			delete cells[i]->plist;
			delete cells[i];
		}
	}
	delete [] cells;
	//cout<<"Bucket receiver destructor"<<endl;
}
int Bucket_receiver::add(uint64_t key, Node<Cdr> * nodeptr){
	cells[counter]=new receiver_node;
	cells[counter]->key=key;
	Lista <Bucket> * temp;
	temp=new Lista<Bucket>;
	temp->add_to_buck(nodeptr);				//add to List<Bucket>
	cells[counter]->plist=temp;
	counter++;
}
void Bucket_receiver::print(){
	cout<<"max bucket_receiver size : "<<bsize;
	cout<<" current bucket_receiver size "<<counter<< endl;
	for(int i=0;i<counter;i++){
		cout<<"Bucket key "<<cells[i]->key<<endl;
		cells[i]->plist->printList();
	}
}

void Bucket_receiver::dump(char * filen,FILE * dfile){
	for(int i=0;i<counter;i++){
		cells[i]->plist->dumpList(filen,dfile);
	}
}

Lista<Bucket> * Bucket_receiver::searchb(uint64_t key){
	if(counter==0)
		return NULL;
	for(int i=0;i<counter;i++){
		if((cells[i]->key)==key)
			return cells[i]->plist;
	}
	return NULL;
}
