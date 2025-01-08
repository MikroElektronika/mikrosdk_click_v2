
---
# LR 9 Click

> [LR 9 Click](https://www.mikroe.com/?pid_product=MIKROE-6038) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6038&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2023.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of LR 9 Click board by processing
> the incoming data and displaying them on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LR9

### Example Key Functions

- `lr9_cfg_setup` Config Object Initialization function.
```c
void lr9_cfg_setup ( lr9_cfg_t *cfg );
```

- `lr9_init` Initialization function.
```c
err_t lr9_init ( lr9_t *ctx, lr9_cfg_t *cfg );
```

- `lr9_send_data_frame` This function sends the desired data frame by using the UART serial interface.
```c
err_t lr9_send_data_frame ( lr9_t *ctx, uint8_t confirm, uint8_t nbtrials, uint8_t *data_frame );
```

- `lr9_inquire_command` Using the UART serial interface, this function writes the desired query command with or without the included equals symbol.
```c
err_t lr9_inquire_command ( lr9_t *ctx, uint8_t *command, lr9_en_set_t en_set );
```

- `lr9_write_command` This function writes a desired command and parameter by using the UART serial interface.
```c
err_t lr9_write_command ( lr9_t *ctx, uint8_t *command, uint8_t *param );
```

### Application Init

> Initializes the driver and performs a hardware reset of the device.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lr9_cfg_t lr9_cfg;  /**< Click config object. */

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
    lr9_cfg_setup( &lr9_cfg );
    LR9_MAP_MIKROBUS( lr9_cfg, MIKROBUS_1 );
    if ( UART_ERROR == lr9_init( &lr9, &lr9_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    lr9_hw_reset( &lr9 );
    Delay_ms ( 500 );

    lr9_inquire_command( &lr9, LR9_CMD_CTXADDRSET, LR9_EQUAL_ENABLE );
    lr9_log_response( );
    Delay_ms ( 500 );

    lr9_inquire_command( &lr9, LR9_CMD_CADDRSET, LR9_EQUAL_ENABLE );
    lr9_log_response( );
    Delay_ms ( 500 );

#ifdef DEMO_APP_TRANSMITTER
    log_printf( &logger, " > Transmitter < \r\n" );
    lr9_write_command( &lr9, LR9_CMD_CTX , LR9_RF_CFG_DEFAULT_TX );
    lr9_log_response( );
    Delay_ms ( 500 );
#else
    log_printf( &logger, " > Receiver < \r\n" );
    lr9_write_command( &lr9, LR9_CMD_CRXS , LR9_RF_CFG_DEFAULT_RX );
    lr9_log_response( );
    Delay_ms ( 500 );
#endif

    lr9_log_response( );
    Delay_ms ( 500 );
}
```

### Application Task

> Depending on the selected mode, the application demo 
> receives and processes all incoming data or sends the LoRa packet demo string.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
#ifdef DEMO_APP_TRANSMITTER
    lr9_send_data_frame( &lr9, LR9_DTRX_CONFIG_DATA, LR9_NB_TRIALS_2, LR9_DEMO_STRING );
    lr9_log_response( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#else
    lr9_log_receiver( );
#endif
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
