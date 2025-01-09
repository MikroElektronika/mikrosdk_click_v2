
---
# OLED W Click

> [OLED W Click](https://www.mikroe.com/?pid_product=MIKROE-1649) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1649&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan  Ilic
- **Date**          : Jun 2021.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use (control) of the OLED W display.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.OLEDW

### Example Key Functions

- `oledw_cfg_setup` Config Object Initialization function.
```c
void oledw_cfg_setup ( oledw_cfg_t *cfg );
```

- `oledw_init` Initialization function.
```c
err_t oledw_init ( oledw_t *ctx, oledw_cfg_t *cfg );
```

- `oledw_send` This function sends commands or data to OLED W Click.
```c
err_t oledw_send( oledw_t *ctx, oledw_data_t tx_data, oledw_data_mode_t data_mode );
```

- `oledw_display_picture` This function allows user to display picture for page addressing mode.
```c
void oledw_display_picture( oledw_t *ctx, oledw_resources_t *pic );
```

- `oledw_set_contrast` This function sets the display contrast level (0 to 255).
```c
void oledw_set_contrast( oledw_t *ctx, oledw_data_t value );
```

### Application Init

> Configures the microcontroller for communication and initializes the Click board to default state.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    oledw_cfg_t oledw_cfg;  /**< Click config object. */

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
    Delay_ms ( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.
    oledw_cfg_setup( &oledw_cfg );
    OLEDW_MAP_MIKROBUS( oledw_cfg, MIKROBUS_1 );
    err_t init_flag  = oledw_init( &oledw, &oledw_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    oledw_default_cfg ( &oledw );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> This section contains the main program that is executed showing a practical example on how to use the implemented functions.

```c
void application_task ( void ) 
{
    uint8_t i;

    oledw_display_picture( &oledw, oledw_img );
    Delay_ms ( 500 );
    oledw_send( &oledw, OLEDW_INVERTDISPLAY, OLEDW_COMMAND );
    Delay_ms ( 500 );
    oledw_send( &oledw, OLEDW_NORMALDISPLAY, OLEDW_COMMAND );
    Delay_ms ( 500 );
    oledw_send( &oledw, OLEDW_INVERTDISPLAY, OLEDW_COMMAND );
    Delay_ms ( 500 );
    oledw_send( &oledw, OLEDW_NORMALDISPLAY, OLEDW_COMMAND );
    Delay_ms ( 300 );

    for (i = 0xAF; i > 0x00; i--) {
        oledw_set_contrast( &oledw, i );
        Delay_ms ( 5 );
    }

    for (i = 0x00; i < 0xAF; i++) {
        oledw_set_contrast( &oledw, i );
        Delay_ms ( 5 );
    }

    oledw_scroll_right( &oledw, 0x00, 0x05 );
    Delay_ms ( 1000 );
    oledw_stop_scroll( &oledw );
    oledw_display_picture( &oledw, oledw_img );

    oledw_scroll_left( &oledw, 0x00, 0x05 );
    Delay_ms ( 1000 );
    oledw_stop_scroll( &oledw );
    oledw_display_picture( &oledw, oledw_img );

    oledw_scroll_diag_right( &oledw, 0x00, 0x05 );
    Delay_ms ( 1000 );
    oledw_stop_scroll( &oledw );
    oledw_display_picture( &oledw, oledw_img );

    oledw_scroll_diag_left( &oledw, 0x00, 0x05 );
    Delay_ms ( 1000 );
    oledw_stop_scroll( &oledw );
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
