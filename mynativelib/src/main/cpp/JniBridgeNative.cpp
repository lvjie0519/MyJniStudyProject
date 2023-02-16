//
// Created by lvjie on 2023/2/16.
//

#include "JniBridgeNative.h"
#include <string>
#include "utils/LogUtil.h"
#include "jnihelper/ScopedGlobalRef.h"

#define TAG "JniBridgeNative"
#define CLASS_NAME                          "com/example/mynativelib/JniBridge"
#define NATIVE_METHOD(name, signature) {#name, signature, (void *)JniBridge_##name}
#define NELEM(array_name) (sizeof(array_name) / sizeof((array_name)[0]))

static JavaVM *sJvm = NULL;
static jint sJvmVersion = -1;

static jmethodID sDispatchCallbackMethodID = NULL;
static jmethodID sSubscribleMessageCallbackMethodID = NULL;

static void JniBridge_dispatchNative(JNIEnv *env, jobject object,
                                          jstring jModule, jstring jMethod,
                                          jstring jParam, jobject jCallback) {

    jobject localJCallback = env->NewGlobalRef(jCallback);
    jobject localJObject = env->NewGlobalRef(object);
    jstring jResponse = env->NewStringUTF("{\"code\":0,\"message\":\"\",\"data\":{\"state\":1}}");
    env->CallVoidMethod(localJObject, sDispatchCallbackMethodID, jResponse, localJCallback);

    env->DeleteGlobalRef(localJCallback);
    env->DeleteGlobalRef(localJObject);
    env->DeleteLocalRef(jResponse);
}

static const JNINativeMethod sMethods[] = {
        NATIVE_METHOD(dispatchNative, "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/Object;)V"),
};

/**
 * 初始化SFBridge
 * @return true 表示成功, false表示失败
 */
bool initJniBridgeNative(JavaVM *vm, JNIEnv *env) {

    if (!vm || !env) {
        LOGE(TAG, "Invalid Arguments");
        return false;
    }
    sJvm = vm;
    sJvmVersion = env->GetVersion();

    jclass clazz = env->FindClass(CLASS_NAME);
    if (!clazz) {
        LOGE(TAG, "class not found");
        return false;
    }

    jint ret = env->RegisterNatives(clazz, sMethods, NELEM(sMethods));
    if (ret != 0) {
        LOGE(TAG, "RegisterNatives failed");
        return false;
    }

    sDispatchCallbackMethodID = env->GetMethodID(clazz, "dispatchCallback", "(Ljava/lang/String;Ljava/lang/Object;)V");
    if (sDispatchCallbackMethodID == NULL) {
        LOGE(TAG, "GetMethodID dispatchCallback failed");
        return false;
    }

    sSubscribleMessageCallbackMethodID = env->GetMethodID(clazz, "subscribleMessageCallback", "(Ljava/lang/String;Ljava/lang/String;)V");
    if (sSubscribleMessageCallbackMethodID == NULL) {
        LOGE(TAG, "GetMethodID subscribleMessageCallback failed");
        return false;
    }

    return true;
}

