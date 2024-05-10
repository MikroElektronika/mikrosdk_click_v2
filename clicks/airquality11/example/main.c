/*!
 * @file main.c
 * @brief Air Quality 11 Click example
 *
 * # Description
 * This example demonstrates the use of the Air Quality 11 Click board 
 * by reading and displaying the calculated Air Quality Index according to the UBA and ScioSense, 
 * and equivalent TVOC and CO2 concentration.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of I2C and SPI module and log UART.
 * After driver initialization, the app sets the default configuration.
 *
 * ## Application Task
 * The demo application displays the Air Quality Index of the UBA information,
 * concentration of the TVOC and CO2 and Air Quality Index according to ScioSense.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * ## Additional Function
 * - static void airquality11_display_aqi_uba ( void )
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "airquality11.h"

static airquality11_t airquality11;
static log_t logger;

/**
 * @brief Air Quality 11 display AQI-UBA function.
 * @details This function parses the Air Quality Index per UBA (AQI-UBA) value 
 * and displays it on the USB UART.
 * @param[in] aqi_uba : AQI-UBA value.
 * @return None.
 * @note None.
 */
void airquality11_display_aqi_uba ( uint8_t aqi_uba );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    airquality11_cfg_t airquality11_cfg;  /**< Click config object. */

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
    airquality11_cfg_setup( &airquality11_cfg );
    AIRQUALITY11_MAP_MIKROBUS( airquality11_cfg, MIKROBUS_1 );
    err_t init_flag = airquality11_init( &airquality11, &airquality11_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AIRQUALITY11_ERROR == airquality11_default_cfg ( &airquality11 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    log_printf( &logger, "---------------------------\r\n " );
    Delay_ms ( 100 );
}

void application_task ( void )
{
    uint8_t aqi_uba = 0;
    uint16_t aq_data = 0;

    if ( AIRQUALITY11_OK == airquality11_get_aqi_uba( &airquality11, &aqi_uba ) )
    {
        airquality11_display_aqi_uba( aqi_uba );
        Delay_ms ( 100 );
    }

    if ( AIRQUALITY11_OK == airquality11_get_tvoc( &airquality11, &aq_data ) )
    {
        log_printf( &logger, " TVOC: %u [ppb]\r\n", aq_data );
        Delay_ms ( 100 );
    }

    if ( AIRQUALITY11_OK == airquality11_get_co2( &airquality11, &aq_data ) )
    {
        log_printf( &logger, " ECO2: %u [ppm]\r\n", aq_data );
        Delay_ms ( 100 );
    }

    if ( AIRQUALITY11_OK == airquality11_get_aqi_s( &airquality11, &aq_data ) )
    {
        log_printf( &logger, " AQIS: %u [idx]\r\n", aq_data );
        Delay_ms ( 100 );
    }
    
    log_printf( &logger, "---------------------------\r\n " );
    Delay_ms ( 1000 );
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

void airquality11_display_aqi_uba ( uint8_t aqi_uba )
{
    switch ( aqi_uba )
    {
        case AIRQUALITY11_AQI_UBA_EXELLENT:
        {
            log_printf( &logger, " AQI-UBA Rating: Exellent\r\n" );
            log_printf( &logger, " Hygienic Rating: No objections\r\n" );
            log_printf( &logger, " Recommendation: Target\r\n" );
            log_printf( &logger, " Exposure Limit: No limit\r\n" );
            break;
        }
        case AIRQUALITY11_AQI_UBA_GOOD:
        {
            log_printf( &logger, " AQI-UBA Rating: Good\r\n" );
            log_printf( &logger, " Hygienic Rating: No relevant objections\r\n" );
            log_printf( &logger, " Recommendation: Sufficient ventilation\r\n" );
            log_printf( &logger, " Exposure Limit: No limit\r\n" );
            break;
        }
        case AIRQUALITY11_AQI_UBA_MODERATE:
        {
            log_printf( &logger, " AQI-UBA Rating: Moderate\r\n" );
            log_printf( &logger, " Hygienic Rating: Some objections\r\n" );
            log_printf( &logger, " Recommendation: Increased ventilation - Search for sources\r\n" );
            log_printf( &logger, " Exposure Limit: < 12 months\r\n" );
            break;
        }
        case AIRQUALITY11_AQI_UBA_POOR:
        {
            log_printf( &logger, " AQI-UBA Rating: Poor\r\n" );
            log_printf( &logger, " Hygienic Rating: Major objections\r\n" );
            log_printf( &logger, " Recommendation: Intensified ventilation - Search for sources\r\n" );
            log_printf( &logger, " Exposure Limit: < 1 month\r\n" );
            break;
        }
        case AIRQUALITY11_AQI_UBA_UNHEALTHY:
        {
            log_printf( &logger, " AQI-UBA Rating: Unhealthy\r\n" );
            log_printf( &logger, " Hygienic Rating: Situation not acceptable\r\n" );
            log_printf( &logger, " Recommendation: Use only if unavoidable - Intensified ventilation recommended \r\n" );
            log_printf( &logger, " Exposure Limit: hours\r\n" );
            break;
        }
        default:
        {
            log_printf( &logger, " AQI-UBA Rating: Unknown\r\n" );
            break;
        }
    }
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n " );
}

// ------------------------------------------------------------------------ END
