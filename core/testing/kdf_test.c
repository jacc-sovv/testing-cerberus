// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT license.

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "platform.h"
#include "testing.h"
#include "engines/hash_testing_engine.h"
#include "mock/hash_mock.h"
#include "crypto/kdf.h"


static const char *SUITE = "kdf";


static const uint8_t kdo_sha1[] = {
	0x06,0x3b,0x74,0x13,0x1d,0xf3,0xf9,0xb2,0xf7,0x25,0x4e,0xab,0xae,0xd3,0xc4,0x9b,
	0x20,0xf5,0x22,0x61
};

static const uint8_t kdo_sha256_32[] = {
	0xe6,0x48,0xd4,0xc7,0x0d,0xc1,0x59,0x75,0xa1,0x4b,0x0a,0x91,0x75,0xd9,0x17,0x10,
	0x21,0x75,0xbc,0x9a,0x92,0x6f,0x6d,0x24,0x93,0xda,0xf3,0x98,0x11,0xc3,0x97,0xf8
};

static const uint8_t kdo_sha256_64[] = {
	0x42,0xa1,0xd9,0x7c,0x1b,0xb4,0x83,0x78,0xc1,0xa9,0xb9,0xb0,0xc6,0x13,0xfc,0x5d,
	0xa4,0xab,0x5c,0x9e,0x69,0xe2,0xc8,0xfd,0x72,0xa3,0x32,0x8f,0xb9,0x20,0xf9,0x0a,
	0x76,0x4d,0xa3,0xb8,0x4c,0xa1,0x77,0x03,0xad,0xbc,0xa0,0x57,0x05,0xb0,0xb1,0x61,
	0x9f,0x7b,0x97,0xc7,0x33,0xd6,0xfa,0xe1,0xf1,0x8a,0xc5,0xdc,0x64,0x79,0xdc,0x5a
};

static const uint8_t kdo_sha256_96[] = {
	0x63,0x8e,0x99,0x88,0x0c,0xe0,0x2f,0x4c,0xde,0xc2,0xb5,0xac,0x39,0x81,0x17,0xc7,
	0x0c,0x97,0x9c,0x97,0xee,0x69,0xe5,0xda,0x00,0x5e,0x6c,0x2c,0x02,0x26,0x79,0x3a,
	0xc8,0x99,0x1c,0x1a,0x2f,0xa7,0x5e,0x8c,0x08,0x2f,0xf5,0x88,0x7e,0xc3,0xea,0xea,
	0x39,0x8c,0xd0,0xa0,0x83,0xcc,0xf4,0x59,0x0a,0x72,0xb3,0x34,0xf6,0x69,0x3c,0x90,
	0x6b,0x3e,0x31,0x5f,0x68,0x22,0x3b,0x9e,0x59,0x3a,0xee,0xb6,0x82,0x5f,0xb4,0x6d,
	0x2e,0x3d,0x3d,0x99,0x84,0x86,0xcc,0xee,0x93,0x35,0x97,0x4a,0x0a,0x1a,0x65,0x20
};

static const uint8_t kdo_sha256_50[] = {
	0x0d,0xec,0xbe,0xd2,0x23,0x8f,0x09,0x54,0xb9,0x2c,0xe6,0xff,0x44,0x48,0xd9,0x08,
	0xa4,0x52,0x96,0x19,0x30,0x63,0x80,0x15,0x0d,0x5a,0xfe,0x42,0xd4,0x93,0xee,0xe9,
	0x27,0x4a,0x75,0xae,0x2b,0x07,0x88,0x28,0x9a,0x91,0xb1,0xbc,0x05,0x0e,0x18,0xd4,
	0x5b,0x00
};


static void kdf_test_nist800_108_counter_mode_sha1 (CuTest *test)
{
	HASH_TESTING_ENGINE hash;
	uint8_t ki[] = {
		0xf1,0x3b,0x43,0x16,0x2c,0xe4,0x02,0x34,0xd6,0x41,0x80,0xfa,0x1a,0x0e,0x0a,0x04,
		0x0e,0x9a,0x37,0xff,0x3e,0xa0,0x05,0x75,0x73,0xc5,0x54,0x10,0xad,0xd5,0xc5,0xc6
	};
	uint8_t label[] = {
		0x0e,0x9a,0x37,0xff,0x3e,0xa0,0x02,0x75,0x73,0xc5,0x54,0x10,0xad,0xd5,0xc5,0xc6,
		0xf1,0x3b,0x43,0x16,0x2c,0xe4,0x05,0x34,0xd6,0x41,0x80,0xfa,0x1a,0x0e,0x0a,0x04
	};
	uint8_t context[] = {
		0xf1,0x3b,0x43,0x16,0x2c,0x0e,0x9a,0x37,0xe4,0x05,0x75,0x73,0xc5,0x54,0x10,0xad,
		0xff,0x3e,0xa0,0x02,0x34,0xd6,0x41,0x80,0xfa,0x1a,0x0e,0x0a,0x04,0xd5,0xc5,0xc6
	};
	uint8_t ko[SHA1_HASH_LENGTH];
	int status;

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&hash);
	CuAssertIntEquals (test, 0, status);

	status = kdf_nist800_108_counter_mode (&hash.base, HMAC_SHA1, ki, sizeof (ki), label,
		sizeof (label), context, sizeof (context), ko, sizeof (ko));
	CuAssertIntEquals (test, 0, status);

	status = testing_validate_array (kdo_sha1, ko, sizeof (kdo_sha1));
	CuAssertIntEquals (test, 0, status);

	HASH_TESTING_ENGINE_RELEASE (&hash);
}

static void kdf_test_nist800_108_counter_mode_sha256 (CuTest *test)
{
	HASH_TESTING_ENGINE hash;
	uint8_t ki[] = {
		0xf1,0x3b,0x43,0x16,0x2c,0xe4,0x02,0x34,0xd6,0x41,0x80,0xfa,0x1a,0x0e,0x0a,0x04,
		0x0e,0x9a,0x37,0xff,0x3e,0xa0,0x05,0x75,0x73,0xc5,0x54,0x10,0xad,0xd5,0xc5,0xc6
	};
	uint8_t label[] = {
		0x0e,0x9a,0x37,0xff,0x3e,0xa0,0x02,0x75,0x73,0xc5,0x54,0x10,0xad,0xd5,0xc5,0xc6,
		0xf1,0x3b,0x43,0x16,0x2c,0xe4,0x05,0x34,0xd6,0x41,0x80,0xfa,0x1a,0x0e,0x0a,0x04
	};
	uint8_t context[] = {
		0xf1,0x3b,0x43,0x16,0x2c,0x0e,0x9a,0x37,0xe4,0x05,0x75,0x73,0xc5,0x54,0x10,0xad,
		0xff,0x3e,0xa0,0x02,0x34,0xd6,0x41,0x80,0xfa,0x1a,0x0e,0x0a,0x04,0xd5,0xc5,0xc6
	};
	uint8_t ko[SHA256_HASH_LENGTH];
	int status;

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&hash);
	CuAssertIntEquals (test, 0, status);

	status = kdf_nist800_108_counter_mode (&hash.base, HMAC_SHA256, ki, sizeof (ki), label,
		sizeof (label), context, sizeof (context), ko, sizeof (ko));
	CuAssertIntEquals (test, 0, status);

	status = testing_validate_array (kdo_sha256_32, ko, sizeof (kdo_sha256_32));
	CuAssertIntEquals (test, 0, status);

	HASH_TESTING_ENGINE_RELEASE (&hash);
}

static void kdf_test_nist800_108_counter_mode_key_larger_than_hash (CuTest *test)
{
	HASH_TESTING_ENGINE hash;
	uint8_t ki[] = {
		0xf1,0x3b,0x43,0x16,0x2c,0xe4,0x02,0x34,0xd6,0x41,0x80,0xfa,0x1a,0x0e,0x0a,0x04,
		0x0e,0x9a,0x37,0xff,0x3e,0xa0,0x05,0x75,0x73,0xc5,0x54,0x10,0xad,0xd5,0xc5,0xc6
	};
	uint8_t label[] = {
		0x0e,0x9a,0x37,0xff,0x3e,0xa0,0x02,0x75,0x73,0xc5,0x54,0x10,0xad,0xd5,0xc5,0xc6,
		0xf1,0x3b,0x43,0x16,0x2c,0xe4,0x05,0x34,0xd6,0x41,0x80,0xfa,0x1a,0x0e,0x0a,0x04
	};
	uint8_t context[] = {
		0xf1,0x3b,0x43,0x16,0x2c,0x0e,0x9a,0x37,0xe4,0x05,0x75,0x73,0xc5,0x54,0x10,0xad,
		0xff,0x3e,0xa0,0x02,0x34,0xd6,0x41,0x80,0xfa,0x1a,0x0e,0x0a,0x04,0xd5,0xc5,0xc6
	};
	uint8_t ko[SHA256_HASH_LENGTH * 2];
	int status;

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&hash);
	CuAssertIntEquals (test, 0, status);

	status = kdf_nist800_108_counter_mode (&hash.base, HMAC_SHA256, ki, sizeof (ki), label,
		sizeof (label), context, sizeof (context), ko, sizeof (ko));
	CuAssertIntEquals (test, 0, status);

	status = testing_validate_array (kdo_sha256_64, ko, sizeof (kdo_sha256_64));
	CuAssertIntEquals (test, 0, status);

	HASH_TESTING_ENGINE_RELEASE (&hash);
}

static void kdf_test_nist800_108_counter_mode_key_larger_than_hash_2 (CuTest *test)
{
	HASH_TESTING_ENGINE hash;
	uint8_t ki[] = {
		0xf1,0x3b,0x43,0x16,0x2c,0xe4,0x02,0x34,0xd6,0x41,0x80,0xfa,0x1a,0x0e,0x0a,0x04,
		0x0e,0x9a,0x37,0xff,0x3e,0xa0,0x05,0x75,0x73,0xc5,0x54,0x10,0xad,0xd5,0xc5,0xc6
	};
	uint8_t label[] = {
		0x0e,0x9a,0x37,0xff,0x3e,0xa0,0x02,0x75,0x73,0xc5,0x54,0x10,0xad,0xd5,0xc5,0xc6,
		0xf1,0x3b,0x43,0x16,0x2c,0xe4,0x05,0x34,0xd6,0x41,0x80,0xfa,0x1a,0x0e,0x0a,0x04
	};
	uint8_t context[] = {
		0xf1,0x3b,0x43,0x16,0x2c,0x0e,0x9a,0x37,0xe4,0x05,0x75,0x73,0xc5,0x54,0x10,0xad,
		0xff,0x3e,0xa0,0x02,0x34,0xd6,0x41,0x80,0xfa,0x1a,0x0e,0x0a,0x04,0xd5,0xc5,0xc6
	};
	uint8_t ko[SHA256_HASH_LENGTH * 3];
	int status;

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&hash);
	CuAssertIntEquals (test, 0, status);

	status = kdf_nist800_108_counter_mode (&hash.base, HMAC_SHA256, ki, sizeof (ki), label,
		sizeof (label), context, sizeof (context), ko, sizeof (ko));
	CuAssertIntEquals (test, 0, status);

	status = testing_validate_array (kdo_sha256_96, ko, sizeof (kdo_sha256_96));
	CuAssertIntEquals (test, 0, status);

	HASH_TESTING_ENGINE_RELEASE (&hash);
}

static void kdf_test_nist800_108_counter_mode_key_larger_than_hash_not_exact_multiple (CuTest *test)
{
	HASH_TESTING_ENGINE hash;
	uint8_t ki[] = {
		0xf1,0x3b,0x43,0x16,0x2c,0xe4,0x02,0x34,0xd6,0x41,0x80,0xfa,0x1a,0x0e,0x0a,0x04,
		0x0e,0x9a,0x37,0xff,0x3e,0xa0,0x05,0x75,0x73,0xc5,0x54,0x10,0xad,0xd5,0xc5,0xc6
	};
	uint8_t label[] = {
		0x0e,0x9a,0x37,0xff,0x3e,0xa0,0x02,0x75,0x73,0xc5,0x54,0x10,0xad,0xd5,0xc5,0xc6,
		0xf1,0x3b,0x43,0x16,0x2c,0xe4,0x05,0x34,0xd6,0x41,0x80,0xfa,0x1a,0x0e,0x0a,0x04
	};
	uint8_t context[] = {
		0xf1,0x3b,0x43,0x16,0x2c,0x0e,0x9a,0x37,0xe4,0x05,0x75,0x73,0xc5,0x54,0x10,0xad,
		0xff,0x3e,0xa0,0x02,0x34,0xd6,0x41,0x80,0xfa,0x1a,0x0e,0x0a,0x04,0xd5,0xc5,0xc6
	};
	uint8_t ko[50];
	int status;

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&hash);
	CuAssertIntEquals (test, 0, status);

	status = kdf_nist800_108_counter_mode (&hash.base, HMAC_SHA256, ki, sizeof (ki), label,
		sizeof (label), context, sizeof (context), ko, sizeof (ko));
	CuAssertIntEquals (test, 0, status);

	status = testing_validate_array (kdo_sha256_50, ko, sizeof (kdo_sha256_50));
	CuAssertIntEquals (test, 0, status);

	HASH_TESTING_ENGINE_RELEASE (&hash);
}

static void kdf_test_nist800_108_counter_mode_init_hmac_fail (CuTest *test)
{
	struct hash_engine_mock hash;
	uint8_t ki[] = {
		0xf1,0x3b,0x43,0x16,0x2c,0xe4,0x02,0x34,0xd6,0x41,0x80,0xfa,0x1a,0x0e,0x0a,0x04,
		0x0e,0x9a,0x37,0xff,0x3e,0xa0,0x05,0x75,0x73,0xc5,0x54,0x10,0xad,0xd5,0xc5,0xc6
	};
	uint8_t label[] = {
		0x0e,0x9a,0x37,0xff,0x3e,0xa0,0x02,0x75,0x73,0xc5,0x54,0x10,0xad,0xd5,0xc5,0xc6,
		0xf1,0x3b,0x43,0x16,0x2c,0xe4,0x05,0x34,0xd6,0x41,0x80,0xfa,0x1a,0x0e,0x0a,0x04
	};
	uint8_t context[] = {
		0xf1,0x3b,0x43,0x16,0x2c,0x0e,0x9a,0x37,0xe4,0x05,0x75,0x73,0xc5,0x54,0x10,0xad,
		0xff,0x3e,0xa0,0x02,0x34,0xd6,0x41,0x80,0xfa,0x1a,0x0e,0x0a,0x04,0xd5,0xc5,0xc6
	};
	uint8_t ko[SHA256_HASH_LENGTH];
	int status;

	TEST_START;

	status = hash_mock_init (&hash);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&hash.mock, hash.base.start_sha256, &hash, HASH_ENGINE_NO_MEMORY);
	CuAssertIntEquals (test, 0, status);

	status = kdf_nist800_108_counter_mode (&hash.base, HMAC_SHA256, ki, sizeof (ki), label,
		sizeof (label), context, sizeof (context), ko, sizeof (ko));
	CuAssertIntEquals (test, HASH_ENGINE_NO_MEMORY, status);

	status = hash_mock_validate_and_release (&hash);
	CuAssertIntEquals (test, 0, status);

}

static void kdf_test_nist800_108_counter_mode_update_index_hmac_fail (CuTest *test)
{
	struct hash_engine_mock hash;
	uint8_t ki[] = {
		0xf1,0x3b,0x43,0x16,0x2c,0xe4,0x02,0x34,0xd6,0x41,0x80,0xfa,0x1a,0x0e,0x0a,0x04,
		0x0e,0x9a,0x37,0xff,0x3e,0xa0,0x05,0x75,0x73,0xc5,0x54,0x10,0xad,0xd5,0xc5,0xc6
	};
	uint8_t label[] = {
		0x0e,0x9a,0x37,0xff,0x3e,0xa0,0x02,0x75,0x73,0xc5,0x54,0x10,0xad,0xd5,0xc5,0xc6,
		0xf1,0x3b,0x43,0x16,0x2c,0xe4,0x05,0x34,0xd6,0x41,0x80,0xfa,0x1a,0x0e,0x0a,0x04
	};
	uint8_t context[] = {
		0xf1,0x3b,0x43,0x16,0x2c,0x0e,0x9a,0x37,0xe4,0x05,0x75,0x73,0xc5,0x54,0x10,0xad,
		0xff,0x3e,0xa0,0x02,0x34,0xd6,0x41,0x80,0xfa,0x1a,0x0e,0x0a,0x04,0xd5,0xc5,0xc6
	};
	uint8_t ko[SHA256_HASH_LENGTH];
	uint32_t i_1 = platform_htonl (1);
	int status;

	TEST_START;

	status = hash_mock_init (&hash);
	CuAssertIntEquals (test, 0, status);

	status = hash_mock_expect_hmac_init (&hash, ki, sizeof (ki));
	status |= mock_expect (&hash.mock, hash.base.update, &hash, HASH_ENGINE_NO_MEMORY,
		MOCK_ARG_PTR_CONTAINS (&i_1, sizeof (i_1)), MOCK_ARG (sizeof (i_1)));
	status |= mock_expect (&hash.mock, hash.base.cancel, &hash, 0);
	CuAssertIntEquals (test, 0, status);

	status = kdf_nist800_108_counter_mode (&hash.base, HMAC_SHA256, ki, sizeof (ki), label,
		sizeof (label), context, sizeof (context), ko, sizeof (ko));
	CuAssertIntEquals (test, HASH_ENGINE_NO_MEMORY, status);

	status = hash_mock_validate_and_release (&hash);
	CuAssertIntEquals (test, 0, status);
}

static void kdf_test_nist800_108_counter_mode_update_label_hmac_fail (CuTest *test)
{
	struct hash_engine_mock hash;
	uint8_t ki[] = {
		0xf1,0x3b,0x43,0x16,0x2c,0xe4,0x02,0x34,0xd6,0x41,0x80,0xfa,0x1a,0x0e,0x0a,0x04,
		0x0e,0x9a,0x37,0xff,0x3e,0xa0,0x05,0x75,0x73,0xc5,0x54,0x10,0xad,0xd5,0xc5,0xc6
	};
	uint8_t label[] = {
		0x0e,0x9a,0x37,0xff,0x3e,0xa0,0x02,0x75,0x73,0xc5,0x54,0x10,0xad,0xd5,0xc5,0xc6,
		0xf1,0x3b,0x43,0x16,0x2c,0xe4,0x05,0x34,0xd6,0x41,0x80,0xfa,0x1a,0x0e,0x0a,0x04
	};
	uint8_t context[] = {
		0xf1,0x3b,0x43,0x16,0x2c,0x0e,0x9a,0x37,0xe4,0x05,0x75,0x73,0xc5,0x54,0x10,0xad,
		0xff,0x3e,0xa0,0x02,0x34,0xd6,0x41,0x80,0xfa,0x1a,0x0e,0x0a,0x04,0xd5,0xc5,0xc6
	};
	uint8_t ko[SHA256_HASH_LENGTH];
	uint32_t i_1 = platform_htonl (1);
	int status;

	TEST_START;

	status = hash_mock_init (&hash);
	CuAssertIntEquals (test, 0, status);

	status = hash_mock_expect_hmac_init (&hash, ki, sizeof (ki));
	status |= mock_expect (&hash.mock, hash.base.update, &hash, 0,
		MOCK_ARG_PTR_CONTAINS (&i_1, sizeof (i_1)), MOCK_ARG (sizeof (i_1)));
	status |= mock_expect (&hash.mock, hash.base.update, &hash, HASH_ENGINE_NO_MEMORY,
		MOCK_ARG_PTR_CONTAINS (&label, sizeof (label)), MOCK_ARG (sizeof (label)));
	status |= mock_expect (&hash.mock, hash.base.cancel, &hash, 0);
	CuAssertIntEquals (test, 0, status);

	status = kdf_nist800_108_counter_mode (&hash.base, HMAC_SHA256, ki, sizeof (ki), label,
		sizeof (label), context, sizeof (context), ko, sizeof (ko));
	CuAssertIntEquals (test, HASH_ENGINE_NO_MEMORY, status);

	status = hash_mock_validate_and_release (&hash);
	CuAssertIntEquals (test, 0, status);
}

static void kdf_test_nist800_108_counter_mode_update_separator_hmac_fail (CuTest *test)
{
	struct hash_engine_mock hash;
	uint8_t ki[] = {
		0xf1,0x3b,0x43,0x16,0x2c,0xe4,0x02,0x34,0xd6,0x41,0x80,0xfa,0x1a,0x0e,0x0a,0x04,
		0x0e,0x9a,0x37,0xff,0x3e,0xa0,0x05,0x75,0x73,0xc5,0x54,0x10,0xad,0xd5,0xc5,0xc6
	};
	uint8_t label[] = {
		0x0e,0x9a,0x37,0xff,0x3e,0xa0,0x02,0x75,0x73,0xc5,0x54,0x10,0xad,0xd5,0xc5,0xc6,
		0xf1,0x3b,0x43,0x16,0x2c,0xe4,0x05,0x34,0xd6,0x41,0x80,0xfa,0x1a,0x0e,0x0a,0x04
	};
	uint8_t context[] = {
		0xf1,0x3b,0x43,0x16,0x2c,0x0e,0x9a,0x37,0xe4,0x05,0x75,0x73,0xc5,0x54,0x10,0xad,
		0xff,0x3e,0xa0,0x02,0x34,0xd6,0x41,0x80,0xfa,0x1a,0x0e,0x0a,0x04,0xd5,0xc5,0xc6
	};
	uint8_t ko[SHA256_HASH_LENGTH];
	uint8_t separator = 0;
	uint32_t i_1 = platform_htonl (1);
	int status;

	TEST_START;

	status = hash_mock_init (&hash);
	CuAssertIntEquals (test, 0, status);

	status = hash_mock_expect_hmac_init (&hash, ki, sizeof (ki));
	status |= mock_expect (&hash.mock, hash.base.update, &hash, 0,
		MOCK_ARG_PTR_CONTAINS (&i_1, sizeof (i_1)), MOCK_ARG (sizeof (i_1)));
	status |= mock_expect (&hash.mock, hash.base.update, &hash, 0,
		MOCK_ARG_PTR_CONTAINS (&label, sizeof (label)), MOCK_ARG (sizeof (label)));
	status |= mock_expect (&hash.mock, hash.base.update, &hash, HASH_ENGINE_NO_MEMORY,
		MOCK_ARG_PTR_CONTAINS (&separator, sizeof (separator)), MOCK_ARG (sizeof (separator)));
	status |= mock_expect (&hash.mock, hash.base.cancel, &hash, 0);
	CuAssertIntEquals (test, 0, status);

	status = kdf_nist800_108_counter_mode (&hash.base, HMAC_SHA256, ki, sizeof (ki), label,
		sizeof (label), context, sizeof (context), ko, sizeof (ko));
	CuAssertIntEquals (test, HASH_ENGINE_NO_MEMORY, status);

	status = hash_mock_validate_and_release (&hash);
	CuAssertIntEquals (test, 0, status);
}

static void kdf_test_nist800_108_counter_mode_update_context_hmac_fail (CuTest *test)
{
	struct hash_engine_mock hash;
	uint8_t ki[] = {
		0xf1,0x3b,0x43,0x16,0x2c,0xe4,0x02,0x34,0xd6,0x41,0x80,0xfa,0x1a,0x0e,0x0a,0x04,
		0x0e,0x9a,0x37,0xff,0x3e,0xa0,0x05,0x75,0x73,0xc5,0x54,0x10,0xad,0xd5,0xc5,0xc6
	};
	uint8_t label[] = {
		0x0e,0x9a,0x37,0xff,0x3e,0xa0,0x02,0x75,0x73,0xc5,0x54,0x10,0xad,0xd5,0xc5,0xc6,
		0xf1,0x3b,0x43,0x16,0x2c,0xe4,0x05,0x34,0xd6,0x41,0x80,0xfa,0x1a,0x0e,0x0a,0x04
	};
	uint8_t context[] = {
		0xf1,0x3b,0x43,0x16,0x2c,0x0e,0x9a,0x37,0xe4,0x05,0x75,0x73,0xc5,0x54,0x10,0xad,
		0xff,0x3e,0xa0,0x02,0x34,0xd6,0x41,0x80,0xfa,0x1a,0x0e,0x0a,0x04,0xd5,0xc5,0xc6
	};
	uint8_t ko[SHA256_HASH_LENGTH];
	uint8_t separator = 0;
	uint32_t i_1 = platform_htonl (1);
	int status;

	TEST_START;

	status = hash_mock_init (&hash);
	CuAssertIntEquals (test, 0, status);

	status = hash_mock_expect_hmac_init (&hash, ki, sizeof (ki));
	status |= mock_expect (&hash.mock, hash.base.update, &hash, 0,
		MOCK_ARG_PTR_CONTAINS (&i_1, sizeof (i_1)), MOCK_ARG (sizeof (i_1)));
	status |= mock_expect (&hash.mock, hash.base.update, &hash, 0,
		MOCK_ARG_PTR_CONTAINS (&label, sizeof (label)), MOCK_ARG (sizeof (label)));
	status |= mock_expect (&hash.mock, hash.base.update, &hash, 0,
		MOCK_ARG_PTR_CONTAINS (&separator, sizeof (separator)), MOCK_ARG (sizeof (separator)));
	status |= mock_expect (&hash.mock, hash.base.update, &hash, HASH_ENGINE_NO_MEMORY,
		MOCK_ARG_PTR_CONTAINS (&context, sizeof (context)), MOCK_ARG (sizeof (context)));
	status |= mock_expect (&hash.mock, hash.base.cancel, &hash, 0);
	CuAssertIntEquals (test, 0, status);

	status = kdf_nist800_108_counter_mode (&hash.base, HMAC_SHA256, ki, sizeof (ki), label,
		sizeof (label), context, sizeof (context), ko, sizeof (ko));
	CuAssertIntEquals (test, HASH_ENGINE_NO_MEMORY, status);

	status = hash_mock_validate_and_release (&hash);
	CuAssertIntEquals (test, 0, status);
}

static void kdf_test_nist800_108_counter_mode_update_ko_len_hmac_fail (CuTest *test)
{
	struct hash_engine_mock hash;
	uint8_t ki[] = {
		0xf1,0x3b,0x43,0x16,0x2c,0xe4,0x02,0x34,0xd6,0x41,0x80,0xfa,0x1a,0x0e,0x0a,0x04,
		0x0e,0x9a,0x37,0xff,0x3e,0xa0,0x05,0x75,0x73,0xc5,0x54,0x10,0xad,0xd5,0xc5,0xc6
	};
	uint8_t label[] = {
		0x0e,0x9a,0x37,0xff,0x3e,0xa0,0x02,0x75,0x73,0xc5,0x54,0x10,0xad,0xd5,0xc5,0xc6,
		0xf1,0x3b,0x43,0x16,0x2c,0xe4,0x05,0x34,0xd6,0x41,0x80,0xfa,0x1a,0x0e,0x0a,0x04
	};
	uint8_t context[] = {
		0xf1,0x3b,0x43,0x16,0x2c,0x0e,0x9a,0x37,0xe4,0x05,0x75,0x73,0xc5,0x54,0x10,0xad,
		0xff,0x3e,0xa0,0x02,0x34,0xd6,0x41,0x80,0xfa,0x1a,0x0e,0x0a,0x04,0xd5,0xc5,0xc6
	};
	uint8_t ko[SHA256_HASH_LENGTH];
	uint8_t separator = 0;
	uint32_t L = platform_htonl (SHA256_HASH_LENGTH * 8);
	uint32_t i_1 = platform_htonl (1);
	int status;

	TEST_START;

	status = hash_mock_init (&hash);
	CuAssertIntEquals (test, 0, status);

	status = hash_mock_expect_hmac_init (&hash, ki, sizeof (ki));
	status |= mock_expect (&hash.mock, hash.base.update, &hash, 0,
		MOCK_ARG_PTR_CONTAINS (&i_1, sizeof (i_1)), MOCK_ARG (sizeof (i_1)));
	status |= mock_expect (&hash.mock, hash.base.update, &hash, 0,
		MOCK_ARG_PTR_CONTAINS (&label, sizeof (label)), MOCK_ARG (sizeof (label)));
	status |= mock_expect (&hash.mock, hash.base.update, &hash, 0,
		MOCK_ARG_PTR_CONTAINS (&separator, sizeof (separator)), MOCK_ARG (sizeof (separator)));
	status |= mock_expect (&hash.mock, hash.base.update, &hash, 0,
		MOCK_ARG_PTR_CONTAINS (&context, sizeof (context)), MOCK_ARG (sizeof (context)));
	status |= mock_expect (&hash.mock, hash.base.update, &hash, HASH_ENGINE_NO_MEMORY,
		MOCK_ARG_PTR_CONTAINS (&L, sizeof (L)), MOCK_ARG (sizeof (L)));
	status |= mock_expect (&hash.mock, hash.base.cancel, &hash, 0);
	CuAssertIntEquals (test, 0, status);

	status = kdf_nist800_108_counter_mode (&hash.base, HMAC_SHA256, ki, sizeof (ki), label,
		sizeof (label), context, sizeof (context), ko, sizeof (ko));
	CuAssertIntEquals (test, HASH_ENGINE_NO_MEMORY, status);

	status = hash_mock_validate_and_release (&hash);
	CuAssertIntEquals (test, 0, status);
}

static void kdf_test_nist800_108_counter_mode_finish_hmac_fail (CuTest *test)
{
	struct hash_engine_mock hash;
	uint8_t ki[] = {
		0xf1,0x3b,0x43,0x16,0x2c,0xe4,0x02,0x34,0xd6,0x41,0x80,0xfa,0x1a,0x0e,0x0a,0x04,
		0x0e,0x9a,0x37,0xff,0x3e,0xa0,0x05,0x75,0x73,0xc5,0x54,0x10,0xad,0xd5,0xc5,0xc6
	};
	uint8_t label[] = {
		0x0e,0x9a,0x37,0xff,0x3e,0xa0,0x02,0x75,0x73,0xc5,0x54,0x10,0xad,0xd5,0xc5,0xc6,
		0xf1,0x3b,0x43,0x16,0x2c,0xe4,0x05,0x34,0xd6,0x41,0x80,0xfa,0x1a,0x0e,0x0a,0x04
	};
	uint8_t context[] = {
		0xf1,0x3b,0x43,0x16,0x2c,0x0e,0x9a,0x37,0xe4,0x05,0x75,0x73,0xc5,0x54,0x10,0xad,
		0xff,0x3e,0xa0,0x02,0x34,0xd6,0x41,0x80,0xfa,0x1a,0x0e,0x0a,0x04,0xd5,0xc5,0xc6
	};
	uint8_t ko[SHA256_HASH_LENGTH];
	uint8_t separator = 0;
	uint32_t L = platform_htonl (SHA256_HASH_LENGTH * 8);
	uint32_t i_1 = platform_htonl (1);
	int status;

	TEST_START;

	status = hash_mock_init (&hash);
	CuAssertIntEquals (test, 0, status);

	status = hash_mock_expect_hmac_init (&hash, ki, sizeof (ki));
	status |= mock_expect (&hash.mock, hash.base.update, &hash, 0,
		MOCK_ARG_PTR_CONTAINS (&i_1, sizeof (i_1)), MOCK_ARG (sizeof (i_1)));
	status |= mock_expect (&hash.mock, hash.base.update, &hash, 0,
		MOCK_ARG_PTR_CONTAINS (&label, sizeof (label)), MOCK_ARG (sizeof (label)));
	status |= mock_expect (&hash.mock, hash.base.update, &hash, 0,
		MOCK_ARG_PTR_CONTAINS (&separator, sizeof (separator)), MOCK_ARG (sizeof (separator)));
	status |= mock_expect (&hash.mock, hash.base.update, &hash, 0,
		MOCK_ARG_PTR_CONTAINS (&context, sizeof (context)), MOCK_ARG (sizeof (context)));
	status |= mock_expect (&hash.mock, hash.base.update, &hash, 0,
		MOCK_ARG_PTR_CONTAINS (&L, sizeof (L)), MOCK_ARG (sizeof (L)));
	status |= mock_expect (&hash.mock, hash.base.finish, &hash, HASH_ENGINE_NO_MEMORY,
		MOCK_ARG_NOT_NULL, MOCK_ARG (SHA256_HASH_LENGTH));
	status |= mock_expect (&hash.mock, hash.base.cancel, &hash, 0);
	CuAssertIntEquals (test, 0, status);

	status = kdf_nist800_108_counter_mode (&hash.base, HMAC_SHA256, ki, sizeof (ki), label,
		sizeof (label), context, sizeof (context), ko, sizeof (ko));
	CuAssertIntEquals (test, HASH_ENGINE_NO_MEMORY, status);

	status = hash_mock_validate_and_release (&hash);
	CuAssertIntEquals (test, 0, status);
}

static void kdf_test_nist800_108_counter_mode_invalid_arg (CuTest *test)
{
	struct hash_engine_mock hash;
	uint8_t ki[] = {
		0xf1,0x3b,0x43,0x16,0x2c,0xe4,0x02,0x34,0xd6,0x41,0x80,0xfa,0x1a,0x0e,0x0a,0x04,
		0x0e,0x9a,0x37,0xff,0x3e,0xa0,0x05,0x75,0x73,0xc5,0x54,0x10,0xad,0xd5,0xc5,0xc6
	};
	uint8_t label[] = {
		0x0e,0x9a,0x37,0xff,0x3e,0xa0,0x02,0x75,0x73,0xc5,0x54,0x10,0xad,0xd5,0xc5,0xc6,
		0xf1,0x3b,0x43,0x16,0x2c,0xe4,0x05,0x34,0xd6,0x41,0x80,0xfa,0x1a,0x0e,0x0a,0x04
	};
	uint8_t context[] = {
		0xf1,0x3b,0x43,0x16,0x2c,0x0e,0x9a,0x37,0xe4,0x05,0x75,0x73,0xc5,0x54,0x10,0xad,
		0xff,0x3e,0xa0,0x02,0x34,0xd6,0x41,0x80,0xfa,0x1a,0x0e,0x0a,0x04,0xd5,0xc5,0xc6
	};
	uint8_t ko[SHA256_HASH_LENGTH];
	int status;

	TEST_START;

	status = hash_mock_init (&hash);
	CuAssertIntEquals (test, 0, status);

	status = kdf_nist800_108_counter_mode (NULL, HMAC_SHA256, ki, sizeof (ki), label,
		sizeof (label), context, sizeof (context), ko, sizeof (ko));
	CuAssertIntEquals (test, KDF_INVALID_ARGUMENT, status);

	status = kdf_nist800_108_counter_mode (&hash.base, HMAC_SHA256, NULL, sizeof (ki), label,
		sizeof (label), context, sizeof (context), ko, sizeof (ko));
	CuAssertIntEquals (test, KDF_INVALID_ARGUMENT, status);

	status = kdf_nist800_108_counter_mode (&hash.base, HMAC_SHA256, ki, sizeof (ki), NULL,
		sizeof (label), context, sizeof (context), ko, sizeof (ko));
	CuAssertIntEquals (test, KDF_INVALID_ARGUMENT, status);

	status = kdf_nist800_108_counter_mode (&hash.base, HMAC_SHA256, ki, sizeof (ki), label,
		sizeof (label), context, sizeof (context), NULL, sizeof (ko));
	CuAssertIntEquals (test, KDF_INVALID_ARGUMENT, status);

	status = hash_mock_validate_and_release (&hash);
	CuAssertIntEquals (test, 0, status);
}

CuSuite* get_kdf_suite ()
{
	CuSuite *suite = CuSuiteNew ();

	SUITE_ADD_TEST (suite, kdf_test_nist800_108_counter_mode_sha1);
	SUITE_ADD_TEST (suite, kdf_test_nist800_108_counter_mode_sha256);
	SUITE_ADD_TEST (suite, kdf_test_nist800_108_counter_mode_key_larger_than_hash);
	SUITE_ADD_TEST (suite, kdf_test_nist800_108_counter_mode_key_larger_than_hash_2);
	SUITE_ADD_TEST (suite,
		kdf_test_nist800_108_counter_mode_key_larger_than_hash_not_exact_multiple);
	SUITE_ADD_TEST (suite, kdf_test_nist800_108_counter_mode_init_hmac_fail);
	SUITE_ADD_TEST (suite, kdf_test_nist800_108_counter_mode_update_index_hmac_fail);
	SUITE_ADD_TEST (suite, kdf_test_nist800_108_counter_mode_update_label_hmac_fail);
	SUITE_ADD_TEST (suite, kdf_test_nist800_108_counter_mode_update_separator_hmac_fail);
	SUITE_ADD_TEST (suite, kdf_test_nist800_108_counter_mode_update_context_hmac_fail);
	SUITE_ADD_TEST (suite, kdf_test_nist800_108_counter_mode_update_ko_len_hmac_fail);
	SUITE_ADD_TEST (suite, kdf_test_nist800_108_counter_mode_finish_hmac_fail);
	SUITE_ADD_TEST (suite, kdf_test_nist800_108_counter_mode_invalid_arg);
	return suite;
}
