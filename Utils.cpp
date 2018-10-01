
#include <iostream>
#include "Utils.h"
#include <cstdlib>
#include <cstdio>
#include <cstring>

using namespace std;
/*
	operation handler returns:
	1->insert case
	2->delete case
	3->find caller case
	4->lookup case
	5->indist1 case
	6->topdest case
	7->top case
	8->bye case
	9->print case
	10->dump case
	(Opws einai arithmimeno kai stin ekfwnisi)
	Also removes operations name from buffer
*/

int operation_handler(char * buffer,char * buffer2){
	int i=0;
	char first[20]={'\0'};
	//cout<<"buffer : "<<buffer<<endl;
	while ((buffer[i]!=' ')&&(buffer[i]!='\n')){
		first[i]=buffer[i];
		i++;
	}
	if(strncmp(first,"insert",strlen("insert")*sizeof(char))==0){
		strcpy(buffer2,buffer+strlen("insert "));
		//cout<<"buffer - insert "<<buffer2<<endl;
		return 1;
	}
	else if(strncmp(first,"delete",strlen("delete")*sizeof(char))==0){
		strcpy(buffer2,buffer+strlen("delete "));
		//cout<<"buffer-delete "<<buffer2<<endl;
		return 2;
	}
	else if (strncmp(first,"find",strlen("find")*sizeof(char))==0){
		strcpy(buffer2,buffer+strlen("find "));
		//cout<<"buffer - find caller "<<buffer2<<endl;				
		//cout<<"return 3"<<endl;
		return 3;
	}
	else if(strncmp(first,"lookup",strlen("lookup")*sizeof(char))==0){
		strcpy(buffer2,buffer+strlen("lookup "));
		//cout<<"buffer - lookup "<<buffer2<<endl;
		return 4;
	}
	else if(strncmp(first,"indist",strlen("indist")*sizeof(char))==0){
		strcpy(buffer2,buffer+strlen("indist "));
		//cout<<"buffer - indist1 "<<buffer2<<endl;
		return 5;
	}
	else if(strncmp(first,"topdest",strlen("topdest")*sizeof(char))==0){
		strcpy(buffer2,buffer+strlen("topdest "));
		//cout<<"buffer - topdest "<<buffer2<<endl;
		return 6;
	}
	else if(strncmp(first,"top",strlen("top")*sizeof(char))==0){
		strcpy(buffer2,buffer+strlen("top "));
		//cout<<"buffer - top "<<buffer2<<endl;
		return 7;
	}
	else if(strncmp(first,"bye",strlen("bye")*sizeof(char))==0){
		return 8;
	}
	else if(strncmp(first,"print",strlen("print")*sizeof(char))==0){

		strcpy(buffer2,buffer+strlen("print "));
		//cout<<"buffer - print "<<buffer2<<endl;
		return 9;
	}
	else if(strncmp(first,"dump",strlen("dump")*sizeof(char))==0){
		strcpy(buffer2,buffer+strlen("dump "));
		cout<<"buffer - dump "<<buffer2<<endl;
		return 10;
	}
	else{
		//cout<<"ERROR"<<endl;
		return -1;
	}
}
Node<Cdr> * insert(Lista<Cdr> * lista, char * buffer){
	int j=0,k=0;
	char temp[9][15]={'\0'};
	for(int i=0;i<9;i++){
		k=0;
		while(buffer[j]!=';'&&j<strlen(buffer)-1&& buffer[j]!='\0' & buffer[j]!='\n'){
			temp[i][k]=buffer[j];

			k++;
			j++;															
		}
		j++;
	}
		Cdr * newcdr;
		newcdr = new Cdr((char* const)(temp[0]),(char* const)(temp[1]),(char* const)(temp[2]),(char* const)(temp[3]),(char* const)(temp[4]),
			temp[5],atoi(temp[6]),atoi(temp[7]),temp[8]);
		//newcdr->print();
		 return (lista->push(newcdr));
}
int * get_time(char* temp1,char * temp2){
	int * toreturn;
	toreturn = new int [4];
	toreturn[0] = atoi(temp1);
	toreturn[1] = atoi(temp1+3);
	toreturn[2] = atoi(temp2);
	toreturn[3]= atoi(temp2+3);
	return toreturn;

}

int * get_year(char * temp1,char * temp2){
	int * toreturn;
	toreturn = new int [6];
	char charyear[5];
	strncpy(charyear,temp1+4,4);
	charyear[4]='\0';
	toreturn[0] = atoi(charyear);
	strncpy(charyear,temp2+4,4);
	charyear[4]='\0';
	toreturn[3]= atoi(charyear);
	char charmon[3];
	strncpy(charmon,temp1+2,2);
	charmon[2]='\0';
	toreturn[1] = atoi(charmon);
	strncpy(charmon,temp2+2,2);
	charmon[2]='\0';
	toreturn[4] = atoi(charmon);
	char charday[3];
	strncpy(charday,temp1,2);
	charday[2]='\0';
	toreturn[2] = atoi(charday);
	strncpy(charday,temp2,2);
	charday[2]='\0';
	toreturn[5]= atoi(charday);
	return toreturn;
}

int * get_year_time(char* temp1,char *temp2,char *temp3,char *temp4){
	int * toreturn;
	toreturn = new int [10];
	int * getyear = get_year(temp2,temp4);
	int * gettime = get_time(temp1,temp3);
	for(int i=0;i<6;i++){
		toreturn[i]=getyear[i];
	}
	for(int i=6;i<10;i++){
		toreturn[i]=gettime[i-6];
	}
	delete [] getyear;
	delete[] gettime;
	return toreturn;
}

void find_caller(Hash<Bucket_caller> * hashtable1,char * buffer){
	int j=0;
	int i=0;
	int k=0;
	char ** temp;
	temp  = new char * [5];
	for(i=0;i<5;i++){
		temp[i]= NULL;
	}
	i=0;
	int max=strlen(buffer);
	while(i<max){
		if(buffer[i]==' ' || i==strlen(buffer)-1){
			temp[k]=new char[15];
			if(k==0){
				strncpy(temp[k],buffer,i);
			}
			else{
				strncpy(temp[k],buffer+j+1,i-j);
			}
			temp[k][i-j]='\0';
			j=i;
			k++;
			//cout<<"k "<<k<<endl;
		}
		i++;
	}
	if(k==0){
		cout<<"ERROR k==0 from find_caller"<<endl;
	}
	Lista <Bucket> * blist;
	char charkey[15];
	i=0;
	j=0;
	max=strlen(temp[0]);
		while(i<strlen(temp[0])){
			if(temp[0][i]=='-'){
				i++;
				continue;
			}
			charkey[j]=temp[0][i];
			i++;
			j++;
		}
		charkey[j]='\0';
		uint64_t key = atoll(charkey);
		caller_node * cnode = hashtable1->searchc(key);
		if(cnode!=NULL)
		blist = cnode->plist;
		if(k==1){		    //case: all calls
		//	cout<<temp[0]<<"contacted: "<<endl;
		//	blist->printList();
		//  cout<<"\n\n";
		}
		else if(k==3){		//case caller time1 time2
							//or   caller year1 year2
			if(strstr(temp[1],":")){		//time case
				int * argum = get_time(temp[1],temp[2]);
				blist->check_time(argum);
				delete [] argum;
			}
			else{							//year case
				int * argum = get_year(temp[1],temp[2]);	
				blist->check_year(argum);
				delete [] argum;
				 
			}

		}
		else if(k==5){		//case caller time1 time2 year1 year2
			int * argum = get_year_time(temp[1],temp[2],temp[3],temp[4]);
			blist->check_year_time(argum);
			delete [] argum;
		}	
	for(i=0;i<k;i++){
		delete[] temp[i];
	}
	delete [] temp;
	return;
}

void lookup_callee(Hash<Bucket_receiver> * hashtable2,char * buffer){
	int j=0;
	int i=0;
	int k=0;
	char ** temp;
	temp  = new char * [5];
	for(i=0;i<5;i++){
		temp[i]= NULL;
	}
	i=0;
	int max=strlen(buffer);
	while(i<max){
		if(buffer[i]==' ' || i==strlen(buffer)-1){
			temp[k]=new char[15];
			if(k==0){
				strncpy(temp[k],buffer,i);
			}
			else{
				strncpy(temp[k],buffer+j+1,i-j);
			}
			temp[k][i-j]='\0';
			j=i;
			k++;
		}
		i++;
	}
	if(k==0){
		cout<<"ERROR k==0 from looku"<<endl;
	}
	Lista <Bucket> * blist;
	char charkey[15];
	i=0;
	j=0;
	max=strlen(temp[0]);
		while(i<strlen(temp[0])){
			if(temp[0][i]=='-'){
				i++;
				continue;
			}
			charkey[j]=temp[0][i];
			i++;
			j++;
		}
		charkey[j]='\0';
		uint64_t key = atoll(charkey);
		blist = hashtable2->search(key);
		if(k==1){		    //case: all calls
		//	cout<<temp[0]<<"contacted: "<<endl;
		//	blist->printList();
		//  cout<<"\n\n";
		}
		else if(k==3){		//case caller time1 time2
							//or   caller year1 year2
			if(strstr(temp[1],":")){		//time case
				int * argum = get_time(temp[1],temp[2]);
				blist->check_time(argum);
				delete [] argum;
			}
			else{							//year case
				int * argum = get_year(temp[1],temp[2]);	
				blist->check_year(argum);
				delete [] argum;
				 
			}

		}
		else if(k==5){		//case caller time1 time2 year1 year2
			int * argum = get_year_time(temp[1],temp[2],temp[3],temp[4]);
			blist->check_year_time(argum);
			delete [] argum;
		}	
	for(i=0;i<k;i++){
		delete[] temp[i];
	}
	delete [] temp;
	return;
}
/*
	-->For now with list later maybe with hashtable <--
*/
void indist(Hash<Bucket_caller> * hashtable1,Hash<Bucket_receiver> * hashtable2, char* buffer){
	int j=0;
	int i=0;
	int k=0;
	char ** temp;
	temp  = new char * [2];
	temp[0]=NULL;
	temp[1]=NULL;
	int max=strlen(buffer);
	while(i<max){
		if(buffer[i]==' ' || i==strlen(buffer)-1){
			temp[k]=new char[15];
			if(k==0){
				strncpy(temp[k],buffer,i);
			}
			else{
				strncpy(temp[k],buffer+j+1,i-j);
			}
			temp[k][14]='\0';

			j=i;
			k++;
		}
		i++;
	}
		//cout<<"temp[0]"<<temp[0]<<" temp[1]"<<temp[1]<<endl;
	if(k==0){
		cout<<"ERROR k==0 from indist"<<endl;
	}
	char charkey[15];
	i=0;
	j=0;
	max=strlen(temp[0]);
		while(i<max){
			if(temp[0][i]=='-'){
				i++;
				continue;
			}
			charkey[j]=temp[0][i];
			i++;
			j++;
		}
	charkey[j]='\0';
	uint64_t key = atoll(charkey);
	caller_node * cnode = hashtable1->searchc(key);
	Lista<Bucket> * caller1_list1 = cnode->plist;					//nodes that caller1 called		
	Lista<Bucket> * caller1_list2 = hashtable2->search(key);		//nodes that called caller1
	i=0;
	j=0;
	max=strlen(temp[1]);
	while(i<max){
		if(temp[1][i]=='-'){
			i++;
			continue;
		}
		charkey[j]=temp[0][i];
		i++;
		j++;
	}
	charkey[j]='\0';
	key = atoll(charkey);
	cnode = hashtable1->searchc(key);
	Lista <Bucket> * caller2_list1 = cnode->plist;					//nodes that caller2 called
	Lista<Bucket> * caller2_list = hashtable2->search(key);			//nodes that called caller2
	delete [] temp[0];
	delete [] temp[1];
	delete [] temp;
}

void dump(Hash<Bucket_caller> * hashtable1,Hash<Bucket_receiver> * hashtable2,char * buffer){
	cout<<"-----------------------"<<endl;
	int j=0;
	int i=0;
	int k=0;
	char ** temp;
	temp  = new char * [2];
	temp[0]=NULL;
	temp[1]=NULL;
	int max=strlen(buffer);
	while(i<max){
		if(buffer[i]==' ' || i==strlen(buffer)-1){
			temp[k]=new char[15];
			if(k==0){
				strncpy(temp[k],buffer,i);
			}
			else{
				strncpy(temp[k],buffer+j+1,i-j);
			}
			temp[k][i-j]='\0';

			j=i;
			k++;
		}
		i++;
	}
		cout<<"temp[0]"<<temp[0]<<" temp[1]"<<temp[1]<<endl;
	if(k==0){
		cout<<"ERROR k==0 from indist"<<endl;
	}
	cout<<"before hash dump"<<endl;
	if(strcmp(temp[0],"hashtable1")==0){
		hashtable1->dump(temp[1]);
	}
	/*else{
		hashtable2->dump(temp[1]);
	}*/
	delete [] temp[0];
	delete [] temp[1];
	delete [] temp;
}