#include "Si1153.h"

Si1153 si1153;

/**
 * Setup for configuration
 */
void setup() {
    uint8_t conf[4];
  
    Wire.begin();
    Serial.begin(9600);
    si1153.send_command(Si1153::RESET_SW);
    delay(50);
    // Configure CHAN_LIST, enable channel 1 and 3
    si1153.param_set(Si1153::CHAN_LIST, 0B00001111);

    /*
     * Configure timing parameters
     */
    si1153.param_set(Si1153::MEASRATE_H, 0);
    si1153.param_set(Si1153::MEASRATE_L, 1);
    si1153.param_set(Si1153::MEASCOUNT_0, 5);
    si1153.param_set(Si1153::MEASCOUNT_1, 10);
    si1153.param_set(Si1153::MEASCOUNT_2, 0);

    /*
     * Configuration for channel 1
     */
    conf[0] = 0B00000000;
    conf[1] = 0B00000011, 
    conf[2] = 0B01000000;
    conf[3] = 0B00100111;

    si1153.param_set(0x02, conf[0]);
    si1153.param_set(0x03, conf[1]);
    si1153.param_set(0x04, conf[2]);
    si1153.param_set(0x05, conf[3]);
    
    conf[0] = 0B00000000;
    conf[1] = 0B00000011, 
    conf[2] = 0B01000000;
    conf[3] = 0B01100111;

    si1153.param_set(0x06, conf[0]);
    si1153.param_set(0x07, conf[1]);
    si1153.param_set(0x08, conf[2]);
    si1153.param_set(0x09, conf[3]); 

    conf[0] = 0B00000000;
    conf[1] = 0B00000011, 
    conf[2] = 0B01000000;
    conf[3] = 0B10100111;

    si1153.param_set(0x0E, conf[0]);
    si1153.param_set(0x0F, conf[1]);
    si1153.param_set(0x10, conf[2]);
    si1153.param_set(0x11, conf[3]);

    conf[0] = 0B00000000;
    conf[1] = 0B10000011, 
    conf[2] = 0B01000000;
    conf[3] = 0B11100111;

    si1153.param_set(0x12, conf[0]);
    si1153.param_set(0x13, conf[1]);
    si1153.param_set(0x14, conf[2]);
    si1153.param_set(0x15, conf[3]);
    // Send start command
    si1153.send_command(Si1153::START);
}

/**
 * Loops and reads data from registers
 */
void loop() {
    uint8_t data[16];
    data[0] = si1153.read_register(Si1153::DEVICE_ADDRESS, Si1153::HOSTOUT_0, 1);
    data[1] = si1153.read_register(Si1153::DEVICE_ADDRESS, Si1153::HOSTOUT_1, 1);
    data[2] = si1153.read_register(Si1153::DEVICE_ADDRESS, Si1153::HOSTOUT_2, 1);
    data[3] = si1153.read_register(Si1153::DEVICE_ADDRESS, Si1153::HOSTOUT_3, 1);
    data[4] = si1153.read_register(Si1153::DEVICE_ADDRESS, Si1153::HOSTOUT_4, 1);
    data[5] = si1153.read_register(Si1153::DEVICE_ADDRESS, Si1153::HOSTOUT_5, 1);
    data[6] = si1153.read_register(Si1153::DEVICE_ADDRESS, Si1153::HOSTOUT_6, 1);
    data[7] = si1153.read_register(Si1153::DEVICE_ADDRESS, Si1153::HOSTOUT_7, 1);
    data[8] = si1153.read_register(Si1153::DEVICE_ADDRESS, Si1153::HOSTOUT_8, 1);
    data[9] = si1153.read_register(Si1153::DEVICE_ADDRESS, Si1153::HOSTOUT_9, 1);
    data[10] = si1153.read_register(Si1153::DEVICE_ADDRESS, Si1153::HOSTOUT_10, 1);
    data[11] = si1153.read_register(Si1153::DEVICE_ADDRESS, Si1153::HOSTOUT_11, 1);
    Serial.print("dist1: ");
    Serial.print(si1153.get_int_from_bytes(data, 3));
    Serial.print("\t\tdist2: ");
    Serial.print(si1153.get_int_from_bytes(data+3, 3));
    Serial.print("\t\tdist3: ");
    Serial.print(si1153.get_int_from_bytes(data+6, 3));
    Serial.print("\t\tdist4: ");
    Serial.println(si1153.get_int_from_bytes(data+9, 3));
//    data[0] = si1153.read_register(Si1153::DEVICE_ADDRESS, 0x00, 1);
//    data[1] = si1153.read_register(Si1153::DEVICE_ADDRESS, 0x01, 1);
//    data[2] = si1153.read_register(Si1153::DEVICE_ADDRESS, 0x02, 1);
//    data[3] = si1153.read_register(Si1153::DEVICE_ADDRESS, 0x03, 1);
//    data[4] = si1153.read_register(Si1153::DEVICE_ADDRESS, 0x04, 1);
//    data[5] = si1153.read_register(Si1153::DEVICE_ADDRESS, 0x0B, 1);
//    data[6] = si1153.read_register(Si1153::DEVICE_ADDRESS, 0x0F, 1);
//    Serial.print("Dev addr: 0x");
//    Serial.print(data[0], HEX);
//    Serial.print("\tHW ID: 0x0");
//    Serial.print(data[1], HEX);
//    Serial.print("\tREV ID: 0x");
//    Serial.print(data[2], HEX);
//    Serial.print("\tINFO0: ");
//    Serial.print(data[3]);
//    Serial.print("\tINFO1: ");
//    Serial.print(data[4]);
//    Serial.print("\tCOMMAND: 0x");
//    Serial.print(data[5],HEX);
//    Serial.print("\tIRQ: 0x");
//    Serial.println(data[6],HEX);
    delay(100);
}
