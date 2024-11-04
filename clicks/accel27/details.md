
---
# Accel 27 Click

> Accel 27 Click is a compact add-on board that contains an acceleration sensor. This board features the ADXL373, a three-axis MEMS ±400g accelerometer from Analog Devices. In addition to its ultra-low power consumption, the ADXL373 enables impact detection while providing system-level power reduction. It offers 12-bit output data at 200mg/LSB scale factor with a configurable host interface that supports SPI and I2C serial communication.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/accel27_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/accel-27-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2022.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Accel 27 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Accel 27 Click driver.

#### Standard key functions :

- `accel27_cfg_setup` Config Object Initialization function.
```c
void accel27_cfg_setup ( accel27_cfg_t *cfg );
```

- `accel27_init` Initialization function.
```c
err_t accel27_init ( accel27_t *ctx, accel27_cfg_t *cfg );
```

- `accel27_default_cfg` Click Default Configuration function.
```c
err_t accel27_default_cfg ( accel27_t *ctx );
```

#### Example key functions :

- `accel27_get_int1_pin` This function returns the interrupt 1 (INT1) pin logic state.
```c
uint8_t accel27_get_int1_pin ( accel27_t *ctx );
```

- `accel27_get_axes` This function reads accel X, Y, and Z axis data in g.
```c
err_t accel27_get_axes ( accel27_t *ctx, accel27_axes_t *axes );
```

- `accel27_reset_device` This function performs the chip software reset.
```c
err_t accel27_reset_device ( accel27_t *ctx );
```

## Example Description

> This example demonstrates the use of Accel 27 Click board by reading and displaying the accelerometer data (X, Y, and Z axis) averaged from 100 samples.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accel27_cfg_t accel27_cfg;  /**< Click config object. */

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
    accel27_cfg_setup( &accel27_cfg );
    ACCEL27_MAP_MIKROBUS( accel27_cfg, MIKROBUS_1 );
    err_t init_flag = accel27_init( &accel27, &accel27_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ACCEL27_ERROR == accel27_default_cfg ( &accel27 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads and displays on the USB UART the accelerometer data (X, Y, and Z axis) averaged from 100 samples.

```c
void application_task ( void )
{
    accel27_axes_t axes = { 0 };
    uint16_t cnt = 0;
    while ( cnt < NUM_OF_SAMPLES )
    {
        // Wait for data ready indication
        while ( !accel27_get_int1_pin ( &accel27 ) );

        accel27_axes_t tmp_axes;
        if ( ACCEL27_OK == accel27_get_axes ( &accel27, &tmp_axes ) )
        {
            axes.x += tmp_axes.x;
            axes.y += tmp_axes.y;
            axes.z += tmp_axes.z;
            cnt++;
        }
    }
    axes.x = axes.x / NUM_OF_SAMPLES;
    axes.y = axes.y / NUM_OF_SAMPLES;
    axes.z = axes.z / NUM_OF_SAMPLES;
    log_printf( &logger, " X: %.1f g\r\n", axes.x );
    log_printf( &logger, " Y: %.1f g\r\n", axes.y );
    log_printf( &logger, " Z: %.1f g\r\n\n", axes.z );
}
```

## Note

> This Click board should be used for high g applications of up to +-400g. It is not recommended
for low g applications because of its high scale factor which is about 200 mg per LSB.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel27

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
