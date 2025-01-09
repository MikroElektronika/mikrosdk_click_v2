
---
# 3D Hall 7 Click

> [3D Hall 7 Click](https://www.mikroe.com/?pid_product=MIKROE-3629) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3629&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Nov 2019.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> 
> Read magnet positions.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.3dHall7

### Example Key Functions

- `c3dhall7_cfg_setup` Config Object Initialization function. 
```c
void c3dhall7_cfg_setup ( c3dhall7_cfg_t *cfg );
``` 
 
- `c3dhall7_init` Initialization function. 
```c
err_t c3dhall7_init ( c3dhall7_t *ctx, c3dhall7_cfg_t *cfg );
```

- `c3dhall7_default_cfg` Click Default Configuration function. 
```c
void c3dhall7_default_cfg ( c3dhall7_t *ctx );
```

- `c3dhall7_get_axis_data` Get Axis data function. 
```c
void c3dhall7_get_axis_data ( c3dhall7_t *ctx, T_C3DHALL7_AXIS *axis );
```
 
- `c3dhall7_get_status` Measurement status function. 
```c
void c3dhall7_get_status ( c3dhall7_t *ctx, T_C3DHALL7_STATUS *status );
```

- `c3dhall7_get_status` Measurement status function. 
```c
void c3dhall7_get_status ( c3dhall7_t *ctx, T_C3DHALL7_STATUS *status );
```

### Application Init

>
> Initializes driver init, test communication and configuration device for measurement.
> 

```c
void application_init ( c3dhall7_t *ctx, void )
{
    c3dhall7_dev_info_t info;

    log_cfg_t log_cfg;
    c3dhall7_cfg_t cfg;

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

    c3dhall7_cfg_setup( &cfg );
    C3DHALL7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c3dhall7_init( &c3dhall7, &cfg );

    c3dhall7_device_reset( &c3dhall7 );
    Delay_ms ( 1000 );
    c3dhall7_read_data( &c3dhall7, 0x01, &red_data, 1 );

    Delay_100ms( );

    for ( ; ; );
    // Test communication 
    c3dhall7_deviceInfo( &info );
    if ( info.device_id == C3DHALL7_DEVICE_ID )
    {
        mikrobus_logW_write( "---- Communication [ OK ]!!! ----", LOG_LINE );
    }
    else
    {
        mikrobus_log_write( "---- Communication [ ERROR ]!!! ----", LOG_LINE );

        for ( ; ; );
    }

    // Configuration 
    c3dhall7_default_cfg ( &c3dhall7 );
}
```

### Application Task

>
> Reads 3 Axis of the magnetic sensor and logs this data to USBUART every 500ms.
> 

```c
void application_task ( void )
{
    c3dhall7_axix_t axis;

    char demo_text[ 50 ];
    
    c3dhall7_get_axis_data( &axis );
    
    mikrobus_log_write( "---- Measurement data of magnetic sensor ----", LOG_LINE );
    
    log_printf( &logger, "X axis: %d \r\n", axis.x );

    log_printf( &logger, "Y axis: %d \r\n", axis.y );

    log_printf( &logger, "Z axis: %d \r\n", axis.z );
    
    mikrobus_log_write( "---------------------------------------------", LOG_LINE);
    Delay_ms ( 500 );
}
```

### Note

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
