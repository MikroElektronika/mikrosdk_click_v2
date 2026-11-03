
---
# Ultrasonic 2 Click

> [Ultrasonic 2 Click](https://www.mikroe.com/?pid_product=MIKROE-3302) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3302&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2026.
- **Type**          : UART type

# Software Support

## Example Description

> This example measures the distance to the first object detected by Ultrasonic 2 Click
> and displays the result in millimetres on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ultrasonic2

### Example Key Functions

- `ultrasonic2_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void ultrasonic2_cfg_setup ( ultrasonic2_cfg_t *cfg );
```

- `ultrasonic2_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t ultrasonic2_init ( ultrasonic2_t *ctx, ultrasonic2_cfg_t *cfg );
```

- `ultrasonic2_default_cfg` This function executes a default configuration of Ultrasonic 2 Click board.
```c
err_t ultrasonic2_default_cfg ( ultrasonic2_t *ctx );
```

- `ultrasonic2_get_measurement` This function sends a preset 1 burst, waits for the record interval and reads the first echo.
```c
err_t ultrasonic2_get_measurement ( ultrasonic2_t *ctx, ultrasonic2_measurement_t *measurement );
```

- `ultrasonic2_write_register` This function writes a PGA460 register by using a checksummed UART command.
```c
err_t ultrasonic2_write_register ( ultrasonic2_t *ctx, uint8_t reg, uint8_t value );
```

- `ultrasonic2_read_register` This function reads a PGA460 register and checks the diagnostic byte and response checksum.
```c
err_t ultrasonic2_read_register ( ultrasonic2_t *ctx, uint8_t reg, uint8_t *value );
```

### Application Init

> Initializes the UART, enables the boost converter and loads the 40 kHz ranging profile.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ultrasonic2_cfg_t ultrasonic2_cfg;  /**< Click config object. */

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
    ultrasonic2_cfg_setup( &ultrasonic2_cfg );
    ULTRASONIC2_MAP_MIKROBUS( ultrasonic2_cfg, MIKROBUS_POSITION_ULTRASONIC2 );
    if ( UART_ERROR == ultrasonic2_init( &ultrasonic2, &ultrasonic2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    // Apply the receiver and threshold profile once after each power-up.
    if ( ULTRASONIC2_OK != ultrasonic2_default_cfg( &ultrasonic2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads one distance measurement, displays the result or an error, and waits 500 ms.

```c
void application_task ( void )
{
    ultrasonic2_measurement_t measurement;

    // The library completes one burst and validates its reply before updating the measurement.
    err_t status = ultrasonic2_get_measurement( &ultrasonic2, &measurement );
    if ( ULTRASONIC2_OK == status )
    {
        log_printf( &logger, " Distance: %u mm\r\n", measurement.distance_mm );
    }
    else if ( ULTRASONIC2_NO_OBJECT == status )
    {
        log_info( &logger, " No object detected." );
    }
    else
    {
        log_error( &logger, " Measurement failed." );
    }

    // Leave a quiet interval between bursts and limit the terminal output rate.
    Delay_ms( 500 );
}
```

### Note

> Connect an external pull-up resistor from mikroBUS RX (PGA460 TXD) to a logic rail
> compatible with the host UART input. PGA460 TXD is high impedance between replies.
> Distance conversion uses a speed of sound of 343 m/s and the configured profile timing compensation.

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
