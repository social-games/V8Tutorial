#include <main.h>
#include <v8-version-string.h>
#include <libplatform/libplatform.h>

using namespace v8;

/**
 * Must stub in case external snapshot files are used.
 */
namespace v8 {
    namespace internal {
        void ReadNatives() {}

        void DisposeNatives() {}

        void SetNativesFromFile(v8::StartupData *s) {}

        void SetSnapshotFromFile(v8::StartupData *s) {}
    }
}

jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    LOGV("JNI OnLoad called");

    JNIEnv* env;
    if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }

    return JNI_VERSION_1_6;
}

void initializeV8() {
    // 666: leaking platform.
    Platform *platform = v8::platform::CreateDefaultPlatform();
    V8::InitializePlatform(platform);
    V8::Initialize();

    // from here, pending stuff is:
    // + create an isolate
    // + create main context
    // + create a context global object
    // etc.
}

extern "C" {
JNIEXPORT void JNICALL
Java_com_socialgames_v8tutorial_SocialGames_InitializeV8(JNIEnv *env, jobject obj) {

    initializeV8();

    JavaVM *vm;
    env->GetJavaVM(&vm);
    vm->AttachCurrentThread(&env, nullptr);

    // call com.socialgames.v8tutorial.SocialGames.setVersion( v8_version )
    // find java method com.socialgames.v8tutorial.SocialGames.setVersion
    jclass clazz = env->GetObjectClass(obj);
    jmethodID method = env->GetMethodID(clazz, "setVersion", "(Ljava/lang/String;)V");
    if (env->ExceptionCheck() == JNI_TRUE) {
        LOGV("JNI Exception detected");
        env->ExceptionDescribe();
        env->ExceptionClear();
    } else {
        // if found, call it.
        jstring jVersionStr = env->NewStringUTF(V8_VERSION_STRING);
        env->CallVoidMethod(obj, method, jVersionStr);
        env->DeleteLocalRef(jVersionStr);
    }
}

}

