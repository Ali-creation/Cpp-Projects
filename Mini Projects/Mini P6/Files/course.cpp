/*
 * VE280 Lab 7, SU2021
 * Created by cyx on 20-5-22.
 * Modified by makersmelx on June 28th, 2021.
 */

#include <iostream>
#include "course.h"

using namespace std;

void TechnicalCourse::updateTask(const std::string &type, int index, int dueMonth, int dueDay)
// REQUIRES: dueMonth and dueDay are in normal range.
// MODIFIES: this
// EFFECTS: if Task index of type already exists in tasks, updates its dueMonth & dueDay ;
//          otherwise, adds Task i of type at the end of tasks if tasks is not full,
//          throw an exception if tasks is full
{
    // TODO: implement this function
    for (int i  =0; i< numTasks; ++i){
        if(tasks[i].type == type){
            if(tasks[i].index == index){
                tasks[i].dueMonth = dueMonth;
                tasks[i].dueDay = dueDay;
                return;
            }
        }
    }
    if(sizeTasks == numTasks)
        throw TooManyTasks{};
    else{
        tasks[numTasks].type = type;
        tasks[numTasks].index = index;
        tasks[numTasks].dueMonth = dueMonth;
        tasks[numTasks].dueDay = dueDay;
        numTasks++;
    }
    //Print out the declaration of the Homeworks
    if(type == "Lab"|| type == "Project")
        cout << courseCode <<" " << type << " "<< index << " "<< "is released! Submit it via oj!" << endl;
    else
        cout << courseCode <<" " << type << " "<< index << " "<< "is released! Submit it via canvas!" << endl;
}

void TechnicalCourse::finishTask(const std::string &type, int index, int finishMonth, int finishDay)
// REQUIRES: Task index of type is in tasks. finishMonth and finishDay are in normal range.
// MODIFIES: this
// EFFECTS: removes Task index of type
{
    // TODO: implement this function
    bool done = false;
    int removedTaskNum;
    for (int i  =0; i< numTasks; ++i){
        if(tasks[i].type == type){
            if(tasks[i].index == index){
                if(tasks[i].dueMonth > finishMonth || (tasks[i].dueMonth == finishMonth && tasks[i].dueDay >= finishDay))
                    cout << courseCode << " "<< type <<" " << index << " "<< "is finished!" << endl;
                else
                    cout << courseCode << " "<< type <<" " << index << " "<< "is overdue!" << endl;
                done = true;
                removedTaskNum = i;
            }
        }
    }
    if (done){
        for(int i = removedTaskNum; i< numTasks; ++i){
            tasks[i] = tasks[i+1];
            //cout << "removed: " << i << endl;
        }
        tasks[numTasks-1] = Task{};
        numTasks--;
    }
    else
        return; 
}

void TechnicalCourse::print() {
    cout << courseCode << endl;
    for (int i = 0; i < numTasks; ++i) {
        cout << tasks[i].type << " " << tasks[i].index << ": "
                  << tasks[i].dueMonth << "/" << tasks[i].dueDay << endl;
    }
}

void UpperLevelTechnicalCourse::updateTask(const std::string &type, int index, int dueMonth, int dueDay)
// REQUIRES: dueMonth and dueDay are in normal range.
// MODIFIES: this
// EFFECTS: If Task index of type does not exist in tasks,
//          adds Task i of type according to its due date if tasks is not full, throw an exception if tasks is full.
//          If Task index of type already exists in tasks,
//          updates its position in tasks & dueMonth & dueDay if its dueMonth/dueDay is changed,
//          do nothing if its dueMonth/dueDay is unchanged.
{
    // TODO: implement this function
    bool updateExisted = false;
    int updatedTaskNum;
    for (int i  =0; i< numTasks; ++i){
        if(tasks[i].type == type){
            if(tasks[i].index == index){
                if(dueMonth == tasks[i].dueMonth && dueDay == tasks[i].dueDay)
                    return;
                else{
                    updateExisted = true;
                    updatedTaskNum = i;
                }
            }
        }
    }

    if(updateExisted){
        tasks[updatedTaskNum].dueMonth = dueMonth;
        tasks[updatedTaskNum].dueDay = dueDay;

        for(int i=1; i<numTasks; ++i){
            if(tasks[i].dueMonth > tasks[i-1].dueMonth || (tasks[i].dueMonth == tasks[i-1].dueMonth && tasks[i].dueDay > tasks[i-1].dueDay))
                continue;
            else if(tasks[i].dueMonth == tasks[i-1].dueMonth && tasks[i].dueDay == tasks[i-1].dueDay){
                if(i-1 == updatedTaskNum){
                    Task swap;
                    swap = tasks[i-1];
                    tasks[i-1] = tasks[i];
                    tasks[i] = swap;
                    updatedTaskNum++;
                }
                else
                    continue;
            }
            else{
                Task swap;
                swap = tasks[i-1];
                tasks[i-1] = tasks[i];
                tasks[i] = swap;
                updatedTaskNum++;
            }
        }
    }

    if(sizeTasks == numTasks && !updateExisted)
        throw TooManyTasks{};

    if(!updateExisted){
        int newTaskNum = 0;
        while (numTasks > newTaskNum){
            if (tasks[newTaskNum].dueMonth > dueMonth || (tasks[newTaskNum].dueMonth == dueMonth && tasks[newTaskNum].dueDay > dueDay))
                break;
            else
                newTaskNum++;
        }
        for(int i = numTasks; i>newTaskNum; --i ){
            tasks[i] = tasks[i-1];
        }
        tasks[newTaskNum].type = type;
        tasks[newTaskNum].index = index;
        tasks[newTaskNum].dueDay = dueDay;
        tasks[newTaskNum].dueMonth = dueMonth;
        numTasks++;

        if(type == "Team Project")
            cout << courseCode <<" " << type << " "<< index << " "<< "is released! Submit it via github!" << endl;
        else if(type == "Lab"|| type == "Project")
            cout << courseCode <<" " << type << " "<< index << " "<< "is released! Submit it via oj!" << endl;
        else
            cout << courseCode <<" " << type << " "<< index << " "<< "is released! Submit it via canvas!" << endl;
    }
    
}

Course *create(const std::string &classType, const std::string &courseCode) {
    if (classType == "Technical") {
        return new TechnicalCourse(courseCode);
    } else if (classType == "Upper Level Technical") {
        return new UpperLevelTechnicalCourse(courseCode);
    } else {
        return nullptr;
    }
}

Course *create(const std::string &classType, const std::string &courseCode, const int &size) {
    if (classType == "Technical") {
        return new TechnicalCourse(courseCode, size);
    } else if (classType == "Upper Level Technical") {
        return new UpperLevelTechnicalCourse(courseCode, size);
    } else {
        return nullptr;
    }
}
