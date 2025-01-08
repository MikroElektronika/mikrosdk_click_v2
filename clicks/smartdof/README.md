
---
# Smart DOF Click

> [Smart DOF Click](https://www.mikroe.com/?pid_product=MIKROE-3457) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3457&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This Click integrates a triaxial accelerometer, triaxial gyroscope and magnetometer.
> It can provide very accurate and precise 3D acceleration, magnetic, and angular velocity data, in real-time. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SmartDof

### Example Key Functions

- `smartdof_cfg_setup` Config Object Initialization function. 
```c
void smartdof_cfg_setup ( smartdof_cfg_t *cfg );
``` 
 
- `smartdof_init` Initialization function. 
```c
err_t smartdof_init ( smartdof_t *ctx, smartdof_cfg_t *cfg );
```

- `smartdof_default_cfg` Click Default Configuration function. 
```c
void smartdof_default_cfg ( smartdof_t *ctx );
```

- `smartdof_receive_packet` This function waits for INT pin to go LOW, receives 4 header bytes and than parses header bytes to get data length of entire packet and stores header bytes to header buffer. 
```c
uint8_t smartdof_receive_packet (  smartdof_t *ctx, uint32_t n_cycles_timeout  );
```
 
- `smartdof_get_feature_response` This function receives get feature response report bytes. 
```c
uint8_t smartdof_get_feature_response ( smartdof_t *ctx, smartdof_sfc_t *sfc );
```

- `smartdof_set_feature_command` This function sends set feature request report to device. 
```c
void smartdof_set_feature_command ( smartdof_t *ctx, smartdof_sfc_t *sfc );
```

### Application Init

> Initializes I2C driver and Smart DOF device 

```c
void application_init ( void )
{
    uint8_t p;
    log_cfg_t log_cfg;
    smartdof_cfg_t cfg;

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

    smartdof_cfg_setup( &cfg );
    SMARTDOF_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    smartdof_init( &smartdof, &cfg );

    if ( smartdof_default_cfg ( &smartdof ) !=0 )
    {
        log_info( &logger, "Error during default configuration" );
    }
}
```

### Application Task

> Executes one of 'smartdof_xxx_task()' additional functions 

```c
void application_task ( void )
{
    accelerometer_task( &smartdof, &smartdof_sfc );
}
```

### Note

> <pre>
> Additional Functions :
> - accelerometer_task() - initializes accelerometer reports in 100000 micro second intervals, receives, parses and logs report data
> - gyroscope_task() - initializes gyroscope calibrated reports in 100000 micro second intervals, receives, parses and logs report data
> - magnetometer_task() - initializes magnetometer calibrated reports in 100000 micro second intervals, receives, parses and logs report data
> </pre> 

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
