//cpg_CPPBridge: Exporting C++ API to the CPPBridge Java library
//(that will transmit processes to interface) via JNI formatted header that Java recognizes.
#include <jni.h>
#ifndef _Included_cpb_CPPBridge
#define _Included_cpb_CPPBridge
#ifdef __cplusplus
extern "C" {
#endif
	JNIEXPORT void JNICALL Java_cpb_CPPBridge_dataRetrieval(JNIEnv *, jobject, jstring dateStamp);
	JNIEXPORT void JNICALL Java_cpb_CPPBridge_encodeEvent(JNIEnv *, jobject, jint inputIndex, jstring inputTitle, jstring inputDescription);
	JNIEXPORT void JNICALL Java_cpb_CPPBridge_removeEvent(JNIEnv *env, jobject, jint inputIndex);
	JNIEXPORT jstring JNICALL Java_cpb_CPPBridge_currentDate(JNIEnv *);
	JNIEXPORT jstring JNICALL Java_cpb_CPPBridge_weekStartOffset(JNIEnv *env, jobject, jstring inputDay, jstring inputMonth);
	JNIEXPORT jstring JNICALL Java_cpb_CPPBridge_fabricateStamp(JNIEnv *, jobject, jint inputMonth, jint day);
	JNIEXPORT jstring JNICALL Java_cpb_CPPBridge_titles(JNIEnv *, jobject, jint index);
	JNIEXPORT jstring JNICALL Java_cpb_CPPBridge_descriptions(JNIEnv *, jobject, jint index);
#ifdef __cplusplus
}
#endif
#endif
