\mainpage Main Page

---
# Water Detect 2 click

> Water Detect 2 Click is a compact add-on board that can detect the presence/flow of a liquid in a clear tube. This board features the OPB350L250, a tube liquid sensor from TT Electronics. Water Detect 2 Click has multiple output states and can recognize fluid present, no fluid present, and no tube present. This sensor excepts 1/4” tubing (6.3mm) as an outside diameter of the clear tubes, regardless of the direction of the liquid’s flow.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/waterdetect2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/water-detect-2-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jul 2023.
- **Type**          : GPIO type


# Software Support

We provide a library for the Water Detect 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Water Detect 2 Click driver.

#### Standard key functions :

- `waterdetect2_cfg_setup` Config Object Initialization function.
```c
void waterdetect2_cfg_setup ( waterdetect2_cfg_t *cfg );
```

- `waterdetect2_init` Initialization function.
```c
err_t waterdetect2_init ( waterdetect2_t *ctx, waterdetect2_cfg_t *cfg );
```

- `waterdetect2_default_cfg` Click Default Configuration function.
```c
void waterdetect2_default_cfg ( waterdetect2_t *ctx );
```

#### Example key functions :

- `waterdetect2_get_fluid_status` Water Detect 2 get fluid status function.
```c
uint8_t waterdetect2_get_fluid_status ( waterdetect2_t *ctx );
```

- `waterdetect2_enable` Water Detect 2 enable function.
```c
void waterdetect2_enable ( waterdetect2_t *ctx );
```

- `waterdetect2_disable` Water Detect 2 disable function.
```c
void waterdetect2_disable ( waterdetect2_t *ctx );
```

## Example Description

> This library contains API for Water Detect 2 Click driver.
> Water Detect 2 click is used for detecting water and other electroconductive liquids.

**The demo application is composed of two sections :**

### Application Init

> Initializes driver and performs the default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    waterdetect2_cfg_t waterdetect2_cfg;  /**< Click config object. */

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
    waterdetect2_cfg_setup( &waterdetect2_cfg );
    WATERDETECT2_MAP_MIKROBUS( waterdetect2_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == waterdetect2_init( &waterdetect2, &waterdetect2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    waterdetect2_default_cfg( &waterdetect2 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads fluid presence status and determines if there is fluid presence or not.

```c
void application_task ( void ) 
{
    uint8_t fluid_status = waterdetect2_get_fluid_status( &waterdetect2 );
    if ( fluid_status != fluid_status_old )
    {
        if ( WATERDETECT2_FLUID_DETECTED == fluid_status )
        {
            log_printf( &logger, " Fluid present! \r\n" );
        }
        else
        {
            log_printf( &logger, " No fluid present. \r\n" );
        }
        log_printf( &logger, "------------------- \r\n" );
        fluid_status_old = fluid_status;
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.WaterDetect2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
