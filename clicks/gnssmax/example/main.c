/*!
 * @file main.c
 * @brief GNSSMAX Click Example.
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
 * - static void gnssmax_clear_app_buf ( void )
 * - static err_t gnssmax_process ( void )
 * - static err_t gnssmax_cmd_parser ( char *cmd )
 * - static err_t gnssmax_element_parser ( char *cmd, uint8_t element, char *element_data )
 *
 * @note
 * For the device to connect it can take it from 1 to 10 minutes.
 * Time to connect is depending on weather.
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "gnssmax.h"

#define PROCESS_BUFFER_SIZE                     700
#define DATA_BUFFER_SIZE                        30

#define RSP_GNGGA                               "GNGGA"
#define RSP_START                               '$'
#define RSP_SEPARATOR                           ','

#define RSP_GNGGA_LATITUDE_ELEMENT              2
#define RSP_GNGGA_LONGITUDE_ELEMENT             4
#define RSP_GNGGA_ALTITUDE_ELEMENT              9

static gnssmax_t gnssmax;
static log_t logger;

static char app_buf[ PROCESS_BUFFER_SIZE ]      = { 0 };
static int32_t app_buf_len                      = 0;
static int32_t app_buf_cnt                      = 0;

static char latitude_data[ DATA_BUFFER_SIZE ]   = { 0 };
static char longitude_data[ DATA_BUFFER_SIZE ]  = { 0 };
static char altitude_data[ DATA_BUFFER_SIZE ]   = { 0 };

err_t last_error_flag;

/**
 * @brief GNSSMAX clearing application buffer.
 * @details This function clears memory of application buffer and reset it's length and counter.
 */
static void gnssmax_clear_app_buf ( void );

/**
 * @brief GNSSMAX data reading function.
 * @details This function reads data from device and concats data to application buffer.
 *
 * @return @li @c GNSSMAX_OK - Read some data.
 *         @li @c GNSSMAX_ERROR - Nothing is read.
 *         @li @c GNSSMAX_ERROR_NO_DATA - Application buffer overflow.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t gnssmax_process ( void );

/**
 * @brief GNSSMAX command data parser.
 * @details This function searches @b app_buf for @b cmd and logs data of that command.
 *
 * @param[in] cmd : Command to parese.
 *
 * @return @li @c GNSSMAX_OK - Parsed data succes.
 *         @li @c GNSSMAX_ERROR - No @b cmd in application buffer.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t gnssmax_cmd_parser ( char *cmd );

/**
 * @brief GNSSMAX element of command data parser.
 * @details This function searches @b app_buf for @b cmd and it's
 *          @b element and copies data to @b element_data buffer.
 *
 * @return @li @c GNSSMAX_OK - Read some data.
 *         @li @c GNSSMAX_ERROR - No @b cmd in application buffer.
 *         @li @c GNSSMAX_ERROR_NO_DATA - No data for @b element in @b cmd.
 *         @li @c GNSSMAX_ERROR_OVERFLOW - Data buffer overflow.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t gnssmax_element_parser ( char *cmd, uint8_t element, char *element_data );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gnssmax_cfg_t gnssmax_cfg;  /**< Click config object. */

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
    Delay_ms( 500 );

    // Click initialization.
    gnssmax_cfg_setup( &gnssmax_cfg );
    GNSSMAX_MAP_MIKROBUS( gnssmax_cfg, MIKROBUS_1 );
    err_t init_flag  = gnssmax_init( &gnssmax, &gnssmax_cfg );
    if ( init_flag == UART_ERROR )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    gnssmax_default_cfg( &gnssmax );

    last_error_flag = GNSSMAX_OK;
    log_info( &logger, " Application Task " );
    Delay_ms( 500 );
}

void application_task ( void )
{
    gnssmax_process();

    err_t error_flag = gnssmax_element_parser( RSP_GNGGA, RSP_GNGGA_LATITUDE_ELEMENT,
                                             latitude_data );

    error_flag |= gnssmax_element_parser(  RSP_GNGGA, RSP_GNGGA_LONGITUDE_ELEMENT,
                                         longitude_data );

    error_flag |= gnssmax_element_parser(  RSP_GNGGA, RSP_GNGGA_ALTITUDE_ELEMENT,
                                         altitude_data );


    if ( error_flag == GNSSMAX_OK )
    {
        if ( last_error_flag != GNSSMAX_OK )
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
    else if ( error_flag < GNSSMAX_ERROR )
    {
        if ( last_error_flag == GNSSMAX_OK )
        {
            log_printf( &logger, "Waiting for data " );
        }
        log_printf( &logger, "." );
    }

    if ( error_flag != GNSSMAX_ERROR )
    {
        last_error_flag = error_flag;
        gnssmax_clear_app_buf(  );
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

static void gnssmax_clear_app_buf ( void )
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
    app_buf_cnt = 0;
}

static err_t gnssmax_process ( void )
{
    int32_t rx_size;
    char rx_buff[ PROCESS_BUFFER_SIZE ] = { 0 };

    rx_size = gnssmax_generic_read( &gnssmax, rx_buff, PROCESS_BUFFER_SIZE );

    if ( rx_size > 0 )
    {
        int32_t buf_cnt = 0;

        if ( ( app_buf_len + rx_size ) > PROCESS_BUFFER_SIZE )
        {
            gnssmax_clear_app_buf(  );
            return GNSSMAX_ERROR_NO_DATA;
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
        return GNSSMAX_OK;
    }
    return GNSSMAX_ERROR;
}

static err_t gnssmax_cmd_parser ( char *cmd )
{
    err_t ret_flag = GNSSMAX_OK;

    if ( strstr( app_buf, cmd ) != GNSSMAX_OK )
    {
        char * __generic_ptr gngga_ptr;

        gngga_ptr = strstr( app_buf, cmd );

        while ( strchr( gngga_ptr, RSP_START ) == GNSSMAX_OK )
        {
            gnssmax_process();
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
        ret_flag = GNSSMAX_ERROR;
    }

    return ret_flag;
}

static err_t gnssmax_element_parser ( char *cmd, uint8_t element, char *element_data )
{
    err_t ret_flag = 0;


    if ( strstr( app_buf, cmd ) != 0 )
    {
        uint8_t element_cnt = 0;
        char data_buf[ DATA_BUFFER_SIZE ] = { 0 };
        uint8_t data_cnt = 0;
        char * __generic_ptr gngga_ptr;

        gngga_ptr = strstr( app_buf, cmd );

        while ( strchr( gngga_ptr, RSP_START ) == GNSSMAX_OK )
        {
            gnssmax_process();
        }

        for ( ; ; )
        {
            if ( ( *gngga_ptr == RSP_START ) )
            {
                ret_flag = GNSSMAX_ERROR_NO_DATA;
                break;
            }

            if ( *gngga_ptr == RSP_SEPARATOR )
            {
                if (element_cnt == element)
                {
                    if ( data_cnt == 0 )
                    {
                        ret_flag = GNSSMAX_ERROR_NO_DATA;
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
                    ret_flag = GNSSMAX_ERROR_OVERFLOW;
                    break;
                }
            }

            gngga_ptr++;
        }
    }
    else
    {
        ret_flag = GNSSMAX_ERROR;
    }

    return ret_flag;
}

// ------------------------------------------------------------------------ END
