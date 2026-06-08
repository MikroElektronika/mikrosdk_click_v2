
---
# Thermostat 7 Click

> [Thermostat 7 Click](https://www.mikroe.com/?pid_product=MIKROE-6948) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6948&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : Apr 2026.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Thermostat 7 Click board by reading
and displaying the temperature in Celsius and whether the
temperature limit has been passed.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermostat7

### Example Key Functions

- `thermostat7_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void thermostat7_cfg_setup ( thermostat7_cfg_t *cfg );
```

- `thermostat7_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t thermostat7_init ( thermostat7_t *ctx, thermostat7_cfg_t *cfg );
```

- `thermostat7_default_cfg` This function executes a default configuration of Thermostat 7 Click board.
```c
err_t thermostat7_default_cfg ( thermostat7_t *ctx );
```

- `thermostat7_set_high_limit` This function sets the high alarm temperature limit.
```c
err_t thermostat7_set_high_limit ( thermostat7_t *ctx, float temperature_limit );
```

- `thermostat7_read_temperature` This function reads the temperature value in degrees Celsius.
```c
err_t thermostat7_read_temperature ( thermostat7_t *ctx, float *temperature );
```

- `thermostat7_read_alarm_status` This function reads the current alarm status by reading the temperature data register.
```c
err_t thermostat7_read_alarm_status ( thermostat7_t *ctx, uint8_t *status );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermostat7_cfg_t thermostat7_cfg;  /**< Click config object. */

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
    thermostat7_cfg_setup( &thermostat7_cfg );
    THERMOSTAT7_MAP_MIKROBUS( thermostat7_cfg, MIKROBUS_POSITION_THERMOSTAT7 );
    if ( I2C_MASTER_ERROR == thermostat7_init( &thermostat7, &thermostat7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( THERMOSTAT7_ERROR == thermostat7_default_cfg ( &thermostat7 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_printf( &logger, " HIGH limit   : %.2f C\r\n", THERMOSTAT7_DEFAULT_TEMP_HIGH );
    log_printf( &logger, " LOW limit    : %.2f C\r\n", THERMOSTAT7_DEFAULT_TEMP_LOW );
    log_printf( &logger, " CRIT limit   : %.2f C\r\n", THERMOSTAT7_DEFAULT_TEMP_CRITICAL );

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the temperature and alarm status from the sensor every second
and logs both over UART.

```c
void application_task ( void )
{
    float temperature = 0;
    uint8_t alarm_status = 0;

    if ( THERMOSTAT7_OK == thermostat7_read_temperature( &thermostat7, &temperature ) )
    {
        log_printf( &logger, " Temperature: %.2f C\r\n", temperature );
    }

    if ( THERMOSTAT7_OK == thermostat7_read_alarm_status( &thermostat7, &alarm_status ) )
    {
        if ( THERMOSTAT7_ALARM_NONE == alarm_status )
        {
            log_printf( &logger, " Status: OK - relay is OFF.\r\n\n" );
        }
        else
        {
            if ( alarm_status & THERMOSTAT7_ALARM_TCRIT )
            {
                log_printf( &logger, " Status: CRITICAL - relay is ON.\r\n\n" );
            }
            else if ( alarm_status & THERMOSTAT7_ALARM_HIGH )
            {
                log_printf( &logger, " Status: HIGH alarm - relay is ON.\r\n\n" );
            }
            else if ( alarm_status & THERMOSTAT7_ALARM_LOW )
            {
                log_printf( &logger, " Status: LOW alarm - relay is ON.\r\n\n" );
            }
        }
    }

    Delay_ms( 1000 );
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
