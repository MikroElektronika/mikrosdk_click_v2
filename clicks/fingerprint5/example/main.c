/*!
 * @file main.c
 * @brief Fingerprint 5 Click Example.
 *
 * # Description
 * This example demonstrates how to use the Fingerprint 5 Click board to enroll and identify fingerprints.
 * The application cycles through several states: checking firmware readiness, reading version info, 
 * deleting existing templates, enrolling new fingerprints, and continuously identifying them.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and the Click board, resets the device and sets up the application state machine.
 *
 * ## Application Task
 * Handles command processing and application state transitions, enabling fingerprint enrollment and identification.
 *
 * @note
 * Make sure to place your finger on the sensor when prompted during enrollment and identification.
 * The example registers 2 fingerprints by default.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "fingerprint5.h"

#define NUMBER_OF_FINGERPRINTS  2   // Number of fingerprints to register.

static fingerprint5_t fingerprint5;
static log_t logger;

/**
 * @brief Example states.
 * @details Predefined enum values for application example state.
 */
typedef enum
{
    FINGERPRINT5_APP_STATE_WAIT_READY = 0,
    FINGERPRINT5_APP_STATE_VERSION,
    FINGERPRINT5_APP_STATE_DELETE_TEMPLATES,
    FINGERPRINT5_APP_STATE_ENROLL,
    FINGERPRINT5_APP_STATE_IDENTIFY

} fingerprint5_app_state_t;

/**
 * @brief Application example variables.
 * @details Variables used in application example.
 */
static fingerprint5_app_state_t app_state = FINGERPRINT5_APP_STATE_WAIT_READY;
static fingerprint5_status_t status;
static fingerprint5_version_t version;
static fingerprint5_list_templates_t templates;
static fingerprint5_enroll_t enroll;
static fingerprint5_identify_t identify;

/**
 * @brief Fingerprint 5 parse command.
 * @details This function parses the received command response from the device and updates
 * the relevant global structures such as status, version, templates, enroll, or identify.
 * @param[in] ctx : Fingerprint 5 Click context object.
 * See #fingerprint5_t object definition for detailed explanation.
 * @note None.
 * @return None.
 */
static void fingerprint5_parse_cmd ( fingerprint5_t *ctx );

/**
 * @brief Fingerprint 5 main process handler.
 * @details This function handles the application state machine for enrolling and identifying fingerprints.
 * It sends commands based on the current state and received data, allowing multiple enrollments and continuous identification.
 * @param[in] ctx : Fingerprint 5 Click context object.
 * See #fingerprint5_t object definition for detailed explanation.
 * @note None.
 * @return None.
 */
static void fingerprint5_process ( fingerprint5_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    fingerprint5_cfg_t fingerprint5_cfg;  /**< Click config object. */

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
    fingerprint5_cfg_setup( &fingerprint5_cfg );
    FINGERPRINT5_MAP_MIKROBUS( fingerprint5_cfg, MIKROBUS_1 );
    if ( UART_ERROR == fingerprint5_init( &fingerprint5, &fingerprint5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    fingerprint5_reset_device ( &fingerprint5 );

    log_info( &logger, " Application Task " );
    
    app_state = FINGERPRINT5_APP_STATE_WAIT_READY;
    log_printf ( &logger, "\r\nAPP STATE: WAIT READY\r\n" );
}

void application_task ( void ) 
{
    if ( FINGERPRINT5_OK == fingerprint5_read_cmd ( &fingerprint5 ) )
    {
        fingerprint5_parse_cmd ( &fingerprint5 );
        fingerprint5_process ( &fingerprint5 );
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

static void fingerprint5_parse_cmd ( fingerprint5_t *ctx )
{
    switch ( ctx->cmd.cmd_id )
    {
        case FINGERPRINT5_CMD_STATUS:
        {
            status.evt = ( ( ( uint16_t ) ctx->cmd.payload[ 1 ] << 8 ) | ctx->cmd.payload[ 0 ] );
            status.state = ( ( ( uint16_t ) ctx->cmd.payload[ 3 ] << 8 ) | ctx->cmd.payload[ 2 ] );
            status.app_fail = ( ( ( uint16_t ) ctx->cmd.payload[ 5 ] << 8 ) | ctx->cmd.payload[ 4 ] );
            if ( status.app_fail )
            {
                log_error ( &logger, "APP FAIL: %.4X\r\n", status.app_fail );
            }
            break;
        }
        case FINGERPRINT5_CMD_VERSION:
        {
            version.unique_id[ 0 ] = ( ( ( uint32_t ) ctx->cmd.payload[ 3 ] << 24 ) | 
                                       ( ( uint32_t ) ctx->cmd.payload[ 2 ] << 16 ) | 
                                       ( ( uint16_t ) ctx->cmd.payload[ 1 ] << 8 ) | 
                                                      ctx->cmd.payload[ 0 ] );
            version.unique_id[ 1 ] = ( ( ( uint32_t ) ctx->cmd.payload[ 7 ] << 24 ) | 
                                       ( ( uint32_t ) ctx->cmd.payload[ 6 ] << 16 ) | 
                                       ( ( uint16_t ) ctx->cmd.payload[ 5 ] << 8 ) | 
                                                      ctx->cmd.payload[ 4 ] );
            version.unique_id[ 2 ] = ( ( ( uint32_t ) ctx->cmd.payload[ 11 ] << 24 ) | 
                                       ( ( uint32_t ) ctx->cmd.payload[ 10 ] << 16 ) | 
                                       ( ( uint16_t ) ctx->cmd.payload[ 9 ] << 8 ) | 
                                                      ctx->cmd.payload[ 8 ] );
            version.fw_id = ctx->cmd.payload[ 12 ];
            version.fw_fuse_lvl = ctx->cmd.payload[ 13 ];
            version.ver_str_len = ( ( ( uint16_t ) ctx->cmd.payload[ 15 ] << 8 ) | ctx->cmd.payload[ 14 ] );
            if ( version.ver_str_len <= FINGERPRINT5_MAX_VERSION_SIZE )
            {
                memcpy ( version.ver_str, &ctx->cmd.payload[ 16 ], version.ver_str_len );
                log_printf ( &logger, "Device ID: %.8X %.8X %.8X\r\n", 
                             version.unique_id[ 0 ], 
                             version.unique_id[ 1 ], 
                             version.unique_id[ 2 ] );
                log_printf ( &logger, "Version: %s\r\n", version.ver_str );
            }
            else
            {
                version.ver_str_len = 0;
            }
            break;
        }
        case FINGERPRINT5_CMD_LIST_TEMPLATES:
        {
            templates.num_templates = ( ( ( uint16_t ) ctx->cmd.payload[ 1 ] << 8 ) | ctx->cmd.payload[ 0 ] );
            if ( templates.num_templates <= FINGERPRINT5_MAX_NUM_TEMPLATES )
            {
                log_printf ( &logger, "Number of templates found: %u\r\n", templates.num_templates );
                for ( uint16_t cnt = 0; cnt < templates.num_templates; cnt++ )
                {
                    templates.template_ids[ cnt ] = ( ( uint16_t ) ctx->cmd.payload[ cnt * 2 + 3 ] ) | 
                                                                   ctx->cmd.payload[ cnt * 2 + 2 ];
                    log_printf ( &logger, "ID: %.4X\r\n", templates.template_ids[ cnt ] );
                }
            }
            break;
        }
        case FINGERPRINT5_CMD_ENROLL:
        {
            enroll.id = ( ( ( uint16_t ) ctx->cmd.payload[ 1 ] << 8 ) | ctx->cmd.payload[ 0 ] );
            enroll.feedback = ctx->cmd.payload[ 2 ];
            enroll.samples_remaining = ctx->cmd.payload[ 3 ];
            log_printf ( &logger, "Enroll samples remaining: %u, feedback: ", 
                         ( uint16_t ) enroll.samples_remaining );
            switch ( enroll.feedback ) 
            {
                case FINGERPRINT5_ENROLL_FEEDBACK_DONE: 
                {
                    log_printf ( &logger, "Done" );
                    break;
                }
                case FINGERPRINT5_ENROLL_FEEDBACK_PROGRESS: 
                {
                    log_printf ( &logger, "Progress" );
                    break;
                }
                case FINGERPRINT5_ENROLL_FEEDBACK_REJECT_LOW_QUALITY: 
                {
                    log_printf ( &logger, "Reject.LowQuality" );
                    break;
                }
                case FINGERPRINT5_ENROLL_FEEDBACK_REJECT_LOW_COVERAGE: 
                {
                    log_printf ( &logger, "Reject.LowCoverage" );
                    break;
                }
                case FINGERPRINT5_ENROLL_FEEDBACK_REJECT_LOW_MOBILITY: 
                {
                    log_printf ( &logger, "Reject.LowMobility" );
                    break;
                }
                case FINGERPRINT5_ENROLL_FEEDBACK_REJECT_OTHER: 
                {
                    log_printf ( &logger, "Reject.Other" );
                    break;
                }
                case FINGERPRINT5_ENROLL_FEEDBACK_PROGRESS_IMMOBILE: 
                {
                    log_printf ( &logger, "Progress.Immobile" );
                    break;
                }
                default:
                {
                    log_printf ( &logger, "Unknown" );
                    break;
                }
            }
            log_printf ( &logger, "\r\n" );
            break;
        }
        case FINGERPRINT5_CMD_IDENTIFY:
        {
            identify.match = ( ( ( uint16_t ) ctx->cmd.payload[ 1 ] << 8 ) | ctx->cmd.payload[ 0 ] );
            identify.type = ( ( ( uint16_t ) ctx->cmd.payload[ 3 ] << 8 ) | ctx->cmd.payload[ 2 ] );
            identify.id = ( ( ( uint16_t ) ctx->cmd.payload[ 5 ] << 8 ) | ctx->cmd.payload[ 4 ] );
            identify.tag = ( ( ( uint16_t ) ctx->cmd.payload[ 7 ] << 8 ) | ctx->cmd.payload[ 6 ] );
            if ( FINGERPRINT5_IDENTIFY_RESULT_MATCH == identify.match )
            {
                log_printf ( &logger, "Identify MATCH on ID: %u\r\n", identify.id );
            }
            else
            {
                log_printf ( &logger, "Identify NO MATCH\r\n" );
            }
            break;
        }
        default:
        {
            log_printf ( &logger, "\r\nCMD ID: %.4X\r\n", ctx->cmd.cmd_id );
            log_printf ( &logger, "Payload Len: %u\r\n", ctx->cmd.payload_len );
            if ( ctx->cmd.payload_len )
            {
                log_printf ( &logger, "Payload:\r\n    " );
            }
            for ( uint16_t cnt = 0; cnt < ctx->cmd.payload_len; cnt++ )
            {
                log_printf ( &logger, "%.2X ", ctx->cmd.payload[ cnt ] );
                if ( 15 == cnt % 16 )
                {
                    log_printf ( &logger, "\r\n    " );
                }
            }
            if ( ctx->cmd.payload_len )
            {
                log_printf ( &logger, "\r\n" );
            }
            break;
        }
    }
}

static void fingerprint5_process ( fingerprint5_t *ctx )
{
    static uint8_t num_fingers_to_enroll = NUMBER_OF_FINGERPRINTS;
    switch ( app_state )
    {
        case FINGERPRINT5_APP_STATE_WAIT_READY:
        { 
            if ( status.state & FINGERPRINT5_STATE_APP_FW_READY )
            {
                log_printf ( &logger, "\r\nAPP STATE: VERSION\r\n" );
                app_state = FINGERPRINT5_APP_STATE_VERSION;
                fingerprint5_get_version ( ctx );
            }
            break;
        }
        case FINGERPRINT5_APP_STATE_VERSION:
        {
            if ( version.ver_str_len )
            {
                log_printf ( &logger, "\r\nAPP STATE: DELETE TEMPLATES\r\n" );
                app_state = FINGERPRINT5_APP_STATE_DELETE_TEMPLATES;
                fingerprint5_delete_templates ( ctx );
            }
            break;
        }
        case FINGERPRINT5_APP_STATE_DELETE_TEMPLATES:
        {
            log_printf ( &logger, "\r\nAPP STATE: ENROLL\r\n" );
            log_printf ( &logger, "\r\nEnrolling finger %u of %u...\r\n", 
                         ( uint16_t ) ( NUMBER_OF_FINGERPRINTS - num_fingers_to_enroll + 1 ), 
                         ( uint16_t ) NUMBER_OF_FINGERPRINTS );
            app_state = FINGERPRINT5_APP_STATE_ENROLL;
            fingerprint5_enroll_finger ( ctx );
            break;
        }
        case FINGERPRINT5_APP_STATE_ENROLL:
        {
            if ( FINGERPRINT5_STATE_ENROLL != ( status.state & FINGERPRINT5_STATE_ENROLL ) )
            {
                num_fingers_to_enroll--;
                if ( num_fingers_to_enroll > 0 )
                {
                    log_printf ( &logger, "\r\nEnrolling finger %u of %u...\r\n", 
                                 ( uint16_t ) ( NUMBER_OF_FINGERPRINTS - num_fingers_to_enroll + 1 ), 
                                 ( uint16_t ) NUMBER_OF_FINGERPRINTS );
                    fingerprint5_enroll_finger ( ctx );
                }
                else
                {
                    log_printf ( &logger, "\r\nAPP STATE: IDENTIFY\r\n" );
                    log_printf ( &logger, "\r\nIdentifying fingerprint...\r\n" );
                    app_state = FINGERPRINT5_APP_STATE_IDENTIFY;
                    fingerprint5_identify_finger ( ctx );
                }
            }
            break;
        }
        case FINGERPRINT5_APP_STATE_IDENTIFY:
        {
            if ( FINGERPRINT5_STATE_IDENTIFY != ( status.state & FINGERPRINT5_STATE_IDENTIFY ) )
            {
                log_printf ( &logger, "\r\nIdentifying fingerprint...\r\n" );
                fingerprint5_identify_finger ( ctx );
            }
            break;
        }
        default:
        {
            log_error ( &logger, "APP STATE: UNKWNOWN\r\n" );
            break;
        }
    }
}

// ------------------------------------------------------------------------ END
