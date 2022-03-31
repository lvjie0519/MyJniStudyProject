package com.example.myjnistudyproject;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import com.example.mynativelib.NativeLib;
import com.example.mynativelib.Student;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = "MainActivity";
    private TextView mTvShowInfo;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        initView();
    }

    private void initView(){
        mTvShowInfo = findViewById(R.id.tv_show_info);
    }

    public void onClickLoadSoFile(View view) {
        NativeLib.loadSoFile();
    }

    public void onClickJniFuncTest(View view) {
        NativeLib nativeLib = new NativeLib();
        String result = nativeLib.stringFromJNI();
        result = result+"  "+nativeLib.addString("1", "2");

        this.mTvShowInfo.setText(result);

    }

    public void onClickCStudy(View view) {
//        NativeLib nativeLib = new NativeLib();
//        nativeLib.testCStudy("");

        testStudent();
    }

    private void testStudent() {
        Student student = new Student();
        student.mAge = 10;
        student.setmName("lvjie");
        Log.i(TAG, student.toString());

        student.callJavaValue();
        Log.i(TAG, student.toString());

        Log.i(TAG, "will callJavaMethod");
        student.callJavaMethod();
    }
}