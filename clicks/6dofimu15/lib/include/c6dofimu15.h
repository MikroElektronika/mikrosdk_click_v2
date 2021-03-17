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
 * \brief This file contains API for 6DOF-IMU-15 Click driver.
 *
 * \addtogroup c6dofimu15 6DOF-IMU-15 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef C6DOFIMU15_H
#define C6DOFIMU15_H

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

#define C6DOFIMU15_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.scl   = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
   cfg.sda   = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup communication Select communication
 * \{
 */
#define C6DOFIMU15_MASTER_I2C 0
#define C6DOFIMU15_MASTER_SPI 1
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define C6DOFIMU15_RETVAL  uint8_t

#define C6DOFIMU15_OK           0x00
#define C6DOFIMU15_INIT_ERROR   0xFF
/** \} */
 
/**
 * \defgroup i2c_address
 * \{
 */
#define C6DOFIMU15_I2C_ADR_GND          0x6A
#define C6DOFIMU15_I2C_ADR_VCC          0x6B
/** \} */
 
/**
 * \defgroup reg_map  Reg map
 * \{
 */
#define C6DOFIMU15_PIN_CTL              0x02
#define C6DOFIMU15_FIFO_CTL1            0x07
#define C6DOFIMU15_FIFO_CTL2            0x08
#define C6DOFIMU15_FIFO_CTL3            0x09
#define C6DOFIMU15_FIFO_CTL4            0x0A
#define C6DOFIMU15_CNT_BDR_REG1         0x0B
#define C6DOFIMU15_CNT_BDR_REG2         0x0C
#define C6DOFIMU15_INT1_CTL             0x0D
#define C6DOFIMU15_INT2_CTL             0x0E
#define C6DOFIMU15_WHO_AM_I             0x0F
#define C6DOFIMU15_CTL1_XL              0x10
#define C6DOFIMU15_CTL2_G               0x11
#define C6DOFIMU15_CTL3_C               0x12
#define C6DOFIMU15_CTL4_C               0x13
#define C6DOFIMU15_CTL5_C               0x14
#define C6DOFIMU15_CTL6_C               0x15
#define C6DOFIMU15_CTL7_G               0x16
#define C6DOFIMU15_CTL8_XL              0x17
#define C6DOFIMU15_CTL9_XL              0x18
#define C6DOFIMU15_CTL10_C              0x19
#define C6DOFIMU15_ALL_INT_SRC          0x1A
#define C6DOFIMU15_WAKE_UP_SRC          0x1B
#define C6DOFIMU15_D6D_SRC              0x1D
#define C6DOFIMU15_STAT_REG             0x1E
#define C6DOFIMU15_OUT_TEMP_L           0x20
#define C6DOFIMU15_OUT_TEMP_H           0x21
#define C6DOFIMU15_OUTX_L_G             0x22
#define C6DOFIMU15_OUTX_H_G             0x23
#define C6DOFIMU15_OUTY_L_G             0x24
#define C6DOFIMU15_OUTY_H_G             0x25
#define C6DOFIMU15_OUTZ_L_G             0x26
#define C6DOFIMU15_OUTZ_H_G             0x27
#define C6DOFIMU15_OUTX_L_A             0x28
#define C6DOFIMU15_OUTX_H_A             0x29
#define C6DOFIMU15_OUTY_L_A             0x2A
#define C6DOFIMU15_OUTY_H_A             0x2B
#define C6DOFIMU15_OUTZ_L_A             0x2C
#define C6DOFIMU15_OUTZ_H_A             0x2D
#define C6DOFIMU15_FIFO_STAT1           0x3A
#define C6DOFIMU15_FIFO_STAT2           0x3B
#define C6DOFIMU15_T_STMP_0_REG         0x40
#define C6DOFIMU15_T_STMP_1_REG         0x41
#define C6DOFIMU15_T_STMP_2_REG         0x42
#define C6DOFIMU15_T_STMP_3_REG         0x43
#define C6DOFIMU15_INT_CFG0             0x56
#define C6DOFIMU15_INT_CFG1             0x58
#define C6DOFIMU15_THS_6D               0x59
#define C6DOFIMU15_WAKE_UP_THS          0x5B
#define C6DOFIMU15_WAKE_UP_DUR          0x5C
#define C6DOFIMU15_FREE_FALL            0x5D
#define C6DOFIMU15_MD1_CFG              0x5E
#define C6DOFIMU15_MD2_CFG              0x5F
#define C6DOFIMU15_INT_FRQ_FINE         0x63
#define C6DOFIMU15_X_OFS_USR            0x73
#define C6DOFIMU15_Y_OFS_USR            0x74
#define C6DOFIMU15_Z_OFS_USR            0x75
#define C6DOFIMU15_FIFO_DATA_OUT_TAG    0x78
#define C6DOFIMU15_FIFO_DATA_OUT_X_L    0x79
#define C6DOFIMU15_FIFO_DATA_OUT_X_H    0x7A
#define C6DOFIMU15_FIFO_DATA_OUT_Y_L    0x7B
#define C6DOFIMU15_FIFO_DATA_OUT_Y_H    0x7C
#define C6DOFIMU15_FIFO_DATA_OUT_Z_L    0x7D
#define C6DOFIMU15_FIFO_DATA_OUT_Z_H    0x7E
/** \} */
 
/**
 * \defgroup sdo  Sdo
 * \{
 */
#define C6DOFIMU15_SDO_PU_EN            0x7F
#define C6DOFIMU15_SDO_PU_DIS           0x3F
/** \} */
 
/**
 * \defgroup control_reg_3  control reg 3
 * \{
 */
#define C6DOFIMU15_BDR_GY_FIFO_NB       0x00
#define C6DOFIMU15_BDR_GY_12_5_HZ       0x10
#define C6DOFIMU15_BDR_GY_26_HZ         0x20
#define C6DOFIMU15_BDR_GY_52_HZ         0x30
#define C6DOFIMU15_BDR_GY_104_HZ        0x40
#define C6DOFIMU15_BDR_GY_208_HZ        0x50
#define C6DOFIMU15_BDR_GY_417_HZ        0x60
#define C6DOFIMU15_BDR_GY_833_HZ        0x70
#define C6DOFIMU15_BDR_GY_1667_HZ       0x80
#define C6DOFIMU15_BDR_GY_3333_HZ       0x90
#define C6DOFIMU15_BDR_GY_6667_HZ       0xA0
#define C6DOFIMU15_BDR_GY_6_5_HZ        0xB0
#define C6DOFIMU15_BDR_XL_FIFO_NB       0x00
#define C6DOFIMU15_BDR_XL_12_5_HZ       0x01
#define C6DOFIMU15_BDR_XL_26_HZ         0x02
#define C6DOFIMU15_BDR_XL_52_HZ         0x03
#define C6DOFIMU15_BDR_XL_104_HZ        0x04
#define C6DOFIMU15_BDR_XL_208_HZ        0x05
#define C6DOFIMU15_BDR_XL_417_HZ        0x06
#define C6DOFIMU15_BDR_XL_833_HZ        0x07
#define C6DOFIMU15_BDR_XL_1667_HZ       0x80
#define C6DOFIMU15_BDR_XL_3333_HZ       0x09
#define C6DOFIMU15_BDR_XL_6667_HZ       0x0A
/** \} */
 
/**
 * \defgroup control_reg_4  control reg 4
 * \{
 */
#define C6DOFIMU15_DEC_TS_BATCH_1       0x40
#define C6DOFIMU15_DEC_TS_BATCH_8       0x80
#define C6DOFIMU15_DEC_TS_BATCH_32      0xC0
#define C6DOFIMU15_ODR_T_BATCH_1_6_HZ   0x10
#define C6DOFIMU15_ODR_T_BATCH_12_5_HZ  0x20
#define C6DOFIMU15_ODR_T_BATCH_52_HZ    0x30
#define C6DOFIMU15_FIFO_DIS             0x00
#define C6DOFIMU15_FIFO_ST_WHEN_FULL    0x01
#define C6DOFIMU15_CONT_TO_FIFO         0x03
#define C6DOFIMU15_BYP_TO_CONT          0x04
#define C6DOFIMU15_CONT_MODE            0x06
#define C6DOFIMU15_BYP_TO_FIFO          0x07
/** \} */
 
/**
 * \defgroup int1_pin_control  Int1 pin control
 * \{
 */
#define C6DOFIMU15_DEN_DRDY_FLAG        0x80
#define C6DOFIMU15_INT1_CNT_BDR         0x40
#define C6DOFIMU15_INT1_FIFO_FULL       0x20
#define C6DOFIMU15_INT1_FIFO_OVR        0x10
#define C6DOFIMU15_INT1_FIFO_TH         0x08
#define C6DOFIMU15_INT1_BOOT            0x04
#define C6DOFIMU15_INT1_DRDY_G          0x02
#define C6DOFIMU15_INT1_DRDY_XL         0x01
/** \} */
 
/**
 * \defgroup int2_pin_control  Int2 pin control
 * \{
 */
#define C6DOFIMU15_INT2_CNT_BDR         0x40
#define C6DOFIMU15_INT2_FIFO_FULL       0x20
#define C6DOFIMU15_INT2_FIFO_OVR        0x10
#define C6DOFIMU15_INT2_FIFO_TH         0x08
#define C6DOFIMU15_INT2_DRDY_TEMP       0x04
#define C6DOFIMU15_INT2_DRDY_G          0x02
#define C6DOFIMU15_INT2_DRDY_XL         0x01
/** \} */
 
/**
 * \defgroup who_i_am  Who I am
 * \{
 */
#define C6DOFIMU15_WHO_AM_I_VAL         0x6B
/** \} */
 
/**
 * \defgroup accel_reg  Accel reg
 * \{
 */
#define C6DOFIMU15_ODR_XL_POW_DWN       0x00
#define C6DOFIMU15_ODR_XL_12_5_HZ       0x10
#define C6DOFIMU15_ODR_XL_26_HZ         0x20
#define C6DOFIMU15_ODR_XL_52_HZ         0x30
#define C6DOFIMU15_ODR_XL_104_HZ        0x40
#define C6DOFIMU15_ODR_XL_208_HZ        0x50
#define C6DOFIMU15_ODR_XL_417_HZ        0x60
#define C6DOFIMU15_ODR_XL_833_HZ        0x70
#define C6DOFIMU15_ODR_XL_1667_HZ       0x80
#define C6DOFIMU15_ODR_XL_3333_HZ       0x90
#define C6DOFIMU15_ODR_XL_6667_HZ       0xA0
#define C6DOFIMU15_FS_XL_2_G            0x00
#define C6DOFIMU15_FS_XL_16_G           0x04
#define C6DOFIMU15_FS_XL_4_G            0x08
#define C6DOFIMU15_FS_XL_8_G            0x0C
#define C6DOFIMU15_LPF2_XL_EN           0x02
/** \} */
 
/**
 * \defgroup gyro_reg  Gyro reg
 * \{
 */
#define C6DOFIMU15_ODR_G_POW_DWN        0x00
#define C6DOFIMU15_ODR_G_12_5_HZ        0x10
#define C6DOFIMU15_ODR_G_26_HZ          0x20
#define C6DOFIMU15_ODR_G_52_HZ          0x30
#define C6DOFIMU15_ODR_G_104_HZ         0x40
#define C6DOFIMU15_ODR_G_208_HZ         0x50
#define C6DOFIMU15_ODR_G_417_HZ         0x60
#define C6DOFIMU15_ODR_G_833_HZ         0x70
#define C6DOFIMU15_ODR_G_1667_HZ        0x80
#define C6DOFIMU15_ODR_G_3333_HZ        0x90
#define C6DOFIMU15_ODR_G_6667_HZ        0xA0
#define C6DOFIMU15_FS_G_250_DPS         0x00
#define C6DOFIMU15_FS_G_500_DPS         0x04
#define C6DOFIMU15_FS_G_1000_DPS        0x08
#define C6DOFIMU15_FS_G_2000_DPS        0x0C
#define C6DOFIMU15_FS_125               0x02
#define C6DOFIMU15_FS_4000              0x01
/** \} */
 
/**
 * \defgroup contro_reg_3  Control reg 3
 * \{
 */
#define C6DOFIMU15_BOOT                 0x80
#define C6DOFIMU15_BDU                  0x40
#define C6DOFIMU15_H_LACTIVE            0x20
#define C6DOFIMU15_PP_OD                0x10
#define C6DOFIMU15_SIM                  0x08
#define C6DOFIMU15_IF_INC               0x04
#define C6DOFIMU15_SW_RESET             0x01
/** \} */
 
/**
 * \defgroup contro_reg_4  Control reg 4
 * \{
 */
#define C6DOFIMU15_SLEEP_G              0x40
#define C6DOFIMU15_INT2_ON_INT1         0x20
#define C6DOFIMU15_DRDY_MASK            0x08
#define C6DOFIMU15_I2C_DIS              0x04
#define C6DOFIMU15_LPF1_SEL_G           0x02
/** \} */
 
/**
 * \defgroup contro_reg_5  Control reg 5
 * \{
 */
#define C6DOFIMU15_ROUNDING_NO          0x00
#define C6DOFIMU15_ROUNDING_XL          0x20
#define C6DOFIMU15_ROUNDING_G           0x40
#define C6DOFIMU15_ROUNDING_G_XL        0x60
#define C6DOFIMU15_ST_G_NOR_OP          0x00
#define C6DOFIMU15_ST_G_POS_SNG         0x04
#define C6DOFIMU15_ST_G_NEG_SNG         0x0C
#define C6DOFIMU15_ST_XL_NOR_OP         0x00
#define C6DOFIMU15_ST_XL_POS_SNG        0x01
#define C6DOFIMU15_ST_XL_NEG_SNG        0x02
/** \} */
 
/**
 * \defgroup contro_reg_6  Control reg 6
 * \{
 */
#define C6DOFIMU15_EDG_SENS_TRIG        0x80
#define C6DOFIMU15_LVL_SENS_TRIG        0x40
#define C6DOFIMU15_LVL_SENS_LTCH        0x60
#define C6DOFIMU15_LVL_SENS_FIFO_EN     0xC0
/** \} */
 
/**
 * \defgroup contro_reg_7  Control reg 7
 * \{
 */
#define C6DOFIMU15_HP_EN_G              0x40
#define C6DOFIMU15_HPM_G_16_MHZ         0x00
#define C6DOFIMU15_HPM_G_65_MHZ         0x10
#define C6DOFIMU15_HPM_G_260_MHZ        0x20
#define C6DOFIMU15_HPM_G_1_04_HZ        0x30
#define C6DOFIMU15_USR_OFF_ON_OUT       0x02
/** \} */
 
/**
 * \defgroup contro_reg_9  Control reg 9
 * \{
 */
#define C6DOFIMU15_DEN_X                0x80
#define C6DOFIMU15_DEN_Y                0x40
#define C6DOFIMU15_DEN_Z                0x20
#define C6DOFIMU15_DEN_XL_G             0x10
#define C6DOFIMU15_DEN_XL_EN            0x08
#define C6DOFIMU15_DEN_LH               0x04
#define C6DOFIMU15_DEV_CFG              0x02
/** \} */
 
/**
 * \defgroup contro_reg_10  Control reg 10
 * \{
 */
#define C6DOFIMU15_T_STAMP_EN           0x20
/** \} */
 
/**
 * \defgroup source_reg  Source reg
 * \{
 */
#define C6DOFIMU15_T_STAMP_END_CNT      0x80
#define C6DOFIMU15_SLEP_CHN_IA          0x20
#define C6DOFIMU15_SRC_D6D_IA           0x10
#define C6DOFIMU15_SRC_WU_IA            0x02
#define C6DOFIMU15_SRC_FF_IA            0x01
/** \} */
 
/**
 * \defgroup wake_up_int  Wake up int
 * \{
 */
#define C6DOFIMU15_SLP_CHN_IA           0x40
#define C6DOFIMU15_INT_FF_IA            0x20
#define C6DOFIMU15_SLP_STAT             0x10
#define C6DOFIMU15_INT_WU_IA            0x08
#define C6DOFIMU15_X_WU                 0x04
#define C6DOFIMU15_Y_WU                 0x02
#define C6DOFIMU15_Z_WU                 0x01
/** \} */
 
/**
 * \defgroup urce_reg  Urce reg
 * \{
 */
#define C6DOFIMU15_DEN_DRDY             0x80
#define C6DOFIMU15_D6D_IA               0x40
#define C6DOFIMU15_Z_AXIS_HIGH          0x20
#define C6DOFIMU15_Z_AXIS_LOW           0x10
#define C6DOFIMU15_Y_AXIS_HIGH          0x08
#define C6DOFIMU15_Y_AXIS_LOW           0x04
#define C6DOFIMU15_X_AXIS_HIGH          0x02
#define C6DOFIMU15_X_AXIS_LOW           0x01
/** \} */
 
/**
 * \defgroup statu_reg  Status reg
 * \{
 */
#define C6DOFIMU15_TDA                  0x04
#define C6DOFIMU15_GDA                  0x02
#define C6DOFIMU15_XLDA                 0x01
/** \} */
 
/**
 * \defgroup latch_mode  Latch mode
 * \{
 */
#define C6DOFIMU15_INT_CLR_ON_READ      0x40
#define C6DOFIMU15_SLP_STAT_ON_INT      0x20
#define C6DOFIMU15_SLOPE_FDS            0x10
#define C6DOFIMU15_LIR                  0x01
/** \} */
 
/**
 * \defgroup enable_int  Enable int
 * \{
 */
#define C6DOFIMU15_INT_EN                  0x80
#define C6DOFIMU15_STAIONARY_MODE          0x00
#define C6DOFIMU15_INA_ACL_12_5_GYR_N_CRG  0x20
#define C6DOFIMU15_INA_ACL_12_5_GYR_SLP    0x40
#define C6DOFIMU15_INA_ACL_12_5_GYR_P_DWN  0x60
/** \} */
 
/**
 * \defgroup pos_reg  Pos reg
 * \{
 */
#define C6DOFIMU15_D4D_EN                  0x80
#define C6DOFIMU15_SIXD_THS_80_DEG         0x00
#define C6DOFIMU15_SIXD_THS_70_DEG         0x20
#define C6DOFIMU15_SIXD_THS_60_DEG         0x40
#define C6DOFIMU15_SIXD_THS_50_DEG         0x60
/** \} */
 
/**
 * \defgroup wake_up_reg  Wake up reg
 * \{
 */
#define C6DOFIMU15_USR_OFF_ON_WU           0x40
/** \} */
 
/**
 * \defgroup mode_function  Mode function
 * \{
 */
#define C6DOFIMU15_FF_DUR5                 0x80
#define C6DOFIMU15_WAKE_THS_W              0x10
/** \} */
 
/**
 * \defgroup set_reg  Set reg
 * \{
 */
#define C6DOFIMU15_FF_THS_500_MG           0x07
#define C6DOFIMU15_FF_THS_469_MG           0x06
#define C6DOFIMU15_FF_THS_406_MG           0x05
#define C6DOFIMU15_FF_THS_344_MG           0x04
#define C6DOFIMU15_FF_THS_312_MG           0x03
#define C6DOFIMU15_FF_THS_250_MG           0x02
#define C6DOFIMU15_FF_THS_219_MG           0x01
#define C6DOFIMU15_FF_THS_156_MG           0x00

#define C6DOFIMU15_INT1_SLP_CHN            0x80
#define C6DOFIMU15_INT1_WU                 0x20
#define C6DOFIMU15_INT1_FF                 0x10
#define C6DOFIMU15_INT1_6D                 0x04

#define C6DOFIMU15_INT2_SLP_CHN            0x80
#define C6DOFIMU15_INT2_WU                 0x20
#define C6DOFIMU15_INT2_FF                 0x10
#define C6DOFIMU15_INT2_6D                 0x04
#define C6DOFIMU15_INT2_T_STAMP            0x01
/** \} */
 
/**
 * \defgroup tag_reg  Tag reg
 * \{
 */
#define C6DOFIMU15_TAG_SEN_GYRO            0x08
#define C6DOFIMU15_TAG_SEN_ACEL            0x10
#define C6DOFIMU15_TAG_SEN_TEMP            0x18
#define C6DOFIMU15_TAG_SEN_T_ST            0x20
#define C6DOFIMU15_TAG_SEN_CFG_CHN         0x28
/** \} */
 
/**
 * \defgroup linear_accel_sensitivity  Linear accel sensitivity
 * \{
 */
#define C6DOFIMU15_LA_FS_2_G                 0.061
#define C6DOFIMU15_LA_FS_4_G                 0.122
#define C6DOFIMU15_LA_FS_8_G                 0.244
#define C6DOFIMU15_LA_FS_16_G                0.488
/** \} */
 
/**
 * \defgroup angular_rate_sensitivity  Angular rate sensitivity
 * \{
 */
#define C6DOFIMU15_G_FS_125_DPS              4.375
#define C6DOFIMU15_G_FS_250_DPS              8.75
#define C6DOFIMU15_G_FS_500_DPS              17.5
#define C6DOFIMU15_G_FS_1000_DPS             35.0
#define C6DOFIMU15_G_FS_2000_DPS             70.0
#define C6DOFIMU15_G_FS_4000_DPS             140.0
/** \} */
 
/**
 * \defgroup duration_reg  Duration reg
 * \{
 */
#define C6DOFIMU15_ODR_COEF_FOR_ODR_12_5  512
#define C6DOFIMU15_ODR_COEF_FOR_ODR_26    256
#define C6DOFIMU15_ODR_COEF_FOR_ODR_52     12
#define C6DOFIMU15_ODR_COEF_FOR_ODR_104    64
#define C6DOFIMU15_ODR_COEF_FOR_ODR_208    32
#define C6DOFIMU15_ODR_COEF_FOR_ODR_416    16
#define C6DOFIMU15_ODR_COEF_FOR_ODR_833     8
#define C6DOFIMU15_ODR_COEF_FOR_ODR_1667    4
#define C6DOFIMU15_ODR_COEF_FOR_ODR_3333    2
#define C6DOFIMU15_ODR_COEF_FOR_ODR_6667    1
/** \} */
 
/**
 * \defgroup property  Property
 * \{
 */
#define C6DOFIMU15_PROP_DIS                0
#define C6DOFIMU15_PROP_EN                 1
/** \} */
 
/**
 * \defgroup spi_mask  Spi mask
 * \{
 */
#define C6DOFIMU15_RD_BIT_MASK       0x80
#define C6DOFIMU15_WR_BIT_MASK       0x7F
/** \} */
 
/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Communication type.
 */
typedef uint8_t  c6dofimu15_select_t;

/**
 * @brief Master Input/Output type.
 */
typedef void ( *c6dofimu15_master_io_t )( struct c6dofimu15_s*, uint8_t, uint8_t*, uint8_t );

/**
 * @brief Click ctx object definition.
 */
typedef struct c6dofimu15_s
{
   // Output pins 
   digital_out_t cs;

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;
    spi_master_t spi;

    // ctx variable 

    uint8_t slave_address;
    pin_name_t chip_select;
    c6dofimu15_master_io_t  write_f;
    c6dofimu15_master_io_t  read_f;
    c6dofimu15_select_t master_sel;

} c6dofimu15_t;

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

    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t  i2c_address;

    uint32_t spi_speed;
    spi_master_mode_t  spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

    c6dofimu15_select_t sel;

} c6dofimu15_cfg_t;

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
void c6dofimu15_cfg_setup ( c6dofimu15_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param c6dofimu15 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
C6DOFIMU15_RETVAL c6dofimu15_init ( c6dofimu15_t *ctx, c6dofimu15_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for 6DOF-IMU-15 click.
 */
void c6dofimu15_default_cfg ( c6dofimu15_t *ctx );

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
void c6dofimu15_generic_write ( c6dofimu15_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx      Click object.
 * @param reg          Register address.
 * @param data_buf  Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function reads data from the desired register.
 */
void c6dofimu15_generic_read ( c6dofimu15_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Check Interrupt state function
 *
 * @param ctx        Click object.
 * 
 * @return
 * - 0 : Interrupt has not occured
 * - 1 : Interrupt has occured
 *
 * @description Function is used to check if an interrupt has occured.
**/
uint8_t c6dofimu15_check_int_pin ( c6dofimu15_t *ctx );

/**
 * @brief Read Gyroscope X-axis data function
 *
 * @param ctx        Click object.
 * 
 * @returns result 16-bit gyroscope X-axis data
 *
 * @description Function is used to read gyroscope X-axis data.
**/
int16_t c6dofimu15_read_gyro_x ( c6dofimu15_t *ctx );

/**
 * @brief Read Gyroscope Y-axis data function
 *
 * @param ctx        Click object.
 * 
 * @returns result 16-bit gyroscope Y-axis data
 *
 * @description Function is used to read gyroscope Y-axis data.
**/
int16_t c6dofimu15_read_gyro_y ( c6dofimu15_t *ctx );

/**
 * @brief Read Gyroscope Z-axis data function
 *
 * @param ctx        Click object.
 * 
 * @returns result 16-bit gyroscope Z-axis data
 *
 * @description Function is used to read gyroscope Z-axis data.
**/
int16_t c6dofimu15_read_gyro_z ( c6dofimu15_t *ctx );

/**
 * @brief Read gyroscope data function
 *
 * @param ctx        Click object.
 * @param gyro_x  16-bit gyroscope X-axis data
 * @param gyro_y  16-bit gyroscope Y-axis data
 * @param gyro_z  16-bit gyroscope Z-axis data
 *
 * @description Function is used to read gyroscope data.
**/
void c6dofimu15_read_gyroscope ( c6dofimu15_t *ctx, int16_t *gyro_x
                               , int16_t *gyro_y
                               , int16_t *gyro_z );

/**
 * @brief Read Angular Rate function
 *
 * @param ctx        Click object.
 * @param x_ang_rte  float X-axis angular rate
 * @param y_ang_rte  float Y-axis angular rate
 * @param z_ang_rte  float Z-axis angular rate
 *
 * @description Function is used to calculate angular rate
 * in milidegrees per second.
**/
void c6dofimu15_angular_rate ( c6dofimu15_t *ctx, float *x_ang_rte
                             , float *y_ang_rte
                             , float *z_ang_rte );

/**
 * @brief Read Accelerometer X-axis data function
 *
 * @param ctx        Click object.
 * 
 * @returns result 16-bit accelerometer X-axis data
 *
 * @description Function is used to read accelerometer X-axis data.
**/
int16_t c6dofimu15_read_accel_x ( c6dofimu15_t *ctx );

/**
 * @brief Read Accelerometer Y-axis data function
 *
 * @param ctx        Click object.
 * 
 * @returns result 16-bit accelerometer Y-axis data
 *
 * @description Function is used to read accelerometer Y-axis data.
**/
int16_t c6dofimu15_read_accel_y ( c6dofimu15_t *ctx );

/**
 * @brief Read Accelerometer Z-axis data function
 *
 * @param ctx        Click object.
 * 
 * @returns result 16-bit accelerometer Z-axis data
 *
 * @description Function is used to read accelerometer Z-axis data.
**/
int16_t c6dofimu15_read_accel_z ( c6dofimu15_t *ctx );

/**
 * @brief Read accelerometer data function
 *
 * @param ctx        Click object.
 * @param accel_x  16-bit accelerometer X-axis data
 * @param accel_y  16-bit accelerometer Y-axis data
 * @param accel_z  16-bit accelerometer Z-axis data
 *
 * @description Function is used to read accelerometer data.
**/
void c6dofimu15_read_accelerometer ( c6dofimu15_t *ctx, int16_t *accel_x
                                   , int16_t *accel_y
                                   , int16_t *accel_z );

/**
 * @brief Read Acceleration Rate function
 *
 * @param ctx        Click object.
 * @param x_accel_rte  float X-axis acceleration rate
 * @param y_accel_rte  float Y-axis acceleration rate
 * @param z_accel_rte  float Z-axis acceleration rate
 *
 * @description Function is used to calculate acceleration rate
 * in milligravities.
**/
void c6dofimu15_acceleration_rate ( c6dofimu15_t *ctx, float *x_acel_rte
                                   , float *y_acel_rte
                                  , float *z_acel_rte );

/**
 * @brief Read temperture function
 *
 * @param ctx        Click object.
 * 
 * @returns result float temperture data
 *
 * @description Function is used to read temperture in degree Centigrade.
**/
float c6dofimu15_read_temp_out ( c6dofimu15_t *ctx );

/**
 * @brief Disable I2C block function
 *
 * @param ctx        Click object.
 * @param com_sel value enables or disables the property.
 *
 * @description Function is used to enable or disable I2C block.
**/
void c6dofimu15_i2c_disable ( c6dofimu15_t *ctx, uint8_t com_sel );

/**
 * @brief Enable the proper device configuration function
 *
 * @param ctx        Click object.
 * @param dev_cfg value enables or disables the property.
 *
 * @description Function enables the proper device configuration.
**/
void c6dofimu15_device_conf_set ( c6dofimu15_t *ctx, uint8_t dev_cfg );

/**
 * @brief Enable register address incrementation function
 *
 * @param ctx        Click object.
 * @param inc_set value enables or disables the property.
 *
 * @description Function is used to enable or disable  automatical register
 * address incrementation during a multiple byte access with a serial interface.
**/
void c6dofimu15_auto_inc_set ( c6dofimu15_t *ctx, uint8_t inc_set );

/**
 * @brief Perform software reset function
 *
 * @param ctx        Click object.
 * @param rst_en value enables or disables the property.
 *
 * @description Function is used to perform software reset.
**/
void c6dofimu15_sw_rst ( c6dofimu15_t *ctx, uint8_t rst_en );

/**
 * @brief Block Data Update function
 *
 * @param ctx        Click object.
 * @param blk_set value enables or disables the property.
 *
 * @description Function is used to enable or disable block data update.
**/
void c6dofimu15_block_data_update_set ( c6dofimu15_t *ctx, uint8_t blk_set );

/**
 * @brief Set FIFO Mode function
 *
 * @param ctx        Click object.
 * @param fifo_set desired FIFO mode
 *
 * @description Function is used to set FIFO mode.
**/
void c6dofimu15_fifo_mode_set ( c6dofimu15_t *ctx, uint8_t fifo_set );

/**
 * @brief Accelerometer data rate selection function
 *
 * @param ctx        Click object.
 * @param data_rate desired accelerometer output data rate
 *
 * @description Function is used to set desired output data rate.
**/
void c6dofimu15_accel_data_rate ( c6dofimu15_t *ctx, uint8_t data_rate );

/**
 * @brief Accelerometer full-scale selection function
 * 
 * @param ctx        Click object.
 * @param data_rate desired accelerometer full-scale range
 *
 * @description Function is used to set desired full-scale range.
**/
void c6dofimu15_accel_full_scale ( c6dofimu15_t *ctx, uint8_t fs_sel );

/**
 * @brief Gyroscope data rate selection function
 *
 * @param ctx        Click object.
 * @param data_rate desired gyroscope output data rate
 *
 * @description Function is used to set desired output data rate.
**/
void c6dofimu15_gyro_data_rate ( c6dofimu15_t *ctx, uint8_t data_rate );

/**
 * @brief Gyroscope full-scale selection function
 *
 * @param ctx        Click object.
 * @param data_rate desired gyroscope full-scale range
 *
 * @description Function is used to set desired full-scale range.
**/
void c6dofimu15_gyro_full_scale ( c6dofimu15_t *ctx, uint8_t fs_sel );

/**
 * @brief Accelerometer new data available function
 *
 * @param ctx        Click object.
 * 
 * @returns new data available flag
 *
 * @description Function gets the accelerometer new data available flag.
**/
uint8_t c6dofimu15_accel_data_rdy ( c6dofimu15_t *ctx );

/**
 * @brief Gyroscope new data available function
 *
 * @param ctx        Click object.
 * 
 * @returns new data available flag
 *
 * @description Function gets the gyroscope new data available flag.
**/
uint8_t c6dofimu15_gyro_data_rdy ( c6dofimu15_t *ctx );

/**
 * @brief Temperature new data available function
 *
 * @param ctx        Click object.
 * 
 * @returns new data available flag
 *
 * @description Function gets the temperature new data available flag.
**/
uint8_t c6dofimu15_temp_data_rdy ( c6dofimu15_t *ctx );

/**
 * @brief Who Am I function
 *
 * @param ctx        Click object.
 * 
 * @returns Fixed value that identifies the device
 *
 * @description Function gets the fixed value that identifies the device.
 * @note The value is fixed at 0x6B.
**/
uint8_t c6dofimu15_who_im_i ( c6dofimu15_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _C6DOFIMU15_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
