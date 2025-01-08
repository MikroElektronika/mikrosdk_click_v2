
---
# Proximity 13 Click

> [Proximity 13 Click](https://www.mikroe.com/?pid_product=MIKROE-3991) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3991&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : Jan 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This demo application shows example for measuring close distance.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity13

### Example Key Functions

- `proximity13_cfg_setup` Config Object Initialization function. 
```c
void proximity13_cfg_setup ( proximity13_cfg_t *cfg );
``` 
 
- `proximity13_init` Initialization function. 
```c
err_t proximity13_init ( proximity13_t *ctx, proximity13_cfg_t *cfg );
```

- `proximity13_default_cfg` Click Default Configuration function. 
```c
void proximity13_default_cfg ( proximity13_t *ctx );
```

- `proximity13_generic_write` This function writes data to the desired register. 
```c
void proximity13_generic_write ( proximity13_t *ctx, uint8_t reg_adr, uint8_t write_data );
```
 
- `proximity13_generic_read` This function reads data from the desired register. 
```c
uint8_t proximity13_generic_read ( proximity13_t *ctx, uint8_t reg_adr );
```

- `proximity13_read_channels` This function reads all enabled channels. 
```c
void proximity13_read_channels ( proximity13_t *ctx, proximity13_chn_val_t *chn_val );
```

### Application Init

> Initialization of I2C module and additional pin, checks id of device, 
> configurates device for measuring 1. channel,
> and then sends command to start measuring.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    proximity13_cfg_t cfg;
    uint8_t status;

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
    log_info( &logger, " Application Init" );

    //  Click initialization.

    proximity13_cfg_setup( &cfg );
    PROXIMITY13_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    proximity13_init( &proximity13, &cfg );
    
    status = proximity13_get_int_pin_status( &proximity13 );
    while ( status != PROXIMITY13_PIN_HIGH );

    status = porximity13_check_id( &proximity13 );
    if ( status == PROXIMITY13_OK )
    {
        log_info( &logger, " Device OK" );
    }
    else
    {
        log_info( &logger, " Device Error" );
        for ( ; ; );
    }
    
    log_info( &logger, " Setting default configuration" );
    proximity13_default_cfg ( &proximity13 );
    
    proximity13_send_command( &proximity13, PROXIMITY13_CMD_START );
    log_info( &logger, " Starting measurement" );
}
```

### Application Task

> Appliction measures values every 100ms and logs result.

```c
void application_task ( void )
{
    proximity13_chn_val_t chn_val;

    proximity13_read_channels( &proximity13, &chn_val );

    log_printf( &logger, " Data : %u\r\n", chn_val.channel_1 );

    Delay_ms ( 100 );
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
