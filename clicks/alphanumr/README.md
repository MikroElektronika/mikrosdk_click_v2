
---
# AlphaNum R Click

> [AlphaNum R Click](https://www.mikroe.com/?pid_product=MIKROE-1864) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1864&image=1" height=300px>
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
- Click.AlphaNumR

### Example Key Functions

- `alphanumr_cfg_setup` Config Object Initialization function.
```c
void alphanumr_cfg_setup ( alphanumr_cfg_t *cfg );
```

- `alphanumr_init` Initialization function.
```c
err_t alphanumr_init ( alphanumr_t *ctx, alphanumr_cfg_t *cfg );
```

- `alphanumr_default_cfg` Click Default Configuration function.
```c
void alphanumr_default_cfg ( alphanumr_t *ctx );
```

- `alphanumr_write_character` This function displays characters on the left and right LED segments.
```c
void alphanumr_write_character ( alphanumr_t *ctx, uint8_t left_char, uint8_t right_char );
```

- `alphanumr_write_number` This function displays numbers on the left and right LED segments.
```c
void alphanumr_write_number ( alphanumr_t *ctx, uint8_t left_char, uint8_t right_char );
```

### Application Init

> This function initializes and configures the logger and Click modules.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    alphanumr_cfg_t alphanumr_cfg;  /**< Click config object. */

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

    alphanumr_cfg_setup( &alphanumr_cfg );
    ALPHANUMR_MAP_MIKROBUS( alphanumr_cfg, MIKROBUS_1 );
    err_t init_flag  = alphanumr_init( &alphanumr, &alphanumr_cfg );
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
    alphanumr_set_display_interval( &alphanumr, 1000 );

    alphanumr_write_character( &alphanumr, 'M', 'E' );
    alphanumr_write_character( &alphanumr, '@', '?' );

    alphanumr_write_number( &alphanumr, 0,  1 );
    alphanumr_write_number( &alphanumr, 1,  2 );
    alphanumr_write_number( &alphanumr, 2,  3 );
    alphanumr_write_number( &alphanumr, 3,  4 );
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
