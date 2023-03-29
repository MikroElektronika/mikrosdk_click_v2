
---
# Brushless 20 click

> Brushless 20 Click is a compact add-on board that controls brushless DC (BLDC) motors with any MCU. This board features the DRV8313, a fully integrated three-phase BLDC motor driver from Texas Instruments. It provides three individually controllable half-H-bridge drivers intended to drive a three-phase BLDC motor, solenoids, or other loads. Each output driver channel consists of N-channel power MOSFETs configured in a 1/2-H-bridge configuration. Besides, it has a wide operating voltage range from 8V to 60V, alongside several built-in protection circuits such as undervoltage, charge pump faults, overcurrent, and overtemperature.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/brushless20_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/brushless-20-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the Brushless 20 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Brushless 20 Click driver.

#### Standard key functions :

- `brushless20_cfg_setup` Config Object Initialization function.
```c
void brushless20_cfg_setup ( brushless20_cfg_t *cfg );
```

- `brushless20_init` Initialization function.
```c
err_t brushless20_init ( brushless20_t *ctx, brushless20_cfg_t *cfg );
```

- `brushless20_default_cfg` Click Default Configuration function.
```c
err_t brushless20_default_cfg ( brushless20_t *ctx );
```

#### Example key functions :

- `brushless20_perform_com_sequence` This function performs a single commutation sequence for the selected rotation direction at a desired speed.
```c
err_t brushless20_perform_com_sequence ( brushless20_t *ctx, uint8_t dir, uint8_t speed );
```

- `brushless20_drive_motor` This function drives the motor for a desired time by performing multiple commutation sequences for the selected rotation direction at a desired speed.
```c
err_t brushless20_drive_motor ( brushless20_t *ctx, uint8_t dir, uint8_t speed, uint32_t time_ms );
```

- `brushless20_get_fault_pin` This function returns the fault pin logic state.
```c
err_t brushless20_get_fault_pin ( brushless20_t *ctx );
```

## Example Description

> This example demonstrates the use of the Brushless 20 click board by driving the motor in both directions at different speeds.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless20_cfg_t brushless20_cfg;  /**< Click config object. */

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
    brushless20_cfg_setup( &brushless20_cfg );
    BRUSHLESS20_MAP_MIKROBUS( brushless20_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == brushless20_init( &brushless20, &brushless20_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS20_ERROR == brushless20_default_cfg ( &brushless20 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Drives the motor in both directions and changes the motor speed every 3 seconds approximately. The current driving direction and speed will be displayed on the USB UART.

```c
void application_task ( void )
{
    log_printf ( &logger, "\r\n Driving motor clockwise \r\n" );
    for ( uint8_t speed = BRUSHLESS20_SPEED_MIN; speed <= BRUSHLESS20_SPEED_MAX; speed += 20 )
    {
        log_printf ( &logger, " Speed: %u\r\n", ( uint16_t ) speed );
        if ( BRUSHLESS20_OK != brushless20_drive_motor ( &brushless20, BRUSHLESS20_DIR_CW, speed, 3000 ) )
        {
            log_error ( &logger, " Drive motor " );
        }
    }
    Delay_ms ( 1000 );
    log_printf ( &logger, "\r\n Driving motor counter-clockwise \r\n" );
    for ( uint8_t speed = BRUSHLESS20_SPEED_MIN; speed <= BRUSHLESS20_SPEED_MAX; speed += 20 )
    {
        log_printf ( &logger, " Speed: %u\r\n", ( uint16_t ) speed );
        if ( BRUSHLESS20_OK != brushless20_drive_motor ( &brushless20, BRUSHLESS20_DIR_CCW, speed, 3000 ) )
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
- Click.Brushless20

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
