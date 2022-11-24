# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.
# 设置cmake构造本库需要的最低版本
cmake_minimum_required(VERSION 3.6.0)

# Declares and names the project.

project("cstudy")


add_library( # Sets the name of the library.
            cstudy

             # Sets the library as a shared library.
             STATIC

             # Provides a relative path to your source file(s).
             FuncStudy.cpp
             ThreadStudy.cpp
        )

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# 指定CMake连接到目标库中，可以链接多个库，如上面的native-lib库以及NDK中自带的log-lib库
target_link_libraries( # Specifies the target library.
        cstudy
        utils

       # Links the target library to the log library
       # included in the NDK.
       ${log-lib} )