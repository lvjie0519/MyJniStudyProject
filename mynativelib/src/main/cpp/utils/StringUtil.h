//
// Created by 陈晶晶 on 2021/7/24.
//

#ifndef MYJNISTUDYPROJECT_STRINGUTIL_H
#define MYJNISTUDYPROJECT_STRINGUTIL_H


#include <string>
#include <jni.h>

class StringUtil {
public:
    static std::string string_j2c(JNIEnv *env, jstring jstr);
};


#endif //MYJNISTUDYPROJECT_STRINGUTIL_H
