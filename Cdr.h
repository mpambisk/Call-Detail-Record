#ifndef CDR_H
#define CDR_H
#include <cstring>
#include "Secondary.h"

using namespace std;
class Cdr{
private:
	char cdr_uniq_id[12];
	char originator_number[15];
	char destination_number[15];
	char date[9];
	char init_time[6];
	char duration[5];
	int type;
	int tarrif;
	char fault_condition[5];
public:
	Cdr(const char*,const char*,const char*,const char*,const char*,char*,int,int,char*);
	~Cdr();
	//set
	void set_cdr_uniq_id(const char* to_set){strcpy(cdr_uniq_id,to_set);}
	void set_originator_number(const char* to_set){strcpy(originator_number,to_set);}
	void set_destination_number(const char* to_set){strcpy(destination_number,to_set);}
	void set_date(const char* to_set){strcpy(date,to_set);}
	void set_init_time(const char* to_set){strcpy(init_time,to_set);}
	void set_duration(char * to_set){strcpy(duration,to_set);}
	void set_type(int to_set){type=to_set;}
	void set_tarrif(int to_set){tarrif=to_set;}
	void set_fault_condition(char* to_set){strcpy(fault_condition,to_set);}
	//get
	char* get_cdr_uniq_id(){return cdr_uniq_id;}
	char* get_originator_number(){return originator_number;}
	char* get_destination_number(){return destination_number;}
	char* get_date(){return date;}
	char* get_init_time(){return init_time;}
	char* get_duration(){return duration;}
	int get_type(){return type;}
	int get_tarrif(){return tarrif;}
	char * get_fault_condition(){return fault_condition;}
	//print 
	void print();
	void dump(char *,FILE *);
	/**/
	double calc_price();
	Cdr * check_year(int *);
	Cdr * check_time(int *);

};

#endif