#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include "Cdr.h"

using namespace std;


Cdr::Cdr(const char* to_id,const char* to_orig,const char* to_des,const char* to_date,const char* to_time,
char * to_dur,int to_type,int to_tar,char* to_con){
	strcpy(cdr_uniq_id,to_id);
	strcpy(originator_number,to_orig);
	strcpy(destination_number,to_des);
	strcpy(date,to_date);
	strcpy(init_time,to_time);
	strcpy(duration,to_dur);
	type=to_type;
	tarrif=to_tar;
	strcpy(fault_condition,to_con);
	//cout<<"Cdr constructor"<<endl;
}

Cdr::~Cdr(){
	//cout<<"Cdr destructor"<<endl;
}


void Cdr::print(){
	cout<<"cdr_uniq_id: "<<cdr_uniq_id<<endl;
	cout<<"originator_number: "<<originator_number<<endl;
	cout<<"destination_number: "<<destination_number<<endl;
	cout<<"date: "<<date<<endl;
	cout<<"init_time: "<<init_time<<endl;
	cout<<"duration: "<<duration<<endl;
	cout<<"type: "<<type<<endl;
	cout<<"tarrif: "<<tarrif<<endl;
	cout<<"fault_condition: "<<fault_condition<<endl;

}

void Cdr::dump(char * filen,FILE * dfile){
	char buffer[200]={'\0'};
	char durationstr[2];
	char typestr[2];
	typestr[0]=type+'0';
	typestr[1]='\0';
	char tarrifstr[2];
	tarrifstr[0]=tarrif+'0';
	tarrifstr[1]='\0';
	strcat(buffer,"insert ");
	strcat(buffer,cdr_uniq_id);
	strcat(buffer,";");
	strcat(buffer,originator_number);
	strcat(buffer,";");
	strcat(buffer,destination_number);
	strcat(buffer,";");
	strcat(buffer,date);
	strcat(buffer,";");
	strcat(buffer,init_time);
	strcat(buffer,";");
	strcat(buffer,duration);
	strcat(buffer,";");
	strcat(buffer,typestr);
	strcat(buffer,";");
	strcat(buffer,tarrifstr);
	strcat(buffer,";");
	strcat(buffer,fault_condition);
	fputs(buffer,dfile);
	fputs("\n",dfile);
}

double Cdr::calc_price(){
	if(type==0)
		return 0.1;
	if(type==1){
		if(tarrif==1)
			return atoi(duration) * 0.5;
		else if(tarrif==2)
			return atoi(duration);

	}
	if(type==2){
		if(tarrif==1)
			return atoi(duration) * 0.2;
		else if(tarrif==2)
			return atoi(duration) * 0.5;
	}
}

Cdr * Cdr::check_year(int * argum){
	int start_year = argum[0];
	int start_mon = argum[1];
	int start_day = argum[2];
	int end_year = argum[3];
	int end_mon = argum[4];
	int end_day = argum[5];
	char charday[3];
	strncpy(charday,date,2);
	charday[2]='\0';
	char charmon[3];
	strncpy(charmon,date+2,2);
	charmon[2]='\0';
	char charyear[5];
	strncpy(charyear,date+4,4);
	charyear[4]='\0';
	int init_year = atoi(charyear);
	int init_mon = atoi(charmon);
	int init_day = atoi(charday);
	if((init_year > end_year)||(init_year<start_year))
			return NULL;
		if(init_year==start_year){
			if(init_mon<start_mon)
				return NULL;
			if(init_mon==start_mon){
				if(init_day<start_day)
					return NULL;
			}
		}
		if(init_year==end_year){
			if(init_mon>end_mon)
				return NULL;
			if(init_mon==end_mon){
				if(init_day>end_day)
					return NULL;
			}
		}
		return this;
}

Cdr * Cdr::check_time(int * argum){
	int start_hours=argum[0];
	int start_mins = argum[1];
	int end_hours = argum[2];
	int end_mins = argum[3];
	int init_hours = atoi(init_time);
	int init_mins = atoi(init_time+3);
	if(start_hours>=end_hours){
		//stuff here
	}
	if((init_hours < start_hours)||(init_hours > end_hours))
		return NULL;
	if(init_hours == start_hours){
		if(init_mins < start_mins )
			return NULL;
	}
	if(init_hours == end_hours){
		if(init_mins > end_mins )
			return NULL;
	}
	return this;
}