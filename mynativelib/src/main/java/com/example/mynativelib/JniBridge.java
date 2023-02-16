package com.example.mynativelib;

import android.os.Handler;
import android.os.HandlerThread;
import android.util.Log;

public class JniBridge {
    private static final String TAG = "JniBridge";

    private boolean mInit = false;
    private final Object mLock = new Object();
    private HandlerThread mHandlerThread = null;
    private Handler mWorkHandler = null;

    public void init() {
        if (mInit) {
            return;
        }

        // 初始化WorkHandler
        initWorkHandler();
        mInit = true;
    }

    private void initWorkHandler() {
        mHandlerThread = new HandlerThread("dispathThread");
        mHandlerThread.start();
        mWorkHandler = new Handler(mHandlerThread.getLooper());
    }

    /**
     * 分发上层事件
     *
     * @param module   需要调用的模块
     * @param method   需要调用的功能
     * @param param    需要的参数
     * @param callback 调用回调
     */
    public void dispatch(String module, String method, String param, JniCallback callback) {

        synchronized (mLock) {
            try {
                mWorkHandler.post(new Runnable() {
                    @Override
                    public void run() {
                        Log.i(TAG, "Runnable called, method=" + method);
                        dispatchNative(module, method, param, callback);
                        Log.i(TAG, "Runnable called completed! method=" + method);
                        synchronized (mLock) {
                            try {
                                Log.i(TAG, "mLock notifyAll, method=" + method);
                                mLock.notifyAll();
                            } catch (Throwable e) {
                                Log.e(TAG, "synchronized lock notify failed! notifyAll error", e);
                            }
                        }
                    }
                });
                mLock.wait();
                Log.i(TAG, "mLock wait over, method=" + method);
            } catch (Throwable e) {
                Log.i(TAG, "synchronized lock wait failed! synchronized lock wait error", e);
            }
        }
    }

    /**
     * jni 层会调用该方法
     *
     * @param response
     * @param callback
     */
    private void dispatchCallback(String response, Object callback) {

        if (callback == null) {
            Log.e(TAG, "callback from C++ but it is empty! callback is null");
            return;
        }
        try {
            ((JniCallback) callback).invoke(response);
        } catch (Throwable e) {
            Log.e(TAG, "callback invoke failed! callback error", e);
        }
    }

    /**
     * c层传递过来的事件处理
     * jni 层会调用该方法
     *
     * @param topic
     * @param content
     */
    private void subscribleMessageCallback(String topic, String content) {
        Log.i(TAG, "will onMessageCallback, topic: " + topic);
    }

    private native void dispatchNative(String module, String method, String param, Object callback);
}
