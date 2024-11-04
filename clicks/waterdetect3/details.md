
---
# Water Detect 3 Click

> Water Detect 3 Click is a compact add-on board that detects water and other electroconductive liquids. This board features the MCP606, a micropower CMOS operational amplifier from Microchip. In the same package, the Water Detect 3 Click comes with a separate PCB with an electroconductive water detection area connected to a Click board™ with wires.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/waterdetect3_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/water-detect-3-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2023.
- **Type**          : GPIO type


# Software Support

We provide a library for the Water Detect 3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Water Detect 3 Click driver.

#### Standard key functions :

- `waterdetect3_cfg_setup` Config Object Initialization function.
```c
void waterdetect3_cfg_setup ( waterdetect3_cfg_t *cfg );
```

- `waterdetect3_init` Initialization function.
```c
err_t waterdetect3_init ( waterdetect3_t *ctx, waterdetect3_cfg_t *cfg );
```

#### Example key functions :

- `waterdetect3_get_int` Water Detect 3 interrupt pin reading function.
```c
uint8_t waterdetect3_get_int ( waterdetect3_t *ctx );
```

## Example Description

> This example demonstrates the use of the Water Detect 3 Click board by
  detecting if water is present on the sensor part of the Click.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and configures hardware for the detection.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    waterdetect3_cfg_t waterdetect3_cfg;  /**< Click config object. */

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
    waterdetect3_cfg_setup( &waterdetect3_cfg );
    WATERDETECT3_MAP_MIKROBUS( waterdetect3_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == waterdetect3_init( &waterdetect3, &waterdetect3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, " Turn potentiometer VR1 all the way to the right.\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " Place a few drops of water onto the sensor.\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " Turn potentiometer VR1 to the left until the detect LED turns off.\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    while ( WATERDETECT3_PIN_STATE_HIGH == waterdetect3_get_int( &waterdetect3 ) );
    
    log_printf( &logger, " Device is ready.\r\n" );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Detects if any water is present on the sensor part.

```c
void application_task ( void ) 
{
    if ( WATERDETECT3_PIN_STATE_HIGH == waterdetect3_get_int( &waterdetect3 ) )
    {
        log_printf( &logger, " Water detected.\r\n" );
        Delay_ms ( 1000 );
    }
}
```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.WaterDetect3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
