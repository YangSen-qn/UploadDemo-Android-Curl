package com.qiniu.curl;


import android.annotation.SuppressLint;

import java.util.ArrayList;

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


    public static class DnsResolver {
        protected final String host;
        protected final String ip;
        protected final int port;

        public DnsResolver(String host, String ip, int port){
            this.host = host;
            this.ip = ip;
            this.port = port;
        }

        @SuppressLint("DefaultLocale")
        public String toString(){
            return String.format("%s:%d:%s", this.host, this.port, this.ip);
        }
    }

    public static class Builder{

        protected String[] dnsResolverArray;
        protected String proxy;
        protected String proxyUserPwd;
        protected String caPath;

        public Builder(){
            if (defaultCAPath == null) {
                defaultCAPath = CurlUtils.getCAPath();
            }
            caPath = defaultCAPath;
        }

        public Builder setDnsResolverArray(DnsResolver[] dnsResolverArray) {
            if (dnsResolverArray == null || dnsResolverArray.length == 0){
                return this;
            }
            ArrayList<String> dnsResolverList = new ArrayList<>();
            for (DnsResolver resolver : dnsResolverArray){
                dnsResolverList.add(resolver.toString());
            }
            this.dnsResolverArray = dnsResolverList.toArray(new String[0]);
            return this;
        }

        public Builder setProxy(String proxy) {
            this.proxy = proxy;
            return this;
        }

        public Builder setProxyUserPwd(String proxyUserPwd) {
            this.proxyUserPwd = proxyUserPwd;
            return this;
        }

        public Builder setCaPath(String caPath) {
            this.caPath = caPath;
            return this;
        }

        public CurlConfiguration build(){
            return new CurlConfiguration(this);
        }
    }
}
