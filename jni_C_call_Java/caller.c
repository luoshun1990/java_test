#include <stdio.h>
#include <jni.h>
/**
*初始化jvm
 */
jint create_vm(JavaVM** jvm,JNIEnv** env){
         JavaVMInitArgs args;
         JavaVMOption options[1];
         args.version = JNI_VERSION_1_6;
         args.nOptions = 1;
         options[0].optionString = "-Djava.class.path=./";
         args.options = options;
         args.ignoreUnrecognized = JNI_FALSE;
         return JNI_CreateJavaVM(jvm, (void **)env, &args);
}

int main(int argc, int **argv){
    jclass cls;
    /*1 ,create java virtual machine*/
    JavaVM* jvm;
    JNIEnv* env;
    jmethodID mid;


    jmethodID mid1;
    jmethodID cid;
    jobject jobj;
    jstring jstr;

    jfieldID nameID;
    jfieldID ageID;
    jstring jstr1;
    int ret = 0;

/*-------------------------------------------------------------------*/
    /*创建java 虚拟机,获取环境变量env*/
    if(create_vm(&jvm,&env))
    {
        printf("can not create jvm\r\n");
        return -1;
    }
    /*2.get class,获取想要的类,hello为类名*/
    cls = (*env)->FindClass(env,"hello");
    if(cls == NULL)
    {
        printf("can not get class\r\n");
        ret  = -1;
         goto destroy;
    }
/*-------------------------------------------------------------------*/



/*--------------------------s-----------------------------------------*/
    /*3.create object*/
    /*3.1获取具体构造的对象,相当于创建一个对象*/
    cid = (*env)->GetMethodID(env,cls,"<init>","()V");
    if (NULL == cid)
    {
        printf("can not get constructor method id\r\n");
        ret = -1;
        goto destroy;
    }
    jobj = (*env)->NewObject(env, cls, cid);
    if (NULL == jobj)
    {
        printf("can not get jobj method id\r\n");
        ret = -1;
        goto destroy;
    }
/*----------------------e---------------------------------------------*/



/*----------------------------s---------------------------------------*/
    /*get/set field
    1,get id,获取变量ID
    2,set id,设置变量ID
    */
    /*注意：id 都是从CLS获取的，field才是从jobj设置*/
    nameID = (*env)->GetFieldID(env,cls,"name","Ljava/lang/String;");
    if (NULL == nameID)
    {
        printf("can not get name id\r\n");
        ret = -1;
        goto destroy;
    }
    jstr1 = (*env)->NewStringUTF(env,"bill");
    /*set*/
    (*env)->SetObjectField(env,jobj,nameID,jstr1);

    ageID = (*env)->GetFieldID(env,cls,"age","I");
    if(NULL == ageID)
    {
        printf("can not get AGE id\r\n");
        ret = -1;
        goto destroy;
    }
    /*set*/
    /*
    除了对象的设置用SetObjectField外，
    其他相应打变量设置用相应的即可：
    例如：int -> SetIntField
         char ->SetCharField
    */
    (*env)->SetIntField(env,jobj,ageID,10);
/*----------------------------e---------------------------------------*/




/*----------------------------s---------------------------------------*/
/*
1,先获取函数ID
2,按照ID调用
*/
    /*3.2 create parameters*/
    jstr = (*env)->NewStringUTF(env,"luoshun");

    /*3.3 new object*()*/
     mid1 = (*env)->GetMethodID(env,cls,"sayhello_to","(Ljava/lang/String;)I");
     if (NULL == mid1)
     {
         printf("can not get method id1\r\n");
         ret = -1;
         goto destroy;
     }

    /*4,call*/
    (*env)->CallIntMethod(env,jobj,mid1,jstr);
/*---------------------------------------e----------------------------*/


/*----------------------s---------------------------------------------*/
/*
1,先获取函数ID
2,按照ID访问
*/
    /*1 new object*(),*/
    mid = (*env)->GetStaticMethodID(env,cls,"main","([Ljava/lang/String;)V");/*static function*/

    if (NULL == mid)
    {
        printf("can not get method id\r\n");
        ret = -1;
        goto destroy;
    }


    /*2.call method*/
    (*env)->CallStaticVoidMethod(env,cls,mid,NULL);
/*--------------------e-----------------------------------------------*/

/*销毁*/
destroy:
    (*jvm)->DestroyJavaVM(jvm);
    return ret;
}