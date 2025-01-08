
---
# Force 3 Click

> [Force 3 Click](https://www.mikroe.com/?pid_product=MIKROE-4149) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4149&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jul 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This application demonstrates the use of Force 3 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Force3

### Example Key Functions

- `force3_cfg_setup` Config Object Initialization function. 
```c
void force3_cfg_setup ( force3_cfg_t *cfg );
``` 
 
- `force3_init` Initialization function. 
```c
err_t force3_init ( force3_t *ctx, force3_cfg_t *cfg );
```

- `force3_read_raw_data` Read 12bit raw data. 
```c
uint16_t force3_read_raw_data ( force3_t *ctx );
```

### Application Init

> Initializes the driver and makes an initial log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    force3_cfg_t cfg;

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

    force3_cfg_setup( &cfg );
    FORCE3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    force3_init( &force3, &cfg );
}
```

### Application Task

> Reads the sensor raw data and displays it on the USB UART.

```c
void application_task ( void )
{
    uint16_t raw_data;

    raw_data = force3_read_raw_data( &force3 );
    log_printf( &logger, "Raw data: %d \r\n", raw_data );

    if ( ( raw_data > 5 ) && ( raw_data <= 200 ) )
    {
       log_printf( &logger, ">> Light touch \r\n" );
    }
    else if ( ( raw_data > 200 ) && ( raw_data <= 500 ) )
    {
       log_printf( &logger, ">> Light squeeze \r\n" );
    }
    else if ( ( raw_data > 500 ) && ( raw_data <= 800 ) )
    {
       log_printf( &logger, ">> Medium squeeze \r\n" );
    }
    else if ( raw_data > 800 )
    {
       log_printf( &logger, ">> Big squeeze \r\n" );
    }
    
    log_printf( &logger, "----------------------\r\n" );
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
