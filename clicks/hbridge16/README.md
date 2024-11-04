\mainpage Main Page

---
# H-Bridge 16 Click

> H-Bridge 16 Click is a compact add-on board with an H-Bridge gate driver, also known as a full-bridge pre-driver. This board features the DRV8262, a dual H-Bridge motor driver from Texas Instruments. The motor driver is designed for a variety of industrial applications and can drive one or two brushed DC motors, one stepper motor, and one or two thermoelectric coolers (TEC). It can operate in a wide supply voltage range of 4.5V to 65V.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hbridge16_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/h-bridge-16-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Sep 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the H-Bridge 16 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for H-Bridge 16 Click driver.

#### Standard key functions :

- `hbridge16_cfg_setup` Config Object Initialization function.
```c
void hbridge16_cfg_setup ( hbridge16_cfg_t *cfg );
```

- `hbridge16_init` Initialization function.
```c
err_t hbridge16_init ( hbridge16_t *ctx, hbridge16_cfg_t *cfg );
```

- `hbridge16_default_cfg` Click Default Configuration function.
```c
err_t hbridge16_default_cfg ( hbridge16_t *ctx );
```

#### Example key functions :

- `hbridge16_set_pins` H-Bridge 16 set pins function.
```c
err_t hbridge16_set_pins ( hbridge16_t *ctx, uint8_t set_mask, uint8_t clr_mask );
```

- `hbridge16_set_mode` H-Bridge 16 set mode function.
```c
err_t hbridge16_set_mode ( hbridge16_t *ctx, uint8_t mode_sel );
```

- `hbridge16_set_out_state` H-Bridge 16 set output function.
```c
err_t hbridge16_set_out_state ( hbridge16_t *ctx, uint8_t out_state );
```

## Example Description

> This example demonstrates the use of the H-Bridge 16 Click board by
  driving the motor in both directions with braking and freewheeling.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hbridge16_cfg_t hbridge16_cfg;  /**< Click config object. */

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
    hbridge16_cfg_setup( &hbridge16_cfg );
    HBRIDGE16_MAP_MIKROBUS( hbridge16_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == hbridge16_init( &hbridge16, &hbridge16_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HBRIDGE16_ERROR == hbridge16_default_cfg ( &hbridge16 ) )
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
    hbridge16_set_out_state( &hbridge16, HBRIDGE16_DRIVE_MOTOR_FORWARD );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Motor brake is on \r\n" );
    hbridge16_set_out_state( &hbridge16, HBRIDGE16_DRIVE_MOTOR_BRAKE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Motor in reverse mode. \r\n" );
    hbridge16_set_out_state( &hbridge16, HBRIDGE16_DRIVE_MOTOR_REVERSE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Motor is coasting \r\n" );
    hbridge16_set_out_state( &hbridge16, HBRIDGE16_DRIVE_MOTOR_FREEWHEEL );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.HBridge16

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
