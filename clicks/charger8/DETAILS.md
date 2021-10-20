

---
# Charger 8 click

Charger 8 Click is an intelligent Li-Ion battery charger, system power manager, and a battery fuel gauge Click board.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/charger8_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/charger-8-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Nov 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Charger8 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https:///shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https:///shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Charger8 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void charger8_cfg_setup ( charger8_cfg_t *cfg ); 
 
- Initialization function.
> CHARGER8_RETVAL charger8_init ( charger8_t *ctx, charger8_cfg_t *cfg );

- Click Default Configuration function.
> void charger8_default_cfg ( charger8_t *ctx );


#### Example key functions :

- Functions for read Temperature of the chip
> float charger8_get_temperature ( charger8_t *ctx );
 
- Function for reads the current capacity of the battery
> uint16_t charger8_get_capacity ( charger8_t *ctx );

- Function for reads the Status register
> uint16_t charger8_get_status ( charger8_t *ctx );

## Examples Description

> This application is used for charging devices and battery diagnostics

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver init, enable moduele and default configuration,
> disable ALERT and USB suspand mode and sets max battery capacity

```c

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
    charger8_set_max_battery_capacity( 2000 );
    log_printf( &logger, " --- Charger - Start measurement --- \r\n" );
    Delay_ms( 1000 );
}
  
```

### Application Task

> Reads battery diagnostics and this data logs to USBUART every 1500 ms.

```c

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
    Delay_ms( 1500 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Charger8

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https:///shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https:///shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https:///shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https:///shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
