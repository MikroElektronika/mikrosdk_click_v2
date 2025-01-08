
---
# Printer Click

> [Printer Click](https://www.mikroe.com/?pid_product=MIKROE-6460) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6460&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2024.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of Printer Click board by providing user interaction
with a thermal printer, allowing the user to check paper status, display commands,
and execute various printing tasks based on user commands through a UART interface.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Printer

### Example Key Functions

- `printer_cfg_setup` Config Object Initialization function.
```c
void printer_cfg_setup ( printer_cfg_t *cfg );
```

- `printer_init` Initialization function.
```c
err_t printer_init ( printer_t *ctx, printer_cfg_t *cfg );
```

- `printer_default_cfg` Click Default Configuration function.
```c
err_t printer_default_cfg ( printer_t *ctx );
```

- `printer_get_status` This function reads the paper status and temperature of the printer and stores results in ctx->status string buffer.
```c
err_t printer_get_status ( printer_t *ctx );
```

- `printer_get_fw_info` This function reads the firmware information of the printer and stores results in ctx->fw_info string buffer.
```c
err_t printer_get_fw_info ( printer_t *ctx );
```

- `printer_print_string_lf` This function prints a string message with line feed.
```c
err_t printer_print_string_lf ( printer_t *ctx, char *data_in );
```

### Application Init

> Initializes the driver, performs the Click default configuration, and displays the list of supported commands on the USB UART.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    printer_cfg_t printer_cfg;  /**< Click config object. */

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
    printer_cfg_setup( &printer_cfg );
    PRINTER_MAP_MIKROBUS( printer_cfg, MIKROBUS_1 );
    if ( UART_ERROR == printer_init( &printer, &printer_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PRINTER_ERROR == printer_default_cfg ( &printer ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    printer_display_commands ( );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Checks the paper status and processes user commands.

```c
void application_task ( void )
{
    uint8_t command = 0;
    printer_check_paper ( &printer );
    if ( 1 == log_read ( &logger, &command, 1 ) ) 
    {
        printer_parse_command ( &printer, command );
    }
}
```

### Note

> The default printer head type is set to LTP02-245-13.

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
