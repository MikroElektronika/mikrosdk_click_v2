\mainpage Main Page

---
# Accel 22 click

> Accel 22 Click is a compact add-on board that contains an acceleration sensor. This board features the ADXL367, an ultra-low-power, high-performance three-axis accelerometer from Analog Devices. The ADXL367 allows selectable full-scale acceleration measurements in ranges of ±2g, ±4g, and ±8g in three axes, with a resolution of 0.25 mg/LSB on the ±2g range, alongside a configurable host interface that supports both SPI and I2C serial communication. This device combines a 3-axis MEMS accelerometer, a temperature sensor, and a 14-bit analog-to-digital converter (ADC) to synchronize an external analog signal conversion.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/accel22_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/accel-22-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2022.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Accel 22 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Accel 22 Click driver.

#### Standard key functions :

- `accel22_cfg_setup` Config Object Initialization function.
```c
void accel22_cfg_setup ( accel22_cfg_t *cfg );
```

- `accel22_init` Initialization function.
```c
err_t accel22_init ( accel22_t *ctx, accel22_cfg_t *cfg );
```

- `accel22_default_cfg` Click Default Configuration function.
```c
err_t accel22_default_cfg ( accel22_t *ctx );
```

#### Example key functions :

- `accel22_get_axes` This function reads accel X, Y, and Z axis data in mg.
```c
err_t accel22_get_axes ( accel22_t *ctx, accel22_axes_t *axes );
```

- `accel22_get_temperature` This function reads the temperature in Celsius.
```c
err_t accel22_get_temperature ( accel22_t *ctx, float *temperature );
```

- `accel22_get_adc` This function reads the ADC voltage.
```c
err_t accel22_get_adc ( accel22_t *ctx, float *v_adc );
```

## Example Description

> This example demonstrates the use of Accel 22 click board by reading and displaying Accel data (X, Y, and Z axis) as well as temperature and ADC measurements on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accel22_cfg_t accel22_cfg;  /**< Click config object. */

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
    accel22_cfg_setup( &accel22_cfg );
    ACCEL22_MAP_MIKROBUS( accel22_cfg, MIKROBUS_1 );
    err_t init_flag  = accel22_init( &accel22, &accel22_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ACCEL22_ERROR == accel22_default_cfg ( &accel22 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads and displays the Accel data (X, Y, and Z axis) as well as temperature and ADC measurements on the USB UART every 100ms approximately.

```c
void application_task ( void )
{
    accel22_axes_t axes;
    // Wait for data ready indication
    while ( !accel22_get_int1_pin ( &accel22 ) );
    if ( ACCEL22_OK == accel22_get_axes ( &accel22, &axes ) )
    {
        log_printf( &logger, " X: %.2f mg\r\n", axes.x );
        log_printf( &logger, " Y: %.2f mg\r\n", axes.y );
        log_printf( &logger, " Z: %.2f mg\r\n", axes.z );
    }
    
    if ( ACCEL22_OK == accel22_enable_temperature_measurement ( &accel22 ) )
    {
        float temperature = 0;
        // Wait for data ready indication
        while ( !accel22_get_int1_pin ( &accel22 ) );
        if ( ACCEL22_OK == accel22_get_temperature ( &accel22, &temperature ) )
        {
            log_printf( &logger, " Temperature: %.2f C\r\n", temperature );
        }
    }
    
    if ( ACCEL22_OK == accel22_enable_adc_measurement ( &accel22 ) )
    {
        float adc_voltage = 0;
        // Wait for data ready indication
        while ( !accel22_get_int1_pin ( &accel22 ) );
        if ( ACCEL22_OK == accel22_get_adc ( &accel22, &adc_voltage ) )
        {
            log_printf( &logger, " ADC: %.2f V\r\n\n", adc_voltage );
        }
    }
    Delay_ms ( 100 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel22

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
