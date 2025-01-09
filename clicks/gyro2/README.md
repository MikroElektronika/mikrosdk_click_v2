
---
# Gyro 2 Click

> [Gyro 2 Click](https://www.mikroe.com/?pid_product=MIKROE-3300) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3300&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This application enables usage of 3 angular movement and velocity sensor.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Gyro2

### Example Key Functions

- `gyro2_cfg_setup` Config Object Initialization function. 
```c
void gyro2_cfg_setup ( gyro2_cfg_t *cfg );
``` 
 
- `gyro2_init` Initialization function. 
```c
err_t gyro2_init ( gyro2_t *ctx, gyro2_cfg_t *cfg );
```

- `gyro2_default_cfg` Click Default Configuration function. 
```c
void gyro2_default_cfg ( gyro2_t *ctx );
```

- `gyro2_get_id` Function will return the ID from the ID register. 
```c
uint8_t gyro2_get_id ( gyro2_t *ctx );
```
 
- Function will read the X, Y and Z axis registers.
- `gyro2_get_axisraw` Data that is read is storred the 3 16bit array. 
```c
void gyro2_get_axisraw ( gyro2_t *ctx, int16_t *axis_data );
```

- `gyro2_calc_axis` Function for calculating raw axis data. 
```c
void gyro2_calc_axis ( int16_t *axis_data );
```

### Application Init

> Initialize the communication interface and configure the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    gyro2_cfg_t cfg;
    uint8_t temp;

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

    gyro2_cfg_setup( &cfg );
    GYRO2_MAP_MIKROBUS( cfg, MIKROBUS_1 );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    gyro2_init( &gyro2, &cfg );

    temp = gyro2_default_cfg( &gyro2 );

    if ( temp == 1 )
    {
        log_printf( &logger, "Gyro 2 present\r\n" );
    }
    else if ( temp == 2 )
    {
        log_printf( &logger, "Error\r\n" );
    }
    Delay_ms ( 100 );
}
```

### Application Task

> Read the x,y,z and temperature data from the Click board and display the resoults on the
> serial port.

```c
void application_task ( void )
{
    //  Task implementation.

    int16_t axis_data[ 3 ];
    uint8_t temperature;

    gyro2_get_axisraw( &gyro2, axis_data );
    gyro2_calc_axis( axis_data );

    log_printf( &logger, "x: %d \r\ny: %d \r\nz: %d \r\n", axis_data[ 0 ], axis_data[ 1 ], axis_data[ 2 ] );

    temperature = gyro2_read_temperature( &gyro2 );

    log_printf( &logger, "Temperature: %d C\r\n ++ \r\n", temperature );

    Delay_ms ( 200 );
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
