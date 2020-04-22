// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT license.

#ifndef AUX_ATTESTATION_H_
#define AUX_ATTESTATION_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "status/rot_status.h"
#include "keystore/keystore.h"
#include "crypto/rsa.h"
#include "crypto/ecc.h"
#include "crypto/hash.h"
#include "crypto/x509.h"
#include "crypto/rng.h"
#include "common/certificate.h"
#include "attestation/pcr_store.h"
#include "riot/riot_key_manager.h"
#include "cmd_interface/cerberus_protocol_optional_commands.h"


/**
 * The types of seeds that can be used for attestation unsealing.
 */
enum aux_attestation_seed_type {
	AUX_ATTESTATION_SEED_RSA = CERBERUS_PROTOCOL_UNSEAL_SEED_RSA,	/**< Attestation seed is RSA encrypted. */
	AUX_ATTESTATION_SEED_ECDH = CERBERUS_PROTOCOL_UNSEAL_SEED_ECDH	/**< Attestation seed is an ECC public key. */
};

/**
 * The padding types possible for the encrypted seed.
 */
enum aux_attestation_seed_padding {
	AUX_ATTESTATION_PADDING_PKCS15 = CERBERUS_PROTOCOL_UNSEAL_RSA_PKCS15,			/**< Attestation seed is padded per PKCS#1 v1.5. */
	AUX_ATTESTATION_PADDING_OAEP_SHA1 = CERBERUS_PROTOCOL_UNSEAL_RSA_OAEP_SHA1,		/**< Attestation seed is OAEP padded with SHA1. */
	AUX_ATTESTATION_PADDING_OAEP_SHA256 = CERBERUS_PROTOCOL_UNSEAL_RSA_OAEP_SHA256,	/**< Attestation seed is OAEP padded with SHA256. */
	AUX_ATTESTATION_PADDING_UNSPECIFIED = 0xff										/**< Seed uses an unspecified padding scheme. */
};

/**
 * Supported encryption and signing key lengths that can be generated.
 */
enum aux_attestation_key_length {
	AUX_ATTESTATION_KEY_256BIT = SHA256_HASH_LENGTH		/**< Generate 256-bit signing and encryption keys. */
};

/**
 * Handler for providing an auxiliary method of attestation.
 */
struct aux_attestation {
	struct keystore *keystore;		/**< Storage for the attestation private key. */
	struct rsa_engine *rsa;			/**< Interface for RSA operations with the private key. */
	struct riot_key_manager *riot;	/**< Storage for the ECC attestation key. */
	struct ecc_engine *ecc;			/**< Interface for ECC unsealing operations. */
	struct der_cert cert;			/**< The certificate for the attestation private key. */
	bool is_static;					/**< Flag indicating if the certificate is in static memory. */
};


int aux_attestation_init (struct aux_attestation *aux, struct keystore *keystore,
	struct rsa_engine *rsa, struct riot_key_manager *riot, struct ecc_engine *ecc);
void aux_attestation_release (struct aux_attestation *aux);

int aux_attestation_generate_key (struct aux_attestation *aux);
int aux_attestation_erase_key (struct aux_attestation *aux);

int aux_attestation_create_certificate (struct aux_attestation *aux, struct x509_engine *x509,
	struct rng_engine *rng, const uint8_t *ca, size_t ca_length, const uint8_t *ca_key,
	size_t key_length);
int aux_attestation_set_certificate (struct aux_attestation *aux, uint8_t *cert, size_t length);
int aux_attestation_set_static_certificate (struct aux_attestation *aux, const uint8_t *cert,
	size_t length);
const struct der_cert* aux_attestation_get_certificate (struct aux_attestation *aux);

int aux_attestation_unseal (struct aux_attestation *aux, struct hash_engine *hash,
	struct pcr_store *pcr, enum aux_attestation_key_length key_type, const uint8_t *seed,
	size_t seed_length, enum aux_attestation_seed_type seed_type,
	enum aux_attestation_seed_padding padding, const uint8_t *hmac, enum hmac_hash hmac_type,
	const uint8_t *ciphertext, size_t cipher_length, const uint8_t sealing[][64], size_t pcr_count,
	uint8_t *key, size_t key_length);

int aux_attestation_decrypt (struct aux_attestation *aux, const uint8_t *encrypted,
	size_t len_encrypted, const uint8_t *label, size_t len_label, enum hash_type pad_hash,
	uint8_t *decrypted, size_t len_decrypted);


#define	AUX_ATTESTATION_ERROR(code)		ROT_ERROR (ROT_MODULE_AUX_ATTESTATION, code)

/**
 * Error codes that can be generated by an auxiliary attestation handler.
 */
enum {
	AUX_ATTESTATION_INVALID_ARGUMENT = AUX_ATTESTATION_ERROR (0x00),		/**< Input parameter is null or not valid. */
	AUX_ATTESTATION_NO_MEMORY = AUX_ATTESTATION_ERROR (0x01),				/**< Memory allocation failed. */
	AUX_ATTESTATION_HAS_CERTIFICATE = AUX_ATTESTATION_ERROR (0x02),			/**< A certificate has already been provisioned. */
	AUX_ATTESTATION_PCR_MISMATCH = AUX_ATTESTATION_ERROR (0x03),			/**< The sealing policy doesn't match the local PCRs. */
	AUX_ATTESTATION_HMAC_MISMATCH = AUX_ATTESTATION_ERROR (0x04),			/**< The payload failed verification against the HMAC. */
	AUX_ATTESTATION_UNSUPPORTED_CRYPTO = AUX_ATTESTATION_ERROR (0x05),		/**< The asymmetric crypto algorithm is not supported. */
	AUX_ATTESTATION_UNSUPPORTED_KEY_LENGTH = AUX_ATTESTATION_ERROR (0x06),	/**< The requested key length is not supported. */
	AUX_ATTESTATION_UNSUPPORTED_HMAC = AUX_ATTESTATION_ERROR (0x07),		/**< The HMAC algorithm is not supported. */
	AUX_ATTESTATION_UNKNOWN_SEED = AUX_ATTESTATION_ERROR (0x08),			/**< Unknown seed algorithm. */
	AUX_ATTESTATION_BUFFER_TOO_SMALL = AUX_ATTESTATION_ERROR (0x09),		/**< Output buffer too small. */
	AUX_ATTESTATION_BAD_SEED_PADDING = AUX_ATTESTATION_ERROR (0x0a),		/**< Seed padding type is invalid or unsupported. */
};


#endif /* AUX_ATTESTATION_H_ */
