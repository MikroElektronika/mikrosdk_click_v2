\mainpage Main Page

---
# Opto Encoder 4 click

> Opto Encoder 4 Click is a compact add-on board that contains an optical sensor/encoder that can be used for movement or rotation encoding. This board features the EE-SX4330, a transmissive photo-microsensor from OMRON. It is intended to be used with an encoder disk or similar device that will act as a barrier between the emitter and detector of the sensor. Usually, it will be the disk with perforations, which is commonly used to detect the rotation speed.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/optoencoder4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/opto-encoder-4-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2023.
- **Type**          : GPIO type


# Software Support

We provide a library for the Opto Encoder 4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Opto Encoder 4 Click driver.

#### Standard key functions :

- `optoencoder4_cfg_setup` Config Object Initialization function.
```c
void optoencoder4_cfg_setup ( optoencoder4_cfg_t *cfg );
```

- `optoencoder4_init` Initialization function.
```c
err_t optoencoder4_init ( optoencoder4_t *ctx, optoencoder4_cfg_t *cfg );
```

#### Example key functions :

- `optoencoder4_get_out_pin` This function returns the output pin logic state.
```c
uint8_t optoencoder4_get_out_pin ( optoencoder4_t *ctx );
```

- `optoencoder4_get_our_pin` This function returns the output pin reversed logic state.
```c
uint8_t optoencoder4_get_our_pin ( optoencoder4_t *ctx );
```

## Example Description

> This example demonstrates the use of Opto Encoder 4 click board by processing
the encoder output pin state and incrementing the step counter on falling edge.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    optoencoder4_cfg_t optoencoder4_cfg;  /**< Click config object. */

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
    optoencoder4_cfg_setup( &optoencoder4_cfg );
    OPTOENCODER4_MAP_MIKROBUS( optoencoder4_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == optoencoder4_init( &optoencoder4, &optoencoder4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Increments the step counter on falling edge of the encoder output pin state and displays it on the USB UART.

```c
void application_task ( void )
{
    static uint32_t step_cnt = 0;

    log_printf( &logger, " Step counter : %lu\r\n", step_cnt );
    
    // Increment counter on falling edge of output pin
    while ( !optoencoder4_get_out_pin ( &optoencoder4 ) );
    while ( optoencoder4_get_out_pin ( &optoencoder4 ) );

    step_cnt++;
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.OptoEncoder4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
