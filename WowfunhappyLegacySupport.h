#ifndef WOWFUNHAPPY_LEGACY_SUPPORT_H
#define WOWFUNHAPPY_LEGACY_SUPPORT_H

#include <CoreFoundation/CoreFoundation.h>
#include <Security/Security.h>
#include <stdbool.h>

bool SecTrustEvaluateWithError(SecTrustRef trust, CFErrorRef *error);

int CCRandomGenerateBytes(void *bytes, size_t count);

#endif