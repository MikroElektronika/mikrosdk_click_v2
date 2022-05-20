
---
# Thermostat 2 click

> Thermostat 2 click is a general-purpose thermostat Click board™ designed to be used with any temperature sensor based on the DS1820 sensor design: 3-pin package with 1-Wire® communication interface.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/thermostat2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/thermostat-2-click)

---


#### Click library

- **Author**        : Aleksandra Cvjeticanin 
- **Date**          : Mar 2022.
- **Type**          : One Wire type


# Software Support

We provide a library for the Thermostat 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Thermostat 2 Click driver.

#### Standard key functions :

- `thermostat2_cfg_setup` Config Object Initialization function.
```c
void thermostat2_cfg_setup ( thermostat2_cfg_t *cfg );
```

- `thermostat2_init` Initialization function.
```c
err_t thermostat2_init ( thermostat2_t *ctx, thermostat2_cfg_t *cfg );
```

- `thermostat2_default_cfg` Click Default Configuration function.
```c
err_t thermostat2_default_cfg ( thermostat2_t *ctx );
```

#### Example key functions :

- `thermostat2_read_temperature ` This function reads the temperature value in Celsius.
```c
err_t thermostat2_read_temperature ( thermostat2_t *ctx, float *temperature ); 
```

- `thermostat2_relay_state` This function turns the relay on/off. 
```c
void thermostat2_relay_state ( thermostat2_t *ctx, uint8_t state );
```

## Example Description

> This example demonstrates the use of Thermostat 2 click board by reading
and displaying the temperature in Celsius and turning the relay on/off 
depending on the temperature value.
DS1820, DS18S20 and DS18B20 chips can be used in this example. 

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermostat2_cfg_t thermostat2_cfg;  /**< Click config object. */

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
    thermostat2_cfg_setup( &thermostat2_cfg );
    THERMOSTAT2_MAP_MIKROBUS( thermostat2_cfg, MIKROBUS_1 );
    if ( ONE_WIRE_ERROR == thermostat2_init( &thermostat2, &thermostat2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( THERMOSTAT2_ERROR == thermostat2_default_cfg ( &thermostat2 ) )
    {
        log_error( &logger, " Default config." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads and displays the temperature measured by the click board on the UART Terminal.
If the temperature goes beneath the THERMOSTAT2_TEMPERATURE_LIMIT, 
the relay will be turned off while otherwise it will be turned on. 
In both cases an appropriate message will be displayed on the terminal.  

```c
void application_task ( void ) 
{
    static uint8_t relay_state = 0xFF;
    float temperature;
    
    if ( THERMOSTAT2_OK == thermostat2_read_temperature ( &thermostat2, &temperature ) )
    {
        log_printf( &logger, " Temperature: %.2f C\r\n\n ", temperature );
    }
    
    if ( temperature < THERMOSTAT2_TEMPERATURE_LIMIT )
    {
        if ( relay_state != THERMOSTAT2_RELAY_ON )
        {
            log_info( &logger, " Relay is ON.\r\n " );
            thermostat2_relay_state ( &thermostat2, THERMOSTAT2_RELAY_ON );
            relay_state = THERMOSTAT2_RELAY_ON;
        }
    }
    else 
    {
        if ( relay_state != THERMOSTAT2_RELAY_OFF )
        {
            log_info( &logger, " Relay is OFF.\r\n" );
            thermostat2_relay_state ( &thermostat2, THERMOSTAT2_RELAY_OFF );
            relay_state = THERMOSTAT2_RELAY_OFF;
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermostat2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
