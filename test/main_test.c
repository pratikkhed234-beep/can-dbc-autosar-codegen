#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "../generated/Can_Com_Generated.h"

static bool Float_Near(float a, float b, float tolerance)
{
    return fabsf(a - b) <= tolerance;
}

int main(void)
{
    printf("=====================================================\n");
    printf(" Automated Vector DBC -> AUTOSAR COM CodeGen Test\n");
    printf("=====================================================\n\n");

    /* 1. Transmitter ECU values */
    Powertrain_Data_PhysType tx_data = {
        .EngineSpeed = 2450.25f,   /* 2450.25 RPM */
        .VehicleSpeed = 82.4f,     /* 82.4 km/h */
        .EngineTemp = 92.0f,       /* 92 deg C */
        .ThrottlePosition = 45.5f, /* 45.5 % */
        .EngineStatus = 2.0f       /* 2 = RUNNING */
    };

    uint8_t can_pdu[8] = {0};

    printf("1. [ECU_Engine] Input Physical Values:\n");
    printf("   - EngineSpeed:        %6.2f rpm\n", tx_data.EngineSpeed);
    printf("   - VehicleSpeed:       %6.2f km/h\n", tx_data.VehicleSpeed);
    printf("   - EngineTemp:         %6.2f degC\n", tx_data.EngineTemp);
    printf("   - ThrottlePosition:   %6.2f %%\n", tx_data.ThrottlePosition);
    printf("   - EngineStatus:       %6.0f\n\n", tx_data.EngineStatus);

    /* 2. Pack into 8-byte CAN frame */
    Powertrain_Data_Pack(&tx_data, can_pdu);

    printf("2. [AUTOSAR COM] Serialized 8-Byte CAN PDU (CAN-ID: 0x%03X):\n", POWERTRAIN_DATA_CAN_ID);
    printf("   Payload: [ ");
    for (int i = 0; i < 8; i++) {
        printf("%02X ", can_pdu[i]);
    }
    printf("]\n\n");

    /* 3. Unpack on Receiver ECU */
    Powertrain_Data_PhysType rx_data = {0};
    Powertrain_Data_Unpack(can_pdu, &rx_data);

    printf("3. [ECU_Cluster] Unpacked Physical Values from CAN Bus:\n");
    printf("   - EngineSpeed:        %6.2f rpm\n", rx_data.EngineSpeed);
    printf("   - VehicleSpeed:       %6.2f km/h\n", rx_data.VehicleSpeed);
    printf("   - EngineTemp:         %6.2f degC\n", rx_data.EngineTemp);
    printf("   - ThrottlePosition:   %6.2f %%\n", rx_data.ThrottlePosition);
    printf("   - EngineStatus:       %6.0f\n\n", rx_data.EngineStatus);

    /* 4. Automated Verification against DBC resolution */
    assert(Float_Near(tx_data.EngineSpeed, rx_data.EngineSpeed, 0.25f));
    assert(Float_Near(tx_data.VehicleSpeed, rx_data.VehicleSpeed, 0.1f));
    assert(Float_Near(tx_data.EngineTemp, rx_data.EngineTemp, 1.0f));
    assert(Float_Near(tx_data.ThrottlePosition, rx_data.ThrottlePosition, 0.5f));
    assert((uint8_t)tx_data.EngineStatus == (uint8_t)rx_data.EngineStatus);

    printf("=====================================================\n");
    printf(" [TEST RESULT] ALL ASSERTIONS PASSED! Round-trip 100%% Valid.\n");
    printf("=====================================================\n");

    return 0;
}