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
 * \brief This file contains API for ECG 3 Click driver.
 *
 * \addtogroup ecg3 ECG 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef ECG3_H
#define ECG3_H

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#ifdef MikroCCoreVersion
    #if MikroCCoreVersion >= 1
        #include "delays.h"
    #endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
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

#define ECG3_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso    = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi    = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck     = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs      = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.clk     = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
   cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define ECG3_RETVAL  uint8_t

#define ECG3_OK           0x00
#define ECG3_INIT_ERROR   0xFF
/** \} */


/**
 * \defgroup register_addresses Register addresses
 * \{
 */
#define ECG3_NO_OP_REG                     0x00
#define ECG3_STAT_REG                      0x01
#define ECG3_EN_INT_REG                    0x02
#define ECG3_EN_INT2_REG                   0x03
#define ECG3_MNGR_INT_REG                  0x04
#define ECG3_MNGR_DYN_REG                  0x05
#define ECG3_SW_RST_REG                    0x08
#define ECG3_SYNC_REG                      0x09
#define ECG3_FIFO_RST_REG                  0x0A
#define ECG3_INFO_REG                      0x0F
#define ECG3_CNFG_GEN_REG                  0x10
#define ECG3_CNFG_CAL_REG                  0x12
#define ECG3_CNFG_EMUX_REG                 0x14
#define ECG3_CNFG_ECG_REG                  0x15
#define ECG3_CNFG_RTOR1_REG                0x1D
#define ECG3_CNFG_RTOR2_REG                0x1E
#define ECG3_ECG_FIFO_BURST_REG            0x20
#define ECG3_ECG_FIFO_REG                  0x21
#define ECG3_RTOR_REG                      0x25
#define ECG3_NO_OP2_REG                    0x7F
/** \} */

/**
 * \defgroup interrupt_bit_mask Interrupt bit mask 
 * \{
 */
#define ECG3_EINT_MASK                     0x800000
#define ECG3_EOVF_MASK                     0x400000
#define ECG3_FSTINT_MASK                   0x200000
#define ECG3_DCLOFF_INT_MASK               0x100000
#define ECG3_LONINT_MASK                   0x000800
#define ECG3_RRINT_MASK                    0x000400
#define ECG3_SAMP_INT_MASK                 0x000200
#define ECG3_PLLINT_MASK                   0x000100
#define ECG3_LDOFF_PH_INT_MASK             0x000008
#define ECG3_LDOFF_PL_INT_MASK             0x000004
#define ECG3_LDOFF_NH_INT_MASK             0x000002
#define ECG3_LDOFF_NL_INT_MASK             0x000001
/** \} */

/**
 * \defgroup en_int_register Settings for EN_INT and EN_INT2 register
 * \{
 */
#define ECG3_INTB_DIS                      0x000000
#define ECG3_INTB_CMOS                     0x000001
#define ECG3_INTB_OD_NMOS                  0x000002
#define ECG3_INTB_OD_NMOS_INTER_PULLUP     0x000003
/** \} */

/**
 * \defgroup mngr_int_register Settings for MNGR_INT register
 * \{
 */
#define ECG3_FSINT_CLR_DISENGAGED          0x000000
#define ECG3_FSINT_CLR_STAT                0x000040
#define ECG3_RRINT_CLR_STAT                0x000000
#define ECG3_RRINT_CLR_RTOR                0x000010
#define ECG3_RRINT_SELF_CLR                0x000020
#define ECG3_SAMP_CLR_STAT                 0x000000
#define ECG3_SAMP_SELF_CLR                 0x000004
#define ECG3_SAMP_FREQ_1_SAMP              0x000000
#define ECG3_SAMP_FREQ_2_SAMP              0x000001
#define ECG3_SAMP_FREQ_4_SAMP              0x000002
#define ECG3_SAMP_FREQ_16_SAMP             0x000003
/** \} */

/**
 * \defgroup mngr_dyn_register Settings for MNGR_DYN register
 * \{
 */
#define ECG3_NORMAL_MODE                   0x000000
#define ECG3_MANUAL_FAST_MODE              0x400000
#define ECG3_AUTO_FAST_MODE                0x800000
/** \} */

/**
 * \defgroup ecg3_commands  Commands for ECG 3 click 
 * \{
 */
#define ECG3_SW_RST_CMD                    0x000000
#define ECG3_FIFO_RST_CMD                  0x000000
#define ECG3_SYNCH_CMD                     0x000000
/** \} */

/**
 * \defgroup cnfg_gen_register Settings for CNFG_GEN register 
 * \{
 */
#define ECG3_ULP_LON_EN                    0x400000
#define ECG3_FMSTR_32768HZ_ECG_512HZ       0x000000
#define ECG3_FMSTR_32000HZ_ECG_500HZ       0x100000
#define ECG3_FMSTR_32000HZ_ECG_200HZ       0x200000
#define ECG3_FMSTR_31968HZ_ECG_199HZ       0x300000
#define ECG3_ECG_CHANN_EN                  0x080000
#define ECG3_DCLOFF_EN                     0x001000
#define ECG3_ECGP_PULLUP                   0x000000
#define ECG3_ECGP_PULLDOWN                 0x000800
#define ECG3_DCLOFF_IMAG_0NA               0x000000
#define ECG3_DCLOFF_IMAG_5NA               0x000100
#define ECG3_DCLOFF_IMAG_10NA              0x000200
#define ECG3_DCLOFF_IMAG_20NA              0x000300
#define ECG3_DCLOFF_IMAG_50NA              0x000400
#define ECG3_DCLOFF_IMAG_100NA             0x000500
#define ECG3_DCLOFF_VTH_300MV              0x000000
#define ECG3_DCLOFF_VTH_400MV              0x000040
#define ECG3_DCLOFF_VTH_450MV              0x000080
#define ECG3_DCLOFF_VTH_500MV              0x0000C0
#define ECG3_RBIAS_EN                      0x000010
#define ECG3_RBIAS_50M_OHM                 0x000000
#define ECG3_RBIAS_100M_OHM                0x000004
#define ECG3_RBIAS_200M_OHM                0x000008
#define ECG3_RBIASP_EN                     0x000002
#define ECG3_RBIASN_EN                     0x000001
/** \} */

/**
 * \defgroup cfng_cal_register Settings for CNFG_CAL register
 * \{
 */
#define ECG3_VCAL_EN                       0x400000
#define ECG3_VMODE_UNIPOL                  0x000000
#define ECG3_VMODE_BIPOL                   0x200000
#define ECG3_VMAG_250MICROV                0x000000
#define ECG3_VMAG_500MICROV                0x100000
#define ECG3_FCAL_256HZ                    0x000000
#define ECG3_FCAL_64HZ                     0x001000
#define ECG3_FCAL_16HZ                     0x002000
#define ECG3_FCAL_4HZ                      0x003000
#define ECG3_FCAL_1HZ                      0x004000
#define ECG3_FCAL_1PER4HZ                  0x005000
#define ECG3_FCAL_1PER16HZ                 0x006000
#define ECG3_FCAL_1PER64HZ                 0x007000
#define ECG3_FIFTY_CAL_THIGH               0x000000
#define ECG3_FIFTY_50PERCENTS              0x000800
/** \} */

/**
 * \defgroup cnfg_emux_register Settings for CNFG_EMUX register
 * \{
 */
#define ECG3_INPUT_NON_INV                 0x000000
#define ECG3_INPUT_INV                     0x800000
#define ECG3_ECGP_EN                       0x000000
#define ECG3_ECGP_DIS                      0x200000
#define ECG3_ECGN_EN                       0x000000
#define ECG3_ECGN_DIS                      0x100000
#define ECG3_ECGP_NO_CAL                   0x000000
#define ECG3_ECGP_CAL_VMID                 0x040000
#define ECG3_ECGP_CAL_VCALP                0x080000
#define ECG3_ECGP_CAL_VCALN                0x0C0000
#define ECG3_ECGN_NO_CAL                   0x000000
#define ECG3_ECGN_CAL_VMID                 0x010000
#define ECG3_ECGN_CAL_VCALP                0x020000
#define ECG3_ECGN_CAL_VCALN                0x030000
/** \} */

/**
 * \defgroup cnfg_ecg_register Settings for CNFG_ECG register
 * \{
 */
#define ECG3_GAIN_20VPERV                  0x000000
#define ECG3_GAIN_40VPERV                  0x010000
#define ECG3_GAIN_80VPERV                  0x020000
#define ECG3_GAIN_160VPERV                 0x030000
#define ECG3_DHPF_BYPASS_DC                0x000000
#define ECG3_DHPF_500MILIHZ                0x004000
#define ECG3_DLPF_BYPASS                   0x000000
#define ECG3_DLPF_40HZ                     0x001000
#define ECG3_DLPF_100HZ                    0x002000
#define ECG3_DLPF_150HZ                    0x003000
/** \} */

/**
 * \defgroup cnfg_rtor_register Settings for CNFG_RTOR1 and CNFG_RTOR2 register
 * \{
 */
#define ECG3_WNDW_6                        0x000000
#define ECG3_WNDW_8                        0x100000
#define ECG3_WNDW_10                       0x200000
#define ECG3_WNDW_12                       0x300000
#define ECG3_WNDW_14                       0x400000
#define ECG3_WNDW_16                       0x500000
#define ECG3_WNDW_18                       0x600000
#define ECG3_WNDW_20                       0x700000
#define ECG3_WNDW_22                       0x800000
#define ECG3_WNDW_24                       0x900000
#define ECG3_WNDW_26                       0xA00000
#define ECG3_WNDW_28                       0xB00000
#define ECG3_RRGAIN_1                      0x000000
#define ECG3_RRGAIN_2                      0x010000
#define ECG3_RRGAIN_4                      0x020000
#define ECG3_RRGAIN_8                      0x030000
#define ECG3_RRGAIN_16                     0x040000
#define ECG3_RRGAIN_32                     0x050000
#define ECG3_RRGAIN_64                     0x060000
#define ECG3_RRGAIN_128                    0x070000
#define ECG3_RRGAIN_256                    0x080000
#define ECG3_RRGAIN_512                    0x090000
#define ECG3_RRGAIN_1024                   0x0A0000
#define ECG3_RRGAIN_2048                   0x0B0000
#define ECG3_RRGAIN_4096                   0x0C0000
#define ECG3_RRGAIN_8192                   0x0D0000
#define ECG3_RRGAIN_16384                  0x0E0000
#define ECG3_RRGAIN_AUTO_SCALE             0x0F0000
#define ECG3_RTOR_EN                       0x008000
#define ECG3_PAVG_2                        0x000000
#define ECG3_PAVG_4                        0x001000
#define ECG3_PAVG_8                        0x002000
#define ECG3_PAVG_16                       0x003000
/** \} */

/**
 * \defgroup functions_response Functions response
 * \{
 */
#define ECG3_WRONG_ADDR                    0x01
#define ECG3_OK                            0x00
#define ECG3_INT_OCCURRED                  0x01
#define ECG3_INT_NOT_OCCURRED              0x00
#define ECG3_DUMMY_BYTE                    0x00
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

    digital_out_t cs;
    digital_out_t clk;

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} ecg3_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t miso;
    pin_name_t mosi;
    pin_name_t sck;
    pin_name_t cs;

    // Additional gpio pins 

    pin_name_t clk;
    pin_name_t int_pin;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} ecg3_cfg_t;

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
void ecg3_cfg_setup ( ecg3_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param ecg3          Click object.
 * @param cfg           Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
ECG3_RETVAL ecg3_init ( ecg3_t *ctx, ecg3_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx           Click object.
 *
 * @description This function executes default configuration for ECG 3 click.
 */
void ecg3_default_cfg ( ecg3_t *ctx );

/**
 * @brief Generic transfer function.
 *
 * @param ctx          Click object.
 * @param wr_buf       Write data buffer
 * @param wr_len       Number of byte in write data buffer
 * @param rd_buf       Read data buffer
 * @param rd_len       Number of byte in read data buffer
 *
 * @description Generic SPI transfer, for sending and receiving packages
 */
void ecg3_generic_transfer ( ecg3_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len );

/**
 * @brief Generic Write function
 *
 * @param ctx           Click object.
 * @param reg_addr      Address where data be written
 * @param data_in       Data to be written
 *
 * @returns 0 - OK, 1 - Wrong address
 *
 * @description Function writes data to the register.
 */
uint8_t ecg3_write_reg ( ecg3_t *ctx, uint8_t reg_addr, uint32_t data_in );

/**
 * @brief Generic Read function
 *
 * @param ctx           Click object.
 * @param reg_addr      Address which from data be read
 * @param data_in       Memory where data be stored
 *
 * @returns 0 - OK, 1 - Wrong address
 *
 * @description Function reads data from the register.
 */
uint8_t ecg3_read_reg ( ecg3_t *ctx, uint8_t reg_addr, uint32_t *data_out );

/**
 * @brief Status Check function
 *
 * @param ctx           Click object.
 * @param bit_mask      Bit mask to checking the desired interrupt flag
 *
 * @returns 0 - Interrupt is not present, 1 - Interrupt is present
 *
 * @description Function checks a status flag for the desired interrupt.
 */
uint8_t ecg3_check_status ( ecg3_t *ctx, uint32_t bit_mask );

/**
 * @brief SW Reset function
 * 
 * @param ctx           Click object.
 * 
 * @description Function performs a SW reset.
 */
void ecg3_sw_reset ( ecg3_t *ctx );

/**
 * @brief FIFO Reset function
 *
 * @param ctx           Click object.
 * 
 * @description Function performs a FIFO reset.
 */
void ecg3_fifo_reset ( ecg3_t *ctx );

/**
 * @brief Synchronization function
 *
 * @param ctx           Click object.
 * 
 * @description Function performs a device synchronization and begins a new ECG operations and recording.
 */
void ecg3_sync ( ecg3_t *ctx );

/**
 * @brief ECG Get function
 *
 * @param ctx           Click object.
 * @param out_ecg       Memory where ECG data be stored
 *
 * @description Function reads ECG data from FIFO register.
 */
void ecg3_get_ecg ( ecg3_t *ctx, uint32_t *out_ecg );

/**
 * @brief RTOR Get function
 *
 * @param ctx           Click object.
 * @param out_hr        Memory where Heart Rate data be stored
 * @param out_rr        Memory where R - R data be stored
 *
 * @description Function reads Heart Rate and R - R data and calculates Heart Rate data to BPM,
 * and R - R data to ms.
 */
void ecg3_get_rtor ( ecg3_t *ctx, uint16_t *out_hr, uint16_t *out_rr );


#ifdef __cplusplus
}
#endif
#endif  // _ECG3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
