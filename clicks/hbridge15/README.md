\mainpage Main Page

---
# H-Bridge 15 Click

> H-Bridge 15 Click is a compact add-on board with an H-Bridge gate driver, also known as a full-bridge pre-driver. This board features the DRV8834, a dual-bridge stepper or DC motor driver from Texas Instruments. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hbridge15_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/h-bridge-15-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the H-Bridge 15 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for H-Bridge 15 Click driver.

#### Standard key functions :

- `hbridge15_cfg_setup` Config Object Initialization function.
```c
void hbridge15_cfg_setup ( hbridge15_cfg_t *cfg );
```

- `hbridge15_init` Initialization function.
```c
err_t hbridge15_init ( hbridge15_t *ctx, hbridge15_cfg_t *cfg );
```

- `hbridge15_default_cfg` Click Default Configuration function.
```c
err_t hbridge15_default_cfg ( hbridge15_t *ctx );
```

#### Example key functions :

- `hbridge15_set_pins` H-Bridge 15 set pins function.
```c
err_t hbridge15_set_pins ( hbridge15_t *ctx, uint8_t set_mask, uint8_t clr_mask );
```

- `hbridge15_set_sleep` H-Bridge 15 set sleep function.
```c
err_t hbridge15_set_sleep ( hbridge15_t *ctx, uint8_t sleep_state );
```

- `hbridge15_set_out_state` H-Bridge 15 set output function.
```c
err_t hbridge15_set_out_state ( hbridge15_t *ctx, uint8_t out_state );
```

## Example Description

> This example demonstrates the use of the H-Bridge 15 Click board by
  driving the motor in both directions with braking and freewheeling. 

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hbridge15_cfg_t hbridge15_cfg;  /**< Click config object. */

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
    hbridge15_cfg_setup( &hbridge15_cfg );
    HBRIDGE15_MAP_MIKROBUS( hbridge15_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == hbridge15_init( &hbridge15, &hbridge15_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HBRIDGE15_ERROR == hbridge15_default_cfg ( &hbridge15 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> This example is driving a motor in both directions with 
  motor braking and freewheeling in between.

```c
void application_task ( void ) 
{
    log_printf( &logger, " Motor in forward mode. \r\n" );
    hbridge15_set_out_state( &hbridge15, HBRIDGE15_DRIVE_MOTOR_FORWARD );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Motor brake is on \r\n" );
    hbridge15_set_out_state( &hbridge15, HBRIDGE15_DRIVE_MOTOR_BRAKE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Motor in reverse mode. \r\n" );
    hbridge15_set_out_state( &hbridge15, HBRIDGE15_DRIVE_MOTOR_REVERSE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Motor is coasting \r\n" );
    hbridge15_set_out_state( &hbridge15, HBRIDGE15_DRIVE_MOTOR_FREEWHEEL );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.HBridge15

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
