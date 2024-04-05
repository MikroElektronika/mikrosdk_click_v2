\mainpage Main Page

---
# H-Bridge 12 click

> H Bridge 12 Click is a compact add-on board with an H-Bridge gate driver, also known as a full-bridge pre-driver. This board features the DRV8823, a 4-bridge serial interface motor driver from Texas Instruments.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hbridge12_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/h-bridge-12-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Apr 2023.
- **Type**          : SPI type


# Software Support

We provide a library for the H-Bridge 12 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for H-Bridge 12 Click driver.

#### Standard key functions :

- `hbridge12_cfg_setup` Config Object Initialization function.
```c
void hbridge12_cfg_setup ( hbridge12_cfg_t *cfg );
```

- `hbridge12_init` Initialization function.
```c
err_t hbridge12_init ( hbridge12_t *ctx, hbridge12_cfg_t *cfg );
```

- `hbridge12_default_cfg` Click Default Configuration function.
```c
err_t hbridge12_default_cfg ( hbridge12_t *ctx );
```

#### Example key functions :

- `hbridge12_write_config` H-Bridge 12 write settings function.
```c
err_t hbridge12_write_config ( hbridge12_t *ctx, hbridge12_config_t config_data );
```

- `hbridge12_set_current_scale` H-Bridge 12 set current scale function.
```c
void hbridge12_set_current_scale ( hbridge12_t *ctx, uint8_t channel_sel, uint8_t out1_curr_scale, uint8_t out2_curr_scale );
```

- `hbridge12_turn_clockwise` H-Bridge 12 turn motor clockwise function.
```c
err_t hbridge12_turn_clockwise ( hbridge12_t *ctx, uint8_t channel_sel );
```

## Example Description

> This example demonstrates the use of the H-Bridge 12 click board by
  driving the motor connected to OUT A and OUT B, in both directions with braking and freewheeling. 

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hbridge12_cfg_t hbridge12_cfg;  /**< Click config object. */

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
    hbridge12_cfg_setup( &hbridge12_cfg );
    HBRIDGE12_MAP_MIKROBUS( hbridge12_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == hbridge12_init( &hbridge12, &hbridge12_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HBRIDGE12_ERROR == hbridge12_default_cfg ( &hbridge12 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Driving motor in both directions for 5 seconds with a motor braking and freewheeling in between.

```c
void application_task ( void )
{
    log_printf( &logger, " Turning motor counterclockwise \r\n" );
    hbridge12_turn_counterclockwise( &hbridge12, HBRIDGE12_AB_BRIDGE_SEL );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Turning motor brake on \r\n" );
    hbridge12_turn_brake_on( &hbridge12, HBRIDGE12_AB_BRIDGE_SEL );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Turning motor clockwise \r\n" );
    hbridge12_turn_clockwise( &hbridge12, HBRIDGE12_AB_BRIDGE_SEL );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Motor freewheeling \r\n" );
    hbridge12_freewheeling_on( &hbridge12, HBRIDGE12_AB_BRIDGE_SEL );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.HBridge12

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
