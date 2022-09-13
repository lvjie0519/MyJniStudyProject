# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.
# 设置cmake构造本库需要的最低版本
cmake_minimum_required(VERSION 3.6.0)

# Declares and names the project.

project("mynativelib")

#打开cmake输出日志
set(CMAKE_VERBOSE_MAKEFILE on)

# 设置源码路径
set(CPP_SOURCE_SRC  ${CMAKE_CURRENT_SOURCE_DIR})
set(UTILS_SOURCE_SRC  ${CPP_SOURCE_SRC}/utils)
set(CSTUDY_SOURCE_SRC  ${CPP_SOURCE_SRC}/cstudy)

message("CPP_SOURCE_SRC:${CPP_SOURCE_SRC}")
message("UTILS_SOURCE_SRC:${UTILS_SOURCE_SRC}")

# DENABLE_DEMO01模块编译选项
MESSAGE(WARNING "ENABLE_DEMO01 =${DENABLE_DEMO01}")
message("ENABLE_DEMO01:${ENABLE_DEMO01}")
if (ENABLE_DEMO01)
    add_definitions(-DENABLE_DEMO01=1)
endif()

# DENABLE_DEMO02模块编译选项
#MESSAGE(WARNING "ENABLE_DEMO02 =${DENABLE_DEMO02}")
message("ENABLE_DEMO02:${ENABLE_DEMO02}")
if (ENABLE_DEMO02)
    add_definitions(-DENABLE_DEMO02=1)
endif()

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
# 创建并命名库，可以将库的类型设置为静态
# 或共享，并提供该库源代码的相对路径。
# 你可以定义多个library库，并使用CMake来构建。
# Gradle会自动打包库集成到apk中。
# STATIC 表示为静态库，linux下为.a文件；  SHARED为动态库，Linux下是.so文件
add_library( # Sets the name of the library.
             mynativelib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
            mynativelib.cpp
            StudentNative.cpp
        )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.
# NDK提供了一套实用的原生API和库，可以使用find_library搜索NDK中存在的库，只需要加入所需要使用库的名称即可，如下面的日志库log-lib。
# 更多的库可参考https://developer.android.com/ndk/guides/stable_apis
find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# include_directories(header-dir) 是一个全局包含，向下传递。
# 就是说如果某个目录的 CMakeLists.txt 中使用了该语句，其下所有的子目录默认也包含了header-dir 目录。
include_directories(${CPP_SOURCE_SRC})

add_subdirectory(${UTILS_SOURCE_SRC})
add_subdirectory(${CSTUDY_SOURCE_SRC})

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.
# 指定CMake连接到目标库中，可以链接多个库，如上面的native-lib库以及NDK中自带的log-lib库
target_link_libraries(
        # Specifies the target library.
       mynativelib

       # Links the target library to the log library
       # included in the NDK.
       ${log-lib}
        utils
        cstudy
)