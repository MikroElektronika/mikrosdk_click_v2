/*!
 * @file main.c
 * @brief Speed Radar Click Example.
 *
 * # Description
 * This example demonstrates the use of Speed Radar Click board by processing
 * the incoming data and displaying them on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * The demo application sends a command that returns and displays the speed [km/h] 
 * and magnitude [dB] of the dominant movement for the forward and backward planes of the spectrum,
 * measured frontal to the sensor.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * ## Additional Function
 * - static void speedradar_clear_app_buf ( void )
 * - static err_t speedradar_process ( speedradar_t *ctx )
 * - static void speedradar_adv_det_display ( void )
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "speedradar.h"

// Application buffer size
#define PROCESS_BUFFER_SIZE        200
#define PROCESS_C00_RSP_LEN        14

// Speed measurement macros
#define NFFT_WIDTH_DEFAULT         256.0
#define FREQUENCY_DEFAULT          44.7
#define COS_ANGLE_OBJECT_VAL       1.0

static speedradar_t speedradar;
static log_t logger;

static uint8_t app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief Speed Radar clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void speedradar_clear_app_buf ( void );

/**
 * @brief Speed Radar data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #speedradar_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t speedradar_process ( speedradar_t *ctx );

/**
 * @brief Speed Radar advanced detection function.
 * @details This function processes and displays the response data of the detection string command. 
 * @note The valid speed of the object is when it is measured frontal to the sensor.
 * An angle between the object and the sensor reduces the dominant movement speed.
 */
static void speedradar_adv_det_display ( void );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    speedradar_cfg_t speedradar_cfg;  /**< Click config object. */

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
    speedradar_cfg_setup( &speedradar_cfg );
    SPEEDRADAR_MAP_MIKROBUS( speedradar_cfg, MIKROBUS_1 );
    if ( UART_ERROR == speedradar_init( &speedradar, &speedradar_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    if ( SPEEDRADAR_ERROR == speedradar_default_cfg ( &speedradar ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    speedradar_process( &speedradar );
    speedradar_clear_app_buf( );
    Delay_ms ( 100 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ---------------------- \r\n" );
    Delay_ms ( 100 );
}

void application_task ( void ) 
{
    speedradar_send_command( &speedradar, SPEEDRADAR_CMD_GET_DETECTION_STR );
    Delay_ms ( 50 );
    speedradar_process( &speedradar );
    if ( app_buf_len >= PROCESS_C00_RSP_LEN  )
    {
        speedradar_adv_det_display( );
        speedradar_clear_app_buf( );
        Delay_ms ( 100 );
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

static void speedradar_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static err_t speedradar_process ( speedradar_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t rx_size = 0;
    rx_size = speedradar_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
    if ( rx_size > 0 ) 
    {
        int32_t buf_cnt = app_buf_len;
        if ( ( ( app_buf_len + rx_size ) > PROCESS_BUFFER_SIZE ) && ( app_buf_len > 0 ) ) 
        {
            buf_cnt = PROCESS_BUFFER_SIZE - ( ( app_buf_len + rx_size ) - PROCESS_BUFFER_SIZE );
            memmove ( app_buf, &app_buf[ PROCESS_BUFFER_SIZE - buf_cnt ], buf_cnt );
        }
        for ( int32_t rx_cnt = 0; rx_cnt < rx_size; rx_cnt++ ) 
        {
            if ( rx_buf[ rx_cnt ] ) 
            {
                app_buf[ buf_cnt++ ] = rx_buf[ rx_cnt ];
                if ( app_buf_len < PROCESS_BUFFER_SIZE )
                {
                    app_buf_len++;
                }
            }
        }
        return SPEEDRADAR_OK;
    }
    return SPEEDRADAR_ERROR;
}

static void speedradar_adv_det_display ( void )
{
    if ( strncmp( SPEEDRADAR_ERR_MSG, app_buf, 3 ) )    
    {
        uint8_t detection = 0, speed = 0, magnitude = 0;
        float speed_km_h = 0;
        detection = ( app_buf[ 0 ] - SPEEDRADAR_ASCII_CHAR_0 ) * SPEEDRADAR_MLP_HUNDREDS +
                    ( app_buf[ 1 ] - SPEEDRADAR_ASCII_CHAR_0 ) * SPEEDRADAR_MLP_TENS  +
                    ( app_buf[ 2 ] - SPEEDRADAR_ASCII_CHAR_0 );
        speed     = ( app_buf[ 4 ] - SPEEDRADAR_ASCII_CHAR_0 ) * SPEEDRADAR_MLP_HUNDREDS +
                    ( app_buf[ 5 ] - SPEEDRADAR_ASCII_CHAR_0 ) * SPEEDRADAR_MLP_TENS  +
                    ( app_buf[ 6 ] - SPEEDRADAR_ASCII_CHAR_0 );
        magnitude = ( app_buf[ 8 ] - SPEEDRADAR_ASCII_CHAR_0 ) * SPEEDRADAR_MLP_HUNDREDS +
                    ( app_buf[ 9 ] - SPEEDRADAR_ASCII_CHAR_0 ) * SPEEDRADAR_MLP_TENS  +
                    ( app_buf[ 10 ] - SPEEDRADAR_ASCII_CHAR_0 );
                        
        if ( SPEEDRADAR_R00_DET_VALID & detection )
        {
            speed_km_h = ( float ) speed;
            speed_km_h *= SPEEDRADAR_SAMPLING_RATE_5120_HZ;
            speed_km_h /= NFFT_WIDTH_DEFAULT;
            speed_km_h /= FREQUENCY_DEFAULT;
            speed_km_h /= COS_ANGLE_OBJECT_VAL;
            if ( SPEEDRADAR_R00_DIR_FORWARD & detection )
            {
                log_printf( &logger, " Speed: +%.2f [km/h]\r\n", speed_km_h );
                log_printf( &logger, " Magnitude: +%d [dB] \r\n", ( uint16_t ) magnitude );             
            }
            else
            {
                log_printf( &logger, " Speed: -%.2f [km/h]\r\n", speed_km_h );
                log_printf( &logger, " Magnitude: -%d [dB] \r\n", ( uint16_t ) magnitude );
                
            }
        }
        else
        {
            log_printf( &logger, " No target found!\r\n" );
        }
        log_printf( &logger, " ---------------------- \r\n" );
    }
    else
    {
        speedradar_clear_app_buf( );
    }
}

// ------------------------------------------------------------------------ END
