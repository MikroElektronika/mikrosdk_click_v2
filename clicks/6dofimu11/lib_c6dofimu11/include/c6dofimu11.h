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
 * \brief This file contains API for 6DOF IMU 11 Click driver.
 *
 * \addtogroup c6dofimu11 6DOF IMU 11 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef C6DOFIMU11_H
#define C6DOFIMU11_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define C6DOFIMU11_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.gp1 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.gp2 = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define C6DOFIMU11_RETVAL  uint8_t

#define C6DOFIMU11_OK           0x00
#define C6DOFIMU11_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup slave_address Slave address
 * \{
 */
#define C6DOFIMU11_I2C_SLAVE_ADDRESS_GND                            0x0E
#define C6DOFIMU11_I2C_SLAVE_ADDRESS_VCC                            0x0F

/** \} */

/**
 * \defgroup register_map Register map
 * \{
 */
#define C6DOFIMU11_WHO_AM_I                                         0x00
#define C6DOFIMU11_INS1                                             0x01
#define C6DOFIMU11_INS2                                             0x02
#define C6DOFIMU11_INS3                                             0x03
#define C6DOFIMU11_INL                                              0x05
#define C6DOFIMU11_ACCEL_XOUT_L                                     0x0A
#define C6DOFIMU11_ACCEL_XOUT_H                                     0x0B
#define C6DOFIMU11_ACCEL_YOUT_L                                     0x0C
#define C6DOFIMU11_ACCEL_YOUT_H                                     0x0D
#define C6DOFIMU11_ACCEL_ZOUT_L                                     0x0E
#define C6DOFIMU11_ACCEL_ZOUT_H                                     0x0F
#define C6DOFIMU11_MAG_XOUT_L                                       0x10
#define C6DOFIMU11_MAG_XOUT_H                                       0x11
#define C6DOFIMU11_MAG_YOUT_L                                       0x12
#define C6DOFIMU11_MAG_YOUT_H                                       0x13
#define C6DOFIMU11_MAG_ZOUT_L                                       0x14
#define C6DOFIMU11_MAG_ZOUT_H                                       0x15
#define C6DOFIMU11_TEMP_OUT_L                                       0x16
#define C6DOFIMU11_TEMP_OUT_H                                       0x17
#define C6DOFIMU11_INC1                                             0x2A
#define C6DOFIMU11_INC2                                             0x2B
#define C6DOFIMU11_INC3                                             0x2C
#define C6DOFIMU11_INC4                                             0x2D
#define C6DOFIMU11_INC5                                             0x2E
#define C6DOFIMU11_AMI_CNTL1                                        0x2F
#define C6DOFIMU11_AMI_CNTL2                                        0x30
#define C6DOFIMU11_AMI_CNTL3                                        0x31
#define C6DOFIMU11_MMI_CNTL1                                        0x32
#define C6DOFIMU11_MMI_CNTL2                                        0x33
#define C6DOFIMU11_MMI_CNTL3                                        0x34
#define C6DOFIMU11_FFI_CNTL1                                        0x35
#define C6DOFIMU11_FFI_CNTL2                                        0x36
#define C6DOFIMU11_FFI_CNTL3                                        0x37
#define C6DOFIMU11_ODCNTL                                           0x38
#define C6DOFIMU11_CNTL1                                            0x39
#define C6DOFIMU11_CNTL2                                            0x3A
#define C6DOFIMU11_COTR                                             0x3C
#define C6DOFIMU11_BUF_CTRL_1                                       0x77
#define C6DOFIMU11_BUF_CTRL_2                                       0x78
#define C6DOFIMU11_BUF_CTRL_3                                       0x79
#define C6DOFIMU11_BUF_CLEAR                                        0x7A
#define C6DOFIMU11_BUF_STATUS_1                                     0x7B
#define C6DOFIMU11_BUF_STATUS_2                                     0x7C
#define C6DOFIMU11_BUF_STATUS_3                                     0x7D
#define C6DOFIMU11_BUF_READ                                         0x7E

/** \} */

/**
 * \defgroup register_bits Register bits
 * \{
 */
#define C6DOFIMU11_WHO_AM_I_WIA_ID                                  0x2D
#define C6DOFIMU11_INS1_INT_NO_INT                                  0x00
#define C6DOFIMU11_INS1_INT_INT                                     0x80
#define C6DOFIMU11_INS1_BFI_BUFF_NOT_FULL                           0x00
#define C6DOFIMU11_INS1_BFI_BUFF_FULL                               0x40
#define C6DOFIMU11_INS1_WMI_MARK_NOT_REACHED                        0x00
#define C6DOFIMU11_INS1_WMI_MARK_REACHED                            0x20
#define C6DOFIMU11_INS1_DRDY_A_NOT_AVAILABLE                        0x00
#define C6DOFIMU11_INS1_DRDY_A_AVAILABLE                            0x10
#define C6DOFIMU11_INS1_DRDY_M_NOT_AVAILABLE                        0x00
#define C6DOFIMU11_INS1_DRDY_M_AVAILABLE                            0x08
#define C6DOFIMU11_INS1_FFI_NO_FFI                                  0x00
#define C6DOFIMU11_INS1_FFI_FFI                                     0x04
#define C6DOFIMU11_INS1_AMI_NO_MOTION                               0x00
#define C6DOFIMU11_INS1_AMI_MOTION                                  0x02
#define C6DOFIMU11_INS1_MMI_NO_MOTION                               0x00
#define C6DOFIMU11_INS1_MMI_MOTION                                  0x01
#define C6DOFIMU11_INS2_AXNI                                        0x20
#define C6DOFIMU11_INS2_AXPI                                        0x10
#define C6DOFIMU11_INS2_AYNI                                        0x08
#define C6DOFIMU11_INS2_AYPI                                        0x04
#define C6DOFIMU11_INS2_AZNI                                        0x02
#define C6DOFIMU11_INS2_AZPI                                        0x01
#define C6DOFIMU11_INS3_MXNI                                        0x20
#define C6DOFIMU11_INS3_MXPI                                        0x10
#define C6DOFIMU11_INS3_MYNI                                        0x08
#define C6DOFIMU11_INS3_MYPI                                        0x04
#define C6DOFIMU11_INS3_MZNI                                        0x02
#define C6DOFIMU11_INS3_MZPI                                        0x01
#define C6DOFIMU11_INC1_BFI1                                        0x40
#define C6DOFIMU11_INC1_WMI1                                        0x20
#define C6DOFIMU11_INC1_DRDY_A1                                     0x10
#define C6DOFIMU11_INC1_DRDY_M1                                     0x08
#define C6DOFIMU11_INC1_FFI1                                        0x04
#define C6DOFIMU11_INC1_AMI1                                        0x02
#define C6DOFIMU11_INC1_MMI1                                        0x01
#define C6DOFIMU11_INC2_BFI2                                        0x40
#define C6DOFIMU11_INC2_WMI2                                        0x20
#define C6DOFIMU11_INC2_DRDY_A2                                     0x10
#define C6DOFIMU11_INC2_DRDY_M2                                     0x08
#define C6DOFIMU11_INC2_FFI2                                        0x04
#define C6DOFIMU11_INC2_AMI2                                        0x02
#define C6DOFIMU11_INC2_MMI2                                        0x01
#define C6DOFIMU11_INC3_IED2_PUSHPULL                               0x00
#define C6DOFIMU11_INC3_IED2_OPENDRAIN                              0x80
#define C6DOFIMU11_INC3_IEA2_LOW                                    0x00
#define C6DOFIMU11_INC3_IEA2_HIGH                                   0x40
#define C6DOFIMU11_INC3_IEL2_LATCHED                                0x00
#define C6DOFIMU11_INC3_IEL2_PULSED                                 0x10
#define C6DOFIMU11_INC3_IEL2_FIFO_TRIG                              0x20
#define C6DOFIMU11_INC3_IEL2_FIFO_TRIG_2                            0x30
#define C6DOFIMU11_INC3_IED1_PUSHPULL                               0x00
#define C6DOFIMU11_INC3_IED1_OPENDRAIN                              0x08
#define C6DOFIMU11_INC3_IEA1_LOW                                    0x00
#define C6DOFIMU11_INC3_IEA1_HIGH                                   0x04
#define C6DOFIMU11_INC3_IEL1_LATCHED                                0x00
#define C6DOFIMU11_INC3_IEL1_PULSED                                 0x01
#define C6DOFIMU11_INC3_IEL1_FIFO_TRIG                              0x02
#define C6DOFIMU11_INC3_IEL1_FIFO_TRIG_2                            0x03
#define C6DOFIMU11_INC4_AXNIE                                       0x20
#define C6DOFIMU11_INC4_AXPIE                                       0x10
#define C6DOFIMU11_INC4_AYNIE                                       0x08
#define C6DOFIMU11_INC4_AYPIE                                       0x04
#define C6DOFIMU11_INC4_AZNIE                                       0x02
#define C6DOFIMU11_INC4_AZPIE                                       0x01
#define C6DOFIMU11_INC5_MXNIE                                       0x20
#define C6DOFIMU11_INC5_MXPIE                                       0x10
#define C6DOFIMU11_INC5_MYNIE                                       0x08
#define C6DOFIMU11_INC5_MYPIE                                       0x04
#define C6DOFIMU11_INC5_MZNIE                                       0x02
#define C6DOFIMU11_INC5_MZPIE                                       0x01
#define C6DOFIMU11_AMI_CNTL3_AMI_EN_DISABLED                        0x00
#define C6DOFIMU11_AMI_CNTL3_AMI_EN_ENABLED                         0x80
#define C6DOFIMU11_AMI_CNTL3_AMIUL                                  0x40
#define C6DOFIMU11_AMI_CNTL3_OAMI_0P781                             0x00
#define C6DOFIMU11_AMI_CNTL3_OAMI_1P563                             0x01
#define C6DOFIMU11_AMI_CNTL3_OAMI_3P125                             0x02
#define C6DOFIMU11_AMI_CNTL3_OAMI_6P25                              0x03
#define C6DOFIMU11_AMI_CNTL3_OAMI_12P5                              0x04
#define C6DOFIMU11_AMI_CNTL3_OAMI_25                                0x05
#define C6DOFIMU11_AMI_CNTL3_OAMI_50                                0x06
#define C6DOFIMU11_AMI_CNTL3_OAMI_100                               0x07
#define C6DOFIMU11_MMI_CNTL3_MMI_EN_DISABLED                        0x00
#define C6DOFIMU11_MMI_CNTL3_MMI_EN_ENABLED                         0x80
#define C6DOFIMU11_MMI_CNTL3_MMIUL                                  0x40
#define C6DOFIMU11_MMI_CNTL3_OMMI_0P781                             0x00
#define C6DOFIMU11_MMI_CNTL3_OMMI_1P563                             0x01
#define C6DOFIMU11_MMI_CNTL3_OMMI_3P125                             0x02
#define C6DOFIMU11_MMI_CNTL3_OMMI_6P25                              0x03
#define C6DOFIMU11_MMI_CNTL3_OMMI_12P5                              0x04
#define C6DOFIMU11_MMI_CNTL3_OMMI_25                                0x05
#define C6DOFIMU11_MMI_CNTL3_OMMI_50                                0x06
#define C6DOFIMU11_MMI_CNTL3_OMMI_100                               0x07
#define C6DOFIMU11_FFI_CNTL3_FFI_EN_DISABLED                        0x00
#define C6DOFIMU11_FFI_CNTL3_FFI_EN_ENABLED                         0x80
#define C6DOFIMU11_FFI_CNTL3_FFIUL                                  0x40
#define C6DOFIMU11_FFI_CNTL3_DCRM                                   0x08
#define C6DOFIMU11_FFI_CNTL3_OFFI_12P5                              0x00
#define C6DOFIMU11_FFI_CNTL3_OFFI_25                                0x01
#define C6DOFIMU11_FFI_CNTL3_OFFI_50                                0x02
#define C6DOFIMU11_FFI_CNTL3_OFFI_100                               0x03
#define C6DOFIMU11_FFI_CNTL3_OFFI_200                               0x04
#define C6DOFIMU11_FFI_CNTL3_OFFI_400                               0x05
#define C6DOFIMU11_FFI_CNTL3_OFFI_800                               0x06
#define C6DOFIMU11_FFI_CNTL3_OFFI_1600                              0x07
#define C6DOFIMU11_ODCNTL_OSA_12P5                                  0x00
#define C6DOFIMU11_ODCNTL_OSA_25                                    0x01
#define C6DOFIMU11_ODCNTL_OSA_50                                    0x02
#define C6DOFIMU11_ODCNTL_OSA_100                                   0x03
#define C6DOFIMU11_ODCNTL_OSA_200                                   0x04
#define C6DOFIMU11_ODCNTL_OSA_400                                   0x05
#define C6DOFIMU11_ODCNTL_OSA_800                                   0x06
#define C6DOFIMU11_ODCNTL_OSA_1600                                  0x07
#define C6DOFIMU11_ODCNTL_OSA_0P781                                 0x08
#define C6DOFIMU11_ODCNTL_OSA_1P563                                 0x09
#define C6DOFIMU11_ODCNTL_OSA_3P125                                 0x0A
#define C6DOFIMU11_ODCNTL_OSA_6P25                                  0x0B
#define C6DOFIMU11_ODCNTL_OSA_25600ST0P8                            0x0C
#define C6DOFIMU11_ODCNTL_OSA_25600ST1P6                            0x0D
#define C6DOFIMU11_ODCNTL_OSA_25600ST3P2                            0x0E
#define C6DOFIMU11_ODCNTL_OSA_25600                                 0x0F
#define C6DOFIMU11_ODCNTL_OSM_12P5                                  0x00
#define C6DOFIMU11_ODCNTL_OSM_25                                    0x10
#define C6DOFIMU11_ODCNTL_OSM_50                                    0x20
#define C6DOFIMU11_ODCNTL_OSM_100                                   0x30
#define C6DOFIMU11_ODCNTL_OSM_200                                   0x40
#define C6DOFIMU11_ODCNTL_OSM_400                                   0x50
#define C6DOFIMU11_ODCNTL_OSM_800                                   0x60
#define C6DOFIMU11_ODCNTL_OSM_1600                                  0x70
#define C6DOFIMU11_ODCNTL_OSM_0P781                                 0x80
#define C6DOFIMU11_ODCNTL_OSM_1P563                                 0x90
#define C6DOFIMU11_ODCNTL_OSM_3P125                                 0xA0
#define C6DOFIMU11_ODCNTL_OSM_6P25                                  0xB0
#define C6DOFIMU11_ODCNTL_OSM_12800A                                0xC0
#define C6DOFIMU11_ODCNTL_OSM_12800B                                0xD0
#define C6DOFIMU11_ODCNTL_OSM_12800C                                0xE0
#define C6DOFIMU11_ODCNTL_OSM_12800                                 0xF0
#define C6DOFIMU11_CNTL1_SRST                                       0x80
#define C6DOFIMU11_CNTL1_STEN_DISABLED                              0x00
#define C6DOFIMU11_CNTL1_STEN_ENABLED                               0x40
#define C6DOFIMU11_CNTL1_STPOL                                      0x20
#define C6DOFIMU11_CNTL1_COTC                                       0x08
/** \} */

/**
 * \defgroup standby_mode Standby mode
 * \{
 */
#define C6DOFIMU11_CNTL2_TEMP_EN_STANDBY_MODE                       0x00
#define C6DOFIMU11_CNTL2_TEMPERATURE_DISABLE                        0x00
#define C6DOFIMU11_CNTL2_TEMPERATURE_ENABLE                         0x01
#define C6DOFIMU11_CNTL2_TEMP_EN_OPERATING_MODE                     0x40
#define C6DOFIMU11_CNTL2_GSEL_8G                                    0x00
#define C6DOFIMU11_CNTL2_GSEL_16G                                   0x10
#define C6DOFIMU11_CNTL2_GSEL_32G                                   0x20
#define C6DOFIMU11_CNTL2_GSEL_64G                                   0x30
#define C6DOFIMU11_CNTL2_RES_A4M2                                   0x00
#define C6DOFIMU11_CNTL2_RES_A32M16                                 0x04
#define C6DOFIMU11_CNTL2_RES_MAX1                                   0x08
#define C6DOFIMU11_CNTL2_RES_MAX2                                   0x0C
#define C6DOFIMU11_CNTL2_MAG_DISABLE                                0x00
#define C6DOFIMU11_CNTL2_MAG_ENABLE                                 0x01
#define C6DOFIMU11_CNTL2_MAG_EN_STANDBY_MODE                        0x00
#define C6DOFIMU11_CNTL2_MAG_EN_OPERATING_MODE                      0x02
#define C6DOFIMU11_CNTL2_ACCEL_EN_STANDBY_MODE                      0x00
#define C6DOFIMU11_CNTL2_ACCEL_EN_OPERATING_MODE                    0x01
#define C6DOFIMU11_CNTL2_ACCEL_DISABLE                              0x00
#define C6DOFIMU11_CNTL2_ACCEL_ENABLE                               0x01
#define C6DOFIMU11_COTR_TEST_RESP_DEFAULT                           0x55
#define C6DOFIMU11_COTR_TEST_RESP_TEST                              0xAA
#define C6DOFIMU11_BUF_CTRL_2_BUF_M_FIFO                            0x00
#define C6DOFIMU11_BUF_CTRL_2_BUF_M_STREAM                          0x02
#define C6DOFIMU11_BUF_CTRL_2_BUF_M_TRIGGER                         0x04
#define C6DOFIMU11_BUF_CTRL_2_BUF_M_FILO                            0x03
#define C6DOFIMU11_BUF_CTRL_2_SMT_TH8                               0x01
#define C6DOFIMU11_BUF_CTRL_3_BFI_EN_DISABLED                       0x00
#define C6DOFIMU11_BUF_CTRL_3_BFI_EN_ENABLED                        0x80
#define C6DOFIMU11_BUF_CTRL_3_BUF_AX_DISABLED                       0x00
#define C6DOFIMU11_BUF_CTRL_3_BUF_AX_ENABLED                        0x40
#define C6DOFIMU11_BUF_CTRL_3_BUF_AY_DISABLED                       0x00
#define C6DOFIMU11_BUF_CTRL_3_BUF_AY_ENABLED                        0x20
#define C6DOFIMU11_BUF_CTRL_3_BUF_AZ_DISABLED                       0x00
#define C6DOFIMU11_BUF_CTRL_3_BUF_AZ_ENABLED                        0x10
#define C6DOFIMU11_BUF_CTRL_3_BUF_MX_DISABLED                       0x00
#define C6DOFIMU11_BUF_CTRL_3_BUF_MX_ENABLED                        0x08
#define C6DOFIMU11_BUF_CTRL_3_BUF_MY_DISABLED                       0x00
#define C6DOFIMU11_BUF_CTRL_3_BUF_MY_ENABLED                        0x04
#define C6DOFIMU11_BUF_CTRL_3_BUF_MZ_DISABLED                       0x00
#define C6DOFIMU11_BUF_CTRL_3_BUF_MZ_ENABLED                        0x02
#define C6DOFIMU11_BUF_CTRL_3_BUF_TEMP_DISABLED                     0x00
#define C6DOFIMU11_BUF_CTRL_3_BUF_TEMP_ENABLED                      0x01
#define C6DOFIMU11_BUF_STATUS_2_BUF_TRIG                            0x02
#define C6DOFIMU11_BUF_STATUS_2_SMP_LEV_H                           0x01
#define C6DOFIMU11_WHO_AM_I_WIA_MASK                                0xFF
#define C6DOFIMU11_INS1_INT_MASK                                    0x80
#define C6DOFIMU11_INS1_BFI_MASK                                    0x40
#define C6DOFIMU11_INS1_WMI_MASK                                    0x20
#define C6DOFIMU11_INS1_DRDY_A_MASK                                 0x10
#define C6DOFIMU11_INS1_DRDY_M_MASK                                 0x08
#define C6DOFIMU11_INS1_FFI_MASK                                    0x04
#define C6DOFIMU11_INS1_AMI_MASK                                    0x02

#define C6DOFIMU11_INS1_MMI_MASK                                    0x01
#define C6DOFIMU11_INC3_IED2_MASK                                   0x80
#define C6DOFIMU11_INC3_IEA2_MASK                                   0x40
#define C6DOFIMU11_INC3_IEL2_MASK                                   0x30
#define C6DOFIMU11_INC3_IED1_MASK                                   0x08
#define C6DOFIMU11_INC3_IEA1_MASK                                   0x04
#define C6DOFIMU11_INC3_IEL1_MASK                                   0x03

#define C6DOFIMU11_AMI_CNTL3_AMI_EN_MASK                            0x80
#define C6DOFIMU11_AMI_CNTL3_OAMI_MASK                              0x07

#define C6DOFIMU11_MMI_CNTL3_MMI_EN_MASK                            0x80
#define C6DOFIMU11_MMI_CNTL3_OMMI_MASK                              0x07

#define C6DOFIMU11_FFI_CNTL3_FFI_EN_MASK                            0x80
#define C6DOFIMU11_FFI_CNTL3_OFFI_MASK                              0x07

#define C6DOFIMU11_ODCNTL_OSA_MASK                                  0x0F

#define C6DOFIMU11_ODCNTL_OSM_MASK                                  0xF0
#define C6DOFIMU11_CNTL1_STEN_MASK                                  0x40
#define C6DOFIMU11_CNTL2_TEMP_EN_MASK                               0x40

#define C6DOFIMU11_CNTL2_GSEL_MASK                                  0x30
#define C6DOFIMU11_CNTL2_RES_MASK                                   0x0C
#define C6DOFIMU11_CNTL2_MAG_EN_MASK                                0x02
#define C6DOFIMU11_CNTL2_ACCEL_EN_MASK                              0x01
#define C6DOFIMU11_COTR_TEST_RESP_MASK                              0xFF
#define C6DOFIMU11_BUF_CTRL_1_SMT_TH_MASK                           0xFF
#define C6DOFIMU11_BUF_CTRL_2_BUF_M_MASK                            0x06
/** \} */

/**
 * \defgroup controls_the_buffer_full_interrupt Controls the buffer full interrupt
 * \{
 */
#define C6DOFIMU11_BUF_CTRL_3_BFI_EN_MASK                           0x80
#define C6DOFIMU11_BUF_CTRL_3_BUF_AX_MASK                           0x40
#define C6DOFIMU11_BUF_CTRL_3_BUF_AY_MASK                           0x20
#define C6DOFIMU11_BUF_CTRL_3_BUF_AZ_MASK                           0x10
#define C6DOFIMU11_BUF_CTRL_3_BUF_MX_MASK                           0x08
#define C6DOFIMU11_BUF_CTRL_3_BUF_MY_MASK                           0x04
#define C6DOFIMU11_BUF_CTRL_3_BUF_MZ_MASK                           0x02
#define C6DOFIMU11_BUF_CTRL_3_BUF_TEMP_MASK                         0x01
#define C6DOFIMU11_BUF_STATUS_1_SMP_LEV_MASK                        0xFF
#define C6DOFIMU11_BUF_STATUS_2_SMP_PAST_MASK                       0xFF
#define C6DOFIMU11_BUF_STATUS_3_SMP_PAST_H_MASK                     0xFF

#define C6DOFIMU11_CHECK_ID_ERROR                                   0x00
#define C6DOFIMU11_CHECK_ID_SUCCESS                                 0x01

#define C6DOFIMU11_ACCEL_COEF_RES_8G                       0.00183111052
#define C6DOFIMU11_ACCEL_COEF_RES_16G                      0.00732444210
#define C6DOFIMU11_ACCEL_COEF_RES_32G                      0.02929776840
#define C6DOFIMU11_ACCEL_COEF_RES_64G                      0.11255815032
#define C6DOFIMU11_MAG_COEF                                0.03662221137
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */



/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t gp1;

    // Input pins 

    digital_in_t gp2;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} c6dofimu11_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t gp1;
    pin_name_t gp2;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} c6dofimu11_cfg_t;

/**
 * @brief Accel axis structure definition.
 */
typedef struct
{
    float x;
    float y;
    float z;
}
c6dofimu11_accel_t;

/**
 * @brief Mag axis structure definition.
 */
typedef struct
{
    float x;
    float y;
    float z;
}
c6dofimu11_mag_t;

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
void c6dofimu11_cfg_setup ( c6dofimu11_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
C6DOFIMU11_RETVAL c6dofimu11_init ( c6dofimu11_t *ctx, c6dofimu11_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for 6DofImu11 click.
 */
void c6dofimu11_default_cfg ( c6dofimu11_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function writes data to the desired register.
 */
void c6dofimu11_generic_write ( c6dofimu11_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void c6dofimu11_generic_read ( c6dofimu11_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief This function write byte.
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param write_data   Write data 
 *
 * @description This function write data from the desired register.
 */
void c6dofimu11_write_byte ( c6dofimu11_t *ctx, uint8_t reg_address, uint8_t write_data );

 /**
 * @brief This function read byte.
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 *
 * @description This function reads data from the desired register.
 */
uint8_t c6dofimu11_read_byte ( c6dofimu11_t *ctx, uint8_t reg_address );

 /**
 * @brief This function write multiple bytes.
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param p_write_data Write data.
 * @param n_bytes      Number of the bytes to be read.
 *
 * @description This function write multiple bytes from the desired register.
 */
void c6dofimu11_write_multiple_bytes ( c6dofimu11_t *ctx, uint8_t reg_address, uint8_t *p_write_data, uint8_t n_bytes );

/**
 * @brief This function read multiple bytes
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param p_read_data  Read data.
 * @param n_bytes      Number of the bytes to be read
 *
 * @description This function reads multiple data from the desired register.
 */
void c6dofimu11_read_multiple_bytes ( c6dofimu11_t *ctx, uint8_t reg_address, uint8_t *p_read_data, uint8_t n_bytes );

 /**
 * @brief This function check id.
 * 
 * @param ctx          Click object.
 *
 * @description This function chek id.
 */
uint8_t c6dofimu11_check_id ( c6dofimu11_t *ctx );

 /**
 * @brief Disable sensor.
 * 
 * @param ctx          Click object.
 *
 * @description This function disable sensor.
 */
void c6dofimu11_disable_sensor ( c6dofimu11_t *ctx );

 /**
 * @brief Enable sensor. 
 * 
 * @param ctx          Click object.
 * @param en_accel     En accel.
 * @param en_mag       En mag.
 * @param en_temp      En temp.
 *
 * @description This function enable sensor.
 */
void c6dofimu11_enable_sensor ( c6dofimu11_t *ctx, uint8_t en_accel, uint8_t en_mag, uint8_t en_temp );

 /**
 * @brief Configuration accel.
 * 
 * @param ctx          Click object.
 * @param data_rate    Data rate.
 * @param data_range   Data range.
 * @param data_resolution  Data resolution
 *
 * @description This function configuration accel.
 */
void c6dofimu11_config_accel ( c6dofimu11_t *ctx, uint8_t data_rate, uint8_t data_range, uint8_t data_resolution );


/**
 * @brief Configuration map.
 * 
 * @param ctx          Click object.
 * @param data_range   Data range.
 * @param data_resolution  Data resolution
 *
 * @description This function configuration map.
 */
void c6dofimu11_config_mag ( c6dofimu11_t *ctx, uint8_t data_rate, uint8_t data_resolution );

 /**
 * @brief Get axis.
 * 
 * @param ctx          Click object.
 * @param reg_add_lsb  Registar add lsb.    
 *
 * @description This function get axis.
 */
int16_t c6dofimu11_get_axis ( c6dofimu11_t *ctx, uint8_t reg_add_lsb );

 /**
 * @brief Get accel data.
 * 
 * @param ctx          Click object.
 * @param accel_x      Accel x.
 * @param accel_y      Accel y.
 * @param accel_z      Accel z.
 *
 * @description This function get  accel data.
 */
void c6dofimu11_get_accel_data ( c6dofimu11_t *ctx, int16_t *accel_x, int16_t *accel_y, int16_t *accel_z );

 /**
 * @brief Get map data.
 * 
 * @param ctx          Click object.
 * @param mag_x        Mag x.
 * @param mag_y        Mag y.
 * @param mag_z        Mag z.
 *
 * @description This function get map data.
 */
void c6dofimu11_get_mag_data ( c6dofimu11_t *ctx, int16_t *mag_x, int16_t *mag_y, int16_t *mag_z );

 /**
 * @brief Read accel.
 * 
 * @param ctx          Click object.
 * @param accel_data   Accel data.
 *
 * @description This function read accel.
 */
void c6dofimu11_read_accel (  c6dofimu11_t *ctx, c6dofimu11_accel_t *accel_data );


 /**
 * @brief Read mag.
 * 
 * @param ctx          Click object.
 * @param mag_data     Mag data.
 *
 * @description This function read.
 */
void c6dofimu11_read_mag ( c6dofimu11_t *ctx, c6dofimu11_mag_t *mag_data );

/**
 * @brief Enable temperature data.
 * 
 * @param ctx          Click object.
 *
 * @description This function enable temperature data.
 */
void c6dofimu11_enable_temperature_data ( c6dofimu11_t *ctx );

 /**
 * @brief Get temperature.
 * 
 * @param ctx          Click object.
 *
 * @description This function get temperature.
 */
float c6dofimu11_get_temperature ( c6dofimu11_t *ctx );

 /**
 * @brief Get interrupt.
 * 
 * @param ctx          Click object.
 *
 * @description This function get interrupt.
 */
uint8_t c6dofimu11_get_interrupt ( c6dofimu11_t *ctx );


#ifdef __cplusplus
}
#endif
#endif  // _C6DOFIMU11_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
