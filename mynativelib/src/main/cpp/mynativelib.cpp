#include <jni.h>
#include <string>
#include <assert.h>
#include "utils/LogUtil.h"
#include "utils/StringUtil.h"
#include "cstudy/FuncStudy.h"
#include "StudentNative.h"

#define NATIVE_METHOD(name, signature) {#name, signature, (void *)NativeLib_##name}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_mynativelib_NativeLib_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

static jstring NativeLib_addStringNative(JNIEnv* env, jobject thiz, jstring str1, jstring str2){

    std::string result = StringUtil::string_j2c(env, str1)+StringUtil::string_j2c(env, str2);
    return env->NewStringUTF(result.c_str());
}

static void NativeLib_testCStudy(JNIEnv* env, jobject thiz, jstring str1){
    FuncStudy::testFunc();
}

// 注册方法的方式让java层与jni层建立对应关系
static const char *NativeLibClass = "com/example/mynativelib/NativeLib";
static JNINativeMethod methods[] = {
        {
                "addString",
                "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;",
                (void *)NativeLib_addStringNative
        },

        NATIVE_METHOD(testCStudy, "(Ljava/lang/String;)V"),
};

static int registerNativeMethods(JNIEnv* env, const char* className,
                                 JNINativeMethod* gMethods, int numMethods){
    jclass clazz;

    clazz = env->FindClass(className);
    if (clazz == NULL)
        return JNI_FALSE;
    if (env->RegisterNatives(clazz, gMethods, numMethods) < 0){
//        LOGE("register nativers error");
        return JNI_FALSE;
    }

    return JNI_TRUE;
}


static int registerNatives(JNIEnv *env) {

    if (!registerNativeMethods(env, NativeLibClass,methods,
                               sizeof(methods) / sizeof(methods[0]))) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

// java 层在调用 System.loadLibrary("mynativelib");   就会执行到这里
jint JNI_OnLoad(JavaVM* vm, void* reserved){
    JNIEnv* env = NULL;
    jint result = -1;

    LOGI("lvjie", "Entering JNI_OnLoad");
    if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
        goto bail;
    assert(env != NULL);

    if (!registerNatives(env))
        goto bail;

    if (!initStudentNative(vm, env))
        goto bail;

    /* success -- return valid version number */
    result = JNI_VERSION_1_4;

    bail:
//    LOGI("Leaving JNI_OnLoad (result=0x%x)\n", result);
    return result;
}