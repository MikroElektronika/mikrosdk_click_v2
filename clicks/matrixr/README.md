
---
# Matrix R Click

> [Matrix R Click](https://www.mikroe.com/?pid_product=MIKROE-2245) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2245&image=1" height=300px>
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
- Click.MatrixR

### Example Key Functions

- `matrixr_cfg_setup` Config Object Initialization function.
```c
void matrixr_cfg_setup ( matrixr_cfg_t *cfg );
```

- `matrixr_init` Initialization function.
```c
err_t matrixr_init ( matrixr_t *ctx, matrixr_cfg_t *cfg );
```

- `matrixr_default_cfg` Click Default Configuration function.
```c
void matrixr_default_cfg ( matrixr_t *ctx );
```

- `matrixr_display_characters` This function displays the specified characters on the L/R segments of the Click.
```c
void matrixr_display_characters ( matrixr_t *ctx, uint8_t left_char, uint8_t right_char );
```

- `matrixr_set_csn_high` This function sets the CSN pin output to high.
```c
void matrixr_set_csn_high ( matrixr_t *ctx );
```

- `matrixr_set_csn_low` This function sets the CSN pin output to low.
```c
void matrixr_set_csn_low ( matrixr_t *ctx );
```

### Application Init

> This function initializes and configures the logger and Click modules. After the initialization of the logger module, communication, mikrobus and pin setup, some of the registers are configured in order for the Click module to work properly.

```c
void application_init ( ) 
{
   
    log_cfg_t log_cfg;
    matrixr_cfg_t cfg;

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

    matrixr_cfg_setup( &cfg );
    MATRIXR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    matrixr_init( &matrixr, &cfg );
    Delay_ms ( 100 );
    matrixr_default_cfg( &matrixr );
    Delay_ms ( 100 );
}
```

### Application Task

> This function displays two strings on each of the LED segments, showing one character every second. It should display " Mikroelektronika" on the left one and "Mikroelektronika " on the right.

```c
void application_task ( ) 
{
   
    matrixr_display_characters( &matrixr, ' ', 'M' );
    Delay_ms ( 1000 );
    matrixr_display_characters( &matrixr, 'M', 'i' );
    Delay_ms ( 1000 );
    matrixr_display_characters( &matrixr, 'i', 'k' );
    Delay_ms ( 1000 );
    matrixr_display_characters( &matrixr, 'k', 'r' );
    Delay_ms ( 1000);
    matrixr_display_characters( &matrixr, 'r', 'o' );
    Delay_ms ( 1000 );
    matrixr_display_characters( &matrixr, 'o', 'E' );
    Delay_ms ( 1000 );
    matrixr_display_characters( &matrixr, 'E', 'l' );
    Delay_ms ( 1000 );
    matrixr_display_characters( &matrixr, 'l', 'e' );
    Delay_ms ( 1000 );
    matrixr_display_characters( &matrixr, 'e', 'k' );
    Delay_ms ( 1000 );
    matrixr_display_characters( &matrixr, 'k', 't' );
    Delay_ms ( 1000 );
    matrixr_display_characters( &matrixr, 't', 'r' );
    Delay_ms ( 1000 );
    matrixr_display_characters( &matrixr, 'r', 'o' );
    Delay_ms ( 1000 );
    matrixr_display_characters( &matrixr, 'o', 'n' );
    Delay_ms ( 1000 );
    matrixr_display_characters( &matrixr, 'n', 'i' );
    Delay_ms ( 1000 );
    matrixr_display_characters( &matrixr, 'i', 'k' );
    Delay_ms ( 1000 );
    matrixr_display_characters( &matrixr, 'k', 'a' );
    Delay_ms ( 100 );
    matrixr_display_characters( &matrixr, 'a', ' ' );
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
