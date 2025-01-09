
---
# Smart Buck Click

> [Smart Buck Click](https://www.mikroe.com/?pid_product=MIKROE-3113) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3113&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application reads voltage, current, and power from all available channels.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SMARTBUCK

### Example Key Functions

- `smartbuck_cfg_setup` Config Object Initialization function. 
```c
void smartbuck_cfg_setup ( smartbuck_cfg_t *cfg );
``` 
 
- `smartbuck_init` Initialization function. 
```c
err_t smartbuck_init ( smartbuck_t *ctx, smartbuck_cfg_t *cfg );
```

- `smartbuck_default_cfg` Click Default Configuration function. 
```c
void smartbuck_default_cfg ( smartbuck_t *ctx );
```

- `smartbuck_send_cmd_PAC` Function performs the desired command for PAC1934. 
```c
uint8_t smartbuck_send_cmd_PAC ( smartbuck_t *ctx, uint8_t command );
```
 
- `smartbuck_get_data` Function reads and calculates the voltage, current and power data from PAC1934 activated channels. 
```c
void smartbuck_get_data ( smartbuck_t *ctx,  float *voltage, float *current, float *power );
```

- `smartbuck_block_read_PAC` Function reads the desired number of bytes from the PAC1934 registers. 
```c
uint8_t smartbuck_block_read_PAC ( smartbuck_t *ctx, uint8_t reg_addr, uint8_t *data_out, uint8_t n_bytes );
```

### Application Init

> Initializes I2C interface and logger and peforms the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    smartbuck_cfg_t cfg;

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

    smartbuck_cfg_setup( &cfg );
    SMARTBUCK_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    smartbuck_init( &smartbuck, &cfg );
    smartbuck_default_cfg( &smartbuck );
}
```

### Application Task

> Sends command for updating data registers with new converted data, 
> then waits 500ms and after that reads new data from data registers. 
> In this way we can get voltage, current and power data from activated channels.
> Results are being logged on USB UART.

```c
void application_task ( void )
{
    smartbuck_send_cmd_pac( &smartbuck, SMARTBUCK_REFRESH_V_CMND );
    Delay_ms ( 500 );
    smartbuck_get_data( &smartbuck, &voltage_res[ 0 ], &current_res[ 0 ], &power_res[ 0 ] );
    
    check_byte = 0x80;
    idx = 0;
    
    for ( cnt = 0; cnt < 4; cnt++ )
    {
        if ( ( smartbuck.enabled_chann & check_byte ) == 0 )
        {
            channel_log();
            
            log_printf( &logger, "U: %.2f V    ", voltage_res[ idx ] );
            log_printf( &logger, "I: %.2f mA    ", current_res[ idx ] );
            log_printf( &logger, "P: %.2f mW    ", power_res[ idx ] );
            
            idx++;
        }
        check_byte >>= 1;
    }
    
    log_printf( &logger, "\n");
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
