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
 * \brief This file contains API for Semper Flash Click driver.
 *
 * \addtogroup semperflash Semper Flash Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef SEMPERFLASH_H
#define SEMPERFLASH_H

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

#define SEMPERFLASH_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS ); \
   cfg.rst   = MIKROBUS( mikrobus, MIKROBUS_RST ); \
   cfg.io2   = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
   cfg.io3   = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define SEMPERFLASH_RETVAL  uint8_t

#define SEMPERFLASH_OK           0x00
#define SEMPERFLASH_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup flash_settings Flash Settings
 * \{
 */
#define SEMPERFLASH_MANUFACTURER_DEVICE_ID                         0x9F
#define SEMPERFLASH_JEDEC_SERIAL_FLASH_DISCOVER_PARAMS             0x5A
#define SEMPERFLASH_DEVICE_ID                                      0x4C
#define SEMPERFLASH_READ_STATUS_REG_1                              0x05
#define SEMPERFLASH_READ_STATUS_REG_2                              0x07
#define SEMPERFLASH_READ_CFG_REG_1                                 0x35
#define SEMPERFLASH_READ_ANY_REG                                   0x65
#define SEMPERFLASH_WRITE_ENABLE                                   0x06
#define SEMPERFLASH_WRITE_ENABLE_VOLATILE                          0x50
#define SEMPERFLASH_WRITE_DISABLE                                  0x04
#define SEMPERFLASH_WRITE_REG                                      0x01
#define SEMPERFLASH_WRITE_ANY_REG                                  0x71
#define SEMPERFLASH_CLEAR_PROGRAM_ERASE_ERROR                      0x30
#define SEMPERFLASH_ENTER_4_BYTE_ADDR_MODE                         0xB7
#define SEMPERFLASH_EXIT_4_BYTE_ADDR_MODE                          0xB8
#define SEMPERFLASH_READ_DATA_LEARN_PATT_REG                       0x41
#define SEMPERFLASH_PROGRAM_DATA_LEARN_PATT                        0x43
#define SEMPERFLASH_WRITE_DATA_LEARN_PATT                          0x4A
#define SEMPERFLASH_AUTOBOOT_REG_WRITE                             0x15
#define SEMPERFLASH_READ_ECC_STATUS                                0x19
#define SEMPERFLASH_CLEAR_ECC_STATUS                               0x1B
#define SEMPERFLASH_DATA_INT_CHECK                                 0x5B
#define SEMPERFLASH_READ_0                                         0x03
#define SEMPERFLASH_READ_1                                         0x13
#define SEMPERFLASH_FAST_READ_0                                    0x0B
#define SEMPERFLASH_FAST_READ_1                                    0x0C
#define SEMPERFLASH_PROGRAM_PAGE_0                                 0x02
#define SEMPERFLASH_PROGRAM_PAGE_1                                 0x12
#define SEMPERFLASH_ERASE_4K_0                                     0x20
#define SEMPERFLASH_ERASE_4K_1                                     0x21
#define SEMPERFLASH_ERASE_256K_1                                   0xD8
#define SEMPERFLASH_ERASE_256K_2                                   0xDC
#define SEMPERFLASH_ERASE_CHIP_1                                   0x60
#define SEMPERFLASH_ERASE_CHIP_2                                   0xC7
#define SEMPERFLASH_ERASE_STATUS                                   0xD0
#define SEMPERFLASH_ERASE_CNT                                      0x5D
#define SEMPERFLASH_SUSPEND_ERASE_PROG_DATA_CHECK                  0x75
#define SEMPERFLASH_SUSPEND_ERASE_PROG                             0x85
#define SEMPERFLASH_RESUME_ERASE_PROG_DATA_CHECK                   0x7A
#define SEMPERFLASH_RESUME_ERASE_PROG                              0x8A
#define SEMPERFLASH_PROG_SECURE_SILICON_REGION                     0x42
#define SEMPERFLASH_READ_SECURE_SILICON_REGION                     0x4B
#define SEMPERFLASH_ASP_PROG                                       0x2F
#define SEMPERFLASH_READ_DYNAMIC_PROTECION_BIT                     0xFA
#define SEMPERFLASH_WRITE_DYNAMIC_PROTECION_BIT                    0xFB
#define SEMPERFLASH_READ_PRESISTENT_PROTECTION_BIT                 0xFC
#define SEMPERFLASH_PROG_PRESISTENT_PROTECTION_BIT                 0xFD
#define SEMPERFLASH_ERASE_PRESISTENT_PROTECTION_BIT                0xE4
#define SEMPERFLASH_WRITE_PPB_PROTECTION_LOCK_BIT                  0xA6
#define SEMPERFLASH_READ_PROG_PRESISTENT_PROTECION_LOCK_BIT        0xA7
#define SEMPERFLASH_PROG_PASSWORD                                  0xE8
#define SEMPERFLASH_PASSWORD_UNLOCK                                0xE9
#define SEMPERFLASH_SOFT_RESET_ENABLE                              0x66
#define SEMPERFLASH_SOFT_RESET                                     0x99
#define SEMPERFLASH_LEGACY_SOFT_RESET                              0xF0
#define SEMPERFLASH_ENTER_DEEP_POWER_DOWN_MODE                     0xB9

#define SEMPERFLASH_PIN_STATE_HIGH                                 1
#define SEMPERFLASH_PIN_STATE_LOW                                  0

#define SEMPERFLASH_ID_ERROR                                       0xCC
#define SEMPERFLASH_SIZE_ERROR                                     0xBB
#define SEMPERFLASH_SUCCESS                                        0xAA

#define SEMPERFLASH_MANUFACTURER_DEVICE_ID_VALUE                   0x34
#define SEMPERFLASH_DEVICE_ID_BYTE_SIZE                            8

#define SEMPERFLASH_STATUS_REG_1_DEFAULT                           0x00
#define SEMPERFLASH_STATUS_REG_1_PROGRAM_ERASE_REG_WRITE_ENABLE    0x02
#define SEMPERFLASH_STATUS_REG_1_DEVICE_BUSY                       0x01
#define SEMPERFLASH_CFG_1_DEFAULT                                  0x00
#define SEMPERFLASH_CFG_2_DEFAULT                                  0x00
#define SEMPERFLASH_CFG_3_DEFAULT                                  0x00
#define SEMPERFLASH_CFG_4_DEFAULT                                  0x00

#define SEMPERFLASH_MANUFACTURER_DEVICE_ID_VALUE                   0x34
#define SEMPERFLASH_MEMORY_BUF_MAX_SIZE                            512
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

    digital_out_t rst;
    digital_out_t io2;
    digital_out_t io3;
    digital_out_t cs;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} semperflash_t;

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

    pin_name_t rst;
    pin_name_t io2;
    pin_name_t io3;

    // static variable 

    uint32_t spi_speed;
    uint8_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} semperflash_cfg_t;

/**
 * @brief Flash configuration structure.
 */
typedef struct
{
    uint8_t status_reg1;
    uint8_t cfg1;
    uint8_t cfg2;
    uint8_t cfg3;
    uint8_t cfg4;

} semperflash_config_t;


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
 * @description This function initializes Click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void semperflash_cfg_setup ( semperflash_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param semperflash Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
SEMPERFLASH_RETVAL semperflash_init ( semperflash_t *ctx, semperflash_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Semper Flash Click.
 */
void semperflash_default_cfg ( semperflash_t *ctx );

/**
 * @brief Send command function.
 *
 * @param ctx  Click object.
 * @param cmd  Command variable.
 *
 * @description This function sends the specified command to the Click module.
 */
void semperflash_send_cmd ( semperflash_t *ctx, uint8_t cmd );

/**
 * @brief Transfer data function.
 *
 * @param ctx        Click object.
 * @param write_buf  Write data.
 * @param wbuf_size   Buffer size.
 * @param read_buf   Read buffer.  
 * @param rbuf_size   Buffer size.
 * 
 * @description This function transfers data to/from the Click module.
 */
void semperflash_transfer_data 
(   
    semperflash_t *ctx, 
    uint8_t *write_buf,
    uint16_t wbuf_size,
    uint8_t *read_buf,
    uint16_t rbuf_size
);

/**
 * @brief Writing data function.
 *
 * @param ctx        Click object.
 * @param write_buf  Write data.
 * @param buf_size   Buffer size.
 * 
 * @description This function transfers data to the Click module.
 */
void semperflash_generic_write 
(   
    semperflash_t *ctx, 
    uint8_t *write_buf,
    uint16_t buf_size
);

/**
 * @brief Write configuration function.
 *
 * @param ctx        Click object.
 * @param cfg_data   Configuration data buffer.
 * 
 * @description This function sends a set of configuration parameters to the Click module.
 */
void semperflash_write_config ( semperflash_t *ctx, semperflash_config_t *cfg_data );

/**
 * @brief Read memory function.
 *
 * @param ctx        Click object.
 * @param addr       Memory address.
 * @param data_buf   Data buffer.  
 * @param buf_size   Buffer size.
 * 
 * @description This function reads data from the flash memory.
 */
uint8_t semperflash_read_memory 
(   
    semperflash_t *ctx,
    uint32_t addr,
    uint8_t *data_buf,
    uint16_t buf_size
);

/**
 * @brief Write memory function.
 *
 * @param ctx        Click object.
 * @param addr       Memory address.
 * @param data_buf   Data buffer.  
 * @param buf_size   Buffer size.
 * 
 * @description This function writes data to the flash memory.
 */
uint8_t semperflash_write_memory 
( 
    semperflash_t *ctx,
    uint32_t addr,
    uint8_t *data_buf,
    uint16_t buf_size
);

/**
 * @brief Erase memory function.
 *
 * @param ctx        Click object.
 * @param addr       Memory address.
 * 
 * @description This function erases data from the flash memory.
 */
void semperflash_erase_memory ( semperflash_t *ctx, uint32_t addr );

/**
 * @brief Get device ID function.
 *
 * @param ctx        Click object.
 * @param id_buf     ID buffer.
 * 
 * @description This function stores the device ID in the specified buffer.
 */
uint8_t semperflash_get_device_id ( semperflash_t *ctx, uint8_t *id_buf );

/**
 * @brief Check manufacturer ID function.
 *
 * @param ctx        Click object.
 * 
 * @description This function checks if the manufacturer ID is OK or not.
 */
uint8_t semperflash_check_manufacturer_id ( semperflash_t *ctx );

/**
 * @brief Check status register function.
 *
 * @param ctx        Click object.
 * 
 * @description This function checks the status register on the Click module.
 */
uint8_t semperflash_check_status_reg_1 ( semperflash_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _SEMPERFLASH_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
