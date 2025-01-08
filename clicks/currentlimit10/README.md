
---
# Current Limit 10 Click

> [Current Limit 10 Click](https://www.mikroe.com/?pid_product=MIKROE-5938) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5938&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Oct 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for the Current Limit 10 Click driver.
> This driver provides the functions to set the current limiting conditions 
> in order to provide the threshold of the fault conditions.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.CurrentLimit10

### Example Key Functions

- `currentlimit10_cfg_setup` Config Object Initialization function.
```c
void currentlimit10_cfg_setup ( currentlimit10_cfg_t *cfg );
```

- `currentlimit10_init` Initialization function.
```c
err_t currentlimit10_init ( currentlimit10_t *ctx, currentlimit10_cfg_t *cfg );
```

- `currentlimit10_default_cfg` Click Default Configuration function.
```c
err_t currentlimit10_default_cfg ( currentlimit10_t *ctx );
```

- `currentlimit10_set_limit` This function sets the desired current limit threshold using the I2C serial interface.
```c
err_t currentlimit10_set_limit ( currentlimit10_t *ctx, float current_limit );
```

- `currentlimit10_get_fault` This function gets the state of the fault flag to indicate overcurrent, overtemperature, or reverse-voltage conditions.
```c
uint8_t currentlimit10_get_fault ( currentlimit10_t *ctx );
```

- `currentlimit10_enable` This function turns on the power switch and enables the internal MOSFET.
```c
void currentlimit10_enable ( currentlimit10_t *ctx );
```

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization, the app executes a default configuration
> and and sets the current limit threshold of 750 mA.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    currentlimit10_cfg_t currentlimit10_cfg;  /**< Click config object. */

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
    currentlimit10_cfg_setup( &currentlimit10_cfg );
    CURRENTLIMIT10_MAP_MIKROBUS( currentlimit10_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == currentlimit10_init( &currentlimit10, &currentlimit10_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CURRENTLIMIT10_ERROR == currentlimit10_default_cfg ( &currentlimit10 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    if ( CURRENTLIMIT10_ERROR == currentlimit10_set_limit( &currentlimit10, 0.75 ) )
    {
        log_error( &logger, " Current limit threshold." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the Current Limit 10 Click board. 
> The demo application checks the fault flag for overcurrent conditions.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    if ( CURRENTLIMIT10_FAULT_FLAG == currentlimit10_get_fault( &currentlimit10 ) )
    {
        log_printf( &logger, "Fault flag: Overcurrent\r\n" );
    }
    else
    {
        log_printf( &logger, " Current limit is 0.75 A\r\n" );
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
