
---
# Inclinometer 4 Click

> Inclinometer 4 Click is a compact add-on board designed to measure angles of slope or elevation of an object concerning gravity's direction. This board features the FXLS8971CF, a 3-axis low-g MEMS accelerometer from NXP Semiconductor. The FXLS8971CF offers high-performance and low-power modes, with selectable full-scale ranges of ±2/4/8/16g and features such as selectable output data rates, motion detection, and a 144-byte output data buffer.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/inclinometer4_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/inclinometer-4-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2024.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Inclinometer 4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Inclinometer 4 Click driver.

#### Standard key functions :

- `inclinometer4_cfg_setup` Config Object Initialization function.
```c
void inclinometer4_cfg_setup ( inclinometer4_cfg_t *cfg );
```

- `inclinometer4_init` Initialization function.
```c
err_t inclinometer4_init ( inclinometer4_t *ctx, inclinometer4_cfg_t *cfg );
```

- `inclinometer4_default_cfg` Click Default Configuration function.
```c
err_t inclinometer4_default_cfg ( inclinometer4_t *ctx );
```

#### Example key functions :

- `inclinometer4_get_int2_pin` This function returns the interrupt 2 (INT2) pin logic state.
```c
uint8_t inclinometer4_get_int2_pin ( inclinometer4_t *ctx );
```

- `inclinometer4_get_data` This function reads accel X, Y, and Z axis data in g and temperature in degrees Celsius.
```c
err_t inclinometer4_get_data ( inclinometer4_t *ctx, inclinometer4_data_t *data_out );
```

- `inclinometer4_set_mode` This function sets the device operating mode to standby or active.
```c
err_t inclinometer4_set_mode ( inclinometer4_t *ctx, uint8_t mode );
```

## Example Description

> This example demonstrates the use of Inclinometer 4 Click board by reading and displaying accel data (X, Y, and Z axis) as well as temperature measurements on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration which enables data ready interrupt on INT2 pin and sets full scale range to +/-2G and output data rate to 160ms.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    inclinometer4_cfg_t inclinometer4_cfg;  /**< Click config object. */

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
    inclinometer4_cfg_setup( &inclinometer4_cfg );
    INCLINOMETER4_MAP_MIKROBUS( inclinometer4_cfg, MIKROBUS_1 );
    err_t init_flag = inclinometer4_init( &inclinometer4, &inclinometer4_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( INCLINOMETER4_ERROR == inclinometer4_default_cfg ( &inclinometer4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Waits for a data ready interrupt, then reads and displays the accel data (X, Y, and Z axis) as well as temperature measurements on the USB UART.

```c
void application_task ( void )
{
    inclinometer4_data_t accel_data;
    
    // Wait for a data ready interrupt
    while ( inclinometer4_get_int2_pin ( &inclinometer4 ) );

    if ( INCLINOMETER4_OK == inclinometer4_get_data ( &inclinometer4, &accel_data ) )
    {
        log_printf( &logger, " X: %.3f g\r\n", accel_data.x );
        log_printf( &logger, " Y: %.3f g\r\n", accel_data.y );
        log_printf( &logger, " Z: %.3f g\r\n", accel_data.z );
        log_printf( &logger, " Temperature: %d degC\r\n\n", ( int16_t ) accel_data.temperature );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Inclinometer4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
