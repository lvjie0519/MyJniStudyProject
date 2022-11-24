//
// Created by lvjie on 2022/3/28.
//

#include <string>
#include "StudentNative.h"
#include "utils/LogUtil.h"
#include "jnihelper/ScopedGlobalRef.h"
#define TAG "StudentNative"

#define NATIVE_METHOD(name, signature) {#name, signature, (void *)Student_##name}

#define CLASS_NAME_Student                          "com/example/mynativelib/Student"

static JavaVM *sJvm = nullptr;
static jint sJvmVersion = -1;

void JNICALL Student_callJavaValue(JNIEnv *env, jobject obj) {
    // 直接过去java 层的变量
//    jclass jclass1 = env->GetObjectClass(obj);
//    jfieldID id_mName = env->GetFieldID(jclass1, "mName", "java/lang/String");
//    jobject mName = env->GetObjectField(obj, id_mName);

    jclass jclass1 = env->GetObjectClass(obj);
    jfieldID id_mAge = env->GetFieldID(jclass1, "mAge", "I");

    LOGI(TAG, "jni toString: %s", "aaa");

    env->SetIntField(obj, id_mAge, 100);
}

void testStringSplit(){
    std::string string1 = "";
    std::string string2 = "bbb@local";

    int index = string1.find_last_of("@");
    LOGI(TAG, "index1: %d", index);
    if(index != std::string::npos){
        string1 = string1.substr(0, index+1);
    }

    index = string2.find_last_of("@");
    LOGI(TAG, "index2: %d", index);
    if(index != std::string::npos){
        string2 = string2.substr(0, index);
    }

    LOGI(TAG, "string1: %s", string1.c_str());
    LOGI(TAG, "string2: %s", string2.c_str());
}
#define MAX_LENGTH 3;
void testStringSubStr(){
    std::string string1 = "123456789";
    std::string string2 = "1234";

    int sub = MAX_LENGTH;
    int len = string1.length();
    for (int i = 0; i < len; i += sub) {
        int subLen = ((len - i) >= sub) ? sub : (len - i);
        std::string result = string1.substr(i, subLen);
        LOGI(TAG, "result: %s", result.c_str());
    }
    LOGI(TAG, "====================================");

    len = string2.length();
    for (int i = 0; i < len; i += sub) {
//        int subLen = ((len - i) >= sub) ? sub : (len - i);
        std::string result = string2.substr(i, len);
        LOGI(TAG, "result: %s", result.c_str());
    }

    LOGI(TAG, "====================================");
    std::string result = string1.substr(0, 0);
    LOGI(TAG, "result: %s", result.c_str());    // result:

    result = string1.substr(0, 1);
    LOGI(TAG, "result: %s", result.c_str());    // result: 1

    result = string1.substr(0, string1.length());
    LOGI(TAG, "result: %s", result.c_str());    // result: 123456789

    result = string1.substr(0, string1.length()+2);
    LOGI(TAG, "result: %s", result.c_str());    // result: 123456789
}

void JNICALL Student_callJavaMethod(JNIEnv *env, jobject obj) {
    // 调用java 层的方法

//    jclass jclass1 = env->GetObjectClass(obj);
//    jmethodID id_toString = env->GetMethodID(jclass1, "toString", "()Ljava/lang/String;");
//    jobject result = env->CallObjectMethod(jclass1, id_toString);

    // todo string object 怎么转换
//    jstring  jstring1 = (jstring)result;
//    // 获取字符串指针
//    const jchar *jchar1 = env->GetStringChars(jstring1, NULL);
//    LOGI(TAG, "toString: %s", jchar1);

    testStringSubStr();

    // 释放指针
//    env->ReleaseStringChars(jstring1, jchar1);
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

class NativeOnClickListener{
public:
    explicit NativeOnClickListener(JNIEnv *env, jobject object) : mRef(*sJvm, *env, object) {
    }

    void onClick(){
        jnihelper::ScopedJniEnv envGuard(*sJvm, sJvmVersion);
        if (!envGuard.valid()) {
            return;
        }
        JNIEnv *env = envGuard.getEnv();
//        env->CallVoidMethod(mRef.get(), sAuthCallbacks[NOTIFY_AUTH_SUCCESS].id, jmsg->get());
    }

private:
    jnihelper::ScopedGlobalRef<jobject> mRef;
};

void Student_setOnClickListenerNative(JNIEnv *env, jobject obj, jobject jlistener) {
    LOGI(TAG, "Student_setOnClickListenerNative");
    if (jlistener == nullptr) {
        LOGI(TAG, "Student_setOnClickListenerNative  jlistener is null");
        return;
    }

    std::shared_ptr<NativeOnClickListener> listener = std::make_shared<NativeOnClickListener>(env,jlistener);
    if (listener != nullptr) {
        listener->onClick();
    }
}

static JNINativeMethod methods[] = {
        NATIVE_METHOD(callJavaValue, "()V"),
        NATIVE_METHOD(callJavaMethod, "()V"),
        NATIVE_METHOD(setOnClickListenerNative, "(Lcom/example/mynativelib/OnClickListener;)V"),
};

bool initStudentNative(JavaVM *vm, JNIEnv *env) {
    if (!vm || !env) {
        LOGE(TAG, "Invalid Arguments");
        return false;
    }

    sJvm = vm;
    sJvmVersion = env->GetVersion();

    if (!registerNativeMethods(env, CLASS_NAME_Student,methods,sizeof(methods) / sizeof(methods[0]))) {
        return JNI_FALSE;
    }

    return true;
}