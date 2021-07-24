//
// Created by 陈晶晶 on 2021/7/24.
//

#include "StringUtil.h"

std::string StringUtil::string_j2c(JNIEnv *env, jstring jstr) {
    if(jstr == NULL){
        return "";
    }

    jsize len = (*env).GetStringLength(jstr);
    char buffer[len];
    (*env).GetStringUTFRegion(jstr, 0, len, buffer);
    const jboolean is_error = (*env).ExceptionCheck();

    if (is_error == JNI_TRUE) {
        return "";
    }

    std::string ret = std::string(buffer, len);
    return ret;
}