/*!
 * @file main.c
 * @brief AirQuality9 Click example
 *
 * # Description
 * This example demonstrates the use of Air Quality 9 click board by reading and displaying
 * outputs such as eCO2, TVOC and AQI in compliance with worldwide IAQ standards.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger and performs the click default configuration.
 *
 * ## Application Task
 * Waits for the new data interrupt which triggers once per second, 
 * and then reads the validity status, TVOC, eCO2, and AQI-UBA values. 
 * All values are being displayed on the USB UART where you can track their changes.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "airquality9.h"

static airquality9_t airquality9;
static log_t logger;

/**
 * @brief Air Quality 9 display status validity function.
 * @details This function parses the status validity from status byte and displays it on the USB UART.
 * @param[in] status : Data status byte.
 * @return None.
 * @note None.
 */
void airquality9_display_status_validity ( uint8_t status );

/**
 * @brief Air Quality 9 display aqi uba function.
 * @details This function parses the Air Quality Index per UBA (AQI-UBA) value and displays it on the USB UART.
 * @param[in] aqi_uba : AQI-UBA value.
 * @return None.
 * @note None.
 */
void airquality9_display_aqi_uba ( uint8_t aqi_uba );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    airquality9_cfg_t airquality9_cfg;  /**< Click config object. */

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
    airquality9_cfg_setup( &airquality9_cfg );
    AIRQUALITY9_MAP_MIKROBUS( airquality9_cfg, MIKROBUS_1 );
    err_t init_flag  = airquality9_init( &airquality9, &airquality9_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AIRQUALITY9_ERROR == airquality9_default_cfg ( &airquality9 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    if ( airquality9_get_int_pin ( &airquality9 ) )
    {
        uint8_t status, aqi_uba;
        uint16_t tvoc, eco2;
        if ( AIRQUALITY9_OK == airquality9_read_status ( &airquality9, &status ) )
        {
            airquality9_display_status_validity ( status );
        }
        if ( AIRQUALITY9_OK == airquality9_read_tvoc ( &airquality9, &tvoc ) )
        {
            log_printf ( &logger, " TVOC: %u ppb\r\n", tvoc );
        }
        if ( AIRQUALITY9_OK == airquality9_read_eco2 ( &airquality9, &eco2 ) )
        {
            log_printf ( &logger, " ECO2: %u ppm\r\n", eco2 );
        }
        if ( AIRQUALITY9_OK == airquality9_read_aqi_uba ( &airquality9, &aqi_uba ) )
        {
            airquality9_display_aqi_uba ( aqi_uba );
        }
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

void airquality9_display_status_validity ( uint8_t status )
{
    switch ( status & AIRQUALITY_STATUS_VALID_FLAG_BITS )
    {
        case AIRQUALITY_STATUS_VALID_NORMAL_OP:
        {
            log_printf ( &logger, " Status: Normal operation\r\n" );
            break;
        }
        case AIRQUALITY_STATUS_VALID_WARM_UP:
        {
            log_printf ( &logger, " Status: Warm-Up phase\r\n" );
            break;
        }
        case AIRQUALITY_STATUS_VALID_INIT_START_UP:
        {
            log_printf ( &logger, " Status: Initial Start-Up phase\r\n" );
            break;
        }
        case AIRQUALITY_STATUS_VALID_INVALID:
        {
            log_printf ( &logger, " Status: Invalid output\r\n" );
            break;
        }
    }
}

void airquality9_display_aqi_uba ( uint8_t aqi_uba )
{
    switch ( aqi_uba )
    {
        case AIRQUALITY9_AQI_UBA_EXELLENT:
        {
            log_printf ( &logger, " AQI-UBA Rating: Exellent\r\n" );
            log_printf ( &logger, " Recommendation: Target\r\n" );
            log_printf ( &logger, " Exposure Limit: No limit\r\n\n" );
            break;
        }
        case AIRQUALITY9_AQI_UBA_GOOD:
        {
            log_printf ( &logger, " AQI-UBA Rating: Good\r\n" );
            log_printf ( &logger, " Recommendation: Sufficient ventilation\r\n" );
            log_printf ( &logger, " Exposure Limit: No limit\r\n\n" );
            break;
        }
        case AIRQUALITY9_AQI_UBA_MODERATE:
        {
            log_printf ( &logger, " AQI-UBA Rating: Moderate\r\n" );
            log_printf ( &logger, " Recommendation: Increased ventilation - Search for sources\r\n" );
            log_printf ( &logger, " Exposure Limit: <12 months\r\n\n" );
            break;
        }
        case AIRQUALITY9_AQI_UBA_POOR:
        {
            log_printf ( &logger, " AQI-UBA Rating: Poor\r\n" );
            log_printf ( &logger, " Recommendation: Intensified ventilation - Search for sources\r\n" );
            log_printf ( &logger, " Exposure Limit: <1 month\r\n\n" );
            break;
        }
        case AIRQUALITY9_AQI_UBA_UNHEALTHY:
        {
            log_printf ( &logger, " AQI-UBA Rating: Unhealthy\r\n" );
            log_printf ( &logger, " Recommendation: Use only if unavoidable - Intensified ventilation\r\n" );
            log_printf ( &logger, " Exposure Limit: No limit\r\n\n" );
            break;
        }
        default:
        {
            log_printf ( &logger, " AQI-UBA Rating: Unknown\r\n\n" );
            break;
        }
    }
}

// ------------------------------------------------------------------------ END
