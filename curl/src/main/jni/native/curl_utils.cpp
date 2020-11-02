//
// Created by yangsen on 2020/10/22.
//

#include "curl_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char *curlUtilStrToLower(char *str) {
    if (str == NULL) {
        return str;
    }
    int i = 0;
    while (i < strlen(str)) {
        str[i] = static_cast<char>(tolower(str[i]));
        i++;
    }
    return str;
}

char *curlUtilStrStr(char *ps, char *pd) {
    char *pt = pd;
    int c = 0;
    while (*ps != '\0') {
        if (*ps == *pd) {
            while (*ps == *pd && *pd != '\0') {
                ps++;
                pd++;
                c++;
            }
        } else {
            ps++;
        }
        if (*pd == '\0') {
            return (ps - c);
        }
        c = 0;
        pd = pt;
    }
    return 0;
}

int curlUtilStrReplace(char *p_result, char *p_source, char *p_seach, char *p_repstr) {
    int c = 0;
    int repstr_leng = 0;
    int searchstr_leng = 0;

    char *p1;
    char *presult = p_result;
    char *psource = p_source;
    char *prep = p_repstr;
    char *pseach = p_seach;
    int nLen = 0;

    repstr_leng = strlen(prep);
    searchstr_leng = strlen(pseach);

    do {
        p1 = curlUtilStrStr(psource, p_seach);

        if (p1 == 0) {
            strcpy(presult, psource);
            return c;
        }
        c++;

        nLen = p1 - psource;
        memcpy(presult, psource, nLen);
        memcpy(presult + nLen, p_repstr, repstr_leng);

        psource = p1 + searchstr_leng;
        presult = presult + nLen + repstr_leng;
    } while (p1);

    return c;
}

long
curlUtilGetRequestContentLength(JNIEnv *env, jbyteArray body, jobjectArray header) {
    if (body != NULL) {
        return env->GetArrayLength(body);
    }

    if (header == NULL) {
        return 0;
    }

    char contentTypeKey[] = "content-length";
    char headerSegmentation[] = ":";
    long contentLength = 0;
    for (int i = 0; i < env->GetArrayLength(header); ++i) {
        jstring headerField = (jstring) env->GetObjectArrayElement(header, i);
        jboolean isHeaderFieldCopy;
        const char *headerFieldChar = env->GetStringUTFChars(headerField, &isHeaderFieldCopy);
        if (strlen(headerFieldChar) < 30) {
            headerFieldChar = curlUtilStrToLower(const_cast<char *>(headerFieldChar));
        } else {
            continue;
        }

        if (strstr(headerFieldChar, contentTypeKey) != NULL &&
            strstr(headerFieldChar, headerSegmentation) != NULL) {

            char spaceChar[] = " ";
            char emptyChar[] = "";

            char *contentLengthSource = const_cast<char *>(headerFieldChar);
            char contentLengthChar0[30] = {0};
            curlUtilStrReplace(contentLengthChar0, contentLengthSource, spaceChar, emptyChar);

            contentLengthSource = contentLengthChar0;
            char contentLengthChar1[30] = {0};
            curlUtilStrReplace(contentLengthChar1, contentLengthSource, contentTypeKey, emptyChar);

            contentLengthSource = contentLengthChar1;
            char contentLengthChar2[30] = {0};
            curlUtilStrReplace(contentLengthChar2, contentLengthSource, headerSegmentation,
                               emptyChar);

            contentLength = atol(contentLengthChar2);
        }

        env->ReleaseStringUTFChars(headerField, headerFieldChar);
    }
    return contentLength;
}

// 返回的char *需要delete
char* curlUtilConvertJByteArrayToChars(JNIEnv *env, jbyteArray byteArray) {
    if (env == NULL) {
        return 0;
    }

    char *chars = NULL;
    jbyte *bytes = env->GetByteArrayElements(byteArray, 0);

    int chars_len = env->GetArrayLength(byteArray);
    chars = new char[chars_len + 1];
    memset(chars, 0, static_cast<size_t>(chars_len + 1));
    memcpy(chars, bytes, static_cast<size_t>(chars_len));
    chars[chars_len] = 0;

    env->ReleaseByteArrayElements(byteArray, bytes, 0);

    return chars;
}

int transformCurlStatusCode(int statusCode){

    int statusCodeRet = statusCode;
    switch (statusCode){
        case CURLE_OK: // 0
            // All fine. Proceed as usual.
            break;
        case CURLE_UNSUPPORTED_PROTOCOL: // 1
            // The URL you passed to libcurl used a protocol that this libcurl does not support.
            // The support might be a compile-time option that you didn't use, it can be a
            // misspelled protocol string or just a protocol libcurl has no code for.
            statusCodeRet = 0;
            break;
        case CURLE_FAILED_INIT: // 2
            // Very early initialization code failed. This is likely to be an internal error or
            // problem, or a resource problem where something fundamental couldn't get done at init
            // time.
            break;
        case CURLE_URL_MALFORMAT: // 3
            // The URL was not properly formatted.
            break;
        case CURLE_NOT_BUILT_IN: // 4
            // A requested feature, protocol or option was not found built-in in this libcurl due
            // to a build-time decision. This means that a feature or option was not enabled or
            // explicitly disabled when libcurl was built and in order to get it to function you
            // have to get a rebuilt libcurl.
            break;
        case CURLE_COULDNT_RESOLVE_PROXY: // 5
            // Couldn't resolve proxy. The given proxy host could not be resolved.
            break;
        case CURLE_COULDNT_RESOLVE_HOST: // 6
            // Couldn't resolve host. The given remote host was not resolved.
            break;
        case CURLE_COULDNT_CONNECT: // 7
            //
            break;
        case CURLE_WEIRD_SERVER_REPLY: // 8
            //
            break;
        case CURLE_REMOTE_ACCESS_DENIED: // 9
            //
            break;
        case CURLE_FTP_ACCEPT_FAILED: //
            //
            break;
        case CURLE_FTP_WEIRD_PASS_REPLY: //
            //
            break;
        case CURLE_FTP_ACCEPT_TIMEOUT: //
            //
            break;
        case CURLE_FTP_WEIRD_PASV_REPLY: //
            //
            break;
        case CURLE_FTP_WEIRD_227_FORMAT: //
            //
            break;
        case CURLE_FTP_CANT_GET_HOST: //
            //
            break;
        case CURLE_HTTP2: //
            //
            break;
        case CURLE_FTP_COULDNT_SET_TYPE: //
            //
            break;
        case CURLE_PARTIAL_FILE: //
            //
            break;
        case CURLE_FTP_COULDNT_RETR_FILE: //
            //
            break;
        case CURLE_QUOTE_ERROR: //
            //
            break;
        case CURLE_HTTP_RETURNED_ERROR: //
            //
            break;
        case CURLE_WRITE_ERROR: //
            //
            break;
        case CURLE_UPLOAD_FAILED: //
            //
            break;
        case CURLE_READ_ERROR: //
            //
            break;
        case CURLE_OUT_OF_MEMORY: //
            //
            break;
        case CURLE_OPERATION_TIMEDOUT: //
            //
            break;
        case CURLE_FTP_PORT_FAILED: //
            //
            break;
        case CURLE_FTP_COULDNT_USE_REST: //
            //
            break;
        case CURLE_RANGE_ERROR: //
            //
            break;
        case CURLE_HTTP_POST_ERROR: //
            //
            break;
        case CURLE_SSL_CONNECT_ERROR: //
            //
            break;
        case CURLE_BAD_DOWNLOAD_RESUME: //
            //
            break;
        case CURLE_FILE_COULDNT_READ_FILE: //
            //
            break;
        case CURLE_LDAP_CANNOT_BIND: //
            //
            break;
        case CURLE_LDAP_SEARCH_FAILED: //
            //
            break;
        case CURLE_FUNCTION_NOT_FOUND: //
            //
            break;
        case CURLE_ABORTED_BY_CALLBACK: //
            //
            break;
        case CURLE_BAD_FUNCTION_ARGUMENT: //
            //
            break;
        case CURLE_INTERFACE_FAILED: //
            //
            break;
        case CURLE_TOO_MANY_REDIRECTS: //
            //
            break;
        case CURLE_UNKNOWN_OPTION: //
            //
            break;
        case CURLE_TELNET_OPTION_SYNTAX: //
            //
            break;
        case CURLE_GOT_NOTHING: //
            //
            break;
        case CURLE_SSL_ENGINE_NOTFOUND: //
            //
            break;
        case CURLE_SSL_ENGINE_SETFAILED: //
            //
            break;
        case CURLE_SEND_ERROR: //
            //
            break;
        case CURLE_RECV_ERROR: //
            //
            break;
        case CURLE_SSL_CERTPROBLEM: //
            //
            break;
        case CURLE_SSL_CIPHER: //
            //
            break;
        case CURLE_PEER_FAILED_VERIFICATION: //
            //
            break;
        case CURLE_BAD_CONTENT_ENCODING: //
            //
            break;
        case CURLE_LDAP_INVALID_URL: //
            //
            break;
        case CURLE_FILESIZE_EXCEEDED: //
            //
            break;
        case CURLE_USE_SSL_FAILED: //
            //
            break;
        case CURLE_SEND_FAIL_REWIND: //
            //
            break;
        case CURLE_SSL_ENGINE_INITFAILED: //
            //
            break;
        case CURLE_LOGIN_DENIED: //
            //
            break;
        case CURLE_TFTP_NOTFOUND: //
            //
            break;
        case CURLE_TFTP_PERM: //
            //
            break;
        case CURLE_REMOTE_DISK_FULL: //
            //
            break;
        case CURLE_TFTP_ILLEGAL: //
            //
            break;
        case CURLE_TFTP_UNKNOWNID: //
            //
            break;
        case CURLE_REMOTE_FILE_EXISTS: //
            //
            break;
        case CURLE_TFTP_NOSUCHUSER: //
            //
            break;
        case CURLE_CONV_FAILED: //
            //
            break;
        case CURLE_CONV_REQD: //
            //
            break;
        case CURLE_SSL_CACERT_BADFILE: //
            //
            break;
        case CURLE_REMOTE_FILE_NOT_FOUND: //
            //
            break;
        case CURLE_SSH: //
            //
            break;
        case CURLE_SSL_SHUTDOWN_FAILED: //
            //
            break;
        case CURLE_AGAIN: //
            //
            break;
        case CURLE_SSL_CRL_BADFILE: //
            //
            break;
        case CURLE_SSL_ISSUER_ERROR: //
            //
            break;
        case CURLE_FTP_PRET_FAILED: //
            //
            break;
        case CURLE_RTSP_CSEQ_ERROR: //
            //
            break;
        case CURLE_RTSP_SESSION_ERROR: //
            //
            break;
        case CURLE_FTP_BAD_FILE_LIST: //
            //
            break;
        case CURLE_CHUNK_FAILED: //
            //
            break;
        case CURLE_NO_CONNECTION_AVAILABLE: //
            //
            break;
        case CURLE_SSL_PINNEDPUBKEYNOTMATCH: //
            //
            break;
        case CURLE_SSL_INVALIDCERTSTATUS: //
            //
            break;
        case CURLE_HTTP2_STREAM: //
            //
            break;
        case CURLE_RECURSIVE_API_CALL: //
            //
            break;
        case CURLE_AUTH_ERROR: //
            //
            break;
        case CURLE_HTTP3: //
            //
            break;
//        case CURLE_QUIC_CONNECT_ERROR:
//            break;
        default:
            break;
    }
    return statusCodeRet;
}