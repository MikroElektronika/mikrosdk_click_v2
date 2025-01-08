
---
# AlphaNum G Click

> [AlphaNum G Click](https://www.mikroe.com/?pid_product=MIKROE-1851) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1851&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This example showcases the initialization and configuration of the logger and Click modules and shows how to display characters and numbers on both LED segments of the Click.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.AlphaNumG

### Example Key Functions

- `alphanumg_cfg_setup` Config Object Initialization function.
```c
void alphanumg_cfg_setup ( alphanumg_cfg_t *cfg );
```

- `alphanumg_init` Initialization function.
```c
err_t alphanumg_init ( alphanumg_t *ctx, alphanumg_cfg_t *cfg );
```

- `alphanumg_write_character` This function displays characters on the left and right LED segments.
```c
void alphanumg_write_character ( alphanumg_t *ctx, uint8_t left_char, uint8_t right_char );
```

- `alphanumg_write_number` This function displays numbers on the left and right LED segments.
```c
void alphanumg_write_number ( alphanumg_t *ctx, uint8_t left_char, uint8_t right_char );
```

### Application Init

> This function initializes and configures the logger and Click modules.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    alphanumg_cfg_t alphanumg_cfg;  /**< Click config object. */

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

    alphanumg_cfg_setup( &alphanumg_cfg );
    ALPHANUMG_MAP_MIKROBUS( alphanumg_cfg, MIKROBUS_1 );
    err_t init_flag  = alphanumg_init( &alphanumg, &alphanumg_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> This function sets the time interval at which the symbols are displayed on the LED segments and shows a few characters and numbers.

```c
void application_task ( void ) 
{
    alphanumg_set_display_interval( &alphanumg, 1000 );

    alphanumg_write_character( &alphanumg, 'M', 'E' );
    alphanumg_write_character( &alphanumg, '@', '?' );

    alphanumg_write_number( &alphanumg, 0,  1 );
    alphanumg_write_number( &alphanumg, 1,  2 );
    alphanumg_write_number( &alphanumg, 2,  3 );
    alphanumg_write_number( &alphanumg, 3,  4 );
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
