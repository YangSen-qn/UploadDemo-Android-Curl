package com.qiniu.curl;

import android.content.Context;
import android.util.Log;
import java.io.IOException;

import java.io.InputStream;


public class CurlConfiguration {

    private static String defaultCAPath;

    private String[] dnsResolverArray;
    private String proxy;
    private String proxyUserPwd;
    private String caPath;

    public String[] getDnsResolverArray() {
        return dnsResolverArray;
    }

    public String getProxy() {
        return proxy;
    }

    public String getProxyUserPwd() {
        return proxyUserPwd;
    }

    public String getCAPath() {
        return caPath;
    }

    public CurlConfiguration(Builder builder) {
        this.dnsResolverArray = builder.dnsResolverArray;
        this.proxy = builder.proxy;
        this.proxyUserPwd = builder.proxyUserPwd;
        this.caPath = builder.caPath;
    }

    public static class Builder{
        public String[] dnsResolverArray;
        public String proxy;
        public String proxyUserPwd;
        private String caPath;

        public Builder(){
            if (defaultCAPath == null) {
                defaultCAPath = CurlUtils.getCAPath();
            }
            caPath = defaultCAPath;
        }



        public CurlConfiguration build(){
            return new CurlConfiguration(this);
        }
    }
}
