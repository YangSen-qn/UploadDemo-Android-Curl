//
// Created by yangsen on 2020/10/26.
//

#include "curl_request.h"

jstring getJavaCurlRequestURL(CurlContext *curlContext, jobject curlRequest) {
    if (curlContext == NULL || curlRequest == NULL) {
        return NULL;
    }

    JNIEnv *env = curlContext->env;
    if (env == NULL) {
        return NULL;
    }

    jclass request_class = env->FindClass("com/qiniu/curl/CurlRequest");
    if (request_class == NULL) {
        return NULL;
    }

    jmethodID getUrlString_method = env->GetMethodID(request_class,
                                                     "getUrlString",
                                                     "()Ljava/lang/String;");
    if (getUrlString_method == NULL) {
        env->DeleteLocalRef(request_class);
        return NULL;
    }

    jstring url = (jstring) env->CallObjectMethod(curlRequest, getUrlString_method);

    env->DeleteLocalRef(request_class);

    return url;
}

int getJavaCurlRequestHttpMethod(CurlContext *curlContext, jobject curlRequest) {
    if (curlContext == NULL || curlRequest == NULL) {
        return Curl_Request_Http_Method_GET;
    }

    JNIEnv *env = curlContext->env;
    if (env == NULL) {
        return Curl_Request_Http_Method_GET;
    }

    jclass request_class = env->FindClass("com/qiniu/curl/CurlRequest");
    if (request_class == NULL) {
        return Curl_Request_Http_Method_GET;
    }

    jmethodID getHttpMethod_method = env->GetMethodID(request_class,
                                                      "getHttpMethod",
                                                      "()I");
    if (getHttpMethod_method == NULL) {
        env->DeleteLocalRef(request_class);
        return Curl_Request_Http_Method_GET;
    }

    int httpMethod = env->CallIntMethod(curlRequest, getHttpMethod_method);

    env->DeleteLocalRef(request_class);

    return httpMethod;
}

jobjectArray getJavaCurlRequestHeaderFields(CurlContext *curlContext, jobject curlRequest) {
    if (curlContext == NULL || curlRequest == NULL) {
        return NULL;
    }

    JNIEnv *env = curlContext->env;
    if (env == NULL) {
        return NULL;
    }

    jclass request_class = env->FindClass("com/qiniu/curl/CurlRequest");
    if (request_class == NULL) {
        return NULL;
    }

    jmethodID getAllHeaderList_method = env->GetMethodID(request_class,
                                                         "getAllHeaderList",
                                                         "()[Ljava/lang/String;");
    if (getAllHeaderList_method == NULL) {
        env->DeleteLocalRef(request_class);
        return NULL;
    }

    jobjectArray headerList = (jobjectArray) env->CallObjectMethod(curlRequest,
                                                                   getAllHeaderList_method);

    env->DeleteLocalRef(request_class);

    return headerList;
}

jbyteArray getJavaCurlRequestBody(CurlContext *curlContext, jobject curlRequest) {
    if (curlContext == NULL || curlRequest == NULL) {
        return NULL;
    }

    JNIEnv *env = curlContext->env;
    if (env == NULL) {
        return NULL;
    }

    jclass request_class = env->FindClass("com/qiniu/curl/CurlRequest");
    if (request_class == NULL) {
        return NULL;
    }

    jmethodID getHttpBody_method = env->GetMethodID(request_class,
                                                    "getHttpBody",
                                                    "()[B");
    if (getHttpBody_method == NULL) {
        env->DeleteLocalRef(request_class);
        return NULL;
    }

    jbyteArray body = (jbyteArray) env->CallObjectMethod(curlRequest, getHttpBody_method);

    env->DeleteLocalRef(request_class);

    return body;
}

int getJavaCurlRequestTimeout(CurlContext *curlContext, jobject curlRequest) {
    if (curlContext == NULL || curlRequest == NULL) {
        return 60;
    }

    JNIEnv *env = curlContext->env;
    if (env == NULL) {
        return 60;
    }

    jclass request_class = env->FindClass("com/qiniu/curl/CurlRequest");
    if (request_class == NULL) {
        return 60;
    }

    jmethodID getTimeout_method = env->GetMethodID(request_class,
                                                   "getTimeout",
                                                   "()I");
    if (getTimeout_method == NULL) {
        env->DeleteLocalRef(request_class);
        return 60;
    }

    int timeout = env->CallIntMethod(curlRequest, getTimeout_method);

    env->DeleteLocalRef(request_class);

    return timeout;
}
