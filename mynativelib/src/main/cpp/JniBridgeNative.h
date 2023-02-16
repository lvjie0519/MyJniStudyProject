//
// Created by lvjie on 2023/2/16.
//

#ifndef MYJNISTUDYPROJECT_JNIBRIDGENATIVE_H
#define MYJNISTUDYPROJECT_JNIBRIDGENATIVE_H


#include <jni.h>

/**
 * 初始化JniBridge
 * @return true 表示成功, false表示失败
 */
bool initJniBridgeNative(JavaVM *vm, JNIEnv *env);


#endif //MYJNISTUDYPROJECT_JNIBRIDGENATIVE_H
