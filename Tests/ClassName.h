//
// Created by cristina on 04/12/2019.
//

#ifndef SETTINGUPGOOGLETEST_CLASSNAME_H
#define SETTINGUPGOOGLETEST_CLASSNAME_H

#include "gtest/gtest.h"
class ClassName {
public:
    int getAge(){
        return age;
    }
    void setAge(int age){
        this->age = age;
    }
private:
    int age;
};


#endif //SETTINGUPGOOGLETEST_CLASSNAME_H
