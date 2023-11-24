\mainpage Main Page

---
# Brushless 27 click

> Brushless 27 Click is a compact add-on board that controls DC brushless motors with any MCU. This board features the TMC6300, a power driver for BLDC/PMSM motors from TRINAMIC. It is a highly efficient low voltage, zero standby driver for 3-phase BLDC/PMSM motors with up to 2A peak current.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/brushless27_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/brushless-27-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Sep 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Brushless 27 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Brushless 27 Click driver.

#### Standard key functions :

- `brushless27_cfg_setup` Config Object Initialization function.
```c
void brushless27_cfg_setup ( brushless27_cfg_t *cfg );
```

- `brushless27_init` Initialization function.
```c
err_t brushless27_init ( brushless27_t *ctx, brushless27_cfg_t *cfg );
```

- `brushless27_default_cfg` Click Default Configuration function.
```c
err_t brushless27_default_cfg ( brushless27_t *ctx );
```

#### Example key functions :

- `brushless27_set_pins` Brushless 27 set pins function.
```c
err_t brushless27_set_pins ( brushless27_t *ctx, uint8_t set_mask, uint8_t clr_mask );
```

- `brushless27_set_trap_com_state` Brushless 27 set trapezoidal com state function.
```c
err_t brushless27_set_trap_com_state ( brushless27_t *ctx, uint8_t state );
```

- `brushless27_drive_motor` Brushless 27 drive motor function.
```c
err_t brushless27_drive_motor ( brushless27_t *ctx, uint8_t dir, uint8_t speed, uint32_t time_ms );
```

## Example Description

> This example demonstrates the use of the Brushless 27 click board by driving the 
  motor in both directions at different speeds.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless27_cfg_t brushless27_cfg;  /**< Click config object. */

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
    brushless27_cfg_setup( &brushless27_cfg );
    BRUSHLESS27_MAP_MIKROBUS( brushless27_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == brushless27_init( &brushless27, &brushless27_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS27_ERROR == brushless27_default_cfg ( &brushless27 ) )
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
    for ( uint8_t speed = BRUSHLESS27_SPEED_MIN; speed <= BRUSHLESS27_SPEED_MAX; speed += 20 )
    {
        log_printf ( &logger, " Speed gain: %u\r\n", ( uint16_t ) speed );
        if ( BRUSHLESS27_OK != brushless27_drive_motor ( &brushless27, BRUSHLESS27_DIR_CW, speed, 2000 ) )
        {
            log_error ( &logger, " Drive motor " );
        }
    }
    Delay_ms ( 1000 );
    
    log_printf ( &logger, "\r\n Driving motor counter-clockwise \r\n" );
    for ( uint8_t speed = BRUSHLESS27_SPEED_MIN; speed <= BRUSHLESS27_SPEED_MAX; speed += 20 )
    {
        log_printf ( &logger, " Speed gain: %u\r\n", ( uint16_t ) speed );
        if ( BRUSHLESS27_OK != brushless27_drive_motor ( &brushless27, BRUSHLESS27_DIR_CCW, speed, 2000 ) )
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
- Click.Brushless27

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
