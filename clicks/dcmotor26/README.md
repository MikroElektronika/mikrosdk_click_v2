
---
# DC Motor 26 Click

> [DC Motor 26 Click](https://www.mikroe.com/?pid_product=MIKROE-5655) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5655&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2023.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of DC Motor 26 Click board by controlling the speed
of DC motor over PWM duty cycle as well as displaying the motor current consumption.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DCMotor26

### Example Key Functions

- `dcmotor26_cfg_setup` Config Object Initialization function.
```c
void dcmotor26_cfg_setup ( dcmotor26_cfg_t *cfg );
```

- `dcmotor26_init` Initialization function.
```c
err_t dcmotor26_init ( dcmotor26_t *ctx, dcmotor26_cfg_t *cfg );
```

- `dcmotor26_default_cfg` Click Default Configuration function.
```c
err_t dcmotor26_default_cfg ( dcmotor26_t *ctx );
```

- `dcmotor26_get_motor_current` DC Motor 26 get motor current function.
```c
err_t dcmotor26_get_motor_current ( dcmotor26_t *ctx, float *current );
```

- `dcmotor26_set_ch1_operation_mode` DC Motor 26 set ch1 operation mode function.
```c
err_t dcmotor26_set_ch1_operation_mode ( dcmotor26_t *ctx, uint8_t mode );
```

- `dcmotor26_set_cm_sel_pin` DC Motor 26 set cm sel pin function.
```c
err_t dcmotor26_set_cm_sel_pin ( dcmotor26_t *ctx, uint8_t state );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dcmotor26_cfg_t dcmotor26_cfg;  /**< Click config object. */

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
    dcmotor26_cfg_setup( &dcmotor26_cfg );
    DCMOTOR26_MAP_MIKROBUS( dcmotor26_cfg, MIKROBUS_1 );
    if ( DCMOTOR26_OK != dcmotor26_init( &dcmotor26, &dcmotor26_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DCMOTOR26_OK != dcmotor26_default_cfg ( &dcmotor26 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Changes the operation mode and motor speed by setting the PWM duty cycle and then calculates
the motor current consumption for that speed. All data is being logged on the USB UART where you can track changes.

```c
void application_task ( void )
{
    if ( DCMOTOR26_OK == dcmotor26_set_ch1_operation_mode ( &dcmotor26, DCMOTOR26_MODE_OUTPUT_OFF ) )
    {
        log_printf ( &logger, " MODE: OFF\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    if ( DCMOTOR26_OK == dcmotor26_set_ch1_operation_mode ( &dcmotor26, DCMOTOR26_MODE_FORWARD ) )
    {
        dcmotor26_set_cm_sel_pin ( &dcmotor26, DCMOTOR26_PIN_LOW_LEVEL );
        for ( uint16_t duty = 0; duty <= DCMOTOR26_CONFIG56_DUTY_PERIOD_MAX; duty += 100 )
        {
            float current;
            log_printf ( &logger, " MODE: FORWARD\r\n" );
            if ( DCMOTOR26_OK == dcmotor26_set_ch1_duty_period ( &dcmotor26, duty ) )
            {
                log_printf ( &logger, " Duty: %u\r\n", duty );
            }
            if ( DCMOTOR26_OK == dcmotor26_get_motor_current ( &dcmotor26, &current ) )
            {
                log_printf ( &logger, " Current: %.3f A\r\n\n", current );
            }
            Delay_ms ( 500 );
        }
    }
    if ( DCMOTOR26_OK == dcmotor26_set_ch1_operation_mode ( &dcmotor26, DCMOTOR26_MODE_BRAKE ) )
    {
        log_printf ( &logger, " MODE: BRAKE\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    if ( DCMOTOR26_OK == dcmotor26_set_ch1_operation_mode ( &dcmotor26, DCMOTOR26_MODE_REVERSE ) )
    {
        dcmotor26_set_cm_sel_pin ( &dcmotor26, DCMOTOR26_PIN_HIGH_LEVEL );
        for ( uint16_t duty = 0; duty <= DCMOTOR26_CONFIG56_DUTY_PERIOD_MAX; duty += 100 )
        {
            float current;
            log_printf ( &logger, " MODE: REVERSE\r\n" );
            if ( DCMOTOR26_OK == dcmotor26_set_ch1_duty_period ( &dcmotor26, duty ) )
            {
                log_printf ( &logger, " Duty: %u\r\n", duty );
            }
            if ( DCMOTOR26_OK == dcmotor26_get_motor_current ( &dcmotor26, &current ) )
            {
                log_printf ( &logger, " Current: %.3f A\r\n\n", current );
            }
            Delay_ms ( 500 );
        }
    }
}
```

### Note

> The Click board swiches should be set as follows: SW 1-2-3-4 : H-H-L-L
This sets the Click board as a SPI controlled single-channel device so the motor should be connected to OUT1/2 and OUT3/4.

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
