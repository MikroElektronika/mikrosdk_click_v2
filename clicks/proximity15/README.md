
---
# Proximity 15 Click

> [Proximity 15 Click](https://www.mikroe.com/?pid_product=MIKROE-4822) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4822&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Proximity 15 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity15

### Example Key Functions

- `proximity15_cfg_setup` Config Object Initialization function.
```c
void proximity15_cfg_setup ( proximity15_cfg_t *cfg );
```

- `proximity15_init` Initialization function.
```c
err_t proximity15_init ( proximity15_t *ctx, proximity15_cfg_t *cfg );
```

- `proximity15_default_cfg` Click Default Configuration function.
```c
err_t proximity15_default_cfg ( proximity15_t *ctx );
```

- `proximity15_get_distance` This function waits for the data ready, then reads the distance measured by the sensor in milimeters and clears interrupts.
```c
err_t proximity15_get_distance ( proximity15_t *ctx, uint16_t *distance );
```

- `proximity15_set_inter_measurement_period` This function programs the inter measurement period in miliseconds.
```c
err_t proximity15_set_inter_measurement_period ( proximity15_t *ctx, uint16_t time_ms );
```

- `proximity15_set_timing_budget` This function programs the timing budget in miliseconds.
```c
err_t proximity15_set_timing_budget ( proximity15_t *ctx, proximity15_timing_budget_t time );
```

### Application Init

> Initializes the driver and performs the Click default configuration which 
enables the sensor and sets it to long distance mode with 50ms timing budget and 100ms inter measurement periods.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;                  /**< Logger config object. */
    proximity15_cfg_t proximity15_cfg;  /**< Click config object. */

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
    proximity15_cfg_setup( &proximity15_cfg );
    PROXIMITY15_MAP_MIKROBUS( proximity15_cfg, MIKROBUS_1 );
    err_t init_flag = proximity15_init( &proximity15, &proximity15_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    init_flag = proximity15_default_cfg ( &proximity15 );
    if ( PROXIMITY15_ERROR == init_flag ) 
    {
        log_error( &logger, " Default Config Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the distance measured by the sensor in milimeters and displays the value on the USB UART approximately every 100ms.

```c
void application_task ( void )
{
    uint16_t distance = 0;
    
    if ( PROXIMITY15_OK == proximity15_get_distance ( &proximity15, &distance ) )
    {
        log_printf( &logger, " Distance(mm): %u\r\n\n", distance );
    }
}
```

### Note

> In order to measure longer distance, increase the timing budget and inter measurement periods.

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
