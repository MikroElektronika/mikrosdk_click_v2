
---
# Compass 4 Click

> [Compass 4 Click](https://www.mikroe.com/?pid_product=MIKROE-4231) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4231&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Sep 2020.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This demo application measures magnetic flux data.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Compass4

### Example Key Functions

- `compass4_cfg_setup` Config Object Initialization function. 
```c
void compass4_cfg_setup ( compass4_cfg_t *cfg );
``` 
 
- `compass4_init` Initialization function. 
```c
err_t compass4_init ( compass4_t *ctx, compass4_cfg_t *cfg );
```

- `compass4_get_interrupt` Gets INT pin state (DRDY pin). 
```c
uint8_t compass4_get_interrupt( compass4_t *ctx );
```
 
- `compass4_get_single_axis` Gets single axis value. 
```c
uint8_t compass4_get_single_axis( compass4_t *ctx, uint8_t axis_reg, int16_t *axis_data );
```

- `compass4_get_magnetic_flux` Gets magnetic flux of X\Y\Z axis value. 
```c
uint8_t compass4_get_magnetic_flux( compass4_t *ctx, compass4_flux_t *flux );
```

### Application Init

> Initializes the driver and resets the module, then checks the communication with the module and sets the module default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    compass4_cfg_t cfg;

    uint8_t device;

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

    compass4_cfg_setup( &cfg );
    COMPASS4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    compass4_init( &compass4, &cfg );

    compass4_hardware_reset( &compass4 );
    Delay_ms ( 500 );
    
    device = compass4_check_device( &compass4 );
    if ( device == 0 )
    {
        log_printf( &logger, ">> Device communication [ OK ] \r\n" );
    }
    else
    {
        log_printf( &logger, ">> Device communication [ ERROR ] \r\n" );
        for ( ; ; );
    }
    
    compass4_configuration ( &compass4, COMPASS4_CTRL1_WM_STEPS_5 | 
                                        COMPASS4_CTRL1_NOISE_ENABLE,
                                        COMPASS4_CTRL2_MODE_CONT_1 | 
                                        COMPASS4_CTRL2_SDR_LOW_NOISE |
                                        COMPASS4_CTRL2_FIFO_ENABLE );
                             
    log_printf( &logger, ">> Start measurement  \r\n" );
}
```

### Application Task

> Reads magnetic flux data and displays the values of X, Y, and Z axis to the USB UART each second.

```c
void application_task ( void )
{
    compass4_flux_t flux;
    uint8_t err;
    
    err = compass4_get_magnetic_flux( &compass4, &flux );
    if ( err != 0 )
    {
        log_printf( &logger, ">> Measurement error  \r\n" );
    }
    else
    {
        log_printf( &logger, ">> Magnetic flux data << \r\n" );
        log_printf( &logger, ">> X: %.2f \r\n", flux.x );
        log_printf( &logger, ">> Y: %.2f \r\n", flux.y );
        log_printf( &logger, ">> Z: %.2f \r\n", flux.z );
    }
    log_printf( &logger, "-----------------------------\r\n" );
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
