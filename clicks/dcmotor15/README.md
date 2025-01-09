
---
# DC Motor 15 Click

> [DC Motor 15 Click](https://www.mikroe.com/?pid_product=MIKROE-4334) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4334&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2021.
- **Type**          : ADC type

# Software Support

## Example Description

> This example demonstrates the use of DC Motor 15 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DCMotor15

### Example Key Functions

- `dcmotor15_cfg_setup` Config Object Initialization function.
```c
void dcmotor15_cfg_setup ( dcmotor15_cfg_t *cfg );
```

- `dcmotor15_init` Initialization function.
```c
err_t dcmotor15_init ( dcmotor15_t *ctx, dcmotor15_cfg_t *cfg );
```

- `dcmotor15_default_cfg` Click Default Configuration function.
```c
void dcmotor15_default_cfg ( dcmotor15_t *ctx );
```

- `dcmotor15_forward` This function drives the motor forward.
```c
void dcmotor15_forward ( dcmotor15_t *ctx );
```

- `dcmotor15_reverse` This function drives the motor in reverse.
```c
void dcmotor15_reverse ( dcmotor15_t *ctx );
```

- `dcmotor15_get_current` This function reads the motor current consumption by performing analog to digital read of IPR pin.
```c
float dcmotor15_get_current ( dcmotor15_t *ctx, uint16_t num_of_conv );
```

### Application Init

> Initializes the driver and makes an initial log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;              /**< Logger config object. */
    dcmotor15_cfg_t dcmotor15_cfg;  /**< Click config object. */

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
    Delay_ms ( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.

    dcmotor15_cfg_setup( &dcmotor15_cfg );
    DCMOTOR15_MAP_MIKROBUS( dcmotor15_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == dcmotor15_init( &dcmotor15, &dcmotor15_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    dcmotor15_default_cfg ( &dcmotor15 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Drives the motor in the forward direction for 5 seconds, then pulls brake for 2 seconds, 
> and after that drives it in the reverse direction for 5 seconds, and finally, 
> disconnects the motor for 2 seconds. It will also calculates and displays the motor current consumption.
> Each step will be logged on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    log_printf( &logger, " The motor turns forward! \r\n" );
    dcmotor15_forward( &dcmotor15 );
    display_current ( &dcmotor15, RUN_PERIOD );
    log_printf( &logger, " Pull brake! \r\n" );
    dcmotor15_brake( &dcmotor15 );
    display_current ( &dcmotor15, IDLE_PERIOD );
    log_printf( &logger, " The motor turns in reverse! \r\n" );
    dcmotor15_reverse( &dcmotor15 );
    display_current ( &dcmotor15, RUN_PERIOD );
    log_printf( &logger, " The motor is disconnected (High-Z)!  \r\n" );
    dcmotor15_stop( &dcmotor15 );
    display_current ( &dcmotor15, IDLE_PERIOD );
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
