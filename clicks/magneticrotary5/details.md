
---
# Magnetic Rotary 5 click

> Magnetic Rotary 5 Click is a compact add-on board for accurate magnet-position sensing. This board features the AS5134, a contactless magnetic rotary encoder from ams AG for accurate angular measurement over a full turn of 360º. It is designed to provide accurate angle measurements with a simple two-pole magnet rotating over the center of the chip, featuring an integrated Hall element, analog front end, and digital signal processing. Offering a high resolution of 8.5 bits, which equates to 360 positions per revolution, it is also capable of high-speed performance, with a maximum RPM of 76875. It can accommodate a wide range of magnetic fields, from 20 to 80mT. It also has an onboard header for incremental and commutation signals of their respective A/B/I and U/V/W signals and pins for Daisy Chain Mode and OTP programming.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/magneticrotary5_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/magnetic-rotary-5-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2022.
- **Type**          : ADC/GPIO type


# Software Support

We provide a library for the Magnetic Rotary 5 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Magnetic Rotary 5 Click driver.

#### Standard key functions :

- `magneticrotary5_cfg_setup` Config Object Initialization function.
```c
void magneticrotary5_cfg_setup ( magneticrotary5_cfg_t *cfg );
```

- `magneticrotary5_init` Initialization function.
```c
err_t magneticrotary5_init ( magneticrotary5_t *ctx, magneticrotary5_cfg_t *cfg );
```

- `magneticrotary5_default_cfg` Click Default Configuration function.
```c
err_t magneticrotary5_default_cfg ( magneticrotary5_t *ctx );
```

#### Example key functions :

- `magneticrotary5_read_angle` This function reads the magnetic angle and automatic gain control (AGC) values measured by the sensor.
```c
err_t magneticrotary5_read_angle ( magneticrotary5_t *ctx, uint8_t *agc, uint16_t *angle );
```

- `magneticrotary5_read_mt_cnt` This function reads the multi turn counter value. With each zero transition in any direction, the output of a special counter is incremented or decremented.
```c
err_t magneticrotary5_read_mt_cnt ( magneticrotary5_t *ctx, int16_t *mt_cnt );
```

- `magneticrotary5_read_voltage` This function reads raw ADC value and converts it to proportional voltage level.
```c
err_t magneticrotary5_read_voltage ( magneticrotary5_t *ctx, float *voltage );
```

## Example Description

> This example demonstrates the use of Magnetic Rotary 5 click board by reading and displaying
the magnet angular position as well as the AGC and multi turn counter values.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and resets the multi turn counter to zero.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    magneticrotary5_cfg_t magneticrotary5_cfg;  /**< Click config object. */

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
    magneticrotary5_cfg_setup( &magneticrotary5_cfg );
    MAGNETICROTARY5_MAP_MIKROBUS( magneticrotary5_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == magneticrotary5_init( &magneticrotary5, &magneticrotary5_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MAGNETICROTARY5_ERROR == magneticrotary5_default_cfg ( &magneticrotary5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the magnet angular position in degrees as well as the voltage from AN pin which is
proportional to the angular position. Also reads the AGC and multi turn counter values.
The results will be displayed on the USB UART every 100ms approximately.

```c
void application_task ( void )
{
    uint8_t agc = 0;
    uint16_t angle = 0;
    int16_t mt_cnt = 0;
    float voltage = 0;
    if ( MAGNETICROTARY5_OK == magneticrotary5_read_angle ( &magneticrotary5, &agc, &angle ) )
    {
        log_printf ( &logger, "\r\n AGC: %u\r\n Angle: %u\r\n", ( uint16_t ) agc, angle );
    }
    if ( MAGNETICROTARY5_OK == magneticrotary5_read_mt_cnt ( &magneticrotary5, &mt_cnt ) )
    {
        log_printf ( &logger, " Multi turn counter: %d\r\n", mt_cnt );
    }
    if ( MAGNETICROTARY5_OK == magneticrotary5_read_voltage ( &magneticrotary5, &voltage ) ) 
    {
        log_printf( &logger, " AN Voltage : %.3f V\r\n", voltage );
    }
    Delay_ms ( 100 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.MagneticRotary5

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
