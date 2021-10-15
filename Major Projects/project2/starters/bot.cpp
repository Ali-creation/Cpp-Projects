#include "bot.h"

void split_string(string& input, string* arr){
    string search = ",";
    int findPos;
    int curPos = 0;
    int prevPos = 0;
    int c = 0;

    do{
        findPos = input.find(search, curPos);
        if(findPos>=0){
            curPos = findPos;
            arr[c] = input.substr(prevPos, curPos-prevPos);
            curPos++;
            prevPos = curPos;
            c++;
        }
    }while( findPos>=0 );
    arr[c] = input.substr(prevPos, input.length());
}


void load_database(string& filename, DataBase& allCourses){
    ifstream courseDataFile(filename);
    if(!courseDataFile.is_open()){
        throw Exception(CANNOT_OPEN_FILE, filename);
    }
    int n;
    courseDataFile >> n;
    string freeSpace;
    getline(courseDataFile, freeSpace);
    string line;
    //This could be replaced with a for loop
    while(getline(courseDataFile, line)){
        string arr[3];
        split_string(line, arr);
        allCourses.courseCodes[allCourses.count] = arr[0];
        allCourses.courseNames[allCourses.count] = arr[1];
        allCourses.teachers[allCourses.count] = arr[2];
        allCourses.count++;
    }
    courseDataFile.close();
}


void load_groupList(string& filename, Group* groupsList, DataBase& allCourses){
    ifstream groupListFile(filename);
    if(!groupListFile.is_open()){
        throw Exception(CANNOT_OPEN_FILE, filename);
    }
    string groupPath; int n; string freeSpace;
    getline(groupListFile, groupPath);
    groupListFile >> n;
    getline(groupListFile, freeSpace);
    allCourses.num_groups = n;
    string line;
    for(int i=0; i<n; i++){
        getline(groupListFile, line);
        groupsList[i].name = line;
        string path = groupPath + "/" + line;
        ifstream groupCheck(path);
        if(!groupCheck.is_open()){
            throw Exception(CANNOT_OPEN_FILE, filename);
        }
        int m; string blank; string member;
        groupCheck >> m;
        getline(groupCheck, blank);
        for(int j=0; j<m; j++){
            getline(groupCheck, member);
            groupsList[i].members[j] = member;
            groupsList[i].num_members++;
        }
    }
    groupListFile.close();
}

int load_seed(char* seedString){
    long long int getSeed = atoll(seedString);
    int seed;
    if(!is_in_int_range(getSeed))
        throw Exception(INVALID_ARGUMENT, OUT_OF_RANGE_MESSAGE);
    seed = getSeed;
    if (seed == 0)
        throw Exception(INVALID_ARGUMENT, INVALID_ARGUMENT_MESSAGE);
    return seed;
}

void load_instructors(Instructor* profile, DataBase& courses,int& max_profile, int& database_ch){
    if(database_ch == courses.count){
        courses.max_profile = max_profile;
        return;
    }
        
    profile[max_profile].name = courses.teachers[database_ch];
    if(max_profile > 0){
        for (int i=0; i < max_profile; i++){
            if(profile[max_profile].name.compare(profile[i].name) == 0){
                database_ch++;
                load_instructors(profile, courses, max_profile, database_ch);
                return;
            }
        }
    }
    
    profile[max_profile].courses[profile[max_profile].max] = courses.courseCodes[database_ch];
    profile[max_profile].max++;
    for (int i=database_ch+1; i<courses.count; i++){
        if (profile[max_profile].name.compare(courses.teachers[i]) == 0){
            profile[max_profile].courses[profile[max_profile].max] = courses.courseCodes[i];
            profile[max_profile].max++;
        }
    }
    max_profile++;
    database_ch++;
    load_instructors(profile, courses, max_profile, database_ch);
}

void load_inputMessage(string& inputMessage, InputQuery& query){
    string arr[4];
    split_string(inputMessage, arr);
    query.time = arr[0];
    query.group = arr[1];
    query.user = arr[2];
    query.content = arr[3];
}

void judge_query(InputQuery& query, DataBase& allCourses, Group* groupList, Instructor* profiles, int seed){
    
    if (group_check(query.group, allCourses, groupList)){
        string command;
        string target;
        int pndPos = query.content.find("#", 0);
        if(pndPos == 0){
            
            int spacePos = query.content.find(" ", 1);
            if(spacePos == -1)
                command = query.content.substr(pndPos, query.content.length());
            else
                command = query.content.substr(pndPos, spacePos);
            
            int tarPosInit = query.content.find_first_not_of(" ", spacePos);
            if(tarPosInit == -1)
                target = " ";
            else{
                int tarPosEnd = query.content.find_last_not_of(" ", query.content.length());
                target = query.content.substr(tarPosInit, tarPosEnd - tarPosInit +1);
            }

            if(command.compare("#stop") == 0)
                stop(query.group ,query.user, groupList, allCourses);
            else if(command.compare("#help") == 0)
                help();
            else if(command.compare("#time") == 0)
                time(query.time);
            else if(command.compare("#course") == 0)
                course(target,allCourses);
            else if(command.compare("#instructor") == 0)
                instructor(target, profiles, allCourses.max_profile);
            else
                rand_out(seed, query.content);
        }
        else{
            rand_out(seed, query.content);
        }
    }
}


bool group_check(string groupName, DataBase& allCourses, Group* groupList){
    for(int i=0; i< allCourses.num_groups; i++){
        if(groupList[i].name == groupName)
            return true;
    }
    return false;
}

bool is_in_int_range(long long int num){
    return ((num > -2147483648) && (num < 2147483648));
}

void course(string target, DataBase& courses){
    if (target == " ")
        cout << MISSING_KEYWORD << endl << endl;
    else{
        bool checker = false;
        for(int i=0; i< courses.count; i++){
            if(courses.courseCodes[i].find(target) <= 5 || courses.courseNames[i].find(target) <= 250){
                cout << "Course Code: " << courses.courseCodes[i] << endl;
                cout << "Course Name: " << courses.courseNames[i] << endl;
                cout << "Instructor: " << courses.teachers[i] << endl;
                checker = true;
            }
        }
        if(!checker)
            cout << COURSE_NOT_FOUND << endl;
        cout << endl;
    }
}

void instructor(string target, Instructor* profile, int maxProfile){

    if (target == " ")
        cout << MISSING_KEYWORD << endl << endl;
    else{
        bool checker;
        for(int i=0; i< maxProfile; i++){
            if(profile[i].name.find(target) <= 250){
                cout << "Instructor: " << profile[i].name << endl;
                cout << "Courses:";
                for (int j=0; j<= profile[i].max; j++){
                cout << " " << profile[i].courses[j];
                }
                cout << endl;
                checker = true;
            }
        }
        if(!checker)
            cout << FACULTY_NOT_FOUND << endl;
        cout << endl;
    }
}

void time(string time){
    cout << time << endl << endl;
}

void stop(string groupName, string user, Group* grouplist, DataBase allData){
    for (int i=0; i< allData.num_groups; i++){
        if (grouplist[i].name.compare(groupName) == 0){
            for(int j=0; j < grouplist[i].num_members; j++){
                if(grouplist[i].members[j].compare(user) == 0){
                    cout << EXIT_PROMPT << endl << endl;
                    exit(0);
                }
            }
        }
    }
    cout << STOP_BOT_FAIL << endl << endl;
}

void help(){
    cout << HELP_TEXT << endl << endl;
}

void rand_out(int seed, string& content){
    
    RespChoice action = randomResponse();
    switch (action){
        case NONE:
            return;
            break;
        case REPEAT:
            cout << content << endl << endl;
            break;
        case ADMIRE:
            if(flipCoin() == 1)
                cout << "Respect " << content << endl << endl;
            else
                cout << "I really admire " << content << endl << endl;
            break;
    }
}