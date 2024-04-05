
---
# Color 13 click

> Color 13 Click is a compact add-on board that measures the subtlest changes in light. This board features the APDS-9999, I2C compatible RGB, proximity detector, and vertical-cavity surface-emitting laser (VCSEL) in one optical module from Broadcom Limited.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/color_13_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/color-13-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : Jun 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the Color13 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Color13 Click driver.

#### Standard key functions :

- `color13_cfg_setup` Config Object Initialization function.
```c
void color13_cfg_setup ( color13_cfg_t *cfg );
```

- `color13_init` Initialization function.
```c
err_t color13_init ( color13_t *ctx, color13_cfg_t *cfg );
```

#### Example key functions :

- `color13_get_rgb_ir` Read color data from device.
```c
err_t color13_get_rgb_ir ( color13_t *ctx, color13_color_t *color_data );
```

- `color13_get_als` Read lux data from device.
```c
err_t color13_get_als ( color13_t *ctx, float *als_data );
```

- `color13_get_proximity` Read proximity data from device.
```c
err_t color13_get_proximity ( color13_t *ctx, uint16_t *ps_data );
```

## Example Description

> This application showcases ability of click board to read RGB and IR data
from device. Also it can be configured to read proximity data and
ALS data in lux units.

**The demo application is composed of two sections :**

### Application Init

> Initialization of host communication modules (UART, I2C) and additonal pin.
Read and check device ID, selects example and configures device for it.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    color13_cfg_t color13_cfg;  /**< Click config object. */

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
    color13_cfg_setup( &color13_cfg );
    COLOR13_MAP_MIKROBUS( color13_cfg, MIKROBUS_1 );
    err_t init_flag = color13_init( &color13, &color13_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    uint8_t temp_data = 0;
    init_flag = color13_generic_read( &color13, COLOR13_REG_PART_ID, &temp_data, 1 );
    log_printf( &logger, " > ID: 0x%.2X\r\n", ( uint16_t )temp_data );
    
    if ( ( COLOR13_OK != init_flag ) && ( COLOR13_ID != temp_data ) )
    {
        log_error( &logger, " ID" );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    //Select example
    example_type = COLOR13_EXAMPLE_RGB;
    color13_generic_write( &color13, COLOR13_REG_MAIN_CTRL, &example_type, 1 );
    
    if ( COLOR13_EXAMPLE_PS_LS == example_type )
    {
        //Configure proximity data to 11 bit
        color13_generic_read( &color13, COLOR13_REG_PS_MEASRATE, &temp_data, 1 );
        temp_data |= 0x18;
        color13_generic_write( &color13, COLOR13_REG_PS_MEASRATE, &temp_data, 1 );
    }
    
    Delay_ms ( 1000 );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Depending of selected example in task proximity and als data will be read from
device, or it will show ADC value for red, green, blue and ir data from device.

```c

void application_task ( void ) 
{
    switch ( example_type )
    {
        case COLOR13_EXAMPLE_PS_LS:
        {
            color13_proximity_als_example( );
            break;
        }
        case COLOR13_EXAMPLE_RGB:
        {
            color13_rgb_example( );
            break;
        }
        default:
        {
            log_error( &logger, " Select example!" );
            break;
        }
    }
    Delay_ms ( 500 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Color13

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
