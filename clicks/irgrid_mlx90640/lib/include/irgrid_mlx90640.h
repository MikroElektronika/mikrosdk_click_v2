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
 * \brief This file contains API for IR Grid MLX90640 Click driver.
 *
 * \addtogroup irgrid_mlx90640 IR Grid MLX90640 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef IRGRID_MLX90640_H
#define IRGRID_MLX90640_H

#include "drv_digital_out.h"
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
#define IRGRID_MLX90640_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define IRGRID_MLX90640_RETVAL  uint8_t

#define IRGRID_MLX90640_OK                 0x00
#define IRGRID_MLX90640_INIT_ERROR         0xFF
#define IRGRID_MLX90640_EEPROM_OK          0x00
#define IRGRID_MLX90640_EEPROM_ERROR       0xF0
#define IRGRID_MLX90640_ADJ_PIXELS_ERROR   0xF1
#define IRGRID_MLX90640_ADJ_PIXELS_OK      0x00
#define IRGRID_MLX90640_BROKEN_PIX_ERROR   0xF2
#define IRGRID_MLX90640_OUTLIER_PIX_ERROR  0xF3
#define IRGRID_MLX90640_2_PIX_ERROR        0xF4
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief MLX90640 params definition.
 */
typedef struct
{
    int16_t k_vdd;
    int16_t vdd_25;
    float kv_ptat;
    float kt_ptat;
    uint16_t v_ptat_25;
    float alpha_ptat;
    int16_t gain_eeprom;
    float tgc;
    float cp_kv;
    float cp_kta;
    uint8_t resolution_eeprom;
    uint8_t calibration_mode_eeprom;
    float ks_ta;
    float ks_to[ 4 ];
    int16_t ct[ 4 ];
    float alpha[ 768 ];
    int16_t offset[ 768 ];
    float kta[ 768 ];
    float kv[ 768 ];
    float cp_alpha[ 2 ];
    int16_t cp_offset[ 2 ];
    float il_chess_c[ 3 ];
    uint16_t broken_pixels[ 5 ];
    uint16_t outlier_pixels[ 5 ];

} irgrid_mlx90640_params_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;
    irgrid_mlx90640_params_t params;

} irgrid_mlx90640_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} irgrid_mlx90640_cfg_t;

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
void irgrid_mlx90640_cfg_setup ( irgrid_mlx90640_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
IRGRID_MLX90640_RETVAL irgrid_mlx90640_init ( irgrid_mlx90640_t *ctx, irgrid_mlx90640_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for IrGridMlx90640 click.
 */
void irgrid_mlx90640_default_cfg ( irgrid_mlx90640_t *ctx );

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
void irgrid_mlx90640_generic_write ( irgrid_mlx90640_t *ctx, uint16_t reg, uint8_t *data_buf, uint16_t len );

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
void irgrid_mlx90640_generic_read ( irgrid_mlx90640_t *ctx, uint16_t reg, uint8_t *data_buf, uint16_t len );

/**
 * @brief Functions for reads EEPROM
 *
 * @param ctx          Click object.
 * @param eeprom_data         Buffer in which the data will be stored
 */
void irgrid_mlx90640_read_eeprom ( irgrid_mlx90640_t *ctx, uint16_t *eeprom_data );

/**
 * @brief Parameters storage functions
 *
 * @param ctx          Click object.
 * @param eeprom_data         EEPROM buffer
 */
uint8_t irgrid_mlx90640_extract_parameters ( irgrid_mlx90640_t *ctx, uint16_t *eeprom_data );

/**
 * @brief Functions for sets refresh rate
 *
 * @param ctx          Click object.
 * @param refresh_rate         the refresh Rate data that will be set
 */
void irgrid_mlx90640_set_refresh_rate ( irgrid_mlx90640_t *ctx, uint8_t refresh_rate );

/**
 * @brief Functions for gets frame data
 *
 * @param ctx          Click object.
 * @param frame_data         Buffer in which the data will be stored
 */
uint16_t irgrid_mlx90640_get_frame_data ( irgrid_mlx90640_t *ctx, uint16_t *frame_data );

/**
 * @brief Functions for settings resolution
 *
 * @param ctx          Click object.
 * @param resolution         The resolution that will be set
 */
void irgrid_mlx90640_set_resolution ( irgrid_mlx90640_t *ctx, uint8_t resolution );

/**
 * @brief Functions for gets current resolution
 *
 * @param ctx          Click object.
 *
 * @return current resolution
 */
uint16_t irgrid_mlx90640_get_current_res ( irgrid_mlx90640_t *ctx );

/**
 * @brief Functions for gets current refresh Rate
 *
 * @param ctx          Click object.
 *
 * @return current refresh Rate
 */
uint16_t irgrid_mlx90640_get_refresh_rate ( irgrid_mlx90640_t *ctx );

/**
 * @brief Functions for sets interleaved mode
 *
 * @param ctx          Click object.
 *
 */
void irgrid_mlx90640_set_interleaved_mode ( irgrid_mlx90640_t *ctx );

/**
 * @brief Functions for sets chess mode
 *
 * @param ctx          Click object.
 */
void irgrid_mlx90640_set_chess_mode ( irgrid_mlx90640_t *ctx );

/**
 * @brief Functions for gets current mode
 *
 * @param ctx          Click object.
 *
 * @return current mode
 */
uint16_t irgrid_mlx90640_get_current_mode ( irgrid_mlx90640_t *ctx );

/**
 * @brief Functions for gets pixels temperature
 *
 * @param ctx                  Click object.
 * @param temp_ambient         Ambient temperature data
 * @param pixel_temp           Output matrix pixels
 *
 * @return pixels temperature
 */
void irgrid_mlx90640_get_pixel_temperature ( irgrid_mlx90640_t *ctx, float *temp_ambient, float *pixel_temp );

/**
 * @brief Functions for gets Ambient temperature
 *
 * @param ctx          Click object.
 * @param frame_data           Frame Data
 *
 * @return Ambient temperature
 */
float irgrid_mlx90640_get_temp_ambient ( irgrid_mlx90640_t *ctx, uint16_t *frame_data );

/**
 * @brief Function for gets sub page number
 *
 * @param ctx          Click object.
 * @param frame_data             Frame Data
 *
 * @return  sub page number
 */
uint16_t irgrid_mlx90640_get_subpage_number ( uint16_t *frame_data );

/**
 * @brief Function for gets Vdd
 *
 * @param ctx          Click object.
 * @param frame_data             Frame Data
 */
float irgrid_mlx90640_get_vdd ( irgrid_mlx90640_t *ctx, uint16_t *frame_data );

/**
 * @brief Function for calculating temperature objects
 *
 * @param ctx          Click object.
 * @param frame_data         Frame Data
 * @param tr_data            Real temperature
 * @param px_matrix          Buffer in which the result of the calculation will be stored
 */
void irgrid_mlx90640_calculate_temp_obj ( irgrid_mlx90640_t *ctx, uint16_t *frame_data, float tr_data, float *px_matrix );

/**
 * @brief Function for gets Image
 *
 * @param ctx          Click object.
 * @param frame_data         Frame Data
 * @param px_matrix          Buffer in which the result of the calculation will be stored
 */
void irgrid_mlx90640_get_image ( irgrid_mlx90640_t *ctx, uint16_t *frame_data, float *px_matrix );

#ifdef __cplusplus
}
#endif
#endif  // _IRGRID_MLX90640_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
