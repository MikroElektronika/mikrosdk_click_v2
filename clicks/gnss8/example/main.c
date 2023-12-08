/*!
 * @file main.c
 * @brief GNSS 8 Click Example.
 *
 * # Description
 * This example showcases device abillity to read data outputed
 * from device and show it's coordinates and altitude when connected.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes host communication modules, additioaln GPIO's used
 * for control of device and resets device.
 *
 * ## Application Task
 * Reads data from device and wait's untill device is connected.
 * While not connected it will log '.'. When conneceted and received
 * data for latitude, longitude, and altitude it will log that data
 * parsed from "GNGGA" command.
 *
 * ## Additional Function
 * - static void gnss8_clear_app_buf ( void )
 * - static err_t gnss8_process ( void )
 * - static err_t gnss8_cmd_parser ( char *cmd )
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "gnss8.h"

#define PROCESS_BUFFER_SIZE                     700
#define DATA_BUFFER_SIZE                        30

#define RSP_GNGGA                               "GNGGA"
#define RSP_START                               '$'
#define RSP_SEPARATOR                           ','

#define RSP_GNGGA_LATITUDE_ELEMENT              2
#define RSP_GNGGA_LONGITUDE_ELEMENT             4
#define RSP_GNGGA_ALTITUDE_ELEMENT              9

static gnss8_t gnss8;
static log_t logger;

static char app_buf[ PROCESS_BUFFER_SIZE ]      = { 0 };
static int32_t app_buf_len                      = 0;
static int32_t app_buf_cnt                      = 0;

static char latitude_data[ DATA_BUFFER_SIZE ]   = { 0 };
static char longitude_data[ DATA_BUFFER_SIZE ]  = { 0 };
static char altitude_data[ DATA_BUFFER_SIZE ]   = { 0 };

err_t last_error_flag;

/**
 * @brief GNSS8 clearing application buffer.
 * @details This function clears memory of application buffer and reset it's length and counter.
 */
static void gnss8_clear_app_buf ( void );

/**
 * @brief GNSS8 data reading function.
 * @details This function reads data from device and concats data to application buffer.
 *
 * @return @li @c GNSS8_OK - Read some data.
 *         @li @c GNSS8_ERROR - Nothing is read.
 *         @li @c GNSS8_ERROR_NO_DATA - Application buffer overflow.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t gnss8_process ( void );

/**
 * @brief GNSS8 command data parser.
 * @details This function searches @b app_buf for @b cmd and logs data of that command.
 *
 * @param[in] cmd : Command to parese.
 *
 * @return @li @c GNSS8_OK - Parsed data succes.
 *         @li @c GNSS8_ERROR - No @b cmd in application buffer.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t gnss8_cmd_parser ( char *cmd );

/**
 * @brief GNSS8 element of command data parser.
 * @details This function searches @b app_buf for @b cmd and it's
 *          @b element and copies data to @b element_data buffer.
 *
 * @return @li @c GNSS8_OK - Read some data.
 *         @li @c GNSS8_ERROR - No @b cmd in application buffer.
 *         @li @c GNSS8_ERROR_NO_DATA - No data for @b element in @b cmd.
 *         @li @c GNSS8_ERROR_OVERFLOW - Data buffer overflow.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t gnss8_element_parser ( char *cmd, uint8_t element, char *element_data );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gnss8_cfg_t gnss8_cfg;  /**< Click config object. */

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
    gnss8_cfg_setup( &gnss8_cfg );
    GNSS8_MAP_MIKROBUS( gnss8_cfg, MIKROBUS_1 );
    err_t init_flag  = gnss8_init( &gnss8, &gnss8_cfg );
    if ( UART_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    gnss8_clear_app_buf(  );
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    gnss8_process();

    err_t error_flag = gnss8_element_parser( RSP_GNGGA, RSP_GNGGA_LATITUDE_ELEMENT,
                                             latitude_data );

    error_flag |= gnss8_element_parser(  RSP_GNGGA, RSP_GNGGA_LONGITUDE_ELEMENT,
                                         longitude_data );

    error_flag |= gnss8_element_parser(  RSP_GNGGA, RSP_GNGGA_ALTITUDE_ELEMENT,
                                         altitude_data );


    if ( error_flag == GNSS8_OK )
    {
        if ( last_error_flag != GNSS8_OK )
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
    else if ( error_flag < GNSS8_ERROR )
    {
        if ( last_error_flag == GNSS8_OK )
        {
            log_printf( &logger, "Waiting for data " );
        }
        log_printf( &logger, "." );
    }

    if ( error_flag != GNSS8_ERROR )
    {
        last_error_flag = error_flag;
        gnss8_clear_app_buf(  );
    }
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

static void gnss8_clear_app_buf ( void )
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
    app_buf_cnt = 0;
}

static err_t gnss8_process ( void )
{
    int32_t rx_size;
    char rx_buff[ PROCESS_BUFFER_SIZE ] = { 0 };

    rx_size = gnss8_generic_read( &gnss8, rx_buff, PROCESS_BUFFER_SIZE );

    if ( rx_size > 0 )
    {
        int32_t buf_cnt = 0;

        if ( app_buf_len + rx_size >= PROCESS_BUFFER_SIZE )
        {
            gnss8_clear_app_buf(  );
            return GNSS8_ERROR_NO_DATA;
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
                buf_cnt--;
            }
        }
        return GNSS8_OK;
    }
    return GNSS8_ERROR;
}

static err_t gnss8_cmd_parser ( char *cmd )
{
    err_t ret_flag = GNSS8_OK;

    if ( strstr( app_buf, cmd ) != GNSS8_OK )
    {
        char * __generic_ptr gngga_ptr;

        gngga_ptr = strstr( app_buf, cmd );

        while ( strchr( gngga_ptr, RSP_START ) == GNSS8_OK )
        {
            gnss8_process();
        }

        for ( ; ; )
        {
            log_printf( &logger, "%c", *gngga_ptr );
            gngga_ptr++;

            if ( ( *gngga_ptr == RSP_START ) )
            {
                break;
            }
        }
    }
    else
    {
        ret_flag = GNSS8_ERROR;
    }

    return ret_flag;
}

static err_t gnss8_element_parser ( char *cmd, uint8_t element, char *element_data )
{
    err_t ret_flag = 0;


    if ( strstr( app_buf, cmd ) != 0 )
    {
        uint8_t element_cnt = 0;
        char data_buf[ DATA_BUFFER_SIZE ] = { 0 };
        uint8_t data_cnt = 0;
        char * __generic_ptr gngga_ptr;

        gngga_ptr = strstr( app_buf, cmd );

        while ( strchr( gngga_ptr, RSP_START ) == GNSS8_OK )
        {
            gnss8_process();
        }

        for ( ; ; )
        {
            if ( ( *gngga_ptr == RSP_START ) )
            {
                ret_flag = GNSS8_ERROR_NO_DATA;
                break;
            }

            if ( *gngga_ptr == RSP_SEPARATOR )
            {
                if (element_cnt == element)
                {
                    if ( data_cnt == 0 )
                    {
                        ret_flag = GNSS8_ERROR_NO_DATA;
                    }
                    strcpy( element_data, data_buf );
                    break;
                }

                element_cnt++;
            }

            if ( ( element == element_cnt ) && ( *gngga_ptr != RSP_SEPARATOR ) )
            {
                data_buf[ data_cnt ] = *gngga_ptr;
                data_cnt++;

                if ( data_cnt >= DATA_BUFFER_SIZE )
                {
                    ret_flag = GNSS8_ERROR_OVERFLOW;
                    break;
                }
            }

            gngga_ptr++;
        }
    }
    else
    {
        ret_flag = GNSS8_ERROR;
    }

    return ret_flag;
}

// ------------------------------------------------------------------------ END
