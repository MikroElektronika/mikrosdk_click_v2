/*!
 * \file 
 * \brief Charger8 Click example
 * 
 * # Description
 * This application is used for charging devices and battery diagnostics
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver init, enable moduele and default configuration,
 * disable ALERT and USB suspand mode and sets max battery capacity
 * 
 * ## Application Task  
 * Reads battery diagnostics and this data logs to USBUART every 1500 ms.
 * 
 * *note:* 
 * The user can charge a battery internally over mikroBUS or externally by supplying the VIN connectors with 5V.
 * For more precise diagnosis and easier tracking of the charging battery status you can set its capacity 
 * - e.g. if you have a 2000mAh battery you can use the "charger8_setMaxBatteryCapacity()" function and pass the parameter for 2000mAh, 
 * by doing this you make the readings more precise.
 * In the example we used only some possibilities of the diagnostics like temperature of the chip during charging,
 * charging current, current battery voltage, current battery capacity and how much the battery is charged in percentage.
 * In case of changing the battery to a different one, it is neccessary to reset the device and set the battery's maximum capacity.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "charger8.h"

// ------------------------------------------------------------------ VARIABLES

static charger8_t charger8;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    charger8_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    charger8_cfg_setup( &cfg );
    CHARGER8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    charger8_init( &charger8, &cfg );

    charger8_enable( &charger8, CHARGER8_CHARGER_ENABLE );
    charger8_default_cfg( &charger8 );
    charger8_reset( &charger8 );

    charger8_set_alert( &charger8, CHARGER8_ALERT_DISABLE );
    charger8_set_usb_suspend( &charger8, CHARGER8_USB_SUSPAND_MODE_DISABLE );
    charger8_set_max_battery_capacity( &charger8, 2000 );
    log_printf( &logger, " --- Charger - Start measurement --- \r\n" );
    
    Delay_ms ( 1000 );
}

void application_task ( void )
{
    //  Task implementation.

    float temperature;
    float current;
    float voltage;
    uint8_t soc;
    uint16_t capacity;
    
    
    log_printf( &logger, " - Battery diagnostics - \r\n" );
    
    temperature = charger8_get_temperature( &charger8 );
    log_printf( &logger, " - Temperature : %f C\r\n", temperature );
    
    current = charger8_get_current( &charger8 );
    log_printf( &logger, " - Current : %f mA\r\n", current);
    
    voltage = charger8_get_voltage( &charger8 );
    log_printf( &logger, " - Voltage : %f mV\r\n", voltage);
    
    capacity = charger8_get_capacity( &charger8 );
    log_printf( &logger, " - Capacity : %d mAh\r\n", capacity );
    
    soc = charger8_get_soc( &charger8 );
    log_printf( &logger, " - SOC : %d %%\r\n", soc );
    
    log_printf( &logger, " -------------------------- \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 500 );
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


// ------------------------------------------------------------------------ END
