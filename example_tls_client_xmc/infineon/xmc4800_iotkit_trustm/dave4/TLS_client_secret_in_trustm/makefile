################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include lib/trustm/pal/xmc4800_freertos/i2c_master_dave/subdir.mk
-include lib/trustm/pal/xmc4800_freertos/subdir.mk
-include lib/trustm/optiga/util/subdir.mk
-include lib/trustm/optiga/crypt/subdir.mk
-include lib/trustm/optiga/comms/ifx_i2c/subdir.mk
-include lib/trustm/optiga/comms/subdir.mk
-include lib/trustm/optiga/common/subdir.mk
-include lib/trustm/optiga/cmd/subdir.mk
-include lib/trustm/examples/utilities/subdir.mk
-include lib/trustm/examples/optiga/subdir.mk
-include lib/trustm/examples/mbedtls_port/subdir.mk
-include lib/trustm/examples/ecdsa_utils/subdir.mk
-include lib/trustm/examples/authenticate_chip/subdir.mk
-include lib/third_party/mbedtls/library/subdir.mk
-include lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/system/subdir.mk
-include lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/esp/subdir.mk
-include lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/api/subdir.mk
-include lib/third_party/XMCLib/2.1.20/drivers/src/subdir.mk
-include lib/third_party/XMCLib/2.1.20/Newlib/subdir.mk
-include lib/third_party/XMCLib/2.1.20/CMSIS/Infineon/XMC4800_series/Source/GCC/subdir.mk
-include lib/third_party/XMCLib/2.1.20/CMSIS/Infineon/XMC4800_series/Source/subdir.mk
-include lib/aws/pkcs11/subdir.mk
-include lib/aws/FreeRTOS/portable/MemMang/subdir.mk
-include lib/aws/FreeRTOS/portable/GCC/ARM_CM4F/subdir.mk
-include lib/aws/FreeRTOS/subdir.mk
-include lib/aws/subdir.mk
-include application_code/infineon_code/subdir.mk
-include application_code/common_demos/source/subdir.mk
-include application_code/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \

SECONDARY_FLASH += \
aws_demos_trustm.lst

SECONDARY_SIZE += \
aws_demos_trustm.siz


LIST_FILES = $(addsuffix .o.lst, $(basename $(OBJS))) 
MAP_FILE = "aws_demos_trustm.map"

TOOLCHAIN_ROOT=C:/Users/limtsesi/Desktop/DAVE_4-4-2_64bit_2018-02-23/DAVE-IDE-4.4.2-64Bit/eclipse/ARM-GCC-49
PROJECT_LOC=C:/XMC4800_FreeRTOS/amazon-freertos-optiga-trust-m/example_tls_client_xmc/infineon/xmc4800_iotkit_trustm/dave4

# All Target
all: aws_demos_trustm.elf secondary-outputs

# Tool invocations
aws_demos_trustm.elf: $(OBJS) ../XMC4800x2048.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM-GCC C Linker'
	$(file >objects.rsp,$(OBJS))
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -T"../XMC4800x2048.ld" -nostartfiles -Xlinker --gc-sections -specs=nano.specs -specs=nosys.specs -Wl,-Map,$(MAP_FILE) -v -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -mcpu=cortex-m4 -mthumb -g -gdwarf-2 -o "aws_demos_trustm.elf" "@objects.rsp" $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo.
aws_demos_trustm.hex: aws_demos_trustm.elf
	@echo 'Invoking: ARM-GCC Create Flash Image'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-objcopy" -O ihex "aws_demos_trustm.elf" "aws_demos_trustm.hex"
	@echo 'Finished building: $@'
	@echo.
aws_demos_trustm.lst: aws_demos_trustm.elf
	@echo 'Invoking: ARM-GCC Create Listing'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-objdump" -h -S "aws_demos_trustm.elf" > "aws_demos_trustm.lst"
	@echo 'Finished building: $@'
	@echo.
aws_demos_trustm.siz: aws_demos_trustm.elf
	@echo 'Invoking: ARM-GCC Print Size'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-size" --format=berkeley -t "aws_demos_trustm.elf"
	@echo 'Finished building: $@'
	@echo.
# Other Targets
clean:
	-$(RM) $(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ARM_GCC_FOR_XMC_LINKER_OUTPUT_TYPE_OUTPUTS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS)
	-$(RM) application_code/common_demos/source/aws_dev_mode_key_provisioning.o application_code/common_demos/source/aws_logging_task_dynamic_buffers.o application_code/common_demos/source/aws_tcp_echo_client_single_task.o application_code/infineon_code/console_io.o application_code/infineon_code/e_eeprom_xmc4.o application_code/infineon_code/entropy_hardware.o application_code/infineon_code/entropy_hardware_alt.o application_code/infineon_code/memcpy.o application_code/infineon_code/optiga_trust_m.o application_code/main.o lib/aws/FreeRTOS/event_groups.o lib/aws/FreeRTOS/list.o lib/aws/FreeRTOS/queue.o lib/aws/FreeRTOS/stream_buffer.o lib/aws/FreeRTOS/tasks.o lib/aws/FreeRTOS/timers.o lib/aws/FreeRTOS/portable/GCC/ARM_CM4F/port.o lib/aws/FreeRTOS/portable/MemMang/heap_4.o lib/aws/aws_bufferpool_static_thread_safe.o lib/aws/aws_crypto.o lib/aws/aws_secure_sockets.o lib/aws/aws_system_init.o lib/aws/aws_tls.o lib/aws/aws_wifi.o lib/aws/pkcs11/aws_pkcs11_mbedtls.o lib/aws/pkcs11/aws_pkcs11_pal.o lib/third_party/XMCLib/2.1.20/CMSIS/Infineon/XMC4800_series/Source/GCC/startup_XMC4800.o lib/third_party/XMCLib/2.1.20/CMSIS/Infineon/XMC4800_series/Source/system_XMC4800.o lib/third_party/XMCLib/2.1.20/Newlib/syscalls.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc1_eru.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc1_flash.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc1_gpio.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc1_rtc.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc1_scu.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc4_eru.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc4_flash.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc4_gpio.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc4_rtc.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc4_scu.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_acmp.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_bccu.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_can.o 
	-$(RM) lib/third_party/XMCLib/2.1.20/drivers/src/xmc_ccu4.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_ccu8.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_common.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_dac.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_dma.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_dsd.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_ebu.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_ecat.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_eru.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_eth_mac.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_eth_phy_dp83848.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_eth_phy_ksz8031rnl.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_eth_phy_ksz8081rnb.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_fce.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_gpio.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_hrpwm.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_i2c.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_i2s.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_ledts.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_math.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_pau.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_posif.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_prng.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_rtc.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_sdmmc.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_spi.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_uart.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_usbd.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_usbh.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_usic.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_vadc.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_wdt.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/api/esp_netconn.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/api/esp_rest_client.o 
	-$(RM) lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/esp/esp.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/esp/esp_ap.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/esp/esp_buff.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/esp/esp_conn.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/esp/esp_debug.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/esp/esp_evt.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/esp/esp_hostname.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/esp/esp_input.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/esp/esp_int.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/esp/esp_mdns.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/esp/esp_mem.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/esp/esp_parser.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/esp/esp_pbuf.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/esp/esp_ping.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/esp/esp_sntp.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/esp/esp_sta.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/esp/esp_threads.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/esp/esp_timeout.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/esp/esp_unicode.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/esp/esp_wps.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/system/esp_ll_xmc4800_iotkit.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/system/esp_sys_freertos.o lib/third_party/mbedtls/library/aes.o lib/third_party/mbedtls/library/aesni.o lib/third_party/mbedtls/library/arc4.o lib/third_party/mbedtls/library/aria.o lib/third_party/mbedtls/library/asn1parse.o lib/third_party/mbedtls/library/asn1write.o lib/third_party/mbedtls/library/base64.o lib/third_party/mbedtls/library/bignum.o 
	-$(RM) lib/third_party/mbedtls/library/blowfish.o lib/third_party/mbedtls/library/camellia.o lib/third_party/mbedtls/library/ccm.o lib/third_party/mbedtls/library/certs.o lib/third_party/mbedtls/library/chacha20.o lib/third_party/mbedtls/library/chachapoly.o lib/third_party/mbedtls/library/cipher.o lib/third_party/mbedtls/library/cipher_wrap.o lib/third_party/mbedtls/library/cmac.o lib/third_party/mbedtls/library/ctr_drbg.o lib/third_party/mbedtls/library/debug.o lib/third_party/mbedtls/library/des.o lib/third_party/mbedtls/library/dhm.o lib/third_party/mbedtls/library/ecdh.o lib/third_party/mbedtls/library/ecdsa.o lib/third_party/mbedtls/library/ecjpake.o lib/third_party/mbedtls/library/ecp.o lib/third_party/mbedtls/library/ecp_curves.o lib/third_party/mbedtls/library/entropy.o lib/third_party/mbedtls/library/entropy_poll.o lib/third_party/mbedtls/library/error.o lib/third_party/mbedtls/library/gcm.o lib/third_party/mbedtls/library/havege.o lib/third_party/mbedtls/library/hkdf.o lib/third_party/mbedtls/library/hmac_drbg.o lib/third_party/mbedtls/library/md.o lib/third_party/mbedtls/library/md2.o lib/third_party/mbedtls/library/md4.o lib/third_party/mbedtls/library/md5.o lib/third_party/mbedtls/library/md_wrap.o lib/third_party/mbedtls/library/memory_buffer_alloc.o lib/third_party/mbedtls/library/net_sockets.o lib/third_party/mbedtls/library/nist_kw.o lib/third_party/mbedtls/library/oid.o lib/third_party/mbedtls/library/padlock.o lib/third_party/mbedtls/library/pem.o lib/third_party/mbedtls/library/pk.o lib/third_party/mbedtls/library/pk_wrap.o lib/third_party/mbedtls/library/pkcs11.o lib/third_party/mbedtls/library/pkcs12.o lib/third_party/mbedtls/library/pkcs5.o lib/third_party/mbedtls/library/pkparse.o lib/third_party/mbedtls/library/pkwrite.o lib/third_party/mbedtls/library/platform.o lib/third_party/mbedtls/library/platform_util.o lib/third_party/mbedtls/library/poly1305.o 
	-$(RM) lib/third_party/mbedtls/library/ripemd160.o lib/third_party/mbedtls/library/rsa.o lib/third_party/mbedtls/library/rsa_internal.o lib/third_party/mbedtls/library/sha1.o lib/third_party/mbedtls/library/sha256.o lib/third_party/mbedtls/library/sha512.o lib/third_party/mbedtls/library/ssl_cache.o lib/third_party/mbedtls/library/ssl_ciphersuites.o lib/third_party/mbedtls/library/ssl_cli.o lib/third_party/mbedtls/library/ssl_cookie.o lib/third_party/mbedtls/library/ssl_srv.o lib/third_party/mbedtls/library/ssl_ticket.o lib/third_party/mbedtls/library/ssl_tls.o lib/third_party/mbedtls/library/threading.o lib/third_party/mbedtls/library/timing.o lib/third_party/mbedtls/library/version.o lib/third_party/mbedtls/library/version_features.o lib/third_party/mbedtls/library/x509.o lib/third_party/mbedtls/library/x509_create.o lib/third_party/mbedtls/library/x509_crl.o lib/third_party/mbedtls/library/x509_crt.o lib/third_party/mbedtls/library/x509_csr.o lib/third_party/mbedtls/library/x509write_crt.o lib/third_party/mbedtls/library/x509write_csr.o lib/third_party/mbedtls/library/xtea.o lib/trustm/examples/authenticate_chip/example_authenticate_chip.o lib/trustm/examples/authenticate_chip/pal_crypt_mbedtls.o lib/trustm/examples/ecdsa_utils/asn1_to_ecdsa_rs.o lib/trustm/examples/ecdsa_utils/ecdsa_rs_to_asn1.o lib/trustm/examples/mbedtls_port/trustm_ecdh.o lib/trustm/examples/mbedtls_port/trustm_ecdsa.o lib/trustm/examples/optiga/example_optiga_crypt_ecc_generate_keypair.o lib/trustm/examples/optiga/example_optiga_crypt_ecdh.o lib/trustm/examples/optiga/example_optiga_crypt_ecdsa_sign.o lib/trustm/examples/optiga/example_optiga_crypt_ecdsa_verify.o lib/trustm/examples/optiga/example_optiga_crypt_hash.o lib/trustm/examples/optiga/example_optiga_crypt_random.o lib/trustm/examples/optiga/example_optiga_crypt_rsa_decrypt.o lib/trustm/examples/optiga/example_optiga_crypt_rsa_encrypt_message.o 
	-$(RM) lib/trustm/examples/optiga/example_optiga_crypt_rsa_encrypt_session.o lib/trustm/examples/optiga/example_optiga_crypt_rsa_generate_keypair.o lib/trustm/examples/optiga/example_optiga_crypt_rsa_sign.o lib/trustm/examples/optiga/example_optiga_crypt_rsa_verify.o lib/trustm/examples/optiga/example_optiga_crypt_tls_prf_sha256.o lib/trustm/examples/optiga/example_optiga_util_protected_update.o lib/trustm/examples/optiga/example_optiga_util_read_data.o lib/trustm/examples/optiga/example_optiga_util_update_count.o lib/trustm/examples/optiga/example_optiga_util_write_data.o lib/trustm/examples/utilities/trustm_chipinfo.o lib/trustm/optiga/cmd/optiga_cmd.o lib/trustm/optiga/common/optiga_lib_common.o lib/trustm/optiga/common/optiga_lib_logger.o lib/trustm/optiga/comms/ifx_i2c/ifx_i2c.o lib/trustm/optiga/comms/ifx_i2c/ifx_i2c_config.o lib/trustm/optiga/comms/ifx_i2c/ifx_i2c_data_link_layer.o lib/trustm/optiga/comms/ifx_i2c/ifx_i2c_physical_layer.o lib/trustm/optiga/comms/ifx_i2c/ifx_i2c_presentation_layer.o lib/trustm/optiga/comms/ifx_i2c/ifx_i2c_transport_layer.o lib/trustm/optiga/comms/optiga_comms_ifx_i2c.o lib/trustm/optiga/crypt/optiga_crypt.o lib/trustm/optiga/util/optiga_util.o lib/trustm/pal/xmc4800_freertos/i2c_master_dave/i2c_master.o lib/trustm/pal/xmc4800_freertos/i2c_master_dave/i2c_master_conf.o lib/trustm/pal/xmc4800_freertos/pal.o lib/trustm/pal/xmc4800_freertos/pal_crypt_mbedtls.o lib/trustm/pal/xmc4800_freertos/pal_gpio.o lib/trustm/pal/xmc4800_freertos/pal_i2c.o lib/trustm/pal/xmc4800_freertos/pal_ifx_i2c_config.o lib/trustm/pal/xmc4800_freertos/pal_logger.o lib/trustm/pal/xmc4800_freertos/pal_os_datastore.o lib/trustm/pal/xmc4800_freertos/pal_os_event.o lib/trustm/pal/xmc4800_freertos/pal_os_lock.o lib/trustm/pal/xmc4800_freertos/pal_os_timer.o  aws_demos_trustm.elf $(LIST_FILES) $(MAP_FILE) objects.rsp
	-@echo.
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
