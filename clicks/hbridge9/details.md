
---
# H-Bridge 9 click

> H-Bridge 9 Click is a compact add-on board that contains six MOSFET half-bridge outputs. This board features the L99UDL01, a six-channel half-bridge driver monolithic integrated circuit that is PWM configurable and current regulated from STMicroelectronics.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hbridge9_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/h-bridge-9-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the HBridge9 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for HBridge9 Click driver.

#### Standard key functions :

- `hbridge9_cfg_setup` Config Object Initialization function.
```c
void hbridge9_cfg_setup ( hbridge9_cfg_t *cfg );
```

- `hbridge9_init` Initialization function.
```c
err_t hbridge9_init ( hbridge9_t *ctx, hbridge9_cfg_t *cfg );
```

- `hbridge9_default_cfg` Click Default Configuration function.
```c
err_t hbridge9_default_cfg ( hbridge9_t *ctx );
```

#### Example key functions :

- `hbridge9_write_register` This function writes a desired data to the selected register.
```c
err_t hbridge9_write_register ( hbridge9_t *ctx, uint8_t reg, uint16_t data_in );
```

- `hbridge9_read_register` This function reads a desired data from the selected register.
```c
err_t hbridge9_read_register ( hbridge9_t *ctx, uint8_t reg, uint16_t *data_out );
```

- `hbridge9_send_actuation_pulse` This function sends an actuation pulse by toggling the ENO pin.
```c
void hbridge9_send_actuation_pulse ( hbridge9_t *ctx );
```

## Example Description

> This example demonstrates the use of H-Bridge 9 click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration which will set the OUT1 to LOW, OUT2 to HIGH polarity, and the runtime to 1000ms.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;            /**< Logger config object. */
    hbridge9_cfg_t hbridge9_cfg;  /**< Click config object. */

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

    hbridge9_cfg_setup( &hbridge9_cfg );
    HBRIDGE9_MAP_MIKROBUS( hbridge9_cfg, MIKROBUS_1 );
    err_t init_flag = hbridge9_init( &hbridge9, &hbridge9_cfg );
    if ( SPI_MASTER_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    init_flag = hbridge9_default_cfg ( &hbridge9 );
    if ( HBRIDGE9_ERROR == init_flag )
    {
        log_error( &logger, " Default Config Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Sends an actuation pulse every 5 seconds which will run the motor for a certain amount of time as set by default configuration.

```c

void application_task ( void )
{
    hbridge9_send_actuation_pulse( &hbridge9 );
    log_printf( &logger, " Actuation pulse has been sent. \r\n\n" );
    Delay_ms( 5000 );
}

```

## Note

> The Voltage should be supplied with 6 to 18V power supply. Make sure to use a motor that operates in the above voltage range.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.HBridge9

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all MikroElektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
