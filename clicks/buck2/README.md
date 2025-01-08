
---
# Buck 2 Click

> [Buck 2 Click](https://www.mikroe.com/?pid_product=MIKROE-2911) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2911&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Katarina Perendic
- **Date**          : nov 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> This application demonstrates the use of Buck 2 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Buck2

### Example Key Functions

- `buck2_cfg_setup` Config Object Initialization function. 
```c
void buck2_cfg_setup ( buck2_cfg_t *cfg );
``` 
 
- `buck2_init` Initialization function. 
```c
err_t buck2_init ( buck2_t *ctx, buck2_cfg_t *cfg );
```

- `buck2_default_cfg` Click Default Configuration function. 
```c
void buck2_default_cfg ( buck2_t *ctx );
```

- `buck2_set_output_voltage` Function settings output voltage. 
```c
void buck2_set_output_voltage( buck2_t *ctx , uint8_t voltage );
```
 
- `buck2_get_power_good` Function reads state PG pin. 
```c
uint8_t buck2_get_power_good( buck2_t *ctx  );
```

- `buck2_set_power_mode` Function settings chip mode. 
```c
void buck2_set_power_mode( buck2_t *ctx, uint8_t mode );
```

### Application Init

> Initializes the driver and configures the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    buck2_cfg_t cfg;

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

    buck2_cfg_setup( &cfg );
    BUCK2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buck2_init( &buck2, &cfg );

    buck2_default_cfg( &buck2 );
}
```

### Application Task

> Sets a different output voltage every 5 seconds then checks if the voltage on 
> the output (OUTSNS) drops under 90% of the regulated voltage 
> and displays an appropriate message on USB UART.

```c
void application_task ( void )
{
    uint8_t pg_state;

    buck2_set_output_voltage( &buck2, BUCK2_SET_VOLTAGE_3300mV );
    log_printf( &logger, "---- Output voltage is 3300 mV ----\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    pg_state = buck2_get_power_good( &buck2 );
    if ( pg_state == 0 )
    {
        log_info( &logger, "---- Voltage of the output dropped under 90%% of the regulated voltage ----" );
    }
    buck2_set_output_voltage( &buck2, BUCK2_SET_VOLTAGE_2500mV );
    log_printf( &logger, "---- Output voltage is 2500 mV ----\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    pg_state = buck2_get_power_good( &buck2 );
    if ( pg_state == 0 )
    {
        log_info( &logger, "---- Voltage of the output dropped under 90%% of the regulated voltage ----" );
    }
    buck2_set_output_voltage( &buck2, BUCK2_SET_VOLTAGE_1800mV );
    log_printf( &logger, "---- Output voltage is 1800 mV ----\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    pg_state = buck2_get_power_good( &buck2 );
    if ( pg_state == 0 )
    {
        log_info( &logger, "---- Voltage of the output dropped under 90%% of the regulated voltage ----" );
    }
    buck2_set_output_voltage( &buck2, BUCK2_SET_VOLTAGE_1500mV );
    log_printf( &logger, "---- Output voltage is 1500 mV ----\r\n" );
    log_printf( &logger, "-----------------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    pg_state = buck2_get_power_good( &buck2 );
    if ( pg_state == 0 )
    {
        log_info( &logger, "---- Voltage of the output dropped under 90%% of the regulated voltage ----" );
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
