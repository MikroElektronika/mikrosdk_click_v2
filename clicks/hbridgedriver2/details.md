
---
# H-Bridge Driver 2 Click

> H-Bridge Driver 2 Click is a compact add-on board that contains an H-bridge gate driver, also known as a full-bridge pre-driver. This board features the NCV7535, a monolithic H−bridge pre-driver for a DC motor with an enhanced feature set, useful in automotive systems from ON Semiconductor. The gate driver channels are independently controlled by a 24-bit SPI interface, allowing this Click board™ to be optionally configured in a single or dual H-bridge mode. It has a wide operating voltage range from 6V to 18V with built-in protection features against short-circuit, under/over voltage, overcurrent, and overtemperature conditions. This Click board™ is suitable to drive external MOSFETs, thus providing control of a DC-motor.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hbridgedriver2click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/h-bridge-driver-2-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Oct 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the HBridgeDriver2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for HBridgeDriver2 Click driver.

#### Standard key functions :

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

#### Example key functions :

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

## Example Description

> This library contains API for the H-Bridge Driver 2 Click driver.
> This demo application shows the use of a H-Bridge Driver 2 Click board™.

**The demo application is composed of two sections :**

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

> This example demonstrates the use of the H-Bridge Driver 2 Click board™.
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

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.HBridgeDriver2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all MikroElektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
