/*!
 * @file main.c
 * @brief USBCSource Click example
 *
 * # Description
 * This is an example that demonstrates the use of the USB-C Source Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization driver enables - I2C, set hardware reset and default configuration 
 * and display configuration of the five PDOs, also write log.
 *
 * ## Application Task
 * In this example, we show port status, monitoring, and connections.
 * All data logs write on USB uart changes every 5 sec.
 * 
 * Additional Functions :
 * - void display_port_status ( ) - Display port status info.
 * - void display_monitoring_status ( ) - Display monitoring status info.
 * - void display_connection_status ( ) - Display connection status info.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "usbcsource.h"

static usbcsource_t usbcsource;
static log_t logger;

port_status_t port_status;
monitor_status_t monitor_status;
connection_status_t conn_status;
pdo_config_t pdo_data;

/**
 * @brief USB-C Source display port status.
 * @details This function is used for displaying port status.
 */
void display_port_status ( void );

/**
 * @brief USB-C Source display monitoring status.
 * @details This function is used for displaying monitoring status.
 */
void display_monitoring_status ( void );

/**
 * @brief USB-C Source display connection status.
 * @details This function is used for displaying connection status.
 */
void display_connection_status ( void );

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    usbcsource_cfg_t usbcsource_cfg;  /**< Click config object. */

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
    usbcsource_cfg_setup( &usbcsource_cfg );
    USBCSOURCE_MAP_MIKROBUS( usbcsource_cfg, MIKROBUS_1 );
    err_t init_flag = usbcsource_init( &usbcsource, &usbcsource_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    usbcsource_hw_reset( &usbcsource );
    Delay_ms( 500 );
    usbcsource_default_config( &usbcsource );
    Delay_ms( 500 );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    
    usbcsource_get_pdo_config( &usbcsource, USBCSOURCE_SEL_PDO1, &pdo_data );
    log_printf( &logger, " PDO 1 - Voltage = %.2f V \r\n", pdo_data.vtg_data );
    log_printf( &logger, " PDO 1 - Current = %.2f A \r\n", pdo_data.curr_data );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    
    usbcsource_get_pdo_config( &usbcsource, USBCSOURCE_SEL_PDO2, &pdo_data );
    log_printf( &logger, " PDO 2 - Voltage = %.2f V \r\n", pdo_data.vtg_data );
    log_printf( &logger, " PDO 2 - Current = %.2f A \r\n", pdo_data.curr_data );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    
    usbcsource_get_pdo_config( &usbcsource, USBCSOURCE_SEL_PDO3, &pdo_data );
    log_printf( &logger, " PDO 3 - Voltage = %.2f V \r\n", pdo_data.vtg_data );
    log_printf( &logger, " PDO 3 - Current = %.2f A \r\n", pdo_data.curr_data );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    
    usbcsource_get_pdo_config( &usbcsource, USBCSOURCE_SEL_PDO4, &pdo_data );
    log_printf( &logger, " PDO 4 - Voltage = %.2f V \r\n", pdo_data.vtg_data );
    log_printf( &logger, " PDO 4 - Current = %.2f A \r\n", pdo_data.curr_data );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    
    usbcsource_get_pdo_config( &usbcsource, USBCSOURCE_SEL_PDO5, &pdo_data );
    log_printf( &logger, " PDO 5 - Voltage = %.2f V \r\n", pdo_data.vtg_data );
    log_printf( &logger, " PDO 5 - Current = %.2f A \r\n", pdo_data.curr_data );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) {
    usbcsource_get_port_status( &usbcsource, &port_status );
    display_port_status( );
    Delay_ms( 100 );
    log_printf( &logger, "- - - - - - - - - - - - - - " );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    
    usbcsource_get_monitoring_status( &usbcsource, &monitor_status );
    display_monitoring_status( );
    Delay_ms( 100 );
    log_printf( &logger, "- - - - - - - - - - - - - - " );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    
    usbcsource_get_connection_status( &usbcsource, &conn_status );
    display_connection_status( );
    Delay_ms( 100 );
    log_printf( &logger, "- - - - - - - - - - - - - - " );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    Delay_ms( 5000 );
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

void display_port_status ( void ) {
    log_printf( &logger, " Attached Device   : " );
    
    switch ( port_status.attached_device ) {
        case USBCSOURCE_ATTACHED_DEVICE_NONE_ATT: {
            log_printf( &logger, "No device connected\r\n" );
            break;
        }
        case USBCSOURCE_ATTACHED_DEVICE_SNK_ATT: {
            log_printf( &logger, "Sink device connected\r\n" );
            break;
        }
        case USBCSOURCE_ATTACHED_DEVICE_SRC_ATT: {
            log_printf( &logger, "Source device connected\r\n" );
            break;
        }
        case USBCSOURCE_ATTACHED_DEVICE_DBG_ATT: {
            log_printf( &logger, "Debug accessory device connected\r\n" );
            break;
        }
        case USBCSOURCE_ATTACHED_DEVICE_AUD_ATT: {
            log_printf( &logger, "Audio accessory device connected\r\n" );
            break;
        }
        case USBCSOURCE_ATTACHED_DEVICE_POW_ACC_ATT: {
            log_printf( &logger, "Power accessory device connected\r\n" );
            break;
        }
    }
    
    log_printf( &logger, " Low Power Standby :" ); 
    if ( port_status.low_power_standby == USBCSOURCE_LOW_POWER_STANDBY_ON ) {
        log_printf( &logger, " ON\r\n" );
    } else {
        log_printf( &logger, " OFF\r\n" );
    }

    log_printf( &logger, " Power Mode        :" );
    if ( port_status.power_mode == USBCSOURCE_POWER_MODE_SRC ) {
        log_printf( &logger, " Source\r\n" );
    } else {
        log_printf( &logger, " Sink\r\n" );
    }

    log_printf( &logger, " Data Mode         :" );
    if ( port_status.data_mode == USBCSOURCE_DATA_MODE_DFP ) {
        log_printf( &logger, " DFP\r\n" );
    } else {
        log_printf( &logger, " UFP\r\n" );
    }

    log_printf( &logger, " Attach            :" );
    if ( port_status.attach == USBCSOURCE_CONN_ATTACHED ) {
        log_printf( &logger, " Attached\r\n" );
    } else {
        log_printf( &logger, " Unattached\r\n" );
    }
}

void display_monitoring_status ( void ) {
    log_printf( &logger, " VBUS Ready        :" );
    if ( monitor_status.vbus_ready == USBCSOURCE_VBUS_READY_CONNECTED ) {
        log_printf( &logger, " Connected\r\n" );
    } else {
        log_printf( &logger, " Disconnected\r\n" );
    }

    log_printf( &logger, " VBUS Safe         :" );
    if ( monitor_status.vbus_vsafe0v == USBCSOURCE_VBUS_VSAFE0V_0_8V_LOWER ) {
        log_printf( &logger, " Lower than 0.8V\r\n" );
    } else {
        log_printf( &logger, " Higher than 0.8V\r\n" );
    }

    log_printf( &logger, " VBUS Valid        :" );
    if ( monitor_status.vbus_valid == USBCSOURCE_VBUS_VALID_3_9V_HIGHER ) {
        log_printf( &logger, " Lower than 3.9V\r\n" );
    } else {
        log_printf( &logger, " Higher than 3.9V\r\n" );
    }
}

void display_connection_status ( void ) {
    log_printf( &logger, " Conn. orientation :" );
    if ( conn_status.cc_reverse == 1 ) {
        log_printf( &logger, " Twisted\r\n" );
    } else {
        log_printf( &logger, " Straight\r\n" );
    }

    log_printf( &logger, " Sink Power Level  :" );
    if ( conn_status.snk_power_level == 0 ) {
        log_printf( &logger, " Rp standard current is connected\r\n" );
    } else if ( conn_status.snk_power_level == 1 ) {
        log_printf( &logger, "  Rp 1.5A is connected\r\n" );
    } else {
        log_printf( &logger, "  Rp 3.0A is connected\r\n" );
    }
}

// ------------------------------------------------------------------------ END
