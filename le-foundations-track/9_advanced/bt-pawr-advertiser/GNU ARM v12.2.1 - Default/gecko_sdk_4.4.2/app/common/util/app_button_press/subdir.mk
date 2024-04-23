################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3/app/common/util/app_button_press/app_button_press.c 

OBJS += \
./gecko_sdk_4.4.2/app/common/util/app_button_press/app_button_press.o 

C_DEPS += \
./gecko_sdk_4.4.2/app/common/util/app_button_press/app_button_press.d 


# Each subdirectory must supply rules for building sources it contributes
gecko_sdk_4.4.2/app/common/util/app_button_press/app_button_press.o: /Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3/app/common/util/app_button_press/app_button_press.c gecko_sdk_4.4.2/app/common/util/app_button_press/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG22C224F512IM40=1' '-DSL_BOARD_NAME="BRD4182A"' '-DSL_BOARD_REV="B04"' '-DHARDWARE_BOARD_DEFAULT_RF_BAND_2400=1' '-DHARDWARE_BOARD_SUPPORTS_1_RF_BAND=1' '-DHARDWARE_BOARD_SUPPORTS_RF_BAND_2400=1' '-DHFXO_FREQ=38400000' '-DSL_COMPONENT_CATALOG_PRESENT=1' '-DMBEDTLS_CONFIG_FILE=<sl_mbedtls_config.h>' '-DMBEDTLS_PSA_CRYPTO_CONFIG_FILE=<psa_crypto_config.h>' '-DSL_RAIL_LIB_MULTIPROTOCOL_SUPPORT=0' '-DSL_RAIL_UTIL_PA_CONFIG_HEADER=<sl_rail_util_pa_config.h>' '-DSLI_RADIOAES_REQUIRES_MASKING=1' -I"/Users/mafaneh/Projects/ble-mastery-training/le-foundations-track/9_advanced/bt-pawr-advertiser/config" -I"/Users/mafaneh/Projects/ble-mastery-training/le-foundations-track/9_advanced/bt-pawr-advertiser/config/btconf" -I"/Users/mafaneh/Projects/ble-mastery-training/le-foundations-track/9_advanced/bt-pawr-advertiser/autogen" -I"/Users/mafaneh/Projects/ble-mastery-training/le-foundations-track/9_advanced/bt-pawr-advertiser" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//platform/Device/SiliconLabs/EFR32MG22/Include" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//app/common/util/app_assert" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//app/common/util/app_button_press" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//app/common/util/app_log" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//platform/common/inc" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//protocol/bluetooth/bgcommon/inc" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//protocol/bluetooth/inc" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//protocol/bluetooth/bgstack/ll/inc" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//hardware/board/inc" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//platform/driver/button/inc" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//platform/CMSIS/Core/Include" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//hardware/driver/configuration_over_swo/inc" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//platform/security/sl_component/sl_cryptoacc_library/include" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//platform/security/sl_component/sl_cryptoacc_library/src" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//platform/driver/debug/inc" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//platform/service/device_init/inc" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//platform/emdrv/dmadrv/inc" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//platform/middleware/glib/dmd" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//platform/middleware/glib" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//platform/emdrv/common/inc" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//platform/emlib/inc" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//app/bluetooth/common/gatt_service_device_information" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//platform/middleware/glib/glib" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//platform/emdrv/gpiointerrupt/inc" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//platform/service/iostream/inc" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//hardware/driver/memlcd/src/ls013b7dh03" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//platform/security/sl_component/sl_mbedtls_support/config" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//platform/security/sl_component/sl_mbedtls_support/config/preset" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//platform/security/sl_component/sl_mbedtls_support/inc" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//util/third_party/mbedtls/include" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//util/third_party/mbedtls/library" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//hardware/driver/memlcd/inc" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//hardware/driver/memlcd/inc/memlcd_usart" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//platform/service/mpu/inc" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//hardware/driver/mx25_flash_shutdown/inc/sl_mx25_flash_shutdown_usart" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//platform/emdrv/nvm3/inc" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//platform/service/power_manager/inc" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//platform/security/sl_component/sl_psa_driver/inc" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//platform/radio/rail_lib/common" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//platform/radio/rail_lib/protocol/ble" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//platform/radio/rail_lib/protocol/ieee802154" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//platform/radio/rail_lib/protocol/wmbus" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//platform/radio/rail_lib/protocol/zwave" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//platform/radio/rail_lib/chip/efr32/efr32xg2x" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//platform/radio/rail_lib/protocol/sidewalk" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//platform/radio/rail_lib/plugin/pa-conversions" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//platform/radio/rail_lib/plugin/pa-conversions/efr32xg22" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//platform/radio/rail_lib/plugin/rail_util_power_manager_init" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//platform/security/sl_component/se_manager/inc" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//platform/security/sl_component/se_manager/src" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//util/silicon_labs/silabs_core/memory_manager" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//platform/common/toolchain/inc" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//platform/service/system/inc" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//platform/service/sleeptimer/inc" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//platform/security/sl_component/sl_protocol_crypto/src" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//platform/emdrv/tempdrv/inc" -I"/Users/mafaneh/SimplicityStudio/SDKs/gecko_sdk_3//platform/service/udelay/inc" -Os -Wall -Wextra -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mcmse --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"gecko_sdk_4.4.2/app/common/util/app_button_press/app_button_press.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


