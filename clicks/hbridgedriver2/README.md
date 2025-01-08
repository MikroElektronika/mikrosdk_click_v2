
---
# H-Bridge Driver 2 Click

> [H-Bridge Driver 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4931) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4931&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Oct 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This library contains API for the H-Bridge Driver 2 Click driver.
> This demo application shows the use of a H-Bridge Driver 2 Click board&trade;.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HBridgeDriver2

### Example Key Functions

- `hbridgedriver2_cfg_setup` Config Object Initialization function.
```c
void hbridgedriver2_cfg_setup ( hbridgedriver2_cfg_t *cfg );
```

- `hbridgedriver2_init` Initialization function.
```c
err_t hbridgedriver2_init ( hbridgedriver2_t *ctx, hbridgedriver2_cfg_t *cfg );
```

- `hbridgedriver2_default_cfg` Click Default Configuration function.
```c
err_t hbridgedriver2_default_cfg ( hbridgedriver2_t *ctx );
```

- `hbridgedriver2_run_forward` H-Bridge Driver 2 run forward function.
```c
err_t hbridgedriver2_run_forward ( hbridgedriver2_t *ctx, uint8_t *global_fault );
```

- `hbridgedriver2_run_backward` H-Bridge Driver 2 run backward function.
```c
err_t hbridgedriver2_run_backward ( hbridgedriver2_t *ctx, uint8_t *global_fault );
```

- `hbridgedriver2_stop_with_brake` H-Bridge Driver 2 stop with brake function.
```c
err_t hbridgedriver2_stop_with_brake ( hbridgedriver2_t *ctx, uint8_t *global_fault );
```

### Application Init

> Initialization of SPI, PWM module and log UART.
> After driver initialization and default settings,
> the application displays the device ID data, sets PWM duty cycle to 50% 
> and start PWM module.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;                        /**< Logger config object. */
    hbridgedriver2_cfg_t hbridgedriver2_cfg;  /**< Click config object. */

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
    hbridgedriver2_cfg_setup( &hbridgedriver2_cfg );
    HBRIDGEDRIVER2_MAP_MIKROBUS( hbridgedriver2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == hbridgedriver2_init( &hbridgedriver2, &hbridgedriver2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms ( 1000 );
    
    hbridgedriver2_enable( &hbridgedriver2 );
    Delay_ms ( 100 );
    log_info( &logger, "  Default config " );
    
    if ( HBRIDGEDRIVER2_ERROR == hbridgedriver2_default_cfg ( &hbridgedriver2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    Delay_ms ( 1000 );

    log_printf( &logger, "--------------------------------\r\n" );
    Delay_ms ( 100 );
    
    hbridgedriver2_get_device_id( &hbridgedriver2, &global_fault, &dev_id );
    Delay_ms ( 100 );  
    log_printf( &logger, " ID header      : 0x%.4X \r\n", dev_id.id_header ); 
    log_printf( &logger, " Version        : 0x%.4X \r\n", dev_id.version );
    log_printf( &logger, " Product Code 1 : 0x%.4X \r\n", dev_id.product_code_1 );
    log_printf( &logger, " Product Code 2 : 0x%.4X \r\n", dev_id.product_code_2 );
    log_printf( &logger, " SPI Frame ID   : 0x%.4X \r\n", dev_id.spi_frame_id );
    log_printf( &logger, "--------------------------------\r\n" );
    Delay_ms ( 100 );
    
    hbridgedriver2_set_duty_cycle ( &hbridgedriver2, 0.5 );
    hbridgedriver2_pwm_start( &hbridgedriver2 );
    Delay_ms ( 100 );
    
    log_printf( &logger, "\t>>> START <<<\r\n" );
    display_status( );
    Delay_ms ( 1000 );
}
```

### Application Task

> This example demonstrates the use of the H-Bridge Driver 2 Click board&trade;.
> The application turns connected MOSFETs gates high or low in order to drive 
> the motor forward, backward, stop with brake or stop.
> Results are being sent to the Usart Terminal, where you can track their changes.

```c
void application_task ( void )
{
    log_printf( &logger, "\t>>> Run Forward\r\n" );
    hbridgedriver2_run_forward( &hbridgedriver2, &global_fault );
    display_status( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "\t>>> Stop With Brake\r\n" );
    hbridgedriver2_stop_with_brake( &hbridgedriver2, &global_fault );
    display_status( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "\t>>> Run Backward\r\n" );
    hbridgedriver2_run_backward( &hbridgedriver2, &global_fault );
    display_status( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "\t>>> Stop\r\n" );
    hbridgedriver2_stop( &hbridgedriver2, &global_fault );
    display_status( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

#### Additional Function

- `display_status` Display status function.
```c
static void display_status ( void );
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
