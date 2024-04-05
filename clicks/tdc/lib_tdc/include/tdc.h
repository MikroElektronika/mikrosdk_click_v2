/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file tdc.h
 * @brief This file contains API for TDC Click Driver.
 */

#ifndef TDC_H
#define TDC_H

#ifdef __cplusplus
extern "C"{
#endif

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

/*!
 * @addtogroup tdc TDC Click Driver
 * @brief API for configuring and manipulating TDC Click driver.
 * @{
 */

/**
 * @defgroup tdc_reg TDC Registers List
 * @brief List of registers of TDC Click driver.
 */

/**
 * @addtogroup tdc_reg
 * @{
 */

/**
 * @brief TDC description register.
 * @details Specified register for description of TDC Click driver.
 */
#define TDC_REG_ADR_CONFIG1                                                0x00
#define TDC_REG_ADR_CONFIG2                                                0x01
#define TDC_REG_ADR_INT_STATUS                                             0x02
#define TDC_REG_ADR_INT_MASK                                               0x03
#define TDC_REG_ADR_COARSE_CNTR_OVF_H                                      0x04
#define TDC_REG_ADR_COARSE_CNTR_OVF_L                                      0x05
#define TDC_REG_ADR_CLOCK_CNTR_OVF_H                                       0x06
#define TDC_REG_ADR_CLOCK_CNTR_OVF_L                                       0x07
#define TDC_REG_ADR_CLOCK_CNTR_STOP_MASK_H                                 0x08
#define TDC_REG_ADR_CLOCK_CNTR_STOP_MASK_L                                 0x09
#define TDC_REG_ADR_TIME1                                                  0x10
#define TDC_REG_ADR_CLOCK_COUNT1                                           0x11
#define TDC_REG_ADR_TIME2                                                  0x12
#define TDC_REG_ADR_CLOCK_COUNT2                                           0x13
#define TDC_REG_ADR_TIME3                                                  0x14
#define TDC_REG_ADR_CLOCK_COUNT3                                           0x15
#define TDC_REG_ADR_TIME4                                                  0x16
#define TDC_REG_ADR_CLOCK_COUNT4                                           0x17
#define TDC_REG_ADR_TIME5                                                  0x18
#define TDC_REG_ADR_CLOCK_COUNT5                                           0x19
#define TDC_REG_ADR_CLOCK_COUNTX(num)                                      (TDC_REG_ADR_CLOCK_COUNT1+2*((num)-1))
#define TDC_REG_ADR_TIME6                                                  0x1A
#define TDC_REG_ADR_TIMEX(num)                                             (TDC_REG_ADR_TIME1+2*((num)-1))
#define TDC_REG_ADR_CALIBRATION1                                           0x1B
#define TDC_REG_ADR_CALIBRATION2                                           0x1C
#define TDC_REG_DEFAULTS_CONFIG2                                           0x40      
#define TDC_REG_DEFAULTS_INT_MASK                                          0x07     

#define TDC_REG_SHIFT_CONFIG1_FORCE_CAL                                    7
#define TDC_REG_SHIFT_CONFIG1_PARITY_EN                                    6
#define TDC_REG_SHIFT_CONFIG1_TRIGG_EDGE                                   5
#define TDC_REG_SHIFT_CONFIG1_STOP_EDGE                                    4
#define TDC_REG_SHIFT_CONFIG1_START_EDGE                                   3
#define TDC_REG_SHIFT_CONFIG1_MEAS_MODE                                    1
#define TDC_REG_SHIFT_CONFIG1_START_MEAS                                   0

#define TDC_REG_VAL_CONFIG1_MEAS_MODE_MIN                                  1
#define TDC_REG_VAL_CONFIG1_MEAS_MODE_MAX                                  2
#define TDC_REG_VAL_CONFIG1_MEAS_MODE(num)                                 ((num)-1)


#define TDC_REG_SHIFT_CONFIG2_CALIBRATION2_PERIODS                         6
#define TDC_REG_SHIFT_CONFIG2_AVG_CYCLES                                   3
#define TDC_REG_SHIFT_CONFIG2_NUM_STOP                                     0

#define TDC_REG_VAL_CONFIG2_CALIBRATION2_PERIODS_2                         0
#define TDC_REG_VAL_CONFIG2_CALIBRATION2_PERIODS_10                        1
#define TDC_REG_VAL_CONFIG2_CALIBRATION2_PERIODS_20                        2
#define TDC_REG_VAL_CONFIG2_CALIBRATION2_PERIODS_40                        3

#define TDC_REG_VAL_CONFIG2_AVG_CYCLES_MIN_VAL                             0
#define TDC_REG_VAL_CONFIG2_AVG_CYCLES_MIN                                 1 << TDC_REG_VAL_CONFIG2_AVG_CYCLES_MIN_VAL
#define TDC_REG_VAL_CONFIG2_AVG_CYCLES_MAX_VAL                             7
#define TDC_REG_VAL_CONFIG2_AVG_CYCLES_MAX                                 1 << TDC_REG_VAL_CONFIG2_AVG_CYCLES_MAX_VAL

#define TDC_REG_VAL_CONFIG2_NUM_STOP(num)                                  ((num)-1)
#define TDC_REG_VAL_CONFIG2_NUM_STOP_MAX                                   5

#define TDC_REG_SHIFT_INT_STATUS_MEAS_COMPLETE_FLAG                        4
#define TDC_REG_SHIFT_INT_STATUS_MEAS_STARTED_FLAG                         3
#define TDC_REG_SHIFT_INT_STATUS_CLOCK_CNTR_OVF_INT                        2
#define TDC_REG_SHIFT_INT_STATUS_COARSE_CNTR_OVF_INT                       1
#define TDC_REG_SHIFT_INT_STATUS_NEW_MEAS_INT                              0

#define TDC_REG_SHIFT_INT_MASK_CLOCK_CNTR_OVF_MASK                         2
#define TDC_REG_SHIFT_INT_MASK_COARSE_CNTR_OVF_MASK                        1
#define TDC_REG_SHIFT_INT_MASK_NEW_MEAS_MASK                               0

/*! @} */ // tdc_reg

/**
 * @defgroup tdc_set TDC Registers Settings
 * @brief Settings for registers of TDC Click driver.
 */

/**
 * @addtogroup tdc_set
 * @{
 */

/**
 * @brief TDC description setting.
 * @details Specified setting for description of TDC Click driver.
 */
#define TDC_CLOCK_FREQ_HZ                                                  8000000    
#define TDC_RING_OSC_FREQ_KHZ                                              8000
#define TDC_RING_OSC_FREQ_MHZ                                              TDC_RING_OSC_FREQ_KHZ/1000
#define PS_PER_K_SEC                                                       1000000000
#define US_PER_K_SEC                                                       1000000
#define PS_PER_PIC32_SEC                                                   878000
#define PS_PER_PIC_SEC                                                     160000
#define TDC_CLOCK_FREQ_HZ_PS_PER_PIC_SEC                                   0.05
#define TDC_CLOCK_FREQ_HZ_PS_PER_ARM_SEC                                   14.745
    
#define TDC_MCU_CLOCK_MODE_168_MHZ                                         0
#define TDC_MCU_CLOCK_MODE_80_MHZ                                          1
#define TDC_MCU_CLOCK_MODE_64_MHZ                                          2

/*! @} */ // tdc_set

/**
 * @defgroup tdc_map TDC MikroBUS Map
 * @brief MikroBUS pin mapping of TDC Click driver.
 */

/**
 * @addtogroup tdc_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of TDC Click to the selected MikroBUS.
 */
#define TDC_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
    cfg.oen = MIKROBUS( mikrobus, MIKROBUS_AN );   \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST );    \
    cfg.trg = MIKROBUS( mikrobus, MIKROBUS_PWM );   \
    cfg.stop = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.start = MIKROBUS( mikrobus, MIKROBUS_RST );   \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // tdc_map
/*! @} */ // tdc

/**
 * @brief TDC Click context object.
 * @details Context object definition of TDC Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  oen;         /**< Oscillator enable pin. */
    digital_out_t  en;          /**< Enable signal to TDC pin. */
    digital_out_t  stop;        /**< STOP signal to TDC pin. */
    digital_out_t  start;       /**< START signal to TDC pin. */

    // Input pins               
    digital_in_t  trg;          /**< Trigger pin. */
    digital_in_t  int_pin;      /**< Interrupt pinw. */

    // Modules                  
    spi_master_t  spi;          /**< SPI driver object. */

    pin_name_t  chip_select;    /**< Chip select pin descriptor (used for SPI driver). */

} tdc_t;

/**
 * @brief TDC Click configuration object.
 * @details Configuration object definition of TDC Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t  miso;       /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t  mosi;       /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t  sck;        /**< Clock pin descriptor for SPI driver. */
    pin_name_t  cs;         /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t  oen;       /**< Oscillator enable pin. */
    pin_name_t  en;        /**< Enable signal to TDC pin. */
    pin_name_t  trg;       /**< Trigger pin. */
    pin_name_t  stop;      /**< STOP signal to TDC pin. */
    pin_name_t  start;     /**< START signal to TDC pin. */
    pin_name_t  int_pin;   /**< Interrupt pinw. */

    // static variable
    uint32_t                           spi_speed;        /**< SPI serial speed. */
    spi_master_mode_t                  spi_mode;         /**< SPI master mode. */
    spi_master_chip_select_polarity_t  cs_polarity;      /**< Chip select pin polarity. */

} tdc_cfg_t;

/**
 * @brief TDC Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   TDC_OK = 0,
   TDC_ERROR = -1

} tdc_return_value_t;

/*!
 * @addtogroup tdc TDC Click Driver
 * @brief API for configuring and manipulating TDC Click driver.
 * @{
 */

/**
 * @brief TDC configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #tdc_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void tdc_cfg_setup ( tdc_cfg_t *cfg );

/**
 * @brief TDC initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #tdc_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #tdc_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tdc_init ( tdc_t *ctx, tdc_cfg_t *cfg );

/**
 * @brief TDC default configuration function.
 * @details This function executes a default configuration of TDC
 * click board.
 * @param[in] ctx : Click context object.
 * See #tdc_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t tdc_default_cfg ( tdc_t *ctx );

/**
 * @brief TDC data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #tdc_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tdc_generic_write ( tdc_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief TDC data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #tdc_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tdc_generic_read ( tdc_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief TDC data write byte function.
 * @details This function writes byte of data from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #tdc_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tdc_generic_write_byte ( tdc_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief TDC data read function.
 * @details This function reads byte of data from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #tdc_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tdc_generic_read_byte ( tdc_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief TDC pulse generation function.
 * @details This function pulse generation mikroBUS 2, RST pin ( Start ), CS pin ( Stop ).
 * @param[in] ctx : Click context object.
 * See #tdc_t object definition for detailed explanation.
 * @param[in] u_sec : Pulse period in microseconds.
 * @param[in] n_stops : Number of stop signals.
 * @return Nothing.
 *
 * @note None.
 */
void tdc_gen_pulse ( tdc_t *ctx, uint32_t u_sec, uint8_t n_stops );

/**
 * @brief TDC start measurement function.
 * @details This function start a new measurement 
 * of the TDC7200 Time-to-Digital Converter for Time-of-Flight Applications in LIDAR, 
 * Magnetostrictive and Flow Meters on the TDC click board™. 
 * @param[in] ctx : Click context object.
 * See #tdc_t object definition for detailed explanation.
 * @return Nothing.
 *
 * @note None.
 */
void tdc_start_measurement ( tdc_t *ctx );

/**
 * @brief TDC setup overflow function.
 * @details This function configuration of the overflow
 * of the TDC7200 Time-to-Digital Converter for Time-of-Flight Applications in LIDAR, 
 * Magnetostrictive and Flow Meters on the TDC click board™.
 * @param[in] ctx : Click context object.
 * See #tdc_t object definition for detailed explanation.
 * @param[in] overflow_ps : Overflow time in  ( ps ).
 * @return Nothing.
 *
 * @note None.
 */
void tdc_setup_overflow ( tdc_t *ctx, uint32_t overflow_ps );

/**
 * @brief TDC setup measurement function.
 * @details This function measurements configuration  
 * of the TDC7200 Time-to-Digital Converter for Time-of-Flight Applications in LIDAR, 
 * Magnetostrictive and Flow Meters on the TDC click board™. 
 * @param[in] ctx : Click context object.
 * See #tdc_t object definition for detailed explanation.
 * @param[in] cal_periods : Number of measuring clock periods, one of ( 2, 10, 20, 40 ).
 * @param[in] avg_cycles : Set number of averaging cycles ( 1, 2, 4, 8, 16, 32, 64, 128 ). 
 * @param[in] num_stops : Set number of stop pulses ( 1, 2, 3, 4, 5 ).
 * @param[in] mode : Set measurement mode ( 1, 2 ). Mode 1 is for measurements < 500 us.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tdc_setup_measurement ( tdc_t *ctx, uint8_t cal_periods, uint8_t avg_cycles, uint8_t num_stops, uint8_t mode );

/**
 * @brief TDC get measurement function.
 * @details This function get measurements  
 * of the TDC7200 Time-to-Digital Converter for Time-of-Flight Applications in LIDAR, 
 * Magnetostrictive and Flow Meters on the TDC click board™. 
 * @param[in] ctx : Click context object.
 * See #tdc_t object definition for detailed explanation.
 * @param[in] clock_mode : MCU clock mode.
 * @param[in] measure_num_stop : Number of stops per measurement.
 * @param[out] time : Pointer to the Measured Times values.
 * @param[out] clock_countn : Pointer to the CLOCK Counter values.
 * @param[out] tof :  Pointer to the Time Of Flight values.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tdc_get_measurement ( tdc_t *ctx, uint8_t clock_mode, uint8_t measure_num_stop, uint32_t *time, uint32_t *clock_countn, uint32_t *tof );

/**
 * @brief TDC get interrupt function.
 * @details This function get interrupt pin state
 * of the TDC7200 Time-to-Digital Converter for Time-of-Flight Applications in LIDAR, 
 * Magnetostrictive and Flow Meters on the TDC click board™.
 * @param[in] ctx : Click context object.
 * See #tdc_t object definition for detailed explanation.
 * @return INT pin state.
 *
 * @note None.
 */
uint8_t tdc_get_interrupt ( tdc_t *ctx );

/**
 * @brief TDC get trigger signal function.
 * @details This function get trigger signal
 * of the TDC7200 Time-to-Digital Converter for Time-of-Flight Applications in LIDAR, 
 * Magnetostrictive and Flow Meters on the TDC click board™.
 * @param[in] ctx : Click context object.
 * See #tdc_t object definition for detailed explanation.
 * @return TRG pin state.
 *
 * @note None.
 */
uint8_t tdc_get_trg ( tdc_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // TDC_H

/*! @} */ // tdc

// ------------------------------------------------------------------------ END
