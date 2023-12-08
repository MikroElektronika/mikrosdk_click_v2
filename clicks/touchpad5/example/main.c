/*!
 * @file main.c
 * @brief TouchPad5 Click example
 *
 * # Description
 * This example demonstrates the use of Touchpad 5 click board by utilizing the touchpad XY
 * and snap functionalities.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and USB UART logging and displays the device version information
 * such as product number, project number, major/minor release number, hardware ID, hardware
 * revision and bootloader status.
 *
 * ## Application Task
 * Task busy waits for the touchpad controller ready bit using polling operation. When the
 * communication window is available, the snap functionality is being checked, as well as 
 * XY touchpad data. Based on the user's touch sensibility and duration, one of the two 
 * features is being determined and logged over UART terminal. Snap (click) corresponds to
 * the shorter and lighter 'click' gesture, while the touch is detected as longer and 
 * stronger 'swipe' gesture.
 * 
 * @note This example relies on the IQS5xx-A000 firmware of the touch-pad controller.
 *
 * @author Stefan Popovic
 *
 */

#include "board.h"
#include "log.h"
#include "touchpad5.h"

// Snap buffer size
#define SNAP_BUFFER_SIZE                     ( 8 )

// Number of read channels for snap status
#define SNAP_NUMBER_OF_CHANNELS              ( 8 )

// Snap detection condition
#define SNAP_MAX_NO_CONSECUTIVE_SAMPLES      ( 3 )

// Touchpad strength threshold for XY touch detection
#define TOUCH_STRENGTH_THRESHOLD             ( 30 )

static touchpad5_t touchpad5;
static log_t logger;
static touchpad5_touch_t touch_data;
static touchpad5_ver_info_t ver_info;

// Bootloader status ( 0xA5 - present, 0xEE - not present )
static uint8_t bl_status = 0;

// Snap (click) support buffer and variables
static uint16_t snap_buffer[ SNAP_BUFFER_SIZE ] = { 0 }; 
static uint16_t snap_reference = 0;
static uint8_t snap_idx = 0;
static uint8_t tmp_count = 0;
static uint8_t snap_calc_no_samples = 0;
static uint16_t tmp_reference = 0;
static uint8_t snap_max_no_samples = SNAP_MAX_NO_CONSECUTIVE_SAMPLES;
static uint16_t snap_reg_data[ 2 * SNAP_NUMBER_OF_CHANNELS ] = { 0 };

/**
 * @brief TouchPad 5 snap sample getter.
 * @details This function gets the snap sample value as the averaged value of the predefined number of channels. 
 * @param[in] ctx : Click context object.
 * See #touchpad5_t object definition for detailed explanation.
 * @param[out] snap_data : Pointer to the memory location of the buffer where data is stored.
 * @return true  - Success,
 *         false - Error.
 *
 * @note Snap functionality must be enabled in control settings byte second byte.
 */
bool touchpad5_get_snap_sample( touchpad5_t *ctx, uint16_t *snap_data );

/**
 * @brief TouchPad 5 snap detection function.
 * @details This function checks for snap criteria defined by snap reference and predefined 
 * number of consecutive samples deviating from said reference.
 * @param[in] ctx : Click context object.
 * See #touchpad5_t object definition for detailed explanation.
 * @param[out] snap_buffer : Snap buffer with snap status data .
 * @param[in] snap_buffer_size : Buffer size of the 16-bit snap data.
 * @param[out] snap_reference : Pointer to the reference data calculated inside within each iteration.
 * @return true -  Snap detected,
 *         false - Snap not detected.
 *
 * @note Snap functionality must be enabled in control settings byte second byte.
 */
bool touchpad5_detect_snap( touchpad5_t *ctx, uint16_t *snap_buffer, uint8_t snap_buffer_size, uint16_t *snap_reference );

void application_init ( void ) 
{
    log_cfg_t log_cfg;                  /**< Logger config object. */
    touchpad5_cfg_t touchpad5_cfg;      /**< Click config object. */

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
    touchpad5_cfg_setup( &touchpad5_cfg );
    TOUCHPAD5_MAP_MIKROBUS( touchpad5_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == touchpad5_init( &touchpad5, &touchpad5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    Delay_100ms();
    
    if ( TOUCHPAD5_ERROR == touchpad5_default_cfg ( &touchpad5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    Delay_1sec( );
    
    if ( TOUCHPAD5_ERROR == touchpad5_check_version( &touchpad5, &ver_info ) )
    {
        log_error( &logger, " Cannot read version.\r\n " );
        for ( ; ; );
    }
    
    Delay_100ms();
    
    if ( TOUCHPAD5_ERROR == touchpad5_check_bl_status( &touchpad5, &bl_status ) )
    {
        log_error( &logger, " Cannot read bootloader status.\r\n " );
        for ( ; ; );
    }
    
    Delay_100ms();
    
    if ( ver_info.product_num != TOUCHPAD5_IQS550_PRODUCT_NUMBER ) 
    {
        log_error( &logger, " Incorrect product number.\r\n " );
        for ( ; ; );
    }
    
    log_printf( &logger, "----------------------------------------------------------------\r\n" );
    log_printf( &logger, " Product number %u \r\n",    ( uint32_t ) ver_info.product_num );
    log_printf( &logger, " Project number %u \r\n",    ( uint32_t ) ver_info.project_num );
    log_printf( &logger, " Version %.1f \r\n", ver_info.version );
    log_printf( &logger, " Hardware ID %x \r\n",       ( uint32_t ) ver_info.hw_id );
    log_printf( &logger, " Hardware revision %x \r\n", ( uint32_t ) ver_info.hw_revision );
    log_printf( &logger, " Bootloader status %x \r\n", ( uint16_t ) bl_status );
    log_printf( &logger, "----------------------------------------------------------------\r\n" );
    Delay_1sec( );
    log_printf( &logger, "----------------------------------------------------------------\r\n" );
    log_printf( &logger, " Waiting for a new touch or snap (click)\r\n" );
    log_printf( &logger, "----------------------------------------------------------------\r\n" );
    Delay_1sec( );
    log_info( &logger, " Application Task " );
}


void application_task ( void ) 
{
    // Get touchpad XY data
    touchpad5_get_touch( &touchpad5, &touch_data );
    
    // Detecting the snap (click) criteria
    if ( touchpad5_detect_snap( &touchpad5, snap_buffer, SNAP_BUFFER_SIZE, &snap_reference) && touch_data.touch_strength > 0 )
    {
        log_printf( &logger, "----------------------------------------------------------------\r\n" );
        log_printf( &logger, "\r\n* Snap (click) event occured with strength: %u *\r\n", 
                                                                        ( uint16_t ) touch_data.touch_strength ); 
        log_printf( &logger, "----------------------------------------------------------------\r\n" );
        Delay_1sec( );
    }
    // Detecting the touch criteria
    else if ( touch_data.x_pos > 0 && touch_data.y_pos > 0 && touch_data.touch_strength > TOUCH_STRENGTH_THRESHOLD )
    {
        
        log_printf( &logger, "----------------------------------------------------------------\r\n" );
        log_printf( &logger, " \r\nTouch with Tag ID %u detected\r\n",  ( uint16_t ) touch_data.id_tag );
        log_printf( &logger, "Coordinate X = %u \r\n",                               touch_data.x_pos );
        log_printf( &logger, "Coordinate Y = %u \r\n",                               touch_data.y_pos );
        log_printf( &logger, "Touch strength = %u  \r\n",               ( uint16_t ) touch_data.touch_strength );
        log_printf( &logger, "----------------------------------------------------------------\r\n\r\n" );
        Delay_ms( 100 );
    }
    
    // Monitoring to determine whether the reset occurred on the device after the last ack reset     
    if ( touch_data.xy_info & TOUCHPAD5_SHOW_RESET )
    {
        log_printf( &logger, "----------------------------------------------------------------\r\n" );
        log_error( &logger, "\r\n Unexpected reset occured. \r\n" ); 
        log_printf( &logger, "----------------------------------------------------------------\r\n\r\n" );
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
  
bool touchpad5_get_snap_sample( touchpad5_t *ctx, uint16_t *snap_data )
{
    bool status = false;
    uint16_t snap_reg_data_avg = 0;
    
    // Get snap status for desired number of channels
    if ( TOUCHPAD5_ERROR == touchpad5_get_status( ctx, TOUCHPAD5_SNAP_STATUS, &snap_reg_data, SNAP_NUMBER_OF_CHANNELS ) )
    {
        status = false; 
    }
    else
    {
        for ( int i = 0; i < SNAP_NUMBER_OF_CHANNELS; i++ )
        {
            snap_reg_data_avg += snap_reg_data[ i ];
        }
        snap_reg_data_avg /= SNAP_NUMBER_OF_CHANNELS;
        status = true;
    }
    
    *snap_data = snap_reg_data_avg;
    
    return status;
}

    
bool touchpad5_detect_snap( touchpad5_t *ctx, uint16_t *snap_buffer, uint8_t snap_buffer_size, uint16_t *snap_reference )
{
    bool status = false;
    
    snap_idx = 0;
    tmp_count = 0;
    tmp_reference = 0;
    snap_calc_no_samples = 0;
    
    // Get snap averaged samples
    for ( int i = 0; i < snap_buffer_size; i++ )
    {
        if ( false == touchpad5_get_snap_sample( ctx, &snap_buffer[ snap_idx ] ) )
        {

            return status;
        }

        ++snap_idx;
    }
    
    // Update reference value
    tmp_reference = snap_buffer[ 0 ];
    snap_idx = 1;
    while ( snap_idx < snap_buffer_size )
    {
        if ( snap_buffer[ snap_idx++ ] == tmp_reference )
        {
            ++tmp_count;
        }
    }
    
    if ( tmp_count == snap_buffer_size - 1 )
    {
        *snap_reference = tmp_reference;
    }


    // Snap detection algorithm - detecting 1 to snap_max_no_samples for confirmed snap
    for ( int i = 0; i < snap_buffer_size; i++ )
    {
        // first snapped index saved
        if ( snap_buffer[ i ] != *snap_reference )
        {
            snap_idx = i;
            ++snap_calc_no_samples;
        }
    }

    for( int i = snap_idx; i < snap_buffer_size; i++)
    {
        if ( snap_buffer[ ( i + 1 ) % snap_buffer_size] != *snap_reference ) 
        {
            ++snap_calc_no_samples;
        }
        else
        {
            snap_calc_no_samples = 0;
        }
    }
    
    if ( snap_calc_no_samples >= 1 && snap_calc_no_samples <= snap_max_no_samples )
    {
        status =  true; 
    }

    return status;
}

// ------------------------------------------------------------------------ END
