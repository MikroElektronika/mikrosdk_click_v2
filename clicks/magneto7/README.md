
---
# Magneto 7 Click

> [Magneto 7 Click](https://www.mikroe.com/?pid_product=MIKROE-3657) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3657&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This demo application reads position of a magnet above the sensor.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Magneto7

### Example Key Functions

- `magneto7_cfg_setup` Config Object Initialization function. 
```c
void magneto7_cfg_setup ( magneto7_cfg_t *cfg );
``` 
 
- `magneto7_init` Initialization function. 
```c
err_t magneto7_init ( magneto7_t *ctx, magneto7_cfg_t *cfg );
```

- `magneto7_default_cfg` Click Default Configuration function. 
```c
void magneto7_default_cfg ( magneto7_t *ctx );
```

- `magneto7_int_get` This function returns INT pin state. 
```c
uint8_t magneto7_int_get ( magneto7_t *ctx );
```
 
- `magneto7_get_register` This function gets register value(s). 
```c
uint8_t magneto7_get_register ( magneto7_t *ctx, uint8_t register_address, uint8_t * data_buffer, uint8_t n_data );
```

- `magneto7_get_temperature` This function gets raw device temperature value. 
```c
void magneto7_get_temperature ( magneto7_t *ctx, uint16_t *device_temperature );
```

### Application Init

> Initializes device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    magneto7_cfg_t cfg;
    uint8_t init_status;

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
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    magneto7_cfg_setup( &cfg );
    MAGNETO7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    magneto7_init( &magneto7, &cfg );
    Delay_ms ( 300 );

    init_status = magneto7_default_cfg( &magneto7 );
    if ( init_status == 0)
    {
        log_printf( &logger, "> app init done\r\n" );
    }
    else if ( init_status == 1 )
    {
        log_printf( &logger, "> app init fail\r\n" );
        for ( ; ; );
    }
}
```

### Application Task

> Waits for INT pin to go LOW, gets raw data, converts it to uT and logs results.

```c
void application_task ( void )
{
    uint8_t int_status;
    float converted_data;

    int16_t data_x;
    int16_t data_y;
    int16_t data_z;

    int_status = magneto7_int_get( &magneto7 );
    
    if ( int_status == 0 )
    {
        magneto7_get_data( &magneto7, &data_x, &data_y, &data_z );
        
        converted_data = magneto7_convert_to_ut( &magneto7, data_x, MAGNETO7_SENSOR_RES_14_BIT );
        log_printf( &logger, "> X Axis : %f [uT]\r\n", converted_data );
        
        converted_data = magneto7_convert_to_ut( &magneto7, data_y, MAGNETO7_SENSOR_RES_14_BIT );
        log_printf( &logger, "> Y Axis : %f [uT]\r\n", converted_data );

        converted_data = magneto7_convert_to_ut( &magneto7, data_z, MAGNETO7_SENSOR_RES_14_BIT );
        log_printf( &logger, "> Z Axis : %f [uT]\r\n", converted_data );

        log_printf( &logger, "\r\n" );
        
        Delay_ms ( 300 );
    }
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
