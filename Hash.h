#ifndef HASH_H
#define HASH_H
#include <stdint.h>
#include "List.h"
#include <cstdlib>
#include <cstdio>

template <class T>
class Hash{						
private:
	uint64_t tsize;
	Lista<T> ** table;
public:
	Hash(uint64_t to_size){						//constructor	
		tsize=to_size;
		table=new Lista<T> * [tsize];
		for(uint64_t i=0;i<tsize;i++)
			table[i]=NULL;
		cout<<"Hash constructor"<<endl;
	}
	~Hash(){									//destructor
		for(uint64_t i=0;i<tsize;i++){
			if(table[i]!=NULL)
				delete table[i];
		}
		delete [] table;
		cout<<"Hash destructor"<<endl;
	}
	//get
	uint64_t get_size(){return tsize;}
	Lista<T> ** get_table(){return table;}

	uint64_t hash_func(uint64_t key){return key%tsize;}			//hash function

	Lista<Bucket> * search(uint64_t key){						//search that returns pointer
		if(table[hash_func(key)]==NULL)							//to the second bucket list
			return NULL;
		return table[hash_func(key)]->searchl(key);
	}
	caller_node * searchc(uint64_t key){						//only for hash with key=originator number
		if(table[hash_func(key)]==NULL)
			return NULL;
		caller_node * toreturn;
		toreturn = table[hash_func(key)]->searchlb(key);
		return toreturn;
	}

	int insert(char * tokey,Node<Cdr> * nodeptr,Heap * toheap){		//insert for hashtable with key=originator number
		char first [20];
		int j=0;
		Cdr * temp_cdr;
		double price;	
		temp_cdr = nodeptr->getData();								//for heap
		price = temp_cdr->calc_price();								//for heap
			while(tokey[j]!=';'){
				j++;
			}
			j++;
		for(int i=0;i<20;i++){
			if(tokey[j]=='-'){
				j++;
				i--;
				continue;
			}
			if(tokey[j]!=';'){
				first[i]=tokey[j];
				j++;
			}
			else{
				first[i]='\0';
				break;
			}
		}
		uint64_t key=uint64_t(atoll(first));
		caller_node * cnode;
		cnode=this->searchc(key);
		uint64_t hashpos = hash_func(key);
		if(cnode==NULL){											//not found in hashtable
				if(table[hashpos]==NULL){							//hash table key pos = NULL
					table[hashpos]=new Lista<Bucket_caller>;		//create new list with buckets
					//cout<<"new position hash"<<endl;
				}
				Heap_node * heap_node_temp = toheap->insert(temp_cdr->get_originator_number(),price);
				table[hashpos]->add_to_buckc(key,nodeptr,heap_node_temp);		//hash::insert->list::add_buckc->Bucket_caller::add
																				//->list::add_buck->Bucket::add
		}
		else{					         										//found in hashtable
			Heap_node * heap_node_temp = cnode->heapnode;						//only need to add node to 2nd Bucket list 
			heap_node_temp = heap_node_temp->update(price);						//update price of heap
			toheap->sort(heap_node_temp);
			Lista<Bucket> * ptr = cnode->plist;
			ptr->add_to_buck(nodeptr);										
		}
	}
	int insert(char * tokey,Node<Cdr> * nodeptr){							//for hashtable with key = destinator
		char first [20];													//only difference with previous insert
		int j=0;															//is that now we have bucket_receiver
		for(int i=0;i<2;i++){												//in the hashtable no need for heap
			while(tokey[j]!=';'){
				j++;
			}
			j++;
		}
		for(int i=0;i<20;i++){
				if(tokey[j]=='-'){
					j++;
					i--;
					continue;
			}
			if(tokey[j]!=';'){
				first[i]=tokey[j];
				j++;
			}
			else{
				first[i]='\0';
				break;
			}
		}
		uint64_t key=uint64_t(atoll(first));
		Lista<Bucket> * ptr;
		ptr=this->search(key);
		uint64_t hashpos = hash_func(key);
		if(ptr==NULL){										//not found in hashtable
				if(table[hashpos]==NULL){						//hash table key pos = NULL
					table[hashpos]=new Lista<Bucket_receiver>;	//create new list with buckets
				}
				table[hashpos]->add_to_buckr(key,nodeptr);		//hash::insert->list::add_buckc->Bucket_caller::add
																//->list::add_buck->Bucket::add
		}
		else{					         					//found in hashtable
			ptr->add_to_buck(nodeptr);
		}
	}
	void print(){
		for(int i=0;i<tsize;i++){
			if(table[i] != NULL){
				table[i]->printList();
			}
		}
	}
	void deletec(char * delstr){
		char cdrid[15],orignum[15];
		int j=0;
		while(delstr[j]!=' '&& delstr[j]!='\n' && delstr[j]!='\0'){
			cdrid[j] = delstr[j];
			j++;
		}
		cdrid[j]='\0';
		strcpy(orignum,delstr + j+1);
		char temporignum[15];
		j=0;
		int i=0;
		while(orignum[j]!='\0'){
			if(orignum[j]!='-'){
				temporignum[i]=orignum[j];
				i++;
			}
			j++;

		}
		caller_node * cnode =searchc(atoll(temporignum));
		if(cnode==NULL){
			return;
		}
		Lista<Bucket> * blist = cnode-> plist;
		if(blist==NULL){							//not found
			return;
		}
		else{
			if(blist->deletec(cdrid)==1){
				if(blist->fix()==1){
					uint64_t hashpos = hash_func(atoll(temporignum));
					Lista<Bucket_caller> * bclist = table[hashpos];
					cout<<"---------------------------------"<<endl;
					int sometemp=bclist->fix();
					cout<<"sometemp= "<<sometemp<<endl;
					if(sometemp==1){
						cout<<"mpike"<<endl;
						table[hashpos]=NULL;
					}
					cout<<"---------------------------------"<<endl;

				}
			}
			}

	}
	void count(){
		int j =0;
		for(int i=0;i<tsize;i++){
			if(table[i]!=NULL){
				j++;
			}
		}
		cout<<"\n\n TO J = "<<j<<"\n\n";
	}

	void dump(char * filen){
		FILE * dfile= fopen(filen,"w");
		for(int i=0;i<tsize;i++){
			if(table[i] != NULL){
				table[i]->dumpList(filen,dfile);
			}
		}
		fclose(dfile);
	}
	
	
};

#endif