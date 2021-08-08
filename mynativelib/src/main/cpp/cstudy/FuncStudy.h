//
// Created by 陈晶晶 on 2021/8/8.
//

#ifndef MYJNISTUDYPROJECT_FUNCSTUDY_H
#define MYJNISTUDYPROJECT_FUNCSTUDY_H

/**
 * 函数参数的传递
 */
class FuncStudy {

public:
    int pub_value;
    FuncStudy();
    FuncStudy(const FuncStudy &funcStudy);  // 拷贝构造
    ~FuncStudy();

    // 等号运算符重载
    FuncStudy & operator = (const FuncStudy& funcStudy);

    static void testFunc();
};


#endif //MYJNISTUDYPROJECT_FUNCSTUDY_H
