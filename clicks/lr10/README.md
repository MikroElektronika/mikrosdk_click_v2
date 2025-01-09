
---
# LR 10 Click

> [LR 10 Click](https://www.mikroe.com/?pid_product=MIKROE-5986) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5986&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Nov 2023.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of LR 10 Click board 
> by processing the incoming data and displaying them on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LR10

### Example Key Functions

- `lr10_cfg_setup` Config Object Initialization function.
```c
void lr10_cfg_setup ( lr10_cfg_t *cfg );
```

- `lr10_init` Initialization function.
```c
err_t lr10_init ( lr10_t *ctx, lr10_cfg_t *cfg );
```

- `lr10_write_cmd` This function writes a desired command by using UART serial interface.
```c
err_t lr10_write_cmd ( lr10_t *ctx, uint8_t *command );
```

- `lr10_write_cmd_sub_param` This function writes a desired command, subcommands and parameter by using UART serial interface.
```c
err_t lr10_write_cmd_sub_param ( lr10_t *ctx, uint8_t *command, uint8_t *sub_param, 
                                              uint8_t *param, lr10_en_quote_t en_quote );
```

### Application Init

> Initializes the driver and performs a hardware reset of the device
> and a group of commands for getting the FW version, the serial number, and the DevEUI. 
> After that, the demo app sets the RF configuration: 
> frequency, SF, bandwidth, TX preamble, RX preamble, and TX power settings.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lr10_cfg_t lr10_cfg;  /**< Click config object. */

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
    lr10_cfg_setup( &lr10_cfg );
    LR10_MAP_MIKROBUS( lr10_cfg, MIKROBUS_1 );
    if ( UART_ERROR == lr10_init( &lr10, &lr10_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    lr10_hw_reset( &lr10 );
    Delay_ms ( 500 );

    lr10_generic_write( &lr10, LR10_CMD_AT, strlen(LR10_CMD_AT) );
    if ( LR10_OK == lr10_process( &lr10 ) ) 
    {
        lr10_log_app_buf( );
        lr10_clear_app_buf( );
    }
    Delay_ms ( 500 );

    lr10_write_cmd( &lr10, LR10_CMD_VER );
    if ( LR10_OK == lr10_process( &lr10 ) ) 
    {
        lr10_log_app_buf( );
        lr10_clear_app_buf( );
    }
    Delay_ms ( 500 );

    lr10_write_cmd( &lr10, LR10_CMD_ID );
    if ( LR10_OK == lr10_process( &lr10 ) ) 
    {
        lr10_log_app_buf( );
        lr10_clear_app_buf( );
    }
    Delay_ms ( 500 );
    
    lr10_write_cmd_sub_param( &lr10, LR10_CMD_MODE, LR10_SUB_CMD_MODE_TEST, 
                                     LR10_SYMBOL_NULL, LR10_QUOTE_DISABLE );
    if ( LR10_OK == lr10_process( &lr10 ) ) 
    {
        lr10_log_app_buf( );
        lr10_clear_app_buf( );
    }
    Delay_ms ( 500 );

    lr10_write_cmd( &lr10, LR10_CMD_TEST );
    if ( LR10_OK == lr10_process( &lr10 ) ) 
    {
        lr10_log_app_buf( );
        lr10_clear_app_buf( );
    }
    Delay_ms ( 500 );

    lr10_inquire_cmd( &lr10, LR10_CMD_MODE );
    if ( LR10_OK == lr10_process( &lr10 ) ) 
    {
        lr10_log_app_buf( );
        lr10_clear_app_buf( );
    }
    Delay_ms ( 500 );

#ifdef DEMO_APP_TRANSMITTER
    lr10_write_cmd_sub_param( &lr10, LR10_CMD_TEST, LR10_SUB_CMD_TEST_RFCFG, 
                                     "868,SF7,125,8,8,14,ON,OFF,OFF", LR10_QUOTE_DISABLE );
    if ( LR10_OK == lr10_process( &lr10 ) ) 
    {
        lr10_log_app_buf( );
        lr10_clear_app_buf( );
    }
    Delay_ms ( 500 );
#endif  
}
```

### Application Task

> Depending on the selected mode, the application demo receives 
> and processes all incoming data or sends the LoRa packet demo string.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
#ifdef DEMO_APP_TRANSMITTER
    lr10_write_cmd_sub_param( &lr10, LR10_CMD_TEST, LR10_SUB_CMD_TEST_TX_STR, 
                                     LR10_DEMO_STRING, LR10_QUOTE_ENABLE );
    if ( LR10_OK == lr10_process( &lr10 ) ) 
    {
        lr10_log_app_buf( );
        lr10_clear_app_buf( );
    }
#else
    lr10_write_cmd_param( &lr10, LR10_CMD_TEST, LR10_SUB_CMD_TEST_RX );
    if ( LR10_OK == lr10_process( &lr10 ) ) 
    {
        lr10_log_receiver( );
        lr10_clear_app_buf( );
    }
#endif
    Delay_ms ( 1000 );   
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
