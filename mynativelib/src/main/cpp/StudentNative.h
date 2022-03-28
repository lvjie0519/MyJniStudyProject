//
// Created by lvjie on 2022/3/28.
//

#ifndef MYJNISTUDYPROJECT_STUDENTNATIVE_H
#define MYJNISTUDYPROJECT_STUDENTNATIVE_H

#include <jni.h>

/**
 * 初始化 HttpRequestNative
 *
 * @param vm 虚拟机
 * @param env JNI 环境
 * @return true 成功
 */
bool initStudentNative(JavaVM *vm, JNIEnv *env);


#endif //MYJNISTUDYPROJECT_STUDENTNATIVE_H
