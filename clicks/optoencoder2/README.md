
---
# Opto Encoder 2 Click

> [Opto Encoder 2 Click](https://www.mikroe.com/?pid_product=MIKROE-3634) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3634&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> This application is used to encode motion or rotation.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.OptoEncoder2

### Example Key Functions

- `optoencoder2_cfg_setup` Config Object Initialization function.
```c
void optoencoder2_cfg_setup ( optoencoder2_cfg_t *cfg ); 
```

- `optoencoder2_init` Initialization function.
```c
err_t optoencoder2_init ( optoencoder2_t *ctx, optoencoder2_cfg_t *cfg );
```

- `optoencoder2_pwm_get` Getting PWM pin state
```c
uint8_t optoencoder2_pwm_get ( optoencoder2_t *ctx );
```

- `optoencoder2_int_get` Getting INT pin state
```c
uint8_t optoencoder2_int_get ( optoencoder2_t *ctx );
```

- `optoencoder2_get_position` Getting encoder position
```c
int32_t optoencoder2_get_position ( optoencoder2_t *ctx );
```

### Application Init

> Initializes GPIO driver and resets encoder counter to 0 (zero).

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    optoencoder2_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.
    optoencoder2_cfg_setup( &cfg );
    OPTOENCODER2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    optoencoder2_init( &optoencoder2, &cfg );

    optoencoder2_zero_counter( &optoencoder2 );
}
```

### Application Task

> If motion is detected - encoder increments or decrements position on each rising edge on Channel A (INT pin) and logs encoder position.

```c
void application_task ( )
{
    int32_t encoder_position = 0;
    uint8_t stop_flag = 0;

    stop_flag = optoencoder2_isr( &optoencoder2, 100 );
    encoder_position = optoencoder2_get_position( &optoencoder2 );
    
    if ( stop_flag == 0 )
    {
        log_printf( &logger, "Position: %ld \r\n", encoder_position );
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
