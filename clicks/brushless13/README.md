
---
# Brushless 13 Click

> [Brushless 13 Click](https://www.mikroe.com/?pid_product=MIKROE-5886) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5886&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Brushless 13 Click board by driving the 
  motor in both directions at different speeds.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless13

### Example Key Functions

- `brushless13_cfg_setup` Config Object Initialization function.
```c
void brushless13_cfg_setup ( brushless13_cfg_t *cfg );
```

- `brushless13_init` Initialization function.
```c
err_t brushless13_init ( brushless13_t *ctx, brushless13_cfg_t *cfg );
```

- `brushless13_default_cfg` Click Default Configuration function.
```c
err_t brushless13_default_cfg ( brushless13_t *ctx );
```

- `brushless13_set_mode` Brushless 13 set mode pin function.
```c
void brushless13_set_mode ( brushless13_t *ctx, uint8_t mode_sel );
```

- `brushless13_get_flt_pin` Brushless 13 get fault pin function.
```c
uint8_t brushless13_get_flt_pin ( brushless13_t *ctx );
```

- `brushless13_drive_motor` Brushless 13 drive motor function.
```c
err_t brushless13_drive_motor ( brushless13_t *ctx, uint8_t dir, uint8_t speed, uint32_t time_ms );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless13_cfg_t brushless13_cfg;  /**< Click config object. */

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
    brushless13_cfg_setup( &brushless13_cfg );
    BRUSHLESS13_MAP_MIKROBUS( brushless13_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == brushless13_init( &brushless13, &brushless13_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS13_ERROR == brushless13_default_cfg ( &brushless13 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Drives the motor in both directions and changes the motor speed approximately every 2 seconds.
  The driving direction and speed will be displayed on the USB UART.

```c
void application_task ( void ) 
{
    log_printf ( &logger, "\r\n Driving motor clockwise \r\n" );
    for ( uint8_t speed = BRUSHLESS13_SPEED_MIN; speed <= BRUSHLESS13_SPEED_MAX; speed += 20 )
    {
        log_printf ( &logger, " Speed gain: %u\r\n", ( uint16_t ) speed );
        if ( BRUSHLESS13_OK != brushless13_drive_motor ( &brushless13, BRUSHLESS13_DIR_CW, speed, 2000 ) )
        {
            log_error ( &logger, " Drive motor " );
        }
    }
    Delay_ms ( 1000 );
    
    log_printf ( &logger, "\r\n Driving motor counter-clockwise \r\n" );
    for ( uint8_t speed = BRUSHLESS13_SPEED_MIN; speed <= BRUSHLESS13_SPEED_MAX; speed += 20 )
    {
        log_printf ( &logger, " Speed gain: %u\r\n", ( uint16_t ) speed );
        if ( BRUSHLESS13_OK != brushless13_drive_motor ( &brushless13, BRUSHLESS13_DIR_CCW, speed, 2000 ) )
        {
            log_error ( &logger, " Drive motor " );
        }
    }
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
