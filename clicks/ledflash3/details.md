
---
# LED Flash 3 click

> LED Flash 3 Click is a compact add-on board representing a powerful flash/torch solution. This board features the KTD2691, an inductor-less, single-flash LED driver from Kinetic Technologies. It includes one current source that can drive up to 1.5A of LED flash current or up to 376mA of torch current.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ledflash3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/led-flash-3-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Sep 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the LED Flash 3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LED Flash 3 Click driver.

#### Standard key functions :

- `ledflash3_cfg_setup` Config Object Initialization function.
```c
void ledflash3_cfg_setup ( ledflash3_cfg_t *cfg );
```

- `ledflash3_init` Initialization function.
```c
err_t ledflash3_init ( ledflash3_t *ctx, ledflash3_cfg_t *cfg );
```

- `ledflash3_default_cfg` Click Default Configuration function.
```c
err_t ledflash3_default_cfg ( ledflash3_t *ctx );
```

#### Example key functions :

- `ledflash3_write_reg` LED Flash 3 register writing function.
```c
err_t ledflash3_write_reg ( ledflash3_t *ctx, uint8_t reg, uint8_t data_in );
```

- `ledflash3_set_flash_current` LED Flash 3 set flash current function.
```c
err_t ledflash3_set_flash_current ( ledflash3_t *ctx, float flash_current );
```

- `ledflash3_set_torch_current` LED Flash 3 set torch current function.
```c
err_t ledflash3_set_torch_current ( ledflash3_t *ctx, float torch_current );
```

## Example Description

> This app demonstrate flash mode on LED Flash 3 Click.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ledflash3_cfg_t ledflash3_cfg;  /**< Click config object. */

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
    ledflash3_cfg_setup( &ledflash3_cfg );
    LEDFLASH3_MAP_MIKROBUS( ledflash3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ledflash3_init( &ledflash3, &ledflash3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LEDFLASH3_ERROR == ledflash3_default_cfg ( &ledflash3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task ");
}

```

### Application Task

> Turning the LED on for a second and off for another second.

```c
void application_task ( void ) 
{
    ledflash3_strobe_pin( &ledflash3 );
    Delay_ms( 2000 );
}
```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LEDFlash3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
