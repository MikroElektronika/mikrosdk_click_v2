
---
# EasyPull Click

> [EasyPull Click](https://www.mikroe.com/?pid_product=MIKROE-6053) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6053&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Dec 2023.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of EasyPull Click boards.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.EasyPull

### Example Key Functions

- `easypull_cfg_setup` Config Object Initialization function.
```c
void easypull_cfg_setup ( easypull_cfg_t *cfg );
```

- `easypull_init` Initialization function.
```c
err_t easypull_init ( easypull_t *ctx, easypull_cfg_t *cfg );
```

- `easypull_get_an_pin` This function reads the state of the AN pin of EasyPull Click board.
```c
uint8_t easypull_get_an_pin ( easypull_t *ctx );
```

- `easypull_get_rst_pin` This function reads the state of the RST pin of EasyPull Click board.
```c
uint8_t easypull_get_rst_pin ( easypull_t *ctx );
```

- `easypull_get_cs_pin` This function reads the state of the CS pin of EasyPull Click board.
```c
uint8_t easypull_get_cs_pin ( easypull_t *ctx );
```

### Application Init

> Initializes the driver and USB UART logger.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    easypull_cfg_t easypull_cfg;  /**< Click config object. */

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
    easypull_cfg_setup( &easypull_cfg );
    EASYPULL_MAP_MIKROBUS( easypull_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == easypull_init( &easypull, &easypull_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> It checks the state of the pins and displays their state on the USB UART.

```c
void application_task ( void ) 
{
    if ( EASYPULL_PIN_STATE_HIGH == easypull_get_an_pin( &easypull ) )
    {
        log_printf( &logger, " AN pin state: HIGH \n" );
    }
    else
    {
        log_printf( &logger, " AN pin state: LOW \n" );
    }

    if ( EASYPULL_PIN_STATE_HIGH == easypull_get_rst_pin( &easypull ) )
    {
        log_printf( &logger, " RST pin state: HIGH \n" );
    }
    else
    {
        log_printf( &logger, " RST pin state: LOW \n" );
    }

    if ( EASYPULL_PIN_STATE_HIGH == easypull_get_cs_pin( &easypull ) )
    {
        log_printf( &logger, " CS pin state: HIGH \n" );
    }
    else
    {
        log_printf( &logger, " CS pin state: LOW \n" );
    }

    if ( EASYPULL_PIN_STATE_HIGH == easypull_get_pwm_pin( &easypull ) )
    {
        log_printf( &logger, " PWM pin state: HIGH \n" );
    }
    else
    {
        log_printf( &logger, " PWM pin state: LOW \n" );
    }

    if ( EASYPULL_PIN_STATE_HIGH == easypull_get_int_pin( &easypull ) )
    {
        log_printf( &logger, " INT pin state: HIGH \n" );
    }
    else
    {
        log_printf( &logger, " INT pin state: LOW \n" );
    }
    log_printf( &logger, "- - - - - - - - - - - - - \r\n" );
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
