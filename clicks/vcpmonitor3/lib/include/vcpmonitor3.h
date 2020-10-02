/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 * \brief This file contains API for VCP Monitor 3 Click driver.
 *
 * \addtogroup vcpmonitor3 VCP Monitor 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef VCPMONITOR3_H
#define VCPMONITOR3_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"
#include "drv_spi_master.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */

#define VCPMONITOR3_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.scl   = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
   cfg.sda   = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.io    = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
   cfg.alr   = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup communication Select communication
 * \{
 */
#define VCPMONITOR3_MASTER_I2C            0
#define VCPMONITOR3_MASTER_SPI            1
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define VCPMONITOR3_RETVAL  uint8_t

#define VCPMONITOR3_OK                    0x00
#define VCPMONITOR3_INIT_ERROR            0xFF
/** \} */


// Device I2C addresses

#define VCPMONITOR3_I2C_ADR_L_L           0x5C
#define VCPMONITOR3_I2C_ADR_L_H           0x5D
#define VCPMONITOR3_I2C_ADR_L_R           0x5E
#define VCPMONITOR3_I2C_ADR_R_L           0x64
#define VCPMONITOR3_I2C_ADR_R_H           0x65
#define VCPMONITOR3_I2C_ADR_R_R           0x66

// Page Select

#define VCPMONITOR3_PAGE_0                0x00
#define VCPMONITOR3_PAGE_1                0x01


// Register Map

// Definitions of available registers without those
// that are part of multiple byte values
// (e.g. accumulators).

// Registers on page 0

#define VCPMONITOR3_REG_GPIOSTATCL        0x67
#define VCPMONITOR3_REG_STATUS            0x80
#define VCPMONITOR3_REG_STATVT            0x81
#define VCPMONITOR3_REG_STATIP            0x82
#define VCPMONITOR3_REG_STATC             0x83
#define VCPMONITOR3_REG_STATE             0x84
#define VCPMONITOR3_REG_STATCEOF          0x85
#define VCPMONITOR3_REG_STATTB            0x86
#define VCPMONITOR3_REG_STATVDVCC         0x87
#define VCPMONITOR3_REG_STATUSM           0x88
#define VCPMONITOR3_REG_STATVTM           0x89
#define VCPMONITOR3_REG_STATIPM           0x8A
#define VCPMONITOR3_REG_STATCM            0x8B
#define VCPMONITOR3_REG_STATEM            0x8C
#define VCPMONITOR3_REG_STATCEOFM         0x8D
#define VCPMONITOR3_REG_STATTBM           0x8E
#define VCPMONITOR3_REG_STATVDVCCM        0x8F
#define VCPMONITOR3_REG_ACCICTL           0xE1
#define VCPMONITOR3_REG_ACCGPCTL          0xE3
#define VCPMONITOR3_REG_ACCIDB            0xE4
#define VCPMONITOR3_REG_ALERTBCTL         0xE8
#define VCPMONITOR3_REG_TBCTL             0xE9
#define VCPMONITOR3_REG_OPCTL             0xF0
#define VCPMONITOR3_REG_PGCTL             0xFF

// Definitions of all byte addresses of all multiple
// byte values (e.g. accumulators)

// Registers on page 0

#define VCPMONITOR3_REG_C1_47_40          0x00
#define VCPMONITOR3_REG_C1_39_32          0x01
#define VCPMONITOR3_REG_C1_31_24          0x02
#define VCPMONITOR3_REG_C1_23_16          0x03
#define VCPMONITOR3_REG_C1_15_8           0x04
#define VCPMONITOR3_REG_C1_7_0            0x05
#define VCPMONITOR3_REG_E1_47_40          0x06
#define VCPMONITOR3_REG_E1_39_32          0x07
#define VCPMONITOR3_REG_E1_31_24          0x08
#define VCPMONITOR3_REG_E1_23_16          0x09
#define VCPMONITOR3_REG_E1_15_8           0x0A
#define VCPMONITOR3_REG_E1_7_0            0x0B
#define VCPMONITOR3_REG_TB1_31_24         0x0C
#define VCPMONITOR3_REG_TB1_23_16         0x0D
#define VCPMONITOR3_REG_TB1_15_8          0x0E
#define VCPMONITOR3_REG_TB1_7_0           0x0F
#define VCPMONITOR3_REG_C2_47_40          0x10
#define VCPMONITOR3_REG_C2_39_32          0x11
#define VCPMONITOR3_REG_C2_31_24          0x12
#define VCPMONITOR3_REG_C2_23_16          0x13
#define VCPMONITOR3_REG_C2_15_8           0x14
#define VCPMONITOR3_REG_C2_7_0            0x15
#define VCPMONITOR3_REG_E2_47_40          0x16
#define VCPMONITOR3_REG_E2_39_32          0x17
#define VCPMONITOR3_REG_E2_31_24          0x18
#define VCPMONITOR3_REG_E2_23_16          0x19
#define VCPMONITOR3_REG_E2_15_8           0x1A
#define VCPMONITOR3_REG_E2_7_0            0x1B
#define VCPMONITOR3_REG_TB2_31_24         0x1C
#define VCPMONITOR3_REG_TB2_23_16         0x1D
#define VCPMONITOR3_REG_TB2_15_8          0x1E
#define VCPMONITOR3_REG_TB2_7_0           0x1F
#define VCPMONITOR3_REG_IMAX_15_8         0x40
#define VCPMONITOR3_REG_IMAX_7_0          0x41
#define VCPMONITOR3_REG_IMIN_15_8         0x42
#define VCPMONITOR3_REG_IMIN_7_0          0x43
#define VCPMONITOR3_REG_PMAX_15_8         0x44
#define VCPMONITOR3_REG_PMAX_7_0          0x45
#define VCPMONITOR3_REG_PMIN_15_8         0x46
#define VCPMONITOR3_REG_PMIN_7_0          0x47
#define VCPMONITOR3_REG_VMAX_15_8         0x50
#define VCPMONITOR3_REG_VMAX_7_0          0x51
#define VCPMONITOR3_REG_VMIN_15_8         0x52
#define VCPMONITOR3_REG_VMIN_7_0          0x53
#define VCPMONITOR3_REG_TEMPMAX_15_8      0x54
#define VCPMONITOR3_REG_TEMPMAX_7_0       0x55
#define VCPMONITOR3_REG_TEMPMIN_15_8      0x56
#define VCPMONITOR3_REG_TEMPMIN_7_0       0x57
#define VCPMONITOR3_REG_VDVCCMAX_15_8     0x58
#define VCPMONITOR3_REG_VDVCCMAX_7_0      0x59
#define VCPMONITOR3_REG_VDVCCMIN_15_8     0x5A
#define VCPMONITOR3_REG_VDVCCMIN_7_0      0x5B
#define VCPMONITOR3_REG_I_23_16           0x90
#define VCPMONITOR3_REG_I_15_8            0x91
#define VCPMONITOR3_REG_I_7_0             0x92
#define VCPMONITOR3_REG_P_23_16           0x93
#define VCPMONITOR3_REG_P_15_8            0x94
#define VCPMONITOR3_REG_P_7_0             0x95
#define VCPMONITOR3_REG_V_15_8            0xA0
#define VCPMONITOR3_REG_V_7_0             0xA1
#define VCPMONITOR3_REG_TEMP_15_8         0xA2
#define VCPMONITOR3_REG_TEMP_7_0          0xA3
#define VCPMONITOR3_REG_VDVCC_15_8        0xA4
#define VCPMONITOR3_REG_VDVCC_7_0         0xA5
#define VCPMONITOR3_REG_IH1_23_16         0xB0
#define VCPMONITOR3_REG_IH1_15_8          0xB1
#define VCPMONITOR3_REG_IH1_7_0           0xB2
#define VCPMONITOR3_REG_IH2_23_16         0xB3
#define VCPMONITOR3_REG_IH2_15_8          0xB4
#define VCPMONITOR3_REG_IH2_7_0           0xB5
#define VCPMONITOR3_REG_IH3_23_16         0xB6
#define VCPMONITOR3_REG_IH3_15_8          0xB7
#define VCPMONITOR3_REG_IH3_7_0           0xB8
#define VCPMONITOR3_REG_IH4_23_16         0xB9
#define VCPMONITOR3_REG_IH4_15_8          0xBA
#define VCPMONITOR3_REG_IH4_7_0           0xBB
#define VCPMONITOR3_REG_IH5_23_16         0xBC
#define VCPMONITOR3_REG_IH5_15_8          0xBD
#define VCPMONITOR3_REG_IH5_7_0           0xBE

// Registers on page 1

#define VCPMONITOR3_REG_C1TH_47_40        0x00
#define VCPMONITOR3_REG_C1TH_39_32        0x01
#define VCPMONITOR3_REG_C1TH_31_24        0x02
#define VCPMONITOR3_REG_C1TH_23_16        0x03
#define VCPMONITOR3_REG_C1TH_15_8         0x04
#define VCPMONITOR3_REG_C1TH_7_0          0x05
#define VCPMONITOR3_REG_C1TL_47_40        0x06
#define VCPMONITOR3_REG_C1TL_39_32        0x07
#define VCPMONITOR3_REG_C1TL_31_24        0x08
#define VCPMONITOR3_REG_C1TL_23_16        0x09
#define VCPMONITOR3_REG_C1TL_15_8         0x0A
#define VCPMONITOR3_REG_C1TL_7_0          0x0B
#define VCPMONITOR3_REG_TB1TH_31_24       0x0C
#define VCPMONITOR3_REG_TB1TH_23_16       0x0D
#define VCPMONITOR3_REG_TB1TH_15_8        0x0E
#define VCPMONITOR3_REG_TB1TH_7_0         0x0F
#define VCPMONITOR3_REG_E1TH_47_40        0x10
#define VCPMONITOR3_REG_E1TH_39_32        0x11
#define VCPMONITOR3_REG_E1TH_31_24        0x12
#define VCPMONITOR3_REG_E1TH_23_16        0x13
#define VCPMONITOR3_REG_E1TH_15_8         0x14
#define VCPMONITOR3_REG_E1TH_7_0          0x15
#define VCPMONITOR3_REG_E1TL_47_40        0x16
#define VCPMONITOR3_REG_E1TL_39_32        0x17
#define VCPMONITOR3_REG_E1TL_31_24        0x18
#define VCPMONITOR3_REG_E1TL_23_16        0x19
#define VCPMONITOR3_REG_E1TL_15_8         0x1A
#define VCPMONITOR3_REG_E1TL_7_0          0x1B
#define VCPMONITOR3_REG_C2TH_47_40        0x20
#define VCPMONITOR3_REG_C2TH_39_32        0x21
#define VCPMONITOR3_REG_C2TH_31_24        0x22
#define VCPMONITOR3_REG_C2TH_23_16        0x23
#define VCPMONITOR3_REG_C2TH_15_8         0x24
#define VCPMONITOR3_REG_C2TH_7_0          0x25
#define VCPMONITOR3_REG_C2TL_47_40        0x26
#define VCPMONITOR3_REG_C2TL_39_32        0x27
#define VCPMONITOR3_REG_C2TL_31_24        0x28
#define VCPMONITOR3_REG_C2TL_23_16        0x29
#define VCPMONITOR3_REG_C2TL_15_8         0x2A
#define VCPMONITOR3_REG_C2TL_7_0          0x2B
#define VCPMONITOR3_REG_TB2TH_31_24       0x2C
#define VCPMONITOR3_REG_TB2TH_23_16       0x2D
#define VCPMONITOR3_REG_TB2TH_15_8        0x2E
#define VCPMONITOR3_REG_TB2TH_7_0         0x2F
#define VCPMONITOR3_REG_E2TH_47_40        0x30
#define VCPMONITOR3_REG_E2TH_39_32        0x31
#define VCPMONITOR3_REG_E2TH_31_24        0x32
#define VCPMONITOR3_REG_E2TH_23_16        0x33
#define VCPMONITOR3_REG_E2TH_15_8         0x34
#define VCPMONITOR3_REG_E2TH_7_0          0x35
#define VCPMONITOR3_REG_E2TL_47_40        0x36
#define VCPMONITOR3_REG_E2TL_39_32        0x37
#define VCPMONITOR3_REG_E2TL_31_24        0x38
#define VCPMONITOR3_REG_E2TL_23_16        0x39
#define VCPMONITOR3_REG_E2TL_15_8         0x3A
#define VCPMONITOR3_REG_E2TL_7_0          0x3B
#define VCPMONITOR3_REG_ITH_15_8          0x80
#define VCPMONITOR3_REG_ITH_7_0           0x81
#define VCPMONITOR3_REG_ITL_15_8          0x82
#define VCPMONITOR3_REG_ITL_7_0           0x83
#define VCPMONITOR3_REG_PTH_15_8          0x84
#define VCPMONITOR3_REG_PTH_7_0           0x85
#define VCPMONITOR3_REG_PTL_15_8          0x86
#define VCPMONITOR3_REG_PTL_7_0           0x87
#define VCPMONITOR3_REG_VTH_15_8          0x90
#define VCPMONITOR3_REG_VTH_7_0           0x91
#define VCPMONITOR3_REG_VTL_15_8          0x92
#define VCPMONITOR3_REG_VTL_7_0           0x93
#define VCPMONITOR3_REG_TEMPTH_15_8       0x94
#define VCPMONITOR3_REG_TEMPTH_7_0        0x95
#define VCPMONITOR3_REG_TEMPTL_15_8       0x96
#define VCPMONITOR3_REG_TEMPTL_7_0        0x97
#define VCPMONITOR3_REG_VDVCCTH_15_8      0x98
#define VCPMONITOR3_REG_VDVCCTH_7_0       0x99
#define VCPMONITOR3_REG_VDVCCTL_15_8      0x9A
#define VCPMONITOR3_REG_VDVCCTL_7_0       0x9B
#define VCPMONITOR3_REG_TEMPTFANH_15_8    0x9C
#define VCPMONITOR3_REG_TEMPTFANH_7_0     0x9D
#define VCPMONITOR3_REG_TEMPTFANL_15_8    0x9E
#define VCPMONITOR3_REG_TEMPTFANL_7_0     0x9F

// Definitions of all available multiple byte values
// (e.g. accumulators)

// Registers on page 0

#define VCPMONITOR3_VAL_C1                0x00
#define VCPMONITOR3_VAL_E1                0x06
#define VCPMONITOR3_VAL_TB1               0x0C
#define VCPMONITOR3_VAL_C2                0x10
#define VCPMONITOR3_VAL_E2                0x16
#define VCPMONITOR3_VAL_TB2               0x1C
#define VCPMONITOR3_VAL_IMAX              0x40
#define VCPMONITOR3_VAL_IMIN              0x42
#define VCPMONITOR3_VAL_PMAX              0x44
#define VCPMONITOR3_VAL_PMIN              0x46
#define VCPMONITOR3_VAL_VMAX              0x50
#define VCPMONITOR3_VAL_VMIN              0x52
#define VCPMONITOR3_VAL_TEMPMAX           0x54
#define VCPMONITOR3_VAL_TEMPMIN           0x56
#define VCPMONITOR3_VAL_VDVCCMAX          0x58
#define VCPMONITOR3_VAL_VDVCCMIN          0x5A
#define VCPMONITOR3_VAL_I                 0x90
#define VCPMONITOR3_VAL_P                 0x93
#define VCPMONITOR3_VAL_V                 0xA0
#define VCPMONITOR3_VAL_TEMP              0xA2
#define VCPMONITOR3_VAL_VDVCC             0xA4
#define VCPMONITOR3_VAL_IH1               0xB0
#define VCPMONITOR3_VAL_IH2               0xB3
#define VCPMONITOR3_VAL_IH3               0xB6
#define VCPMONITOR3_VAL_IH4               0xB9
#define VCPMONITOR3_VAL_IH5               0xBC

// Registers on page 1

#define VCPMONITOR3_VAL_C1TH              0x00
#define VCPMONITOR3_VAL_C1TL              0x06
#define VCPMONITOR3_VAL_TB1TH             0x0C
#define VCPMONITOR3_VAL_E1TH              0x10
#define VCPMONITOR3_VAL_E1TL              0x16
#define VCPMONITOR3_VAL_C2TH              0x20
#define VCPMONITOR3_VAL_C2TL              0x26
#define VCPMONITOR3_VAL_TB2TH             0x2C
#define VCPMONITOR3_VAL_E2TH              0x30
#define VCPMONITOR3_VAL_E2TL              0x36
#define VCPMONITOR3_VAL_ITH               0x80
#define VCPMONITOR3_VAL_ITL               0x82
#define VCPMONITOR3_VAL_PTH               0x84
#define VCPMONITOR3_VAL_PTL               0x86
#define VCPMONITOR3_VAL_VTH               0x90
#define VCPMONITOR3_VAL_VTL               0x92
#define VCPMONITOR3_VAL_TEMPTH            0x94
#define VCPMONITOR3_VAL_TEMPTL            0x96
#define VCPMONITOR3_VAL_VDVCCTH           0x98
#define VCPMONITOR3_VAL_VDVCCTL           0x9A
#define VCPMONITOR3_VAL_TEMPTFANH         0x9C
#define VCPMONITOR3_VAL_TEMPTFANL         0x9E

// LSB values

#define VCPMONITOR3_LSB_IMAX              12.0
#define VCPMONITOR3_LSB_IMIN              12.0
#define VCPMONITOR3_LSB_PMAX              200.0
#define VCPMONITOR3_LSB_PMIN              200.0
#define VCPMONITOR3_LSB_VMAX              2.0
#define VCPMONITOR3_LSB_VMIN              2.0
#define VCPMONITOR3_LSB_TEMPMAX           0.204
#define VCPMONITOR3_OFFS_TEMPMAX          5.5
#define VCPMONITOR3_LSB_TEMPMIN           0.204
#define VCPMONITOR3_OFFS_TEMPMIN          5.5
#define VCPMONITOR3_LSB_VDVCCMAX          145.0
#define VCPMONITOR3_LSB_VDVCCMIN          145.0
#define VCPMONITOR3_LSB_I                 3.0
#define VCPMONITOR3_LSB_P                 50.0
#define VCPMONITOR3_LSB_V                 2.0
#define VCPMONITOR3_LSB_TEMP              0.204
#define VCPMONITOR3_OFFS_TEMP             5.5
#define VCPMONITOR3_LSB_VDVCC             145.0
#define VCPMONITOR3_LSB_IH1               3.0
#define VCPMONITOR3_LSB_IH2               3.0
#define VCPMONITOR3_LSB_IH3               3.0
#define VCPMONITOR3_LSB_IH4               3.0
#define VCPMONITOR3_LSB_IH5               3.0
#define VCPMONITOR3_LSB_C1                0.0000011933326
#define VCPMONITOR3_LSB_E1                0.000019888856
#define VCPMONITOR3_LSB_TB1               0.0003977765
#define VCPMONITOR3_LSB_C2                0.0000011933326
#define VCPMONITOR3_LSB_E2                0.000019888856
#define VCPMONITOR3_LSB_TB2               0.0003977765

// Operation Control

#define VCPMONITOR3_NORM_OP               0x00
#define VCPMONITOR3_SHDN                  0x01
#define VCPMONITOR3_CLR                   0x02
#define VCPMONITOR3_SSHOT                 0x04
#define VCPMONITOR3_CONT                  0x08
#define VCPMONITOR3_RST                   0x80

// Status

#define VCPMONITOR3_UVLOA                 0x01
#define VCPMONITOR3_PORA                  0x02
#define VCPMONITOR3_UVLOSTBY              0x04
#define VCPMONITOR3_UVLOD                 0x08
#define VCPMONITOR3_UPDATE                0x10
#define VCPMONITOR3_ADCERR                0x20
#define VCPMONITOR3_TBERR                 0x40

// SPI Read and Write Commands

#define VCPMONITOR3_SPI_RD_CMD            0x01
#define VCPMONITOR3_SPI_WR_CMD            0x00

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Communication type.
 */
typedef uint8_t  vcpmonitor3_select_t;

/**
 * @brief Master Input/Output type.
 */
typedef void ( *vcpmonitor3_master_io_t )( struct vcpmonitor3_s*, uint8_t, uint8_t*, uint8_t );

/**
 * @brief Click ctx object definition.
 */
typedef struct vcpmonitor3_s
{
    // Output pins 

    digital_out_t cs;
    digital_out_t io;

    // Input pins 

    digital_in_t alr;
    
    // Modules 

    i2c_master_t i2c;
    spi_master_t spi;

    // ctx variable 

   uint8_t slave_address;
   pin_name_t chip_select;
   vcpmonitor3_master_io_t write_f;
   vcpmonitor3_master_io_t read_f;
   vcpmonitor3_select_t master_sel;

} vcpmonitor3_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    pin_name_t miso;
    pin_name_t mosi;
    pin_name_t sck;
    pin_name_t cs;
    
    // Additional gpio pins 

    pin_name_t io;
    pin_name_t alr;

    // static variable 

   uint32_t i2c_speed;
   uint8_t  i2c_address;

   uint32_t spi_speed;
   spi_master_mode_t  spi_mode;
   spi_master_chip_select_polarity_t cs_polarity;

   vcpmonitor3_select_t sel;

} vcpmonitor3_cfg_t;

/** \} */ // End types group
// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS
/**
 * \defgroup public_function Public function
 * \{
 */

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Config Object Initialization function.
 *
 * @param cfg  Click configuration structure.
 *
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void vcpmonitor3_cfg_setup ( vcpmonitor3_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
VCPMONITOR3_RETVAL vcpmonitor3_init ( vcpmonitor3_t *ctx, vcpmonitor3_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for VCP Monitor 3 click.
 */
void vcpmonitor3_default_cfg ( vcpmonitor3_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx        Click object.
 * @param reg        Register address.
 * @param data_buf   Output data buf
 * @param len        Number of the bytes to be read
 *
 * @description This function writes data to the desired register.
 */
void vcpmonitor3_generic_write ( vcpmonitor3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx      Click object.
 * @param reg      Register address.
 * @param data_buf Data buf to be written.
 * @param len      Number of the bytes in data buf.
 *
 * @description This function reads data from the desired register.
 */
void vcpmonitor3_generic_read ( vcpmonitor3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Write Data To Page 0 function
 *
 * @param ctx      Click object. 
 * @param reg      8-bit register address
 * @param wr_data  8-bit write data
 * @param n_bytes  16-bit number of bytes
 *
 * @description Writes user defined number of bytes into page 0 registers defined by 8-bit
 * register address
**/
void vcpmonitor3_wr_page_0 ( vcpmonitor3_t *ctx, uint8_t reg, uint8_t *wr_data, uint8_t n_bytes );

/**
 * @brief Read Data From Page 0 function
 *
 * @param ctx      Click object. 
 * @param reg      8-bit register address
 * @param rd_data  8-bit read data
 * @param n_bytes  16-bit number of bytes
 *
 * @description Reads user defined number of bytes from page 0 registers defined by 8-bit
 * register address
**/
void vcpmonitor3_rd_page_0 ( vcpmonitor3_t *ctx, uint8_t reg, uint8_t *rd_data, uint8_t n_bytes );

/**
 * @brief Write Data To Page 1 function
 *
 * @param ctx      Click object.  
 * @param reg      8-bit register address
 * @param wr_data  8-bit write data
 * @param n_bytes  16-bit number of bytes
 *
 * @description Writes user defined number of bytes into page 1 registers defined by 8-bit
 * register address
**/
void vcpmonitor3_wr_page_1 ( vcpmonitor3_t *ctx, uint8_t reg, uint8_t *wr_data, uint8_t n_bytes );

/**
 * @brief Read Data From Page 1 function
 *
 * @param ctx      Click object.  
 * @param reg      8-bit register address
 * @param rd_data  8-bit read data
 * @param n_bytes  16-bit number of bytes
 *
 * @description Reads user defined number of bytes from page 1 registers defined by 8-bit
 * register address
**/
void vcpmonitor3_rd_page_1 ( vcpmonitor3_t *ctx, uint8_t reg, uint8_t *rd_data, uint8_t n_bytes );

/**
 * @brief Set Operation Mode function
 *
 * @param ctx      Click object.  
 * @param op_mode  value that defines operation mode
 *
 * @description Function is used to select operation mode.
**/
void vcpmonitor3_set_op_mode ( vcpmonitor3_t *ctx, uint8_t op_mode );

/**
 * @brief Read Current in Amps function
 *
 * @param ctx      Click object.  
 *
 * @returns result float value representing current in Amperes
 *
 * @description Function is used to get current in Amperes.
**/
float vcpmonitor3_read_i ( vcpmonitor3_t *ctx );

/**
 * @brief Read Power in Watts function
 *
 * @param ctx      Click object.  
 *
 * @returns result float value representing power in Watts
 *
 * @description Function is used to get power in Watts.
**/
float vcpmonitor3_read_p ( vcpmonitor3_t *ctx );

/**
 * @brief Read Voltage in Volts function
 *
 * @param ctx      Click object. 
 *
 * @returns result float value voltage in Volts
 *
 * @description Function is used to get voltage in Volts.
**/
float vcpmonitor3_read_v ( vcpmonitor3_t *ctx );

/**
 * @brief Read Die Temperature in degrees Centigrade function
 *
 * @param ctx      Click object.
 * 
 * @returns result float value representing die temperature in degrees Centigrade
 *
 * @description Function is used to get die temperature in degrees Centigrade.
**/
float vcpmonitor3_read_temp ( vcpmonitor3_t *ctx );

/**
 * @brief Read Voltage at DVCC in Volts function
 *
 * @param ctx      Click object.
 * 
 * @returns result float value representing voltage at DVCC in Volts
 *
 * @description Function is used to get die voltage at DVCC in Volts.
**/
float vcpmonitor3_read_vcc ( vcpmonitor3_t *ctx );

/**
 * @brief Read Charge in Coulombs function
 *
 * @param ctx           Click object. 
 * @param accu_set1    
 * <pre>
 *    - 0 : read accumulated quantities set 1
 *    - 1 : read accumulated quantities set 2
 * </pre> 
 *
 * @returns result float value representing charge in Coulombs
 *
 * @description Function is used to get charge in Coulombs.
**/
float vcpmonitor3_read_c ( vcpmonitor3_t *ctx, uint8_t accu_set1 );

/**
 * @brief Read Energy in Joules function
 *
 * @param ctx           Click object.  
 * @param accu_set1 
 * <pre>
 *    - 0 : read accumulated quantities set 1
 *    - 1 : read accumulated quantities set 2
 * </pre>  
 *
 * @returns result float value representing energy in Joules
 *
 * @description Function is used to get energy in Joules.
**/
float vcpmonitor3_read_e ( vcpmonitor3_t *ctx, uint8_t accu_set1 );

/**
 * @brief Read Time in Seconds function
 *
 * @param ctx           Click object.  
 * @param accu_set1   
 * <pre>  
 *    - 0 : read accumulated quantities set 1
 *    - 1 : read accumulated quantities set 2
 * </pre> 
 *
 * @returns result float value representing time in Seconds
 *
 * @description Function is used to get time in Seconds.
**/
float vcpmonitor3_read_tb ( vcpmonitor3_t *ctx, uint8_t accu_set1 );

/**
 * @brief Get Interrupt state function
 *
 * @param ctx           Click object.  
 * @returns
 * <pre>   
 * - 1 : Interrupt has not occured
 * - 0 : Interrupt has occured
 * </pre>  
 *
 * @description Function is used to check if an interrupt has occured.
**/
uint8_t vcpmonitor3_get_int ( vcpmonitor3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _VCPMONITOR3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
