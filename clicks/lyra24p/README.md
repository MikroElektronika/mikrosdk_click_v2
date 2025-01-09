
---
# LYRA 24P Click

> [LYRA 24P Click](https://www.mikroe.com/?pid_product=MIKROE-6021) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6021&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Nov 2023.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of LYRA 24P Click board by processing
> the incoming data and displaying them on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LYRA24P

### Example Key Functions

- `lyra24p_cfg_setup` Config Object Initialization function.
```c
void lyra24p_cfg_setup ( lyra24p_cfg_t *cfg );
```

- `lyra24p_init` Initialization function.
```c
err_t lyra24p_init ( lyra24p_t *ctx, lyra24p_cfg_t *cfg );
```

- `lyra24p_write_command` This function writes a desired command by using UART serial interface.
```c
err_t lyra24p_write_command ( lyra24p_t *ctx, uint8_t *command );
```

- `lyra24p_write_cmd_param` This function writes a desired command, command value, prefix and parameter by using UART serial interface.
```c
err_t lyra24p_write_cmd_param ( lyra24p_t *ctx, uint8_t *command, uint8_t *cmd_val, uint8_t *prefix, uint8_t *param );
```

- `lyra24p_inquire_command` This function writes a desired inquire command, command value and enable/disable quote by using UART serial interface.
```c
err_t lyra24p_inquire_command ( lyra24p_t *ctx, uint8_t *command, uint8_t *cmd_val, uint8_t en_query );
```

### Application Init

> Initializes the driver and performs a factory reset. 
> In the next step, the demo app requests the LYRA module name, software version, 
> and MAC address and sets the local device name, 
> sets the module into VSP mode and start advertising.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lyra24p_cfg_t lyra24p_cfg;  /**< Click config object. */

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
    lyra24p_cfg_setup( &lyra24p_cfg );
    LYRA24P_MAP_MIKROBUS( lyra24p_cfg, MIKROBUS_1 );
    if ( UART_ERROR == lyra24p_init( &lyra24p, &lyra24p_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    lyra24p_hw_reset( &lyra24p );
    Delay_ms ( 500 );

    lyra24p_write_command( &lyra24p, LYRA24P_CMD_AT );
    lyra24p_check_response( LYRA24P_RSP_OK );
    Delay_ms ( 500 );

    lyra24p_write_command( &lyra24p, LYRA24P_CMD_AT );
    lyra24p_check_response( LYRA24P_RSP_OK );
    Delay_ms ( 500 );

    lyra24p_inquire_command( &lyra24p, LYRA24P_CMD_ATI, 
                                       LYRA24P_ATI_ARG_DEV_NAME, 
                                       LYRA24P_QUERY_DIS );
    lyra24p_check_response( LYRA24P_RSP_OK );
    Delay_ms ( 500 );

    lyra24p_inquire_command( &lyra24p, LYRA24P_CMD_ATI, 
                                       LYRA24P_ATI_ARG_FW_VER, 
                                       LYRA24P_QUERY_DIS );
    lyra24p_check_response( LYRA24P_RSP_OK );
    Delay_ms ( 500 );

    lyra24p_inquire_command( &lyra24p, LYRA24P_CMD_ATI, 
                                       LYRA24P_ATI_ARG_BT_ADDR, 
                                       LYRA24P_QUERY_DIS );
    lyra24p_check_response( LYRA24P_RSP_OK );
    Delay_ms ( 500 );

    lyra24p_write_cmd_param( &lyra24p, LYRA24P_CMD_ATS, 
                                       LYRA24P_ATS_ARG_DEVNAME_FORMAT, 
                                       LYRA24P_PREFIX_SYMBOL_SET_VAL, 
                                       LYRA24P_ATS_VAL_DEVNAME );
    lyra24p_check_response( LYRA24P_RSP_OK );
    Delay_ms ( 500 );
    
    lyra24p_set_device_name( &lyra24p, DEVICE_NAME );
    lyra24p_check_response( LYRA24P_RSP_OK );
    Delay_ms ( 500 );

    lyra24p_inquire_command( &lyra24p, LYRA24P_CMD_ATPS, 
                                       LYRA24P_PREFIX_SYMBOL_ZERO, 
                                       LYRA24P_QUERY_EN );
    lyra24p_check_response( LYRA24P_RSP_OK );
    Delay_ms ( 500 );

    lyra24p_write_command( &lyra24p, LYRA24P_CMD_ATLADV );
    lyra24p_check_response( LYRA24P_RSP_OK );
    Delay_ms ( 500 );

    lyra24p_write_command( &lyra24p, LYRA24P_CMD_ATLVSP );
    lyra24p_check_response( LYRA24P_RSP_OK );
    Delay_ms ( 500 );
}
```

### Application Task

> Initializes the driver and performs a factory reset. 
> In the next step, the demo app are requesting the LYRA module name, 
> software version and MAC address and sets the local device name "LYRA 24P Click",  
> sets the module into VSP mode and start adverttising.

```c
void application_task ( void ) 
{
    if ( LYRA24P_OK == lyra24p_process( &lyra24p ) ) 
    {
        lyra24p_log_app_buf( );
        lyra24p_clear_app_buf( );
        Delay_ms ( 100 );
    }
}
```

### Note

> We have used the BLE Scanner smartphone application for the test.

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
