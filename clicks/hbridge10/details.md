
---
# H-Bridge 10 click

> H-Bridge 10 Click is a compact add-on board containing H-bridge outputs that let you control a DC motor to go backward or forward. This board features the MP6523, a triple, half-bridge, DMOS, output driver with integrated power MOSFETs that can drive up to three different loads from Monolithic Power Systems (MPS). The MP6523 is rated for an operating voltage range from 7V to 28V. It is SPI-configurable and has various diagnostic functions. Complete protection features include short-circuit protection (SCP), under-voltage protection (UVP), and thermal shutdown, alongside an onboard power supply existence-check circuit. This Click board™ is suitable as a multiple brushed DC motor driver for driving various loads in automotive and industrial applications, and more.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hbridge10_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/h-bridge-10-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2022.
- **Type**          : SPI type


# Software Support

We provide a library for the H-Bridge 10 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for H-Bridge 10 Click driver.

#### Standard key functions :

- `hbridge10_cfg_setup` Config Object Initialization function.
```c
void hbridge10_cfg_setup ( hbridge10_cfg_t *cfg );
```

- `hbridge10_init` Initialization function.
```c
err_t hbridge10_init ( hbridge10_t *ctx, hbridge10_cfg_t *cfg );
```

- `hbridge10_default_cfg` Click Default Configuration function.
```c
err_t hbridge10_default_cfg ( hbridge10_t *ctx );
```

#### Example key functions :

- `hbridge10_set_output_state` This function sets the output channel state.
```c
err_t hbridge10_set_output_state ( hbridge10_t *ctx, uint8_t channel, uint8_t state );
```

- `hbridge10_get_status` This function reads the status of output register.
```c
err_t hbridge10_get_status ( hbridge10_t *ctx, uint16_t *status );
```

- `hbridge10_get_fault_pin` This function returns the fault (FLT) pin logic state.
```c
uint8_t hbridge10_get_fault_pin ( hbridge10_t *ctx );
```

## Example Description

> This example demonstrates the use of the H-Bridge 10 click board by driving the motors connected between OUT1-OUT2 and OUT2-OUT3 in both directions. 

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hbridge10_cfg_t hbridge10_cfg;  /**< Click config object. */

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
    hbridge10_cfg_setup( &hbridge10_cfg );
    HBRIDGE10_MAP_MIKROBUS( hbridge10_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == hbridge10_init( &hbridge10, &hbridge10_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HBRIDGE10_ERROR == hbridge10_default_cfg ( &hbridge10 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Drives the motors connected between OUT1-OUT2 and OUT2-OUT3 in both directions in the span of 6 seconds, and displays the status messages on the USB UART.

```c
void application_task ( void )
{
    uint16_t status;
    if ( ( HBRIDGE10_OK == hbridge10_set_output_state ( &hbridge10, HBRIDGE10_CHANNEL_OUT1, HBRIDGE10_OUT_HIGH ) ) && 
         ( HBRIDGE10_OK == hbridge10_set_output_state ( &hbridge10, HBRIDGE10_CHANNEL_OUT2, HBRIDGE10_OUT_LOW ) ) && 
         ( HBRIDGE10_OK == hbridge10_set_output_state ( &hbridge10, HBRIDGE10_CHANNEL_OUT3, HBRIDGE10_OUT_HIGH ) ) )
    {
        Delay_ms ( 100 );
        if ( HBRIDGE10_OK == hbridge10_get_status ( &hbridge10, &status ) )
        {
            hbridge10_display_status ( status );
            Delay_ms ( 3000 );
        }
    }
    if ( ( HBRIDGE10_OK == hbridge10_set_output_state ( &hbridge10, HBRIDGE10_CHANNEL_OUT1, HBRIDGE10_OUT_LOW ) ) && 
         ( HBRIDGE10_OK == hbridge10_set_output_state ( &hbridge10, HBRIDGE10_CHANNEL_OUT2, HBRIDGE10_OUT_HIGH ) ) && 
         ( HBRIDGE10_OK == hbridge10_set_output_state ( &hbridge10, HBRIDGE10_CHANNEL_OUT3, HBRIDGE10_OUT_LOW ) ) )
    {
        Delay_ms ( 100 );
        if ( HBRIDGE10_OK == hbridge10_get_status ( &hbridge10, &status ) )
        {
            hbridge10_display_status ( status );
            Delay_ms ( 3000 );
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.HBridge10

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
