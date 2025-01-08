
---
# Current Limit 5 Click

> [Current Limit 5 Click](https://www.mikroe.com/?pid_product=MIKROE-4999) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4999&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Current Limit 5 Click board by limiting
the current to a certain value and displaying an appropriate message when the current reaches the limit.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.CurrentLimit5

### Example Key Functions

- `currentlimit5_cfg_setup` Config Object Initialization function.
```c
void currentlimit5_cfg_setup ( currentlimit5_cfg_t *cfg );
```

- `currentlimit5_init` Initialization function.
```c
err_t currentlimit5_init ( currentlimit5_t *ctx, currentlimit5_cfg_t *cfg );
```

- `currentlimit5_set_ilimit` This function sets the current limit value by configuring the onboard digital potentiometer.
```c
err_t currentlimit5_set_ilimit ( currentlimit5_t *ctx, currentlimit5_ilimit_t ilimit );
```

- `currentlimit5_get_fault_pin` This function returns the fault pin logic state.
```c
uint8_t currentlimit5_get_fault_pin ( currentlimit5_t *ctx );
```

- `currentlimit5_enable_limit` This function enables the current limiting switch.
```c
void currentlimit5_enable_limit ( currentlimit5_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration which sets the current limit to 200mA.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    currentlimit5_cfg_t currentlimit5_cfg;  /**< Click config object. */

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
    currentlimit5_cfg_setup( &currentlimit5_cfg );
    CURRENTLIMIT5_MAP_MIKROBUS( currentlimit5_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == currentlimit5_init( &currentlimit5, &currentlimit5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CURRENTLIMIT5_ERROR == currentlimit5_default_cfg ( &currentlimit5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Displays the fault indicator state on the USB UART.

```c
void application_task ( void )
{
    static uint8_t currentlimit_ind = 2;
    if ( currentlimit5_get_fault_pin ( &currentlimit5 ) )
    {
        if ( currentlimit_ind != 0 )
        {
            log_printf ( &logger, " The switch is in normal operation \r\n\n" );
            currentlimit_ind = 0;
        }
    }
    else
    {
        if ( currentlimit_ind != 1 )
        {
            log_printf ( &logger, " The switch is in the current limiting or thermal shutdown operation \r\n\n" );
            currentlimit_ind = 1;
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
