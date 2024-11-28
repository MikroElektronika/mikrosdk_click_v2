
---
# Light 4 Click

> Light 4 Click is a compact add-on board designed for precise ambient light, UV index, and light flicker detection. This board features the TSL2585 sensor from ams OSRAM, which incorporates photopic, infrared (IR), and ultraviolet (UV) photodiodes to enable multiple concurrent sensing functions. The TSL2585 continuously monitors ambient light, calculates irradiance, and detects light flicker using optimized filters and dedicated IR and UV channels. It communicates with the host MCU via a standard I2C interface, includes interrupt-driven events for threshold-based alerts, and operates with 3.3V logic voltage.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/light4_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/light-4-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Feb 2024.
- **Type**          : I2C type


# Software Support

We provide a library for the Light 4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Light 4 Click driver.

#### Standard key functions :

- `light4_cfg_setup` Config Object Initialization function.
```c
void light4_cfg_setup ( light4_cfg_t *cfg );
```

- `light4_init` Initialization function.
```c
err_t light4_init ( light4_t *ctx, light4_cfg_t *cfg );
```

- `light4_default_cfg` Click Default Configuration function.
```c
err_t light4_default_cfg ( light4_t *ctx );
```

#### Example key functions :

- `light4_write_reg` This function writes a byte into the selected register by using I2C serial interface.
```c
err_t light4_write_reg ( light4_t *ctx, uint8_t reg, uint8_t data_in );
```

- `light4_sw_reset` This function is used to perform software reset of Light 4 Click board.
```c
err_t light4_sw_reset ( light4_t *ctx );
```

- `light4_read_channel_data` This function is used to read data from selected channel of Light 4 Click board.
```c
err_t light4_read_channel_data ( light4_t *ctx, uint8_t channel_sel, float *channel_data );
```

## Example Description

> This example demonstrates the use of Light 4 Click board by measuring 
  the ambient light level in Lux.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, performs the Click default configuration 
  and checking I2C Communication by reading Device ID.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    light4_cfg_t light4_cfg;  /**< Click config object. */

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
    light4_cfg_setup( &light4_cfg );
    LIGHT4_MAP_MIKROBUS( light4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == light4_init( &light4, &light4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LIGHT4_ERROR == light4_default_cfg ( &light4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    uint8_t dev_id = 0;
    light4_read_reg ( &light4, LIGHT4_REG_ID, &dev_id ); 
    if ( LIGHT4_DEVICE_ID == dev_id )
    {
        log_printf( &logger, " Device ID: 0x%.2X \r\n", ( uint16_t ) dev_id );
    }
    else
    {
        log_error( &logger, " Read error." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reading channel 0 ambient light level in lux once per 
  second and displaying it on the UART terminal.

```c
void application_task ( void ) 
{
    float channel_data = 0;
    err_t error_flag;

    error_flag = light4_read_channel_data( &light4, LIGHT4_CHANNEL0_SEL, &channel_data );
    if( LIGHT4_OK == error_flag )
    {
        log_printf( &logger, " Data: %.2f Lux \r\n", channel_data );
    }
    else if ( LIGHT4_ANALOG_SAT == error_flag )
    {
        log_error( &logger, " Analog saturation \r\n" );
    }
    
    Delay_ms ( 1000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Light4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
