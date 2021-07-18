package com.example.myjnistudyproject.firstjni;

import android.util.Log;

public class MyFirstJni {

    static {
        //此名字必须和build.gradle中的ndk下moduleName一致
        try {
            System.loadLibrary("MyFirstJinTest");
            Log.i("JNI", "MyFirstJinTest load success");
        } catch (Exception e) {
            Log.e("JNI", "MyFirstJinTest load error");
            e.printStackTrace();
        }
    }

    public static native String getString();
    public static native int add(int a, int b);

}
