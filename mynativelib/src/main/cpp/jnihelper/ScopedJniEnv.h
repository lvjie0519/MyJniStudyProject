
#ifndef LINESELECTORDEMO_SCOPEDJNIENV_H
#define LINESELECTORDEMO_SCOPEDJNIENV_H


#include <jni.h>
#include <stddef.h>

namespace jnihelper {

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

class ScopedJniEnv {
public:
	ScopedJniEnv(JavaVM& vm, jint version)
			: vm_(&vm), env_(NULL), attached_(false) {

		jint ret = vm_->GetEnv((void **) &env_, version);
		if (ret == JNI_OK) {
			return;
		} else if (ret != JNI_EDETACHED) {
			return;
		}

		ret = vm_->AttachCurrentThread(&env_, NULL);
		if (ret == JNI_OK) {
			attached_ = true;
		} else {
		}
	}

	~ScopedJniEnv() {
		if (attached_) {
			vm_->DetachCurrentThread();
		}
	}

	JNIEnv *getEnv() const {
		return env_;
	}

	bool valid() const {
		return env_ != NULL;
	}

private:
	JavaVM * const vm_;
	JNIEnv *env_;
	bool attached_;

	DISALLOW_COPY_AND_ASSIGN(ScopedJniEnv);
};

}

#endif //LINESELECTORDEMO_SCOPEDJNIENV_H
