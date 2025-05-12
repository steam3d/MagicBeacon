#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct {
    uint8_t address[6];
    uint8_t payload[27];
    uint8_t payload_length;
} LeData;

void ble_start_advertising(LeData* data);

void ble_stop_advertising(void);

void ble_update_payload(const LeData* data);