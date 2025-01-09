
---
# Matrix G Click

> [Matrix G Click](https://www.mikroe.com/?pid_product=MIKROE-2246) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2246&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Jelena Milosavljevic
- **Date**          : Jun 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This example showcases how to prepare the logger and Click modules for use and how to display ASCII characters on both of the LED segments of the Click.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.MatrixG

### Example Key Functions

- `matrixg_cfg_setup` Config Object Initialization function.
```c
void matrixg_cfg_setup ( matrixg_cfg_t *cfg );
```

- `matrixg_init` Initialization function.
```c
err_t matrixg_init ( matrixg_t *ctx, matrixg_cfg_t *cfg );
```

- `matrixg_default_cfg` Click Default Configuration function.
```c
void matrixg_default_cfg ( matrixg_t *ctx );
```

- `matrixg_display_characters` This function displays the specified characters on the L/R segments of the Click.
```c
void matrixg_display_characters ( matrixg_t *ctx, uint8_t left_char, uint8_t right_char );
```

- `matrixg_set_csn_high` This function sets the CSN pin output to high.
```c
void matrixg_set_csn_high ( matrixg_t *ctx );
```

- `matrixg_set_csn_low` This function sets the CSN pin output to low.
```c
void matrixg_set_csn_low ( matrixg_t *ctx );
```

### Application Init

> This function initializes and configures the logger and Click modules. After the initialization of the logger module, communication, mikrobus and pin setup, some of the registers are configured in order for the Click module to work properly.

```c
void application_init ( ) 
{
   
    log_cfg_t log_cfg;
    matrixg_cfg_t cfg;

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

    matrixg_cfg_setup( &cfg );
    MATRIXG_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    matrixg_init( &matrixg, &cfg );
    Delay_ms ( 100 );
    matrixg_default_cfg( &matrixg );
    Delay_ms ( 100 );
}
```

### Application Task

> This function displays two strings on each of the LED segments, showing one character every second. It should display " Mikroelektronika" on the left one and "Mikroelektronika " on the right.

```c
void application_task ( ) 
{
   
    matrixg_display_characters( &matrixg, ' ', 'M' );
    Delay_ms ( 1000 );
    matrixg_display_characters( &matrixg, 'M', 'i' );
    Delay_ms ( 1000 );
    matrixg_display_characters( &matrixg, 'i', 'k' );
    Delay_ms ( 1000 );
    matrixg_display_characters( &matrixg, 'k', 'r' );
    Delay_ms ( 1000);
    matrixg_display_characters( &matrixg, 'r', 'o' );
    Delay_ms ( 1000 );
    matrixg_display_characters( &matrixg, 'o', 'E' );
    Delay_ms ( 1000 );
    matrixg_display_characters( &matrixg, 'E', 'l' );
    Delay_ms ( 1000 );
    matrixg_display_characters( &matrixg, 'l', 'e' );
    Delay_ms ( 1000 );
    matrixg_display_characters( &matrixg, 'e', 'k' );
    Delay_ms ( 1000 );
    matrixg_display_characters( &matrixg, 'k', 't' );
    Delay_ms ( 1000 );
    matrixg_display_characters( &matrixg, 't', 'r' );
    Delay_ms ( 1000 );
    matrixg_display_characters( &matrixg, 'r', 'o' );
    Delay_ms ( 1000 );
    matrixg_display_characters( &matrixg, 'o', 'n' );
    Delay_ms ( 1000 );
    matrixg_display_characters( &matrixg, 'n', 'i' );
    Delay_ms ( 1000 );
    matrixg_display_characters( &matrixg, 'i', 'k' );
    Delay_ms ( 1000 );
    matrixg_display_characters( &matrixg, 'k', 'a' );
    Delay_ms ( 100 );
    matrixg_display_characters( &matrixg, 'a', ' ' );
    Delay_ms ( 100 );
}
```

### Note

> The Click has two chips, each controlling one of the LED segments, on and requires you to write data to both at the same time. Writing to one specific chip will not work. If you wish to display characters on a single segment, you have to send ' ' characters to the other segment.

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
