/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class JNIDemo */

#ifndef _Included_JNIDemo
#define _Included_JNIDemo
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     JNIDemo
 * Method:    hello
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_JNIDemo_hello
  (JNIEnv *, jclass, jstring);

/*
 * Class:     JNIDemo
 * Method:    sum
 * Signature: ([I)I
 */
JNIEXPORT jint JNICALL Java_JNIDemo_sum
  (JNIEnv *, jclass, jintArray);

#ifdef __cplusplus
}
#endif
#endif
