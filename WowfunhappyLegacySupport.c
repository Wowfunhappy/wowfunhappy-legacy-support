#include <CoreFoundation/CoreFoundation.h>
#include <Security/Security.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

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