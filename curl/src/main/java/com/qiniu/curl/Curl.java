package com.qiniu.curl;


import android.util.Log;

import java.util.ArrayList;
import java.util.Map;

public class Curl {

    private boolean isCancel = false;

    static {
        System.loadLibrary("qn-curl");
    }

    public boolean isCancel() {
        return isCancel;
    }

    public native long globalInit();

    public void request(final CurlRequest request,
                        final CurlConfiguration curlConfiguration,
                        final CurlHandlerI curlHandler){

        CurlThreadPool.run(new Runnable() {
            @Override
            public void run() {
                Log.d("==Curl request thread", Thread.currentThread().toString());
                CurlHandler curlHandlerReal = new CurlHandler(curlHandler);
                requestNative(request, curlConfiguration, curlHandlerReal);
            }
        });
    }

    public native void requestNative(final CurlRequest request,
                                     final CurlConfiguration curlConfiguration,
                                     final CurlHandler curlHandler);

    public void cancel(){
        isCancel = true;
    }

}
