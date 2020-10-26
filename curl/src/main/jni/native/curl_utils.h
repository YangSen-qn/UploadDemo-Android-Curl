//
// Created by yangsen on 2020/10/22.
//

#include <jni.h>
#include "curl_context.h"

#ifndef UPLOADDEMO_ANDROID_CURL_UTILS_H
#define UPLOADDEMO_ANDROID_CURL_UTILS_H

char * curlUtilStrToLower(char *str);

char * curlUtilStrStr(char * ps,char *pd);

void * curlUtilMemcpy(void * dest,const void *src,size_t count);

int curlUtilStrReplace(char *p_result,char* p_source,char* p_seach,char *p_repstr);

long curlUtilGetRequestContentLength(CurlContext *curlContext, jbyteArray body, jobjectArray header);

// 返回的char *需要delete
char* curlUtilConvertJByteArrayToChars(CurlContext *curlContext, jbyteArray byteArray);

#endif //UPLOADDEMO_ANDROID_CURL_UTILS_H
