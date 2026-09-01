#ifndef ANDROID_VERSIONING_H
#define ANDROID_VERSIONING_H

/*
 * Minimal stand-in for bionic's android/versioning.h.
 *
 * Under bionic this header comes from the toolchain (via sys/cdefs.h) and
 * provides API-level availability annotations. On glibc hosts the stub
 * headers have no toolchain-provided definition, so mirror what bionic
 * exposes: availability macros expand to nothing.
 *
 * In the NDK the real header defines __ANDROID_API_AVAILABLE_INTRODUCED_IN()
 * etc. in terms of clang availability attributes; none of that is needed for
 * stub builds.
 */

#ifndef __INTRODUCED_IN
#define __INTRODUCED_IN(__api_level) /* nothing */
#endif

#ifndef __DEPRECATED_IN
#define __DEPRECATED_IN(__api_level) /* nothing */
#endif

#ifndef __REMOVED_IN
#define __REMOVED_IN(__api_level) /* nothing */
#endif

#endif /* ANDROID_VERSIONING_H */
