
---
# DC Motor 10 Click

> [DC Motor 10 Click](https://www.mikroe.com/?pid_product=MIKROE-3879) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3879&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Jovan Stajkovic
- **Date**          : Jan 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> 
> This example is running dc motors on channels 1 through 3.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DcMotor10

### Example Key Functions

- `dcmotor10_cfg_setup` Config Object Initialization function. 
```c
void dcmotor10_cfg_setup ( dcmotor10_cfg_t *cfg );
``` 
 
- `dcmotor10_init` Initialization function. 
```c
err_t dcmotor10_init ( dcmotor10_t *ctx, dcmotor10_cfg_t *cfg );
```

- `dcmotor10_send_cmd` Function is used to send command. 
```c
void dcmotor10_send_cmd ( dcmotor10_t *ctx, uint16_t wr_data );
```
 
- `dcmotor10_read_status` Function is used to read status. 
```c
uint16_t dcmotor10_read_status ( dcmotor10_t *ctx );
```

- `dcmotor10_inhibit` Function is used to inhibit or uninhibit the device. 
```c
void dcmotor10_inhibit ( dcmotor10_t *ctx, uint8_t state );
```

### Application Init

>
> Initalizes SPI, Click drivers and uninhibites the device.
> 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    dcmotor10_cfg_t cfg;

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

    dcmotor10_cfg_setup( &cfg );
    DCMOTOR10_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dcmotor10_init( &dcmotor10, &cfg );
    Delay_ms ( 100 );
    
    dcmotor10_inhibit(&dcmotor10, DCMOTOR10_UNINHIBIT );
    dcmotor10_send_cmd( &dcmotor10, DCMOTOR10_RESET_STATUS_REG );
    Delay_ms ( 100 );
}
```

### Application Task

>
> This example demonstrates the use of DC MOTOR 10 Click by running dc motors 
> on channels 1 through 3, first all 3 together and then separately.
> 

```c
void application_task ( void )
{
    dcmotor10_send_cmd( &dcmotor10, DCMOTOR10_ENABLE_1 | DCMOTOR10_ENABLE_2 
                      | DCMOTOR10_ENABLE_3 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    dcmotor10_send_cmd( &dcmotor10, DCMOTOR10_ENABLE_1 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    dcmotor10_send_cmd( &dcmotor10, DCMOTOR10_ENABLE_2 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    dcmotor10_send_cmd( &dcmotor10, DCMOTOR10_ENABLE_3 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    dcmotor10_send_cmd( &dcmotor10, DCMOTOR10_RESET_STATUS_REG );
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
