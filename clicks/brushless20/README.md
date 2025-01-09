
---
# Brushless 20 Click

> [Brushless 20 Click](https://www.mikroe.com/?pid_product=MIKROE-5294) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5294&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Brushless 20 Click board by driving the motor in both directions at different speeds.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless20

### Example Key Functions

- `brushless20_cfg_setup` Config Object Initialization function.
```c
void brushless20_cfg_setup ( brushless20_cfg_t *cfg );
```

- `brushless20_init` Initialization function.
```c
err_t brushless20_init ( brushless20_t *ctx, brushless20_cfg_t *cfg );
```

- `brushless20_default_cfg` Click Default Configuration function.
```c
err_t brushless20_default_cfg ( brushless20_t *ctx );
```

- `brushless20_perform_com_sequence` This function performs a single commutation sequence for the selected rotation direction at a desired speed.
```c
err_t brushless20_perform_com_sequence ( brushless20_t *ctx, uint8_t dir, uint8_t speed );
```

- `brushless20_drive_motor` This function drives the motor for a desired time by performing multiple commutation sequences for the selected rotation direction at a desired speed.
```c
err_t brushless20_drive_motor ( brushless20_t *ctx, uint8_t dir, uint8_t speed, uint32_t time_ms );
```

- `brushless20_get_fault_pin` This function returns the fault pin logic state.
```c
err_t brushless20_get_fault_pin ( brushless20_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless20_cfg_t brushless20_cfg;  /**< Click config object. */

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
    brushless20_cfg_setup( &brushless20_cfg );
    BRUSHLESS20_MAP_MIKROBUS( brushless20_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == brushless20_init( &brushless20, &brushless20_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS20_ERROR == brushless20_default_cfg ( &brushless20 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Drives the motor in both directions and changes the motor speed every 3 seconds approximately. The current driving direction and speed will be displayed on the USB UART.

```c
void application_task ( void )
{
    log_printf ( &logger, "\r\n Driving motor clockwise \r\n" );
    for ( uint8_t speed = BRUSHLESS20_SPEED_MIN; speed <= BRUSHLESS20_SPEED_MAX; speed += 20 )
    {
        log_printf ( &logger, " Speed: %u\r\n", ( uint16_t ) speed );
        if ( BRUSHLESS20_OK != brushless20_drive_motor ( &brushless20, BRUSHLESS20_DIR_CW, speed, 3000 ) )
        {
            log_error ( &logger, " Drive motor " );
        }
    }
    Delay_ms ( 1000 );
    log_printf ( &logger, "\r\n Driving motor counter-clockwise \r\n" );
    for ( uint8_t speed = BRUSHLESS20_SPEED_MIN; speed <= BRUSHLESS20_SPEED_MAX; speed += 20 )
    {
        log_printf ( &logger, " Speed: %u\r\n", ( uint16_t ) speed );
        if ( BRUSHLESS20_OK != brushless20_drive_motor ( &brushless20, BRUSHLESS20_DIR_CCW, speed, 3000 ) )
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
