
#include <iostream>
#include "Utils.h"
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;


int main(int argc,char* argv[]){

	char * foperation = NULL ;			//var to store operation file 
	char * fconfig = NULL;				//var to store configuration file
	uint64_t h1size = 20000;		//default hashtable size with key=originator
	uint64_t h2size = 20000;		//-//- key = destinator	
	int bsize = 3;
/*
	command line arguments
*/
	for(int i=1;i<argc;i++){
		if(strcmp(argv[i],"-o")==0){
			cout<<"operation file case file to open : "<<argv[++i]<<endl;
			foperation =new char[32];
			strcpy(foperation,argv[i]);
		}
		else if(strcmp(argv[i],"-h1")==0){
			cout<<"hashtable1 size = "<<argv[++i]<<endl;
			h1size=atoi(argv[i]);
		}
		else if(strcmp(argv[i],"-h2")==0){
			cout<<"hashtable1 size = "<<argv[++i]<<endl;
			h2size=atoi(argv[i]);
		}
		else if(strcmp(argv[i],"-c")==0){
			cout<<"bucket size = "<<argv[++i]<<endl;
			bsize = atoi(argv[i]);
		}
		else if(strcmp(argv[i],"-s")==0){
			cout<<"config file case file to open : "<<argv[++i]<<endl;
			fconfig = new char[32];
			strcpy(fconfig,argv[i]);
		}
	}
/*
	end of arguments
*/
/*
	initialise all the structs needed
*/
	Lista <Cdr> * lista;
	lista=new Lista <Cdr>;

	Hash <Bucket_caller>  * hashtable1;
	hashtable1 = new Hash <Bucket_caller>(h1size);

	Hash <Bucket_receiver> * hashtable2;
	hashtable2 = new Hash <Bucket_receiver>(h2size);

	Heap * maxheap;
	maxheap = new Heap;
	Node <Cdr> * tempnode;

	if(foperation!=NULL){											//we have an operation file
		int cases;
		FILE * operat = fopen(foperation,"r");
		char buffer [200],buffer2[200];
		while (fgets(buffer,200,operat)!=NULL){
			cases=operation_handler(buffer,buffer2);				//check function for return values
			if(cases==1){											//insert case
				tempnode=insert(lista,buffer2);						//insert to list with cdr
				hashtable1->insert(buffer2,tempnode,maxheap);		//insert to h1,set ptr to tempnode list
																	//also insert or update to heap
				hashtable2->insert(buffer2,tempnode);				//insert to h2,no need to add to heap
			}
			else if(cases==2){									//delete case
				hashtable1->deletec(buffer2);
			}
			else if(cases==3){									//find case
				find_caller(hashtable1,buffer2);
			}
			else if(cases==4){									//lookup case
				lookup_callee(hashtable2,buffer2);
			}
			else if(cases==5){									//indist1 case
				indist(hashtable1,hashtable2,buffer2);
			}
			else if(cases==6){									//topdest case

			}
			else if(cases==7){									//top case

			}
			else if(cases==8){									//bye case
				break;
			}
			else if(cases==9){									//print case
			if(strncmp(buffer2,"hashtable1",10)==0){
				//hashtable1->print();
			}
			else{
				//hashtable2->print();
			}
			}
			else if(cases==10){									//dump case
				dump(hashtable1,hashtable2,buffer);
			}
			//else
			//	cout<<"ERROR OPERATION_HANDLER"<<endl;

		}
		fclose(operat);					//close operation file pointer
	}
/*
	code to read from stdin, stores at buffer
*/
	char buffer[200],buffer2[200];
	int cases;
	char bye[5]="bye\n";
	cases=12;				//buffer2 contains the string
															//without name of operation
//*************ADD MESSAGE FOR WRONG INPUT**********
	while(cases!=8){										//bye
		cout<<"give input or bye to terminate"<<endl;
		fgets(buffer,200,stdin);
		cases=operation_handler(buffer,buffer2);
		cout<<"cases "<<cases<<endl;
		if(cases==1){											//insert case
			tempnode=insert(lista,buffer2);						//insert to list with cdr
			hashtable1->insert(buffer2,tempnode,maxheap);		//insert to h1,set ptr to tempnode list
																//also insert or update to heap
			hashtable2->insert(buffer2,tempnode);				//insert to h2,no need to add to heap
		}
		else if(cases==2){									//delete case
			hashtable1->deletec(buffer2);
		}
		else if(cases==3){									//find case
			find_caller(hashtable1,buffer2);
		}
		else if(cases==4){									//lookup case
			lookup_callee(hashtable2,buffer2);
		}
		else if(cases==5){									//indist1 case

		}
		else if(cases==6){									//topdest case

		}
		else if(cases==7){									//top case

		}
		else if(cases==8)
			break;
		else if(cases==9){									//print case
			cout<<"buffer2 "<<buffer2<<endl;
			if(strncmp(buffer2,"hashtable1",10)==0){
				//hashtable1->print();
			}
			else{
				//hashtable2->print();
			}
		}
		else if(cases==10){									//dump case
			dump(hashtable1,hashtable2,buffer2);
		}
		else{
			cout<<"ERROR WRONG INPUT"<<endl;
			cout<<"TRY AGAIN "<<endl;
		}

	}
	//maxheap->print();										//debug
	//lista->printList();									//debug
	//hashtable1->print();									//debug
	if(foperation!=NULL){
		delete [] foperation;
	}
	if(fconfig!=NULL)	
		delete [] fconfig;
	delete lista;
	hashtable1->count();
	delete hashtable1;
	delete hashtable2;
	delete maxheap;
}
