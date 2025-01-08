
---
# Color 6 Click

> [Color 6 Click](https://www.mikroe.com/?pid_product=MIKROE-3061) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3061&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Nov 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> Reads values from the X / Y / Z channel and 
> converts to ee (input light irradiance regarding to the photodiode�s area
> within the conversion time interval) data. 
 
### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Color6

### Example Key Functions

- `color6_cfg_setup` Config Object Initialization function. 
```c
void color6_cfg_setup ( color6_cfg_t *cfg );
``` 
 
- `color6_init` Initialization function. 
```c
err_t color6_init ( color6_t *ctx, color6_cfg_t *cfg );
```

- `color6_default_cfg` Click Default Configuration function. 
```c
void color6_default_cfg ( color6_t *ctx );
```

- `color6_write_byte` This function write one byte in register. 
```c
void color6_write_byte ( color6_t *ctx, uint8_t reg, uint8_t r_data );
```
 
- `color6_read_byte` This function reads one byte data from register. 
```c
uint8_t color6_read_byte ( color6_t *ctx, uint8_t reg );
```

- `color6_get_temperature` The measurement result is available as TEMP of the output result registers. 
```c
float color6_get_temperature ( color6_t *ctx );
```

### Application Init

> Initializes driver init and configuration chip for measurement. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    color6_cfg_t cfg;

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

    color6_cfg_setup( &cfg );
    COLOR6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    color6_init( &color6, &cfg );

    color6_software_reset( &color6 );
    color6_default_cfg ( &color6 );
    color6_go_to_measurement_mode( &color6 );
}

  
```

### Application Task

> Reads values from the X / Y / Z channel and 
> converts to ee (input light irradiance regarding to the photodiode�s area
> within the conversion time interval) data. 
> This data logs on USB UART every 2 seconds.

```c
void application_task ( void )
{
    x_data = color6_read_data( &color6, COLOR6_MREG_MEASUREMENT_X_CHANNEL );
    log_printf( &logger, " Channel X :  %d ", x_data );

    ee_data = color6_converting_to_ee( COLOR6_MREG_MEASUREMENT_X_CHANNEL, x_data);
    log_printf( &logger, " Ee X channel data:   %f ", ee_data );

    y_data = color6_read_data( &color6, COLOR6_MREG_MEASUREMENT_Y_CHANNEL );
    log_printf( &logger, " Channel Y :  %d ", y_data );

    ee_data = color6_converting_to_ee( COLOR6_MREG_MEASUREMENT_Y_CHANNEL, y_data);
    log_printf( &logger, " Ee Y channel data:   %f ", ee_data );

    z_data = color6_read_data( &color6, COLOR6_MREG_MEASUREMENT_Z_CHANNEL );
    log_printf( &logger, " Channel Z :  %d ", z_data );

    ee_data = color6_converting_to_ee( COLOR6_MREG_MEASUREMENT_Z_CHANNEL, z_data);
    log_printf( &logger, " Ee Z channel data:   %f ", ee_data );

    temperature = color6_getTemperature( &color6 );
    log_printf( &logger, " Temperature :  %f ", temperature );

    Delay_ms ( 1000 );
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
