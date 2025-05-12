#include "ble.h"
#include <furi.h>
#include <furi_hal.h>
#include "utils.h"

#define TAG "magic_beacon"

int common_update_payload(const LeData* data) {
    const uint8_t header_data[] = {
        data->payload_length + 3,
        0xFF,
        0x4C,
        0x00,
    };
    size_t header_size = sizeof(header_data);

    if(header_size + data->payload_length > EXTRA_BEACON_MAX_DATA_SIZE) {
        FURI_LOG_E(TAG, "Payload size too large: %u\n", header_size + data->payload_length);
        return -1;
    }

    uint8_t combined_data[header_size + data->payload_length];
    memcpy(combined_data, header_data, header_size);
    memcpy(combined_data + header_size, data->payload, data->payload_length);

    furi_check(furi_hal_bt_extra_beacon_set_data(combined_data, sizeof(combined_data)));
    return 0;
}

void ble_update_payload(const LeData* data) {
    if(furi_hal_bt_extra_beacon_is_active()) {
        common_update_payload(data);
    };
}

void ble_start_advertising(LeData* data) {
    furi_hal_bt_extra_beacon_stop();

    GapExtraBeaconConfig config = {
        .min_adv_interval_ms = 50,
        .max_adv_interval_ms = 150,
        .adv_channel_map = GapAdvChannelMapAll,
        .adv_power_level = GapAdvPowerLevel_0dBm,
        .address_type = GapAddressTypePublic};

    memcpy(config.address, data->address, sizeof(config.address));
    reverse_bytes(config.address, sizeof(config.address));

    furi_check(furi_hal_bt_extra_beacon_set_config(&config));

    if(common_update_payload(data) != 0) {
        furi_hal_light_set(LightRed, 255);
        furi_delay_ms(500);
        furi_hal_light_set(LightRed, 0);
        return;
    }

    furi_check(furi_hal_bt_extra_beacon_start());

    furi_hal_light_blink_start(LightBlue, 255, 50, 150);
}

void ble_stop_advertising(void) {
    furi_hal_bt_extra_beacon_stop();
    furi_hal_light_blink_stop();
}
