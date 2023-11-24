\mainpage Main Page

---
# Brushless 13 click

> Brushless 13 Click is a compact add-on board that controls brushless DC motors with any MCU. This board features the STSPIN830, a compact and versatile three-phase and three-sense motor driver from STMicroelectronics. The driver integrates both the control logic and a fully protected low RDson triple half-bridge power stage.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/brushless13_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/brushless-13-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Brushless 13 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Brushless 13 Click driver.

#### Standard key functions :

- `brushless13_cfg_setup` Config Object Initialization function.
```c
void brushless13_cfg_setup ( brushless13_cfg_t *cfg );
```

- `brushless13_init` Initialization function.
```c
err_t brushless13_init ( brushless13_t *ctx, brushless13_cfg_t *cfg );
```

- `brushless13_default_cfg` Click Default Configuration function.
```c
err_t brushless13_default_cfg ( brushless13_t *ctx );
```

#### Example key functions :

- `brushless13_set_mode` Brushless 13 set mode pin function.
```c
void brushless13_set_mode ( brushless13_t *ctx, uint8_t mode_sel );
```

- `brushless13_get_flt_pin` Brushless 13 get fault pin function.
```c
uint8_t brushless13_get_flt_pin ( brushless13_t *ctx );
```

- `brushless13_drive_motor` Brushless 13 drive motor function.
```c
err_t brushless13_drive_motor ( brushless13_t *ctx, uint8_t dir, uint8_t speed, uint32_t time_ms );
```

## Example Description

> This example demonstrates the use of the Brushless 13 click board by driving the 
  motor in both directions at different speeds.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless13_cfg_t brushless13_cfg;  /**< Click config object. */

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
    brushless13_cfg_setup( &brushless13_cfg );
    BRUSHLESS13_MAP_MIKROBUS( brushless13_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == brushless13_init( &brushless13, &brushless13_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS13_ERROR == brushless13_default_cfg ( &brushless13 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Drives the motor in both directions and changes the motor speed approximately every 2 seconds.
  The driving direction and speed will be displayed on the USB UART.

```c
void application_task ( void ) 
{
    log_printf ( &logger, "\r\n Driving motor clockwise \r\n" );
    for ( uint8_t speed = BRUSHLESS13_SPEED_MIN; speed <= BRUSHLESS13_SPEED_MAX; speed += 20 )
    {
        log_printf ( &logger, " Speed gain: %u\r\n", ( uint16_t ) speed );
        if ( BRUSHLESS13_OK != brushless13_drive_motor ( &brushless13, BRUSHLESS13_DIR_CW, speed, 2000 ) )
        {
            log_error ( &logger, " Drive motor " );
        }
    }
    Delay_ms ( 1000 );
    
    log_printf ( &logger, "\r\n Driving motor counter-clockwise \r\n" );
    for ( uint8_t speed = BRUSHLESS13_SPEED_MIN; speed <= BRUSHLESS13_SPEED_MAX; speed += 20 )
    {
        log_printf ( &logger, " Speed gain: %u\r\n", ( uint16_t ) speed );
        if ( BRUSHLESS13_OK != brushless13_drive_motor ( &brushless13, BRUSHLESS13_DIR_CCW, speed, 2000 ) )
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
- Click.Brushless13

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
