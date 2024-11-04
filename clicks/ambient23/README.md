\mainpage Main Page

---
# Ambient 23 Click

> Ambient 23 Click is a compact add-on board that measures the intensity of visible light. This board features the VEML3235SL, an advanced ambient light sensor designed by the CMOS process from Vishay Semiconductors that transforms light intensity to a 16-bit digital signal output that can be directly communicated via an I2C interface. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ambient23_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ambient-23-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Apr 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Ambient 23 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Ambient 23 Click driver.

#### Standard key functions :

- `ambient23_cfg_setup` Config Object Initialization function.
```c
void ambient23_cfg_setup ( ambient23_cfg_t *cfg );
```

- `ambient23_init` Initialization function.
```c
err_t ambient23_init ( ambient23_t *ctx, ambient23_cfg_t *cfg );
```

- `ambient23_default_cfg` Click Default Configuration function.
```c
err_t ambient23_default_cfg ( ambient23_t *ctx );
```

#### Example key functions :

- `ambient23_reg_read` Ambient 23 register reading function.
```c
err_t ambient23_reg_read ( ambient23_t *ctx, uint8_t reg, uint16_t *data_out );
```

- `ambient23_calculate_res` Ambient 23 get conversion data function.
```c
err_t ambient23_calculate_res ( ambient23_t *ctx, float *conversion_mul );
```

- `ambient23_read_light_data` Ambient 23 get light data function.
```c
err_t ambient23_read_light_data ( ambient23_t *ctx, float *light_data );
```

## Example Description

> This example demonstrates the use of Ambient 23 Click board by measuring 
  the ambient light level in Lux.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, checks communication by reading part ID
  and performs the Click default configuration.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ambient23_cfg_t ambient23_cfg;  /**< Click config object. */

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
    ambient23_cfg_setup( &ambient23_cfg );
    AMBIENT23_MAP_MIKROBUS( ambient23_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ambient23_init( &ambient23, &ambient23_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    uint16_t part_id = 0;
    ambient23_reg_read( &ambient23, AMBIENT23_REG_DEVICE_ID, &part_id );
    if ( AMBIENT23_PART_ID != ( uint8_t ) part_id )
    {
        log_error( &logger, " Communication error." );
        for ( ; ; );
    }
    
    if ( AMBIENT23_ERROR == ambient23_default_cfg ( &ambient23 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Measuring ambient light level by reading data from the Ambient 23 Click board
  and displaying it using UART Serial terminal.

```c
void application_task ( void ) 
{
    float data_tmp;
    
    ambient23_read_light_data( &ambient23, &data_tmp );
    log_printf( &logger, "Data: %.2f lux\r\n", data_tmp );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient23

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
