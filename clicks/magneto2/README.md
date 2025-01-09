
---
# Magneto 2 Click

> [Magneto 2 Click](https://www.mikroe.com/?pid_product=MIKROE-1938) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1938&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> This example collects data from the sensor, calculates position of absolute 
> rotary angle and then logs it.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Magneto2

### Example Key Functions

- `magneto2_cfg_setup` Config Object Initialization function. 
```c
void magneto2_cfg_setup ( magneto2_cfg_t *cfg );
``` 
 
- `magneto2_init` Initialization function. 
```c
err_t magneto2_init ( magneto2_t *ctx, magneto2_cfg_t *cfg );
```

- This function reads 14-bit data value from target register,
  calculates and converts to float angle value from 0� to 360�.
> float magneto2_read_angle ( magneto2_t* ctx )
 
- `magneto2_read_data` This function takes 14-bit data value from target register. 
```c
uint16_t magneto2_read_data ( magneto2_t* ctx );
```

### Application Init

> Initializes driver and start write log.


```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    magneto2_cfg_t cfg;

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

    magneto2_cfg_setup( &cfg );
    MAGNETO2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    magneto2_init( &magneto2, &cfg );

    angle_value = 0;
    angle_value_old = -1.0;
}
```

### Application Task

> Magneto 2 Click communicates with register via SPI by read from register
> and calculates position of absolute rotary angle float value.
> Results are being sent to the Uart Terminal where you can track their changes.
> All data logs on usb uart when magnetic field is detected.


```c
void application_task ( void )
{
    angle_value = magneto2_read_angle( &magneto2 );
    Delay_100ms();

    if ( angle_value_old != angle_value )
    {
        if ( angle_value != -1 )
        {
            if ( angle_value != 0 )
            {
                log_printf( &logger, "Angle %f\r\n", angle_value );
            }
            else
            {
                log_printf( &logger, "Magnetic field too weak\r\n" );
            }
        }
        else
        {
            log_printf(&logger, "Magnetic field too strong\r\n");
        }

        angle_value_old = angle_value;
        Delay_ms ( 1000 );
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
