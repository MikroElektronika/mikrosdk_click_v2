/*!
 * @file main.c
 * @brief IRNSS Click Example.
 *
 * # Description
 * This example application reads data, checks for specific command. If command 
 * is found checks for data validation and if it's found logs that data to UART terminal.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes log and device communication modules.
 *
 * ## Application Task
 * Collects data and waits for Latitude, longitude, and altitude data from the device. 
 * When it's received logs data, and while waiting it will log '.' until data is received.
 *
 * ## Additional Function
 * - static void irnss_clear_app_buf ( void )           - Function clears memory of app_buf.
 * - static err_t irnss_process ( void )                - The general process of collecting 
 *                                                        presponce that a module sends.
 * - static err_t irnss_cmd_parser ( char *cmd )        - This function searches @b app_buf 
 *                                                        for @b cmd and logs data of that command.
 * - static err_t irnss_element_parser 
 * ( char *cmd, uint8_t element, char *element_data )   - This function searches @b app_buf 
 *                                                        for @b cmd and it's @b element and 
 *                                                        copies data to @b element_data buffer.
 *
 * *note:* 
 * - For the device to connect it can take it from 1 to 8 minutes to get useful data from satellites.
 *   Time to connect is depending on weather, do you have an external antenna, etc.
 * 
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "irnss.h"
#include "string.h"

#define PROCESS_BUFFER_SIZE                 700

#define RSP_GNGGA                           "GNGGA"

#define RSP_GNGGA_LATITUDE_ELEMENT          2
#define RSP_GNGGA_LONGITUDE_ELEMENT         4
#define RSP_GNGGA_ALTITUDE_ELEMENT          9

static irnss_t irnss;
static log_t logger;

static char app_buf[ PROCESS_BUFFER_SIZE ]  = { 0 };
static int32_t app_buf_len                  = 0;
static int32_t app_buf_cnt                  = 0;

static char latitude_data[ 30 ]             = { 0 };
static char longitude_data[ 30 ]            = { 0 };
static char altitude_data[ 30 ]             = { 0 };

err_t last_error_flag;

/**
 * @brief IRNSS clearing application buffer.
 * @details This function clears memory of application buffer and reset it's length and counter.
 * @note None.
 */
static void irnss_clear_app_buf ( void );

/**
 * @brief IRNSS data reading function.
 * @details This function reads data from device and concats data to application buffer.
 *
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 *         @li @c -2 - Application buffer overflow.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t irnss_process ( void );

/**
 * @brief IRNSS command data parser.
 * @details This function searches @b app_buf for @b cmd and logs data of that command.
 *
 * @param[in] cmd : Command to parese.
 * 
 * @return @li @c  0 - Parsed data succes.
 *         @li @c -1 - No @b cmd in application buffer.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t irnss_cmd_parser ( char *cmd );

/**
 * @brief IRNSS element of command data parser.
 * @details This function searches @b app_buf for @b cmd and it's 
 *          @b element and copies data to @b element_data buffer.
 *
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - No @b cmd in application buffer.
 *         @li @c -2 - No data for @b element in @b cmd.
 *         @li @c -3 - Data buffer overflow.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t irnss_element_parser ( char *cmd, uint8_t element, char *element_data );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    irnss_cfg_t irnss_cfg;  /**< Click config object. */

    // Logger initialization.
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );
    Delay_ms( 500 );

    // Click initialization.
    irnss_cfg_setup( &irnss_cfg );
    IRNSS_MAP_MIKROBUS( irnss_cfg, MIKROBUS_1 );
    err_t init_flag  = irnss_init( &irnss, &irnss_cfg );
    if ( init_flag == UART_ERROR )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    app_buf_len = 0;
    app_buf_cnt = 0;
    last_error_flag = 0;
    log_info( &logger, " Application Task " );
    Delay_ms( 500 );
    irnss_process();
    irnss_clear_app_buf(  );
}

void application_task ( void ) 
{
    irnss_process();

    err_t error_flag = irnss_element_parser( RSP_GNGGA, RSP_GNGGA_LATITUDE_ELEMENT, 
                                             latitude_data );

    error_flag |= irnss_element_parser(  RSP_GNGGA, RSP_GNGGA_LONGITUDE_ELEMENT, 
                                         longitude_data );

    error_flag |= irnss_element_parser(  RSP_GNGGA, RSP_GNGGA_ALTITUDE_ELEMENT, 
                                         altitude_data );

    if ( error_flag == 0 )
    {
        if ( last_error_flag != 0)
        {
            log_printf( &logger, "\r\n" );
        }
        log_printf( &logger, ">Latitude:\r\n - deg: %.2s \r\n - min: %s\r\n", 
                    latitude_data, &latitude_data[ 2 ] );
        
        log_printf( &logger, ">Longitude:\r\n - deg: %.3s \r\n - min: %s\r\n", 
                    longitude_data, &longitude_data[ 3 ] );
        
        log_printf( &logger, ">Altitude:\r\n - %sm\r\n", 
                    altitude_data );
        
        log_printf( &logger, "----------------------------------------\r\n" );
    }
    else if ( error_flag < -1 )
    {
        if ( last_error_flag == 0 )
        {
            log_printf( &logger, "Waiting for data" );
        }
        log_printf( &logger, "." );
    }

    if ( error_flag != -1 )
    {
        last_error_flag = error_flag;
        irnss_clear_app_buf(  );
    }
}

void main ( void ) 
{
    application_init( );

    for ( ; ; ) 
    {
        application_task( );
    }
}

static void irnss_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
    app_buf_cnt = 0;
}

static err_t irnss_process ( void ) 
{
    int32_t rx_size;
    char rx_buff[ PROCESS_BUFFER_SIZE ] = { 0 };

    rx_size = irnss_generic_read( &irnss, rx_buff, PROCESS_BUFFER_SIZE );

    if ( rx_size > 0 )
    {
        int32_t buf_cnt = 0;

        if ( app_buf_len + rx_size >= PROCESS_BUFFER_SIZE )
        {
            irnss_clear_app_buf(  );
            return -2;
        }
        else
        {
            buf_cnt = app_buf_len;
            app_buf_len += rx_size;
        }

        for ( int32_t rx_cnt = 0; rx_cnt < rx_size; rx_cnt++ )
        {
            if ( rx_buff[ rx_cnt ] != 0 )
            {
                app_buf[ ( buf_cnt + rx_cnt ) ] = rx_buff[ rx_cnt ];
            }
            else
            {
                app_buf_len--;
            }
        }
        return 0;
    }
    return -1;
}

static err_t irnss_cmd_parser ( char *cmd )
{
    err_t ret_flag = 0;

    if ( strstr( app_buf, cmd ) != 0 )
    {
        char * __generic gngga_ptr;

        gngga_ptr = strstr( app_buf, cmd );

        while (strchr( gngga_ptr, '$' ) == 0)
        {
            irnss_process();
        }

        for ( ; ; )
        {
            log_printf( &logger, "%c", *gngga_ptr );
            gngga_ptr++;

            if ( ( *gngga_ptr == '$' ) )
            {
                break;
            }
        }
    }
    else
    {
        ret_flag = -1;
    }

    return ret_flag;
}

static err_t irnss_element_parser ( char *cmd, uint8_t element, char *element_data )
{
    err_t ret_flag = 0;

    if ( strstr( app_buf, cmd ) != 0 )
    {
        uint8_t element_cnt = 0;
        char data_buf[ 30 ] = { 0 };
        uint8_t data_cnt = 0;
        char * __generic gngga_ptr;

        gngga_ptr = strstr( app_buf, cmd );

        while (strchr( gngga_ptr, '$' ) == 0)
        {
            irnss_process();
        }

        for ( ; ; )
        {
            if ( ( *gngga_ptr == '$' ) )
            {
                ret_flag = -2;
                break;
            }

            if ( *gngga_ptr == ',' )
            {
                if (element_cnt == element)
                {
                    if ( data_cnt == 0 )
                    {
                        ret_flag = -2;
                    }
                    strcpy( element_data, data_buf );
                    break;
                }

                element_cnt++;
            }

            if ( ( element == element_cnt ) && ( *gngga_ptr != ',' ) )
            {
                data_buf[ data_cnt ] = *gngga_ptr;
                data_cnt++;

                if ( data_cnt >= 30 )
                {
                    ret_flag = -3;
                    break;
                }
            }

            gngga_ptr++;
        }
    }
    else
    {
        ret_flag = -1;
    }

    return ret_flag;
}

// ------------------------------------------------------------------------ END
