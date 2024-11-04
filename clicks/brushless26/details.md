
---
# Brushless 26 Click

> Brushless 26 Click is a compact add-on board that controls brushless DC motors with any MCU. This board features the DRV8317H, a three-phase PWM motor driver from Texas Instruments. It provides three integrated MOSFET half-bridges for driving three-phase brushless DC (BLDC) motors with 5V, 9V, 12V, or 18V DC rails or 2s to 4s batteries.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/brushless26_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/brushless-26-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : May 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Brushless 26 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Brushless 26 Click driver.

#### Standard key functions :

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

#### Example key functions :

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

## Example Description

> This example demonstrates the use of the Brushless 26 Click board by driving the 
  motor in both directions at different speeds.

**The demo application is composed of two sections :**

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

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless26

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
