package com.example.myjnistudyproject;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import com.example.mynativelib.NativeLib;

public class MainActivity extends AppCompatActivity {

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
}