/*!
 * @file main.c
 * @brief PoE Source Click example
 *
 * # Description
 * This example demonstrates the use of the PoE Source Click board for
 * Power over Ethernet (PoE) sourcing. The application reads detection
 * and classification results of the connected powered device (PD),
 * as well as voltage, current, and temperature measurements.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and PoE Source Click driver, and applies the
 * default configuration.
 *
 * ## Application Task
 * Reads and parses detection/classification results, measures input
 * voltage, output voltage, output current, and die temperature, and
 * logs the results to the serial terminal.
 *
 * @note
 * Make sure to provide a stable 48V power supply to VIN connector.
 * The black RJ45 connector is for a data-only connection, and the inox one
 * has added power for PoE devices such as wireless access points (WAPs),
 * IP cameras and VoIP phones.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "poesource.h"

#ifndef MIKROBUS_POSITION_POESOURCE
    #define MIKROBUS_POSITION_POESOURCE MIKROBUS_1
#endif

static poesource_t poesource;
static log_t logger;

/**
 * @brief PoE Source parse DET/CLS result function.
 * @details This function parses the DET/CLS result register value and displays it on the USB UART.
 * @param[in] ctx : Click context object.
 * See #poesource_t object definition for detailed explanation.
 * @param[in] det_cls_res : DET/CLS result register value.
 * @return None.
 * @note None.
 */
static void poesource_parse_det_cls_result ( uint8_t det_cls_res );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    poesource_cfg_t poesource_cfg;  /**< Click config object. */

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
    poesource_cfg_setup( &poesource_cfg );
    POESOURCE_MAP_MIKROBUS( poesource_cfg, MIKROBUS_POSITION_POESOURCE );
    if ( I2C_MASTER_ERROR == poesource_init( &poesource, &poesource_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( POESOURCE_ERROR == poesource_default_cfg ( &poesource ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float vin = 0;
    float vout = 0;
    float iout = 0;
    float temperature = 0;
    uint8_t det_cls_res = 0;

    if ( POESOURCE_OK == poesource_read_reg ( &poesource, POESOURCE_REG_DET_CLS_RESULT, &det_cls_res ) )
    {
        poesource_parse_det_cls_result ( det_cls_res );
    }
    if ( POESOURCE_OK == poesource_read_vin ( &poesource, &vin ) )
    {
        log_printf ( &logger, " Vin: %.2f V\r\n", vin );
    }
    if ( POESOURCE_OK == poesource_read_vout ( &poesource, &vout ) )
    {
        log_printf ( &logger, " Vout: %.2f V\r\n", vout );
    }
    if ( POESOURCE_OK == poesource_read_iout ( &poesource, &iout ) )
    {
        log_printf ( &logger, " Iout: %.1f mA\r\n", iout );
    }
    if ( POESOURCE_OK == poesource_read_die_temp ( &poesource, &temperature ) )
    {
        log_printf ( &logger, " Die temperature: %.1f degC\r\n\n", temperature );
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

static void poesource_parse_det_cls_result ( uint8_t det_cls_res )
{
    log_printf ( &logger, " Classification result: " );
    switch ( det_cls_res & POESOURCE_DET_CLS_RESULT_CLSR_MASK )
    {
        case POESOURCE_DET_CLS_RESULT_CLSR_NOT_DONE:
        {
            log_printf ( &logger, "Classification is not done\r\n" );
            break;
        }
        case POESOURCE_DET_CLS_RESULT_CLSR_CLASS_1:
        {
            log_printf ( &logger, "Class 1\r\n" );
            break;
        }
        case POESOURCE_DET_CLS_RESULT_CLSR_CLASS_2:
        {
            log_printf ( &logger, "Class 2\r\n" );
            break;
        }
        case POESOURCE_DET_CLS_RESULT_CLSR_CLASS_3:
        {
            log_printf ( &logger, "Class 3\r\n" );
            break;
        }
        case POESOURCE_DET_CLS_RESULT_CLSR_CLASS_4:
        {
            log_printf ( &logger, "Class 4\r\n" );
            break;
        }
        case POESOURCE_DET_CLS_RESULT_CLSR_CLASS_5:
        {
            log_printf ( &logger, "Class 5\r\n" );
            break;
        }
        case POESOURCE_DET_CLS_RESULT_CLSR_CLASS_0:
        {
            log_printf ( &logger, "Class 0\r\n" );
            break;
        }
        case POESOURCE_DET_CLS_RESULT_CLSR_OC_CONDITION:
        {
            log_printf ( &logger, "OC condition\r\n" );
            break;
        }
        case POESOURCE_DET_CLS_RESULT_CLSR_NOT_MATCH:
        {
            log_printf ( &logger, "The first and secondary class results do not match\r\n" );
            break;
        }
        default:
        {
            log_printf ( &logger, "Unknown\r\n" );
            break;
        }
    }
    log_printf ( &logger, " Detection result: " );
    switch ( det_cls_res & POESOURCE_DET_CLS_RESULT_DETR_MASK )
    {
        case POESOURCE_DET_CLS_RESULT_DETR_NOT_COMPLETED:
        {
            log_printf ( &logger, "Detection has not completed (default after a power-on reset)\r\n" );
            break;
        }
        case POESOURCE_DET_CLS_RESULT_DETR_SHORTED:
        {
            log_printf ( &logger, "The port is shorted (VIN-OUT is below 1.5V)\r\n" );
            break;
        }
        case POESOURCE_DET_CLS_RESULT_DETR_CAP_HIGH:
        {
            log_printf ( &logger, "The detection capacitance (CDET) is too high (exceeds 5uF)\r\n" );
            break;
        }
        case POESOURCE_DET_CLS_RESULT_DETR_RDET_LOW:
        {
            log_printf ( &logger, "The detection resistance (RDET) is too low (below 19kOhm)\r\n" );
            break;
        }
        case POESOURCE_DET_CLS_RESULT_DETR_VALID:
        {
            log_printf ( &logger, "Detection is valid (RDET is between 19kOhm and 26.5kOhm)\r\n" );
            break;
        }
        case POESOURCE_DET_CLS_RESULT_DETR_RDET_HIGH:
        {
            log_printf ( &logger, "RDET is too high (exceeds 26.5kOhm)\r\n" );
            break;
        }
        case POESOURCE_DET_CLS_RESULT_DETR_PORT_OPEN:
        {
            log_printf ( &logger, "The port is open (below 30uA load current)\r\n" );
            break;
        }
        case POESOURCE_DET_CLS_RESULT_DETR_LOW_IMPEDANCE:
        {
            log_printf ( &logger, "Low impedance to PGND (OUT-PGND is below 2V)\r\n" );
            break;
        }
        default:
        {
            log_printf ( &logger, "Unknown\r\n" );
            break;
        }
    }
    if ( POESOURCE_DET_CLS_RESULT_2EVNTC_COMPLETED == ( det_cls_res & POESOURCE_DET_CLS_RESULT_2EVNTC_MASK ) )
    {
        log_printf ( &logger, " Two-event cassification has been completed\r\n" );
    }
}

// ------------------------------------------------------------------------ END
