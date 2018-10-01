#include "Heap.h"
#include <cmath>
#include <iostream>
#include <cstring>
#include "List.h"

using namespace std;

Heap_node::Heap_node(long long int tokey,double tovalue,Heap_node * toparent=NULL){
	left_child = NULL;
	right_child = NULL;
	parent = toparent;
	key =tokey;
	//cout<<"new heap node key = "<<key<<endl;
	value=tovalue;
	//cout<<"Heap node constructor"<<endl;
}

Heap_node::~Heap_node(){
	//cout<<"Heap node destructor"<<endl;
}

Heap::Heap(){
	root=NULL;
	height=-1;
	node_count=0;
//	cout<<"Heap constructor"<<endl;
}
Heap::~Heap(){
	if(root!=NULL)
		hdelete(root);
	//cout<<"Heap destructor"<<endl;
}



void Heap::hdelete(Heap_node * temp){
	if(temp->get_left_child()!=NULL)
		hdelete(temp->get_left_child());
	if(temp->get_right_child()!= NULL)
		hdelete(temp->get_right_child());
	delete temp;
}

/*
	Prints complete tree ending line when 
	height changes. At the top height 0
	to max height. | after nodes that have the same 
	parent
*/
void Heap::print(){
	cout<<"Height = "<<height<<endl;
	if(root==NULL)
		return;
	Lista<Heap_node> * mylist;
	mylist=new Lista<Heap_node >;
	Lista<Heap_node> * mylist2;
	mylist2=new Lista<Heap_node>;
	Heap_node * temp;
	mylist->push(root);
	temp=root;
	for(int i=0;i<=height;i++){
		int j=0;
		while(mylist->getCounter()>0){
			Heap_node * htemp=mylist->pop2();
			j++;
			if(htemp->get_left_child()!=NULL)
				mylist2->push(htemp->get_left_child());	
			if(htemp->get_right_child()!=NULL)
				mylist2->push(htemp->get_right_child());
			if(htemp!=NULL)
				cout<<" "<<(htemp->get_key())<<" ";
			if(j==2){
				cout<<"|";
				j=0;
			}
		}
		cout<<endl;
		Lista <Heap_node> * temp3;
		temp3=mylist;
		mylist=mylist2;
		mylist2=temp3;
	}
	delete mylist;
	delete mylist2;

}

void Heap::swap(Heap_node * child, Heap_node * par){
	if(par==NULL){
		return;
	}
	if(child==NULL){
		return;
	}
	Heap_node * child_left_child = child->get_left_child();
	Heap_node * child_right_child = child->get_right_child();
	Heap_node * par_parent=par->get_parent();
	Heap_node * par_left_child = par->get_left_child();
	Heap_node * par_right_child = par->get_right_child();
	if(par_parent!=NULL){
		if(par_parent->get_right_child()== par){
			par_parent->set_right_child(child);
			child->set_parent(par_parent);
		}
		else if(par_parent->get_left_child() == par){
			par_parent->set_left_child(child);
			child->set_parent(par_parent);
		}
	}
	else{
		root=child;
		child->set_parent(NULL);
	}
	if(child_left_child!=NULL)
		child_left_child->set_parent(par);
	if(child_right_child!=NULL)
		child_right_child->set_parent(par);
	// ta meataksi tous twra
	if(par->get_right_child() == child){			//					par
		par->set_left_child(child_left_child);		//par-right_c				 	child
		par->set_right_child(child_right_child);
		child->set_left_child(par_left_child);
		child->set_right_child(par);
		par->set_parent(child);
		if(par_left_child!=NULL){
			par_left_child->set_parent(child);
		}
	}
	else if(par->get_left_child() == child){
		par->set_left_child(child_left_child);
		par->set_right_child(child_right_child);
		child->set_right_child(par_right_child);
		child->set_left_child(par);
		par->set_parent(child);
		if(par_right_child!=NULL)
			par_right_child->set_parent(child);
	}
}

void Heap::sort(Heap_node * newnode){
	Heap_node * par = newnode->get_parent();
	if(par==NULL)
		return;
	if(newnode->get_value() > par->get_value()){
		swap(newnode,par);
		sort(newnode);
	}
}
/*
	Heap::insert adds nodes left to right top to bottom
*/
Heap_node * Heap::insert(long long int tokey,double tovalue){
	Heap_node * temp;
	if(root==NULL){									//empty tree
		temp = new Heap_node(tokey,tovalue);
		root=temp;
		height=0;
		node_count=1;
		return temp;
	}
	else{											//not empty
		Heap_node * temp2, *tempparent;
		uint32_t max_nodes = pow(2,height+1)-1;
		if(node_count==max_nodes){						//full tree
			temp2 = root;
			while(temp2->get_left_child()!=NULL){		//go to the bottom left node
				temp2=temp2->get_left_child();
			}
			temp = new Heap_node(tokey,tovalue,temp2);	//create node and set parent temp2 node
			temp2->set_left_child(temp);				//set  temp2 left child temp(new node)
			height++;									//new lvl
			//print();
			sort(temp);
			return temp;


		}
		else{
			temp2 = root;
			uint32_t max_lowest = pow(2,height);			//count max number of nodes at the lowest lvl
			uint32_t empty_lowest = max_nodes - node_count;      //nodes lowest = empty spaces for nodes
		 													//at the lowest level
			uint32_t curr_lowest = max_lowest / 2 ;			//to check left or right
			while(temp2!=NULL){					
				if(empty_lowest > curr_lowest){				//left case (more empty nodes) at
					tempparent = temp2;						//the lowest lvl than half 2^h
		 			temp2 = temp2->get_left_child();
		 			if(temp2==NULL){
		 				temp2 = new Heap_node(tokey,tovalue,tempparent);
		 				tempparent->set_left_child(temp2);
		 				break;
		 			}
		 			empty_lowest=empty_lowest-curr_lowest;	//change empty_lowest and curr_lowest
		 			curr_lowest=curr_lowest / 2;			//for half lowest lvl
				}
				else{										//right case
					tempparent = temp2;
					temp2 = temp2->get_right_child();
					if(temp2==NULL){
						temp2 = new Heap_node(tokey,tovalue,tempparent);
						tempparent->set_right_child(temp2);
						break;
					}
					curr_lowest=curr_lowest / 2;			//only need to change curr_lowest
				}
			}
			root->set_parent(NULL);										//mpakalia
			Heap_node * tempn =root;
			sort(temp2);

		}

		node_count++;
		return temp2;
	}
}

Heap_node *  Heap_node::update(double toadd){
	value = value +toadd;
	return this;
}