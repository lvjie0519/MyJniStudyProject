//
// Created by lvjie on 2022/3/28.
//

#include <string>
#include "StudentNative.h"
#include "utils/LogUtil.h"
#define TAG "StudentNative"

#define NATIVE_METHOD(name, signature) {#name, signature, (void *)Student_##name}

#define CLASS_NAME_Student                          "com/example/mynativelib/Student"

void JNICALL Student_callJavaValue(JNIEnv *env, jobject obj) {
    // 直接过去java 层的变量
//    jclass jclass1 = env->GetObjectClass(obj);
//    jfieldID id_mName = env->GetFieldID(jclass1, "mName", "java/lang/String");
//    jobject mName = env->GetObjectField(obj, id_mName);

    jclass jclass1 = env->GetObjectClass(obj);
    jfieldID id_mAge = env->GetFieldID(jclass1, "mAge", "I");

    env->SetIntField(obj, id_mAge, 100);
}

void JNICALL Student_callJavaMethod(JNIEnv *env, jobject obj) {
    // 调用java 层的方法

    jclass jclass1 = env->GetObjectClass(obj);
    jmethodID id_toString = env->GetMethodID(jclass1, "toString", "()Ljava/lang/String;");
    jobject result = env->CallObjectMethod(jclass1, id_toString);

    // todo string object 怎么转换
//    LOGI(TAG, "toString: %s", str);
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
        NATIVE_METHOD(callJavaValue, "()V"),
        NATIVE_METHOD(callJavaMethod, "()V"),
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