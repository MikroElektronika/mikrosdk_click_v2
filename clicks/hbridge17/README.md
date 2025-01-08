
---
# H-Bridge 17 Click

> [H-Bridge 17 Click](https://www.mikroe.com/?pid_product=MIKROE-6051) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6051&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2023.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of the H-Bridge 17 Click board by
> driving the motor in both directions with braking and freewheeling. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HBridge17

### Example Key Functions

- `hbridge17_cfg_setup` Config Object Initialization function.
```c
void hbridge17_cfg_setup ( hbridge17_cfg_t *cfg );
```

- `hbridge17_init` Initialization function.
```c
err_t hbridge17_init ( hbridge17_t *ctx, hbridge17_cfg_t *cfg );
```

- `hbridge17_set_out_state` This function is used to set the output state of the H-Bridge 17 Click board.
```c
err_t hbridge17_set_out_state ( hbridge17_t *ctx, hbridge17_out_state_t out_state );
```

- `hbridge17_ic_enable` This function enables driver IC by setting the EN (RST) pin on the high level of the H-Bridge 17 Click board.
```c
void hbridge17_ic_enable ( hbridge17_t *ctx );
```

- `hbridge17_fault_indication` This function reads the state of the FLT (INT) pin of the H-Bridge 17 Click board.
```c
uint8_t hbridge17_fault_indication ( hbridge17_t *ctx );
```

### Application Init

> Initializes the driver and enable H-Bridge driver IC.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hbridge17_cfg_t hbridge17_cfg;  /**< Click config object. */

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
    hbridge17_cfg_setup( &hbridge17_cfg );
    HBRIDGE17_MAP_MIKROBUS( hbridge17_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == hbridge17_init( &hbridge17, &hbridge17_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    hbridge17_ic_enable( &hbridge17 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> The demo application drives the motor in both directions 
> with coasting and braking in between, every state lasts 5 seconds.

```c
void application_task ( void ) 
{
    if ( HBRIDGE17_OK == hbridge17_set_out_state( &hbridge17, HBRIDGE17_DRIVE_MOTOR_FORWARD ) )
    {
        log_printf( &logger, " Motor in forward mode.\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }

    if ( HBRIDGE17_OK == hbridge17_set_out_state( &hbridge17, HBRIDGE17_DRIVE_MOTOR_BRAKE ) )
    {
        log_printf( &logger, " Motor brake is on.\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    
    if ( HBRIDGE17_OK == hbridge17_set_out_state( &hbridge17, HBRIDGE17_DRIVE_MOTOR_REVERSE ) )
    {
        log_printf( &logger, "Motor in reverse mode.\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }

    if ( HBRIDGE17_OK == hbridge17_set_out_state( &hbridge17, HBRIDGE17_DRIVE_MOTOR_FREEWHEEL ) )
    {
        log_printf( &logger, " Motor is coasting.\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    log_printf( &logger, "-------------------\r\n" );
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
