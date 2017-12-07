#include <stdlib.h>
#include <stdio.h>
#include <jni.h>
#if 0
typedef struct{
    char *name; //java 里面调用打函数名
    char *signature;//JNI字段描述符
    void *fnPtr;//c语言本地函数
}JNINativeMethod;
#endif

jstring c_hello(JNIEnv* env,jobject cls,jstring str)
{
    const jbyte *cstr;
    cstr = (*env)->GetStringUTFChars(env,str,NULL);
    if(NULL == cstr)
    {
        return NULL;
    }
    printf("get from java:%s\r\n",cstr);
    (*env)->ReleaseStringUTFChars(env,str,cstr);
    return (*env)->NewStringUTF(env,"get from c");
}

jint  c_sum(JNIEnv * env, jobject cls , jintArray arr)
{
    int i;
    int *p_buf;
    int sum = 0;

    p_buf = (*env)->GetIntArrayElements(env,arr,NULL);
    if(p_buf == NULL)
    {
        return 0;
    }
    for(i=0;i<(*env)->GetArrayLength(env,arr);i++)
        sum+=p_buf[i];
    (*env)->ReleaseIntArrayElements(env,arr,p_buf,0);

    return sum;
}

static const JNINativeMethod methods[] = {
    {"hello","(Ljava/lang/String;)Ljava/lang/String;",(void *)c_hello},/*hello 为jni中用到打函数,c_hello为c函数*/
    {"sum","([I)I",(void *)c_sum},
};

JNIEXPORT jint JNICALL

JNI_OnLoad(JavaVM *jvm,void * reserved){
    JNIEnv *env;
    jclass cls;
    jint method_num;
    if((*jvm)->GetEnv(jvm, (void **)&env,JNI_VERSION_1_4))
        return JNI_ERR;

    cls = (*env)->FindClass(env,"JNIDemo");//查找类

    if(NULL == cls)
        return JNI_ERR;

    /*map java hello <-->c_hello*/
    method_num = sizeof(methods)/sizeof(JNINativeMethod);

    if((*env)->RegisterNatives(env, cls, methods,method_num) < 0){
        return JNI_ERR;
    }

    return JNI_VERSION_1_4;
}

