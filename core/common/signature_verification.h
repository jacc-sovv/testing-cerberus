// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT license.

#ifndef SIGNATURE_VERIFICATION_H_
#define SIGNATURE_VERIFICATION_H_

#include <stdint.h>
#include <stddef.h>
#include "status/rot_status.h"


/**
 * Interface for executing signature verification.  Verification implementations may not be
 * thread-safe.
 */
struct signature_verification {
	/**
	 * Verify that a calculated digest matches a signature.
	 *
	 * @param verification The verification context to use for checking the signature.
	 * @param digest The digest to verify.
	 * @param digest_length The length of the digest.
	 * @param signature The signature to compare against the digest.
	 * @param sig_length The length of the signature.
	 *
	 * @return 0 if the digest matches the signature or an error code.
	 */
	int (*verify_signature) (struct signature_verification *verification, const uint8_t *digest,
		size_t length, const uint8_t *signature, size_t sig_length);
};


#define	SIG_VERIFICATION_ERROR(code)		ROT_ERROR (ROT_MODULE_SIG_VERIFICATION, code)

/**
 * Error codes that can be generated by an observer manager.
 */
enum {
	SIG_VERIFICATION_INVALID_ARGUMENT = SIG_VERIFICATION_ERROR (0x00),	/**< Input parameter is null or not valid. */
	SIG_VERIFICATION_NO_MEMORY = SIG_VERIFICATION_ERROR (0x01),			/**< Memory allocation failed. */
	SIG_VERIFICATION_VERIFY_SIG_FAILED = SIG_VERIFICATION_ERROR (0x02),	/**< There was a failure during signature verification. */
};


#endif /* SIGNATURE_VERIFICATION_H_ */