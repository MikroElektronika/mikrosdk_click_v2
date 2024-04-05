
---
# Accel 16 click

> Accel 16 Click is a compact add-on board that contains an acceleration sensor. This board features the ADXL363, a micropower three-sensor combination including acceleration and temperature from Analog Devices. This device combines a 3-axis MEMS accelerometer, a temperature sensor, and an analog-to-digital converter (ADC) input for synchronized conversions of external signals.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/accel16_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/accel-16-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : Sep 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the Accel16 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Accel16 Click driver.

#### Standard key functions :

- `accel16_cfg_setup` Config Object Initialization function.
```c
void accel16_cfg_setup ( accel16_cfg_t *cfg );
```

- `accel16_init` Initialization function.
```c
err_t accel16_init ( accel16_t *ctx, accel16_cfg_t *cfg );
```

- `accel16_default_cfg` Click Default Configuration function.
```c
err_t accel16_default_cfg ( accel16_t *ctx );
```

#### Example key functions :

- `accel16_get_axes` Get axes data.
```c
err_t accel16_get_axes ( accel16_t *ctx, accel16_axes_t *axes );
```

- `accel16_filter_configuration` Filter configuration.
```c
err_t accel16_filter_configuration ( accel16_t *ctx, accel16_gain_t gain, accel16_output_rate_t odr );
```

- `accel16_get_temperature` Get temperature data.
```c
err_t accel16_get_temperature ( accel16_t *ctx, float *temperature );
```

## Example Description

> This showcases ability of the click board to 
read x, y, and z axes data in different resolution,
read IC temperature and also have additional functionality
to read ADC data. Device also has ability to store data 
in internal fifo buffer.

**The demo application is composed of two sections :**

### Application Init

> Initialization of communication modules(SPI, UART) and 
additional interrupt pins. Reads device ID's and revision.
Then configures device to work in FIFO mode or to read data
from the registers, sets 2g resolution, 12.5Hz output data rate,
sets interrupt 1 active low, powers on device, and calibrates temperature.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accel16_cfg_t accel16_cfg;  /**< Click config object. */

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
    accel16_cfg_setup( &accel16_cfg );
    ACCEL16_MAP_MIKROBUS( accel16_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == accel16_init( &accel16, &accel16_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    accel16.application_type = ACCEL16_APPLICATION_REG;
    
    uint8_t temp_buf[ 4 ] = { 0 };
    
    accel16_multiple_reg_read( &accel16, ACCEL16_REG_DEVID_AD, temp_buf, 4 );
    log_printf( &logger, " > ID0: 0x%.2X\r\n > ID1: 0x%.2X\r\n > ID2: 0x%.2X\r\n > REV: 0x%.2X\r\n", 
                ( uint16_t ) temp_buf[ 0 ], ( uint16_t ) temp_buf[ 1 ], 
                ( uint16_t ) temp_buf[ 2 ], ( uint16_t ) temp_buf[ 3 ] );
    
    
    if ( ACCEL16_ERROR == accel16_default_cfg ( &accel16 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Depending of the application mode selects example. 
 - If fifo example is selected waits for the interrupt 
     to indicate that data is ready  in fifo buffer and 
     reads number of fifo entries. Data that should be 
     read are X, Y, Z axes and temperature.
 - If register example is selected also waits for interrupt
     to indicate that data is ready to read. Then reads X, Y, Z
     axes, temperature, and ADC data.

```c

void application_task ( void )
{   
    if ( ACCEL16_APPLICATION_FIFO == accel16.application_type )
    {
        accel16_read_fifo_data( );
    }
    else if ( ACCEL16_APPLICATION_REG == accel16.application_type )
    {
        accel16_read_reg_data( );
    }

    log_printf( &logger, "********************************************************\r\n" );
    Delay_ms ( 300 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel16

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all MikroElektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
