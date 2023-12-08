/****************************************************************************
** Copyright (C) 2021 MikroElektronika d.o.o.
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
 * @file efuse2.h
 * @brief This file contains API for eFuse 2 Click Driver.
 */

#ifndef EFUSE2_H
#define EFUSE2_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup efuse2 eFuse 2 Click Driver
 * @brief API for configuring and manipulating eFuse 2 Click driver.
 * @{
 */

/**
 * @defgroup efuse2_set eFuse 2 Registers Settings
 * @brief Settings for registers of eFuse 2 Click driver.
 */

/**
 * @addtogroup efuse2_set
 * @{
 */

/**
 * @brief eFuse 2 description setting.
 * @details Specified setting for description of eFuse 2 Click driver.
 */
#define EFUSE2_AD5175_SHUTDOWN_BIT_MASK                             0x01
#define EFUSE2_AD5175_NORMAL_MODE                                   0x00
#define EFUSE2_AD5175_SHUTDOWN_MODE                                 0x01                                          
  
  /**
 * @brief eFuse 2 ADD5175 Bit masks.
 * @details Specified ADD5175 bit masks for description of eFuse 2 Click driver.
 */
#define EFUSE2_AD5175_CTRL_REG_BIT_MASK                             0x0B
#define EFUSE2_AD5175_FUSE_PROGRAM_SUCCESSFUL                       0x00
#define EFUSE2_AD5175_FUSE_PROGRAM_UNSUCCESSFUL                     0x08
#define EFUSE2_AD5175_WIPER_POS_FROZEN                              0x00
#define EFUSE2_AD5175_UPDATE_WIPER_POS                              0x02
#define EFUSE2_AD5175_50T_PROGRAM_DISABLED                          0x00
#define EFUSE2_AD5175_50T_PROGRAM_ENABLE                            0x01

/**
 * @brief eFuse 2 ADD5175 commands.
 * @details Specified ADD5175 commands for description of eFuse 2 Click driver.
 */
#define EFUSE2_AD5175_COMMAND_NOP                                   0x00
#define EFUSE2_AD5175_COMMAND_WRITE_RDAC                            0x04
#define EFUSE2_AD5175_COMMAND_READ_RDAC                             0x08
#define EFUSE2_AD5175_COMMAND_STORE_WIPER                           0x0C
#define EFUSE2_AD5175_COMMAND_SW_RESET                              0x10
#define EFUSE2_AD5175_COMMAND_READ_50TP                             0x14
#define EFUSE2_AD5175_COMMAND_READ_MEMORY                           0x18
#define EFUSE2_AD5175_COMMAND_WRITE_MEMORY                          0x1C
#define EFUSE2_AD5175_COMMAND_READ_CONTROL                          0x20
#define EFUSE2_AD5175_COMMAND_SW_SHUTDOWN                           0x24  

#define EFUSE2_AD5241_RDAC0                                         0x00
#define EFUSE2_AD5241_RDAC1                                         0x80
#define EFUSE2_AD5241_NO_RESET                                      0x00
#define EFUSE2_AD5241_RESET                                         0x40
#define EFUSE2_AD5241_NO_SHUTDOWN                                   0x00
#define EFUSE2_AD5241_SHUTDOWN                                      0x20
#define EFUSE2_AD5241_O1_LOW                                        0x00
#define EFUSE2_AD5241_O1_HIGH                                       0x10
#define EFUSE2_AD5241_O2_LOW                                        0x00
#define EFUSE2_AD5241_O2_HIGH                                       0x08 

/**
 * @brief eFuse 2 device address setting.
 * @details Specified setting for device slave address selection of
 * eFuse 2 Click driver.
 */
#define EFUSE2_I2C_SLAVE_ADDRESS_AD5241_0                           0x2C
#define EFUSE2_I2C_SLAVE_ADDRESS_AD5241_1                           0x2D
#define EFUSE2_I2C_SLAVE_ADDRESS_AD5241_2                           0x2E
#define EFUSE2_I2C_SLAVE_ADDRESS_AD5241_3                           0x2F
#define EFUSE2_I2C_SLAVE_ADDRESS_AD5175_GND                         0x2F
#define EFUSE2_I2C_SLAVE_ADDRESS_AD5175_VCC                         0x2C
#define EFUSE2_I2C_SLAVE_ADDRESS_AD5175_NC                          0x2E                                                      

/**
 * @brief eFuse 2 fault setting.
 * @details Specified fault setting of eFuse 2 Click driver.
 */
#define EFUSE2_FAULT                                                0x00
#define EFUSE2_NO_FAULT                                             0x01

/**
 * @brief eFuse 2 data setting.
 * @details Specified data setting of eFuse 2 Click driver.
 */
#define EFUSE2_10_BIT                                             0x03FF
#define EFUSE2_DUMMY                                              0x0000


/*! @} */ // efuse2_set

/**
 * @defgroup efuse2_map eFuse 2 MikroBUS Map
 * @brief MikroBUS pin mapping of eFuse 2 Click driver.
 */

/**
 * @addtogroup efuse2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of eFuse 2 Click to the selected MikroBUS.
 */
#define EFUSE2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.flt = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // efuse2_map
/*! @} */ // efuse2

/**
 * @brief eFuse 2 Click context object.
 * @details Context object definition of eFuse 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  rst;             /**< Reset. */

    // Input pins
    digital_in_t  flt;              /**< Fault Indication. */

    // Modules
    i2c_master_t i2c;               /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address_ad5175;   /**< Device slave address (used for I2C driver). */
    uint8_t slave_address_ad5241;   /**< Device slave address (used for I2C driver). */

} efuse2_t;

/**
 * @brief eFuse 2 Click configuration object.
 * @details Configuration object definition of eFuse 2 Click driver.
 */
typedef struct
{
    pin_name_t  scl;                /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;                /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  rst;                /**< Reset. */
    pin_name_t  flt;                /**< Fault Indication. */

    uint32_t  i2c_speed;            /**< I2C serial speed. */
    uint8_t   i2c_address_ad5175;   /**< I2C slave address. */
    uint8_t   i2c_address_ad5241;   /**< I2C slave address. */

} efuse2_cfg_t;

/**
 * @brief eFuse 2 Click instruction object.
 * @details Instruction object definition of eFuse 2 Click driver.
 */
typedef struct
{
    uint8_t select_rdac;
    uint8_t midscale_reset;
    uint8_t active_shutdown;
    uint8_t output_logic_pin_1;
    uint8_t output_logic_pin_2;
    
} ad5241_instru_t;

/**
 * @brief eFuse 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   EFUSE2_OK = 0,
   EFUSE2_ERROR = -1

} efuse2_return_value_t;

/*!
 * @addtogroup efuse2 eFuse 2 Click Driver
 * @brief API for configuring and manipulating eFuse 2 Click driver.
 * @{
 */

/**
 * @brief eFuse 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #efuse2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void efuse2_cfg_setup ( efuse2_cfg_t *cfg );

/**
 * @brief eFuse 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #efuse2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #efuse2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t efuse2_init ( efuse2_t *ctx, efuse2_cfg_t *cfg );

/**
 * @brief eFuse 2 default configuration function.
 * @details This function executes a default configuration of eFuse 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #efuse2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t efuse2_default_cfg ( efuse2_t *ctx );

/**
 * @brief Generic write data to the AD5241 function.
 * @details The function writes a the byte of data and instruction of the
 * AD5241 I2C Compatible, 256-Position Digital Potentiometers
 * on the eFuse 2 click board.
 * @param[in] ctx : Click context object.
 * See #efuse2_t object definition for detailed explanation.
 * @param[in] cmd : Pointer to the memory location where data is stored.
 * @param[in] data_byte : Byte of the data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t efuse2_write_ad5241 ( efuse2_t *ctx, ad5241_instru_t cmd, uint8_t data_byte );

/**
 * @brief Generic read data from the AD5241 function.
 * @details The function read a the byte of data from the
 * AD5241 I2C Compatible, 256-Position Digital Potentiometers
 * on the eFuse 2 click board.
 * @param[in] ctx : Click context object.
 * See #efuse2_t object definition for detailed explanation.
 * @return Read the byte of the data.
 */
uint8_t efuse2_read_ad5241 ( efuse2_t *ctx );

/**
 * @brief Hardware reset function.
 * @details The function reset the
 * AD5241 I2C Compatible, 256-Position Digital Potentiometers
 * on the eFuse 2 click board.
 * @param[out] ctx : Click context object.
 * See #efuse2_t object definition for detailed explanation.
 * @return Nothing.
 */
void efuse2_hw_reset ( efuse2_t *ctx );

/**
 * @brief Set operating voltage function.
 * @details The function set operating voltage, OVLO and UVLO of the
 * AD5241 I2C Compatible, 256-Position Digital Potentiometers
 * on the eFuse 2 click board.
 * @param[in] ctx : Click context object.
 * See #efuse2_t object definition for detailed explanation.
 * @param[in] voltage : Operating voltage ( from 3.65 V to the 15.0 V ).
 * @param[in] min_voltage : Pointer to the memory location where UVLO data is stored.
 * @param[in] max_voltage : Pointer to the memory location where OVLO data is stored.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t efuse2_set_operating_voltage ( efuse2_t *ctx, float voltage, float *min_voltage, float *max_voltage );
/**
 * @brief Generic write data to the AD5175 function.
 * @details The function writes a 10-bit data to the
 * AD5175 Single-Channel, 1024-Position, Digital Rheostat with I2C Interface
 * and 50-TP Memory on the eFuse 2 click board.
 * @param[in] ctx : Click context object.
 * See #efuse2_t object definition for detailed explanation.
 * @param[in] cmd : Pointer to the memory location where data is stored.
 * @param[in] data_byte : 10-bit data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t efuse2_write_ad5175 ( efuse2_t *ctx, uint8_t cmd, uint16_t data_byte );

/**
 * @brief Generic read data from the AD5175 function.
 * @details The function read a 10-bit data of the
 * AD5175 Single-Channel, 1024-Position, Digital Rheostat with I2C Interface
 * and 50-TP Memory on the eFuse 2 click board.
 * @param[in] ctx : Click context object.
 * See #efuse2_t object definition for detailed explanation.
 * @param[in] cmd : Command Operation:
 *      @li @c 0x00 ( EFUSE2_AD5175_COMMAND_NOP ) : NOP, do nothing.
 *      @li @c 0x04 ( EFUSE2_AD5175_COMMAND_WRITE_RDAC ) : Write contents of serial register data to RDAC.
 *      @li @c 0x08 ( EFUSE2_AD5175_COMMAND_READ_RDAC ) : Read contents of RDAC wiper register.
 *      @li @c 0x0C ( EFUSE2_AD5175_COMMAND_STORE_WIPER ) : Store wiper setting: store RDAC setting to 50-TP.
 *      @li @c 0x10 ( EFUSE2_AD5175_COMMAND_SW_RESET ) : Software reset: refresh RDAC with the last 50-TP memory stored value.
 *      @li @c 0x14 ( EFUSE2_AD5175_COMMAND_READ_50TP ) : Read contents of 50-TP from the SDO output in the next frame.
 *      @li @c 0x18 ( EFUSE2_AD5175_COMMAND_READ_MEMORY ) : Read address of the last 50-TP programmed memory location.
 *      @li @c 0x1C ( EFUSE2_AD5175_COMMAND_WRITE_MEMORY ) : Write contents of the serial register data to the control register.
 *      @li @c 0x20 ( EFUSE2_AD5175_COMMAND_READ_CONTROL ) : Read contents of the control register.
 *      @li @c 0x24 ( EFUSE2_AD5175_COMMAND_SW_SHUTDOWN ) : Software shutdown.
 * @param[in] data_byte : 10-bit data to be written.
 * @return 10-bit read data.
 */
uint16_t efuse2_read_ad5175 ( efuse2_t *ctx, uint8_t cmd, uint8_t wiper_location );

/**
 * @brief Read RDAC function.
 * @details The function read a 10-bit RDAC data of the
 * AD5175 Single-Channel, 1024-Position, Digital Rheostat with I2C Interface
 * and 50-TP Memory on the eFuse 2 click board.
 * @param[in] ctx : Click context object.
 * See #efuse2_t object definition for detailed explanation.
 * @return 10-bit read data.
 */
uint16_t efuse2_read_rdac ( efuse2_t *ctx );

/**
 * @brief Enable write function.
 * @details The function enable write of the
 * AD5175 Single-Channel, 1024-Position, Digital Rheostat with I2C Interface
 * and 50-TP Memory on the eFuse 2 click board.
 * @param[in] ctx : Click context object.
 * See #efuse2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t efuse2_enable_write ( efuse2_t *ctx );

/**
 * @brief Write RDAC function.
 * @details The function writes a 10-bit RDAC data of the
 * AD5175 Single-Channel, 1024-Position, Digital Rheostat with I2C Interface
 * and 50-TP Memory on the eFuse 2 click board.
 * @param[in] ctx : Click context object.
 * See #efuse2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t efuse2_write_rdac ( efuse2_t *ctx, uint16_t data_byte );

/**
 * @brief Set operating current function.
 * @details The function set operating current of the
 * AD5241 I2C Compatible, 256-Position Digital Potentiometers
 * on the eFuse 2 click board.
 * @param[in] ctx : Click context object.
 * See #efuse2_t object definition for detailed explanation.
 * @param[in] current : Operating current ( from 0.125 A to the 2.0 A ).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t efuse2_set_current_limit ( efuse2_t *ctx, float current );

/**
 * @brief Software reset function.
 * @details The function software reset the
 * AD5241 I2C Compatible, 256-Position Digital Potentiometers
 * on the eFuse 2 click board.
 * @param[in] ctx : Click context object.
 * See #efuse2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t efuse2_sw_reset ( efuse2_t *ctx );

/**
 * @brief Store wiper setting function.
 * @details The function store wiper setting, store RDAC setting to 50-TP
 * of the AD5241 I2C Compatible, 256-Position Digital Potentiometers
 * on the eFuse 2 click board.
 * @param[in] ctx : Click context object.
 * See #efuse2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t efuse2_store_wiper ( efuse2_t *ctx );

/**
 * @brief Set operating mode function.
 * @details The function set operating mode of the
 * AD5241 I2C Compatible, 256-Position Digital Potentiometers
 * on the eFuse 2 click board.
 * @param[in] ctx : Click context object.
 * See #efuse2_t object definition for detailed explanation.
 * @param[in] mode : Operation mode options
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t efuse2_operating_mode ( efuse2_t *ctx, uint8_t mode );

/**
 * @brief Next frame read function.
 * @details The function next frame read of the
 * AD5241 I2C Compatible, 256-Position Digital Potentiometers
 * on the eFuse 2 click board.
 * @param[in] ctx : Click context object.
 * See #efuse2_t object definition for detailed explanation.
 * @param[in] wiper_location : Wiper location ( from 0x00 to the 0x38 ).
 * @return 10-bit read data.
 */
uint16_t efuse2_next_frame_read ( efuse2_t *ctx, uint8_t wiper_location );

/**
 * @brief Read memory function.
 * @details The function read address of the
 * last 50-TP programmed memory location of the
 * AD5241 I2C Compatible, 256-Position Digital Potentiometers
 * on the eFuse 2 click board.
 * @param[in] ctx : Click context object.
 * See #efuse2_t object definition for detailed explanation.
 * @return 10-bit read data.
 */
uint16_t efuse2_read_memory ( efuse2_t *ctx );

/**
 * @brief Read control register function.
 * @details The function read contents of the control register of the
 * AD5241 I2C Compatible, 256-Position Digital Potentiometers
 * on the eFuse 2 click board.
 * @param[in] ctx : Click context object.
 * See #efuse2_t object definition for detailed explanation.
 * @return Control data
 *        @li @c 0x01 ( EFUSE2_AD5175_50T_PROGRAM_ENABLE ) : Enable device for 50-TP program.
 *        @li @c 0x02 ( EFUSE2_AD5175_UPDATE_WIPER_POS ) : RDAC register write protect.
 *        @li @c 0x08 ( EFUSE2_AD5175_FUSE_PROGRAM_UNSUCCESSFUL ) : Fuse program command successful.
 */
uint8_t efuse2_read_control ( efuse2_t *ctx );

/**
 * @brief Get fault function.
 * @details The function get state of the FLT ( INT ) pin,
 * active low indicator which will be pulled low when a fault is detected.
 * It is an open-drain output that requires an external pull-up resistance
 * of the TPS2596 2.7 to 19 V, 0.125 to 2-A, 89-mO eFuse
 * With Accurate Current Monitor and Fast Overvoltage Protection
 * on the eFuse 2 click board.
 * @param[in] ctx : Click context object.
 * See #efuse2_t object definition for detailed explanation.
 * @return State of the FLT ( INT ) pin.
 */
uint8_t efuse2_get_fault ( efuse2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // EFUSE2_H

/*! @} */ // efuse2

// ------------------------------------------------------------------------ END
