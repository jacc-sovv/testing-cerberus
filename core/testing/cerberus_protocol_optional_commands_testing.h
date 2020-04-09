// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT license.

#ifndef CERBERUS_PROTOCOL_OPTIONAL_COMMANDS_TESTING_H_
#define CERBERUS_PROTOCOL_OPTIONAL_COMMANDS_TESTING_H_

#include <stdint.h>
#include <stddef.h>
#include "testing.h"
#include "cmd_interface/cmd_interface.h"
#include "attestation/pcr_store.h"
#include "mock/firmware_update_control_mock.h"
#include "mock/manifest_cmd_interface_mock.h"
#include "mock/pfm_manager_mock.h"
#include "mock/cmd_background_mock.h"
#include "mock/logging_mock.h"
#include "mock/hash_mock.h"
#include "mock/host_control_mock.h"
#include "mock/cmd_authorization_mock.h"
#include "mock/recovery_image_cmd_interface_mock.h"
#include "mock/recovery_image_manager_mock.h"


void cerberus_protocol_optional_commands_testing_process_fw_update_init (CuTest *test,
	struct cmd_interface *cmd, struct firmware_update_control_mock *update);
void cerberus_protocol_optional_commands_testing_process_fw_update_init_invalid_len (CuTest *test,
	struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_fw_update_init_fail (CuTest *test,
	struct cmd_interface *cmd, struct firmware_update_control_mock *update);

void cerberus_protocol_optional_commands_testing_process_fw_update (CuTest *test,
	struct cmd_interface *cmd, struct firmware_update_control_mock *update);
void cerberus_protocol_optional_commands_testing_process_fw_update_no_data (CuTest *test,
	struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_fw_update_fail (CuTest *test,
	struct cmd_interface *cmd, struct firmware_update_control_mock *update);

void cerberus_protocol_optional_commands_testing_process_complete_fw_update (CuTest *test,
	struct cmd_interface *cmd, struct firmware_update_control_mock *update);
void cerberus_protocol_optional_commands_testing_process_complete_fw_update_invalid_len (
	CuTest *test, struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_complete_fw_update_fail (CuTest *test,
	struct cmd_interface *cmd, struct firmware_update_control_mock *update);

void cerberus_protocol_optional_commands_testing_process_pfm_update_init_port0 (CuTest *test,
	struct cmd_interface *cmd, struct manifest_cmd_interface_mock *pfm_0);
void cerberus_protocol_optional_commands_testing_process_pfm_update_init_port1 (CuTest *test,
	struct cmd_interface *cmd, struct manifest_cmd_interface_mock *pfm_1);
void cerberus_protocol_optional_commands_testing_process_pfm_update_init_port0_null (CuTest *test,
	struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_pfm_update_init_port1_null (CuTest *test,
	struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_pfm_update_init_invalid_port (CuTest *test,
	struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_pfm_update_init_invalid_len (CuTest *test,
	struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_pfm_update_init_fail (CuTest *test,
	struct cmd_interface *cmd, struct manifest_cmd_interface_mock *pfm_0);

void cerberus_protocol_optional_commands_testing_process_pfm_update_port0 (CuTest *test,
	struct cmd_interface *cmd, struct manifest_cmd_interface_mock *pfm_0);
void cerberus_protocol_optional_commands_testing_process_pfm_update_port1 (CuTest *test,
	struct cmd_interface *cmd, struct manifest_cmd_interface_mock *pfm_1);
void cerberus_protocol_optional_commands_testing_process_pfm_update_port0_null (CuTest *test,
	struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_pfm_update_port1_null (CuTest *test,
	struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_pfm_update_no_data (CuTest *test,
	struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_pfm_update_invalid_port (CuTest *test,
	struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_pfm_update_fail (CuTest *test,
	struct cmd_interface *cmd, struct manifest_cmd_interface_mock *pfm_0);

void cerberus_protocol_optional_commands_testing_process_pfm_update_complete_port0 (CuTest *test,
	struct cmd_interface *cmd, struct manifest_cmd_interface_mock *pfm_0);
void cerberus_protocol_optional_commands_testing_process_pfm_update_complete_port1 (CuTest *test,
	struct cmd_interface *cmd, struct manifest_cmd_interface_mock *pfm_1);
void cerberus_protocol_optional_commands_testing_process_pfm_update_complete_port0_immediate (
	CuTest *test, struct cmd_interface *cmd, struct manifest_cmd_interface_mock *pfm_0);
void cerberus_protocol_optional_commands_testing_process_pfm_update_complete_port1_immediate (
	CuTest *test, struct cmd_interface *cmd, struct manifest_cmd_interface_mock *pfm_1);
void cerberus_protocol_optional_commands_testing_process_pfm_update_complete_port0_null (
	CuTest *test, struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_pfm_update_complete_port1_null (
	CuTest *test, struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_pfm_update_complete_invalid_len (
	CuTest *test, struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_pfm_update_complete_invalid_port (
	CuTest *test, struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_pfm_update_complete_fail (CuTest *test,
	struct cmd_interface *cmd, struct manifest_cmd_interface_mock *pfm_0);

void cerberus_protocol_optional_commands_testing_process_get_pfm_id_port0_region0 (CuTest *test,
	struct cmd_interface *cmd, struct pfm_manager_mock *pfm_manager_0);
void cerberus_protocol_optional_commands_testing_process_get_pfm_id_port0_region1 (CuTest *test,
	struct cmd_interface *cmd, struct pfm_manager_mock *pfm_manager_0);
void cerberus_protocol_optional_commands_testing_process_get_pfm_id_port1_region0 (CuTest *test,
	struct cmd_interface *cmd, struct pfm_manager_mock *pfm_manager_1);
void cerberus_protocol_optional_commands_testing_process_get_pfm_id_port1_region1 (CuTest *test,
	struct cmd_interface *cmd, struct pfm_manager_mock *pfm_manager_1);
void cerberus_protocol_optional_commands_testing_process_get_pfm_id_no_id_type (CuTest *test,
	struct cmd_interface *cmd, struct pfm_manager_mock *pfm_manager_0);
void cerberus_protocol_optional_commands_testing_process_get_pfm_id_port0_region0_null (
	CuTest *test, struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_get_pfm_id_port0_region1_null (
	CuTest *test, struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_get_pfm_id_port1_region0_null (
	CuTest *test, struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_get_pfm_id_port1_region1_null (
	CuTest *test, struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_get_pfm_id_no_active_pfm (CuTest *test,
	struct cmd_interface *cmd, struct pfm_manager_mock *pfm_manager_0);
void cerberus_protocol_optional_commands_testing_process_get_pfm_id_no_pending_pfm (CuTest *test,
	struct cmd_interface *cmd, struct pfm_manager_mock *pfm_manager_0);
void cerberus_protocol_optional_commands_testing_process_get_pfm_id_fail (CuTest *test,
	struct cmd_interface *cmd, struct pfm_manager_mock *pfm_manager_0);
void cerberus_protocol_optional_commands_testing_process_get_pfm_id_invalid_len (CuTest *test,
	struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_get_pfm_id_invalid_port (CuTest *test,
	struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_get_pfm_id_invalid_region (CuTest *test,
	struct cmd_interface *cmd);

void cerberus_protocol_optional_commands_testing_process_get_pfm_supported_fw_port0_region0 (
	CuTest *test, struct cmd_interface *cmd, struct pfm_manager_mock *pfm_manager_0);
void cerberus_protocol_optional_commands_testing_process_get_pfm_supported_fw_port0_region1 (
	CuTest *test, struct cmd_interface *cmd, struct pfm_manager_mock *pfm_manager_0);
void cerberus_protocol_optional_commands_testing_process_get_pfm_supported_fw_port1_region0 (
	CuTest *test, struct cmd_interface *cmd, struct pfm_manager_mock *pfm_manager_1);
void cerberus_protocol_optional_commands_testing_process_get_pfm_supported_fw_port1_region1 (
	CuTest *test, struct cmd_interface *cmd, struct pfm_manager_mock *pfm_manager_1);
void cerberus_protocol_optional_commands_testing_process_get_pfm_supported_fw_nonzero_offset (
	CuTest *test, struct cmd_interface *cmd, struct pfm_manager_mock *pfm_manager_0);
void cerberus_protocol_optional_commands_testing_process_get_pfm_supported_fw_limited_response (
	CuTest *test, struct cmd_interface *cmd, struct pfm_manager_mock *pfm_manager_0);
void cerberus_protocol_optional_commands_testing_process_get_pfm_supported_fw_empty_list (
	CuTest *test, struct cmd_interface *cmd, struct pfm_manager_mock *pfm_manager_0);
void cerberus_protocol_optional_commands_testing_process_get_pfm_supported_fw_empty_list_nonzero_offset (
	CuTest *test, struct cmd_interface *cmd, struct pfm_manager_mock *pfm_manager_0);
void cerberus_protocol_optional_commands_testing_process_get_pfm_supported_fw_port0_region0_null (
	CuTest *test, struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_get_pfm_supported_fw_port0_region1_null (
	CuTest *test, struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_get_pfm_supported_fw_port1_region0_null (
	CuTest *test, struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_get_pfm_supported_fw_port1_region1_null (
	CuTest *test, struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_get_pfm_supported_fw_no_active_pfm (
	CuTest *test, struct cmd_interface *cmd, struct pfm_manager_mock *pfm_manager_0);
void cerberus_protocol_optional_commands_testing_process_get_pfm_supported_fw_no_pending_pfm (
	CuTest *test, struct cmd_interface *cmd, struct pfm_manager_mock *pfm_manager_0);
void cerberus_protocol_optional_commands_testing_process_get_pfm_supported_fw_fail_id (
	CuTest *test, struct cmd_interface *cmd, struct pfm_manager_mock *pfm_manager_0);
void cerberus_protocol_optional_commands_testing_process_get_pfm_supported_fw_fail (
	CuTest *test, struct cmd_interface *cmd, struct pfm_manager_mock *pfm_manager_0);
void cerberus_protocol_optional_commands_testing_process_get_pfm_supported_fw_invalid_len (
	CuTest *test, struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_get_pfm_supported_fw_invalid_region (
	CuTest *test, struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_get_pfm_supported_fw_invalid_offset (
	CuTest *test, struct cmd_interface *cmd, struct pfm_manager_mock *pfm_manager_0);
void cerberus_protocol_optional_commands_testing_process_get_pfm_supported_fw_invalid_port (
	CuTest *test, struct cmd_interface *cmd);

void cerberus_protocol_optional_commands_testing_process_log_clear_debug (CuTest *test,
	struct cmd_interface *cmd, struct cmd_background_mock *background);
void cerberus_protocol_optional_commands_testing_process_log_clear_tcg (CuTest *test,
	struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_log_clear_invalid_len (CuTest *test,
	struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_log_clear_invalid_type (CuTest *test,
	struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_log_clear_debug_fail (CuTest *test,
	struct cmd_interface *cmd, struct cmd_background_mock *background);

void cerberus_protocol_optional_commands_testing_process_get_log_info (CuTest *test,
	struct cmd_interface *cmd, struct logging_mock *debug, int tcg_entries);
void cerberus_protocol_optional_commands_testing_process_get_log_info_invalid_len (CuTest *test,
	struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_get_log_info_fail_debug (CuTest *test,
	struct cmd_interface *cmd, struct logging_mock *debug, int tcg_entries);

void cerberus_protocol_optional_commands_testing_process_log_read_debug (CuTest *test,
	struct cmd_interface *cmd, struct logging_mock *debug);
void cerberus_protocol_optional_commands_testing_process_log_read_debug_limited_response (
	CuTest *test, struct cmd_interface *cmd, struct logging_mock *debug);
void cerberus_protocol_optional_commands_testing_process_log_read_tcg (CuTest *test,
	struct cmd_interface *cmd, struct hash_engine_mock *hash, struct pcr_store *store);
void cerberus_protocol_optional_commands_testing_process_log_read_tcg_limited_response (
	CuTest *test, struct cmd_interface *cmd, struct hash_engine_mock *hash,
	struct pcr_store *store);
void cerberus_protocol_optional_commands_testing_process_log_read_debug_fail (CuTest *test,
	struct cmd_interface *cmd, struct logging_mock *debug);
void cerberus_protocol_optional_commands_testing_process_log_read_tcg_fail (CuTest *test,
	struct cmd_interface *cmd, struct hash_engine_mock *hash, struct pcr_store *store);
void cerberus_protocol_optional_commands_testing_process_log_read_invalid_offset (CuTest *test,
	struct cmd_interface *cmd, struct logging_mock *debug);
void cerberus_protocol_optional_commands_testing_process_log_read_invalid_type (CuTest *test,
	struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_log_read_invalid_len (CuTest *test,
	struct cmd_interface *cmd);

void cerberus_protocol_optional_commands_testing_process_request_unseal (CuTest *test,
	struct cmd_interface *cmd, struct cmd_background_mock *background, int pcr);
void cerberus_protocol_optional_commands_testing_process_request_unseal_fail (CuTest *test,
	struct cmd_interface *cmd, struct cmd_background_mock *background, int pcr);
void cerberus_protocol_optional_commands_testing_process_request_unseal_no_seed_len (CuTest *test,
	struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_request_unseal_no_cipher_len (CuTest *test,
	struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_request_unseal_incomplete_payload (
	CuTest *test, struct cmd_interface *cmd);

void cerberus_protocol_optional_commands_testing_process_request_unseal_result (CuTest *test,
	struct cmd_interface *cmd, struct cmd_background_mock *background);
void cerberus_protocol_optional_commands_testing_process_request_unseal_result_limited_response (
	CuTest *test, struct cmd_interface *cmd, struct cmd_background_mock *background);
void cerberus_protocol_optional_commands_testing_process_request_unseal_result_busy (CuTest *test,
	struct cmd_interface *cmd, struct cmd_background_mock *background);
void cerberus_protocol_optional_commands_testing_process_request_unseal_result_fail (CuTest *test,
	struct cmd_interface *cmd, struct cmd_background_mock *background);
void cerberus_protocol_optional_commands_testing_process_request_unseal_result_invalid_len (
	CuTest *test, struct cmd_interface *cmd);

void cerberus_protocol_optional_commands_testing_process_get_host_reset_status_port0_out_of_reset (
	CuTest *test, struct cmd_interface *cmd, struct host_control_mock *host_ctrl_0);
void cerberus_protocol_optional_commands_testing_process_get_host_reset_status_port0_held_in_reset (
	CuTest *test, struct cmd_interface *cmd, struct host_control_mock *host_ctrl_0);
void cerberus_protocol_optional_commands_testing_process_get_host_reset_status_port0_not_held_in_reset (
	CuTest *test, struct cmd_interface *cmd, struct host_control_mock *host_ctrl_0);
void cerberus_protocol_optional_commands_testing_process_get_host_reset_status_port0_null (
	CuTest *test, struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_get_host_reset_status_port1_out_of_reset (
	CuTest *test, struct cmd_interface *cmd, struct host_control_mock *host_ctrl_1);
void cerberus_protocol_optional_commands_testing_process_get_host_reset_status_port1_held_in_reset (
	CuTest *test, struct cmd_interface *cmd, struct host_control_mock *host_ctrl_1);
void cerberus_protocol_optional_commands_testing_process_get_host_reset_status_port1_not_held_in_reset (
	CuTest *test, struct cmd_interface *cmd, struct host_control_mock *host_ctrl_1);
void cerberus_protocol_optional_commands_testing_process_get_host_reset_status_port1_null (
	CuTest *test, struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_get_host_reset_status_invalid_len (
	CuTest *test, struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_get_host_reset_status_invalid_port (
	CuTest *test, struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_get_host_reset_status_check_error (
	CuTest *test, struct cmd_interface *cmd, struct host_control_mock *host_ctrl_1);
void cerberus_protocol_optional_commands_testing_process_get_host_reset_status_hold_check_error (
	CuTest *test, struct cmd_interface *cmd, struct host_control_mock *host_ctrl_0);

void cerberus_protocol_optional_commands_testing_process_reset_bypass_no_nonce_authorized (
	CuTest *test, struct cmd_interface *cmd, struct cmd_authorization_mock *auth,
	struct cmd_background_mock *background);
void cerberus_protocol_optional_commands_testing_process_reset_bypass_no_nonce_challenge (
	CuTest *test, struct cmd_interface *cmd, struct cmd_authorization_mock *auth);
void cerberus_protocol_optional_commands_testing_process_reset_bypass_no_nonce_max_challenge (
	CuTest *test, struct cmd_interface *cmd, struct cmd_authorization_mock *auth);
void cerberus_protocol_optional_commands_testing_process_reset_bypass_no_nonce_not_authorized (
	CuTest *test, struct cmd_interface *cmd, struct cmd_authorization_mock *auth);
void cerberus_protocol_optional_commands_testing_process_reset_bypass_with_nonce_authorized (
	CuTest *test, struct cmd_interface *cmd, struct cmd_authorization_mock *auth,
	struct cmd_background_mock *background);
void cerberus_protocol_optional_commands_testing_process_reset_bypass_with_nonce_not_authorized (
	CuTest *test, struct cmd_interface *cmd, struct cmd_authorization_mock *auth);
void cerberus_protocol_optional_commands_testing_process_reset_bypass_no_nonce_invalid_challenge (
	CuTest *test, struct cmd_interface *cmd, struct cmd_authorization_mock *auth);
void cerberus_protocol_optional_commands_testing_process_reset_bypass_no_nonce_invalid_challenge_limited_response (
	CuTest *test, struct cmd_interface *cmd, struct cmd_authorization_mock *auth);
void cerberus_protocol_optional_commands_testing_process_reset_bypass_error (
	CuTest *test, struct cmd_interface *cmd, struct cmd_authorization_mock *auth,
	struct cmd_background_mock *background);

void cerberus_protocol_optional_commands_testing_process_restore_defaults_no_nonce_authorized (
	CuTest *test, struct cmd_interface *cmd, struct cmd_authorization_mock *auth,
	struct cmd_background_mock *background);
void cerberus_protocol_optional_commands_testing_process_restore_defaults_no_nonce_challenge (
	CuTest *test, struct cmd_interface *cmd, struct cmd_authorization_mock *auth);
void cerberus_protocol_optional_commands_testing_process_restore_defaults_no_nonce_max_challenge (
	CuTest *test, struct cmd_interface *cmd, struct cmd_authorization_mock *auth);
void cerberus_protocol_optional_commands_testing_process_restore_defaults_no_nonce_not_authorized (
	CuTest *test, struct cmd_interface *cmd, struct cmd_authorization_mock *auth);
void cerberus_protocol_optional_commands_testing_process_restore_defaults_with_nonce_authorized (
	CuTest *test, struct cmd_interface *cmd, struct cmd_authorization_mock *auth,
	struct cmd_background_mock *background);
void cerberus_protocol_optional_commands_testing_process_restore_defaults_with_nonce_not_authorized (
	CuTest *test, struct cmd_interface *cmd, struct cmd_authorization_mock *auth);
void cerberus_protocol_optional_commands_testing_process_restore_defaults_no_nonce_invalid_challenge (
	CuTest *test, struct cmd_interface *cmd, struct cmd_authorization_mock *auth);
void cerberus_protocol_optional_commands_testing_process_restore_defaults_no_nonce_invalid_challenge_limited_response (
	CuTest *test, struct cmd_interface *cmd, struct cmd_authorization_mock *auth);
void cerberus_protocol_optional_commands_testing_process_restore_defaults_error (
	CuTest *test, struct cmd_interface *cmd, struct cmd_authorization_mock *auth,
	struct cmd_background_mock *background);

void cerberus_protocol_optional_commands_testing_process_reset_config_invalid_len (CuTest *test,
	struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_reset_config_invalid_request_subtype (
	CuTest *test, struct cmd_interface *cmd);

void cerberus_protocol_optional_commands_testing_process_prepare_recovery_image_port0 (CuTest *test,
	struct cmd_interface *cmd, struct recovery_image_cmd_interface_mock *recovery_0);
void cerberus_protocol_optional_commands_testing_process_prepare_recovery_image_port1 (CuTest *test,
	struct cmd_interface *cmd, struct recovery_image_cmd_interface_mock *recovery_1);
void cerberus_protocol_optional_commands_testing_process_prepare_recovery_image_port0_null (
	CuTest *test, struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_prepare_recovery_image_port1_null (
	CuTest *test, struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_prepare_recovery_image_invalid_len (
	CuTest *test, struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_prepare_recovery_image_fail (CuTest *test,
	struct cmd_interface *cmd, struct recovery_image_cmd_interface_mock *recovery_0);
void cerberus_protocol_optional_commands_testing_process_prepare_recovery_image_bad_port_index (
	CuTest *test, struct cmd_interface *cmd);

void cerberus_protocol_optional_commands_testing_process_update_recovery_image_port0 (CuTest *test,
	struct cmd_interface *cmd, struct recovery_image_cmd_interface_mock *recovery_0);
void cerberus_protocol_optional_commands_testing_process_update_recovery_image_port1 (CuTest *test,
	struct cmd_interface *cmd, struct recovery_image_cmd_interface_mock *recovery_1);
void cerberus_protocol_optional_commands_testing_process_update_recovery_image_port0_null (
	CuTest *test, struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_update_recovery_image_port1_null (
	CuTest *test, struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_update_recovery_image_no_data (
	CuTest *test, struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_update_recovery_image_bad_port_index (
	CuTest *test, struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_update_recovery_image_fail (CuTest *test,
	struct cmd_interface *cmd, struct recovery_image_cmd_interface_mock *recovery_0);

void cerberus_protocol_optional_commands_testing_process_activate_recovery_image_port0 (
	CuTest *test, struct cmd_interface *cmd, struct recovery_image_cmd_interface_mock *recovery_0);
void cerberus_protocol_optional_commands_testing_process_activate_recovery_image_port1 (
	CuTest *test, struct cmd_interface *cmd, struct recovery_image_cmd_interface_mock *recovery_1);
void cerberus_protocol_optional_commands_testing_process_activate_recovery_image_port0_null (
	CuTest *test, struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_activate_recovery_image_port1_null (
	CuTest *test, struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_activate_recovery_image_invalid_len (
	CuTest *test, struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_activate_recovery_image_bad_port_index (
	CuTest *test, struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_activate_recovery_image_fail (CuTest *test,
	struct cmd_interface *cmd, struct recovery_image_cmd_interface_mock *recovery_0);

void cerberus_protocol_optional_commands_testing_process_get_recovery_image_version_port0 (
	CuTest *test, struct cmd_interface *cmd,
	struct recovery_image_manager_mock *recovery_manager_0);
void cerberus_protocol_optional_commands_testing_process_get_recovery_image_version_port1 (
	CuTest *test, struct cmd_interface *cmd,
	struct recovery_image_manager_mock *recovery_manager_1);
void cerberus_protocol_optional_commands_testing_process_get_recovery_image_version_no_id_type (
	CuTest *test, struct cmd_interface *cmd, struct
	recovery_image_manager_mock *recovery_manager_0);
void cerberus_protocol_optional_commands_testing_process_get_recovery_image_version_port0_null (
	CuTest *test, struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_get_recovery_image_version_port1_null (
	CuTest *test, struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_get_recovery_image_version_no_image (
	CuTest *test, struct cmd_interface *cmd,
	struct recovery_image_manager_mock *recovery_manager_0);
void cerberus_protocol_optional_commands_testing_process_get_recovery_image_version_fail (
	CuTest *test, struct cmd_interface *cmd,
	struct recovery_image_manager_mock *recovery_manager_0);
void cerberus_protocol_optional_commands_testing_process_get_recovery_image_version_invalid_len (
	CuTest *test, struct cmd_interface *cmd);
void cerberus_protocol_optional_commands_testing_process_get_recovery_image_version_bad_port_index (
	CuTest *test, struct cmd_interface *cmd);


#endif /* CERBERUS_PROTOCOL_OPTIONAL_COMMANDS_TESTING_H_ */
