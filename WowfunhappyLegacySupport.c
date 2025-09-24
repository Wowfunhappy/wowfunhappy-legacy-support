//@build: make

#include <CoreFoundation/CoreFoundation.h>
#include <Security/Security.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

// For debugging. Use with `ASL_LOG("Hello world.");`
#define ASL_LOG(format, ...) asl_log(NULL, NULL, ASL_LEVEL_ERR, format, ##__VA_ARGS__)

//https://trac.macports.org/ticket/66749#comment:2
CFStringRef getStringForResultType(SecTrustResultType resultType) {
	switch (resultType) {
		case kSecTrustResultInvalid: return CFSTR("Error evaluating certificate");
		case kSecTrustResultDeny: return CFSTR("User specified to deny trust");
		case kSecTrustResultUnspecified: return CFSTR("Rejected Certificate");
		case kSecTrustResultRecoverableTrustFailure : return CFSTR("Rejected Certificate");
		case kSecTrustResultFatalTrustFailure :return CFSTR("Bad Certificate");
		case kSecTrustResultOtherError: return CFSTR("Error evaluating certificate");
		case kSecTrustResultProceed: return CFSTR("Proceed");
		default: return CFSTR("Unknown");
	}
}
bool SecTrustEvaluateWithError(SecTrustRef trust, CFErrorRef  *error) {
	SecTrustResultType trustResult = kSecTrustResultInvalid;
	OSStatus status = SecTrustEvaluate(trust, &trustResult);
	if (status == errSecSuccess && (trustResult == kSecTrustResultProceed || trustResult == kSecTrustResultUnspecified)) {
		if (error) {
			*error = NULL;
		}
		return true;
	}
	if (error)
		*error = CFErrorCreate(kCFAllocatorDefault, getStringForResultType(trustResult), 0, NULL);
	return false;
}

// Needed by the `rollup` npm package
int CCRandomGenerateBytes(void *bytes, size_t count) {
	if (bytes == NULL || count == 0) {
		return -4300;
	}
	arc4random_buf(bytes, count);
	return 0;
}

// Needed by wrangler 3+
bool notify_is_valid_token(int token) {
	errno = ENOSYS;
	return false;
}

// Needed by deno. Written by Claude 4.1 Opus.
void *aligned_alloc(size_t alignment, size_t size) {
	// Check that alignment is a power of two
	if (alignment == 0 || (alignment & (alignment - 1)) != 0) {
		errno = EINVAL;
		return NULL;
	}

	// Check that size is a multiple of alignment
	if (size % alignment != 0) {
		errno = EINVAL;
		return NULL;
	}

	void *ptr = NULL;
	// posix_memalign is available on older macOS versions
	int result = posix_memalign(&ptr, alignment, size);
	if (result != 0) {
		errno = result;
		return NULL;
	}

	return ptr;
}

// Stack probe function used by LLVM/Clang for stack overflow checking. Stubbed.
void ___chkstk_darwin(void) {
	return;
}

// QoS (Quality of Service) thread priority functions introduced in macOS 10.10+
// Stubbed because they're just optimization hints.
#include <pthread.h>
typedef unsigned int qos_class_t;
typedef struct pthread_override_s *pthread_override_t;
pthread_override_t pthread_override_qos_class_start_np(pthread_t thread, qos_class_t qos_class, int relative_priority) {
	static int dummy_override = 1;
	return (pthread_override_t)&dummy_override;
}
int pthread_override_qos_class_end_np(pthread_override_t override) {
	return 0;
}