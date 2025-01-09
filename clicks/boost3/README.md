
---
# Boost 3 Click

> [Boost 3 Click](https://www.mikroe.com/?pid_product=MIKROE-4287) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4287&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Sep 2020.
- **Type**          : GPIO type

# Software Support

## Example Description

> Boost 3 Click provides an adjustable output voltage through the onboard
> potentiometer. The chip is a 700-kHz pulse-width modulating (PWM) step-up 
> converter with an 85-V switch FET with an input ranging from 2.5 V to 5.5 V. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Boost3

### Example Key Functions

- `boost3_cfg_setup` Config Object Initialization function. 
```c
void boost3_cfg_setup ( boost3_cfg_t *cfg );
``` 
 
- `boost3_init` Initialization function. 
```c
err_t boost3_init ( boost3_t *ctx, boost3_cfg_t *cfg );
```

- `boost3_dev_enable` Function is used to enable or disable the device. 
```c
void boost3_dev_enable ( boost3_t *ctx, uint8_t state );
```

### Application Init

> Initializes GPIO and LOG structures, and set CS pin as output.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    boost3_cfg_t cfg;

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

    boost3_cfg_setup( &cfg );
    BOOST3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    boost3_init( &boost3, &cfg );
}
```

### Application Task

> Turns ON the device for 10 seconds and then turns it OFF for 3 seconds.
> It also displays appropriate messages on the USB UART.

```c
void application_task ( void )
{
    boost3_dev_enable( &boost3, BOOST3_ENABLE );
        
    log_printf( &logger, "The Click board is enabled!\r\n" );
    log_printf( &logger, "Please use the on-board potentiometer" );
    log_printf( &logger, " to adjust the voltage output.\r\n" );
    log_printf( &logger, "--------------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    boost3_dev_enable( &boost3, BOOST3_DISABLE );
    log_printf( &logger, "The Click board is turned OFF!\r\n" );
    log_printf( &logger, "--------------------------------\r\n" );
    Delay_ms ( 1000 );
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
