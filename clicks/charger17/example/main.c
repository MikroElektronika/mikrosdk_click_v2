/*!
 * @file main.c
 * @brief Charger 17 Click example
 *
 * # Description
 * This example demonstrates the use of Charger 17 Click board by enabling battery charging and
 * displaying the charging status.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration which enables charging.
 *
 * ## Application Task
 * Reads and displays the battery charging status (IC_STATUS and STAT0 regs) on the USB UART
 * approximately once per second.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "charger17.h"

static charger17_t charger17;
static log_t logger;

/**
 * @brief Charger 17 parse ic status function.
 * @details This function parses and displays on the USB UART the IC_STATUS register value from input.
 * @param[in] ic_status : IC status register data.
 * @return None.
 * @note None.
 */
static void charger17_parse_ic_status ( uint8_t ic_status );

/**
 * @brief Charger 17 parse status 0 function.
 * @details This function parses and displays on the USB UART the STAT0 register value from input.
 * @param[in] status_0 : STAT0 register data.
 * @return None.
 * @note None.
 */
static void charger17_parse_status_0 ( uint8_t status_0 );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    charger17_cfg_t charger17_cfg;  /**< Click config object. */

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
    charger17_cfg_setup( &charger17_cfg );
    CHARGER17_MAP_MIKROBUS( charger17_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == charger17_init( &charger17, &charger17_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CHARGER17_ERROR == charger17_default_cfg ( &charger17 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint8_t ic_status, status_0;
    if ( CHARGER17_OK == charger17_read_register ( &charger17, CHARGER17_REG_IC_STATUS, &ic_status ) )
    {
        charger17_parse_ic_status ( ic_status );
    }
    if ( CHARGER17_OK == charger17_read_register ( &charger17, CHARGER17_REG_STAT0, &status_0 ) )
    {
        charger17_parse_status_0 ( status_0 );
    }
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

static void charger17_parse_ic_status ( uint8_t ic_status )
{
    log_printf ( &logger, "\r\n IC status\r\n" );
    log_printf ( &logger, "   PORT: " );
    switch ( ic_status & CHARGER17_PORT_STAT_BIT_MASK )
    {
        case CHARGER17_PORT_STAT_VBUS_DEV_1:
        {
            log_printf ( &logger, "VBUS = device 1 (2100mA-APPLE-10w)\r\n" );
            break;
        }
        case CHARGER17_PORT_STAT_VBUS_DEV_2:
        {
            log_printf ( &logger, "VBUS = device 2 (2000mA-SAMSUNG-10w)\r\n" );
            break;
        }
        case CHARGER17_PORT_STAT_VBUS_DEV_3:
        {
            log_printf ( &logger, "VBUS = device 3 (1000mA-APPLE-5w)\r\n" );
            break;
        }
        case CHARGER17_PORT_STAT_VBUS_DEV_4:
        {
            log_printf ( &logger, "VBUS = device 4 (2400mA-APPLE-12w)\r\n" );
            break;
        }
        case CHARGER17_PORT_STAT_VBUS_UNKNOWN:
        {
            log_printf ( &logger, "VBUS = unknown / NSDP (500mA)\r\n" );
            break;
        }
        case CHARGER17_PORT_STAT_VBUS_SDP:
        {
            log_printf ( &logger, "VBUS = SDP (500mA) / PSEL = High\r\n" );
            break;
        }
        case CHARGER17_PORT_STAT_VBUS_CDP:
        {
            log_printf ( &logger, "VBUS = CDP (1500mA)\r\n" );
            break;
        }
        case CHARGER17_PORT_STAT_VBUS_DCP:
        {
            log_printf ( &logger, "VBUS = DCP (2400mA) / PSEL = Low\r\n" );
            break;
        }
        default:
        {
            log_printf ( &logger, "No information\r\n" );
            break;
        }
    }
    log_printf ( &logger, "   IC: " );
    switch ( ic_status & CHARGER17_IC_STAT_BIT_MASK )
    {
        case CHARGER17_IC_STAT_HZ_SLEEP:
        {
            log_printf ( &logger, "HZ/SLEEP\r\n" );
            break;
        }
        case CHARGER17_IC_STAT_VBUS_READY:
        {
            log_printf ( &logger, "VBUS ready for charge\r\n" );
            break;
        }
        case CHARGER17_IC_STAT_TRICKLE_CHG:
        {
            log_printf ( &logger, "Trickle-charge\r\n" );
            break;
        }
        case CHARGER17_IC_STAT_PRE_CHG:
        {
            log_printf ( &logger, "Pre-charge\r\n" );
            break;
        }
        case CHARGER17_IC_STAT_FAST_CHG:
        {
            log_printf ( &logger, "Fast-charge\r\n" );
            break;
        }
        case CHARGER17_IC_STAT_IEOC_CHG:
        {
            log_printf ( &logger, "IEOC-charge (EOC and TE = 0)\r\n" );
            break;
        }
        case CHARGER17_IC_STAT_BACK_GROUND_CHG:
        {
            log_printf ( &logger, "Back-Ground charge (EOC and TE = 1 and before turn off power path)\r\n" );
            break;
        }
        case CHARGER17_IC_STAT_CHG_DONE:
        {
            log_printf ( &logger, "Charge done (EOC and TE = 1 and power path off)\r\n" );
            break;
        }
        case CHARGER17_IC_STAT_CHG_FAULT:
        {
            log_printf ( &logger, "Charge fault (VAC_OV/CHG_BUSUV/CHG_TOUT/CHG_SYSOV/CHG_BATOV/JEITA_HOT/JEITA_COLD/OTP)\r\n" );
            break;
        }
        case CHARGER17_IC_STAT_OTG:
        {
            log_printf ( &logger, "OTG\r\n" );
            break;
        }
        default:
        {
            log_printf ( &logger, "No information\r\n" );
            break;
        }
    }
}

static void charger17_parse_status_0 ( uint8_t status_0 )
{
    log_printf ( &logger, "\r\n Status 0\r\n" );
    log_printf ( &logger, "   VBUS_GD: VBUS %s good\r\n", 
                 ( char * ) ( ( status_0 & CHARGER17_STAT0_VBUS_GD ) ? "is" : "is not" ) );
    log_printf ( &logger, "   CHG_RDY: VBUS %s ready for charging\r\n", 
                 ( char * ) ( ( status_0 & CHARGER17_STAT0_CHG_RDY ) ? "is" : "is not" ) );
    log_printf ( &logger, "   IEOC: %s in EOC\r\n", 
                 ( char * ) ( ( status_0 & CHARGER17_STAT0_IEOC ) ? "While" : "Not in" ) );
    log_printf ( &logger, "   BG_CHG: %s\r\n", 
                 ( char * ) ( ( status_0 & CHARGER17_STAT0_BG_CHG ) ? "While in EOC state and TE = 1 and BG_CHG_TMR != 00" : 
                                                                      "Not in EOC state or TE = 0 or BG_CHG_TMR = 00" ) );
    log_printf ( &logger, "   CHG_DONE: %s\r\n", 
                 ( char * ) ( ( status_0 & CHARGER17_STAT0_CHG_DONE ) ? "While in EOC state and BATFET off" : 
                                                                        "Not in EOC state or BATFET on" ) );
    log_printf ( &logger, "   BC12_DONE: BC1.2 process %s\r\n", 
                 ( char * ) ( ( status_0 & CHARGER17_STAT0_BC12_DONE ) ? "done" : "not ready" ) );
}

// ------------------------------------------------------------------------ END
