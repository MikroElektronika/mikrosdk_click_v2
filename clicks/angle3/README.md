
---
# Angle 3 Click

> [Angle 3 Click](https://www.mikroe.com/?pid_product=MIKROE-2755) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2755&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> This application reads data from the angle sensor, calculates it to degrees and writes it to the terminal.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Angle3

### Example Key Functions

- `angle3_cfg_setup` Config Object Initialization function.
```c
void angle3_cfg_setup ( angle3_cfg_t *cfg ); 
```

- `angle3_init` Initialization function.
```c
err_t angle3_init ( angle3_t *ctx, angle3_cfg_t *cfg );
```

- `angle3_write_data` Writes given data to given address.
```c
void angle3_write_data ( angle3_t* ctx, uint8_t opcode, uint8_t reg, uint16_t write_data );
```

- `angle3_read_data` Reads data from given address.
```c
uint16_t angle3_read_data ( angle3_t* ctx, uint8_t opcode, uint8_t reg );
```

- `angle3_read_angle_data` Function reads the latest angle output data.
```c
uint16_t angle3_read_angle_data( angle3_t* ctx );
```

### Application Init

> Initialization driver enable's - SPI, set normal mode and start write log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    angle3_cfg_t angle3_cfg;

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
    angle3_cfg_setup( &angle3_cfg );
    ANGLE3_MAP_MIKROBUS( angle3_cfg, MIKROBUS_1 );
    if ( ANGLE3_ERROR == angle3_init( &angle3, &angle3_cfg ) )
    {
        log_info( &logger, "---- Application Init Error ----" );
        log_info( &logger, "---- Please, run program again... ----" );
        for ( ; ; );
    }
    angle3_default_cfg ( &angle3 );
    
    log_info( &logger, "---- Application Task ----\n" );
}
```

### Application Task

> Angle 3 Click communicates with registers via SPI, reads data from the angle sensor, calculates it to degrees and writes it to the terminal.

```c
void application_task ( void )
{
    static uint16_t angle_value_old = 0;

    if ( angle3_read_error( &angle3 ) )
    {
        uint16_t angle_value = angle3_read_angle_data( &angle3 );

        if ( angle_value_old != angle_value )
        {
            float angle_data_degrees = angle3_calculate_degrees( &angle3, angle_value );

            log_printf( &logger, " Angle : %.1f deg\r\n", angle_data_degrees );

            angle_value_old = angle_value;

            Delay_ms ( 300 );
        }
    }
    else
    {
        log_printf( &logger, " Magnetic Field Too Weak\r\n" );

        angle_value_old = 0;
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
