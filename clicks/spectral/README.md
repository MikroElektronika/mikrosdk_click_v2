
---
# Spectral Click

> [Spectral Click](https://www.mikroe.com/?pid_product=MIKROE-2972) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2972&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Mar 2020.
- **Type**          : UART type

# Software Support

## Example Description

> This example reads and processes data from Spectral Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Spectral

### Example Key Functions

- `spectral_cfg_setup` Config Object Initialization function.
```c
void spectral_cfg_setup ( spectral_cfg_t *cfg ); 
```

- `spectral_init` Initialization function.
```c
err_t spectral_init ( spectral_t *ctx, spectral_cfg_t *cfg );
```

- `spectral_uart_read` Generic read function.
```c
int32_t spectral_uart_read ( spectral_t *ctx, uint8_t *data_buf, uint16_t max_len );
```

- `spectral_send_command` Send Command
```c
void spectral_send_command ( spectral_t *ctx, uint8_t *command );
```

- `spectral_get_data` Read raw X, Y, Z and NIR data as well as two special internal registers D, & C.
```c
void spectral_get_data ( uint8_t *rsp, uint16_t *c_data );
```

### Application Init

> Initializes the driver and configures the sensor.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    spectral_cfg_t cfg;

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

    // Click initialization.
    spectral_cfg_setup( &cfg );
    SPECTRAL_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    spectral_init( &spectral, &cfg );

    spectral_module_reset( &spectral );
    Delay_ms ( 500 );

    log_printf( &logger, "Configuring the sensor...\r\n" );
    spectral_send_command( &spectral, SPECTRAL_CMD_AT );
    spectral_process( );
    spectral_send_command( &spectral, SPECTRAL_CMD_GAIN );
    spectral_process( );
    spectral_send_command( &spectral, SPECTRAL_CMD_MODE );
    spectral_process( );
    log_printf( &logger, "The sensor has been configured!\r\n" );
    Delay_ms ( 1000 );
}
```

### Application Task

> Reads the values of all 6 channels and parses it to the USB UART each second.

```c
void application_task ( void )
{
    parser_application( );  
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
