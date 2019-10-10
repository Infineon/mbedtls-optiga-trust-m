################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include lib/third_party/aws/pkcs11/subdir.mk
-include lib/third_party/aws/FreeRTOS/portable/MemMang/subdir.mk
-include lib/third_party/aws/FreeRTOS/portable/GCC/ARM_CM4F/subdir.mk
-include lib/third_party/aws/FreeRTOS/subdir.mk
-include lib/third_party/aws/subdir.mk
-include lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/system/subdir.mk
-include lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/esp/subdir.mk
-include lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/api/subdir.mk
-include lib/third_party/XMCLib/2.1.20/drivers/src/subdir.mk
-include lib/third_party/XMCLib/2.1.20/Newlib/subdir.mk
-include lib/third_party/XMCLib/2.1.20/Dave/Generated/USBD_VCOM/virtual_com/subdir.mk
-include lib/third_party/XMCLib/2.1.20/Dave/Generated/USBD_VCOM/class_driver/device/subdir.mk
-include lib/third_party/XMCLib/2.1.20/Dave/Generated/USBD_VCOM/subdir.mk
-include lib/third_party/XMCLib/2.1.20/Dave/Generated/USBD/usb/core/xmc4000/subdir.mk
-include lib/third_party/XMCLib/2.1.20/Dave/Generated/USBD/usb/core/subdir.mk
-include lib/third_party/XMCLib/2.1.20/Dave/Generated/USBD/subdir.mk
-include lib/third_party/XMCLib/2.1.20/Dave/Generated/UART/subdir.mk
-include lib/third_party/XMCLib/2.1.20/Dave/Generated/TIMER/subdir.mk
-include lib/third_party/XMCLib/2.1.20/Dave/Generated/INTERRUPT/subdir.mk
-include lib/third_party/XMCLib/2.1.20/Dave/Generated/I2C_MASTER/subdir.mk
-include lib/third_party/XMCLib/2.1.20/Dave/Generated/GLOBAL_CCU4/subdir.mk
-include lib/third_party/XMCLib/2.1.20/Dave/Generated/DIGITAL_IO/subdir.mk
-include lib/third_party/XMCLib/2.1.20/Dave/Generated/CPU_CTRL_XMC4/subdir.mk
-include lib/third_party/XMCLib/2.1.20/Dave/Generated/CLOCK_XMC4/subdir.mk
-include lib/third_party/XMCLib/2.1.20/Dave/Generated/subdir.mk
-include lib/third_party/XMCLib/2.1.20/CMSIS/Infineon/XMC4800_series/Source/GCC/subdir.mk
-include lib/third_party/XMCLib/2.1.20/CMSIS/Infineon/XMC4800_series/Source/subdir.mk
-include lib/optiga-trust-m/pal/xmc4800/subdir.mk
-include lib/optiga-trust-m/pal/subdir.mk
-include lib/optiga-trust-m/optiga/util/subdir.mk
-include lib/optiga-trust-m/optiga/crypt/subdir.mk
-include lib/optiga-trust-m/optiga/comms/ifx_i2c/subdir.mk
-include lib/optiga-trust-m/optiga/comms/subdir.mk
-include lib/optiga-trust-m/optiga/common/subdir.mk
-include lib/optiga-trust-m/optiga/cmd/subdir.mk
-include lib/optiga-trust-m/examples/utilities/authenticate_chip/subdir.mk
-include lib/optiga-trust-m/examples/utilities/subdir.mk
-include lib/optiga-trust-m/examples/optiga/usecases/subdir.mk
-include lib/optiga-trust-m/examples/optiga/subdir.mk
-include lib/mbedtls_port/subdir.mk
-include lib/mbedtls/library/subdir.mk
-include common/subdir.mk
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
example_tls_client_xmc.lst

SECONDARY_SIZE += \
example_tls_client_xmc.siz


LIST_FILES = $(addsuffix .o.lst, $(basename $(OBJS))) 
MAP_FILE = "example_tls_client_xmc.map"

TOOLCHAIN_ROOT=C:/Users/Yushev/Downloads/DAVE_4-4-2_64bit_2018-02-23/DAVE-IDE-4.4.2-64Bit/eclipse/ARM-GCC-49
PROJECT_LOC=C:/Users/Yushev/git/optiga_trust/mbedtls-optiga-trust-m/example_tls_client_xmc/xmc4800_iot_kit

# All Target
all: example_tls_client_xmc.elf secondary-outputs

# Tool invocations
example_tls_client_xmc.elf: $(OBJS) ../XMC4800x2048.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM-GCC C Linker'
	$(file >objects.rsp,$(OBJS))
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -T"../XMC4800x2048.ld" -nostartfiles -Xlinker --gc-sections -specs=nano.specs -specs=nosys.specs -Wl,-Map,$(MAP_FILE) -v -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -mcpu=cortex-m4 -mthumb -g -gdwarf-2 -o "example_tls_client_xmc.elf" "@objects.rsp" $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo.
example_tls_client_xmc.hex: example_tls_client_xmc.elf
	@echo 'Invoking: ARM-GCC Create Flash Image'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-objcopy" -O ihex "example_tls_client_xmc.elf" "example_tls_client_xmc.hex"
	@echo 'Finished building: $@'
	@echo.
example_tls_client_xmc.lst: example_tls_client_xmc.elf
	@echo 'Invoking: ARM-GCC Create Listing'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-objdump" -h -S "example_tls_client_xmc.elf" > "example_tls_client_xmc.lst"
	@echo 'Finished building: $@'
	@echo.
example_tls_client_xmc.siz: example_tls_client_xmc.elf
	@echo 'Invoking: ARM-GCC Print Size'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-size" --format=berkeley -x -t "example_tls_client_xmc.elf"
	@echo 'Finished building: $@'
	@echo.
# Other Targets
clean:
	-$(RM) $(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ARM_GCC_FOR_XMC_LINKER_OUTPUT_TYPE_OUTPUTS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS)
	-$(RM) common/aws_dev_mode_key_provisioning.o common/aws_logging_task_dynamic_buffers.o common/aws_tcp_echo_client_single_task.o common/console_io.o common/e_eeprom_xmc4.o common/entropy_hardware.o common/entropy_hardware_alt.o common/memcpy.o common/optiga_trust_m.o lib/mbedtls/library/aes.o lib/mbedtls/library/aesni.o lib/mbedtls/library/arc4.o lib/mbedtls/library/aria.o lib/mbedtls/library/asn1parse.o lib/mbedtls/library/asn1write.o lib/mbedtls/library/base64.o lib/mbedtls/library/bignum.o lib/mbedtls/library/blowfish.o lib/mbedtls/library/camellia.o lib/mbedtls/library/ccm.o lib/mbedtls/library/certs.o lib/mbedtls/library/chacha20.o lib/mbedtls/library/chachapoly.o lib/mbedtls/library/cipher.o lib/mbedtls/library/cipher_wrap.o lib/mbedtls/library/cmac.o lib/mbedtls/library/ctr_drbg.o lib/mbedtls/library/debug.o lib/mbedtls/library/des.o lib/mbedtls/library/dhm.o lib/mbedtls/library/ecdh.o lib/mbedtls/library/ecdsa.o lib/mbedtls/library/ecjpake.o lib/mbedtls/library/ecp.o lib/mbedtls/library/ecp_curves.o lib/mbedtls/library/entropy.o lib/mbedtls/library/entropy_poll.o lib/mbedtls/library/error.o lib/mbedtls/library/gcm.o lib/mbedtls/library/havege.o lib/mbedtls/library/hkdf.o lib/mbedtls/library/hmac_drbg.o lib/mbedtls/library/md.o lib/mbedtls/library/md2.o lib/mbedtls/library/md4.o lib/mbedtls/library/md5.o lib/mbedtls/library/md_wrap.o lib/mbedtls/library/memory_buffer_alloc.o lib/mbedtls/library/net_sockets.o lib/mbedtls/library/nist_kw.o lib/mbedtls/library/oid.o lib/mbedtls/library/padlock.o lib/mbedtls/library/pem.o lib/mbedtls/library/pk.o lib/mbedtls/library/pk_wrap.o lib/mbedtls/library/pkcs11.o lib/mbedtls/library/pkcs12.o lib/mbedtls/library/pkcs5.o lib/mbedtls/library/pkparse.o lib/mbedtls/library/pkwrite.o lib/mbedtls/library/platform.o lib/mbedtls/library/platform_util.o lib/mbedtls/library/poly1305.o lib/mbedtls/library/ripemd160.o lib/mbedtls/library/rsa.o lib/mbedtls/library/rsa_internal.o 
	-$(RM) lib/mbedtls/library/sha1.o lib/mbedtls/library/sha256.o lib/mbedtls/library/sha512.o lib/mbedtls/library/ssl_cache.o lib/mbedtls/library/ssl_ciphersuites.o lib/mbedtls/library/ssl_cli.o lib/mbedtls/library/ssl_cookie.o lib/mbedtls/library/ssl_srv.o lib/mbedtls/library/ssl_ticket.o lib/mbedtls/library/ssl_tls.o lib/mbedtls/library/threading.o lib/mbedtls/library/timing.o lib/mbedtls/library/version.o lib/mbedtls/library/version_features.o lib/mbedtls/library/x509.o lib/mbedtls/library/x509_create.o lib/mbedtls/library/x509_crl.o lib/mbedtls/library/x509_crt.o lib/mbedtls/library/x509_csr.o lib/mbedtls/library/x509write_crt.o lib/mbedtls/library/x509write_csr.o lib/mbedtls/library/xtea.o lib/optiga-trust-m/examples/optiga/example_optiga_crypt_ecc_generate_keypair.o lib/optiga-trust-m/examples/optiga/example_optiga_crypt_ecdh.o lib/optiga-trust-m/examples/optiga/example_optiga_crypt_ecdsa_sign.o lib/optiga-trust-m/examples/optiga/example_optiga_crypt_ecdsa_verify.o lib/optiga-trust-m/examples/optiga/example_optiga_crypt_hash.o lib/optiga-trust-m/examples/optiga/example_optiga_crypt_random.o lib/optiga-trust-m/examples/optiga/example_optiga_crypt_rsa_decrypt.o lib/optiga-trust-m/examples/optiga/example_optiga_crypt_rsa_encrypt_message.o lib/optiga-trust-m/examples/optiga/example_optiga_crypt_rsa_encrypt_session.o lib/optiga-trust-m/examples/optiga/example_optiga_crypt_rsa_generate_keypair.o lib/optiga-trust-m/examples/optiga/example_optiga_crypt_rsa_sign.o lib/optiga-trust-m/examples/optiga/example_optiga_crypt_rsa_verify.o lib/optiga-trust-m/examples/optiga/example_optiga_crypt_tls_prf_sha256.o lib/optiga-trust-m/examples/optiga/example_optiga_hibernate_restore.o lib/optiga-trust-m/examples/optiga/example_optiga_util_protected_update.o lib/optiga-trust-m/examples/optiga/example_optiga_util_read_data.o lib/optiga-trust-m/examples/optiga/example_optiga_util_update_count.o 
	-$(RM) lib/optiga-trust-m/examples/optiga/example_optiga_util_write_data.o lib/optiga-trust-m/examples/optiga/usecases/example_pair_host_and_optiga_using_pre_shared_secret.o lib/optiga-trust-m/examples/utilities/authenticate_chip/example_authenticate_chip.o lib/optiga-trust-m/examples/utilities/authenticate_chip/pal_crypt_mbedtls.o lib/optiga-trust-m/examples/utilities/ecdsa_utils.o lib/optiga-trust-m/examples/utilities/trustm_chipinfo.o lib/optiga-trust-m/optiga/cmd/optiga_cmd.o lib/optiga-trust-m/optiga/common/optiga_lib_common.o lib/optiga-trust-m/optiga/common/optiga_lib_logger.o lib/optiga-trust-m/optiga/comms/ifx_i2c/ifx_i2c.o lib/optiga-trust-m/optiga/comms/ifx_i2c/ifx_i2c_config.o lib/optiga-trust-m/optiga/comms/ifx_i2c/ifx_i2c_data_link_layer.o lib/optiga-trust-m/optiga/comms/ifx_i2c/ifx_i2c_physical_layer.o lib/optiga-trust-m/optiga/comms/ifx_i2c/ifx_i2c_presentation_layer.o lib/optiga-trust-m/optiga/comms/ifx_i2c/ifx_i2c_transport_layer.o lib/optiga-trust-m/optiga/comms/optiga_comms_ifx_i2c.o lib/optiga-trust-m/optiga/crypt/optiga_crypt.o lib/optiga-trust-m/optiga/util/optiga_util.o lib/optiga-trust-m/pal/pal_crypt_mbedtls.o lib/optiga-trust-m/pal/xmc4800/pal.o lib/optiga-trust-m/pal/xmc4800/pal_gpio.o lib/optiga-trust-m/pal/xmc4800/pal_i2c.o lib/optiga-trust-m/pal/xmc4800/pal_ifx_i2c_config.o lib/optiga-trust-m/pal/xmc4800/pal_os_datastore.o lib/optiga-trust-m/pal/xmc4800/pal_os_event.o lib/optiga-trust-m/pal/xmc4800/pal_os_lock.o lib/optiga-trust-m/pal/xmc4800/pal_os_timer.o lib/third_party/XMCLib/2.1.20/CMSIS/Infineon/XMC4800_series/Source/GCC/startup_XMC4800.o lib/third_party/XMCLib/2.1.20/CMSIS/Infineon/XMC4800_series/Source/system_XMC4800.o lib/third_party/XMCLib/2.1.20/Dave/Generated/CLOCK_XMC4/clock_xmc4.o lib/third_party/XMCLib/2.1.20/Dave/Generated/CLOCK_XMC4/clock_xmc4_conf.o lib/third_party/XMCLib/2.1.20/Dave/Generated/CPU_CTRL_XMC4/cpu_ctrl_xmc4.o 
	-$(RM) lib/third_party/XMCLib/2.1.20/Dave/Generated/CPU_CTRL_XMC4/cpu_ctrl_xmc4_conf.o lib/third_party/XMCLib/2.1.20/Dave/Generated/DAVE.o lib/third_party/XMCLib/2.1.20/Dave/Generated/DIGITAL_IO/digital_io.o lib/third_party/XMCLib/2.1.20/Dave/Generated/DIGITAL_IO/digital_io_conf.o lib/third_party/XMCLib/2.1.20/Dave/Generated/GLOBAL_CCU4/global_ccu4.o lib/third_party/XMCLib/2.1.20/Dave/Generated/GLOBAL_CCU4/global_ccu4_conf.o lib/third_party/XMCLib/2.1.20/Dave/Generated/I2C_MASTER/i2c_master.o lib/third_party/XMCLib/2.1.20/Dave/Generated/I2C_MASTER/i2c_master_conf.o lib/third_party/XMCLib/2.1.20/Dave/Generated/INTERRUPT/interrupt.o lib/third_party/XMCLib/2.1.20/Dave/Generated/INTERRUPT/interrupt_conf.o lib/third_party/XMCLib/2.1.20/Dave/Generated/TIMER/timer.o lib/third_party/XMCLib/2.1.20/Dave/Generated/TIMER/timer_conf.o lib/third_party/XMCLib/2.1.20/Dave/Generated/UART/uart.o lib/third_party/XMCLib/2.1.20/Dave/Generated/UART/uart_conf.o lib/third_party/XMCLib/2.1.20/Dave/Generated/USBD/usb/core/usb_task.o lib/third_party/XMCLib/2.1.20/Dave/Generated/USBD/usb/core/xmc4000/usbd_endpoint_stream_xmc4000.o lib/third_party/XMCLib/2.1.20/Dave/Generated/USBD/usb/core/xmc4000/usbd_endpoint_xmc4000.o lib/third_party/XMCLib/2.1.20/Dave/Generated/USBD/usbd.o lib/third_party/XMCLib/2.1.20/Dave/Generated/USBD/usbd_conf.o lib/third_party/XMCLib/2.1.20/Dave/Generated/USBD_VCOM/class_driver/device/cdc_class_device.o lib/third_party/XMCLib/2.1.20/Dave/Generated/USBD_VCOM/usbd_vcom.o lib/third_party/XMCLib/2.1.20/Dave/Generated/USBD_VCOM/usbd_vcom_conf.o lib/third_party/XMCLib/2.1.20/Dave/Generated/USBD_VCOM/virtual_com/descriptors.o lib/third_party/XMCLib/2.1.20/Newlib/syscalls.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc1_eru.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc1_flash.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc1_gpio.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc1_rtc.o 
	-$(RM) lib/third_party/XMCLib/2.1.20/drivers/src/xmc1_scu.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc4_eru.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc4_flash.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc4_gpio.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc4_rtc.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc4_scu.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_acmp.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_bccu.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_can.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_ccu4.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_ccu8.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_common.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_dac.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_dma.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_dsd.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_ebu.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_ecat.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_eru.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_eth_mac.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_eth_phy_dp83848.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_eth_phy_ksz8031rnl.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_eth_phy_ksz8081rnb.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_fce.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_gpio.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_hrpwm.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_i2c.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_i2s.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_ledts.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_math.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_pau.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_posif.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_prng.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_rtc.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_sdmmc.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_spi.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_uart.o 
	-$(RM) lib/third_party/XMCLib/2.1.20/drivers/src/xmc_usbd.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_usbh.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_usic.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_vadc.o lib/third_party/XMCLib/2.1.20/drivers/src/xmc_wdt.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/api/esp_netconn.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/api/esp_rest_client.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/esp/esp.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/esp/esp_ap.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/esp/esp_buff.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/esp/esp_conn.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/esp/esp_debug.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/esp/esp_evt.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/esp/esp_hostname.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/esp/esp_input.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/esp/esp_int.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/esp/esp_mdns.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/esp/esp_mem.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/esp/esp_parser.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/esp/esp_pbuf.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/esp/esp_ping.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/esp/esp_sntp.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/esp/esp_sta.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/esp/esp_threads.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/esp/esp_timeout.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/esp/esp_unicode.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/esp/esp_wps.o 
	-$(RM) lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/system/esp_ll_xmc4800_iotkit.o lib/third_party/XMCLib/2.1.20/third_party/ESP_AT_Lib/src/system/esp_sys_freertos.o lib/third_party/aws/FreeRTOS/event_groups.o lib/third_party/aws/FreeRTOS/list.o lib/third_party/aws/FreeRTOS/queue.o lib/third_party/aws/FreeRTOS/stream_buffer.o lib/third_party/aws/FreeRTOS/tasks.o lib/third_party/aws/FreeRTOS/timers.o lib/third_party/aws/FreeRTOS/portable/GCC/ARM_CM4F/port.o lib/third_party/aws/FreeRTOS/portable/MemMang/heap_4.o lib/third_party/aws/aws_bufferpool_static_thread_safe.o lib/third_party/aws/aws_crypto.o lib/third_party/aws/aws_secure_sockets.o lib/third_party/aws/aws_system_init.o lib/third_party/aws/aws_tls.o lib/third_party/aws/aws_wifi.o lib/third_party/aws/pkcs11/aws_pkcs11_mbedtls.o lib/third_party/aws/pkcs11/aws_pkcs11_pal.o main.o  example_tls_client_xmc.elf $(LIST_FILES) $(MAP_FILE) objects.rsp
	-@echo.
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
