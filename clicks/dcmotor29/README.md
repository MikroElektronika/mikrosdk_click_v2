
---
# DC Motor 29 Click

> [DC Motor 29 Click](https://www.mikroe.com/?pid_product=MIKROE-5905) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5905&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Sep 2023.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of the DC Motor 29 Click board by driving the 
  motor in both directions with braking and coasting in between.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DCMotor29

### Example Key Functions

- `dcmotor29_cfg_setup` Config Object Initialization function.
```c
void dcmotor29_cfg_setup ( dcmotor29_cfg_t *cfg );
```

- `dcmotor29_init` Initialization function.
```c
err_t dcmotor29_init ( dcmotor29_t *ctx, dcmotor29_cfg_t *cfg );
```

- `dcmotor29_default_cfg` Click Default Configuration function.
```c
err_t dcmotor29_default_cfg ( dcmotor29_t *ctx );
```

- `dcmotor29_register_write` DC Motor 29 data register writing function.
```c
err_t dcmotor29_register_write ( dcmotor29_t *ctx, uint8_t reg, uint8_t data_in );
```

- `dcmotor29_port_expander_read` DC Motor 29 port ecpander read register function.
```c
err_t dcmotor29_port_expander_read ( dcmotor29_t *ctx, uint8_t reg, uint8_t *data_out );
```

- `dcmotor29_drive_motor` DC Motor 29 drive motor function.
```c
err_t dcmotor29_drive_motor ( dcmotor29_t *ctx, uint8_t state );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dcmotor29_cfg_t dcmotor29_cfg;  /**< Click config object. */

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
    dcmotor29_cfg_setup( &dcmotor29_cfg );
    DCMOTOR29_MAP_MIKROBUS( dcmotor29_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == dcmotor29_init( &dcmotor29, &dcmotor29_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DCMOTOR29_ERROR == dcmotor29_default_cfg ( &dcmotor29 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
       
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Drives the motor in both directions with coasting and braking in between, every sate is lasting 5 seconds.

```c
void application_task ( void )
{
    dcmotor29_drive_motor( &dcmotor29, DCMOTOR29_DRIVE_MOTOR_CW );
    log_printf( &logger, " Driving motor Clockwise \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    dcmotor29_drive_motor( &dcmotor29, DCMOTOR29_DRIVE_MOTOR_BRAKE );
    log_printf( &logger, " Brake is on \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    dcmotor29_drive_motor( &dcmotor29, DCMOTOR29_DRIVE_MOTOR_CCW );
    log_printf( &logger, " Driving motor counter-clockwise \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    dcmotor29_drive_motor( &dcmotor29, DCMOTOR29_DRIVE_MOTOR_COASTING );
    log_printf( &logger, " Driving motor Coasting \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
