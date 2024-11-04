/*!
 * @file main.c
 * @brief Fingerprint 4 Click example
 *
 * # Description
 * This example demonstrates the use of the Fingerprint 4 Click boards by registering 3 fingerprints and
 * then waiting until a finger is detected on the sensor and identifying if the fingerprint matches one of
 * those stored in the Flash storage.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and reads the sensor firmware version, then resets the sensor and removes all
 * stored fingerprint templates. After that it registers 3 new fingerprint templates and stores them in the Flash storage.
 * 
 * ## Application Task  
 * Waits until a finger is detected on the sensor, takes an image of the finger and checks if there's
 * a fingerprint in the library that matches the one it has just read. If it finds a match, a fingerprint template
 * ID will be displayed. All data is being logged on the USB UART where you can track the program flow.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "fingerprint4.h"

#define LOCATION_IN_FLASH               0   // Starting location or template ID where the fingerprints will be stored.
#define NUMBER_OF_FINGERPRINTS          3   // Number of fingerprints to register.

static fingerprint4_t fingerprint4;
static log_t logger;

/**
 * @brief Fingerprint 4 error check function.
 * @details This function checks the @b error_flag and displays the result appended to @b message 
 * on the USB UART.
 * @param[in] message : Prefix message of the error_flag result.
 * @param[in] error_flag : Error flag, return value of the functions.
 * @return None.
 * @note None.
 */
static void fingerprint4_error_check ( char *message, err_t error_flag );

/**
 * @brief Fingerprint 4 enroll fingerprint function.
 * @details This function enrolls a single fingerprint by taking 3 image captures. Each step will be logged on the USB UART
 * where you can track the function flow.
 * @param[in] ctx : Click context object.
 * See #fingerprint4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c <0 - Error.
 * See #fingerprint4_return_value_t definition for detailed explanation.
 * @note None.
 */
static err_t fingerprint4_enroll_fingerprint ( fingerprint4_t *ctx );

/**
 * @brief Fingerprint 4 register fingerprints function.
 * @details This function registers a desired number of fingerprints starting from the selected template ID.
 * Each step will be logged on the USB UART where you can track the function flow.
 * @param[in] ctx : Click context object.
 * See #fingerprint4_t object definition for detailed explanation.
 * @param[in] template_id : Starting template ID of fingerprints to store to Flash.
 * @param[in] num_fpc : Number of fingerprints to register.
 * @return None.
 * @note None.
 */
static void fingerprint4_register_fingerprints ( fingerprint4_t *ctx, uint16_t template_id, uint8_t num_fpc );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    fingerprint4_cfg_t fingerprint4_cfg;  /**< Click config object. */

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
    fingerprint4_cfg_setup( &fingerprint4_cfg );
    FINGERPRINT4_MAP_MIKROBUS( fingerprint4_cfg, MIKROBUS_1 );
    if ( FINGERPRINT4_RES_OK != fingerprint4_init( &fingerprint4, &fingerprint4_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    fingerprint4_reset_device ( &fingerprint4 );
    
    fingerprint4.phy_rx_timeout = FINGERPRINT4_DEFAULT_PHY_RX_TIMEOUT_MS;
    
    uint8_t version[ 50 ] = { 0 };
    if ( FINGERPRINT4_RES_OK == fingerprint4_version ( &fingerprint4, version, 50 ) )
    {
        log_printf( &logger, " FW version: %s\r\n", version );
        log_printf( &logger, "---------------------------------\r\n\n" );
    }
    
    fingerprint4_error_check( "Sensor reset", fingerprint4_sensor_reset ( &fingerprint4 ) );
    
    fingerprint4_error_check( "Remove all templates", fingerprint4_template_remove_all ( &fingerprint4 ) );
    
    fingerprint4_register_fingerprints ( &fingerprint4, LOCATION_IN_FLASH, NUMBER_OF_FINGERPRINTS );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    uint16_t template_id;
    bool match;
    log_printf( &logger, " Put your finger on the sensor.\r\n" );
    err_t error_flag = fingerprint4_identify_finger ( &fingerprint4, FINGERPRINT4_INFINITE_TIMEOUT, &template_id, &match );
    if ( error_flag )
    {
        fingerprint4_error_check( "Identify finger", error_flag );
    }
    else
    {
        if ( match )
        {
            log_printf( &logger, " >>>>> Fingerprint MATCH - Template ID: %u <<<<<\r\n", template_id );
        }
        else
        {
            log_printf( &logger, " >>>>> NO MATCH in the library <<<<<\r\n" );
        }
    }
    log_printf( &logger, " Lift the finger of the sensor.\r\n" );
    fingerprint4_wait_finger_not_present ( &fingerprint4, FINGERPRINT4_INFINITE_TIMEOUT );
    log_printf( &logger, "---------------------------------\r\n\n" );
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

static void fingerprint4_error_check ( char *message, err_t error_flag )
{
    log_printf( &logger, " %s: ", message );
    if ( error_flag )
    {
        log_printf( &logger, "FAIL! [ERROR] Num: %ld\r\n", error_flag );
    }
    else
    {
        log_printf( &logger, "DONE!\r\n" );
    }
    log_printf( &logger, "---------------------------------\r\n\n" );
}

static void fingerprint4_register_fingerprints ( fingerprint4_t *ctx, uint16_t template_id, uint8_t num_fpc )
{
    err_t error_flag = FINGERPRINT4_RES_OK;
    uint8_t cnt = 1;
    while ( cnt <= num_fpc )
    {
        log_printf( &logger, " >>> Registering fingerprint %u of %u <<<\r\n", ( uint16_t ) cnt, 
                                                                              ( uint16_t ) num_fpc );
        error_flag = fingerprint4_enroll_fingerprint ( ctx );
        if ( error_flag )
        {
            fingerprint4_error_check( "Enroll finger", error_flag );
        }
        else
        {
            error_flag = fingerprint4_template_save ( &fingerprint4, template_id + cnt - 1 );
            if ( error_flag )
            {
                fingerprint4_error_check( "Template save", error_flag );
            }
            else
            {
                log_printf( &logger, " Fingerprint template ID: %u\r\n", template_id + cnt - 1 );
                log_printf( &logger, "---------------------------------\r\n\n" );
                cnt++;
            }
        }
    }
}

static err_t fingerprint4_enroll_fingerprint ( fingerprint4_t *ctx )
{
    err_t error_flag = FINGERPRINT4_RES_OK;
    bool enroll_done = false;
    // Enroll start
    error_flag = fingerprint4_send_cmd ( ctx, FINGERPRINT4_CMD_ENROLL, FINGERPRINT4_ARG_START );
    if ( error_flag )
    {
        fingerprint4_error_check( "Enroll start", error_flag );
        return error_flag;
    }
    uint8_t cnt = 1;
    while ( cnt <= FINGERPRINT4_NUM_IMAGES )
    {
        log_printf( &logger, " >>> Taking image %u of %u <<<\r\n", ( uint16_t ) cnt, 
                                                                   ( uint16_t ) FINGERPRINT4_NUM_IMAGES );
        log_printf( &logger, " Put your finger on the sensor.\r\n" );
        // Capture image
        uint32_t prev_timeout = ctx->phy_rx_timeout;
        ctx->phy_rx_timeout = FINGERPRINT4_INFINITE_TIMEOUT;
        error_flag = fingerprint4_send_cmd_arg ( ctx, FINGERPRINT4_CMD_CAPTURE, FINGERPRINT4_ARG_NONE, 
                                                 FINGERPRINT4_ARG_TIMEOUT, &ctx->phy_rx_timeout, sizeof ( ctx->phy_rx_timeout ) );
        ctx->phy_rx_timeout = prev_timeout;
        if ( error_flag ) 
        {
            fingerprint4_error_check( "Capture image", error_flag );
            continue;
        }
        // Enroll add
        error_flag = fingerprint4_send_cmd ( ctx, FINGERPRINT4_CMD_ENROLL, FINGERPRINT4_ARG_ADD );
        if ( error_flag ) 
        {
            fingerprint4_error_check( "Enroll add", error_flag );
            continue;
        }
        cnt++;
        uint32_t samples_remaining;
        fingerprint4_copy_arg ( ctx, FINGERPRINT4_ARG_COUNT, ( uint8_t * ) &samples_remaining, 4 );
        // Break enrolling if we collected enough correct images
        if ( !samples_remaining ) 
        {
            enroll_done = true;
            break;
        }
        log_printf( &logger, " Lift the finger of the sensor.\r\n" );
        log_printf( &logger, "---------------------------------\r\n" );
        fingerprint4_wait_finger_not_present ( ctx, FINGERPRINT4_INFINITE_TIMEOUT );
    }
    error_flag = fingerprint4_send_cmd ( ctx, FINGERPRINT4_CMD_ENROLL, FINGERPRINT4_ARG_FINISH );
    if ( error_flag )
    {
        fingerprint4_error_check( "Enroll finish", error_flag );
        return error_flag;
    }
    log_printf( &logger, " Lift the finger of the sensor.\r\n" );
    log_printf( &logger, "---------------------------------\r\n" );
    fingerprint4_wait_finger_not_present ( ctx, FINGERPRINT4_INFINITE_TIMEOUT );
    return ( !enroll_done ) ? FINGERPRINT4_RES_ERROR : error_flag;
}

// ------------------------------------------------------------------------ END
