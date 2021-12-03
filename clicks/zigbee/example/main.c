/*!
 * @file main.c
 * @brief ZigBee Click Example.
 *
 * # Description
 * This is an example that demonstrates the use of the ZigBee Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of driver, UART ISR and then configures device. 
 * Depending on previous selected device mode it creates new PAN network or joins to one.
 *
 * ## Application Task
 * Host mode: Broadcasts message 'MikroE' every 3 seconds.
 * User mode: Checks if something is received.
 *
 * ## Additional Function
 * - void zigbee_clear_app_buf ( void ) - Clearing application buffer function.
 * - void resp_wait ( zigbee_t *ctx ) - Function for waiting for complete response.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "zigbee.h"

static zigbee_t zigbee;
static log_t logger;

uint8_t dev_mode;
uint8_t app_mode;

static char app_buf[ ZIGBEE_DEV_BUFFER_MAX ] = { 0 };

char AT_BCAST_MSG[ 15 ] = ":00,MikroE";

char AT_HOST_CFG1[ 10 ] = "00=6314";
char AT_HOST_CFG2[ 20 ] = "0A=0914;password";
char AT_HOST_CFG3[ 50 ] = "09=5A6967426565416C6C69616E63653039;password";

/**
 * @brief ZigBee clearing application buffer.
 * @details This function clears memory of application buffer and reset it's length and counter.
 */
void zigbee_clear_app_buf ( void );

/**
 * @brief ZigBee wait response.
 * @details This function is used for waiting for complete response.
 */
void resp_wait ( zigbee_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    zigbee_cfg_t zigbee_cfg;  /**< Click config object. */

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
    app_mode = ZIGBEE_APP_INIT;
    dev_mode = ZIGBEE_DEV_USER;

    // Click initialization.
    zigbee_cfg_setup( &zigbee_cfg );
    ZIGBEE_MAP_MIKROBUS( zigbee_cfg, MIKROBUS_1 );
    if ( UART_ERROR == zigbee_init( &zigbee, &zigbee_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    log_printf( &logger, "------------------------------\r\n", app_buf );
    log_printf( &logger, " Restarting Device \r\n" );
    zigbee_restart( &zigbee );

    log_printf( &logger, "------------------------------\r\n", app_buf );
    log_printf( &logger, " Sending command : AT \r\n", app_buf );
    zigbee_send_cmd( &zigbee, ZIGBEE_CMD_AT );
    resp_wait( &zigbee );

    log_printf( &logger, "------------------------------\r\n", app_buf );
    log_printf( &logger, " Sending command : AT + DASSL \r\n", app_buf );
    zigbee_send_cmd( &zigbee, ZIGBEE_CMD_AT_DASSL );
    resp_wait( &zigbee );

    log_printf( &logger, "------------------------------\r\n", app_buf );
    log_printf( &logger, " Sending command : ATZ \r\n", app_buf );
    zigbee_send_cmd( &zigbee, ZIGBEE_CMD_ATZ );
    resp_wait( &zigbee );

    log_printf( &logger, "------------------------------\r\n", app_buf );
    log_printf( &logger, " Sending command : ATI \r\n", app_buf );
    zigbee_send_cmd( &zigbee, ZIGBEE_CMD_ATI );
    resp_wait( &zigbee );

    log_printf( &logger, "------------------------------\r\n", app_buf );
    log_printf( &logger, " Sending command : AT + N \r\n", app_buf );
    zigbee_send_cmd( &zigbee, ZIGBEE_CMD_AT_N );
    resp_wait( &zigbee );
    
    if ( ZIGBEE_DEV_HOST == dev_mode )
    {
        // Setting the device into host mode and creating a network for other devices to connect.
        log_printf( &logger, "-----------------------------------\r\n", app_buf );
        log_printf( &logger, " Sending command : AT + HOST CFG 1 \r\n", app_buf );
        zigbee_send_at( &zigbee, ZIGBEE_CMD_ATS, &AT_HOST_CFG1[ 0 ] );
        resp_wait( &zigbee );
        log_printf( &logger, "-----------------------------------\r\n", app_buf );
        log_printf( &logger, " Sending command : AT + HOST CFG 2 \r\n", app_buf );
        zigbee_send_at( &zigbee, ZIGBEE_CMD_ATS, &AT_HOST_CFG2[ 0 ] );
        resp_wait( &zigbee );
        log_printf( &logger, "-----------------------------------\r\n", app_buf );
        log_printf( &logger, " Sending command : AT + HOST CFG 3 \r\n", app_buf );
        zigbee_send_at( &zigbee, ZIGBEE_CMD_ATS, &AT_HOST_CFG3[ 0 ] );
        resp_wait( &zigbee );
        log_printf( &logger, "-----------------------------------\r\n", app_buf );
        log_printf( &logger, " Sending command : AT + EN \r\n", app_buf );
        zigbee_send_cmd( &zigbee, ZIGBEE_CMD_AT_EN );
        resp_wait( &zigbee );
    }
    else if ( ZIGBEE_DEV_USER == dev_mode )
    {
        // Setting the device into user mode and joining the existing network.
        log_printf( &logger, "-----------------------------------\r\n", app_buf );
        log_printf( &logger, " Sending command : AT + JN \r\n", app_buf );
        zigbee_send_cmd( &zigbee, ZIGBEE_CMD_AT_JN );
        resp_wait( &zigbee );
    }

    log_printf( &logger, "-----------------------------------\r\n", app_buf );
    log_printf( &logger, " Sending command : AT + IDREQ \r\n", app_buf );
    zigbee_send_cmd( &zigbee, ZIGBEE_CMD_AT_IDREQ );
    resp_wait( &zigbee );

    log_printf( &logger, "-----------------------------------\r\n", app_buf );
    log_printf( &logger, " Sending command : AT + N \r\n", app_buf );
    zigbee_send_cmd( &zigbee, ZIGBEE_CMD_AT_N );
    resp_wait( &zigbee );

    Delay_ms( 1000 );
    app_mode = ZIGBEE_APP_TASK;
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-----------------------------------\r\n", app_buf );
}

void application_task ( void ) 
{
    if ( ZIGBEE_DEV_HOST == dev_mode )
    {
        log_printf( &logger, "-----------------------------------\r\n", app_buf );
        zigbee_send_at( &zigbee, ZIGBEE_CMD_AT_BCAST, &AT_BCAST_MSG[ 0 ] );
        resp_wait( &zigbee );
        Delay_ms( 3000 );
    }
    else if ( ZIGBEE_DEV_USER == dev_mode )
    {
        resp_wait( &zigbee );
        log_printf( &logger, "-----------------------------------\r\n", app_buf );
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

void zigbee_clear_app_buf ( void ) 
{
    memset( app_buf, 0, ZIGBEE_DEV_BUFFER_MAX );
}

void resp_wait ( zigbee_t *ctx )
{
    uint8_t resp_flag;
    for ( ; ; )
    {  
        zigbee_generic_read( &zigbee, app_buf, ZIGBEE_DEV_BUFFER_MAX );
        Delay_ms( 50 );
        resp_flag = zigbee_resp( ctx, app_buf );

        if ( ( ZIGBEE_APP_TASK == app_mode ) && ( ZIGBEE_DEV_USER == dev_mode ) )
        {  
            if ( ( ZIGBEE_OP_WAIT != resp_flag ) )
            {   
                
                log_printf( &logger, " %s ", app_buf ); 
                zigbee_clear_app_buf(  );
            }
        }
        else
        {  
            if ( ( ZIGBEE_OP_OK == resp_flag ) || ( ZIGBEE_OP_ERROR == resp_flag ) )
            {
                log_printf( &logger, "%s", app_buf );
                log_printf( &logger, "\r\n" );
                zigbee_clear_app_buf(  );
                break;
            }
        }

    }
}

// ------------------------------------------------------------------------ END
