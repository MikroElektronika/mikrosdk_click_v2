
---
# Brushless 26 Click

> [Brushless 26 Click](https://www.mikroe.com/?pid_product=MIKROE-5843) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5843&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : May 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Brushless 26 Click board by driving the 
  motor in both directions at different speeds.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless26

### Example Key Functions

- `brushless26_cfg_setup` Config Object Initialization function.
```c
void brushless26_cfg_setup ( brushless26_cfg_t *cfg );
```

- `brushless26_init` Initialization function.
```c
err_t brushless26_init ( brushless26_t *ctx, brushless26_cfg_t *cfg );
```

- `brushless26_default_cfg` Click Default Configuration function.
```c
err_t brushless26_default_cfg ( brushless26_t *ctx );
```

- `brushless26_reset_port_exp` Brushless 26 reset port expander function.
```c
void brushless26_reset_port_exp ( brushless26_t *ctx );
```

- `brushless26_set_pins` Brushless 26 set pins function.
```c
err_t brushless26_set_pins ( brushless26_t *ctx, uint8_t set_mask, uint8_t clr_mask );
```

- `brushless26_drive_motor` Brushless 26 drive motor function.
```c
err_t brushless26_drive_motor ( brushless26_t *ctx, uint8_t dir, uint8_t speed, uint32_t time_ms );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless26_cfg_t brushless26_cfg;  /**< Click config object. */

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
    brushless26_cfg_setup( &brushless26_cfg );
    BRUSHLESS26_MAP_MIKROBUS( brushless26_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == brushless26_init( &brushless26, &brushless26_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS26_ERROR == brushless26_default_cfg ( &brushless26 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task");
}
```

### Application Task

> Drives the motor in both directions and changes the motor speed approximately every 2 seconds.
  The driving direction and speed will be displayed on the USB UART.

```c
void application_task ( void ) 
{
    log_printf ( &logger, "\r\n Driving motor clockwise \r\n" );
    for ( uint8_t speed = BRUSHLESS26_SPEED_MIN; speed <= BRUSHLESS26_SPEED_MAX; speed += 20 )
    {
        log_printf ( &logger, " Speed gain: %u\r\n", ( uint16_t ) speed );
        if ( BRUSHLESS26_OK != brushless26_drive_motor ( &brushless26, BRUSHLESS26_DIR_CW, speed, 2000 ) )
        {
            log_error ( &logger, " Drive motor " );
        }
    }
    Delay_ms ( 1000 );
    
    log_printf ( &logger, "\r\n Driving motor counter-clockwise \r\n" );
    for ( uint8_t speed = BRUSHLESS26_SPEED_MIN; speed <= BRUSHLESS26_SPEED_MAX; speed += 20 )
    {
        log_printf ( &logger, " Speed gain: %u\r\n", ( uint16_t ) speed );
        if ( BRUSHLESS26_OK != brushless26_drive_motor ( &brushless26, BRUSHLESS26_DIR_CCW, speed, 2000 ) )
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
