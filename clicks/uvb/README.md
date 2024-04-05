\mainpage Main Page

---
# UVB click

> UVB Click is ultraviolet sensing board based on GUVB-C31SM sensor from GenUV, capable of measuring UV index between 0 to 16. UVB Click supports integrated functions of ultraviolet light sensors such that can be easily configured and used in user applications. Overexposure to UVB radiation not only can cause sunburn but also some forms of skin cancer, so knowing amount of UVB light can be quite important and this Click board™ is perfect solution for that task.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/UVB_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/uvb-click)

---


#### Click library

- **Author**        : Mikroe Team
- **Date**          : Sep 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the UVB Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for UVB Click driver.

#### Standard key functions :

- `uvb_cfg_setup` Config Object Initialization function.
```c
void uvb_cfg_setup ( uvb_cfg_t *cfg );
```

- `uvb_init` Initialization function.
```c
err_t uvb_init ( uvb_t *ctx, uvb_cfg_t *cfg );
```

- `uvb_default_cfg` Click Default Configuration function.
```c
err_t uvb_default_cfg ( uvb_t *ctx );
```

#### Example key functions :

- `uvb_configuration` Configuration register.
```c
void uvb_configuration ( uvb_t *ctx, uint8_t reg, uint8_t cfg );
```

- `uvb_read_byte` Read one byte data from register.
```c
uint8_t uvb_read_byte ( uvb_t *ctx, uint8_t reg );
```

- `uvb_get_uv_data` Get UVB data.
```c
uint16_t uvb_get_uv_data ( uvb_t *ctx );
```

## Example Description

> This Click is ultraviolet sensing board, capable of measuring UV index between 0 to 16. UVB Click supports integrated functions of ultraviolet light sensors.

**The demo application is composed of two sections :**

### Application Init

> Initialization driver init, check communication and configuration module for measurement.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    uvb_cfg_t uvb_cfg;  /**< Click config object. */

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
    uvb_cfg_setup( &uvb_cfg );
    UVB_MAP_MIKROBUS( uvb_cfg, MIKROBUS_1 );
    err_t init_flag = uvb_init( &uvb, &uvb_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    uvb_default_cfg ( &uvb );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "--------------------------\r\n" );
}

```

### Application Task

> Reads UVB data and logs to the USBUART every 1500ms.

```c

void application_task ( void ) 
{
    uvb_data = uvb_get_uv_data( &uvb );

    log_printf( &logger, ">> UVB data: %d\r\n", uvb_data );

    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 500 );
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.UVB

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
