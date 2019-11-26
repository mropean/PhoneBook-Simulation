#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct sdata {
	string name;
	string nickname;
	string number;
};

struct lists {
	sdata data;
	lists* llink;
	lists* rlink;
};

class phonebook {
private:
	lists data;
	lists* head;
	int count;
public:
	phonebook();
	void file_Load();
	void count_increase();
	void count_decrease();
	void print_list();
	bool checking_number(string String);
	bool checking_name(string String);
	bool empty();
	void init(lists* phead);
	void Add_Member();
	void Delete_Member();
	void Search_Member();
	void file_Save();
	lists* Explore(string ckecking, int num);
	~phonebook();
};

long file_Size(ifstream& file);