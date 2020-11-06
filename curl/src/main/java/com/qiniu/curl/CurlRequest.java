package com.qiniu.curl;

import android.util.Log;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class CurlRequest {

    private String urlString;
    private int httpMethod;
    private Map<String, String> allHeaders;
    private int timeout;
    private byte[] httpBody;

    public CurlRequest(String urlString,
                       int httpMethod,
                       Map<String, String> allHeaders,
                       byte[] httpBody,
                       int timeout) {

        this.urlString = urlString;
        this.httpMethod = httpMethod;
        this.allHeaders = (allHeaders != null) ? allHeaders : new HashMap<String, String>();
        this.httpBody = (httpBody != null) ? httpBody : new byte[0];
        this.timeout = timeout;
    }

    public String getUrlString() {
        return urlString;
    }

    public int getHttpMethod() {
        return httpMethod;
    }

    public Map<String, String> getAllHeaders() {
        return allHeaders;
    }

    public String[] getAllHeaderList() {
        String[] headerArray = new String[]{};
        if (allHeaders != null){
            ArrayList<String> headerList = new ArrayList<>();
            for (String headerKey : allHeaders.keySet()) {
                String headerValue = allHeaders.get(headerKey);
                String header = headerKey + ": " + headerValue;
                Log.d("== header:", "[" + header + ":" + headerValue + "]");
                headerList.add(header);
            }
            headerList.add("Expect: null");
            headerArray = headerList.toArray(new String[]{});

        }
        return headerArray;
    }

    public int getTimeout() {
        return timeout;
    }

    public byte[] getHttpBody() {
        return httpBody;
    }
}
