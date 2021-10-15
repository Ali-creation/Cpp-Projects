#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>
#include "rand.h"

using namespace std;


const int CANNOT_OPEN_FILE = 1003;
const int MISSING_ARGUMENT = 1002;
const int INVALID_ARGUMENT = 1001;
const int MAX_ALLOWED = 500;

struct Exception: public exception{
    int error_code;
    string Info;

    Exception(int err, const string& info){
        this->error_code = err;
        this->Info = info;
    }
};

struct DataBase{
    string courseCodes[MAX_ALLOWED];
    string courseNames[MAX_ALLOWED];
    string teachers[MAX_ALLOWED];
    int count = 0;
    int num_groups = 0;
    int max_profile = 0;
};

struct Group{
    string name;
    string members[MAX_ALLOWED];
    int num_members = 0;
};

struct Instructor{
    string name;
    string courses[10];
    int max = 0;
};

struct InputQuery{
    string time;
    string group;
    string user;
    string content;
};

void split_string(string& input, string* arr);
void load_database(string& filename, DataBase& allCourses);
void load_groupList(string& filename, Group* groupsList, DataBase& allCourses);
int load_seed(char* seedString);
void load_instructors(Instructor* profile, DataBase& courses,int& max_profile, int& database_ch);

void load_inputMessage(string& inputMessage, InputQuery& query);
void judge_query(InputQuery& query, DataBase& allCourses, Group* groupList, Instructor* profiles, int seed);
bool group_check(string groupName, DataBase& allCourses, Group* groupList);
bool is_in_int_range(long long int num);

void course(string target, DataBase& courses);
void instructor(string target, Instructor* profile, int maxProfile);
void time(string time);
void stop(string groupName, string user, Group* grouplist, DataBase courses);
void help();
void rand_out(int seed, string& content);