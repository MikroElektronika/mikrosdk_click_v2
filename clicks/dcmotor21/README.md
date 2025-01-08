
---
# DC Motor 21 Click

> [DC Motor 21 Click](https://www.mikroe.com/?pid_product=MIKROE-4877) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4877&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2021.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of DC Motor 21 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DCMotor21

### Example Key Functions

- `dcmotor21_cfg_setup` Config Object Initialization function.
```c
void dcmotor21_cfg_setup ( dcmotor21_cfg_t *cfg );
```

- `dcmotor21_init` Initialization function.
```c
err_t dcmotor21_init ( dcmotor21_t *ctx, dcmotor21_cfg_t *cfg );
```

- `dcmotor21_default_cfg` Click Default Configuration function.
```c
void dcmotor21_default_cfg ( dcmotor21_t *ctx );
```

- `dcmotor21_set_out_1` This function sets the state of output 1.
```c
void dcmotor21_set_out_1 ( dcmotor21_t *ctx, uint8_t state );
```

- `dcmotor21_set_out_2` This function sets the state of output 2.
```c
void dcmotor21_set_out_2 ( dcmotor21_t *ctx, uint8_t state );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dcmotor21_cfg_t dcmotor21_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    dcmotor21_cfg_setup( &dcmotor21_cfg );
    DCMOTOR21_MAP_MIKROBUS( dcmotor21_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == dcmotor21_init( &dcmotor21, &dcmotor21_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    dcmotor21_default_cfg ( &dcmotor21 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> In the span of six seconds, it drives the motor in one direction, then switches the direction, 
> and after that disconnects the motor. Each step will be logged on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    dcmotor21_set_out_1 ( &dcmotor21, DCMOTOR21_OUT_LOW );
    dcmotor21_set_out_2 ( &dcmotor21, DCMOTOR21_OUT_HIGH );
    log_printf( &logger, " \r\n Driving the motor...\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    dcmotor21_set_out_1 ( &dcmotor21, DCMOTOR21_OUT_HIGH );
    dcmotor21_set_out_2 ( &dcmotor21, DCMOTOR21_OUT_LOW );
    log_printf( &logger, " Switch direction.\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    dcmotor21_set_out_1 ( &dcmotor21, DCMOTOR21_OUT_HIGH_Z );
    dcmotor21_set_out_2 ( &dcmotor21, DCMOTOR21_OUT_HIGH_Z );
    log_printf( &logger, " The motor is disconnected.\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Note

> For this example, a DC motor should be connected to OUT1 and OUT2 lines.

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
