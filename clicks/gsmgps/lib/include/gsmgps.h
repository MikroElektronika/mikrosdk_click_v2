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
 * \brief This file contains API for GSMGPS Click driver.
 *
 * \addtogroup gsmgps GSMGPS Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef GSMGPS_H
#define GSMGPS_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_uart.h"


// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define GSMGPS_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.tx_pin  = MIKROBUS( mikrobus, MIKROBUS_TX ); \
  cfg.rx_pin  = MIKROBUS( mikrobus, MIKROBUS_RX ); \
  cfg.sta = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.pwk = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.rts = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.ri = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
  cfg.cts = MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define GSMGPS_RETVAL  uint8_t

#define GSMGPS_OK           0x00
#define GSMGPS_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup parser_error Parser error
 * \{
 */
#define GSMGPS_PARSER_NO_ERROR    0x00
#define GSMGPS_PARSER_ERROR_REF   0x01
#define GSMGPS_PARSER_ERROR_CMD   0x02
#define GSMGPS_PARSER_ERROR_DATA  0x04
/** \} */

/**
 * \defgroup click_status G2C 3G click status
 * \{
 */
#define GSMGPS_STATUS_DEVICE_READY            1
#define GSMGPS_STATUS_ACT_NETWORK_AND_BROKER  4
#define GSMGPS_STATUS_ACT_NETWORK             2
#define GSMGPS_STATUS_ACT_BROKER              3
#define GSMGPS_STATUS_DEVICE_BUSY             0
/** \} */

/**
 * \defgroup module_state Module power state
 * \{
 */
#define GSMGPS_MODULE_POWER_ON   1
#define GSMGPS_MODULE_POWER_OFF  0
/** \} */

/**
 * \defgroup at_command AT command 
 * \{
 */
#define GSMGPS_SINGLE_CMD_AT        "AT"
#define GSMGPS_SINGLE_CMD_ATI       "ATI"
#define GSMGPS_SINGLE_CMD_AT_W      "AT+W"
#define GSMGPS_SINGLE_CMD_AT_R      "AT+R"
#define GSMGPS_SINGLE_CMD_ATE0      "ATE0"
#define GSMGPS_SINGLE_CMD_ATE1      "ATE1"
#define GSMGPS_SINGLE_CMD_AT_RST    "AT+RST"
#define GSMGPS_SINGLE_CMD_AT_CRST   "AT+CRST"
#define GSMGPS_SINGLE_CMD_AT_GMR    "AT+GMR"
#define GSMGPS_SINGLE_CMD_AT_GMSTA  "AT+GMSTA"
#define GSMGPS_SINGLE_CMD_AT_PUB    "AT+PUB"

#define GSMGPS_SINGLE_CMD_SET_AT_LRSP_1 "AT+LRSP=1"
#define GSMGPS_SINGLE_CMD_SET_AT_LRSP_0 "AT+LRSP=0"
#define GSMGPS_SINGLE_CMD_SET_AT_CEN_1  "AT+CEN=1"
#define GSMGPS_SINGLE_CMD_SET_AT_CEN_0  "AT+CEN=0"
#define GSMGPS_SINGLE_CMD_SET_AT_NWC_1  "AT+NWC=1"
#define GSMGPS_SINGLE_CMD_SET_AT_NWC_0  "AT+NWC=0"
#define GSMGPS_SINGLE_CMD_SET_AT_BRC_1  "AT+BRC=1"
#define GSMGPS_SINGLE_CMD_SET_AT_BRC_0  "AT+BRC=0"
#define GSMGPS_SINGLE_CMD_SET_AT_GPEN_0 "AT+GPEN=0"
#define GSMGPS_SINGLE_CMD_SET_AT_GPEN_1 "AT+GPEN=1"

#define GSMGPS_SINGLE_CMD_GET_AT_LRSP "AT+LRSP?"
#define GSMGPS_SINGLE_CMD_GET_AT_CEN  "AT+CEN?"
#define GSMGPS_SINGLE_CMD_GET_AT_NWC  "AT+NWC?"
#define GSMGPS_SINGLE_CMD_GET_AT_BRC  "AT+BRC?"
#define GSMGPS_SINGLE_CMD_GET_AT_GPEN "AT+GPEN?"
#define GSMGPS_SINGLE_CMD_GET_AT_NWCR "AT+NWCR?"
#define GSMGPS_SINGLE_CMD_GET_AT_BRCR "AT+BRCR?"
#define GSMGPS_SINGLE_CMD_GET_AT_DSET "AT+DSET?"

#define GSMGPS_SINGLE_CMD_TEST_AT_LRSP "AT+LRSP=?"
#define GSMGPS_SINGLE_CMD_TEST_AT_CEN  "AT+CEN=?"
#define GSMGPS_SINGLE_CMD_TEST_AT_NWC  "AT+NWC=?"
#define GSMGPS_SINGLE_CMD_TEST_AT_BRC  "AT+BRC=?"
#define GSMGPS_SINGLE_CMD_TEST_AT_GPEN "AT+GPEN=?"
#define GSMGPS_SINGLE_CMD_TEST_AT_NWCR "AT+NWCR=?"
#define GSMGPS_SINGLE_CMD_TEST_AT_BRCR "AT+BRCR=?"
#define GSMGPS_SINGLE_CMD_TEST_AT_DSET "AT+DSET=?"

#define GSMGPS_MULTI_CMD_AT_DSET "AT+DSET"
#define GSMGPS_MULTI_CMD_AT_BRCR "AT+BRCR"
#define GSMGPS_MULTI_CMD_AT_NWCR "AT+NWCR"


#define GSMGPS_SINGLE_CMD_IFC      "AT+IFC=2,2"
#define GSMGPS_SINGLE_CMD_CMGF     "AT+CMGF=1"
#define GSMGPS_SINGLE_CMD_ATH      "ATH"
#define GSMGPS_SINGLE_CMD_CLCC     "AT+CLCC"
#define GSMGPS_SINGLE_CMD_QGNSSC   "AT+QGNSSC=1"
#define GSMGPS_SINGLE_CMD_QGNSSRD  "AT+QGNSSRD=\"NMEA/GGA\""
#define GSMGPS_CMD_CGNSPWR         "AT+CGNSPWR=1"

#define GSMGPS_CMD_CGNSSEQ      "AT+CGNSSEQ=\"GGA\""
#define GSMGPS_CMD_CGNSINF      "AT+CGNSINF"
#define GSMGPS_CMD_AT_CSCS      "AT+CSCS=\"GSM\""
/** \} */

/**
 * \defgroup support_cmd Current support NEMA command 
 * \{
 */
#define GSM_GPS_NEMA_GPGGA 1
#define GNS_GNSS2_NEMA_RMC   2
#define GSM_GPS_NEMA_GPGLL 3
#define GSM_GPS_NEMA_CGNSINF 4
#define GSM_GPS_NEMA_GPGGA_NUM_ELEMENT 15
#define GSM_GPS_NEMA_GPGLL_NUM_ELEMENT 5
#define GMS_GNSS2_NMEA_RMC_NUM_ELEMENT 9
#define GSM_GPS_NEMA_CGNSINF_NUM_ELEMENT 22
/** \} */

/**
 * \defgroup gpgga_element GPGGA command elements 
 * \{
 */
#define GSM_GPS_GPGGA_TIME                      1 
#define GSM_GPS_GPGGA_LATITUDE                  2
#define GSM_GPS_GPGGA_LATITUDE_SIDE             3
#define GSM_GPS_GPGGA_LONGITUDE                 4
#define GSM_GPS_GPGGA_LONGITUDE_SIDE            5
#define GSM_GPS_GPGGA_QUALITY_INDICATOR         6
#define GSM_GPS_GPGGA_NUMBER_OF_SATELLITES      7
#define GSM_GPS_GPGGA_H_DILUTION_OF_POS         8
#define GSM_GPS_GPGGA_ALTITUDE                  9
#define GSM_GPS_GPGGA_ALTITUDE_UNIT             10
#define GSM_GPS_GPGGA_GEOIDAL_SEPARATION        11
#define GSM_GPS_GPGGA_GEOIDAL_SEPARATION_UNIT   12
#define GSM_GPS_GPGGA_TIME_SINCE_LAST_DGPS      13
#define GSM_GPS_GPGGA_DGPS_REFERENCE_STATION_ID 14
/** \} */

/**
 * \defgroup rmc_element RMC command elements 
 * \{
 */
#define GSM_GPS_RMC_TIME                        1
#define GSM_GPS_RMC_STATUS                      2
#define GSM_GPS_RMC_LATITUDE                    3
#define GSM_GPS_RMC_LONGITUDE                   4
#define GSM_GPS_RMC_SPEED_KNOTS                 5
#define GSM_GPS_RMC_TRACK_ANGLE                 6
#define GSM_GPS_RMC_DATE                        7
#define GSM_GPS_RMC_MAGNETIC_VAR_DEG            8
/** \} */

/**
 * \defgroup rmc_element CGNSINF command elements 
 * \{
 */
#define GSM_GPS_CGNSINF_RUN_STAT                1
#define GSM_GPS_CGNSINF_FIX_STAT                2
#define GSM_GPS_CGNSINF_DATE_TIME               3
#define GSM_GPS_CGNSINF_LATITUDE                4
#define GSM_GPS_CGNSINF_LONGITUDE               5
#define GSM_GPS_CGNSINF_ALTITUDE                6
#define GSM_GPS_CGNSINF_SPEED                   7
#define GSM_GPS_CGNSINF_COURSE                  8
#define GSM_GPS_CGNSINF_FIX_MODE                9 
#define GSM_GPS_CGNSINF_RESERVED1               10
#define GSM_GPS_CGNSINF_HDOP                    11
#define GSM_GPS_CGNSINF_PDOP                    12
#define GSM_GPS_CGNSINF_VDOP                    13
#define GSM_GPS_CGNSINF_RESERVED2               14
#define GSM_GPS_CGNSINF_SAT_VIEW                15
#define GSM_GPS_CGNSINF_SAT_USED                16
#define GSM_GPS_CGNSINF_GLONASS_VIEW            17           
#define GSM_GPS_CGNSINF_RESERVED3               18
#define GSM_GPS_CGNSINF_C_N0                    19
#define GSM_GPS_CGNSINF_HPA                     20
#define GSM_GPS_CGNSINF_VPA                     21
/** \} */

/**
 * \defgroup gpgll_element GPGLL command elements 
 * \{
 */
#define GSM_GPS_GPGLL_LATITUDE                  1
#define GSM_GPS_GPGLL_LATITUDE_SIDE             2
#define GSM_GPS_GPGLL_LONGITUDE                 3
#define GSM_GPS_GPGLL_LONGITUDE_SIDE            4
/** \} */

/**
 * \defgroup error_parser Parser command error 
 * \{
 */
#define GSM_GPS_ERROR_COMMAND_OR_ELEMENT   0xFF
#define GSM_GPS_ERROR_START_OR_END_COMMAND 0x8F
#define GSM_GPS_ERROR_NEXT_ELEMENT         0x4F
#define GSM_GPS_ERROR_CURRENT_ELEMENT      0x2F
#define GSM_GPS_NO_ERROR                   0x00
/** \} */

/**
 * \defgroup driver Driver define
 * \{
 */
#define DRV_RX_BUFFER_SIZE 500
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

    digital_out_t pwk;
    digital_out_t rts;

    // Input pins 

    digital_in_t sta;
    digital_in_t ri;
    digital_in_t cts;
    
    // Modules 

    uart_t uart;

    char uart_rx_buffer[ DRV_RX_BUFFER_SIZE ];
    char uart_tx_buffer[ DRV_RX_BUFFER_SIZE ];

} gsmgps_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t rx_pin;
    pin_name_t tx_pin;
    
    // Additional gpio pins 

    pin_name_t sta;
    pin_name_t pwk;
    pin_name_t rts;
    pin_name_t ri;
    pin_name_t cts;

    // static variable 

    uint32_t          baud_rate;     // Clock speed.
    bool              uart_blocking;
    uart_data_bits_t  data_bit;      // Data bits.
    uart_parity_t     parity_bit;    // Parity bit.  
    uart_stop_bits_t  stop_bit;      // Stop bits.    

} gsmgps_cfg_t;

/**
 * @brief Error type 
 */
// Actuator switch type
typedef uint8_t gsmgps_actuator_sw_t;

// Actuator counter type
typedef int16_t gsmgps_actuator_cnt_t;

// Actuator string type
typedef char gsmgps_actuator_str_t;

// Parser error type
typedef uint8_t gsmgps_error_t;

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
void gsmgps_cfg_setup ( gsmgps_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
GSMGPS_RETVAL gsmgps_init ( gsmgps_t *ctx, gsmgps_cfg_t *cfg );

/**
 * @brief Poewr/Reset module.
 * @param ctx Click object.
 */
void gsmgps_reset ( gsmgps_t *ctx );

/**
 * @brief Generic write function.
 * @param ctx Click object.
 * @param data_buf Data buffer for sends.
 * @param len Number of bytes for sends.
 */
void gsmgps_generic_write ( gsmgps_t *ctx, char *data_buf, uint16_t len );

/**
 * @brief Generic read function.
 * @param ctx Click object.
 * @param data_buf Data buffer for read data.
 * @param max_len The maximum length of data that can be read.
 * @return Number of reads data.
 */
uint16_t gsmgps_generic_read ( gsmgps_t *ctx, char *data_buf, uint16_t max_len );

/**
 * @brief Command function.
 * @param ctx  Click object.
 * @param command  Command.
 * @description This function sends comamnd.
 */
void gsmgps_send_command ( gsmgps_t *ctx, char *command );

/**
 * @brief Generic parser function.
 * @param command NEMA ( GPS/GNSS ) command.
 * @param element Element position in command.
 * @param parser_buf Parser buffer for data storage.
 * @return error data
 */
gsmgps_error_t gsm_gps_generic_parser ( char *rsp,  uint8_t command, uint8_t element, char *parser_buf );

#ifdef __cplusplus
}
#endif
#endif  // _GSMGPS_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
