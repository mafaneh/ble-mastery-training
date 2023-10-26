################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../gecko_sdk_4.3.2/platform/security/sl_component/sl_mbedtls_support/src/sl_mbedtls.c \
../gecko_sdk_4.3.2/platform/security/sl_component/sl_mbedtls_support/src/sl_psa_crypto.c \
../gecko_sdk_4.3.2/platform/security/sl_component/sl_mbedtls_support/src/sli_psa_crypto.c 

OBJS += \
./gecko_sdk_4.3.2/platform/security/sl_component/sl_mbedtls_support/src/sl_mbedtls.o \
./gecko_sdk_4.3.2/platform/security/sl_component/sl_mbedtls_support/src/sl_psa_crypto.o \
./gecko_sdk_4.3.2/platform/security/sl_component/sl_mbedtls_support/src/sli_psa_crypto.o 

C_DEPS += \
./gecko_sdk_4.3.2/platform/security/sl_component/sl_mbedtls_support/src/sl_mbedtls.d \
./gecko_sdk_4.3.2/platform/security/sl_component/sl_mbedtls_support/src/sl_psa_crypto.d \
./gecko_sdk_4.3.2/platform/security/sl_component/sl_mbedtls_support/src/sli_psa_crypto.d 


# Each subdirectory must supply rules for building sources it contributes
gecko_sdk_4.3.2/platform/security/sl_component/sl_mbedtls_support/src/sl_mbedtls.o: ../gecko_sdk_4.3.2/platform/security/sl_component/sl_mbedtls_support/src/sl_mbedtls.c gecko_sdk_4.3.2/platform/security/sl_component/sl_mbedtls_support/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG24B310F1536IM48=1' '-DSL_APP_PROPERTIES=1' '-DBOOTLOADER_APPLOADER=1' '-DHARDWARE_BOARD_DEFAULT_RF_BAND_2400=1' '-DHARDWARE_BOARD_SUPPORTS_1_RF_BAND=1' '-DHARDWARE_BOARD_SUPPORTS_RF_BAND_2400=1' '-DSL_BOARD_NAME="BRD2601B"' '-DSL_BOARD_REV="A01"' '-DSL_COMPONENT_CATALOG_PRESENT=1' '-DMBEDTLS_CONFIG_FILE=<sl_mbedtls_config.h>' '-DMBEDTLS_PSA_CRYPTO_CONFIG_FILE=<psa_crypto_config.h>' '-DSL_RAIL_LIB_MULTIPROTOCOL_SUPPORT=0' '-DSL_RAIL_UTIL_PA_CONFIG_HEADER=<sl_rail_util_pa_config.h>' '-DSLI_RADIOAES_REQUIRES_MASKING=1' -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/config" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/config/btconf" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/Device/SiliconLabs/EFR32MG24/Include" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/app/common/util/app_assert" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/app/common/util/app_log" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/protocol/bluetooth/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/common/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/protocol/bluetooth/bgstack/ll/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/hardware/board/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/bootloader" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/bootloader/api" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/driver/button/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/CMSIS/Core/Include" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/hardware/driver/configuration_over_swo/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/driver/debug/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/service/device_init/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/emdrv/dmadrv/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/emdrv/common/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/emlib/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/app/bluetooth/common/gatt_service_device_information" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/emdrv/gpiointerrupt/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/service/hfxo_manager/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/app/bluetooth/common/in_place_ota_dfu" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/service/iostream/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/driver/leddrv/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/security/sl_component/sl_mbedtls_support/config" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/security/sl_component/sl_mbedtls_support/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/util/third_party/mbedtls/include" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/util/third_party/mbedtls/library" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/service/mpu/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/hardware/driver/mx25_flash_shutdown/inc/sl_mx25_flash_shutdown_usart" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/emdrv/nvm3/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/peripheral/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/service/power_manager/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/security/sl_component/sl_psa_driver/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/radio/rail_lib/common" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/radio/rail_lib/protocol/ble" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/radio/rail_lib/protocol/ieee802154" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/radio/rail_lib/protocol/wmbus" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/radio/rail_lib/protocol/zwave" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/radio/rail_lib/chip/efr32/efr32xg2x" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/radio/rail_lib/protocol/sidewalk" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/radio/rail_lib/plugin/rail_util_built_in_phys/efr32xg24" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/radio/rail_lib/plugin/pa-conversions" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/radio/rail_lib/plugin/pa-conversions/efr32xg24" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/radio/rail_lib/plugin/rail_util_power_manager_init" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/radio/rail_lib/plugin/rail_util_pti" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/security/sl_component/se_manager/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/security/sl_component/se_manager/src" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/util/silicon_labs/silabs_core/memory_manager" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/common/toolchain/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/service/system/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/service/sleeptimer/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/security/sl_component/sl_protocol_crypto/src" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/service/udelay/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/autogen" -Os -Wall -Wextra -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mcmse --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"gecko_sdk_4.3.2/platform/security/sl_component/sl_mbedtls_support/src/sl_mbedtls.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

gecko_sdk_4.3.2/platform/security/sl_component/sl_mbedtls_support/src/sl_psa_crypto.o: ../gecko_sdk_4.3.2/platform/security/sl_component/sl_mbedtls_support/src/sl_psa_crypto.c gecko_sdk_4.3.2/platform/security/sl_component/sl_mbedtls_support/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG24B310F1536IM48=1' '-DSL_APP_PROPERTIES=1' '-DBOOTLOADER_APPLOADER=1' '-DHARDWARE_BOARD_DEFAULT_RF_BAND_2400=1' '-DHARDWARE_BOARD_SUPPORTS_1_RF_BAND=1' '-DHARDWARE_BOARD_SUPPORTS_RF_BAND_2400=1' '-DSL_BOARD_NAME="BRD2601B"' '-DSL_BOARD_REV="A01"' '-DSL_COMPONENT_CATALOG_PRESENT=1' '-DMBEDTLS_CONFIG_FILE=<sl_mbedtls_config.h>' '-DMBEDTLS_PSA_CRYPTO_CONFIG_FILE=<psa_crypto_config.h>' '-DSL_RAIL_LIB_MULTIPROTOCOL_SUPPORT=0' '-DSL_RAIL_UTIL_PA_CONFIG_HEADER=<sl_rail_util_pa_config.h>' '-DSLI_RADIOAES_REQUIRES_MASKING=1' -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/config" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/config/btconf" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/Device/SiliconLabs/EFR32MG24/Include" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/app/common/util/app_assert" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/app/common/util/app_log" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/protocol/bluetooth/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/common/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/protocol/bluetooth/bgstack/ll/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/hardware/board/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/bootloader" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/bootloader/api" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/driver/button/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/CMSIS/Core/Include" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/hardware/driver/configuration_over_swo/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/driver/debug/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/service/device_init/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/emdrv/dmadrv/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/emdrv/common/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/emlib/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/app/bluetooth/common/gatt_service_device_information" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/emdrv/gpiointerrupt/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/service/hfxo_manager/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/app/bluetooth/common/in_place_ota_dfu" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/service/iostream/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/driver/leddrv/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/security/sl_component/sl_mbedtls_support/config" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/security/sl_component/sl_mbedtls_support/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/util/third_party/mbedtls/include" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/util/third_party/mbedtls/library" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/service/mpu/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/hardware/driver/mx25_flash_shutdown/inc/sl_mx25_flash_shutdown_usart" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/emdrv/nvm3/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/peripheral/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/service/power_manager/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/security/sl_component/sl_psa_driver/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/radio/rail_lib/common" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/radio/rail_lib/protocol/ble" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/radio/rail_lib/protocol/ieee802154" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/radio/rail_lib/protocol/wmbus" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/radio/rail_lib/protocol/zwave" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/radio/rail_lib/chip/efr32/efr32xg2x" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/radio/rail_lib/protocol/sidewalk" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/radio/rail_lib/plugin/rail_util_built_in_phys/efr32xg24" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/radio/rail_lib/plugin/pa-conversions" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/radio/rail_lib/plugin/pa-conversions/efr32xg24" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/radio/rail_lib/plugin/rail_util_power_manager_init" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/radio/rail_lib/plugin/rail_util_pti" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/security/sl_component/se_manager/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/security/sl_component/se_manager/src" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/util/silicon_labs/silabs_core/memory_manager" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/common/toolchain/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/service/system/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/service/sleeptimer/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/security/sl_component/sl_protocol_crypto/src" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/service/udelay/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/autogen" -Os -Wall -Wextra -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mcmse --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"gecko_sdk_4.3.2/platform/security/sl_component/sl_mbedtls_support/src/sl_psa_crypto.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

gecko_sdk_4.3.2/platform/security/sl_component/sl_mbedtls_support/src/sli_psa_crypto.o: ../gecko_sdk_4.3.2/platform/security/sl_component/sl_mbedtls_support/src/sli_psa_crypto.c gecko_sdk_4.3.2/platform/security/sl_component/sl_mbedtls_support/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEFR32MG24B310F1536IM48=1' '-DSL_APP_PROPERTIES=1' '-DBOOTLOADER_APPLOADER=1' '-DHARDWARE_BOARD_DEFAULT_RF_BAND_2400=1' '-DHARDWARE_BOARD_SUPPORTS_1_RF_BAND=1' '-DHARDWARE_BOARD_SUPPORTS_RF_BAND_2400=1' '-DSL_BOARD_NAME="BRD2601B"' '-DSL_BOARD_REV="A01"' '-DSL_COMPONENT_CATALOG_PRESENT=1' '-DMBEDTLS_CONFIG_FILE=<sl_mbedtls_config.h>' '-DMBEDTLS_PSA_CRYPTO_CONFIG_FILE=<psa_crypto_config.h>' '-DSL_RAIL_LIB_MULTIPROTOCOL_SUPPORT=0' '-DSL_RAIL_UTIL_PA_CONFIG_HEADER=<sl_rail_util_pa_config.h>' '-DSLI_RADIOAES_REQUIRES_MASKING=1' -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/config" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/config/btconf" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/Device/SiliconLabs/EFR32MG24/Include" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/app/common/util/app_assert" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/app/common/util/app_log" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/protocol/bluetooth/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/common/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/protocol/bluetooth/bgstack/ll/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/hardware/board/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/bootloader" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/bootloader/api" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/driver/button/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/CMSIS/Core/Include" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/hardware/driver/configuration_over_swo/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/driver/debug/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/service/device_init/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/emdrv/dmadrv/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/emdrv/common/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/emlib/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/app/bluetooth/common/gatt_service_device_information" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/emdrv/gpiointerrupt/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/service/hfxo_manager/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/app/bluetooth/common/in_place_ota_dfu" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/service/iostream/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/driver/leddrv/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/security/sl_component/sl_mbedtls_support/config" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/security/sl_component/sl_mbedtls_support/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/util/third_party/mbedtls/include" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/util/third_party/mbedtls/library" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/service/mpu/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/hardware/driver/mx25_flash_shutdown/inc/sl_mx25_flash_shutdown_usart" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/emdrv/nvm3/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/peripheral/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/service/power_manager/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/security/sl_component/sl_psa_driver/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/radio/rail_lib/common" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/radio/rail_lib/protocol/ble" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/radio/rail_lib/protocol/ieee802154" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/radio/rail_lib/protocol/wmbus" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/radio/rail_lib/protocol/zwave" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/radio/rail_lib/chip/efr32/efr32xg2x" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/radio/rail_lib/protocol/sidewalk" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/radio/rail_lib/plugin/rail_util_built_in_phys/efr32xg24" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/radio/rail_lib/plugin/pa-conversions" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/radio/rail_lib/plugin/pa-conversions/efr32xg24" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/radio/rail_lib/plugin/rail_util_power_manager_init" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/radio/rail_lib/plugin/rail_util_pti" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/security/sl_component/se_manager/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/security/sl_component/se_manager/src" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/util/silicon_labs/silabs_core/memory_manager" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/common/toolchain/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/service/system/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/service/sleeptimer/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/security/sl_component/sl_protocol_crypto/src" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/gecko_sdk_4.3.2/platform/service/udelay/inc" -I"/Users/mafaneh/ble-mastery-training-original/le-foundations-track/3_gatt/bt-gatt-data-transfer/autogen" -Os -Wall -Wextra -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mcmse --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"gecko_sdk_4.3.2/platform/security/sl_component/sl_mbedtls_support/src/sli_psa_crypto.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


