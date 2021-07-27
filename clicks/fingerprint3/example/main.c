/*!
 * \file 
 * \brief Fingerprint3 Click example
 * 
 * # Description
 * This example reads and processes data from Fingerprint 3 clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver, configures the sensor, and enrolls fingerprints.
 * 
 * ## Application Task  
 * Takes an image of the finger, then checks if there's a fingerprint in the library that matches the
 * one it has just read. All data is being logged on the USB UART.
 * 
 * ## Additional Function
 * - static void display_error ( char *message )
 * - static void display_full_rsp ( fingerprint3_t *ctx )
 * - static void search_finger( fingerprint3_t *ctx )
 * - static void match_finger( fingerprint3_t *ctx, uint16_t location )
 * - static uint8_t enroll_finger( fingerprint3_t *ctx, uint16_t location, uint8_t features )
 *  
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "fingerprint3.h"
#include "string.h"

// ------------------------------------------------------------------ VARIABLES

#define LOCATION_IN_LIBRARY            1    // Location in flash where the fingerprint template will be stored.
#define NUMBER_OF_FINGERPRINTS         2    // Number of fingerprints for enrolling.
#define NUMBER_OF_IMAGES               3    // Number of images it will take for a single fingerprint template.

static fingerprint3_t fingerprint3;
static log_t logger;
uint8_t package_content[ FINGERPRINT3_MAX_PACKAGE_LENGTH ];
uint8_t error_check = 0;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

/**
 * @brief Display error function.
 *
 * @param message  Input string.
 *
 * @description This function concatenates status of response to the input string and prints it on the USB UART.
 */
static void display_error ( char *message );

/**
 * @brief Display full response function.
 *
 * @param ctx  Click object.
 *
 * @description This function parses and displays full response to the previously sent command on the USB UART.
 */
static void display_full_rsp ( fingerprint3_t *ctx );

/**
 * @brief Search finger function.
 *
 * @param ctx  Click object.
 *
 * @description This function searches the whole finger library for the template that matches the one 
 *              it stores in char_buffer 1. All data is being logged on the USB UART.
 */
static void search_finger( fingerprint3_t *ctx );

/**
 * @brief Match finger function.
 *
 * @param ctx       Click object.
 * @param location  Location in library.
 *
 * @description This function checks if the template stored at the desired location matches the fingerprint
 *              it reads. All data is being logged on the USB UART.
 */
static void match_finger( fingerprint3_t *ctx, uint16_t location );

/**
 * @brief Enroll finger function.
 *
 * @param ctx       Click object.
 * @param location  Location in library where the fingerprint template will be stored.
 * @param features  Number of fingerprint images it will combine in a template.
 *
 * @description This function enrolls the fingerprint, creates a template combining the taken images and
 *              stores it at the desired location. All data is being logged on the USB UART.
 */
static uint8_t enroll_finger( fingerprint3_t *ctx, uint16_t location, uint8_t features );


// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    fingerprint3_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );
    Delay_ms( 100 );

    //  Click initialization.

    fingerprint3_cfg_setup( &cfg );
    FINGERPRINT3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    err_t init_flag = fingerprint3_init( &fingerprint3, &cfg );
    if ( init_flag == UART_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    Delay_ms( 100 );
    
    error_check = fingerprint3_set_config ( &fingerprint3, FINGERPRINT3_DEFAULT_ADDRESS, 
                                                           FINGERPRINT3_DEFAULT_PASSWORD );
    display_error( "Set Config" );
    Delay_ms( 500 );
    
    error_check = fingerprint3_soft_reset ( &fingerprint3 );
    display_error( "Soft Reset" );
    Delay_ms( 500 );
    
    error_check = fingerprint3_check_sensor ( &fingerprint3 );
    display_error( "Check Sensor" );
    Delay_ms( 500 );
    
    error_check = fingerprint3_empty_library ( &fingerprint3 );
    display_error( "Empty the Library" );
    Delay_ms( 500 );
    
    uint8_t cnt = 0; 
    do 
    {
        log_printf( &logger, " >>>  Register fingerprint %u of %u  <<<\r\n", ( uint16_t ) cnt + 1, 
                                                                             ( uint16_t ) NUMBER_OF_FINGERPRINTS );
        log_printf( &logger, "--------------------------------- \r\n" );
        error_check = enroll_finger ( &fingerprint3, LOCATION_IN_LIBRARY + cnt, NUMBER_OF_IMAGES );
        display_error( "Enroll finger" );
        if ( FINGERPRINT3_OK != error_check )
        {
            log_printf( &logger, " Please enroll your fingerprint again.\r\n" );
            log_printf( &logger, "--------------------------------- \r\n" );
        }
        else
        {
            cnt++;
        }
        Delay_ms( 1000 );
    }
    while ( FINGERPRINT3_OK != error_check || cnt != NUMBER_OF_FINGERPRINTS );
}

void application_task ( void )
{    
    search_finger( &fingerprint3 );
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

static void display_error ( char *message )
{
    log_printf( &logger, " %s: ", message );
    if ( FINGERPRINT3_OK == error_check )
    {
        log_printf( &logger, "DONE!\r\n" );
    }
    else
    {
        log_printf( &logger, "FAIL! [ERROR] Num: 0x%.2X\r\n", ( uint16_t ) error_check );
    }
    log_printf( &logger, "--------------------------------- \r\n" );
}

static void display_full_rsp ( fingerprint3_t *ctx )
{
    log_printf( &logger, "* Header            : 0x%.4X\r\n", ctx->rsp.header );
    log_printf( &logger, "* Address           : 0x%.8LX\r\n", ctx->rsp.addr );
    log_printf( &logger, "* Package identifier: 0x%.2X\r\n", ( uint16_t ) ctx->rsp.pkg_id );
    log_printf( &logger, "* Package length    : 0x%.4X\r\n", ctx->rsp.pkg_len );

    log_printf( &logger, "* Confirmation code :" );

    if ( ctx->rsp.pkg_content[ 0 ] == FINGERPRINT3_CONF_CMD_OK )
    {
        log_printf( &logger, " OK!\r\n" );
    }
    else
    {
        log_error( &logger, " Num: 0x%.2X", ( uint16_t ) ctx->rsp.pkg_content[ 0 ] );
    }

    if ( ctx->rsp.pkg_len > 3 )
    {
        log_printf( &logger, "* Package Content: " );
        for ( uint16_t n_cnt = 1; n_cnt < ctx->rsp.pkg_len - 2; n_cnt++ )
        {

            log_printf( &logger, "0x%.2X ", ( uint16_t ) ctx->rsp.pkg_content[ n_cnt ] );
        }
        log_printf( &logger, "\r\n" );
    }

    log_printf( &logger, "* Checksum           : 0x%.4X \r\n", ctx->rsp.checksum );
}

static void search_finger( fingerprint3_t *ctx )
{
    log_printf( &logger, "  >>> Searching Fingerprints <<<  \r\n" );
    log_printf( &logger, "--------------------------------- \r\n" );
    fingerprint3_aura_control ( &fingerprint3, FINGERPRINT3_AURA_CTRL_BREATH, 0xFF, 
                                               FINGERPRINT3_AURA_LED_PURPLE, FINGERPRINT3_AURA_TIME_INFINITE );
    log_printf( &logger, " Put your finger on the sensor  \r\n" );
    log_printf( &logger, "--------------------------------- \r\n" );
    
    while ( fingerprint3_finger_indicator( &fingerprint3 ) == FINGERPRINT3_DETECT_NO_FINGER );
    
    while ( FINGERPRINT3_OK != fingerprint3_aura_control ( &fingerprint3, FINGERPRINT3_AURA_CTRL_OFF, 0xFF, 
                                                                          FINGERPRINT3_AURA_LED_PURPLE, 
                                                                          FINGERPRINT3_AURA_TIME_INFINITE ) )
    {
        Delay_ms( 100 );
    }
    for ( ; ; )
    {
        error_check = fingerprint3_take_image ( &fingerprint3 );
        if ( FINGERPRINT3_OK != error_check )
        {
            display_error( "Take Image" );
            Delay_ms( 1000 );
            continue;
        }
        error_check = fingerprint3_extract_features ( &fingerprint3, 1 );
        
        if ( FINGERPRINT3_OK != error_check )
        {
            display_error( "Extract Features" );
            Delay_ms( 1000 );
            continue;
        }
        break;
    }
    
    uint16_t match_score, location;
    
    error_check = fingerprint3_search_finger ( &fingerprint3, 1, &location, &match_score );
    if ( FINGERPRINT3_OK == error_check )
    {
        log_printf( &logger, "  >>>>> FINGERPRINT MATCH <<<<<< \r\n\r\n" );
        log_printf( &logger, "  Location: 0x%.4X Match score : %u\r\n", location, match_score );
        log_printf( &logger, "---------------------------------\r\n" );
        fingerprint3_aura_control ( &fingerprint3, FINGERPRINT3_AURA_CTRL_BREATH, 0x80, 
                                                   FINGERPRINT3_AURA_LED_BLUE, 1 );
    }
    else if ( FINGERPRINT3_CONF_NOT_FOUND == error_check )
    {
        log_printf( &logger, " >>>>> NO MATCH in library <<<<<<\r\n\r\n" );
        log_printf( &logger, "---------------------------------\r\n" );
        fingerprint3_aura_control ( &fingerprint3, FINGERPRINT3_AURA_CTRL_BREATH, 0x80, 
                                                   FINGERPRINT3_AURA_LED_RED, 1 );
    }
    else
    {
        display_error( "Search Finger" );
        fingerprint3_aura_control ( &fingerprint3, FINGERPRINT3_AURA_CTRL_BREATH, 0x80, 
                                                   FINGERPRINT3_AURA_LED_RED, 1 );
    }
    Delay_ms( 100 );
    log_printf( &logger, " Lift the finger of the sensor.\r\n" );
    log_printf( &logger, "--------------------------------- \r\n" );
            
    error_check = fingerprint3_take_image ( &fingerprint3 );
    while ( error_check != FINGERPRINT3_CONF_NO_FINGER )
    {
        Delay_ms( 100 );
        error_check = fingerprint3_take_image ( &fingerprint3 );
    }
    while ( fingerprint3_finger_indicator( &fingerprint3 ) != FINGERPRINT3_DETECT_NO_FINGER );
    
    Delay_ms( 1000 );
}

static void match_finger( fingerprint3_t *ctx, uint16_t location )
{
    error_check = fingerprint3_load_template ( &fingerprint3, 2, location );
    display_error( "Load Template" );
    Delay_ms( 100 );
    
    log_printf( &logger, "  >>> Matching Fingerprints <<<  \r\n" );
    log_printf( &logger, "--------------------------------- \r\n" );
    fingerprint3_aura_control ( &fingerprint3, FINGERPRINT3_AURA_CTRL_BREATH, 0xFF, 
                                               FINGERPRINT3_AURA_LED_PURPLE, FINGERPRINT3_AURA_TIME_INFINITE );
    log_printf( &logger, " Put your finger on the sensor  \r\n" );
    log_printf( &logger, "--------------------------------- \r\n" );
    
    while ( fingerprint3_finger_indicator( &fingerprint3 ) == FINGERPRINT3_DETECT_NO_FINGER );
    
    while ( FINGERPRINT3_OK != fingerprint3_aura_control ( &fingerprint3, FINGERPRINT3_AURA_CTRL_OFF, 0xFF, 
                                                                          FINGERPRINT3_AURA_LED_PURPLE, 
                                                                          FINGERPRINT3_AURA_TIME_INFINITE ) )
    {
        Delay_ms( 100 );
    }
    
    for ( ; ; )
    {
        error_check = fingerprint3_take_image ( &fingerprint3 );
        if ( FINGERPRINT3_OK != error_check )
        {
            display_error( "Take Image" );
            Delay_ms( 1000 );
            continue;
        }
        error_check = fingerprint3_extract_features ( &fingerprint3, 3 );
        
        if ( FINGERPRINT3_OK != error_check )
        {
            display_error( "Extract Features" );
            Delay_ms( 1000 );
            continue;
        }
        break;
    }
    
    uint16_t match_score;
    
    error_check = fingerprint3_match_finger ( &fingerprint3, &match_score );
    if ( FINGERPRINT3_OK == error_check )
    {
        log_printf( &logger, "  >>>>> FINGERPRINT MATCH <<<<<< \r\n\r\n" );
        log_printf( &logger, "  Match score       : %u\r\n", match_score );
        log_printf( &logger, "---------------------------------\r\n" );
        fingerprint3_aura_control ( &fingerprint3, FINGERPRINT3_AURA_CTRL_BREATH, 0x80, 
                                                   FINGERPRINT3_AURA_LED_BLUE, 1 );
    }
    else if ( FINGERPRINT3_CONF_NO_MATCH == error_check )
    {
        log_printf( &logger, " >>>>> NO MATCH at location: 0x%.4X <<<<<<\r\n\r\n", location );
        log_printf( &logger, "---------------------------------\r\n" );
        fingerprint3_aura_control ( &fingerprint3, FINGERPRINT3_AURA_CTRL_BREATH, 0x80, 
                                                   FINGERPRINT3_AURA_LED_RED, 1 );
    }
    else
    {
        display_error( "Match Finger" );
        fingerprint3_aura_control ( &fingerprint3, FINGERPRINT3_AURA_CTRL_BREATH, 0x80, 
                                                   FINGERPRINT3_AURA_LED_RED, 1 );
    }
    Delay_ms( 100 );
    log_printf( &logger, " Lift the finger of the sensor.\r\n" );
    log_printf( &logger, "--------------------------------- \r\n" );
            
    error_check = fingerprint3_take_image ( &fingerprint3 );
    while ( error_check != FINGERPRINT3_CONF_NO_FINGER )
    {
        Delay_ms( 100 );
        error_check = fingerprint3_take_image ( &fingerprint3 );
    }
    while ( fingerprint3_finger_indicator( &fingerprint3 ) != FINGERPRINT3_DETECT_NO_FINGER );
    
    Delay_ms( 1000 );
}

static uint8_t enroll_finger( fingerprint3_t *ctx, uint16_t location, uint8_t features )
{
    for ( uint8_t cnt = 1; cnt <= features; )
    {
        log_printf( &logger, " >>>  Taking image %u of %u  <<<\r\n", ( uint16_t ) cnt, 
                                                                     ( uint16_t ) features );
        log_printf( &logger, "--------------------------------- \r\n" );

        log_printf( &logger, " Put your finger on the sensor  \r\n" );
        log_printf( &logger, "--------------------------------- \r\n" );
        fingerprint3_aura_control ( &fingerprint3, FINGERPRINT3_AURA_CTRL_BREATH, 0xFF, 
                                                   FINGERPRINT3_AURA_LED_PURPLE, FINGERPRINT3_AURA_TIME_INFINITE );

        while ( fingerprint3_finger_indicator( &fingerprint3 ) == FINGERPRINT3_DETECT_NO_FINGER );
        
        while ( FINGERPRINT3_OK != fingerprint3_aura_control ( &fingerprint3, FINGERPRINT3_AURA_CTRL_OFF, 0xFF, 
                                                                              FINGERPRINT3_AURA_LED_PURPLE, 
                                                                              FINGERPRINT3_AURA_TIME_INFINITE ) )
        {
            Delay_ms( 100 );
        }

        error_check = fingerprint3_take_image ( &fingerprint3 );
        display_error( "Take Image" );
                
        if ( FINGERPRINT3_OK == error_check )
        {
            Delay_ms( 100 );
            error_check = fingerprint3_extract_features ( &fingerprint3, cnt );
            display_error( "Extract Features" );
            if ( FINGERPRINT3_OK == error_check )
            {
                cnt++;
            }
            Delay_ms( 100 );
            fingerprint3_aura_control ( &fingerprint3, FINGERPRINT3_AURA_CTRL_BREATH, 0x80, 
                                                       FINGERPRINT3_AURA_LED_BLUE, 1 );
            Delay_ms( 100 );
            
        }

        log_printf( &logger, " Lift the finger of the sensor.\r\n" );
        log_printf( &logger, "--------------------------------- \r\n" );
        
        error_check = fingerprint3_take_image ( &fingerprint3 );
        while ( error_check != FINGERPRINT3_CONF_NO_FINGER )
        {
            Delay_ms( 100 );
            error_check = fingerprint3_take_image ( &fingerprint3 );
        }
        while ( fingerprint3_finger_indicator( &fingerprint3 ) != FINGERPRINT3_DETECT_NO_FINGER );
        Delay_ms( 100 );
    }
    error_check = fingerprint3_create_template ( &fingerprint3 );
    display_error( "Create Template" );
    if ( FINGERPRINT3_OK != error_check )
    {
        return error_check;
    }
    Delay_ms( 100 );
    error_check = fingerprint3_store_template ( &fingerprint3, 1, location );
    display_error( "Store Template" );
    if ( FINGERPRINT3_OK != error_check )
    {
        return error_check;
    }
    Delay_ms( 100 );
    
    return FINGERPRINT3_OK;
}

// ------------------------------------------------------------------------ END
