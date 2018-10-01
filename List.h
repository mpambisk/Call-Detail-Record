
#ifndef LISTA_H
#define LISTA_H
#include <iostream>
#include <stdint.h>
//#include "Heap.h"
#include "Bucket.h"
using namespace std;

//-----------------------Node-----------------------//
class Bucket;
class Bucket_caller;
//class Bucket_receiver;

template <class T> class Node
{
    T* data; 		//the object information
    Node* next; 	//pointer to the next node element
    Node* prev;

public:
	Node(){
		data = NULL;
		next = NULL;
		prev=NULL;
	}
	~Node(){
		next = NULL;
        if(data!=NULL)
            delete data;
		data = NULL;
	}
	void setData(T* info){
		data = info;
	}
	void setNext(Node * n){
		next = n;
	}
	void setPrev(Node * n){
		prev= n;
	}
	T* getData(){
		return data;
	}
	Node* getNext(){
		return next;
	}
	Node * getPrev(){
		return prev;
	}
	void printNode(){
		data->print();
		//cout<<data->get_key();
	}
    void dumpNode(char * filen,FILE * dfile){
         data->dump(filen,dfile);
    }
    void dataNULL(){
        data=NULL;
    }
};


//-----------------------Lista-----------------------//
template <class T> class Lista
{
    Node<T> *head, *tail;
    uint64_t counter; 

public:

    Lista()
    {
    	counter = 0;
        head = NULL;
        tail = NULL;
    }
    ~Lista()
    {
    	while (counter > 0){
    		pop();
    	}
    }

   Node <T> * get_tail(){return tail;}
   uint64_t get_counter(){return counter;}
    void deleteLista(){
        T* temp;

		while (counter > 0){
    		temp = pop();
    		delete temp;
    	}
    }

    //Method adds info to the end of the list
    Node<T> * push(T* info){
        if(head == NULL) //if our list is currently empty
        {
        	counter = 1;
            head = new Node<T>; //Create new node of type T
            head->setData(info);
            tail = head;
        }
        else //if not empty add to the end and move the tail
        {
        	counter++;
            Node<T>* temp = new Node<T>;
            temp->setData(info);
            tail->setNext(temp);
            temp->setPrev(tail);
            tail = tail->getNext();
        }
        return tail;
    }

    void popall(){
        if(head == NULL){ //if our list is currently empty
        	//EMPTY LIST
        	return;
        }
		while (counter > 0){
    		pop();
    	}
    }

    T* pop(){
        if(head == NULL){ //if our list is currently empty
        	//EMPTY LIST
        	return NULL;
        }
		
		counter--;
		Node<T>* temp = head;
		T* ret = temp->getData();
		head = head->getNext();
		delete temp;
		return ret;
    }
/*
    pop2 sets data pointer to NULL
    in order not to destroy this object
*/
    
    T* pop2(){
       if(head == NULL){ //if our list is currently empty
            //EMPTY LIST
            return NULL;
        }
        
        counter--;
        Node<T>* temp = head;
        T* ret = temp->getData();
        head = head->getNext();
        temp->dataNULL();
        delete temp;
        return ret;    
    }
    Node<T> * getHead(){return head;}

	uint64_t getCounter(){
	return counter;
	}

    void printList(){
    	Node<T>* cur = head;
    	while (cur!=NULL){
    		cur->printNode();
    		cur = cur->getNext();
    	}
    }

    void dumpList(char * filen,FILE * dfile){
        Node<T>* cur = head;
        while (cur!=NULL){
            cur->dumpNode(filen,dfile);
            cur = cur->getNext();
        }
    }
    Lista<Bucket> * searchl(uint64_t key){
        if(head==NULL)
            return NULL;
        Lista<Bucket> * toreturn = NULL;
        Node<T>* temp = head;
        while(temp!=NULL){

            toreturn=((temp->getData())->searchb(key));
            if(toreturn!=NULL)
                return toreturn;
            temp=temp->getNext();
        }
        return NULL;
    }
    caller_node * searchlb(uint64_t key){
        if(head==NULL)
            return NULL;
        caller_node * toreturn = NULL;
        Node<T>* temp = head;
        while(temp!=NULL){

            toreturn=((temp->getData())->searchb(key));
            if(toreturn!=NULL){
				return toreturn;
            }
            temp=temp->getNext();
        }
        return NULL;
    }
    int add_to_buck(Node<Cdr> * nodeptr){
        if(head==NULL){                                 //empty list
            Bucket * newbuck;
            newbuck = new Bucket(200);
            newbuck->add(nodeptr);
            this->push(newbuck);
        }
        else{
            if(((tail->getData())->is_full())==1){      //full bucket
                Bucket * newbuck;
                newbuck = new Bucket(200);
                newbuck->add(nodeptr);
                this->push(newbuck);
            }
            else{
                (tail->getData())->add(nodeptr);
            }
        }
    }
    
    int add_to_buckc(uint64_t key,Node<Cdr>* nodeptr,Heap_node * hnode=NULL){

        if(head==NULL){                              	 //Empty list
            Bucket_caller * newbuck;
            newbuck=new Bucket_caller(10);
            newbuck->add(key,nodeptr,hnode);
            this->push(newbuck);
        }
        else{                                           //Not empty
            Bucket_caller * temp = tail->getData();
            if(temp->is_full()==1){                 	//full bucket
                Bucket_caller * newbuck;
                newbuck=new Bucket_caller(10);
                newbuck->add(key,nodeptr,hnode);
                this->push(newbuck);
            }
            else{                                   	//empty space in bucket
                temp->add(key,nodeptr,hnode);
            }
        }
    }
    int add_to_buckr(uint64_t key,Node<Cdr>* nodeptr){

        if(head==NULL){                               	//Empty list
            Bucket_receiver * newbuck;
            newbuck=new Bucket_receiver(10);
            newbuck->add(key,nodeptr);
            this->push(newbuck);
        }
        else{                                           //Not empty
            Bucket_receiver * temp = tail->getData();
            if(temp->is_full()==1){                 	//full bucket
                Bucket_receiver * newbuck;
                newbuck=new Bucket_receiver(10);
                newbuck->add(key,nodeptr);
                this->push(newbuck);
            }
            else{                                   //empty space in bucket
                temp->add(key,nodeptr);
            }
        }
    }
    int deletec(char * cdrid){
    	Node<Bucket> * bucknode = head;
    	if(head==NULL )
    		return -1;
    	Bucket * buck = bucknode->getData();
    	int pos= (buck->search_spec_id(cdrid));				//found the specific id in bucket
    	while(pos==-1){								//while not found in this buck
    		if(bucknode==tail){					//if end of list not found id , return
    			return -1;
    		}					
    		bucknode=bucknode->getNext();			//next list node
    		buck=bucknode->getData();
    		pos = buck->search_spec_id(cdrid);		//search again
    	}
    	Node <Cdr> * last_cdr = tail->getData()->get_last();
    	Node <Cdr> * curr_cdr = buck->get_spec_ptr(pos);
    	if(bucknode==tail){
	    	if(last_cdr == curr_cdr){						//cdr ==  last node of list
	    		buck->nullify_spec_ptr(pos);
	    		if(buck->get_counter()== 0 ){
	    			//cout<<"empty bcuk need to delete bucket above"<<endl;
	    			return 1;
	    		}
	    		else{
	    			tail->getData()->nullify_spec_ptr(counter-1);
	    			return 0;
	    		}
	    	}
	    	else{
	    		buck->set_spec_ptr(pos,tail->getData()->get_spec_ptr(counter-1));
	    		tail->getData()->nullify_spec_ptr(counter-1);
	    		return 0;
	    	}
    	}
    	else{
    		buck->set_spec_ptr(pos,tail->getData()->get_spec_ptr(counter-1));
    		tail->getData()->nullify_spec_ptr(counter-1);
    		if(tail->getData()->get_counter()==0){
    			return 1;
    		}
    		return 0;
    	}
    }
   /*
   		function to fix list, delete
   		empty buckets something went wrong
   */
    int fix(){ 
    	if(head==NULL){
    		return 1;
    	}
 
    	while(tail->getData()->get_counter()==0){
    		if(counter==1){
    			return 1;
    		}
    		Node<T> * temp=tail;
    		tail=tail->getPrev();
    		tail->setNext(NULL);
    		delete temp;
    		temp=NULL;
    		counter--;
    	}
    	if(counter==0){
    		return 1;
    	}
    	return 0;
    }

    void check_time(int * argum){
    	Node<T>* cur = head;
    	while (cur!=NULL){
    		cur->getData()->check_time(argum);
    		cur = cur->getNext();
    	}
    }
    void check_year(int * argum){
    	Node<T>* cur = head;
    	while (cur!=NULL){
    		cur->getData()->check_year(argum);
    		cur = cur->getNext();
    	}
    }
    void check_year_time(int * argum){
    	Node<T>* cur = head;
    	
    	while (cur!=NULL){
    		cur->getData()->check_year_time(argum);
    		cur = cur->getNext();
    	}
    }
    int search_for_string(char* tosearch){
    	Node<T>* cur = head;
    	while (cur!=NULL){
    		if(strcmp(cur->getData(),tosearch)==0)
    			return 1;
    		cur = cur->getNext();
    	}
    	return 0;
    }
    void push_individuals(char* topush){
    	if(search_for_string(topush)==0)
    		push(topush);
    }
};

#endif