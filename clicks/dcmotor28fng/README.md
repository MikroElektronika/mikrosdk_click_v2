
---
# DC Motor 28 FNG Click

> [DC Motor 28 FNG Click](https://www.mikroe.com/?pid_product=MIKROE-6506) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6506&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2025.
- **Type**          : ADC type

# Software Support

## Example Description

> This example demonstrates the use of the DC Motor 28 FNG Click board. It initializes the Click driver, 
calibrates the offset for accurate current measurements, and then controls the motor in different states 
while measuring and logging the output current in milliamps (mA).

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DCMotor28FNG

### Example Key Functions

- `dcmotor28fng_cfg_setup` Config Object Initialization function.
```c
void dcmotor28fng_cfg_setup ( dcmotor28fng_cfg_t *cfg );
```

- `dcmotor28fng_init` Initialization function.
```c
err_t dcmotor28fng_init ( dcmotor28fng_t *ctx, dcmotor28fng_cfg_t *cfg );
```

- `dcmotor28fng_drive_motor` This function drives the motor in the selected PWM control mode state.
```c
void dcmotor28fng_drive_motor ( dcmotor28fng_t *ctx, uint8_t state );
```

- `dcmotor28fng_calib_offset` This function calibrates the zero current offset value.
```c
err_t dcmotor28fng_calib_offset ( dcmotor28fng_t *ctx );
```

- `dcmotor28fng_get_out_current` This function reads the current output measurement in mA.
```c
err_t dcmotor28fng_get_out_current ( dcmotor28fng_t *ctx, float *current );
```

### Application Init

> Initializes the logger and the DC Motor 28 FNG Click driver and performs offset calibration for current measurements.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dcmotor28fng_cfg_t dcmotor28fng_cfg;  /**< Click config object. */

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
    dcmotor28fng_cfg_setup( &dcmotor28fng_cfg );
    DCMOTOR28FNG_MAP_MIKROBUS( dcmotor28fng_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == dcmotor28fng_init( &dcmotor28fng, &dcmotor28fng_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DCMOTOR28FNG_ERROR == dcmotor28fng_calib_offset ( &dcmotor28fng ) )
    {
        log_error( &logger, " Offset calibration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Controls the motor in a sequence of states: FORWARD, BRAKE, REVERSE, and COAST. In each state, the output 
current is measured and logged, providing insights into the motor's performance and consumption.

```c
void application_task ( void )
{
    float current = 0;

    log_printf( &logger, " Motor state : FORWARD\r\n" );
    dcmotor28fng_drive_motor ( &dcmotor28fng, DCMOTOR28FNG_MOTOR_FORWARD );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    if ( DCMOTOR28FNG_OK == dcmotor28fng_get_out_current ( &dcmotor28fng, &current ) ) 
    {
        log_printf( &logger, " Current : %.3f mA\r\n\n", current );
    }

    log_printf( &logger, " Motor state : BRAKE\r\n" );
    dcmotor28fng_drive_motor ( &dcmotor28fng, DCMOTOR28FNG_MOTOR_BRAKE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    if ( DCMOTOR28FNG_OK == dcmotor28fng_get_out_current ( &dcmotor28fng, &current ) ) 
    {
        log_printf( &logger, " Current : %.3f mA\r\n\n", current );
    }

    log_printf( &logger, " Motor state : REVERSE\r\n" );
    dcmotor28fng_drive_motor ( &dcmotor28fng, DCMOTOR28FNG_MOTOR_REVERSE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    if ( DCMOTOR28FNG_OK == dcmotor28fng_get_out_current ( &dcmotor28fng, &current ) ) 
    {
        log_printf( &logger, " Current : %.3f mA\r\n\n", current );
    }

    log_printf( &logger, " Motor state : COAST\r\n" );
    dcmotor28fng_drive_motor ( &dcmotor28fng, DCMOTOR28FNG_MOTOR_COAST );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    if ( DCMOTOR28FNG_OK == dcmotor28fng_get_out_current ( &dcmotor28fng, &current ) ) 
    {
        log_printf( &logger, " Current : %.3f mA\r\n\n", current );
    }
}
```

### Note

> Ensure the PMODE switch is set to position 1 (HIGH), the motor is properly connected to the board
OUT1 and OUT2 terminals, and the proper power supply is connected to the input terminal.

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
