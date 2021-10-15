#include "bot.h"

using namespace std;

int main(int argc, char* argv[]){
    
    try{
        if(argc<4){
            throw MISSING_ARGUMENT;
        }
    }
    catch(const int& num){
        cout << MISSING_ARGUMENT_MESSAGE;
        return 0;
    }

    DataBase allCourseDataBase;
    allCourseDataBase.count = 0;
    Group groupsList[MAX_ALLOWED];
    string path1 = argv[1];
    string path2 = argv[2];
    char* seed = argv[3];
    string message;
    InputQuery query;
    int max_profiles = 0;
    int database_ch = 0;
    
    try{
        //functions
        load_database (path1, allCourseDataBase);
        Instructor profile[allCourseDataBase.count];
        load_instructors(profile, allCourseDataBase, max_profiles, database_ch);
        load_groupList(path2, groupsList, allCourseDataBase);
        int Seed = load_seed(seed);
        initializeWithSeed(Seed);
        while(getline(cin, message)){
            load_inputMessage(message, query);
            judge_query(query, allCourseDataBase, groupsList, profile, Seed);
        }
    }
    catch(const Exception& exception){
        if (exception.error_code == CANNOT_OPEN_FILE){
            cout << CANNOT_OPEN_FILE_PREFIX << exception.Info << endl;
            return 0;
        }
        if(exception.error_code == INVALID_ARGUMENT){
            cout << exception.Info << endl;
            return 0;
        }
    }

    return 0;
}