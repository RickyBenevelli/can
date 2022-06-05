#ifndef secondary_NETWORK_H
#define secondary_NETWORK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>
#include <stdbool.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

#ifndef CANLIB_ASSERTS
#define CANLIB_ASSERTS

static_assert(sizeof(float) == 4, "canlib: sizeof(float) != 4 BYTES");
static_assert(sizeof(double) == 8, "canlib: sizeof(double) != 8 BYTES");

/* Is it little endian?

          ████████                        ████████
        ██        ██                  ████        ████
      ██▒▒▒▒        ██              ██▒▒              ██
    ██▒▒▒▒▒▒      ▒▒▒▒██          ██▒▒▒▒            ▒▒▒▒██
    ██▒▒▒▒▒▒      ▒▒▒▒██          ██▒▒▒▒  ▒▒▒▒▒▒    ▒▒▒▒██
  ██  ▒▒▒▒        ▒▒▒▒▒▒██      ██▒▒▒▒  ▒▒▒▒▒▒▒▒▒▒  ▒▒▒▒▒▒██
  ██                ▒▒▒▒██      ██      ▒▒▒▒▒▒▒▒▒▒    ▒▒▒▒██
██▒▒      ▒▒▒▒▒▒          ██    ██      ▒▒▒▒▒▒▒▒▒▒        ██
██      ▒▒▒▒▒▒▒▒▒▒        ██    ██▒▒      ▒▒▒▒▒▒          ██
██      ▒▒▒▒▒▒▒▒▒▒    ▒▒▒▒██      ██                ▒▒▒▒██
██▒▒▒▒  ▒▒▒▒▒▒▒▒▒▒  ▒▒▒▒▒▒██      ██  ▒▒▒▒        ▒▒▒▒▒▒██
  ██▒▒▒▒  ▒▒▒▒▒▒    ▒▒▒▒██          ██▒▒▒▒▒▒      ▒▒▒▒██
  ██▒▒▒▒            ▒▒▒▒██          ██▒▒▒▒▒▒      ▒▒▒▒██
    ██▒▒              ██              ██▒▒▒▒        ██
      ████        ████                  ██        ██
          ████████                        ████████

                                    Or is it big endian? */
#ifndef __CANLIB_ENDIAN_ORDER
    #define __CANLIB_ENDIAN_ORDER 1094861636L // "ABCD"
#endif
#if !defined(__CANLIB_LITTLE_ENDIAN) && !defined(__CANLIB_BIG_ENDIAN) && !defined(__CANLIB_PDP_ENDIAN)
    #if __CANLIB_ENDIAN_ORDER==0x41424344UL
        #define __CANLIB_LITTLE_ENDIAN
    #elif __CANLIB_ENDIAN_ORDER==0x44434241UL
        #define __CANLIB_BIG_ENDIAN
    #elif __CANLIB_ENDIAN_ORDER==0x42414443UL
        #define __CANLIB_PDP_ENDIAN
    #else
        #error "canlib: endianess not supported"
    #endif
#endif

#ifndef __CANLIB_LITTLE_ENDIAN
    #error "canlib: endianess not supported"
#endif

#endif // CANLIB_ASSERTS

#ifndef CANLIB_SHARED
#define CANLIB_SHARED

/* We know it's PACKING but PARKING sounds a bit better ;) */
#if defined(__MINGW32__)
#define CANLIB_PARKING __attribute__((__gcc_struct__, __packed__)) // , __aligned__(1)))
#else
#define CANLIB_PARKING __attribute__((__packed__)) // , __aligned__(1)))
#endif

#define PRIf32 "f"
#define PRIf64 "f"

#endif // CANLIB_SHARED

#ifndef CANLIB_BITMASK_UTILS
#define CANLIB_BITMASK_UTILS

#define CANLIB_BITMASK_TYPE uint8_t
#define CANLIB_BITMASK_TYPE_BITS 8

#define CANLIB_BITMASK_ARRAY(b) (1 << ((b) % CANLIB_BITMASK_TYPE_BITS))
#define CANLIB_BITSLOT_ARRAY(b) ((b) / CANLIB_BITMASK_TYPE_BITS)
#define CANLIB_BITSET_ARRAY(a, b) ((a)[CANLIB_BITSLOT_ARRAY(b)] |= CANLIB_BITMASK_ARRAY(b))
#define CANLIB_BITCLEAR_ARRAY(a, b) ((a)[CANLIB_BITSLOT_ARRAY(b)] &= ~CANLIB_BITMASK_ARRAY(b))
#define CANLIB_BITTEST_ARRAY(a, b) ((a)[CANLIB_BITSLOT_ARRAY(b)] & CANLIB_BITMASK_ARRAY(b))
#define CANLIB_BITNSLOTS_ARRAY(nb) ((nb + CANLIB_BITMASK_TYPE_BITS - 1) / CANLIB_BITMASK_TYPE_BITS)

#define CANLIB_BITMASK(b) (1 << (b))
#define CANLIB_BITSET(a, b) ((a) |= CANLIB_BITMASK(b))
#define CANLIB_BITCLEAR(a, b) ((a) &= ~CANLIB_BITMASK(b))
#define CANLIB_BITTEST(a, b) ((a) & CANLIB_BITMASK(b))

#endif // CANLIB_BITMASK_UTILS

#ifndef CANLIB_SEPARATOR
#define CANLIB_SEPARATOR ","
#endif // CANLIB_SEPARATOR

#ifndef CANLIB_MESSAGE_ID_TYPE
#define CANLIB_MESSAGE_ID_TYPE
typedef uint16_t canlib_message_id;
#endif // CANLIB_MESSAGE_ID_TYPE

// Info

#define secondary_NUMBER_OF_MESSAGES 24

// Custom types

#define secondary_int8 int8_t
#define secondary_uint8 uint8_t
#define secondary_int16 int16_t
#define secondary_uint16 uint16_t
#define secondary_int32 int32_t
#define secondary_uint32 uint32_t
#define secondary_int64 int64_t
#define secondary_uint64 uint64_t
#define secondary_float32 float
#define secondary_float64 double
#define secondary_bool bool
#define secondary_byte_size uint32_t

typedef union {
    secondary_uint8 bytes[4];
    secondary_float32 value;
} secondary_float32_helper;

typedef union {
    secondary_uint8 bytes[8];
    secondary_float64 value;
} secondary_float64_helper;

#ifdef __cplusplus
#define secondary_float32_to_bytes(float, index) (reinterpret_cast<secondary_uint8*>(&((float)))[(index)])
#else
#define secondary_float32_to_bytes(float, index) ({(secondary_float32_helper)secondary_float32_helper.value = (f)}.bytes[(index)])
#endif

typedef struct {
    uint16_t id;
    void* raw_message;
    void* message;
} secondary_devices[secondary_NUMBER_OF_MESSAGES];

// ============== SIZES ============== //


#define secondary_IMU_ANGULAR_RATE_SIZE 6
#define secondary_IMU_ACCELERATION_SIZE 6
#define secondary_IRTS_FL_0_SIZE 8
#define secondary_IRTS_FL_1_SIZE 8
#define secondary_IRTS_FL_2_SIZE 8
#define secondary_IRTS_FL_3_SIZE 8
#define secondary_IRTS_FR_0_SIZE 8
#define secondary_IRTS_FR_1_SIZE 8
#define secondary_IRTS_FR_2_SIZE 8
#define secondary_IRTS_FR_3_SIZE 8
#define secondary_IRTS_RL_0_SIZE 8
#define secondary_IRTS_RL_1_SIZE 8
#define secondary_IRTS_RL_2_SIZE 8
#define secondary_IRTS_RL_3_SIZE 8
#define secondary_IRTS_RR_0_SIZE 8
#define secondary_IRTS_RR_1_SIZE 8
#define secondary_IRTS_RR_2_SIZE 8
#define secondary_IRTS_RR_3_SIZE 8
#define secondary_GPS_COORDS_SIZE 8
#define secondary_GPS_SPEED_SIZE 2
#define secondary_LAP_COUNT_SIZE 5
#define secondary_PEDALS_OUTPUT_SIZE 5
#define secondary_CONTROL_OUTPUT_SIZE 8
#define secondary_STEERING_ANGLE_SIZE 4

// ============== BIT SETS ============== //



// ============== ENUMS ============== //



// Structs



typedef struct CANLIB_PARKING {
    secondary_uint16 ang_rate_x;
    secondary_uint16 ang_rate_y;
    secondary_uint16 ang_rate_z;
#ifdef CANLIB_TIMESTAMP
    secondary_uint64 _timestamp;
#endif // CANLIB_TIMESTAMP
} secondary_message_IMU_ANGULAR_RATE;


typedef struct CANLIB_PARKING {
    secondary_uint16 accel_x;
    secondary_uint16 accel_y;
    secondary_uint16 accel_z;
#ifdef CANLIB_TIMESTAMP
    secondary_uint64 _timestamp;
#endif // CANLIB_TIMESTAMP
} secondary_message_IMU_ACCELERATION;


typedef struct CANLIB_PARKING {
    secondary_uint16 channel1;
    secondary_uint16 channel2;
    secondary_uint16 channel3;
    secondary_uint16 channel4;
#ifdef CANLIB_TIMESTAMP
    secondary_uint64 _timestamp;
#endif // CANLIB_TIMESTAMP
} secondary_message_IRTS_FL_0;


typedef struct CANLIB_PARKING {
    secondary_uint16 channel5;
    secondary_uint16 channel6;
    secondary_uint16 channel7;
    secondary_uint16 channel8;
#ifdef CANLIB_TIMESTAMP
    secondary_uint64 _timestamp;
#endif // CANLIB_TIMESTAMP
} secondary_message_IRTS_FL_1;


typedef struct CANLIB_PARKING {
    secondary_uint16 channel9;
    secondary_uint16 channel10;
    secondary_uint16 channel11;
    secondary_uint16 channel12;
#ifdef CANLIB_TIMESTAMP
    secondary_uint64 _timestamp;
#endif // CANLIB_TIMESTAMP
} secondary_message_IRTS_FL_2;


typedef struct CANLIB_PARKING {
    secondary_uint16 channel13;
    secondary_uint16 channel14;
    secondary_uint16 channel15;
    secondary_uint16 channel16;
#ifdef CANLIB_TIMESTAMP
    secondary_uint64 _timestamp;
#endif // CANLIB_TIMESTAMP
} secondary_message_IRTS_FL_3;


typedef struct CANLIB_PARKING {
    secondary_uint16 channel1;
    secondary_uint16 channel2;
    secondary_uint16 channel3;
    secondary_uint16 channel4;
#ifdef CANLIB_TIMESTAMP
    secondary_uint64 _timestamp;
#endif // CANLIB_TIMESTAMP
} secondary_message_IRTS_FR_0;


typedef struct CANLIB_PARKING {
    secondary_uint16 channel5;
    secondary_uint16 channel6;
    secondary_uint16 channel7;
    secondary_uint16 channel8;
#ifdef CANLIB_TIMESTAMP
    secondary_uint64 _timestamp;
#endif // CANLIB_TIMESTAMP
} secondary_message_IRTS_FR_1;


typedef struct CANLIB_PARKING {
    secondary_uint16 channel9;
    secondary_uint16 channel10;
    secondary_uint16 channel11;
    secondary_uint16 channel12;
#ifdef CANLIB_TIMESTAMP
    secondary_uint64 _timestamp;
#endif // CANLIB_TIMESTAMP
} secondary_message_IRTS_FR_2;


typedef struct CANLIB_PARKING {
    secondary_uint16 channel13;
    secondary_uint16 channel14;
    secondary_uint16 channel15;
    secondary_uint16 channel16;
#ifdef CANLIB_TIMESTAMP
    secondary_uint64 _timestamp;
#endif // CANLIB_TIMESTAMP
} secondary_message_IRTS_FR_3;


typedef struct CANLIB_PARKING {
    secondary_uint16 channel1;
    secondary_uint16 channel2;
    secondary_uint16 channel3;
    secondary_uint16 channel4;
#ifdef CANLIB_TIMESTAMP
    secondary_uint64 _timestamp;
#endif // CANLIB_TIMESTAMP
} secondary_message_IRTS_RL_0;


typedef struct CANLIB_PARKING {
    secondary_uint16 channel5;
    secondary_uint16 channel6;
    secondary_uint16 channel7;
    secondary_uint16 channel8;
#ifdef CANLIB_TIMESTAMP
    secondary_uint64 _timestamp;
#endif // CANLIB_TIMESTAMP
} secondary_message_IRTS_RL_1;


typedef struct CANLIB_PARKING {
    secondary_uint16 channel9;
    secondary_uint16 channel10;
    secondary_uint16 channel11;
    secondary_uint16 channel12;
#ifdef CANLIB_TIMESTAMP
    secondary_uint64 _timestamp;
#endif // CANLIB_TIMESTAMP
} secondary_message_IRTS_RL_2;


typedef struct CANLIB_PARKING {
    secondary_uint16 channel13;
    secondary_uint16 channel14;
    secondary_uint16 channel15;
    secondary_uint16 channel16;
#ifdef CANLIB_TIMESTAMP
    secondary_uint64 _timestamp;
#endif // CANLIB_TIMESTAMP
} secondary_message_IRTS_RL_3;


typedef struct CANLIB_PARKING {
    secondary_uint16 channel1;
    secondary_uint16 channel2;
    secondary_uint16 channel3;
    secondary_uint16 channel4;
#ifdef CANLIB_TIMESTAMP
    secondary_uint64 _timestamp;
#endif // CANLIB_TIMESTAMP
} secondary_message_IRTS_RR_0;


typedef struct CANLIB_PARKING {
    secondary_uint16 channel5;
    secondary_uint16 channel6;
    secondary_uint16 channel7;
    secondary_uint16 channel8;
#ifdef CANLIB_TIMESTAMP
    secondary_uint64 _timestamp;
#endif // CANLIB_TIMESTAMP
} secondary_message_IRTS_RR_1;


typedef struct CANLIB_PARKING {
    secondary_uint16 channel9;
    secondary_uint16 channel10;
    secondary_uint16 channel11;
    secondary_uint16 channel12;
#ifdef CANLIB_TIMESTAMP
    secondary_uint64 _timestamp;
#endif // CANLIB_TIMESTAMP
} secondary_message_IRTS_RR_2;


typedef struct CANLIB_PARKING {
    secondary_uint16 channel13;
    secondary_uint16 channel14;
    secondary_uint16 channel15;
    secondary_uint16 channel16;
#ifdef CANLIB_TIMESTAMP
    secondary_uint64 _timestamp;
#endif // CANLIB_TIMESTAMP
} secondary_message_IRTS_RR_3;


typedef struct CANLIB_PARKING {
    secondary_float32 latitude;
    secondary_float32 longitude;
#ifdef CANLIB_TIMESTAMP
    secondary_uint64 _timestamp;
#endif // CANLIB_TIMESTAMP
} secondary_message_GPS_COORDS;


typedef struct CANLIB_PARKING {
    secondary_uint16 speed;
#ifdef CANLIB_TIMESTAMP
    secondary_uint64 _timestamp;
#endif // CANLIB_TIMESTAMP
} secondary_message_GPS_SPEED;


typedef struct CANLIB_PARKING {
    secondary_uint32 timestamp;
    secondary_uint8 lap_count;
#ifdef CANLIB_TIMESTAMP
    secondary_uint64 _timestamp;
#endif // CANLIB_TIMESTAMP
} secondary_message_LAP_COUNT;

typedef struct CANLIB_PARKING {
    secondary_float32 bse_front;
    secondary_float32 bse_rear;
    secondary_uint8 apps;
#ifdef CANLIB_TIMESTAMP
    secondary_uint64 _timestamp;
#endif // CANLIB_TIMESTAMP
} secondary_message_PEDALS_OUTPUT_conversion;

typedef struct CANLIB_PARKING {
    secondary_uint16 bse_front;
    secondary_uint16 bse_rear;
    secondary_uint8 apps;
#ifdef CANLIB_TIMESTAMP
    secondary_uint64 _timestamp;
#endif // CANLIB_TIMESTAMP
} secondary_message_PEDALS_OUTPUT;


typedef struct CANLIB_PARKING {
    secondary_float32 right;
    secondary_float32 left;
#ifdef CANLIB_TIMESTAMP
    secondary_uint64 _timestamp;
#endif // CANLIB_TIMESTAMP
} secondary_message_CONTROL_OUTPUT;


typedef struct CANLIB_PARKING {
    secondary_float32 angle;
#ifdef CANLIB_TIMESTAMP
    secondary_uint64 _timestamp;
#endif // CANLIB_TIMESTAMP
} secondary_message_STEERING_ANGLE;



// ============== IMU_ANGULAR_RATE ============== //

secondary_byte_size secondary_serialize_IMU_ANGULAR_RATE(
    uint8_t* data,
    secondary_uint16 ang_rate_x,
    secondary_uint16 ang_rate_y,
    secondary_uint16 ang_rate_z
);
secondary_byte_size secondary_serialize_struct_IMU_ANGULAR_RATE(
    uint8_t* data,
    secondary_message_IMU_ANGULAR_RATE* message
);
void secondary_deserialize_IMU_ANGULAR_RATE(
    secondary_message_IMU_ANGULAR_RATE* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 timestamp
#endif // CANLIB_TIMESTAMP
);
int secondary_to_string_IMU_ANGULAR_RATE(secondary_message_IMU_ANGULAR_RATE* message, char* buffer);
int secondary_fields_IMU_ANGULAR_RATE(char* buffer);
int secondary_to_string_file_IMU_ANGULAR_RATE(secondary_message_IMU_ANGULAR_RATE* message, FILE* buffer);
int secondary_fields_file_IMU_ANGULAR_RATE(FILE* buffer);


// ============== IMU_ACCELERATION ============== //

secondary_byte_size secondary_serialize_IMU_ACCELERATION(
    uint8_t* data,
    secondary_uint16 accel_x,
    secondary_uint16 accel_y,
    secondary_uint16 accel_z
);
secondary_byte_size secondary_serialize_struct_IMU_ACCELERATION(
    uint8_t* data,
    secondary_message_IMU_ACCELERATION* message
);
void secondary_deserialize_IMU_ACCELERATION(
    secondary_message_IMU_ACCELERATION* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 timestamp
#endif // CANLIB_TIMESTAMP
);
int secondary_to_string_IMU_ACCELERATION(secondary_message_IMU_ACCELERATION* message, char* buffer);
int secondary_fields_IMU_ACCELERATION(char* buffer);
int secondary_to_string_file_IMU_ACCELERATION(secondary_message_IMU_ACCELERATION* message, FILE* buffer);
int secondary_fields_file_IMU_ACCELERATION(FILE* buffer);


// ============== IRTS_FL_0 ============== //

secondary_byte_size secondary_serialize_IRTS_FL_0(
    uint8_t* data,
    secondary_uint16 channel1,
    secondary_uint16 channel2,
    secondary_uint16 channel3,
    secondary_uint16 channel4
);
secondary_byte_size secondary_serialize_struct_IRTS_FL_0(
    uint8_t* data,
    secondary_message_IRTS_FL_0* message
);
void secondary_deserialize_IRTS_FL_0(
    secondary_message_IRTS_FL_0* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 timestamp
#endif // CANLIB_TIMESTAMP
);
int secondary_to_string_IRTS_FL_0(secondary_message_IRTS_FL_0* message, char* buffer);
int secondary_fields_IRTS_FL_0(char* buffer);
int secondary_to_string_file_IRTS_FL_0(secondary_message_IRTS_FL_0* message, FILE* buffer);
int secondary_fields_file_IRTS_FL_0(FILE* buffer);


// ============== IRTS_FL_1 ============== //

secondary_byte_size secondary_serialize_IRTS_FL_1(
    uint8_t* data,
    secondary_uint16 channel5,
    secondary_uint16 channel6,
    secondary_uint16 channel7,
    secondary_uint16 channel8
);
secondary_byte_size secondary_serialize_struct_IRTS_FL_1(
    uint8_t* data,
    secondary_message_IRTS_FL_1* message
);
void secondary_deserialize_IRTS_FL_1(
    secondary_message_IRTS_FL_1* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 timestamp
#endif // CANLIB_TIMESTAMP
);
int secondary_to_string_IRTS_FL_1(secondary_message_IRTS_FL_1* message, char* buffer);
int secondary_fields_IRTS_FL_1(char* buffer);
int secondary_to_string_file_IRTS_FL_1(secondary_message_IRTS_FL_1* message, FILE* buffer);
int secondary_fields_file_IRTS_FL_1(FILE* buffer);


// ============== IRTS_FL_2 ============== //

secondary_byte_size secondary_serialize_IRTS_FL_2(
    uint8_t* data,
    secondary_uint16 channel9,
    secondary_uint16 channel10,
    secondary_uint16 channel11,
    secondary_uint16 channel12
);
secondary_byte_size secondary_serialize_struct_IRTS_FL_2(
    uint8_t* data,
    secondary_message_IRTS_FL_2* message
);
void secondary_deserialize_IRTS_FL_2(
    secondary_message_IRTS_FL_2* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 timestamp
#endif // CANLIB_TIMESTAMP
);
int secondary_to_string_IRTS_FL_2(secondary_message_IRTS_FL_2* message, char* buffer);
int secondary_fields_IRTS_FL_2(char* buffer);
int secondary_to_string_file_IRTS_FL_2(secondary_message_IRTS_FL_2* message, FILE* buffer);
int secondary_fields_file_IRTS_FL_2(FILE* buffer);


// ============== IRTS_FL_3 ============== //

secondary_byte_size secondary_serialize_IRTS_FL_3(
    uint8_t* data,
    secondary_uint16 channel13,
    secondary_uint16 channel14,
    secondary_uint16 channel15,
    secondary_uint16 channel16
);
secondary_byte_size secondary_serialize_struct_IRTS_FL_3(
    uint8_t* data,
    secondary_message_IRTS_FL_3* message
);
void secondary_deserialize_IRTS_FL_3(
    secondary_message_IRTS_FL_3* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 timestamp
#endif // CANLIB_TIMESTAMP
);
int secondary_to_string_IRTS_FL_3(secondary_message_IRTS_FL_3* message, char* buffer);
int secondary_fields_IRTS_FL_3(char* buffer);
int secondary_to_string_file_IRTS_FL_3(secondary_message_IRTS_FL_3* message, FILE* buffer);
int secondary_fields_file_IRTS_FL_3(FILE* buffer);


// ============== IRTS_FR_0 ============== //

secondary_byte_size secondary_serialize_IRTS_FR_0(
    uint8_t* data,
    secondary_uint16 channel1,
    secondary_uint16 channel2,
    secondary_uint16 channel3,
    secondary_uint16 channel4
);
secondary_byte_size secondary_serialize_struct_IRTS_FR_0(
    uint8_t* data,
    secondary_message_IRTS_FR_0* message
);
void secondary_deserialize_IRTS_FR_0(
    secondary_message_IRTS_FR_0* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 timestamp
#endif // CANLIB_TIMESTAMP
);
int secondary_to_string_IRTS_FR_0(secondary_message_IRTS_FR_0* message, char* buffer);
int secondary_fields_IRTS_FR_0(char* buffer);
int secondary_to_string_file_IRTS_FR_0(secondary_message_IRTS_FR_0* message, FILE* buffer);
int secondary_fields_file_IRTS_FR_0(FILE* buffer);


// ============== IRTS_FR_1 ============== //

secondary_byte_size secondary_serialize_IRTS_FR_1(
    uint8_t* data,
    secondary_uint16 channel5,
    secondary_uint16 channel6,
    secondary_uint16 channel7,
    secondary_uint16 channel8
);
secondary_byte_size secondary_serialize_struct_IRTS_FR_1(
    uint8_t* data,
    secondary_message_IRTS_FR_1* message
);
void secondary_deserialize_IRTS_FR_1(
    secondary_message_IRTS_FR_1* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 timestamp
#endif // CANLIB_TIMESTAMP
);
int secondary_to_string_IRTS_FR_1(secondary_message_IRTS_FR_1* message, char* buffer);
int secondary_fields_IRTS_FR_1(char* buffer);
int secondary_to_string_file_IRTS_FR_1(secondary_message_IRTS_FR_1* message, FILE* buffer);
int secondary_fields_file_IRTS_FR_1(FILE* buffer);


// ============== IRTS_FR_2 ============== //

secondary_byte_size secondary_serialize_IRTS_FR_2(
    uint8_t* data,
    secondary_uint16 channel9,
    secondary_uint16 channel10,
    secondary_uint16 channel11,
    secondary_uint16 channel12
);
secondary_byte_size secondary_serialize_struct_IRTS_FR_2(
    uint8_t* data,
    secondary_message_IRTS_FR_2* message
);
void secondary_deserialize_IRTS_FR_2(
    secondary_message_IRTS_FR_2* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 timestamp
#endif // CANLIB_TIMESTAMP
);
int secondary_to_string_IRTS_FR_2(secondary_message_IRTS_FR_2* message, char* buffer);
int secondary_fields_IRTS_FR_2(char* buffer);
int secondary_to_string_file_IRTS_FR_2(secondary_message_IRTS_FR_2* message, FILE* buffer);
int secondary_fields_file_IRTS_FR_2(FILE* buffer);


// ============== IRTS_FR_3 ============== //

secondary_byte_size secondary_serialize_IRTS_FR_3(
    uint8_t* data,
    secondary_uint16 channel13,
    secondary_uint16 channel14,
    secondary_uint16 channel15,
    secondary_uint16 channel16
);
secondary_byte_size secondary_serialize_struct_IRTS_FR_3(
    uint8_t* data,
    secondary_message_IRTS_FR_3* message
);
void secondary_deserialize_IRTS_FR_3(
    secondary_message_IRTS_FR_3* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 timestamp
#endif // CANLIB_TIMESTAMP
);
int secondary_to_string_IRTS_FR_3(secondary_message_IRTS_FR_3* message, char* buffer);
int secondary_fields_IRTS_FR_3(char* buffer);
int secondary_to_string_file_IRTS_FR_3(secondary_message_IRTS_FR_3* message, FILE* buffer);
int secondary_fields_file_IRTS_FR_3(FILE* buffer);


// ============== IRTS_RL_0 ============== //

secondary_byte_size secondary_serialize_IRTS_RL_0(
    uint8_t* data,
    secondary_uint16 channel1,
    secondary_uint16 channel2,
    secondary_uint16 channel3,
    secondary_uint16 channel4
);
secondary_byte_size secondary_serialize_struct_IRTS_RL_0(
    uint8_t* data,
    secondary_message_IRTS_RL_0* message
);
void secondary_deserialize_IRTS_RL_0(
    secondary_message_IRTS_RL_0* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 timestamp
#endif // CANLIB_TIMESTAMP
);
int secondary_to_string_IRTS_RL_0(secondary_message_IRTS_RL_0* message, char* buffer);
int secondary_fields_IRTS_RL_0(char* buffer);
int secondary_to_string_file_IRTS_RL_0(secondary_message_IRTS_RL_0* message, FILE* buffer);
int secondary_fields_file_IRTS_RL_0(FILE* buffer);


// ============== IRTS_RL_1 ============== //

secondary_byte_size secondary_serialize_IRTS_RL_1(
    uint8_t* data,
    secondary_uint16 channel5,
    secondary_uint16 channel6,
    secondary_uint16 channel7,
    secondary_uint16 channel8
);
secondary_byte_size secondary_serialize_struct_IRTS_RL_1(
    uint8_t* data,
    secondary_message_IRTS_RL_1* message
);
void secondary_deserialize_IRTS_RL_1(
    secondary_message_IRTS_RL_1* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 timestamp
#endif // CANLIB_TIMESTAMP
);
int secondary_to_string_IRTS_RL_1(secondary_message_IRTS_RL_1* message, char* buffer);
int secondary_fields_IRTS_RL_1(char* buffer);
int secondary_to_string_file_IRTS_RL_1(secondary_message_IRTS_RL_1* message, FILE* buffer);
int secondary_fields_file_IRTS_RL_1(FILE* buffer);


// ============== IRTS_RL_2 ============== //

secondary_byte_size secondary_serialize_IRTS_RL_2(
    uint8_t* data,
    secondary_uint16 channel9,
    secondary_uint16 channel10,
    secondary_uint16 channel11,
    secondary_uint16 channel12
);
secondary_byte_size secondary_serialize_struct_IRTS_RL_2(
    uint8_t* data,
    secondary_message_IRTS_RL_2* message
);
void secondary_deserialize_IRTS_RL_2(
    secondary_message_IRTS_RL_2* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 timestamp
#endif // CANLIB_TIMESTAMP
);
int secondary_to_string_IRTS_RL_2(secondary_message_IRTS_RL_2* message, char* buffer);
int secondary_fields_IRTS_RL_2(char* buffer);
int secondary_to_string_file_IRTS_RL_2(secondary_message_IRTS_RL_2* message, FILE* buffer);
int secondary_fields_file_IRTS_RL_2(FILE* buffer);


// ============== IRTS_RL_3 ============== //

secondary_byte_size secondary_serialize_IRTS_RL_3(
    uint8_t* data,
    secondary_uint16 channel13,
    secondary_uint16 channel14,
    secondary_uint16 channel15,
    secondary_uint16 channel16
);
secondary_byte_size secondary_serialize_struct_IRTS_RL_3(
    uint8_t* data,
    secondary_message_IRTS_RL_3* message
);
void secondary_deserialize_IRTS_RL_3(
    secondary_message_IRTS_RL_3* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 timestamp
#endif // CANLIB_TIMESTAMP
);
int secondary_to_string_IRTS_RL_3(secondary_message_IRTS_RL_3* message, char* buffer);
int secondary_fields_IRTS_RL_3(char* buffer);
int secondary_to_string_file_IRTS_RL_3(secondary_message_IRTS_RL_3* message, FILE* buffer);
int secondary_fields_file_IRTS_RL_3(FILE* buffer);


// ============== IRTS_RR_0 ============== //

secondary_byte_size secondary_serialize_IRTS_RR_0(
    uint8_t* data,
    secondary_uint16 channel1,
    secondary_uint16 channel2,
    secondary_uint16 channel3,
    secondary_uint16 channel4
);
secondary_byte_size secondary_serialize_struct_IRTS_RR_0(
    uint8_t* data,
    secondary_message_IRTS_RR_0* message
);
void secondary_deserialize_IRTS_RR_0(
    secondary_message_IRTS_RR_0* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 timestamp
#endif // CANLIB_TIMESTAMP
);
int secondary_to_string_IRTS_RR_0(secondary_message_IRTS_RR_0* message, char* buffer);
int secondary_fields_IRTS_RR_0(char* buffer);
int secondary_to_string_file_IRTS_RR_0(secondary_message_IRTS_RR_0* message, FILE* buffer);
int secondary_fields_file_IRTS_RR_0(FILE* buffer);


// ============== IRTS_RR_1 ============== //

secondary_byte_size secondary_serialize_IRTS_RR_1(
    uint8_t* data,
    secondary_uint16 channel5,
    secondary_uint16 channel6,
    secondary_uint16 channel7,
    secondary_uint16 channel8
);
secondary_byte_size secondary_serialize_struct_IRTS_RR_1(
    uint8_t* data,
    secondary_message_IRTS_RR_1* message
);
void secondary_deserialize_IRTS_RR_1(
    secondary_message_IRTS_RR_1* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 timestamp
#endif // CANLIB_TIMESTAMP
);
int secondary_to_string_IRTS_RR_1(secondary_message_IRTS_RR_1* message, char* buffer);
int secondary_fields_IRTS_RR_1(char* buffer);
int secondary_to_string_file_IRTS_RR_1(secondary_message_IRTS_RR_1* message, FILE* buffer);
int secondary_fields_file_IRTS_RR_1(FILE* buffer);


// ============== IRTS_RR_2 ============== //

secondary_byte_size secondary_serialize_IRTS_RR_2(
    uint8_t* data,
    secondary_uint16 channel9,
    secondary_uint16 channel10,
    secondary_uint16 channel11,
    secondary_uint16 channel12
);
secondary_byte_size secondary_serialize_struct_IRTS_RR_2(
    uint8_t* data,
    secondary_message_IRTS_RR_2* message
);
void secondary_deserialize_IRTS_RR_2(
    secondary_message_IRTS_RR_2* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 timestamp
#endif // CANLIB_TIMESTAMP
);
int secondary_to_string_IRTS_RR_2(secondary_message_IRTS_RR_2* message, char* buffer);
int secondary_fields_IRTS_RR_2(char* buffer);
int secondary_to_string_file_IRTS_RR_2(secondary_message_IRTS_RR_2* message, FILE* buffer);
int secondary_fields_file_IRTS_RR_2(FILE* buffer);


// ============== IRTS_RR_3 ============== //

secondary_byte_size secondary_serialize_IRTS_RR_3(
    uint8_t* data,
    secondary_uint16 channel13,
    secondary_uint16 channel14,
    secondary_uint16 channel15,
    secondary_uint16 channel16
);
secondary_byte_size secondary_serialize_struct_IRTS_RR_3(
    uint8_t* data,
    secondary_message_IRTS_RR_3* message
);
void secondary_deserialize_IRTS_RR_3(
    secondary_message_IRTS_RR_3* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 timestamp
#endif // CANLIB_TIMESTAMP
);
int secondary_to_string_IRTS_RR_3(secondary_message_IRTS_RR_3* message, char* buffer);
int secondary_fields_IRTS_RR_3(char* buffer);
int secondary_to_string_file_IRTS_RR_3(secondary_message_IRTS_RR_3* message, FILE* buffer);
int secondary_fields_file_IRTS_RR_3(FILE* buffer);


// ============== GPS_COORDS ============== //

secondary_byte_size secondary_serialize_GPS_COORDS(
    uint8_t* data,
    secondary_float32 latitude,
    secondary_float32 longitude
);
secondary_byte_size secondary_serialize_struct_GPS_COORDS(
    uint8_t* data,
    secondary_message_GPS_COORDS* message
);
void secondary_deserialize_GPS_COORDS(
    secondary_message_GPS_COORDS* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 timestamp
#endif // CANLIB_TIMESTAMP
);
int secondary_to_string_GPS_COORDS(secondary_message_GPS_COORDS* message, char* buffer);
int secondary_fields_GPS_COORDS(char* buffer);
int secondary_to_string_file_GPS_COORDS(secondary_message_GPS_COORDS* message, FILE* buffer);
int secondary_fields_file_GPS_COORDS(FILE* buffer);


// ============== GPS_SPEED ============== //

secondary_byte_size secondary_serialize_GPS_SPEED(
    uint8_t* data,
    secondary_uint16 speed
);
secondary_byte_size secondary_serialize_struct_GPS_SPEED(
    uint8_t* data,
    secondary_message_GPS_SPEED* message
);
void secondary_deserialize_GPS_SPEED(
    secondary_message_GPS_SPEED* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 timestamp
#endif // CANLIB_TIMESTAMP
);
int secondary_to_string_GPS_SPEED(secondary_message_GPS_SPEED* message, char* buffer);
int secondary_fields_GPS_SPEED(char* buffer);
int secondary_to_string_file_GPS_SPEED(secondary_message_GPS_SPEED* message, FILE* buffer);
int secondary_fields_file_GPS_SPEED(FILE* buffer);


// ============== LAP_COUNT ============== //

secondary_byte_size secondary_serialize_LAP_COUNT(
    uint8_t* data,
    secondary_uint32 timestamp,
    secondary_uint8 lap_count
);
secondary_byte_size secondary_serialize_struct_LAP_COUNT(
    uint8_t* data,
    secondary_message_LAP_COUNT* message
);
void secondary_deserialize_LAP_COUNT(
    secondary_message_LAP_COUNT* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 timestamp
#endif // CANLIB_TIMESTAMP
);
int secondary_to_string_LAP_COUNT(secondary_message_LAP_COUNT* message, char* buffer);
int secondary_fields_LAP_COUNT(char* buffer);
int secondary_to_string_file_LAP_COUNT(secondary_message_LAP_COUNT* message, FILE* buffer);
int secondary_fields_file_LAP_COUNT(FILE* buffer);


// ============== PEDALS_OUTPUT ============== //

secondary_byte_size secondary_serialize_PEDALS_OUTPUT(
    uint8_t* data,
    secondary_uint16 bse_front,
    secondary_uint16 bse_rear,
    secondary_uint8 apps
);
secondary_byte_size secondary_serialize_struct_PEDALS_OUTPUT(
    uint8_t* data,
    secondary_message_PEDALS_OUTPUT* message
);
void secondary_deserialize_PEDALS_OUTPUT(
    secondary_message_PEDALS_OUTPUT* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 timestamp
#endif // CANLIB_TIMESTAMP
);
void secondary_raw_to_conversion_PEDALS_OUTPUT(
    secondary_message_PEDALS_OUTPUT_conversion* conversion,
    secondary_message_PEDALS_OUTPUT* raw
);
void secondary_conversion_to_raw_PEDALS_OUTPUT(
    secondary_message_PEDALS_OUTPUT* raw,
    secondary_message_PEDALS_OUTPUT_conversion* conversion
);
int secondary_to_string_PEDALS_OUTPUT(secondary_message_PEDALS_OUTPUT_conversion* message, char* buffer);
int secondary_fields_PEDALS_OUTPUT(char* buffer);
int secondary_to_string_file_PEDALS_OUTPUT(secondary_message_PEDALS_OUTPUT_conversion* message, FILE* buffer);
int secondary_fields_file_PEDALS_OUTPUT(FILE* buffer);


// ============== CONTROL_OUTPUT ============== //

secondary_byte_size secondary_serialize_CONTROL_OUTPUT(
    uint8_t* data,
    secondary_float32 right,
    secondary_float32 left
);
secondary_byte_size secondary_serialize_struct_CONTROL_OUTPUT(
    uint8_t* data,
    secondary_message_CONTROL_OUTPUT* message
);
void secondary_deserialize_CONTROL_OUTPUT(
    secondary_message_CONTROL_OUTPUT* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 timestamp
#endif // CANLIB_TIMESTAMP
);
int secondary_to_string_CONTROL_OUTPUT(secondary_message_CONTROL_OUTPUT* message, char* buffer);
int secondary_fields_CONTROL_OUTPUT(char* buffer);
int secondary_to_string_file_CONTROL_OUTPUT(secondary_message_CONTROL_OUTPUT* message, FILE* buffer);
int secondary_fields_file_CONTROL_OUTPUT(FILE* buffer);


// ============== STEERING_ANGLE ============== //

secondary_byte_size secondary_serialize_STEERING_ANGLE(
    uint8_t* data,
    secondary_float32 angle
);
secondary_byte_size secondary_serialize_struct_STEERING_ANGLE(
    uint8_t* data,
    secondary_message_STEERING_ANGLE* message
);
void secondary_deserialize_STEERING_ANGLE(
    secondary_message_STEERING_ANGLE* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 timestamp
#endif // CANLIB_TIMESTAMP
);
int secondary_to_string_STEERING_ANGLE(secondary_message_STEERING_ANGLE* message, char* buffer);
int secondary_fields_STEERING_ANGLE(char* buffer);
int secondary_to_string_file_STEERING_ANGLE(secondary_message_STEERING_ANGLE* message, FILE* buffer);
int secondary_fields_file_STEERING_ANGLE(FILE* buffer);




// ============== UTILS ============== //

void secondary_devices_new(secondary_devices* map);
int secondary_devices_index_from_id(canlib_message_id message_id, secondary_devices* map);
void secondary_fields_from_id(canlib_message_id message_id, FILE *buffer);
void secondary_string_from_id(canlib_message_id message_id, void* message, FILE *buffer);
void secondary_deserialize_from_id(
    canlib_message_id message_id,
    uint8_t* data,
    void* raw_message,
    void* message
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 timestamp
#endif // CANLIB_TIMESTAMP
);

#ifdef secondary_IMPLEMENTATION
// ============== SERIALIZE ============== //

secondary_byte_size secondary_serialize_IMU_ANGULAR_RATE(
    uint8_t* data,
    secondary_uint16 ang_rate_x,
    secondary_uint16 ang_rate_y,
    secondary_uint16 ang_rate_z
) {
    data[0] = ang_rate_x & 255;
    data[1] = (ang_rate_x >> 8) & 255;
    data[2] = ang_rate_y & 255;
    data[3] = (ang_rate_y >> 8) & 255;
    data[4] = ang_rate_z & 255;
    data[5] = (ang_rate_z >> 8) & 255;
    return 6;
}

secondary_byte_size secondary_serialize_struct_IMU_ANGULAR_RATE(
    uint8_t* data,
    secondary_message_IMU_ANGULAR_RATE* message
) {
    data[0] = message->ang_rate_x & 255;
    data[1] = (message->ang_rate_x >> 8) & 255;
    data[2] = message->ang_rate_y & 255;
    data[3] = (message->ang_rate_y >> 8) & 255;
    data[4] = message->ang_rate_z & 255;
    data[5] = (message->ang_rate_z >> 8) & 255;
    return 6;
}

// ============== DESERIALIZE ============== //

void secondary_deserialize_IMU_ANGULAR_RATE(
    secondary_message_IMU_ANGULAR_RATE* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 _timestamp
#endif // CANLIB_TIMESTAMP
) {
#ifdef CANLIB_TIMESTAMP
    message->_timestamp = _timestamp;
#endif // CANLIB_TIMESTAMP
    message->ang_rate_x = data[0] | (data[1] << 8);
    message->ang_rate_y = data[2] | (data[3] << 8);
    message->ang_rate_z = data[4] | (data[5] << 8);
}

// ============== STRING ============== //

int secondary_to_string_IMU_ANGULAR_RATE(secondary_message_IMU_ANGULAR_RATE* message, char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->ang_rate_x,
        message->ang_rate_y,
        message->ang_rate_z
    );}
int secondary_fields_IMU_ANGULAR_RATE(char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "ang_rate_x" CANLIB_SEPARATOR 
        "ang_rate_y" CANLIB_SEPARATOR 
        "ang_rate_z"
    );}
int secondary_to_string_file_IMU_ANGULAR_RATE(secondary_message_IMU_ANGULAR_RATE* message, FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->ang_rate_x,
        message->ang_rate_y,
        message->ang_rate_z
    );}
int secondary_fields_file_IMU_ANGULAR_RATE(FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "ang_rate_x" CANLIB_SEPARATOR 
        "ang_rate_y" CANLIB_SEPARATOR 
        "ang_rate_z"
    );}

// ============== SERIALIZE ============== //

secondary_byte_size secondary_serialize_IMU_ACCELERATION(
    uint8_t* data,
    secondary_uint16 accel_x,
    secondary_uint16 accel_y,
    secondary_uint16 accel_z
) {
    data[0] = accel_x & 255;
    data[1] = (accel_x >> 8) & 255;
    data[2] = accel_y & 255;
    data[3] = (accel_y >> 8) & 255;
    data[4] = accel_z & 255;
    data[5] = (accel_z >> 8) & 255;
    return 6;
}

secondary_byte_size secondary_serialize_struct_IMU_ACCELERATION(
    uint8_t* data,
    secondary_message_IMU_ACCELERATION* message
) {
    data[0] = message->accel_x & 255;
    data[1] = (message->accel_x >> 8) & 255;
    data[2] = message->accel_y & 255;
    data[3] = (message->accel_y >> 8) & 255;
    data[4] = message->accel_z & 255;
    data[5] = (message->accel_z >> 8) & 255;
    return 6;
}

// ============== DESERIALIZE ============== //

void secondary_deserialize_IMU_ACCELERATION(
    secondary_message_IMU_ACCELERATION* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 _timestamp
#endif // CANLIB_TIMESTAMP
) {
#ifdef CANLIB_TIMESTAMP
    message->_timestamp = _timestamp;
#endif // CANLIB_TIMESTAMP
    message->accel_x = data[0] | (data[1] << 8);
    message->accel_y = data[2] | (data[3] << 8);
    message->accel_z = data[4] | (data[5] << 8);
}

// ============== STRING ============== //

int secondary_to_string_IMU_ACCELERATION(secondary_message_IMU_ACCELERATION* message, char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->accel_x,
        message->accel_y,
        message->accel_z
    );}
int secondary_fields_IMU_ACCELERATION(char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "accel_x" CANLIB_SEPARATOR 
        "accel_y" CANLIB_SEPARATOR 
        "accel_z"
    );}
int secondary_to_string_file_IMU_ACCELERATION(secondary_message_IMU_ACCELERATION* message, FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->accel_x,
        message->accel_y,
        message->accel_z
    );}
int secondary_fields_file_IMU_ACCELERATION(FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "accel_x" CANLIB_SEPARATOR 
        "accel_y" CANLIB_SEPARATOR 
        "accel_z"
    );}

// ============== SERIALIZE ============== //

secondary_byte_size secondary_serialize_IRTS_FL_0(
    uint8_t* data,
    secondary_uint16 channel1,
    secondary_uint16 channel2,
    secondary_uint16 channel3,
    secondary_uint16 channel4
) {
    data[0] = channel1 & 255;
    data[1] = (channel1 >> 8) & 255;
    data[2] = channel2 & 255;
    data[3] = (channel2 >> 8) & 255;
    data[4] = channel3 & 255;
    data[5] = (channel3 >> 8) & 255;
    data[6] = channel4 & 255;
    data[7] = (channel4 >> 8) & 255;
    return 8;
}

secondary_byte_size secondary_serialize_struct_IRTS_FL_0(
    uint8_t* data,
    secondary_message_IRTS_FL_0* message
) {
    data[0] = message->channel1 & 255;
    data[1] = (message->channel1 >> 8) & 255;
    data[2] = message->channel2 & 255;
    data[3] = (message->channel2 >> 8) & 255;
    data[4] = message->channel3 & 255;
    data[5] = (message->channel3 >> 8) & 255;
    data[6] = message->channel4 & 255;
    data[7] = (message->channel4 >> 8) & 255;
    return 8;
}

// ============== DESERIALIZE ============== //

void secondary_deserialize_IRTS_FL_0(
    secondary_message_IRTS_FL_0* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 _timestamp
#endif // CANLIB_TIMESTAMP
) {
#ifdef CANLIB_TIMESTAMP
    message->_timestamp = _timestamp;
#endif // CANLIB_TIMESTAMP
    message->channel1 = data[0] | (data[1] << 8);
    message->channel2 = data[2] | (data[3] << 8);
    message->channel3 = data[4] | (data[5] << 8);
    message->channel4 = data[6] | (data[7] << 8);
}

// ============== STRING ============== //

int secondary_to_string_IRTS_FL_0(secondary_message_IRTS_FL_0* message, char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->channel1,
        message->channel2,
        message->channel3,
        message->channel4
    );}
int secondary_fields_IRTS_FL_0(char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "channel1" CANLIB_SEPARATOR 
        "channel2" CANLIB_SEPARATOR 
        "channel3" CANLIB_SEPARATOR 
        "channel4"
    );}
int secondary_to_string_file_IRTS_FL_0(secondary_message_IRTS_FL_0* message, FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->channel1,
        message->channel2,
        message->channel3,
        message->channel4
    );}
int secondary_fields_file_IRTS_FL_0(FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "channel1" CANLIB_SEPARATOR 
        "channel2" CANLIB_SEPARATOR 
        "channel3" CANLIB_SEPARATOR 
        "channel4"
    );}

// ============== SERIALIZE ============== //

secondary_byte_size secondary_serialize_IRTS_FL_1(
    uint8_t* data,
    secondary_uint16 channel5,
    secondary_uint16 channel6,
    secondary_uint16 channel7,
    secondary_uint16 channel8
) {
    data[0] = channel5 & 255;
    data[1] = (channel5 >> 8) & 255;
    data[2] = channel6 & 255;
    data[3] = (channel6 >> 8) & 255;
    data[4] = channel7 & 255;
    data[5] = (channel7 >> 8) & 255;
    data[6] = channel8 & 255;
    data[7] = (channel8 >> 8) & 255;
    return 8;
}

secondary_byte_size secondary_serialize_struct_IRTS_FL_1(
    uint8_t* data,
    secondary_message_IRTS_FL_1* message
) {
    data[0] = message->channel5 & 255;
    data[1] = (message->channel5 >> 8) & 255;
    data[2] = message->channel6 & 255;
    data[3] = (message->channel6 >> 8) & 255;
    data[4] = message->channel7 & 255;
    data[5] = (message->channel7 >> 8) & 255;
    data[6] = message->channel8 & 255;
    data[7] = (message->channel8 >> 8) & 255;
    return 8;
}

// ============== DESERIALIZE ============== //

void secondary_deserialize_IRTS_FL_1(
    secondary_message_IRTS_FL_1* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 _timestamp
#endif // CANLIB_TIMESTAMP
) {
#ifdef CANLIB_TIMESTAMP
    message->_timestamp = _timestamp;
#endif // CANLIB_TIMESTAMP
    message->channel5 = data[0] | (data[1] << 8);
    message->channel6 = data[2] | (data[3] << 8);
    message->channel7 = data[4] | (data[5] << 8);
    message->channel8 = data[6] | (data[7] << 8);
}

// ============== STRING ============== //

int secondary_to_string_IRTS_FL_1(secondary_message_IRTS_FL_1* message, char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->channel5,
        message->channel6,
        message->channel7,
        message->channel8
    );}
int secondary_fields_IRTS_FL_1(char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "channel5" CANLIB_SEPARATOR 
        "channel6" CANLIB_SEPARATOR 
        "channel7" CANLIB_SEPARATOR 
        "channel8"
    );}
int secondary_to_string_file_IRTS_FL_1(secondary_message_IRTS_FL_1* message, FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->channel5,
        message->channel6,
        message->channel7,
        message->channel8
    );}
int secondary_fields_file_IRTS_FL_1(FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "channel5" CANLIB_SEPARATOR 
        "channel6" CANLIB_SEPARATOR 
        "channel7" CANLIB_SEPARATOR 
        "channel8"
    );}

// ============== SERIALIZE ============== //

secondary_byte_size secondary_serialize_IRTS_FL_2(
    uint8_t* data,
    secondary_uint16 channel9,
    secondary_uint16 channel10,
    secondary_uint16 channel11,
    secondary_uint16 channel12
) {
    data[0] = channel9 & 255;
    data[1] = (channel9 >> 8) & 255;
    data[2] = channel10 & 255;
    data[3] = (channel10 >> 8) & 255;
    data[4] = channel11 & 255;
    data[5] = (channel11 >> 8) & 255;
    data[6] = channel12 & 255;
    data[7] = (channel12 >> 8) & 255;
    return 8;
}

secondary_byte_size secondary_serialize_struct_IRTS_FL_2(
    uint8_t* data,
    secondary_message_IRTS_FL_2* message
) {
    data[0] = message->channel9 & 255;
    data[1] = (message->channel9 >> 8) & 255;
    data[2] = message->channel10 & 255;
    data[3] = (message->channel10 >> 8) & 255;
    data[4] = message->channel11 & 255;
    data[5] = (message->channel11 >> 8) & 255;
    data[6] = message->channel12 & 255;
    data[7] = (message->channel12 >> 8) & 255;
    return 8;
}

// ============== DESERIALIZE ============== //

void secondary_deserialize_IRTS_FL_2(
    secondary_message_IRTS_FL_2* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 _timestamp
#endif // CANLIB_TIMESTAMP
) {
#ifdef CANLIB_TIMESTAMP
    message->_timestamp = _timestamp;
#endif // CANLIB_TIMESTAMP
    message->channel9 = data[0] | (data[1] << 8);
    message->channel10 = data[2] | (data[3] << 8);
    message->channel11 = data[4] | (data[5] << 8);
    message->channel12 = data[6] | (data[7] << 8);
}

// ============== STRING ============== //

int secondary_to_string_IRTS_FL_2(secondary_message_IRTS_FL_2* message, char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->channel9,
        message->channel10,
        message->channel11,
        message->channel12
    );}
int secondary_fields_IRTS_FL_2(char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "channel9" CANLIB_SEPARATOR 
        "channel10" CANLIB_SEPARATOR 
        "channel11" CANLIB_SEPARATOR 
        "channel12"
    );}
int secondary_to_string_file_IRTS_FL_2(secondary_message_IRTS_FL_2* message, FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->channel9,
        message->channel10,
        message->channel11,
        message->channel12
    );}
int secondary_fields_file_IRTS_FL_2(FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "channel9" CANLIB_SEPARATOR 
        "channel10" CANLIB_SEPARATOR 
        "channel11" CANLIB_SEPARATOR 
        "channel12"
    );}

// ============== SERIALIZE ============== //

secondary_byte_size secondary_serialize_IRTS_FL_3(
    uint8_t* data,
    secondary_uint16 channel13,
    secondary_uint16 channel14,
    secondary_uint16 channel15,
    secondary_uint16 channel16
) {
    data[0] = channel13 & 255;
    data[1] = (channel13 >> 8) & 255;
    data[2] = channel14 & 255;
    data[3] = (channel14 >> 8) & 255;
    data[4] = channel15 & 255;
    data[5] = (channel15 >> 8) & 255;
    data[6] = channel16 & 255;
    data[7] = (channel16 >> 8) & 255;
    return 8;
}

secondary_byte_size secondary_serialize_struct_IRTS_FL_3(
    uint8_t* data,
    secondary_message_IRTS_FL_3* message
) {
    data[0] = message->channel13 & 255;
    data[1] = (message->channel13 >> 8) & 255;
    data[2] = message->channel14 & 255;
    data[3] = (message->channel14 >> 8) & 255;
    data[4] = message->channel15 & 255;
    data[5] = (message->channel15 >> 8) & 255;
    data[6] = message->channel16 & 255;
    data[7] = (message->channel16 >> 8) & 255;
    return 8;
}

// ============== DESERIALIZE ============== //

void secondary_deserialize_IRTS_FL_3(
    secondary_message_IRTS_FL_3* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 _timestamp
#endif // CANLIB_TIMESTAMP
) {
#ifdef CANLIB_TIMESTAMP
    message->_timestamp = _timestamp;
#endif // CANLIB_TIMESTAMP
    message->channel13 = data[0] | (data[1] << 8);
    message->channel14 = data[2] | (data[3] << 8);
    message->channel15 = data[4] | (data[5] << 8);
    message->channel16 = data[6] | (data[7] << 8);
}

// ============== STRING ============== //

int secondary_to_string_IRTS_FL_3(secondary_message_IRTS_FL_3* message, char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->channel13,
        message->channel14,
        message->channel15,
        message->channel16
    );}
int secondary_fields_IRTS_FL_3(char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "channel13" CANLIB_SEPARATOR 
        "channel14" CANLIB_SEPARATOR 
        "channel15" CANLIB_SEPARATOR 
        "channel16"
    );}
int secondary_to_string_file_IRTS_FL_3(secondary_message_IRTS_FL_3* message, FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->channel13,
        message->channel14,
        message->channel15,
        message->channel16
    );}
int secondary_fields_file_IRTS_FL_3(FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "channel13" CANLIB_SEPARATOR 
        "channel14" CANLIB_SEPARATOR 
        "channel15" CANLIB_SEPARATOR 
        "channel16"
    );}

// ============== SERIALIZE ============== //

secondary_byte_size secondary_serialize_IRTS_FR_0(
    uint8_t* data,
    secondary_uint16 channel1,
    secondary_uint16 channel2,
    secondary_uint16 channel3,
    secondary_uint16 channel4
) {
    data[0] = channel1 & 255;
    data[1] = (channel1 >> 8) & 255;
    data[2] = channel2 & 255;
    data[3] = (channel2 >> 8) & 255;
    data[4] = channel3 & 255;
    data[5] = (channel3 >> 8) & 255;
    data[6] = channel4 & 255;
    data[7] = (channel4 >> 8) & 255;
    return 8;
}

secondary_byte_size secondary_serialize_struct_IRTS_FR_0(
    uint8_t* data,
    secondary_message_IRTS_FR_0* message
) {
    data[0] = message->channel1 & 255;
    data[1] = (message->channel1 >> 8) & 255;
    data[2] = message->channel2 & 255;
    data[3] = (message->channel2 >> 8) & 255;
    data[4] = message->channel3 & 255;
    data[5] = (message->channel3 >> 8) & 255;
    data[6] = message->channel4 & 255;
    data[7] = (message->channel4 >> 8) & 255;
    return 8;
}

// ============== DESERIALIZE ============== //

void secondary_deserialize_IRTS_FR_0(
    secondary_message_IRTS_FR_0* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 _timestamp
#endif // CANLIB_TIMESTAMP
) {
#ifdef CANLIB_TIMESTAMP
    message->_timestamp = _timestamp;
#endif // CANLIB_TIMESTAMP
    message->channel1 = data[0] | (data[1] << 8);
    message->channel2 = data[2] | (data[3] << 8);
    message->channel3 = data[4] | (data[5] << 8);
    message->channel4 = data[6] | (data[7] << 8);
}

// ============== STRING ============== //

int secondary_to_string_IRTS_FR_0(secondary_message_IRTS_FR_0* message, char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->channel1,
        message->channel2,
        message->channel3,
        message->channel4
    );}
int secondary_fields_IRTS_FR_0(char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "channel1" CANLIB_SEPARATOR 
        "channel2" CANLIB_SEPARATOR 
        "channel3" CANLIB_SEPARATOR 
        "channel4"
    );}
int secondary_to_string_file_IRTS_FR_0(secondary_message_IRTS_FR_0* message, FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->channel1,
        message->channel2,
        message->channel3,
        message->channel4
    );}
int secondary_fields_file_IRTS_FR_0(FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "channel1" CANLIB_SEPARATOR 
        "channel2" CANLIB_SEPARATOR 
        "channel3" CANLIB_SEPARATOR 
        "channel4"
    );}

// ============== SERIALIZE ============== //

secondary_byte_size secondary_serialize_IRTS_FR_1(
    uint8_t* data,
    secondary_uint16 channel5,
    secondary_uint16 channel6,
    secondary_uint16 channel7,
    secondary_uint16 channel8
) {
    data[0] = channel5 & 255;
    data[1] = (channel5 >> 8) & 255;
    data[2] = channel6 & 255;
    data[3] = (channel6 >> 8) & 255;
    data[4] = channel7 & 255;
    data[5] = (channel7 >> 8) & 255;
    data[6] = channel8 & 255;
    data[7] = (channel8 >> 8) & 255;
    return 8;
}

secondary_byte_size secondary_serialize_struct_IRTS_FR_1(
    uint8_t* data,
    secondary_message_IRTS_FR_1* message
) {
    data[0] = message->channel5 & 255;
    data[1] = (message->channel5 >> 8) & 255;
    data[2] = message->channel6 & 255;
    data[3] = (message->channel6 >> 8) & 255;
    data[4] = message->channel7 & 255;
    data[5] = (message->channel7 >> 8) & 255;
    data[6] = message->channel8 & 255;
    data[7] = (message->channel8 >> 8) & 255;
    return 8;
}

// ============== DESERIALIZE ============== //

void secondary_deserialize_IRTS_FR_1(
    secondary_message_IRTS_FR_1* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 _timestamp
#endif // CANLIB_TIMESTAMP
) {
#ifdef CANLIB_TIMESTAMP
    message->_timestamp = _timestamp;
#endif // CANLIB_TIMESTAMP
    message->channel5 = data[0] | (data[1] << 8);
    message->channel6 = data[2] | (data[3] << 8);
    message->channel7 = data[4] | (data[5] << 8);
    message->channel8 = data[6] | (data[7] << 8);
}

// ============== STRING ============== //

int secondary_to_string_IRTS_FR_1(secondary_message_IRTS_FR_1* message, char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->channel5,
        message->channel6,
        message->channel7,
        message->channel8
    );}
int secondary_fields_IRTS_FR_1(char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "channel5" CANLIB_SEPARATOR 
        "channel6" CANLIB_SEPARATOR 
        "channel7" CANLIB_SEPARATOR 
        "channel8"
    );}
int secondary_to_string_file_IRTS_FR_1(secondary_message_IRTS_FR_1* message, FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->channel5,
        message->channel6,
        message->channel7,
        message->channel8
    );}
int secondary_fields_file_IRTS_FR_1(FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "channel5" CANLIB_SEPARATOR 
        "channel6" CANLIB_SEPARATOR 
        "channel7" CANLIB_SEPARATOR 
        "channel8"
    );}

// ============== SERIALIZE ============== //

secondary_byte_size secondary_serialize_IRTS_FR_2(
    uint8_t* data,
    secondary_uint16 channel9,
    secondary_uint16 channel10,
    secondary_uint16 channel11,
    secondary_uint16 channel12
) {
    data[0] = channel9 & 255;
    data[1] = (channel9 >> 8) & 255;
    data[2] = channel10 & 255;
    data[3] = (channel10 >> 8) & 255;
    data[4] = channel11 & 255;
    data[5] = (channel11 >> 8) & 255;
    data[6] = channel12 & 255;
    data[7] = (channel12 >> 8) & 255;
    return 8;
}

secondary_byte_size secondary_serialize_struct_IRTS_FR_2(
    uint8_t* data,
    secondary_message_IRTS_FR_2* message
) {
    data[0] = message->channel9 & 255;
    data[1] = (message->channel9 >> 8) & 255;
    data[2] = message->channel10 & 255;
    data[3] = (message->channel10 >> 8) & 255;
    data[4] = message->channel11 & 255;
    data[5] = (message->channel11 >> 8) & 255;
    data[6] = message->channel12 & 255;
    data[7] = (message->channel12 >> 8) & 255;
    return 8;
}

// ============== DESERIALIZE ============== //

void secondary_deserialize_IRTS_FR_2(
    secondary_message_IRTS_FR_2* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 _timestamp
#endif // CANLIB_TIMESTAMP
) {
#ifdef CANLIB_TIMESTAMP
    message->_timestamp = _timestamp;
#endif // CANLIB_TIMESTAMP
    message->channel9 = data[0] | (data[1] << 8);
    message->channel10 = data[2] | (data[3] << 8);
    message->channel11 = data[4] | (data[5] << 8);
    message->channel12 = data[6] | (data[7] << 8);
}

// ============== STRING ============== //

int secondary_to_string_IRTS_FR_2(secondary_message_IRTS_FR_2* message, char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->channel9,
        message->channel10,
        message->channel11,
        message->channel12
    );}
int secondary_fields_IRTS_FR_2(char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "channel9" CANLIB_SEPARATOR 
        "channel10" CANLIB_SEPARATOR 
        "channel11" CANLIB_SEPARATOR 
        "channel12"
    );}
int secondary_to_string_file_IRTS_FR_2(secondary_message_IRTS_FR_2* message, FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->channel9,
        message->channel10,
        message->channel11,
        message->channel12
    );}
int secondary_fields_file_IRTS_FR_2(FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "channel9" CANLIB_SEPARATOR 
        "channel10" CANLIB_SEPARATOR 
        "channel11" CANLIB_SEPARATOR 
        "channel12"
    );}

// ============== SERIALIZE ============== //

secondary_byte_size secondary_serialize_IRTS_FR_3(
    uint8_t* data,
    secondary_uint16 channel13,
    secondary_uint16 channel14,
    secondary_uint16 channel15,
    secondary_uint16 channel16
) {
    data[0] = channel13 & 255;
    data[1] = (channel13 >> 8) & 255;
    data[2] = channel14 & 255;
    data[3] = (channel14 >> 8) & 255;
    data[4] = channel15 & 255;
    data[5] = (channel15 >> 8) & 255;
    data[6] = channel16 & 255;
    data[7] = (channel16 >> 8) & 255;
    return 8;
}

secondary_byte_size secondary_serialize_struct_IRTS_FR_3(
    uint8_t* data,
    secondary_message_IRTS_FR_3* message
) {
    data[0] = message->channel13 & 255;
    data[1] = (message->channel13 >> 8) & 255;
    data[2] = message->channel14 & 255;
    data[3] = (message->channel14 >> 8) & 255;
    data[4] = message->channel15 & 255;
    data[5] = (message->channel15 >> 8) & 255;
    data[6] = message->channel16 & 255;
    data[7] = (message->channel16 >> 8) & 255;
    return 8;
}

// ============== DESERIALIZE ============== //

void secondary_deserialize_IRTS_FR_3(
    secondary_message_IRTS_FR_3* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 _timestamp
#endif // CANLIB_TIMESTAMP
) {
#ifdef CANLIB_TIMESTAMP
    message->_timestamp = _timestamp;
#endif // CANLIB_TIMESTAMP
    message->channel13 = data[0] | (data[1] << 8);
    message->channel14 = data[2] | (data[3] << 8);
    message->channel15 = data[4] | (data[5] << 8);
    message->channel16 = data[6] | (data[7] << 8);
}

// ============== STRING ============== //

int secondary_to_string_IRTS_FR_3(secondary_message_IRTS_FR_3* message, char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->channel13,
        message->channel14,
        message->channel15,
        message->channel16
    );}
int secondary_fields_IRTS_FR_3(char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "channel13" CANLIB_SEPARATOR 
        "channel14" CANLIB_SEPARATOR 
        "channel15" CANLIB_SEPARATOR 
        "channel16"
    );}
int secondary_to_string_file_IRTS_FR_3(secondary_message_IRTS_FR_3* message, FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->channel13,
        message->channel14,
        message->channel15,
        message->channel16
    );}
int secondary_fields_file_IRTS_FR_3(FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "channel13" CANLIB_SEPARATOR 
        "channel14" CANLIB_SEPARATOR 
        "channel15" CANLIB_SEPARATOR 
        "channel16"
    );}

// ============== SERIALIZE ============== //

secondary_byte_size secondary_serialize_IRTS_RL_0(
    uint8_t* data,
    secondary_uint16 channel1,
    secondary_uint16 channel2,
    secondary_uint16 channel3,
    secondary_uint16 channel4
) {
    data[0] = channel1 & 255;
    data[1] = (channel1 >> 8) & 255;
    data[2] = channel2 & 255;
    data[3] = (channel2 >> 8) & 255;
    data[4] = channel3 & 255;
    data[5] = (channel3 >> 8) & 255;
    data[6] = channel4 & 255;
    data[7] = (channel4 >> 8) & 255;
    return 8;
}

secondary_byte_size secondary_serialize_struct_IRTS_RL_0(
    uint8_t* data,
    secondary_message_IRTS_RL_0* message
) {
    data[0] = message->channel1 & 255;
    data[1] = (message->channel1 >> 8) & 255;
    data[2] = message->channel2 & 255;
    data[3] = (message->channel2 >> 8) & 255;
    data[4] = message->channel3 & 255;
    data[5] = (message->channel3 >> 8) & 255;
    data[6] = message->channel4 & 255;
    data[7] = (message->channel4 >> 8) & 255;
    return 8;
}

// ============== DESERIALIZE ============== //

void secondary_deserialize_IRTS_RL_0(
    secondary_message_IRTS_RL_0* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 _timestamp
#endif // CANLIB_TIMESTAMP
) {
#ifdef CANLIB_TIMESTAMP
    message->_timestamp = _timestamp;
#endif // CANLIB_TIMESTAMP
    message->channel1 = data[0] | (data[1] << 8);
    message->channel2 = data[2] | (data[3] << 8);
    message->channel3 = data[4] | (data[5] << 8);
    message->channel4 = data[6] | (data[7] << 8);
}

// ============== STRING ============== //

int secondary_to_string_IRTS_RL_0(secondary_message_IRTS_RL_0* message, char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->channel1,
        message->channel2,
        message->channel3,
        message->channel4
    );}
int secondary_fields_IRTS_RL_0(char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "channel1" CANLIB_SEPARATOR 
        "channel2" CANLIB_SEPARATOR 
        "channel3" CANLIB_SEPARATOR 
        "channel4"
    );}
int secondary_to_string_file_IRTS_RL_0(secondary_message_IRTS_RL_0* message, FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->channel1,
        message->channel2,
        message->channel3,
        message->channel4
    );}
int secondary_fields_file_IRTS_RL_0(FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "channel1" CANLIB_SEPARATOR 
        "channel2" CANLIB_SEPARATOR 
        "channel3" CANLIB_SEPARATOR 
        "channel4"
    );}

// ============== SERIALIZE ============== //

secondary_byte_size secondary_serialize_IRTS_RL_1(
    uint8_t* data,
    secondary_uint16 channel5,
    secondary_uint16 channel6,
    secondary_uint16 channel7,
    secondary_uint16 channel8
) {
    data[0] = channel5 & 255;
    data[1] = (channel5 >> 8) & 255;
    data[2] = channel6 & 255;
    data[3] = (channel6 >> 8) & 255;
    data[4] = channel7 & 255;
    data[5] = (channel7 >> 8) & 255;
    data[6] = channel8 & 255;
    data[7] = (channel8 >> 8) & 255;
    return 8;
}

secondary_byte_size secondary_serialize_struct_IRTS_RL_1(
    uint8_t* data,
    secondary_message_IRTS_RL_1* message
) {
    data[0] = message->channel5 & 255;
    data[1] = (message->channel5 >> 8) & 255;
    data[2] = message->channel6 & 255;
    data[3] = (message->channel6 >> 8) & 255;
    data[4] = message->channel7 & 255;
    data[5] = (message->channel7 >> 8) & 255;
    data[6] = message->channel8 & 255;
    data[7] = (message->channel8 >> 8) & 255;
    return 8;
}

// ============== DESERIALIZE ============== //

void secondary_deserialize_IRTS_RL_1(
    secondary_message_IRTS_RL_1* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 _timestamp
#endif // CANLIB_TIMESTAMP
) {
#ifdef CANLIB_TIMESTAMP
    message->_timestamp = _timestamp;
#endif // CANLIB_TIMESTAMP
    message->channel5 = data[0] | (data[1] << 8);
    message->channel6 = data[2] | (data[3] << 8);
    message->channel7 = data[4] | (data[5] << 8);
    message->channel8 = data[6] | (data[7] << 8);
}

// ============== STRING ============== //

int secondary_to_string_IRTS_RL_1(secondary_message_IRTS_RL_1* message, char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->channel5,
        message->channel6,
        message->channel7,
        message->channel8
    );}
int secondary_fields_IRTS_RL_1(char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "channel5" CANLIB_SEPARATOR 
        "channel6" CANLIB_SEPARATOR 
        "channel7" CANLIB_SEPARATOR 
        "channel8"
    );}
int secondary_to_string_file_IRTS_RL_1(secondary_message_IRTS_RL_1* message, FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->channel5,
        message->channel6,
        message->channel7,
        message->channel8
    );}
int secondary_fields_file_IRTS_RL_1(FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "channel5" CANLIB_SEPARATOR 
        "channel6" CANLIB_SEPARATOR 
        "channel7" CANLIB_SEPARATOR 
        "channel8"
    );}

// ============== SERIALIZE ============== //

secondary_byte_size secondary_serialize_IRTS_RL_2(
    uint8_t* data,
    secondary_uint16 channel9,
    secondary_uint16 channel10,
    secondary_uint16 channel11,
    secondary_uint16 channel12
) {
    data[0] = channel9 & 255;
    data[1] = (channel9 >> 8) & 255;
    data[2] = channel10 & 255;
    data[3] = (channel10 >> 8) & 255;
    data[4] = channel11 & 255;
    data[5] = (channel11 >> 8) & 255;
    data[6] = channel12 & 255;
    data[7] = (channel12 >> 8) & 255;
    return 8;
}

secondary_byte_size secondary_serialize_struct_IRTS_RL_2(
    uint8_t* data,
    secondary_message_IRTS_RL_2* message
) {
    data[0] = message->channel9 & 255;
    data[1] = (message->channel9 >> 8) & 255;
    data[2] = message->channel10 & 255;
    data[3] = (message->channel10 >> 8) & 255;
    data[4] = message->channel11 & 255;
    data[5] = (message->channel11 >> 8) & 255;
    data[6] = message->channel12 & 255;
    data[7] = (message->channel12 >> 8) & 255;
    return 8;
}

// ============== DESERIALIZE ============== //

void secondary_deserialize_IRTS_RL_2(
    secondary_message_IRTS_RL_2* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 _timestamp
#endif // CANLIB_TIMESTAMP
) {
#ifdef CANLIB_TIMESTAMP
    message->_timestamp = _timestamp;
#endif // CANLIB_TIMESTAMP
    message->channel9 = data[0] | (data[1] << 8);
    message->channel10 = data[2] | (data[3] << 8);
    message->channel11 = data[4] | (data[5] << 8);
    message->channel12 = data[6] | (data[7] << 8);
}

// ============== STRING ============== //

int secondary_to_string_IRTS_RL_2(secondary_message_IRTS_RL_2* message, char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->channel9,
        message->channel10,
        message->channel11,
        message->channel12
    );}
int secondary_fields_IRTS_RL_2(char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "channel9" CANLIB_SEPARATOR 
        "channel10" CANLIB_SEPARATOR 
        "channel11" CANLIB_SEPARATOR 
        "channel12"
    );}
int secondary_to_string_file_IRTS_RL_2(secondary_message_IRTS_RL_2* message, FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->channel9,
        message->channel10,
        message->channel11,
        message->channel12
    );}
int secondary_fields_file_IRTS_RL_2(FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "channel9" CANLIB_SEPARATOR 
        "channel10" CANLIB_SEPARATOR 
        "channel11" CANLIB_SEPARATOR 
        "channel12"
    );}

// ============== SERIALIZE ============== //

secondary_byte_size secondary_serialize_IRTS_RL_3(
    uint8_t* data,
    secondary_uint16 channel13,
    secondary_uint16 channel14,
    secondary_uint16 channel15,
    secondary_uint16 channel16
) {
    data[0] = channel13 & 255;
    data[1] = (channel13 >> 8) & 255;
    data[2] = channel14 & 255;
    data[3] = (channel14 >> 8) & 255;
    data[4] = channel15 & 255;
    data[5] = (channel15 >> 8) & 255;
    data[6] = channel16 & 255;
    data[7] = (channel16 >> 8) & 255;
    return 8;
}

secondary_byte_size secondary_serialize_struct_IRTS_RL_3(
    uint8_t* data,
    secondary_message_IRTS_RL_3* message
) {
    data[0] = message->channel13 & 255;
    data[1] = (message->channel13 >> 8) & 255;
    data[2] = message->channel14 & 255;
    data[3] = (message->channel14 >> 8) & 255;
    data[4] = message->channel15 & 255;
    data[5] = (message->channel15 >> 8) & 255;
    data[6] = message->channel16 & 255;
    data[7] = (message->channel16 >> 8) & 255;
    return 8;
}

// ============== DESERIALIZE ============== //

void secondary_deserialize_IRTS_RL_3(
    secondary_message_IRTS_RL_3* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 _timestamp
#endif // CANLIB_TIMESTAMP
) {
#ifdef CANLIB_TIMESTAMP
    message->_timestamp = _timestamp;
#endif // CANLIB_TIMESTAMP
    message->channel13 = data[0] | (data[1] << 8);
    message->channel14 = data[2] | (data[3] << 8);
    message->channel15 = data[4] | (data[5] << 8);
    message->channel16 = data[6] | (data[7] << 8);
}

// ============== STRING ============== //

int secondary_to_string_IRTS_RL_3(secondary_message_IRTS_RL_3* message, char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->channel13,
        message->channel14,
        message->channel15,
        message->channel16
    );}
int secondary_fields_IRTS_RL_3(char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "channel13" CANLIB_SEPARATOR 
        "channel14" CANLIB_SEPARATOR 
        "channel15" CANLIB_SEPARATOR 
        "channel16"
    );}
int secondary_to_string_file_IRTS_RL_3(secondary_message_IRTS_RL_3* message, FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->channel13,
        message->channel14,
        message->channel15,
        message->channel16
    );}
int secondary_fields_file_IRTS_RL_3(FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "channel13" CANLIB_SEPARATOR 
        "channel14" CANLIB_SEPARATOR 
        "channel15" CANLIB_SEPARATOR 
        "channel16"
    );}

// ============== SERIALIZE ============== //

secondary_byte_size secondary_serialize_IRTS_RR_0(
    uint8_t* data,
    secondary_uint16 channel1,
    secondary_uint16 channel2,
    secondary_uint16 channel3,
    secondary_uint16 channel4
) {
    data[0] = channel1 & 255;
    data[1] = (channel1 >> 8) & 255;
    data[2] = channel2 & 255;
    data[3] = (channel2 >> 8) & 255;
    data[4] = channel3 & 255;
    data[5] = (channel3 >> 8) & 255;
    data[6] = channel4 & 255;
    data[7] = (channel4 >> 8) & 255;
    return 8;
}

secondary_byte_size secondary_serialize_struct_IRTS_RR_0(
    uint8_t* data,
    secondary_message_IRTS_RR_0* message
) {
    data[0] = message->channel1 & 255;
    data[1] = (message->channel1 >> 8) & 255;
    data[2] = message->channel2 & 255;
    data[3] = (message->channel2 >> 8) & 255;
    data[4] = message->channel3 & 255;
    data[5] = (message->channel3 >> 8) & 255;
    data[6] = message->channel4 & 255;
    data[7] = (message->channel4 >> 8) & 255;
    return 8;
}

// ============== DESERIALIZE ============== //

void secondary_deserialize_IRTS_RR_0(
    secondary_message_IRTS_RR_0* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 _timestamp
#endif // CANLIB_TIMESTAMP
) {
#ifdef CANLIB_TIMESTAMP
    message->_timestamp = _timestamp;
#endif // CANLIB_TIMESTAMP
    message->channel1 = data[0] | (data[1] << 8);
    message->channel2 = data[2] | (data[3] << 8);
    message->channel3 = data[4] | (data[5] << 8);
    message->channel4 = data[6] | (data[7] << 8);
}

// ============== STRING ============== //

int secondary_to_string_IRTS_RR_0(secondary_message_IRTS_RR_0* message, char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->channel1,
        message->channel2,
        message->channel3,
        message->channel4
    );}
int secondary_fields_IRTS_RR_0(char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "channel1" CANLIB_SEPARATOR 
        "channel2" CANLIB_SEPARATOR 
        "channel3" CANLIB_SEPARATOR 
        "channel4"
    );}
int secondary_to_string_file_IRTS_RR_0(secondary_message_IRTS_RR_0* message, FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->channel1,
        message->channel2,
        message->channel3,
        message->channel4
    );}
int secondary_fields_file_IRTS_RR_0(FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "channel1" CANLIB_SEPARATOR 
        "channel2" CANLIB_SEPARATOR 
        "channel3" CANLIB_SEPARATOR 
        "channel4"
    );}

// ============== SERIALIZE ============== //

secondary_byte_size secondary_serialize_IRTS_RR_1(
    uint8_t* data,
    secondary_uint16 channel5,
    secondary_uint16 channel6,
    secondary_uint16 channel7,
    secondary_uint16 channel8
) {
    data[0] = channel5 & 255;
    data[1] = (channel5 >> 8) & 255;
    data[2] = channel6 & 255;
    data[3] = (channel6 >> 8) & 255;
    data[4] = channel7 & 255;
    data[5] = (channel7 >> 8) & 255;
    data[6] = channel8 & 255;
    data[7] = (channel8 >> 8) & 255;
    return 8;
}

secondary_byte_size secondary_serialize_struct_IRTS_RR_1(
    uint8_t* data,
    secondary_message_IRTS_RR_1* message
) {
    data[0] = message->channel5 & 255;
    data[1] = (message->channel5 >> 8) & 255;
    data[2] = message->channel6 & 255;
    data[3] = (message->channel6 >> 8) & 255;
    data[4] = message->channel7 & 255;
    data[5] = (message->channel7 >> 8) & 255;
    data[6] = message->channel8 & 255;
    data[7] = (message->channel8 >> 8) & 255;
    return 8;
}

// ============== DESERIALIZE ============== //

void secondary_deserialize_IRTS_RR_1(
    secondary_message_IRTS_RR_1* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 _timestamp
#endif // CANLIB_TIMESTAMP
) {
#ifdef CANLIB_TIMESTAMP
    message->_timestamp = _timestamp;
#endif // CANLIB_TIMESTAMP
    message->channel5 = data[0] | (data[1] << 8);
    message->channel6 = data[2] | (data[3] << 8);
    message->channel7 = data[4] | (data[5] << 8);
    message->channel8 = data[6] | (data[7] << 8);
}

// ============== STRING ============== //

int secondary_to_string_IRTS_RR_1(secondary_message_IRTS_RR_1* message, char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->channel5,
        message->channel6,
        message->channel7,
        message->channel8
    );}
int secondary_fields_IRTS_RR_1(char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "channel5" CANLIB_SEPARATOR 
        "channel6" CANLIB_SEPARATOR 
        "channel7" CANLIB_SEPARATOR 
        "channel8"
    );}
int secondary_to_string_file_IRTS_RR_1(secondary_message_IRTS_RR_1* message, FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->channel5,
        message->channel6,
        message->channel7,
        message->channel8
    );}
int secondary_fields_file_IRTS_RR_1(FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "channel5" CANLIB_SEPARATOR 
        "channel6" CANLIB_SEPARATOR 
        "channel7" CANLIB_SEPARATOR 
        "channel8"
    );}

// ============== SERIALIZE ============== //

secondary_byte_size secondary_serialize_IRTS_RR_2(
    uint8_t* data,
    secondary_uint16 channel9,
    secondary_uint16 channel10,
    secondary_uint16 channel11,
    secondary_uint16 channel12
) {
    data[0] = channel9 & 255;
    data[1] = (channel9 >> 8) & 255;
    data[2] = channel10 & 255;
    data[3] = (channel10 >> 8) & 255;
    data[4] = channel11 & 255;
    data[5] = (channel11 >> 8) & 255;
    data[6] = channel12 & 255;
    data[7] = (channel12 >> 8) & 255;
    return 8;
}

secondary_byte_size secondary_serialize_struct_IRTS_RR_2(
    uint8_t* data,
    secondary_message_IRTS_RR_2* message
) {
    data[0] = message->channel9 & 255;
    data[1] = (message->channel9 >> 8) & 255;
    data[2] = message->channel10 & 255;
    data[3] = (message->channel10 >> 8) & 255;
    data[4] = message->channel11 & 255;
    data[5] = (message->channel11 >> 8) & 255;
    data[6] = message->channel12 & 255;
    data[7] = (message->channel12 >> 8) & 255;
    return 8;
}

// ============== DESERIALIZE ============== //

void secondary_deserialize_IRTS_RR_2(
    secondary_message_IRTS_RR_2* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 _timestamp
#endif // CANLIB_TIMESTAMP
) {
#ifdef CANLIB_TIMESTAMP
    message->_timestamp = _timestamp;
#endif // CANLIB_TIMESTAMP
    message->channel9 = data[0] | (data[1] << 8);
    message->channel10 = data[2] | (data[3] << 8);
    message->channel11 = data[4] | (data[5] << 8);
    message->channel12 = data[6] | (data[7] << 8);
}

// ============== STRING ============== //

int secondary_to_string_IRTS_RR_2(secondary_message_IRTS_RR_2* message, char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->channel9,
        message->channel10,
        message->channel11,
        message->channel12
    );}
int secondary_fields_IRTS_RR_2(char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "channel9" CANLIB_SEPARATOR 
        "channel10" CANLIB_SEPARATOR 
        "channel11" CANLIB_SEPARATOR 
        "channel12"
    );}
int secondary_to_string_file_IRTS_RR_2(secondary_message_IRTS_RR_2* message, FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->channel9,
        message->channel10,
        message->channel11,
        message->channel12
    );}
int secondary_fields_file_IRTS_RR_2(FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "channel9" CANLIB_SEPARATOR 
        "channel10" CANLIB_SEPARATOR 
        "channel11" CANLIB_SEPARATOR 
        "channel12"
    );}

// ============== SERIALIZE ============== //

secondary_byte_size secondary_serialize_IRTS_RR_3(
    uint8_t* data,
    secondary_uint16 channel13,
    secondary_uint16 channel14,
    secondary_uint16 channel15,
    secondary_uint16 channel16
) {
    data[0] = channel13 & 255;
    data[1] = (channel13 >> 8) & 255;
    data[2] = channel14 & 255;
    data[3] = (channel14 >> 8) & 255;
    data[4] = channel15 & 255;
    data[5] = (channel15 >> 8) & 255;
    data[6] = channel16 & 255;
    data[7] = (channel16 >> 8) & 255;
    return 8;
}

secondary_byte_size secondary_serialize_struct_IRTS_RR_3(
    uint8_t* data,
    secondary_message_IRTS_RR_3* message
) {
    data[0] = message->channel13 & 255;
    data[1] = (message->channel13 >> 8) & 255;
    data[2] = message->channel14 & 255;
    data[3] = (message->channel14 >> 8) & 255;
    data[4] = message->channel15 & 255;
    data[5] = (message->channel15 >> 8) & 255;
    data[6] = message->channel16 & 255;
    data[7] = (message->channel16 >> 8) & 255;
    return 8;
}

// ============== DESERIALIZE ============== //

void secondary_deserialize_IRTS_RR_3(
    secondary_message_IRTS_RR_3* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 _timestamp
#endif // CANLIB_TIMESTAMP
) {
#ifdef CANLIB_TIMESTAMP
    message->_timestamp = _timestamp;
#endif // CANLIB_TIMESTAMP
    message->channel13 = data[0] | (data[1] << 8);
    message->channel14 = data[2] | (data[3] << 8);
    message->channel15 = data[4] | (data[5] << 8);
    message->channel16 = data[6] | (data[7] << 8);
}

// ============== STRING ============== //

int secondary_to_string_IRTS_RR_3(secondary_message_IRTS_RR_3* message, char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->channel13,
        message->channel14,
        message->channel15,
        message->channel16
    );}
int secondary_fields_IRTS_RR_3(char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "channel13" CANLIB_SEPARATOR 
        "channel14" CANLIB_SEPARATOR 
        "channel15" CANLIB_SEPARATOR 
        "channel16"
    );}
int secondary_to_string_file_IRTS_RR_3(secondary_message_IRTS_RR_3* message, FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16 CANLIB_SEPARATOR 
        "%" PRIu16,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->channel13,
        message->channel14,
        message->channel15,
        message->channel16
    );}
int secondary_fields_file_IRTS_RR_3(FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "channel13" CANLIB_SEPARATOR 
        "channel14" CANLIB_SEPARATOR 
        "channel15" CANLIB_SEPARATOR 
        "channel16"
    );}

// ============== SERIALIZE ============== //

secondary_byte_size secondary_serialize_GPS_COORDS(
    uint8_t* data,
    secondary_float32 latitude,
    secondary_float32 longitude
) {
    data[0] = secondary_float32_to_bytes(latitude, 0);
    data[1] = secondary_float32_to_bytes(latitude, 1);
    data[2] = secondary_float32_to_bytes(latitude, 2);
    data[3] = secondary_float32_to_bytes(latitude, 3);
    data[4] = secondary_float32_to_bytes(longitude, 0);
    data[5] = secondary_float32_to_bytes(longitude, 1);
    data[6] = secondary_float32_to_bytes(longitude, 2);
    data[7] = secondary_float32_to_bytes(longitude, 3);
    return 8;
}

secondary_byte_size secondary_serialize_struct_GPS_COORDS(
    uint8_t* data,
    secondary_message_GPS_COORDS* message
) {
    data[0] = secondary_float32_to_bytes(message->latitude, 0);
    data[1] = secondary_float32_to_bytes(message->latitude, 1);
    data[2] = secondary_float32_to_bytes(message->latitude, 2);
    data[3] = secondary_float32_to_bytes(message->latitude, 3);
    data[4] = secondary_float32_to_bytes(message->longitude, 0);
    data[5] = secondary_float32_to_bytes(message->longitude, 1);
    data[6] = secondary_float32_to_bytes(message->longitude, 2);
    data[7] = secondary_float32_to_bytes(message->longitude, 3);
    return 8;
}

// ============== DESERIALIZE ============== //

void secondary_deserialize_GPS_COORDS(
    secondary_message_GPS_COORDS* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 _timestamp
#endif // CANLIB_TIMESTAMP
) {
#ifdef CANLIB_TIMESTAMP
    message->_timestamp = _timestamp;
#endif // CANLIB_TIMESTAMP
    message->latitude = ((secondary_float32_helper) {data[0] ,data[1] ,data[2] ,data[3]}).value;
    message->longitude = ((secondary_float32_helper) {data[4] ,data[5] ,data[6] ,data[7]}).value;
}

// ============== STRING ============== //

int secondary_to_string_GPS_COORDS(secondary_message_GPS_COORDS* message, char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIf32 CANLIB_SEPARATOR 
        "%" PRIf32,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->latitude,
        message->longitude
    );}
int secondary_fields_GPS_COORDS(char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "latitude" CANLIB_SEPARATOR 
        "longitude"
    );}
int secondary_to_string_file_GPS_COORDS(secondary_message_GPS_COORDS* message, FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIf32 CANLIB_SEPARATOR 
        "%" PRIf32,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->latitude,
        message->longitude
    );}
int secondary_fields_file_GPS_COORDS(FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "latitude" CANLIB_SEPARATOR 
        "longitude"
    );}

// ============== SERIALIZE ============== //

secondary_byte_size secondary_serialize_GPS_SPEED(
    uint8_t* data,
    secondary_uint16 speed
) {
    data[0] = speed & 255;
    data[1] = (speed >> 8) & 255;
    return 2;
}

secondary_byte_size secondary_serialize_struct_GPS_SPEED(
    uint8_t* data,
    secondary_message_GPS_SPEED* message
) {
    data[0] = message->speed & 255;
    data[1] = (message->speed >> 8) & 255;
    return 2;
}

// ============== DESERIALIZE ============== //

void secondary_deserialize_GPS_SPEED(
    secondary_message_GPS_SPEED* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 _timestamp
#endif // CANLIB_TIMESTAMP
) {
#ifdef CANLIB_TIMESTAMP
    message->_timestamp = _timestamp;
#endif // CANLIB_TIMESTAMP
    message->speed = data[0] | (data[1] << 8);
}

// ============== STRING ============== //

int secondary_to_string_GPS_SPEED(secondary_message_GPS_SPEED* message, char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIu16,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->speed
    );}
int secondary_fields_GPS_SPEED(char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "speed"
    );}
int secondary_to_string_file_GPS_SPEED(secondary_message_GPS_SPEED* message, FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIu16,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->speed
    );}
int secondary_fields_file_GPS_SPEED(FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "speed"
    );}

// ============== SERIALIZE ============== //

secondary_byte_size secondary_serialize_LAP_COUNT(
    uint8_t* data,
    secondary_uint32 timestamp,
    secondary_uint8 lap_count
) {
    data[0] = timestamp & 255;
    data[1] = (timestamp >> 8) & 255;
    data[2] = (timestamp >> 16) & 255;
    data[3] = (timestamp >> 24) & 255;
    data[4] = lap_count;
    return 5;
}

secondary_byte_size secondary_serialize_struct_LAP_COUNT(
    uint8_t* data,
    secondary_message_LAP_COUNT* message
) {
    data[0] = message->timestamp & 255;
    data[1] = (message->timestamp >> 8) & 255;
    data[2] = (message->timestamp >> 16) & 255;
    data[3] = (message->timestamp >> 24) & 255;
    data[4] = message->lap_count;
    return 5;
}

// ============== DESERIALIZE ============== //

void secondary_deserialize_LAP_COUNT(
    secondary_message_LAP_COUNT* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 _timestamp
#endif // CANLIB_TIMESTAMP
) {
#ifdef CANLIB_TIMESTAMP
    message->_timestamp = _timestamp;
#endif // CANLIB_TIMESTAMP
    message->timestamp = data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);
    message->lap_count = data[4];
}

// ============== STRING ============== //

int secondary_to_string_LAP_COUNT(secondary_message_LAP_COUNT* message, char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIu32 CANLIB_SEPARATOR 
        "%" PRIu8,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->timestamp,
        message->lap_count
    );}
int secondary_fields_LAP_COUNT(char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "timestamp" CANLIB_SEPARATOR 
        "lap_count"
    );}
int secondary_to_string_file_LAP_COUNT(secondary_message_LAP_COUNT* message, FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIu32 CANLIB_SEPARATOR 
        "%" PRIu8,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->timestamp,
        message->lap_count
    );}
int secondary_fields_file_LAP_COUNT(FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "timestamp" CANLIB_SEPARATOR 
        "lap_count"
    );}

// ============== SERIALIZE ============== //

secondary_byte_size secondary_serialize_PEDALS_OUTPUT(
    uint8_t* data,
    secondary_uint16 bse_front,
    secondary_uint16 bse_rear,
    secondary_uint8 apps
) {
    data[0] = bse_front & 255;
    data[1] = (bse_front >> 8) & 255;
    data[2] = bse_rear & 255;
    data[3] = (bse_rear >> 8) & 255;
    data[4] = apps;
    return 5;
}

secondary_byte_size secondary_serialize_struct_PEDALS_OUTPUT(
    uint8_t* data,
    secondary_message_PEDALS_OUTPUT* message
) {
    data[0] = message->bse_front & 255;
    data[1] = (message->bse_front >> 8) & 255;
    data[2] = message->bse_rear & 255;
    data[3] = (message->bse_rear >> 8) & 255;
    data[4] = message->apps;
    return 5;
}

// ============== DESERIALIZE ============== //

void secondary_deserialize_PEDALS_OUTPUT(
    secondary_message_PEDALS_OUTPUT* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 _timestamp
#endif // CANLIB_TIMESTAMP
) {
#ifdef CANLIB_TIMESTAMP
    message->_timestamp = _timestamp;
#endif // CANLIB_TIMESTAMP
    message->bse_front = data[0] | (data[1] << 8);
    message->bse_rear = data[2] | (data[3] << 8);
    message->apps = data[4];
}// ============== CONVERSION ============== //

void secondary_raw_to_conversion_PEDALS_OUTPUT(
    secondary_message_PEDALS_OUTPUT_conversion* conversion,
    secondary_message_PEDALS_OUTPUT* raw
){
#ifdef CANLIB_TIMESTAMP
    conversion->_timestamp = raw->_timestamp;
#endif // CANLIB_TIMESTAMP
    conversion->bse_front = (((secondary_float32)raw->bse_front) / 655.36) + 0;
    conversion->bse_rear = (((secondary_float32)raw->bse_rear) / 655.36) + 0;
    conversion->apps = raw->apps;
}
void secondary_conversion_to_raw_PEDALS_OUTPUT(
    secondary_message_PEDALS_OUTPUT* raw,
    secondary_message_PEDALS_OUTPUT_conversion* conversion
){
#ifdef CANLIB_TIMESTAMP
    raw->_timestamp = conversion->_timestamp;
#endif // CANLIB_TIMESTAMP
    raw->bse_front = (secondary_uint16)((conversion->bse_front + 0) * 655.36);
    raw->bse_rear = (secondary_uint16)((conversion->bse_rear + 0) * 655.36);
    raw->apps = conversion->apps;
}

// ============== STRING ============== //

int secondary_to_string_PEDALS_OUTPUT(secondary_message_PEDALS_OUTPUT_conversion* message, char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIf32 CANLIB_SEPARATOR 
        "%" PRIf32 CANLIB_SEPARATOR 
        "%" PRIu8,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->bse_front,
        message->bse_rear,
        message->apps
    );}
int secondary_fields_PEDALS_OUTPUT(char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "bse_front" CANLIB_SEPARATOR 
        "bse_rear" CANLIB_SEPARATOR 
        "apps"
    );}
int secondary_to_string_file_PEDALS_OUTPUT(secondary_message_PEDALS_OUTPUT_conversion* message, FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIf32 CANLIB_SEPARATOR 
        "%" PRIf32 CANLIB_SEPARATOR 
        "%" PRIu8,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->bse_front,
        message->bse_rear,
        message->apps
    );}
int secondary_fields_file_PEDALS_OUTPUT(FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "bse_front" CANLIB_SEPARATOR 
        "bse_rear" CANLIB_SEPARATOR 
        "apps"
    );}

// ============== SERIALIZE ============== //

secondary_byte_size secondary_serialize_CONTROL_OUTPUT(
    uint8_t* data,
    secondary_float32 right,
    secondary_float32 left
) {
    data[0] = secondary_float32_to_bytes(right, 0);
    data[1] = secondary_float32_to_bytes(right, 1);
    data[2] = secondary_float32_to_bytes(right, 2);
    data[3] = secondary_float32_to_bytes(right, 3);
    data[4] = secondary_float32_to_bytes(left, 0);
    data[5] = secondary_float32_to_bytes(left, 1);
    data[6] = secondary_float32_to_bytes(left, 2);
    data[7] = secondary_float32_to_bytes(left, 3);
    return 8;
}

secondary_byte_size secondary_serialize_struct_CONTROL_OUTPUT(
    uint8_t* data,
    secondary_message_CONTROL_OUTPUT* message
) {
    data[0] = secondary_float32_to_bytes(message->right, 0);
    data[1] = secondary_float32_to_bytes(message->right, 1);
    data[2] = secondary_float32_to_bytes(message->right, 2);
    data[3] = secondary_float32_to_bytes(message->right, 3);
    data[4] = secondary_float32_to_bytes(message->left, 0);
    data[5] = secondary_float32_to_bytes(message->left, 1);
    data[6] = secondary_float32_to_bytes(message->left, 2);
    data[7] = secondary_float32_to_bytes(message->left, 3);
    return 8;
}

// ============== DESERIALIZE ============== //

void secondary_deserialize_CONTROL_OUTPUT(
    secondary_message_CONTROL_OUTPUT* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 _timestamp
#endif // CANLIB_TIMESTAMP
) {
#ifdef CANLIB_TIMESTAMP
    message->_timestamp = _timestamp;
#endif // CANLIB_TIMESTAMP
    message->right = ((secondary_float32_helper) {data[0] ,data[1] ,data[2] ,data[3]}).value;
    message->left = ((secondary_float32_helper) {data[4] ,data[5] ,data[6] ,data[7]}).value;
}

// ============== STRING ============== //

int secondary_to_string_CONTROL_OUTPUT(secondary_message_CONTROL_OUTPUT* message, char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIf32 CANLIB_SEPARATOR 
        "%" PRIf32,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->right,
        message->left
    );}
int secondary_fields_CONTROL_OUTPUT(char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "right" CANLIB_SEPARATOR 
        "left"
    );}
int secondary_to_string_file_CONTROL_OUTPUT(secondary_message_CONTROL_OUTPUT* message, FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIf32 CANLIB_SEPARATOR 
        "%" PRIf32,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->right,
        message->left
    );}
int secondary_fields_file_CONTROL_OUTPUT(FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "right" CANLIB_SEPARATOR 
        "left"
    );}

// ============== SERIALIZE ============== //

secondary_byte_size secondary_serialize_STEERING_ANGLE(
    uint8_t* data,
    secondary_float32 angle
) {
    data[0] = secondary_float32_to_bytes(angle, 0);
    data[1] = secondary_float32_to_bytes(angle, 1);
    data[2] = secondary_float32_to_bytes(angle, 2);
    data[3] = secondary_float32_to_bytes(angle, 3);
    return 4;
}

secondary_byte_size secondary_serialize_struct_STEERING_ANGLE(
    uint8_t* data,
    secondary_message_STEERING_ANGLE* message
) {
    data[0] = secondary_float32_to_bytes(message->angle, 0);
    data[1] = secondary_float32_to_bytes(message->angle, 1);
    data[2] = secondary_float32_to_bytes(message->angle, 2);
    data[3] = secondary_float32_to_bytes(message->angle, 3);
    return 4;
}

// ============== DESERIALIZE ============== //

void secondary_deserialize_STEERING_ANGLE(
    secondary_message_STEERING_ANGLE* message,
    uint8_t* data
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 _timestamp
#endif // CANLIB_TIMESTAMP
) {
#ifdef CANLIB_TIMESTAMP
    message->_timestamp = _timestamp;
#endif // CANLIB_TIMESTAMP
    message->angle = ((secondary_float32_helper) {data[0] ,data[1] ,data[2] ,data[3]}).value;
}

// ============== STRING ============== //

int secondary_to_string_STEERING_ANGLE(secondary_message_STEERING_ANGLE* message, char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIf32,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->angle
    );}
int secondary_fields_STEERING_ANGLE(char* buffer) {
    return sprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "angle"
    );}
int secondary_to_string_file_STEERING_ANGLE(secondary_message_STEERING_ANGLE* message, FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        PRIXu64 CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "%" PRIf32,
#ifdef CANLIB_TIMESTAMP
        message->_timestamp,
#endif // CANLIB_TIMESTAMP
        message->angle
    );}
int secondary_fields_file_STEERING_ANGLE(FILE* buffer) {
    return fprintf(
        buffer,
#ifdef CANLIB_TIMESTAMP
        "_timestamp" CANLIB_SEPARATOR
#endif // CANLIB_TIMESTAMP
        "angle"
    );}


// ============== UTILS ============== //

void secondary_fields_from_id(canlib_message_id message_id, FILE *buffer) {
    switch (message_id) {
    case 1260:
        secondary_fields_file_IMU_ANGULAR_RATE(buffer);
        break;
    case 1261:
        secondary_fields_file_IMU_ACCELERATION(buffer);
        break;
    case 1460:
        secondary_fields_file_IRTS_FL_0(buffer);
        break;
    case 1461:
        secondary_fields_file_IRTS_FL_1(buffer);
        break;
    case 1462:
        secondary_fields_file_IRTS_FL_2(buffer);
        break;
    case 1463:
        secondary_fields_file_IRTS_FL_3(buffer);
        break;
    case 1464:
        secondary_fields_file_IRTS_FR_0(buffer);
        break;
    case 1465:
        secondary_fields_file_IRTS_FR_1(buffer);
        break;
    case 1466:
        secondary_fields_file_IRTS_FR_2(buffer);
        break;
    case 1467:
        secondary_fields_file_IRTS_FR_3(buffer);
        break;
    case 1468:
        secondary_fields_file_IRTS_RL_0(buffer);
        break;
    case 1469:
        secondary_fields_file_IRTS_RL_1(buffer);
        break;
    case 1470:
        secondary_fields_file_IRTS_RL_2(buffer);
        break;
    case 1471:
        secondary_fields_file_IRTS_RL_3(buffer);
        break;
    case 1472:
        secondary_fields_file_IRTS_RR_0(buffer);
        break;
    case 1473:
        secondary_fields_file_IRTS_RR_1(buffer);
        break;
    case 1474:
        secondary_fields_file_IRTS_RR_2(buffer);
        break;
    case 1475:
        secondary_fields_file_IRTS_RR_3(buffer);
        break;
    case 1025:
        secondary_fields_file_GPS_COORDS(buffer);
        break;
    case 1057:
        secondary_fields_file_GPS_SPEED(buffer);
        break;
    case 1089:
        secondary_fields_file_LAP_COUNT(buffer);
        break;
    case 769:
        secondary_fields_file_PEDALS_OUTPUT(buffer);
        break;
    case 801:
        secondary_fields_file_CONTROL_OUTPUT(buffer);
        break;
    case 258:
        secondary_fields_file_STEERING_ANGLE(buffer);
        break;
    }
}

void secondary_string_from_id(canlib_message_id message_id, void* message, FILE *buffer) {
    switch (message_id) {
        case 1260:
            secondary_to_string_file_IMU_ANGULAR_RATE((secondary_message_IMU_ANGULAR_RATE*) message, buffer);
        break;
        case 1261:
            secondary_to_string_file_IMU_ACCELERATION((secondary_message_IMU_ACCELERATION*) message, buffer);
        break;
        case 1460:
            secondary_to_string_file_IRTS_FL_0((secondary_message_IRTS_FL_0*) message, buffer);
        break;
        case 1461:
            secondary_to_string_file_IRTS_FL_1((secondary_message_IRTS_FL_1*) message, buffer);
        break;
        case 1462:
            secondary_to_string_file_IRTS_FL_2((secondary_message_IRTS_FL_2*) message, buffer);
        break;
        case 1463:
            secondary_to_string_file_IRTS_FL_3((secondary_message_IRTS_FL_3*) message, buffer);
        break;
        case 1464:
            secondary_to_string_file_IRTS_FR_0((secondary_message_IRTS_FR_0*) message, buffer);
        break;
        case 1465:
            secondary_to_string_file_IRTS_FR_1((secondary_message_IRTS_FR_1*) message, buffer);
        break;
        case 1466:
            secondary_to_string_file_IRTS_FR_2((secondary_message_IRTS_FR_2*) message, buffer);
        break;
        case 1467:
            secondary_to_string_file_IRTS_FR_3((secondary_message_IRTS_FR_3*) message, buffer);
        break;
        case 1468:
            secondary_to_string_file_IRTS_RL_0((secondary_message_IRTS_RL_0*) message, buffer);
        break;
        case 1469:
            secondary_to_string_file_IRTS_RL_1((secondary_message_IRTS_RL_1*) message, buffer);
        break;
        case 1470:
            secondary_to_string_file_IRTS_RL_2((secondary_message_IRTS_RL_2*) message, buffer);
        break;
        case 1471:
            secondary_to_string_file_IRTS_RL_3((secondary_message_IRTS_RL_3*) message, buffer);
        break;
        case 1472:
            secondary_to_string_file_IRTS_RR_0((secondary_message_IRTS_RR_0*) message, buffer);
        break;
        case 1473:
            secondary_to_string_file_IRTS_RR_1((secondary_message_IRTS_RR_1*) message, buffer);
        break;
        case 1474:
            secondary_to_string_file_IRTS_RR_2((secondary_message_IRTS_RR_2*) message, buffer);
        break;
        case 1475:
            secondary_to_string_file_IRTS_RR_3((secondary_message_IRTS_RR_3*) message, buffer);
        break;
        case 1025:
            secondary_to_string_file_GPS_COORDS((secondary_message_GPS_COORDS*) message, buffer);
        break;
        case 1057:
            secondary_to_string_file_GPS_SPEED((secondary_message_GPS_SPEED*) message, buffer);
        break;
        case 1089:
            secondary_to_string_file_LAP_COUNT((secondary_message_LAP_COUNT*) message, buffer);
        break;
        case 769:
            secondary_to_string_file_PEDALS_OUTPUT((secondary_message_PEDALS_OUTPUT_conversion*) message, buffer);
        break;
        case 801:
            secondary_to_string_file_CONTROL_OUTPUT((secondary_message_CONTROL_OUTPUT*) message, buffer);
        break;
        case 258:
            secondary_to_string_file_STEERING_ANGLE((secondary_message_STEERING_ANGLE*) message, buffer);
        break;
    }
}

void secondary_deserialize_from_id(
    canlib_message_id message_id,
    uint8_t* data,
    void* raw_message,
    void* message
#ifdef CANLIB_TIMESTAMP
    , secondary_uint64 timestamp
#endif // CANLIB_TIMESTAMP
) {
    switch (message_id) {
        case 1260:
            secondary_deserialize_IMU_ANGULAR_RATE(
                (secondary_message_IMU_ANGULAR_RATE*) raw_message,
                data
                #ifdef CANLIB_TIMESTAMP
                , timestamp
                #endif
            );
        break;
        case 1261:
            secondary_deserialize_IMU_ACCELERATION(
                (secondary_message_IMU_ACCELERATION*) raw_message,
                data
                #ifdef CANLIB_TIMESTAMP
                , timestamp
                #endif
            );
        break;
        case 1460:
            secondary_deserialize_IRTS_FL_0(
                (secondary_message_IRTS_FL_0*) raw_message,
                data
                #ifdef CANLIB_TIMESTAMP
                , timestamp
                #endif
            );
        break;
        case 1461:
            secondary_deserialize_IRTS_FL_1(
                (secondary_message_IRTS_FL_1*) raw_message,
                data
                #ifdef CANLIB_TIMESTAMP
                , timestamp
                #endif
            );
        break;
        case 1462:
            secondary_deserialize_IRTS_FL_2(
                (secondary_message_IRTS_FL_2*) raw_message,
                data
                #ifdef CANLIB_TIMESTAMP
                , timestamp
                #endif
            );
        break;
        case 1463:
            secondary_deserialize_IRTS_FL_3(
                (secondary_message_IRTS_FL_3*) raw_message,
                data
                #ifdef CANLIB_TIMESTAMP
                , timestamp
                #endif
            );
        break;
        case 1464:
            secondary_deserialize_IRTS_FR_0(
                (secondary_message_IRTS_FR_0*) raw_message,
                data
                #ifdef CANLIB_TIMESTAMP
                , timestamp
                #endif
            );
        break;
        case 1465:
            secondary_deserialize_IRTS_FR_1(
                (secondary_message_IRTS_FR_1*) raw_message,
                data
                #ifdef CANLIB_TIMESTAMP
                , timestamp
                #endif
            );
        break;
        case 1466:
            secondary_deserialize_IRTS_FR_2(
                (secondary_message_IRTS_FR_2*) raw_message,
                data
                #ifdef CANLIB_TIMESTAMP
                , timestamp
                #endif
            );
        break;
        case 1467:
            secondary_deserialize_IRTS_FR_3(
                (secondary_message_IRTS_FR_3*) raw_message,
                data
                #ifdef CANLIB_TIMESTAMP
                , timestamp
                #endif
            );
        break;
        case 1468:
            secondary_deserialize_IRTS_RL_0(
                (secondary_message_IRTS_RL_0*) raw_message,
                data
                #ifdef CANLIB_TIMESTAMP
                , timestamp
                #endif
            );
        break;
        case 1469:
            secondary_deserialize_IRTS_RL_1(
                (secondary_message_IRTS_RL_1*) raw_message,
                data
                #ifdef CANLIB_TIMESTAMP
                , timestamp
                #endif
            );
        break;
        case 1470:
            secondary_deserialize_IRTS_RL_2(
                (secondary_message_IRTS_RL_2*) raw_message,
                data
                #ifdef CANLIB_TIMESTAMP
                , timestamp
                #endif
            );
        break;
        case 1471:
            secondary_deserialize_IRTS_RL_3(
                (secondary_message_IRTS_RL_3*) raw_message,
                data
                #ifdef CANLIB_TIMESTAMP
                , timestamp
                #endif
            );
        break;
        case 1472:
            secondary_deserialize_IRTS_RR_0(
                (secondary_message_IRTS_RR_0*) raw_message,
                data
                #ifdef CANLIB_TIMESTAMP
                , timestamp
                #endif
            );
        break;
        case 1473:
            secondary_deserialize_IRTS_RR_1(
                (secondary_message_IRTS_RR_1*) raw_message,
                data
                #ifdef CANLIB_TIMESTAMP
                , timestamp
                #endif
            );
        break;
        case 1474:
            secondary_deserialize_IRTS_RR_2(
                (secondary_message_IRTS_RR_2*) raw_message,
                data
                #ifdef CANLIB_TIMESTAMP
                , timestamp
                #endif
            );
        break;
        case 1475:
            secondary_deserialize_IRTS_RR_3(
                (secondary_message_IRTS_RR_3*) raw_message,
                data
                #ifdef CANLIB_TIMESTAMP
                , timestamp
                #endif
            );
        break;
        case 1025:
            secondary_deserialize_GPS_COORDS(
                (secondary_message_GPS_COORDS*) raw_message,
                data
                #ifdef CANLIB_TIMESTAMP
                , timestamp
                #endif
            );
        break;
        case 1057:
            secondary_deserialize_GPS_SPEED(
                (secondary_message_GPS_SPEED*) raw_message,
                data
                #ifdef CANLIB_TIMESTAMP
                , timestamp
                #endif
            );
        break;
        case 1089:
            secondary_deserialize_LAP_COUNT(
                (secondary_message_LAP_COUNT*) raw_message,
                data
                #ifdef CANLIB_TIMESTAMP
                , timestamp
                #endif
            );
        break;
        case 769:
            secondary_deserialize_PEDALS_OUTPUT(
                (secondary_message_PEDALS_OUTPUT*) raw_message,
                data
                #ifdef CANLIB_TIMESTAMP
                , timestamp
                #endif
            );
            secondary_raw_to_conversion_PEDALS_OUTPUT(
                (secondary_message_PEDALS_OUTPUT_conversion*) message,
                (secondary_message_PEDALS_OUTPUT*) raw_message
            );
        break;
        case 801:
            secondary_deserialize_CONTROL_OUTPUT(
                (secondary_message_CONTROL_OUTPUT*) raw_message,
                data
                #ifdef CANLIB_TIMESTAMP
                , timestamp
                #endif
            );
        break;
        case 258:
            secondary_deserialize_STEERING_ANGLE(
                (secondary_message_STEERING_ANGLE*) raw_message,
                data
                #ifdef CANLIB_TIMESTAMP
                , timestamp
                #endif
            );
        break;
    }
}

void secondary_devices_new(secondary_devices* map) {
    (*map)[0].id = 1260;
    (*map)[0].raw_message = (void*) malloc(sizeof(secondary_message_IMU_ANGULAR_RATE));
    (*map)[0].message = NULL;

    (*map)[1].id = 1261;
    (*map)[1].raw_message = (void*) malloc(sizeof(secondary_message_IMU_ACCELERATION));
    (*map)[1].message = NULL;

    (*map)[2].id = 1460;
    (*map)[2].raw_message = (void*) malloc(sizeof(secondary_message_IRTS_FL_0));
    (*map)[2].message = NULL;

    (*map)[3].id = 1461;
    (*map)[3].raw_message = (void*) malloc(sizeof(secondary_message_IRTS_FL_1));
    (*map)[3].message = NULL;

    (*map)[4].id = 1462;
    (*map)[4].raw_message = (void*) malloc(sizeof(secondary_message_IRTS_FL_2));
    (*map)[4].message = NULL;

    (*map)[5].id = 1463;
    (*map)[5].raw_message = (void*) malloc(sizeof(secondary_message_IRTS_FL_3));
    (*map)[5].message = NULL;

    (*map)[6].id = 1464;
    (*map)[6].raw_message = (void*) malloc(sizeof(secondary_message_IRTS_FR_0));
    (*map)[6].message = NULL;

    (*map)[7].id = 1465;
    (*map)[7].raw_message = (void*) malloc(sizeof(secondary_message_IRTS_FR_1));
    (*map)[7].message = NULL;

    (*map)[8].id = 1466;
    (*map)[8].raw_message = (void*) malloc(sizeof(secondary_message_IRTS_FR_2));
    (*map)[8].message = NULL;

    (*map)[9].id = 1467;
    (*map)[9].raw_message = (void*) malloc(sizeof(secondary_message_IRTS_FR_3));
    (*map)[9].message = NULL;

    (*map)[10].id = 1468;
    (*map)[10].raw_message = (void*) malloc(sizeof(secondary_message_IRTS_RL_0));
    (*map)[10].message = NULL;

    (*map)[11].id = 1469;
    (*map)[11].raw_message = (void*) malloc(sizeof(secondary_message_IRTS_RL_1));
    (*map)[11].message = NULL;

    (*map)[12].id = 1470;
    (*map)[12].raw_message = (void*) malloc(sizeof(secondary_message_IRTS_RL_2));
    (*map)[12].message = NULL;

    (*map)[13].id = 1471;
    (*map)[13].raw_message = (void*) malloc(sizeof(secondary_message_IRTS_RL_3));
    (*map)[13].message = NULL;

    (*map)[14].id = 1472;
    (*map)[14].raw_message = (void*) malloc(sizeof(secondary_message_IRTS_RR_0));
    (*map)[14].message = NULL;

    (*map)[15].id = 1473;
    (*map)[15].raw_message = (void*) malloc(sizeof(secondary_message_IRTS_RR_1));
    (*map)[15].message = NULL;

    (*map)[16].id = 1474;
    (*map)[16].raw_message = (void*) malloc(sizeof(secondary_message_IRTS_RR_2));
    (*map)[16].message = NULL;

    (*map)[17].id = 1475;
    (*map)[17].raw_message = (void*) malloc(sizeof(secondary_message_IRTS_RR_3));
    (*map)[17].message = NULL;

    (*map)[18].id = 1025;
    (*map)[18].raw_message = (void*) malloc(sizeof(secondary_message_GPS_COORDS));
    (*map)[18].message = NULL;

    (*map)[19].id = 1057;
    (*map)[19].raw_message = (void*) malloc(sizeof(secondary_message_GPS_SPEED));
    (*map)[19].message = NULL;

    (*map)[20].id = 1089;
    (*map)[20].raw_message = (void*) malloc(sizeof(secondary_message_LAP_COUNT));
    (*map)[20].message = NULL;

    (*map)[21].id = 769;
    (*map)[21].raw_message = (void*) malloc(sizeof(secondary_message_PEDALS_OUTPUT));
    (*map)[21].message = (void*) malloc(sizeof(secondary_message_PEDALS_OUTPUT_conversion));

    (*map)[22].id = 801;
    (*map)[22].raw_message = (void*) malloc(sizeof(secondary_message_CONTROL_OUTPUT));
    (*map)[22].message = NULL;

    (*map)[23].id = 258;
    (*map)[23].raw_message = (void*) malloc(sizeof(secondary_message_STEERING_ANGLE));
    (*map)[23].message = NULL;

}

int secondary_devices_index_from_id(canlib_message_id message_id, secondary_devices* map) {
    for (int index = 0; index < secondary_NUMBER_OF_MESSAGES; index++) {
        if ((*map)[index].id == message_id)
            return index;
    }
    return -1;
}

#endif

#ifdef __cplusplus
}
#endif

#endif // secondary_NETWORK_H