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
 * \brief This file contains API for TMR Angle Click driver.
 *
 * \addtogroup tmrangle TMR Angle Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef TMRANGLE_H
#define TMRANGLE_H

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

#define TMRANGLE_MAP_MIKROBUS( cfg, mikrobus ) \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define TMRANGLE_RETVAL  uint8_t

#define TMRANGLE_OK           0x00
#define TMRANGLE_INIT_ERROR   0xFF
/** \} */

/**
* \defgroup sin_cos_signal Sinus and Cosinus Signal
* \{
*/
#define TMRANGLE_COS_N    0x00
#define TMRANGLE_COS_P    0x01
#define TMRANGLE_SIN_P    0x02
#define TMRANGLE_SIN_N    0x03
/** \} */

/**
* \defgroup angle Angle
* \{
*/
#define TMRANGLE_RAD2DEGFACTOR        57.3248
#define TMRANGLE_ROTATION_VALID       1
#define TMRANGLE_ANGLE45_H            0.7894
#define TMRANGLE_ANGLE45_L            0.7806
#define TMRANGLE_ANGLE135_H           2.3594
#define TMRANGLE_ANGLE135_L           2.3506
/** \} */

/**
* \defgroup diff_value Differential Value
* \{
*/
#define TMRANGLE_MAX_DIFF_SIN         1251
#define TMRANGLE_MAX_DIFF_COS         1217
#define TMRANGLE_MIN_DIFF_SIN         -1200
#define TMRANGLE_MIN_DIFF_COS         -1206
#define TMRANGLE_SIN_45               854.0
#define TMRANGLE_COS_45               864.0
#define TMRANGLE_SIN_135              873.0
#define TMRANGLE_COS_135              -865.0
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
    uint16_t sin_p;

    uint16_t cos_p;

    uint16_t sin_n;

    uint16_t cos_n;

    int16_t diff_x;

    int16_t diff_y;

    float uncalibrated_angle;
}tmrangle_analog_sensor_data_t;

typedef struct
{
    digital_out_t cs;

    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

    tmrangle_analog_sensor_data_t sensor_data;

} tmrangle_t;

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


    // static variable 

    uint32_t spi_speed;
    uint8_t spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} tmrangle_cfg_t;


typedef struct
{
    uint8_t angle_45_found;
    uint8_t angle_135_found;
    uint32_t nr_valid_rotations;
    
    int32_t max_cos;

    int32_t min_cos;

    int32_t max_sin;
    
    int32_t min_sin;

    float x_45;

    float x_135;
    
    float y_45;
    
    float y_135;
    
    float x_45_corr;
    
    float x_135_corr;

    float y_45_corr;

    float y_135_corr;

    float amplitude_x;

    float amplitude_y;

    float offset_x;

    float offset_y;
    
    float magnitude_45;
    
    float magnitude_135;
    
    float ortho_one_dir;

} tmrangle_rotation_data_store_t;

typedef struct
{
    tmrangle_rotation_data_store_t rotation_data;
    
    float sin_ortho;
    
    float cos_ortho;

} tmrangle_calib_data_t;

typedef struct
{
    int32_t max_diff_sin;
    int32_t max_diff_cos;
    int32_t min_diff_sin;
    int32_t min_diff_cos;
    float sin_45;
    float cos_45;
    float sin_135;
    float cos_135;

} trigonometry_t;

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
void tmrangle_cfg_setup ( tmrangle_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param tmrangle Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this Click.
 */
TMRANGLE_RETVAL tmrangle_init ( tmrangle_t *ctx, tmrangle_cfg_t *cfg );

/**
 * @brief Read the ADC value of the selected channel function
 *
 * @param ctx          Click object.
 * @param channel
 *
 * @return result
 * 12-bit selected channel ADC value
 *
 * @description Function read the ADC value of the selected channel
 * of the TLE5501 magnetic position sensor � analog TMR based angle sensors
 * on TMR Angle Click board.
 */
uint16_t tmrangle_read_channel_adc ( tmrangle_t* ctx, uint8_t channel );

/**
 * @brief Calculate the differential values of sin,cos signal and angle function
 *
 * @param ctx          Click object.
 *
 * @description Function calculates the differential values
 * will be used to get the uncalibrated angle value or in the calibration procedure
 * of the TLE5501 magnetic position sensor � analog TMR based angle sensors
 * on TMR Angle Click board.
 */
void tmrangle_calculate_diff ( tmrangle_t* ctx );

/**
 * @brief Read and stores parameters data function
 *
 * @param ctx          Click object.
 *
 * @description Function read and stores negative and positive, sine and cosine parameters data
 * of the TLE5501 magnetic position sensor � analog TMR based angle sensors
 * on TMR Angle Click board.
 */
void tmrangle_init_sensor_data ( tmrangle_t* ctx );

/**
 * @brief Calculates and stores parameters, based on found parameters function
 *
 * @param ctx                          Click object.
 * @param rotation_data_store          Structure where rotation data be stored
 *
 * @description Function calculates and stores parameters, based on found parameters
 * of the TLE5501 magnetic position sensor � analog TMR based angle sensors
 * on TMR Angle Click board.
 */
void tmrangle_calib_calculate_one_direction ( tmrangle_t* ctx,
                                              tmrangle_rotation_data_store_t* rotation_data_store );

/**
 * @brief Calculates and stores parameters, based on found parameters from both CW and CCW function
 *
 * @param calib_param                 Structure where calibration parameters ( CW and CCW ) data be stored
 *
 * @description Function calculates and stores parameters, based on found parameters from both CW and CCW
 * of the TLE5501 magnetic position sensor � analog TMR based angle sensors
 * on TMR Angle Click board.
 */
void tmrangle_calib_calculate_ortho ( tmrangle_calib_data_t* calib_param );

/**
 * @brief Initialization and stores calibration parameters function
 *
 * @param ctx              Click object.
 * @param calib_param      Structure where calibration parameters data be stored
 * @param dev              Structure with trigonometry values.
 *
 * @description Function initialization and stores calibration parameters
 * of the TLE5501 magnetic position sensor � analog TMR based angle sensors
 * on TMR Angle Click board.
 *
 * @note
 * This function must be called once before tmrangle_calibrationFindParam( tmrangle_calib_data_t *calibParam ).
 */
void tmrangle_init_calib_data ( tmrangle_t* ctx, tmrangle_calib_data_t* calib_param,
                                trigonometry_t* dev );

/**
 * @brief Calculate the calibrated angle ( radians ) function
 *
 * @param ctx              Click object.
 * @param calib_param                 Structure where calibration parameters data be stored
 *
 * @returns result
 * float value of the angle in radians
 *
 * @description Function calculates the calibrated angle in radians
 * of the TLE5501 magnetic position sensor � analog TMR based angle sensors
 * on TMR Angle Click board.
 */
float tmrangle_get_calib_deff_angle ( tmrangle_t* ctx, tmrangle_calib_data_t* calib_param );


/**
 * @brief Calculate the calibrated angle ( degree ) function
 *
 * @param ctx            Click object.
 * @param calib_param    Structure where calibration parameters data be stored
 *
 * @returns result
 * float value of the angle in degree
 *
 * @description Function calculate the calibrated angle in degree and
 * this structure holds the current sensor calibration parameters
 * of the TLE5501 magnetic position sensor � analog TMR based angle sensors
 * on TMR Angle Click board.
 */
float tmrangle_get_calib_angle ( tmrangle_t* ctx, tmrangle_calib_data_t* calib_param );

/**
 * @brief Compare and stores rotation parameters function
 *
 * @param ctx                         Click object.
 * @param rotation_data_store         Structure where rotation parameters data be stored
 *
 * @description Function compare and stores rotation parameters,
 * used to search for the min/max differential signal level
 * of the TLE5501 magnetic position sensor � analog TMR based angle sensors
 * on TMR Angle Click board.
 */
void tmrangle_calib_find_min_max ( tmrangle_t* ctx, tmrangle_rotation_data_store_t* rotation_data_store );

/**
 * @brief Find and stores rotation parameters ( min, max ) function
 *
 * @param ctx                         Click object.
 * @param rotation_data_store         Structure where rotation parameters data be stored
 *
 * @description Function compare and stores rotation parameters,
 * used to search for the magnitude components (at 45 and 135 deg) and min/max signal level
 * of the TLE5501 magnetic position sensor � analog TMR based angle sensors
 * on TMR Angle Click board.
 */
void tmrangle_calib_one_direction_min_max ( tmrangle_t* ctx, tmrangle_rotation_data_store_t* rotation_data_store );

/**
 * @brief Get new calibration rotation parameters function
 *
 * @param ctx             Click object.
 * @param calib_param     Structure where calibration parameters data be stored
 *
 * @description Function get when new calibration parameters have been found,
 * this function will do mathematical calculations, which will take more time for one moment
 * of the TLE5501 magnetic position sensor � analog TMR based angle sensors
 * on TMR Angle Click board.
 *
 * @note
 * @description This function will extract the maximum, minimum voltage levels,
 * amplitude, offset, and orthogonality.
 */
void tmrangle_calibration_find_param ( tmrangle_t* ctx,
                                       tmrangle_calib_data_t* calib_param );



#ifdef __cplusplus
}
#endif
#endif  // _TMRANGLE_H_

/** \} */ // End public_function group
/// \}    // End Click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
