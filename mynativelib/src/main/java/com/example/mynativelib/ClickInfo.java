package com.example.mynativelib;

public class ClickInfo {
    private int mCode;
    private String mMessage;

    public ClickInfo(){}

    public ClickInfo(int code, String message){
        this.mCode = code;
        this.mMessage = message;
    }

    @Override
    public String toString() {
        return "ClickInfo{" +
                "mCode=" + mCode +
                ", mMessage='" + mMessage + '\'' +
                '}';
    }
}
