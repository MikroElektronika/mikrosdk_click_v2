\mainpage Main Page

---
# Ambient 20 click

> Ambient 20 Click is a compact add-on board used to measure the amount of the present ambient light. This board features the BU27030NUC, a 16-bit digital-output ambient light sensor with an I2C interface from Rohm Semiconductor. The BU27030NUC has a flexible and wide operating range of up to 20klx with a maximum resolution of 0.0007lux/count, providing an excellent responsivity close to the human eyes' response. It also features inherent 50Hz/60Hz light noise rejection and excellent IR-cut characteristics for high robustness at high sensitivity.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ambient20_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ambient-20-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Nov 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the Ambient 20 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Ambient 20 Click driver.

#### Standard key functions :

- `ambient20_cfg_setup` Config Object Initialization function.
```c
void ambient20_cfg_setup ( ambient20_cfg_t *cfg );
```

- `ambient20_init` Initialization function.
```c
err_t ambient20_init ( ambient20_t *ctx, ambient20_cfg_t *cfg );
```

- `ambient20_default_cfg` Click Default Configuration function.
```c
err_t ambient20_default_cfg ( ambient20_t *ctx );
```

#### Example key functions :

- `ambient20_sw_reset` Software reset function.
```c
err_t ambient20_sw_reset ( ambient20_t *ctx );
```

- `ambient20_set_gain` Set data gain function.
```c
err_t ambient20_set_gain ( ambient20_t *ctx, uint8_t data0_gain, uint8_t data1_gain );
```

- `ambient20_read_data0` Read data0 function.
```c
err_t ambient20_read_data0 ( ambient20_t *ctx, uint16_t *data0_out );
```

## Example Description

> This example demonstrates the use of Ambient 20 click board by measuring the ambient light level.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ambient20_cfg_t ambient20_cfg;  /**< Click config object. */

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
    ambient20_cfg_setup( &ambient20_cfg );
    AMBIENT20_MAP_MIKROBUS( ambient20_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ambient20_init( &ambient20, &ambient20_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AMBIENT20_ERROR == ambient20_default_cfg ( &ambient20 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    uint8_t id;
    ambient20_get_manufacturer_id( &ambient20, &id );
    
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
    log_printf( &logger, " Part ID = 0x%.2X \r\n", ( uint16_t ) id );
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );

    log_info( &logger, " Application Task " );
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
}

```

### Application Task

> Measuring ambient light level by reading DATA0 and DATA1 channels of the Ambient 20 click board and displaying it using UART Serial terminal.

```c
void application_task ( void ) 
{
    //  Task implementation.
    float data0, data1;
    ambient20_get_data_lux( &ambient20, &data0, &data1 );
    
    log_printf( &logger, "Data 0: %.2f lx \r\n", data0 );
    log_printf( &logger, "Data 1: %.2f lx \r\n", data1 );
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
    
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient20

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
