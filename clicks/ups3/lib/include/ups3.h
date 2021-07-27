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
 * @file ups3.h
 * @brief This file contains API for UPS 3 Click Driver.
 */

#ifndef UPS3_H
#define UPS3_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"

/*!
 * @addtogroup ups3 UPS 3 Click Driver
 * @brief API for configuring and manipulating UPS 3 Click driver.
 * @{
 */

/**
 * @addtogroup dir_mode
 * @{
 */

/**
 * @brief UPS 3 description setting.
 * @details Specified setting for description of UPS 3 Click driver.
 */
#define UPS3_DIR_MODE_BACKUP             0x00
#define UPS3_DIR_MODE_CHARGE             0x01

/*! @} */ // dir_mode

/**
 * @addtogroup enable
 * @{
 */

/**
 * @brief UPS 3 description setting.
 * @details Specified setting for description of UPS 3 Click driver.
 */
#define UPS3_ENABLE_SHUTDOWN             0x00
#define UPS3_ENABLE_NORMAL_OPERATION     0x01

/*! @} */ // enable

/**
 * @addtogroup get_error
 * @{
 */

/**
 * @brief UPS 3 general purpose comparator setting.
 * @details Specified setting for general purpose comparator
 * of UPS 3 Click driver.
 */
#define UPS3_GET_ERROR_CMPIN_OK         0x00
#define UPS3_GET_ERROR_CMPIN_EMPTY      0x01

/*! @} */ // get_error

/**
 * @addtogroup get_cap_ok
 * @{
 */

/**
 * @brief UPS 3 voltage ok indicator setting.
 * @details Specified setting for voltage ok indicator
 * of UPS 3 Click driver.
 */
#define UPS3_GET_CAP_OK_FBV_LOW         0x00
#define UPS3_GET_CAP_OK_FBV_HIGH        0x01

/*! @} */ // get_cap_ok

/**
 * @addtogroup get_chrg
 * @{
 */

/**
 * @brief UPS 3 charge/backup mode indicator setting.
 * @details Specified setting for charge/backup mode indicator
 * of UPS 3 Click driver.
 */
#define UPS3_GET_CHRG_CHARGE_MODE       0x00
#define UPS3_GET_CHRG_BACKUP_MODE       0x01

/*! @} */ // get_chrg

/**
 * @addtogroup status
 * @{
 */

/**
 * @brief UPS 3 error status.
 * @details Specified error status 
 * for description of UPS 3 Click driver.
 */
#define UPS3_SUCCESS                      0
#define UPS3_ERROR                       -1


/*! @} */ // status

/**
 * @defgroup ups3_map UPS 3 MikroBUS Map
 * @brief MikroBUS pin mapping of UPS 3 Click driver.
 */

/**
 * @addtogroup ups3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of UPS 3 Click to the selected MikroBUS.
 */
#define UPS3_MAP_MIKROBUS( cfg, mikrobus )        \
    cfg.err = MIKROBUS( mikrobus, MIKROBUS_AN );  \
    cfg.cok = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.dir = MIKROBUS( mikrobus, MIKROBUS_CS );  \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_PWM );  \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // ups3_map
/*! @} */ // ups3

/**
 * @brief UPS 3 Click context object.
 * @details Context object definition of UPS 3 Click driver.
 */
typedef struct
{
    // Output pins
    
    digital_out_t  dir;      /**< Charge/Backup Mode Selector. */
    digital_out_t  en;       /**< Logic-Controlled Shutdown. */

    // Input pins
    
    digital_in_t  err;       /**< General Purpose Comparator. */
    digital_in_t  cok;       /**< Voltage OK Indicator. */
    digital_in_t  int_pin;   /**< Charge/Backup Mode. */

} ups3_t;

/**
 * @brief UPS 3 Click configuration object.
 * @details Configuration object definition of UPS 3 Click driver.
 */
typedef struct
{
    pin_name_t  err;      /**< General Purpose Comparator. */
    pin_name_t  cok;      /**< Voltage OK Indicator. */
    pin_name_t  dir;      /**< Charge/Backup Mode Selector. */
    pin_name_t  en;       /**< Logic-Controlled Shutdown. */
    pin_name_t  int_pin;  /**< Charge/Backup Mode. */

} ups3_cfg_t;

/*!
 * @addtogroup ups3 UPS 3 Click Driver
 * @brief API for configuring and manipulating UPS 3 Click driver.
 * @{
 */

/**
 * @brief UPS 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #ups3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void ups3_cfg_setup ( ups3_cfg_t *cfg );

/**
 * @brief UPS 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #ups3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #ups3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ups3_init ( ups3_t *ctx, ups3_cfg_t *cfg );

/**
 * @brief UPS 3 default configuration function.
 * @details This function executes a default configuration of UPS 3
 * click board.
 * @param[in] ctx : Click context object.
 * See #ups3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t ups3_default_cfg ( ups3_t *ctx );

/**
 * @brief UPS 3 get error function.
 * @details This function reads the state of the ERR ( AN ) pin of UPS 3
 * click board.
 * @param[in] ctx : Click context object.
 * See #ups3_t object definition for detailed explanation.
 * @return @li @c 0 - CMPIN pin voltage is above the comparator rising threshold,
 *         @li @c 1 - CMPIN is below the falling threshold.
 *
 * @note None.
 */
uint8_t ups3_get_error ( ups3_t *ctx );

/**
 * @brief UPS 3 pin get capacitor ok function.
 * @details This function reads the state of the COK ( RST ) pin of UPS 3
 * click board.
 * @param[in] ctx : Click context object.
 * See #ups3_t object definition for detailed explanation.
 * @return @li @c 0 - FBVcap voltage is lower than falling threshold,
 *         @li @c 1 - FBVcap is higher than the rising threshold.
 *
 * @note None.
 */
uint8_t ups3_get_cap_ok ( ups3_t *ctx );

/**
 * @brief UPS 3 get charge/backup mode function.
 * @details This function reads the state of the INT pin of UPS 3
 * click board.
 * @param[in] ctx : Click context object.
 * See #ups3_t object definition for detailed explanation.
 * @return @li @c 0 - Regulator is in charge mode,
 *         @li @c 1 - Regulator is in backup mode.
 *
 * @note None.
 */
uint8_t ups3_get_chrg ( ups3_t *ctx );

/**
 * @brief UPS 3 pin select direction of the operation modes function.
 * @details This function sets the DIR ( CS ) pin on the low or high level of
 * UPS 3 click board.
 * @param[in] ctx : Click context object.
 * See #ups3_t object definition for detailed explanation.
 * @param[in] dir_mode : Direction of the operation modes.
 *         @li @c 0x00 ( UPS3_DIR_MODE_BACKUP ) - Backup mode,
 *         @li @c 0x01 ( UPS3_DIR_MODE_CHARGE ) - Charger mode.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ups3_select_dir_mode ( ups3_t *ctx, uint8_t dir_mode );

/**
 * @brief UPS 3 enable device function.
 * @details This function sets the EN ( PWM ) pin on the low or high level of
 * UPS 3 click board.
 * @param[in] ctx : Click context object.
 * See #ups3_t object definition for detailed explanation.
 * @param[in] enable : Logic-Controlled Shutdown.
 *         @li @c 0x00 ( UPS3_ENABLE_SHUTDOWN ) - Shutdown,
 *         @li @c 0x01 ( UPS3_ENABLE_NORMAL_OPERATION ) - Normal operation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ups3_set_enable ( ups3_t *ctx, uint8_t enable );

/**
 * @brief UPS 3 reset the device function.
 * @details This function executes a hardware reset of
 * UPS 3 click board.
 * @param[in] ctx : Click context object.
 * See #ups3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t ups3_hw_reset ( ups3_t *ctx ) ;

#ifdef __cplusplus
}
#endif
#endif // UPS3_H

/*! @} */ // ups3

// ------------------------------------------------------------------------ END
