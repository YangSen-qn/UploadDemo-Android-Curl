package com.qiniu.curl;


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

//        ClassLoader classLoader = Curl.class.getClassLoader();

        new Thread(new Runnable() {
            @Override
            public void run() {

                CurlHandler curlHandlerReal = new CurlHandler(curlHandler);
                requestNative(request, curlConfiguration, curlHandlerReal);
            }
        }).start();
    }

    public native void requestNative(final CurlRequest request,
                                     final CurlConfiguration curlConfiguration,
                                     final CurlHandler curlHandler);

    public void cancel(){
        isCancel = true;
    }

}
