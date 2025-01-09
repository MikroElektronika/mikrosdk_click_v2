
---
# H-Bridge 9 Click

> [H-Bridge 9 Click](https://www.mikroe.com/?pid_product=MIKROE-4821) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4821&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of H-Bridge 9 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HBridge9

### Example Key Functions

- `hbridge9_cfg_setup` Config Object Initialization function.
```c
void hbridge9_cfg_setup ( hbridge9_cfg_t *cfg );
```

- `hbridge9_init` Initialization function.
```c
err_t hbridge9_init ( hbridge9_t *ctx, hbridge9_cfg_t *cfg );
```

- `hbridge9_default_cfg` Click Default Configuration function.
```c
err_t hbridge9_default_cfg ( hbridge9_t *ctx );
```

- `hbridge9_write_register` This function writes a desired data to the selected register.
```c
err_t hbridge9_write_register ( hbridge9_t *ctx, uint8_t reg, uint16_t data_in );
```

- `hbridge9_read_register` This function reads a desired data from the selected register.
```c
err_t hbridge9_read_register ( hbridge9_t *ctx, uint8_t reg, uint16_t *data_out );
```

- `hbridge9_send_actuation_pulse` This function sends an actuation pulse by toggling the ENO pin.
```c
void hbridge9_send_actuation_pulse ( hbridge9_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration which will set the OUT1 to LOW, OUT2 to HIGH polarity, and the runtime to 1000ms.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;            /**< Logger config object. */
    hbridge9_cfg_t hbridge9_cfg;  /**< Click config object. */

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

    hbridge9_cfg_setup( &hbridge9_cfg );
    HBRIDGE9_MAP_MIKROBUS( hbridge9_cfg, MIKROBUS_1 );
    err_t init_flag = hbridge9_init( &hbridge9, &hbridge9_cfg );
    if ( SPI_MASTER_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    init_flag = hbridge9_default_cfg ( &hbridge9 );
    if ( HBRIDGE9_ERROR == init_flag )
    {
        log_error( &logger, " Default Config Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Sends an actuation pulse every 5 seconds which will run the motor for a certain amount of time as set by default configuration.

```c
void application_task ( void )
{
    hbridge9_send_actuation_pulse( &hbridge9 );
    log_printf( &logger, " Actuation pulse has been sent. \r\n\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Note

> The Voltage should be supplied with 6 to 18V power supply. Make sure to use a motor that operates in the above voltage range.

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
