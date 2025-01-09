
---
# Thermostat 2 Click

> [Thermostat 2 Click](https://www.mikroe.com/?pid_product=MIKROE-3415) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3415&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Aleksandra Cvjeticanin 
- **Date**          : Mar 2022.
- **Type**          : One Wire type

# Software Support

## Example Description

> This example demonstrates the use of Thermostat 2 Click board by reading
and displaying the temperature in Celsius and turning the relay on/off 
depending on the temperature value.
DS1820, DS18S20 and DS18B20 chips can be used in this example. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermostat2

### Example Key Functions

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

- `thermostat2_read_temperature ` This function reads the temperature value in Celsius.
```c
err_t thermostat2_read_temperature ( thermostat2_t *ctx, float *temperature ); 
```

- `thermostat2_relay_state` This function turns the relay on/off. 
```c
void thermostat2_relay_state ( thermostat2_t *ctx, uint8_t state );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

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

> Reads and displays the temperature measured by the Click board on the UART Terminal.
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

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
