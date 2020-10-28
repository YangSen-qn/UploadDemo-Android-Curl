//
// Created by yangsen on 2020/10/26.
//
#include <jni.h>
#include "curl_context.h"

#ifndef UPLOADDEMO_ANDROID_CURL_REQUEST_H
#define UPLOADDEMO_ANDROID_CURL_REQUEST_H

#define Curl_Request_Http_Method_GET 1
#define Curl_Request_Http_Method_POST 2
#define Curl_Request_Http_Method_PUT 3
#define Curl_Request_Http_Method_DELETE 4

void setCurlContextWithRequest(JNIEnv *env, CurlContext *curlContext, jobject curlRequest);

#endif //UPLOADDEMO_ANDROID_CURL_REQUEST_H
