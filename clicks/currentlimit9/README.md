
---
# Current Limit 9 Click

> [Current Limit 9 Click](https://www.mikroe.com/?pid_product=MIKROE-5937) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5937&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Oct 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for the Current Limit 9 Click driver.
> This driver provides the functions to set the current limiting conditions 
> in order to provide the threshold of the fault conditions.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.CurrentLimit9

### Example Key Functions

- `currentlimit9_cfg_setup` Config Object Initialization function.
```c
void currentlimit9_cfg_setup ( currentlimit9_cfg_t *cfg );
```

- `currentlimit9_init` Initialization function.
```c
err_t currentlimit9_init ( currentlimit9_t *ctx, currentlimit9_cfg_t *cfg );
```

- `currentlimit9_default_cfg` Click Default Configuration function.
```c
err_t currentlimit9_default_cfg ( currentlimit9_t *ctx );
```

- `currentlimit9_set_limit` This function sets the desired current limit threshold using the I2C serial interface.
```c
err_t currentlimit9_set_limit ( currentlimit9_t *ctx, currentlimit9_limit_t current_limit );
```

- `currentlimit9_get_fault` This function gets the state of the fault flag to indicate overcurrent, overtemperature, or reverse-voltage conditions.
```c
uint8_t currentlimit9_get_fault ( currentlimit9_t *ctx );
```

- `currentlimit9_enable` This function turns on the power switch and enables the internal MOSFET.
```c
void currentlimit9_enable ( currentlimit9_t *ctx );
```

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization, the app executes a default configuration
> and sets the current limit threshold of 460 mA.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    currentlimit9_cfg_t currentlimit9_cfg;  /**< Click config object. */

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
    currentlimit9_cfg_setup( &currentlimit9_cfg );
    CURRENTLIMIT9_MAP_MIKROBUS( currentlimit9_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == currentlimit9_init( &currentlimit9, &currentlimit9_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CURRENTLIMIT9_ERROR == currentlimit9_default_cfg ( &currentlimit9 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    if ( CURRENTLIMIT9_ERROR == currentlimit9_set_limit( &currentlimit9, CURRENTLIMIT9_LIMIT_0_46_A ) )
    {
        log_error( &logger, " Current limit threshold." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the Current Limit 9 Click board. 
> The demo application checks the fault flag for overcurrent conditions.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    if ( CURRENTLIMIT9_FAULT_FLAG == currentlimit9_get_fault( &currentlimit9 ) )
    {
        log_printf( &logger, "Fault flag: Overcurrent\r\n" );
    }
    else
    {
        log_printf( &logger, " Current limit is 460 mA\r\n" );
    }
    Delay_ms ( 1000 );
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
