
---
# 1-Wire Switch Click

> [1-Wire Switch Click](https://www.mikroe.com/?pid_product=MIKROE-5589) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5589&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jan 2023.
- **Type**          : One Wire type

# Software Support

## Example Description

> This library contains API for 1-Wire Switch Click driver. 
The library initializes and defines the 1-Wire bus drivers to 
write and read data for state programmable I/O, 
as well as the default configuration.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.c1WireSwitch

### Example Key Functions

- `c1wireswitch_cfg_setup` Config Object Initialization function.
```c
void c1wireswitch_cfg_setup ( c1wireswitch_cfg_t *cfg );
```

- `c1wireswitch_init` Initialization function.
```c
err_t c1wireswitch_init ( c1wireswitch_t *ctx, c1wireswitch_cfg_t *cfg );
```

- `c1wireswitch_default_cfg` Click Default Configuration function.
```c
err_t c1wireswitch_default_cfg ( c1wireswitch_t *ctx );
```

- `c1wireswitch_set_pio_state` 1-Wire Switch write specific programmable I/O state function.
```c
err_t c1wireswitch_set_pio_state ( c1wireswitch_t *ctx, uint8_t pio_a, uint8_t pio_b );
```

- `c1wireswitch_get_pio_state` 1-Wire Switch read specific programmable I/O state function.
```c
err_t c1wireswitch_get_pio_state ( c1wireswitch_t *ctx, uint8_t *pio_a, uint8_t *pio_b );
```

- `c1wireswitch_get_pio_latch_state` 1-Wire Switch read programmable I/O latch state function.
```c
err_t c1wireswitch_get_pio_latch_state ( c1wireswitch_t *ctx, uint8_t *pio_a_latch, uint8_t *pio_b_latch );
```

### Application Init

> Initializes the driver and performs default configuration and sets 
the PIO A to OFF and PIO B to ON state.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c1wireswitch_cfg_t c1wireswitch_cfg;  /**< Click config object. */

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
    c1wireswitch_cfg_setup( &c1wireswitch_cfg );
    C1WIRESWITCH_MAP_MIKROBUS( c1wireswitch_cfg, MIKROBUS_1 );
    if ( ONE_WIRE_ERROR == c1wireswitch_init( &c1wireswitch, &c1wireswitch_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C1WIRESWITCH_ERROR == c1wireswitch_default_cfg ( &c1wireswitch ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    c1wireswitch_set_pio_state( &c1wireswitch, C1WIRESWITCH_PIOA_OFF, C1WIRESWITCH_PIOB_ON );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> This example demonstrates the use of the 1-Wire Switch Click board by changing the PIO A state, 
which is controlling the LED, every time the state of PIO B changes. 
Change on the PIO B happens when the button is pushed.

```c
void application_task ( void ) 
{
    uint8_t pio_a = 0;
    uint8_t pio_b = 0;
    
    c1wireswitch_get_pio_state( &c1wireswitch, &pio_a, &pio_b );
    
    if ( pio_b == C1WIRESWITCH_PIOB_OFF )
    {
        if ( state == 0 )
        {
            c1wireswitch_set_pio_state( &c1wireswitch, C1WIRESWITCH_PIOA_ON, C1WIRESWITCH_PIOB_ON );
            log_printf( &logger, " Button is pressed, LED is ON. \r\n " );
            state = 1;
        }
        else
        {
            c1wireswitch_set_pio_state( &c1wireswitch, C1WIRESWITCH_PIOA_OFF, C1WIRESWITCH_PIOB_ON );
            log_printf( &logger, " Button is pressed, LED is OFF. \r\n " );
            state = 0;
        }
        Delay_ms ( 100 );
    }
    Delay_ms ( 100 );
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
