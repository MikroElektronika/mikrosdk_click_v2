\mainpage Main Page

---
# Clock Gen 6 click

> Clock Gen 6 Click is a compact add-on board representing a digital oscillator solution. This board features the MIC1557, an IttyBitty CMOS RC oscillator designed to provide rail-to-rail pulses for precise time delay or frequency generation from Microchip Technology. The MIC1557 has a single threshold and trigger connection, internally connected, for astable (oscillator) operation only. It also has an enable/reset control signal routed to the RST pin of the mikroBUS™ socket, which controls the bias supply to the oscillator’s internal circuitry and optimizes power consumption used for oscillator power ON/OFF purposes. In addition, it provides the ability to select the desired frequency programmed via a digital potentiometer, the MAX5401.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/clockgen6_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/clock-gen-6-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the Clock Gen 6 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Clock Gen 6 Click driver.

#### Standard key functions :

- `clockgen6_cfg_setup` Config Object Initialization function.
```c
void clockgen6_cfg_setup ( clockgen6_cfg_t *cfg );
```

- `clockgen6_init` Initialization function.
```c
err_t clockgen6_init ( clockgen6_t *ctx, clockgen6_cfg_t *cfg );
```

- `clockgen6_default_cfg` This function executes a default configuration of Clock Gen 6 click board.
```c
err_t clockgen6_default_cfg ( clockgen6_t *ctx );
```

#### Example key functions :

- `clockgen6_set_digipot` This function sets the digital potentiometer position by using SPI serial interface.
```c
err_t clockgen6_set_digipot ( clockgen6_t *ctx, uint8_t position );
```

- `clockgen6_enable_output` This function enables the output by setting the EN pin to high logic state.
```c
void clockgen6_enable_output ( clockgen6_t *ctx );
```

- `clockgen6_disable_output` This function disables the output by setting the EN pin to low logic state.
```c
void clockgen6_disable_output ( clockgen6_t *ctx );
```

## Example Description

> This example demonstrates the use of Clock Gen 6 click board which acts as an astable oscillator.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration which sets the digital potentiometer to max position and enables the clock output.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    clockgen6_cfg_t clockgen6_cfg;  /**< Click config object. */

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
    clockgen6_cfg_setup( &clockgen6_cfg );
    CLOCKGEN6_MAP_MIKROBUS( clockgen6_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == clockgen6_init( &clockgen6, &clockgen6_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CLOCKGEN6_ERROR == clockgen6_default_cfg ( &clockgen6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Changes the clock output frequency by changing the digital potentiometer position every second. The potentiometer position value will be displayed on the USB UART.

```c
void application_task ( void )
{
    for ( int16_t pos = CLOCKGEN6_DIGIPOT_POSITION_MAX; pos >= CLOCKGEN6_DIGIPOT_POSITION_MIN; )
    {
        if ( CLOCKGEN6_OK == clockgen6_set_digipot ( &clockgen6, pos ) )
        {
            log_printf( &logger, " DIGIPOT position: %u\r\n", pos );
            Delay_ms ( 1000 );
            pos -= 5;
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ClockGen6

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
