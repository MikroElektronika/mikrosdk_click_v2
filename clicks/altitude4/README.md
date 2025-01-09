
---
# Altitude 4 Click

> [Altitude 4 Click](https://www.mikroe.com/?pid_product=MIKROE-4127) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4127&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This example showcases how to initialize, configure and use the Altitude 4 Click module. The
  Click has a sensor that measures: altitude, pressure and temperature. No additional equipment
  or special configuration is required in order for this demo to work. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Altitude4

### Example Key Functions

- `altitude4_cfg_setup` Config Object Initialization function. 
```c
void altitude4_cfg_setup ( altitude4_cfg_t *cfg );
``` 
 
- `altitude4_init` Initialization function. 
```c
err_t altitude4_init ( altitude4_t *ctx, altitude4_cfg_t *cfg );
```

- `altitude4_default_cfg` Click Default Configuration function. 
```c
void altitude4_default_cfg ( altitude4_t *ctx );
```

- This function stores the len amount of data into the r_buf. The data is read from
  the address reg.
> void altitude4_generic_read ( altitude4_t *ctx, uint8_t reg, uint8_t *r_buf, uint8_t len );
 
- `altitude4_generic_write` This function writes the len amount of data from the w_buf to the address reg. 
```c
void altitude4_generic_write ( altitude4_t *ctx, uint8_t reg, uint8_t *w_buf, uint8_t len );
```

- This function acquires sensor data from the Click module and stores it in the
  sensor data object.
> uint8_t altitude4_read_sensor ( altitude4_t *ctx, altitude4_sensor_t *sens_data );

### Application Init

> This function initializes and configures the logger and Click modules. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    altitude4_cfg_t cfg;

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

    altitude4_cfg_setup( &cfg );
    ALTITUDE4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    altitude4_init( &altitude4, &cfg );
    Delay_ms ( 500 );
}
```

### Application Task

> This function initializes the sensor data object through the read_sensor(...) function and
  then prints altitude, pressure and temperature values in the UART console. It does so every
  second.

```c
void application_task ( void )
{
    altitude4_sensor_t sensor_data;
    
    altitude4_read_sensor( &altitude4, &sensor_data );
    
    log_printf( &logger, " * Altitude: %.2f m\r\n", sensor_data.altitude );
    log_printf( &logger, " * Pressure: %.2f mBar\r\n", sensor_data.pressure );
    log_printf( &logger, " * Temperature: %.2f C\r\n", sensor_data.temperature );
    log_printf( &logger, " -------------------------\r\n" );

    Delay_1sec( );
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
