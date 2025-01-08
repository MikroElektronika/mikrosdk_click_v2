
---
# Current Limit Click

> [Current Limit Click](https://www.mikroe.com/?pid_product=MIKROE-4271) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4271&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jul 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This example shows capabilities of Current Limit Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.CurrentLimit

### Example Key Functions

- `currentlimit_cfg_setup` Config Object Initialization function.
```c
void currentlimit_cfg_setup ( currentlimit_cfg_t *cfg );
```

- `currentlimit_init` Initialization function.
```c
err_t currentlimit_init ( currentlimit_t *ctx, currentlimit_cfg_t *cfg );
```

- `currentlimit_dev_enable` Device enable function.
```c
void currentlimit_dev_enable ( currentlimit_t *ctx, uint8_t state );
```

- `currentlimit_set_limit` Set Current With Predefined Values Limit function.
```c
void currentlimit_set_limit ( currentlimit_t *ctx, uint8_t lim_val );
```

- `currentlimit_set_limit_calc` Set Calculated Current Limit function.
```c
void currentlimit_set_limit_calc ( currentlimit_t *ctx, float lim_val );
```

### Application Init

> Initalizes SPI driver and enables the device.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    currentlimit_cfg_t currentlimit_cfg;  /**< Click config object. */

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

    currentlimit_cfg_setup( &currentlimit_cfg );
    CURRENTLIMIT_MAP_MIKROBUS( currentlimit_cfg, MIKROBUS_1 );
    err_t init_flag  = currentlimit_init( &currentlimit, &currentlimit_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    currentlimit_dev_enable( &currentlimit, CURRENTLIMIT_ENABLE );
    log_printf( &logger, "    Click  Enabled!    \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms ( 100 );
    log_info( &logger, " Application Task " );
    display_settings( );
}
```

### Application Task

> Reading users input from USART terminal and using it as an index for an array of pre-calculated values that define current limit level.

```c
void application_task ( void ) 
{
    char inx;
    if ( log_read( &logger, &inx, 1 ) != CURRENTLIMIT_ERROR ) {
        if ( inx >= '1' && inx <= '8' ) {
            currentlimit_set_limit( &currentlimit, lim_val[ inx - 49 ] );
            log_printf( &logger, " Selected mode %d, \r\n Current limit is %d mA \r\n", ( uint16_t ) inx - 48, lim_data[ inx - 49 ] );
            log_printf( &logger, "- - - - - - - - - - - - - - - \r\n" );
        } else { 
            log_printf( &logger, "- - - - - - - - - - - - - - - \r\n" );
            log_printf( &logger, " Data not in range! \r\n" );
            log_printf( &logger, "- - - - - - - - - - - - - - - \r\n" );
            display_settings( );
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
