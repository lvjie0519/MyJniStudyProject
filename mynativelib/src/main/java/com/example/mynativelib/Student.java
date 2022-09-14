package com.example.mynativelib;

public class Student {

    public String mName;
    public int mAge;

    public String getmName() {
        return mName;
    }

    public void setmName(String mName) {
        this.mName = mName;
    }

    public int getmAge() {
        return mAge;
    }

    public void setmAge(int mAge) {
        this.mAge = mAge;
    }

    @Override
    public String toString() {
        return "Student{" +
                "mName='" + mName + '\'' +
                ", mAge=" + mAge +
                '}';
    }

    private boolean launchApp(String packageName, int reason, String extraData) {
        return true;
    }

    public void setOnClickListener(OnClickListener listener){
        setOnClickListenerNative(listener);
    }

    public native void callJavaValue();

    public native void callJavaMethod();

    public native void setOnClickListenerNative(OnClickListener listener);
}
