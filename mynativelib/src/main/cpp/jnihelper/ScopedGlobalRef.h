
#ifndef LINESELECTORDEMO_SCOPEDGLOBALREFF_H
#define LINESELECTORDEMO_SCOPEDGLOBALREFF_H

#include <jni.h>
#include <stddef.h>
#include "ScopedJniEnv.h"

namespace jnihelper {
// A smart pointer that deletes a JNI local reference when it goes out of scope.
template<typename T>
class ScopedGlobalRef {
public:
	ScopedGlobalRef(JavaVM &vm, JNIEnv &env, T localRef) : mJvm(&vm) {
		mJvmVersion = env.GetVersion();
        if (localRef) {
            mGlobalRef = reinterpret_cast<T>(env.NewGlobalRef(localRef));
        } else {
            mGlobalRef = localRef;
        }
		if (mGlobalRef == nullptr) {
		}
	}

	virtual ~ScopedGlobalRef() {
		reset();
	}

	void reset(T ptr = nullptr) {
		if (ptr == mGlobalRef) {
			return;
		}

        ScopedJniEnv env(*mJvm, mJvmVersion);
        if (!env.valid()) {
            return;
        }

		if (mGlobalRef != nullptr) {
            env.getEnv()->DeleteGlobalRef(mGlobalRef);
			mGlobalRef = nullptr;
		}
        if (ptr != nullptr) {
            mGlobalRef = reinterpret_cast<T>(env.getEnv()->NewGlobalRef(ptr));
        }
	}

	bool valid() {
		return get() != nullptr;
	}

	T get() const {
		return mGlobalRef;
	}

private:
    JavaVM *const mJvm;
    int mJvmVersion = 0;
	T mGlobalRef;

	DISALLOW_COPY_AND_ASSIGN(ScopedGlobalRef);
};

}

#endif //LINESELECTORDEMO_SCOPEDGLOBALREF_H
