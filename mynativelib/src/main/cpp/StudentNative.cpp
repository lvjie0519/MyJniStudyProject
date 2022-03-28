//
// Created by lvjie on 2022/3/28.
//

#include "StudentNative.h"
#include "utils/LogUtil.h"
#define TAG "StudentNative"

#define NATIVE_METHOD(name, signature) {#name, signature, (void *)Student_##name}

#define CLASS_NAME_Student                          "com/example/mynativelib/Student"

void JNICALL Student_sayHello(JNIEnv *env, jobject obj) {
    // 直接过去java 层的变量
//    jclass jclass1 = env->GetObjectClass(obj);
//    jfieldID id_mName = env->GetFieldID(jclass1, "mName", "java/lang/String");
//    jobject mName = env->GetObjectField(obj, id_mName);

    jclass jclass1 = env->GetObjectClass(obj);
    jfieldID id_mAge = env->GetFieldID(jclass1, "mAge", "I");

    env->SetIntField(obj, id_mAge, 100);
}

int registerNativeMethods(JNIEnv* env, const char* className,
                                 JNINativeMethod* gMethods, int numMethods){
    jclass clazz;

    clazz = env->FindClass(className);
    if (clazz == NULL)
        return JNI_FALSE;
    if (env->RegisterNatives(clazz, gMethods, numMethods) < 0){
        LOGE(TAG, "register nativers error");
        return JNI_FALSE;
    }

    return JNI_TRUE;
}

static JNINativeMethod methods[] = {
        NATIVE_METHOD(sayHello, "()V"),
};

bool initStudentNative(JavaVM *vm, JNIEnv *env) {
    if (!vm || !env) {
        LOGE(TAG, "Invalid Arguments");
        return false;
    }

    if (!registerNativeMethods(env, CLASS_NAME_Student,methods,sizeof(methods) / sizeof(methods[0]))) {
        return JNI_FALSE;
    }

    return true;
}