
---
# Presence Click

> [Presence Click](https://www.mikroe.com/?pid_product=MIKROE-3575) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3575&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This application enables usage of sensor for motion and presence sensing and measuring of object's and ambient temperature.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Presence

### Example Key Functions

- `presence_cfg_setup` Config Object Initialization function.
```c
void presence_cfg_setup ( presence_cfg_t *cfg ); 
```

- `presence_init` Initialization function.
```c
err_t presence_init ( presence_t *ctx, presence_cfg_t *cfg );
```

- `presence_default_cfg` Click Default Configuration function.
```c
err_t presence_default_cfg ( presence_t *ctx );
```

- `presence_ambient_temperature` This function returns ambient temperature in degrees Celsius.
```c
err_t presence_ambient_temperature( presence_t *ctx, float *temperature )
```

- `presence_object_temperature` This function returns object temperature.
```c
err_t presence_object_temperature( presence_t *ctx, float *temperature );
```

### Application Init

> Initializes driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    presence_cfg_t cfg;

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
    presence_cfg_setup( &cfg );
    PRESENCE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    presence_init( &presence, &cfg );

    if ( PRESENCE_ERROR == presence_default_cfg ( &presence ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Checks whether a new event (motion, presence or over-temperature) is detected. 
If there's no event detected it reads the ambient and object temperature and displays the results on the USB UART.

```c
void application_task ( void )
{
    uint8_t int_status = 0;
    uint8_t tp_presence = 0;
    uint8_t tp_motion = 0;
    float t_amb = 0;
    float t_obj = 0;
    
    if ( PRESENCE_OK == presence_generic_read( &presence, PRESENCE_REG_INTERRUPT_STATUS, &int_status, 1 ) )
    {
        if ( int_status & PRESENCE_INT_MASK1_PRESENCE )
        {
            if ( PRESENCE_OK == presence_generic_read( &presence, PRESENCE_REG_TP_PRESENCE, &tp_presence, 1 ) )
            {
                log_info( &logger, "Presence detected! Level: %u", ( uint16_t ) tp_presence );
            }
        }
        else if ( int_status & PRESENCE_INT_MASK1_MOTION )
        {
            if ( PRESENCE_OK == presence_generic_read( &presence, PRESENCE_REG_TP_MOTION, &tp_motion, 1 ) )
            {
                log_info( &logger, "Motion detected! Level: %u", ( uint16_t ) tp_motion );
            }
        }
        else if ( int_status & PRESENCE_INT_MASK1_TP_OT )
        {
            log_info( &logger, "Temp threshold exceeded!" );
        }
        else
        {
            if ( PRESENCE_OK == presence_ambient_temperature( &presence, &t_amb ) )
            {
                log_printf( &logger, "Ambient temperature: %.2f degC\r\n", t_amb );
            }
            if ( PRESENCE_OK == presence_object_temperature( &presence, &t_obj ) )
            {
                log_printf( &logger, "Object temperature: %.2f degC\r\n\n", t_obj );
            }
        }
    }
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