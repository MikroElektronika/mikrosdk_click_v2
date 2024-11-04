
---
# Color 14 Click

> Color 14 Click is a compact add-on board that represents an accurate color sensing solution. This board features the APDS-9151, an integrated RGB, ambient light sensing, IR LED, and a complete proximity detection system from Broadcom Limited. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/color_14_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/color-14-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : Aug 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the Color14 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Color14 Click driver.

#### Standard key functions :

- `color14_cfg_setup` Config Object Initialization function.
```c
void color14_cfg_setup ( color14_cfg_t *cfg );
```

- `color14_init` Initialization function.
```c
err_t color14_init ( color14_t *ctx, color14_cfg_t *cfg );
```

#### Example key functions :

- `color14_get_rgb_ir` Read color data from device.
```c
err_t color14_get_rgb_ir ( color14_t *ctx, color14_color_t *color_data );
```

- `color14_get_als` Read lux data from device.
```c
err_t color14_get_als ( color14_t *ctx, float *als_data );
```

- `color14_get_proximity` Read proximity data from device.
```c
err_t color14_get_proximity ( color14_t *ctx, uint16_t *ps_data );
```

## Example Description

> This application showcases ability of Click board to read RGB and IR data
from device. Also it can be configured to read proximity data and
ALS data in lux units.

**The demo application is composed of two sections :**

### Application Init

> ## Application Init
Initialization of host communication modules (UART, I2C) and additonal pin.
Read and check device ID, selects example and configures device for it.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    color14_cfg_t color14_cfg;  /**< Click config object. */

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
    color14_cfg_setup( &color14_cfg );
    COLOR14_MAP_MIKROBUS( color14_cfg, MIKROBUS_1 );
    err_t init_flag = color14_init( &color14, &color14_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    uint8_t temp_data = 0;
    init_flag = color14_generic_read( &color14, COLOR14_REG_PART_ID, &temp_data, 1 );
    log_printf( &logger, " > ID: 0x%.2X\r\n", ( uint16_t )temp_data );
    
    if ( ( COLOR14_OK != init_flag ) && ( COLOR14_ID != temp_data ) )
    {
        log_error( &logger, " ID" );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    //Select example
    example_type = COLOR14_EXAMPLE_RGB;
    color14_generic_write( &color14, COLOR14_REG_MAIN_CTRL, &example_type, 1 );
    
    if ( COLOR14_EXAMPLE_PS_LS == example_type )
    {
        //Configure proximity data to 11 bit
        color14_generic_read( &color14, COLOR14_REG_PS_MEASRATE, &temp_data, 1 );
        temp_data |= 0x18;
        color14_generic_write( &color14, COLOR14_REG_PS_MEASRATE, &temp_data, 1 );
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
        case COLOR14_EXAMPLE_PS_LS:
        {
            color14_proximity_als_example( );
            break;
        }
        case COLOR14_EXAMPLE_RGB:
        {
            color14_rgb_example( );
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
- Click.Color14

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
