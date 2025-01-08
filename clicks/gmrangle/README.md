
---
# GMR Angle Click

> [GMR Angle Click](https://www.mikroe.com/?pid_product=MIKROE-3815) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3815&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This is an example which demonstrates the use of GMR Angle Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.GmrAngle

### Example Key Functions

- `gmrangle_cfg_setup` Config Object Initialization function.
```c
void gmrangle_cfg_setup ( gmrangle_cfg_t *cfg ); 
```

- `gmrangle_init` Initialization function.
```c
err_t gmrangle_init ( gmrangle_t *ctx, gmrangle_cfg_t *cfg );
```

- `gmrangle_read_data` Generic read 16-bit data function.
```c
uint16_t gmrangle_read_data ( gmrangle_t *ctx, uint8_t reg );
```

- `gmrangle_write_data` Generic write 16-bit data function.
```c
void gmrangle_write_data ( gmrangle_t *ctx, uint8_t reg, uint16_t tx_data );
```

- `gmrangle_calculate_angle` Calculate angle function.
```c
float gmrangle_calculate_angle ( gmrangle_t *ctx );
```

### Application Init

> Initializes GPIO pins, SPI and LOG modules.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    gmrangle_cfg_t cfg;

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
    gmrangle_cfg_setup( &cfg );
    GMRANGLE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gmrangle_init( &gmrangle, &cfg );
    
    GMRANGLE_SET_DATA_SAMPLE_EDGE; 
    
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "   GMR Angle Click\r\n" );
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "        Start\r\n" );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> Display angle value in degrees.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs write on USB uart changes for every 300 msec.

```c
void application_task ( void )
{
    angle = gmrangle_calculate_angle( &gmrangle );
    log_printf( &logger, " Angle is %.1f\r\n", angle );
    Delay_ms ( 300 );
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
