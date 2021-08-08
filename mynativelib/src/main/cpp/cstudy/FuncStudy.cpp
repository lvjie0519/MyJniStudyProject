//
// Created by 陈晶晶 on 2021/8/8.
//

#include "FuncStudy.h"
#include "utils/LogUtil.h"

#define TAG "FuncStudy"

FuncStudy::FuncStudy(){
    LOGI(TAG, "FuncStudy()...");
}

FuncStudy::FuncStudy(const FuncStudy &funcStudy){
    LOGI(TAG, "FuncStudy(const FuncStudy &funcStudy)...");
}

FuncStudy::~FuncStudy(){
    LOGI(TAG, "~FuncStudy()...");
}

FuncStudy & FuncStudy::operator = (const FuncStudy& funcStudy){
    LOGI(TAG, "operator =...");
}

/**
 *
 * @param funcStudy
 */
void test1(FuncStudy funcStudy){
    funcStudy.pub_value = 100;
}

void FuncStudy::testFunc() {
    FuncStudy funcStudy1;           // 调用无参构造
    funcStudy1.pub_value = 1;
    test1(funcStudy1);              // 会调用一次拷贝构造，test1 中修改的值并不会影响funcStudy1的数据
    LOGI(TAG, "testFunc pub_value: %d", funcStudy1.pub_value);  // testFunc pub_value: 1
}


