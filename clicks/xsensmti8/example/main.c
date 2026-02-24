/*!
 * @file main.c
 * @brief XSENS MTi-8 Click Example.
 *
 * # Description
 * This example demonstrates the initialization and use of the XSENS MTi-8 Click board.
 * It performs device identification, configures the output data streams, and displays 
 * various sensor measurements such as orientation (quaternion and Euler angles), 
 * magnetic field, latitude and longitude, altitude, barometric pressure, temperature, 
 * and UTC time. The data is received in the MTData2 format and parsed accordingly.
 *
 * The demo application is composed of two sections:
 *
 * ## Application Init
 * Initializes the logger and the XSENS MTi-8 Click driver, resets the device, 
 * retrieves the device and firmware information, and sets the desired output configuration.
 *
 * ## Application Task
 * Continuously reads and parses the incoming MTData2 messages and displays 
 * the decoded sensor data via the logger terminal.
 *
 * @note
 * For the GNSS functionality, make sure the GNSS RTK Click with a valid GNSS antenna is
 * connected to the MTi-8 Click board.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "xsensmti8.h"

static xsensmti8_t xsensmti8;
static log_t logger;

/**
 * @brief XSENS MTi-8 parse received message function.
 * @details This function parses the last received response message from the XSENS MTi-8 Click board 
 * and logs the interpreted information to the logger terminal.
 * @param[in] ctx : Click context object.
 * See #xsensmti8_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void xsensmti8_parse_message ( xsensmti8_t *ctx );

/**
 * @brief XSENS MTi-8 parse MTData2 message function.
 * @details This function parses MTData2 formatted sensor data received from the XSENS MTi-8 Click board
 * and logs the interpreted measurements to the logger terminal.
 * @param[in] ctx : Click context object.
 * See #xsensmti8_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void xsensmti8_parse_mtdata2 ( xsensmti8_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    xsensmti8_cfg_t xsensmti8_cfg;  /**< Click config object. */

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.
    xsensmti8_cfg_setup( &xsensmti8_cfg );
    XSENSMTI8_MAP_MIKROBUS( xsensmti8_cfg, MIKROBUS_1 );
    if ( UART_ERROR == xsensmti8_init( &xsensmti8, &xsensmti8_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, ">> Reset Device\r\n" );
    xsensmti8_reset_device ( &xsensmti8 );
    if ( XSENSMTI8_OK == xsensmti8_wait_message ( &xsensmti8, XSENSMTI8_MID_WAKE_UP ) )
    {
        xsensmti8_parse_message ( &xsensmti8 );
    }
    
    log_printf( &logger, ">> Get Device ID\r\n" );
    xsensmti8.cmd_msg.msg_id = XSENSMTI8_MID_DEVICE_ID;
    xsensmti8.cmd_msg.data_len = 0;
    xsensmti8_send_message ( &xsensmti8 );
    if ( XSENSMTI8_OK == xsensmti8_wait_message ( &xsensmti8, XSENSMTI8_MID_DEVICE_ID_ACK ) )
    {
        xsensmti8_parse_message ( &xsensmti8 );
    }
    
    log_printf( &logger, ">> Get Product Code\r\n" );
    xsensmti8.cmd_msg.msg_id = XSENSMTI8_MID_PRODUCT_CODE;
    xsensmti8.cmd_msg.data_len = 0;
    xsensmti8_send_message ( &xsensmti8 );
    if ( XSENSMTI8_OK == xsensmti8_wait_message ( &xsensmti8, XSENSMTI8_MID_PRODUCT_CODE_ACK ) )
    {
        xsensmti8_parse_message ( &xsensmti8 );
    }
    
    log_printf( &logger, ">> Get HW Version\r\n" );
    xsensmti8.cmd_msg.msg_id = XSENSMTI8_MID_HARDWARE_VERSION;
    xsensmti8.cmd_msg.data_len = 0;
    xsensmti8_send_message ( &xsensmti8 );
    if ( XSENSMTI8_OK == xsensmti8_wait_message ( &xsensmti8, XSENSMTI8_MID_HARDWARE_VERSION_ACK ) )
    {
        xsensmti8_parse_message ( &xsensmti8 );
    }
    
    log_printf( &logger, ">> Get FW Version\r\n" );
    xsensmti8.cmd_msg.msg_id = XSENSMTI8_MID_FW_REV;
    xsensmti8.cmd_msg.data_len = 0;
    xsensmti8_send_message ( &xsensmti8 );
    if ( XSENSMTI8_OK == xsensmti8_wait_message ( &xsensmti8, XSENSMTI8_MID_FW_REV_ACK ) )
    {
        xsensmti8_parse_message ( &xsensmti8 );
    }
    
    log_printf( &logger, ">> Set Output Configuration\r\n" );
    xsensmti8.cmd_msg.msg_id = XSENSMTI8_MID_OUTPUT_CONFIGURATION;
    xsensmti8.cmd_msg.data_len = 32;
    xsensmti8.cmd_msg.data_buf[ 0 ] = ( uint8_t ) ( ( XSENSMTI8_XDI_QUARTERNION >> 8 ) & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 1 ] = ( uint8_t ) ( XSENSMTI8_XDI_QUARTERNION & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 2 ] = ( uint8_t ) ( ( XSENSMTI8_XDI_FREQUENCY_5HZ >> 8 ) & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 3 ] = ( uint8_t ) ( XSENSMTI8_XDI_FREQUENCY_5HZ & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 4 ] = ( uint8_t ) ( ( XSENSMTI8_XDI_EULER_ANGLES >> 8 ) & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 5 ] = ( uint8_t ) ( XSENSMTI8_XDI_EULER_ANGLES & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 6 ] = ( uint8_t ) ( ( XSENSMTI8_XDI_FREQUENCY_5HZ >> 8 ) & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 7 ] = ( uint8_t ) ( XSENSMTI8_XDI_FREQUENCY_5HZ & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 8 ] = ( uint8_t ) ( ( XSENSMTI8_XDI_MAGNETIC_FIELD >> 8 ) & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 9 ] = ( uint8_t ) ( XSENSMTI8_XDI_MAGNETIC_FIELD & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 10 ] = ( uint8_t ) ( ( XSENSMTI8_XDI_FREQUENCY_5HZ >> 8 ) & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 11 ] = ( uint8_t ) ( XSENSMTI8_XDI_FREQUENCY_5HZ & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 12 ] = ( uint8_t ) ( ( XSENSMTI8_XDI_LAT_LON >> 8 ) & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 13 ] = ( uint8_t ) ( XSENSMTI8_XDI_LAT_LON & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 14 ] = ( uint8_t ) ( ( XSENSMTI8_XDI_FREQUENCY_5HZ >> 8 ) & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 15 ] = ( uint8_t ) ( XSENSMTI8_XDI_FREQUENCY_5HZ & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 16 ] = ( uint8_t ) ( ( XSENSMTI8_XDI_ALTITUDE_ELLIPSOID >> 8 ) & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 17 ] = ( uint8_t ) ( XSENSMTI8_XDI_ALTITUDE_ELLIPSOID & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 18 ] = ( uint8_t ) ( ( XSENSMTI8_XDI_FREQUENCY_5HZ >> 8 ) & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 19 ] = ( uint8_t ) ( XSENSMTI8_XDI_FREQUENCY_5HZ & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 20 ] = ( uint8_t ) ( ( XSENSMTI8_XDI_BARO_PRESSURE >> 8 ) & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 21 ] = ( uint8_t ) ( XSENSMTI8_XDI_BARO_PRESSURE & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 22 ] = ( uint8_t ) ( ( XSENSMTI8_XDI_FREQUENCY_5HZ >> 8 ) & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 23 ] = ( uint8_t ) ( XSENSMTI8_XDI_FREQUENCY_5HZ & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 24 ] = ( uint8_t ) ( ( XSENSMTI8_XDI_TEMPERATURE >> 8 ) & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 25 ] = ( uint8_t ) ( XSENSMTI8_XDI_TEMPERATURE & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 26 ] = ( uint8_t ) ( ( XSENSMTI8_XDI_FREQUENCY_5HZ >> 8 ) & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 27 ] = ( uint8_t ) ( XSENSMTI8_XDI_FREQUENCY_5HZ & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 28 ] = ( uint8_t ) ( ( XSENSMTI8_XDI_UTC_TIME >> 8 ) & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 29 ] = ( uint8_t ) ( XSENSMTI8_XDI_UTC_TIME & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 30 ] = ( uint8_t ) ( ( XSENSMTI8_XDI_FREQUENCY_5HZ >> 8 ) & 0xFF );
    xsensmti8.cmd_msg.data_buf[ 31 ] = ( uint8_t ) ( XSENSMTI8_XDI_FREQUENCY_5HZ & 0xFF );
    xsensmti8_send_message ( &xsensmti8 );
    if ( XSENSMTI8_OK == xsensmti8_wait_message ( &xsensmti8, XSENSMTI8_MID_OUTPUT_CONFIGURATION_ACK ) )
    {
        xsensmti8_parse_message ( &xsensmti8 );
    }
    
    log_printf( &logger, ">> Go to Measurement\r\n" );
    xsensmti8.cmd_msg.msg_id = XSENSMTI8_MID_GO_TO_MEASUREMENT;
    xsensmti8.cmd_msg.data_len = 0;
    xsensmti8_send_message ( &xsensmti8 );
    if ( XSENSMTI8_OK == xsensmti8_wait_message ( &xsensmti8, XSENSMTI8_MID_GO_TO_MEASUREMENT_ACK ) )
    {
        xsensmti8_parse_message ( &xsensmti8 );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    if ( XSENSMTI8_OK == xsensmti8_read_message( &xsensmti8 ) ) 
    {
        xsensmti8_parse_message ( &xsensmti8 );
    }
}

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

static void xsensmti8_parse_message ( xsensmti8_t *ctx ) 
{
    uint32_t u32_data = 0;
    switch ( ctx->rsp_msg.msg_id )
    {
        case XSENSMTI8_MID_WAKE_UP:
        {
            log_printf( &logger, "Wake UP acknowledge\r\n" );
            xsensmti8.cmd_msg.msg_id = XSENSMTI8_MID_WAKE_UP_ACK;
            xsensmti8.cmd_msg.data_len = 0;
            xsensmti8_send_message ( &xsensmti8 );
            break;
        }
        case XSENSMTI8_MID_DEVICE_ID_ACK:
        {
            log_printf ( &logger, "%.2X%.2X%.2X%.2X\r\n", 
                        ( uint16_t ) xsensmti8.rsp_msg.data_buf[ 0 ], 
                        ( uint16_t ) xsensmti8.rsp_msg.data_buf[ 1 ], 
                        ( uint16_t ) xsensmti8.rsp_msg.data_buf[ 2 ], 
                        ( uint16_t ) xsensmti8.rsp_msg.data_buf[ 3 ] );
            break;
        }
        case XSENSMTI8_MID_PRODUCT_CODE_ACK:
        {
            log_printf ( &logger, "%s\r\n", xsensmti8.rsp_msg.data_buf );
            break;
        }
        case XSENSMTI8_MID_HARDWARE_VERSION_ACK:
        {
            log_printf ( &logger, "%u.%u\r\n", 
                        ( uint16_t ) xsensmti8.rsp_msg.data_buf[ 0 ], 
                        ( uint16_t ) xsensmti8.rsp_msg.data_buf[ 1 ] );
            break;
        }
        case XSENSMTI8_MID_FW_REV_ACK:
        {
            u32_data = ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ 3 ] << 24 ) |
                       ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ 4 ] << 16 ) |
                       ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ 5 ] << 8 ) |
                       ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ 6 ] << 0 );
            log_printf ( &logger, "%u.%u.%u build %lu ", 
                        ( uint16_t ) xsensmti8.rsp_msg.data_buf[ 0 ], 
                        ( uint16_t ) xsensmti8.rsp_msg.data_buf[ 1 ], 
                        ( uint16_t ) xsensmti8.rsp_msg.data_buf[ 2 ],
                        u32_data );
            u32_data = ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ 7 ] << 24 ) |
                       ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ 8 ] << 16 ) |
                       ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ 9 ] << 8 ) |
                       ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ 10 ] << 0 );
            log_printf ( &logger, "rev %lu\r\n", u32_data );
            break;
        }
        case XSENSMTI8_MID_MT_DATA_2:
        {
            xsensmti8_parse_mtdata2( ctx );
            break;
        }
        case XSENSMTI8_MID_WARNING:
        {
            u32_data = ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ 0 ] << 24 ) |
                       ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ 1 ] << 16 ) |
                       ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ 2 ] << 8 ) |
                       ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ 3 ] << 0 );
            switch ( u32_data )
            {
                case XSENSMTI8_WARNING_REFUSED:
                {
                    log_printf ( &logger, "Warning: A configuration item was refused by the GNSS receiver\r\n" );
                    break;
                }
                case XSENSMTI8_WARNING_TIMEOUT:
                {
                    log_printf ( &logger, "Warning: Communication with the GNSS receiver has timed out\r\n" );
                    break;
                }
                case XSENSMTI8_WARNING_FAILED:
                {
                    log_printf ( &logger, "Warning: Communication with the GNSS receiver failed\r\n" );
                    break;
                }
                case XSENSMTI8_WARNING_LOST:
                {
                    log_printf ( &logger, "Warning: Communication with the GNSS receiver was lost\r\n" );
                    break;
                }
                case XSENSMTI8_WARNING_INCOMPLETE:
                {
                    log_printf ( &logger, "Warning: Incomplete dataset delivered by the GNSS receiver\r\n" );
                    break;
                }
                default:
                {
                    log_printf ( &logger, "Warning: Unknown\r\n" );
                    break;
                }
            }
            break;
        }
        default:
        {
            log_printf ( &logger, "MID: %.2X\r\n", ( uint16_t ) xsensmti8.rsp_msg.msg_id );
            log_printf ( &logger, "DATA_LEN: %u\r\n", ( uint16_t ) xsensmti8.rsp_msg.data_len );
            if ( xsensmti8.rsp_msg.data_len )
            {
                log_printf ( &logger, "DATA:" );
            }
            for ( uint8_t cnt = 0; cnt < xsensmti8.rsp_msg.data_len; cnt++ )
            {
                log_printf ( &logger, " %.2X", ( uint16_t ) xsensmti8.rsp_msg.data_buf[ cnt ] );
                if ( ( 15 == cnt % 16 ) && ( ( cnt + 1 ) < xsensmti8.rsp_msg.data_len ) )
                {
                    log_printf ( &logger, "\r\n     " );
                }
            }
            if ( xsensmti8.rsp_msg.data_len )
            {
                log_printf ( &logger, "\r\n" );
            }
        }
    }
    log_printf( &logger, "--------------------------------\r\n" );
}

static void xsensmti8_parse_mtdata2 ( xsensmti8_t *ctx )
{
    uint16_t data_id = 0;
    uint8_t data_len = 0;
    uint8_t msg_data_cnt = 0;
    uint16_t u16_data = 0;
    uint32_t u32_data = 0;
    int32_t s32_data = 0;
    float f_data = 0;
    for ( msg_data_cnt = 0; msg_data_cnt < xsensmti8.rsp_msg.data_len; msg_data_cnt += ( data_len + 3 ) )
    {
        data_id = ( ( uint16_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt ] << 8 ) | 
                  xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 1 ];
        data_len = xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 2 ];
        switch ( data_id )
        {
            case XSENSMTI8_XDI_QUARTERNION:
            {
                if ( 16 == data_len )
                {
                    s32_data = ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 3 ] << 24 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 4 ] << 16 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 5 ] << 8 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 6 ] << 0 );
                    memcpy ( &f_data, &s32_data, sizeof ( s32_data ) );
                    log_printf ( &logger, "Q0: %f, ", f_data );
                    s32_data = ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 7 ] << 24 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 8 ] << 16 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 9 ] << 8 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 10 ] << 0 );
                    memcpy ( &f_data, &s32_data, sizeof ( s32_data ) );
                    log_printf ( &logger, "Q1: %f, ", f_data );
                    s32_data = ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 11 ] << 24 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 12 ] << 16 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 13 ] << 8 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 14 ] << 0 );
                    memcpy ( &f_data, &s32_data, sizeof ( s32_data ) );
                    log_printf ( &logger, "Q2: %f, ", f_data );
                    s32_data = ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 15 ] << 24 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 16 ] << 16 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 17 ] << 8 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 18 ] << 0 );
                    memcpy ( &f_data, &s32_data, sizeof ( s32_data ) );
                    log_printf ( &logger, "Q3: %f\r\n", f_data );
                }
                break;
            }
            case XSENSMTI8_XDI_EULER_ANGLES:
            {
                if ( 12 == data_len )
                {
                    s32_data = ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 3 ] << 24 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 4 ] << 16 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 5 ] << 8 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 6 ] << 0 );
                    memcpy ( &f_data, &s32_data, sizeof ( s32_data ) );
                    log_printf ( &logger, "Roll: %f, ", f_data );
                    s32_data = ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 7 ] << 24 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 8 ] << 16 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 9 ] << 8 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 10 ] << 0 );
                    memcpy ( &f_data, &s32_data, sizeof ( s32_data ) );
                    log_printf ( &logger, "Pitch: %f, ", f_data );
                    s32_data = ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 11 ] << 24 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 12 ] << 16 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 13 ] << 8 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 14 ] << 0 );
                    memcpy ( &f_data, &s32_data, sizeof ( s32_data ) );
                    log_printf ( &logger, "Yaw: %f\r\n", f_data );
                }
                break;
            }
            case XSENSMTI8_XDI_TEMPERATURE:
            {
                if ( 4 == data_len )
                {
                    s32_data = ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 3 ] << 24 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 4 ] << 16 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 5 ] << 8 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 6 ] << 0 );
                    memcpy ( &f_data, &s32_data, sizeof ( s32_data ) );
                    log_printf ( &logger, "Temperature: %.2f degC\r\n", f_data );
                }
                break;
            }
            case XSENSMTI8_XDI_MAGNETIC_FIELD:
            {
                if ( 12 == data_len )
                {
                    s32_data = ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 3 ] << 24 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 4 ] << 16 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 5 ] << 8 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 6 ] << 0 );
                    memcpy ( &f_data, &s32_data, sizeof ( s32_data ) );
                    log_printf ( &logger, "Mag X: %f, ", f_data );
                    s32_data = ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 7 ] << 24 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 8 ] << 16 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 9 ] << 8 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 10 ] << 0 );
                    memcpy ( &f_data, &s32_data, sizeof ( s32_data ) );
                    log_printf ( &logger, "Mag Y: %f, ", f_data );
                    s32_data = ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 11 ] << 24 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 12 ] << 16 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 13 ] << 8 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 14 ] << 0 );
                    memcpy ( &f_data, &s32_data, sizeof ( s32_data ) );
                    log_printf ( &logger, "Mag Z: %f\r\n", f_data );
                }
                break;
            }
            case XSENSMTI8_XDI_ALTITUDE_ELLIPSOID:
            {
                if ( 4 == data_len )
                {
                    s32_data = ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 3 ] << 24 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 4 ] << 16 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 5 ] << 8 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 6 ] << 0 );
                    memcpy ( &f_data, &s32_data, sizeof ( s32_data ) );
                    log_printf ( &logger, "Altitude: %.2f m\r\n", f_data );
                }
                break;
            }
            case XSENSMTI8_XDI_LAT_LON:
            {
                if ( 8 == data_len )
                {
                    s32_data = ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 3 ] << 24 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 4 ] << 16 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 5 ] << 8 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 6 ] << 0 );
                    memcpy ( &f_data, &s32_data, sizeof ( s32_data ) );
                    log_printf ( &logger, "Latitude: %f, ", f_data );
                    s32_data = ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 7 ] << 24 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 8 ] << 16 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 9 ] << 8 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 10 ] << 0 );
                    memcpy ( &f_data, &s32_data, sizeof ( s32_data ) );
                    log_printf ( &logger, "Longitude: %f\r\n", f_data );
                }
                break;
            }
            case XSENSMTI8_XDI_BARO_PRESSURE:
            {
                if ( 4 == data_len )
                {
                    u32_data = ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 3 ] << 24 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 4 ] << 16 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 5 ] << 8 ) |
                               ( ( uint32_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 6 ] << 0 );
                    log_printf ( &logger, "Pressure: %lu Pa\r\n", u32_data );
                }
                break;
            }
            case XSENSMTI8_XDI_UTC_TIME:
            {
                if ( 12 == data_len )
                {
                    u16_data = ( ( uint16_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 7 ] << 8 ) |
                               ( ( uint16_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 8 ] << 0 );
                    log_printf ( &logger, "UTC: %u-%u-%u ", 
                                 ( uint16_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 10 ],
                                 ( uint16_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 9 ],
                                 u16_data );
                    log_printf ( &logger, "%.2u:%.2u:%.2u\r\n", 
                                 ( uint16_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 11 ],
                                 ( uint16_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 12 ],
                                 ( uint16_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 13 ] );
                }
                break;
            }
            default:
            {
                log_printf ( &logger, "DATA_ID: %.4X\r\n", data_id );
                log_printf ( &logger, "DATA_LEN: %u\r\n", ( uint16_t ) data_len );
                if ( data_len )
                {
                    log_printf ( &logger, "DATA:" );
                }
                for ( uint8_t cnt_data = 0; cnt_data < data_len; cnt_data++ )
                {
                    log_printf ( &logger, " %.2X", ( uint16_t ) xsensmti8.rsp_msg.data_buf[ msg_data_cnt + 3 + cnt_data ] );
                    if ( ( 15 == cnt_data % 16 ) && ( ( cnt_data + 1 ) < data_len ) )
                    {
                        log_printf ( &logger, "\r\n     " );
                    }
                }
                if ( data_len )
                {
                    log_printf ( &logger, "\r\n" );
                }
            }
        }
        Delay_5ms ( );
    }
}

// ------------------------------------------------------------------------ END
