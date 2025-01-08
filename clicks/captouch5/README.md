
---
# Cap Touch 5 Click

> [Cap Touch 5 Click](https://www.mikroe.com/?pid_product=MIKROE-3786) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3786&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This example is waiting for touch sensor to detect something and then logs what is touched.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.CapTouch5

### Example Key Functions

- `captouch5_cfg_setup` Config Object Initialization function. 
```c
void captouch5_cfg_setup ( captouch5_cfg_t *cfg );
``` 
 
- `captouch5_init` Initialization function. 
```c
err_t captouch5_init ( captouch5_t *ctx, captouch5_cfg_t *cfg );
```

- `captouch5_default_cfg` Click Default Configuration function. 
```c
void captouch5_default_cfg ( captouch5_t *ctx );
```

- `captouch5_read_button_status` This function reads button status. 
```c
void captouch5_read_button_status ( captouch5_t *ctx, T_CAPTOUCH5_BUTTONS *buttons );
```
 
- `captouch5_read_slider_position` This function reads slider position. 
```c
uint16_t captouch5_read_slider_position ( captouch5_t *ctx );
```

### Application Init

> Initializes I2C module and driver, tests communication and configures device. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    captouch5_cfg_t cfg;

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

    captouch5_cfg_setup( &cfg );
    CAPTOUCH5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    captouch5_init( &captouch5, &cfg );
    captouch5_default_cfg ( &captouch5, &device_cfg );
}
```

### Application Task

> Waiting for touch sensor to detect something and then logs what is touched.

```c
void application_task ( void )
{
    uint16_t temp_byte;
    uint16_t last_temp;
    uint8_t temp_slider;

    state_check = 0;

    if ( CAPTOUCH5_ERROR == captouch5_process( &captouch5 ) )
    {
        log_printf( &logger, "***** ERROR *****" );
        state_check = 1;
        return;
    }

    temp_byte = captouch5_read_slider_position( &captouch5 );
    captouch5_read_button_status( &captouch5, &buttons );

    if ( temp_byte != last_temp )
    {
        log_printf( &logger, "Slider position value: %u \r\n", temp_byte );
        last_temp = temp_byte;
        state_check = 1;
    }

    captouch5_read_buttons(  );

    Delay_ms ( 100 );

    if ( state_check == 1 )
    {
        log_info( &logger, "--- Waiting for command ---\r\n" );
    }
}
```

### Note

> Click will go to sleep if doesn't get any command in 340ms.
  When you start device try restarting your board few times to start device.

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
