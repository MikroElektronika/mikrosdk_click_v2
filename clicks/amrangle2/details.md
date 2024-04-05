
---
# AMR Angle 2 click

> AMR Angle 2 Click is a compact add-on board containing an anisotropic magnetoresistive measurement solution ideal for either angle or linear position measurements. This board features the ADA4570, an integrated AMR angle sensor with an integrated signal conditioner and differential outputs from Analog Devices. The ADA4570 delivers amplified differential cosine and sine output signals, with respect to the angle measuring from 0° to 180° when the magnetic field is rotating in the x-axis and the y-axis (x-y) plane, processed later by MAX11122, SAR ADC, which forwards the digital angle information to MCU via SPI interface for further processing.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/amrangle2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/amr-angle-2-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2022.
- **Type**          : SPI type


# Software Support

We provide a library for the AMR Angle 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for AMR Angle 2 Click driver.

#### Standard key functions :

- `amrangle2_cfg_setup` Config Object Initialization function.
```c
void amrangle2_cfg_setup ( amrangle2_cfg_t *cfg );
```

- `amrangle2_init` Initialization function.
```c
err_t amrangle2_init ( amrangle2_t *ctx, amrangle2_cfg_t *cfg );
```

- `amrangle2_default_cfg` Click Default Configuration function.
```c
err_t amrangle2_default_cfg ( amrangle2_t *ctx );
```

#### Example key functions :

- `amrangle2_read_angle` This function reads a Vsin and Vcos voltages and converts them to angle in Degrees.
```c
err_t amrangle2_read_angle ( amrangle2_t *ctx, float *angle );
```

- `amrangle2_read_temperature` This function reads a temperature measurements in Celsius.
```c
err_t amrangle2_read_temperature ( amrangle2_t *ctx, float *temperature );
```

- `amrangle2_read_vsin_vcos` This function reads a voltage of sine and cosine differential signal outputs.
```c
err_t amrangle2_read_vsin_vcos ( amrangle2_t *ctx, float *vsin, float *vcos );
```

## Example Description

> This example demonstrates the use of AMR Angle 2 click board by reading and displaying the magnet's angular position in Degrees and a system temperature in Celsius.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    amrangle2_cfg_t amrangle2_cfg;  /**< Click config object. */

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
    amrangle2_cfg_setup( &amrangle2_cfg );
    AMRANGLE2_MAP_MIKROBUS( amrangle2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == amrangle2_init( &amrangle2, &amrangle2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AMRANGLE2_ERROR == amrangle2_default_cfg ( &amrangle2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the magnet's angular position in degrees and a system temperature in Celsius and displays the results on the USB UART approximately every 100ms.

```c
void application_task ( void )
{
    float angle, temperature;
    if ( AMRANGLE2_OK == amrangle2_read_angle ( &amrangle2, &angle ) ) 
    {
        log_printf( &logger, " Angle: %.2f Degrees\r\n", angle );
    }
    if ( AMRANGLE2_OK == amrangle2_read_temperature ( &amrangle2, &temperature ) ) 
    {
        log_printf( &logger, " Temperature: %.2f C\r\n\n", temperature );
    }
    Delay_ms ( 100 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.AMRAngle2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
