//
// Created by 陈晶晶 on 2021/7/24.
//
#include <android/log.h>
#ifndef MYJNISTUDYPROJECT_LOGUTIL_H
#define MYJNISTUDYPROJECT_LOGUTIL_H

#define LOGI(tag, ...) __android_log_print(ANDROID_LOG_INFO, tag, __VA_ARGS__)
#define LOGE(tag, message) __android_log_print(ANDROID_LOG_ERROR, tag, message)

#endif //MYJNISTUDYPROJECT_LOGUTIL_H
