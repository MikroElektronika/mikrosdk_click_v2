\mainpage Main Page

---
# DIGI Isolator 2 Click

> DIGI Isolator 2 Click is a compact add-on board that provides isolated digital input signals to your application. This board features the ISO1228, an eight-channel isolated digital input from Texas Instruments. It comes with 8-channel isolated 24V digital input receivers, with a current limit and diagnostics. The device also provides a field-side input-current-powered LED indication to reduce system power dissipation and reduce the board temperatures.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/digiisolator2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/digi-isolator-2-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2023.
- **Type**          : SPI type


# Software Support

We provide a library for the DIGI Isolator 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DIGI Isolator 2 Click driver.

#### Standard key functions :

- `digiisolator2_cfg_setup` Config Object Initialization function.
```c
void digiisolator2_cfg_setup ( digiisolator2_cfg_t *cfg );
```

- `digiisolator2_init` Initialization function.
```c
err_t digiisolator2_init ( digiisolator2_t *ctx, digiisolator2_cfg_t *cfg );
```

- `digiisolator2_default_cfg` Click Default Configuration function.
```c
err_t digiisolator2_default_cfg ( digiisolator2_t *ctx );
```

#### Example key functions :

- `digiisolator2_enable_output` This function enables output by setting the EN pin to high state.
```c
void digiisolator2_enable_output ( digiisolator2_t *ctx );
```

- `digiisolator2_disable_output` This function disables output by setting the EN pin to low state.
```c
void digiisolator2_disable_output ( digiisolator2_t *ctx );
```

- `digiisolator2_read_inputs` This function reads all inputs state via the selected driver interface.
```c
err_t digiisolator2_read_inputs ( digiisolator2_t *ctx, uint8_t *data_out );
```

## Example Description

> This example demonstrates the use of DIGI Isolator 2 Click board by reading and displaying the state of 8 digital input channels.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and enables isolator outputs.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    digiisolator2_cfg_t digiisolator2_cfg;  /**< Click config object. */

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
    digiisolator2_cfg_setup( &digiisolator2_cfg );
    DIGIISOLATOR2_MAP_MIKROBUS( digiisolator2_cfg, MIKROBUS_1 );
    if ( DIGIISOLATOR2_OK != digiisolator2_init( &digiisolator2, &digiisolator2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    digiisolator2_enable_output( &digiisolator2 );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the state of 8 digital input channels in hex format where MSB represents IN8 and LSB the channel IN1. The results are displayed on the USB UART every 500ms.

```c
void application_task ( void )
{
    uint8_t input_data = 0;
    if ( DIGIISOLATOR2_OK == digiisolator2_read_inputs ( &digiisolator2, &input_data ) )
    {
        log_printf( &logger, " INPUT: 0x%.2X\r\n\n", ( uint16_t ) input_data );
        Delay_ms ( 500 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DIGIIsolator2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
