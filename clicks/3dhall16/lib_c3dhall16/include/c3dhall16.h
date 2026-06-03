/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file c3dhall16.h
 * @brief This file contains API for 3D Hall 16 Click Driver.
 */

#ifndef C3DHALL16_H
#define C3DHALL16_H

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
#include "spi_specifics.h"

/*!
 * @addtogroup c3dhall16 3D Hall 16 Click Driver
 * @brief API for configuring and manipulating 3D Hall 16 Click driver.
 * @{
 */

/**
 * @defgroup c3dhall16_reg 3D Hall 16 Registers List
 * @brief List of registers of 3D Hall 16 Click driver.
 */

/**
 * @addtogroup c3dhall16_reg
 * @{
 */

/**
 * @brief 3D Hall 16 register map.
 * @details Specified register map of 3D Hall 16 Click driver.
 */
#define C3DHALL16_REG_BX_MSB            0x00
#define C3DHALL16_REG_BX_LSB            0x01
#define C3DHALL16_REG_BY_MSB            0x02
#define C3DHALL16_REG_BY_LSB            0x03
#define C3DHALL16_REG_BZ_MSB            0x04
#define C3DHALL16_REG_BZ_LSB            0x05
#define C3DHALL16_REG_TEMP_MSB          0x06
#define C3DHALL16_REG_TEMP_LSB          0x07
#define C3DHALL16_REG_CRC               0x08
#define C3DHALL16_REG_DIAG              0x09
#define C3DHALL16_REG_MOD1              0x0A
#define C3DHALL16_REG_MOD2              0x0B
#define C3DHALL16_REG_WU_XH             0x0C
#define C3DHALL16_REG_WU_XL             0x0D
#define C3DHALL16_REG_WU_YH             0x0E
#define C3DHALL16_REG_WU_YL             0x0F
#define C3DHALL16_REG_WU_ZH             0x10
#define C3DHALL16_REG_WU_ZL             0x11
#define C3DHALL16_REG_WU_XY             0x12
#define C3DHALL16_REG_WU_Z              0x13
#define C3DHALL16_REG_RST               0x14
#define C3DHALL16_REG_ID0               0x15
#define C3DHALL16_REG_ID1               0x16
#define C3DHALL16_REG_ID2               0x17
#define C3DHALL16_REG_ID3               0x18
#define C3DHALL16_REG_ID4               0x19
#define C3DHALL16_REG_ID5               0x1A

/*! @} */ // c3dhall16_reg

/**
 * @defgroup c3dhall16_set 3D Hall 16 Registers Settings
 * @brief Settings for registers of 3D Hall 16 Click driver.
 */

/**
 * @addtogroup c3dhall16_set
 * @{
 */

/**
 * @brief 3D Hall 16 DIAG register setting.
 * @details Specified setting for DIAG register of 3D Hall 16 Click driver.
 */
#define C3DHALL16_DIAG_FUSE_PAR_FLG     0x01
#define C3DHALL16_DIAG_CRC_WR_FLG       0x02
#define C3DHALL16_DIAG_WU_PAR_FLG       0x04
#define C3DHALL16_DIAG_RST_FLG          0x08
#define C3DHALL16_DIAG_FRAME_CNT_MASK   0x30
#define C3DHALL16_DIAG_TEST_FLG         0x40
#define C3DHALL16_DIAG_MEAS_FLG         0x80

/**
 * @brief 3D Hall 16 MOD1 register setting.
 * @details Specified setting for MOD1 register of 3D Hall 16 Click driver.
 */
#define C3DHALL16_MOD1_CRC_WR_DIS       0x00
#define C3DHALL16_MOD1_CRC_WR_EN        0x01
#define C3DHALL16_MOD1_TRIG_NONE        0x00
#define C3DHALL16_MOD1_TRIG_ON_READ     0x04
#define C3DHALL16_MOD1_TRIG_ON_STOP     0x08
#define C3DHALL16_MOD1_WU_DIS           0x00
#define C3DHALL16_MOD1_WU_EN            0x10
#define C3DHALL16_MOD1_INT_EN           0x00
#define C3DHALL16_MOD1_INT_DIS          0x40
#define C3DHALL16_MOD1_LOW_POWER        0x00
#define C3DHALL16_MOD1_MASTER_CTRL      0x80
#define C3DHALL16_MOD1_MODE_MASK        0x80

/**
 * @brief 3D Hall 16 MOD2 register setting.
 * @details Specified setting for MOD2 register of 3D Hall 16 Click driver.
 */
#define C3DHALL16_MOD2_FULL_RANGE       0x00
#define C3DHALL16_MOD2_SHORT_RANGE      0x01
#define C3DHALL16_MOD2_XSHORT_RANGE     0x02
#define C3DHALL16_MOD2_RANGE_MASK       0x03
#define C3DHALL16_MOD2_FUPDATE_1000HZ   0x00
#define C3DHALL16_MOD2_FUPDATE_125HZ    0x04
#define C3DHALL16_MOD2_FUPDATE_31HZ     0x08
#define C3DHALL16_MOD2_FUPDATE_16HZ     0x0C
#define C3DHALL16_MOD2_CH_ALL           0x00
#define C3DHALL16_MOD2_CH_BX_TEMP       0xC0
#define C3DHALL16_MOD2_CH_BX_BY         0xD0
#define C3DHALL16_MOD2_CH_BZ_TEMP       0xE0

/**
 * @brief 3D Hall 16 RST register setting.
 * @details Specified setting for RST register of 3D Hall 16 Click driver.
 */
#define C3DHALL16_SOFT_RST              0x01
#define C3DHALL16_RST_FLG_CLR           0x02

/**
 * @brief 3D Hall 16 SPI command bits setting.
 * @details Specified setting for SPI command bits of 3D Hall 16 Click driver.
 */
#define C3DHALL16_SPI_READ_CMD          0x80
#define C3DHALL16_SPI_WRITE_CMD         0x00
#define C3DHALL16_SPI_AUTO_INC          0x40
#define C3DHALL16_SPI_ADDR_MASK         0x3F

/**
 * @brief 3D Hall 16 timeout setting.
 * @details Specified setting for timeout of 3D Hall 16 Click driver.
 */
#define C3DHALL16_RESET_TIMEOUT_MS      10 
#define C3DHALL16_CHECK_COM_TIMEOUT_MS  10 

/**
 * @brief 3D Hall 16 sensitivity constants setting.
 * @details Specified setting for sensitivity constants of 3D Hall 16 Click driver.
 */
#define C3DHALL16_SENS_FULL_RANGE       29.5f
#define C3DHALL16_SENS_SHORT_RANGE      59.0f
#define C3DHALL16_SENS_XSHORT_RANGE     118.0f
#define C3DHALL16_MT_TO_UT              1000.0f

/**
 * @brief 3D Hall 16 temperature conversion constants setting.
 * @details Specified setting for temperature conversion constants of 3D Hall 16 Click driver.
 */
#define C3DHALL16_TEMP_REF_VALUE        4200   
#define C3DHALL16_TEMP_REF_DEG          25.0f  
#define C3DHALL16_TEMP_SENSITIVITY      15.2f  

/**
 * @brief 3D Hall 16 14-bit signed value setting.
 * @details Specified setting for 14-bit signed value of 3D Hall 16 Click driver.
 */
#define C3DHALL16_14BIT_MSB_SHIFT       6
#define C3DHALL16_14BIT_LSB_MASK        0x3F    
#define C3DHALL16_14BIT_SIGN_BIT        0x2000  
#define C3DHALL16_14BIT_SIGN_EXT        0xC000  

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b c3dhall16_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define C3DHALL16_SET_DATA_SAMPLE_EDGE      SET_SPI_DATA_SAMPLE_EDGE
#define C3DHALL16_SET_DATA_SAMPLE_MIDDLE    SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // c3dhall16_set

/**
 * @defgroup c3dhall16_map 3D Hall 16 MikroBUS Map
 * @brief MikroBUS pin mapping of 3D Hall 16 Click driver.
 */

/**
 * @addtogroup c3dhall16_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of 3D Hall 16 Click to the selected MikroBUS.
 */
#define C3DHALL16_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // c3dhall16_map
/*! @} */ // c3dhall16

/**
 * @brief 3D Hall 16 Click context object.
 * @details Context object definition of 3D Hall 16 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;               /**< Interrupt pin - active LOW, indicates measurement complete. */

    // Modules
    spi_master_t spi;                   /**< SPI driver object. */

    pin_name_t chip_select;             /**< Chip select pin descriptor (used for SPI driver). */

    // Sensitivity cache
    float sensitivity;                  /**< Current magnetic sensitivity [LSB/mT], depends on range setting. */

} c3dhall16_t;

/**
 * @brief 3D Hall 16 Click configuration object.
 * @details Configuration object definition of 3D Hall 16 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t miso;                                /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                                /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                                 /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                                  /**< Chip select pin descriptor for SPI driver. */

    // Additional gpio pins
    pin_name_t int_pin;                             /**< Interrupt pin - active LOW, indicates measurement complete. */

    // static variable
    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

} c3dhall16_cfg_t;

/**
 * @brief 3D Hall 16 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    C3DHALL16_OK = 0,
    C3DHALL16_ERROR = -1

} c3dhall16_return_value_t;

/*!
 * @addtogroup c3dhall16 3D Hall 16 Click Driver
 * @brief API for configuring and manipulating 3D Hall 16 Click driver.
 * @{
 */

/**
 * @brief 3D Hall 16 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #c3dhall16_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void c3dhall16_cfg_setup ( c3dhall16_cfg_t *cfg );

/**
 * @brief 3D Hall 16 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #c3dhall16_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #c3dhall16_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall16_init ( c3dhall16_t *ctx, c3dhall16_cfg_t *cfg );

/**
 * @brief 3D Hall 16 default configuration function.
 * @details This function executes a default configuration of 3D Hall 16
 * Click board.
 * @param[in] ctx : Click context object.
 * See #c3dhall16_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t c3dhall16_default_cfg ( c3dhall16_t *ctx );

/**
 * @brief 3D Hall 16 write register function.
 * @details This function writes a single byte of data to the selected register.
 * @param[in] ctx : Click context object.
 * See #c3dhall16_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall16_write_reg ( c3dhall16_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief 3D Hall 16 write registers function.
 * @details This function writes a sequential block of data starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #c3dhall16_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Pointer to the input data buffer.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall16_write_regs ( c3dhall16_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief 3D Hall 16 read register function.
 * @details This function reads a single byte of data from the selected register.
 * @param[in] ctx : Click context object.
 * See #c3dhall16_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the output data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall16_read_reg ( c3dhall16_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief 3D Hall 16 read registers function.
 * @details This function reads a sequential block of data starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #c3dhall16_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Pointer to the output data buffer.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall16_read_regs ( c3dhall16_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief 3D Hall 16 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #c3dhall16_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t c3dhall16_get_int_pin ( c3dhall16_t *ctx );

/**
 * @brief 3D Hall 16 reset function.
 * @details This function performs a software reset of the device.
 * @param[in] ctx : Click context object.
 * See #c3dhall16_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall16_reset ( c3dhall16_t *ctx );

/**
 * @brief 3D Hall 16 check communication function.
 * @details This function verifies communication by reading the 
 * DIAG register and checking the fuse_par_flg bit.
 * @param[in] ctx : Click context object.
 * See #c3dhall16_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall16_check_communication ( c3dhall16_t *ctx );

/**
 * @brief 3D Hall 16 check data ready function.
 * @details This function checks whether a new valid measurement is available.
 * @param[in] ctx : Click context object.
 * See #c3dhall16_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall16_check_data_ready ( c3dhall16_t *ctx );

/**
 * @brief 3D Hall 16 set operating mode function.
 * @details This function sets the sensor operating mode by writing the MOD1 register.
 * @param[in] ctx : Click context object.
 * See #c3dhall16_t object definition for detailed explanation.
 * @param[in] mode : Operating mode.
 * See 3D Hall 16 MOD1 register macros definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall16_set_operating_mode ( c3dhall16_t *ctx, uint8_t mode );

/**
 * @brief 3D Hall 16 set range function.
 * @details This function sets the magnetic measurement range.
 * @param[in] ctx : Click context object.
 * See #c3dhall16_t object definition for detailed explanation.
 * @param[in] range : @li C3DHALL16_MOD2_FULL_RANGE   - +-160 mT
 *                    @li C3DHALL16_MOD2_SHORT_RANGE  - +-100 mT
 *                    @li C3DHALL16_MOD2_XSHORT_RANGE - +-50 mT
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall16_set_range ( c3dhall16_t *ctx, uint8_t range );

/**
 * @brief 3D Hall 16 get magnetic flux function.
 * @details This function reads the raw values of X, Y, and Z axis and converts them to magnetic flux
 * data in microTesla.
 * @param[in] ctx : Click context object.
 * See #c3dhall16_t object definition for detailed explanation.
 * @param[out] x_axis : Pointer to X-axis magnetic flux density result in microTesla.
 * @param[out] y_axis : Pointer to Y-axis magnetic flux density result in microTesla.
 * @param[out] z_axis : Pointer to Z-axis magnetic flux density result in microTesla.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall16_get_magnetic_flux ( c3dhall16_t *ctx, float *x_axis, float *y_axis, float *z_axis );

/**
 * @brief 3D Hall 16 get temperature function.
 * @details This function reads the raw temperature value and converts it to Celsius.
 * @param[in] ctx : Click context object.
 * See #c3dhall16_t object definition for detailed explanation.
 * @param[out] temperature : Pointer to the temperature result in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall16_get_temperature ( c3dhall16_t *ctx, float *temperature );

/**
 * @brief 3D Hall 16 get data function.
 * @details This function reads the X, Y, Z magnetic flux density and
 * internal junction temperature from the sensor.
 * @param[in] ctx : Click context object.
 * See #c3dhall16_t object definition for detailed explanation.
 * @param[out] x_axis : Pointer to X-axis magnetic flux density result in microTesla.
 * @param[out] y_axis : Pointer to Y-axis magnetic flux density result in microTesla.
 * @param[out] z_axis : Pointer to Z-axis magnetic flux density result in microTesla.
 * @param[out] temperature : Pointer to the temperature result in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t c3dhall16_get_data ( c3dhall16_t *ctx, float *x_axis, float *y_axis, float *z_axis, float *temperature );
                               
#ifdef __cplusplus
}
#endif
#endif // C3DHALL16_H

/*! @} */ // c3dhall16

// ------------------------------------------------------------------------ END
