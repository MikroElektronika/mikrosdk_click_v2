\mainpage Main Page

---
# DIGI POT 11 click

> DIGI POT 11 Click is a compact add-on board representing a digitally controlled potentiometer. This board features a double pack of the MAX5387, a dual, 256-tap, volatile, low-voltage linear taper digital potentiometer from Analog Devices. This way, four digitally I2C-controlled potentiometers are realized with end-to-end resistance values of 50kΩ. Operating from a single +3.3V power supply, this device provides a low 35ppm/ºC end-to-end temperature coefficient.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/digipot11_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/digi-pot-11-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the DIGI POT 11 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DIGI POT 11 Click driver.

#### Standard key functions :

- `digipot11_cfg_setup` Config Object Initialization function.
```c
void digipot11_cfg_setup ( digipot11_cfg_t *cfg );
```

- `digipot11_init` Initialization function.
```c
err_t digipot11_init ( digipot11_t *ctx, digipot11_cfg_t *cfg );
```

#### Example key functions :

- `digipot11_set_u1_wiper` This function sets the position of the selected wiper of U1 device by using I2C serial interface.
```c
err_t digipot11_set_u1_wiper ( digipot11_t *ctx, uint8_t wiper_sel, uint8_t data_in );
```

- `digipot11_set_u2_wiper` This function sets the position of the selected wiper of U2 device by using I2C serial interface.
```c
err_t digipot11_set_u2_wiper ( digipot11_t *ctx, uint8_t wiper_sel, uint8_t data_in );
```

## Example Description

> This example demonstrates the use of DIGI POT 11 click board by changing the wipers position of both U1 and U2 devices.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    digipot11_cfg_t digipot11_cfg;  /**< Click config object. */

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
    digipot11_cfg_setup( &digipot11_cfg );
    DIGIPOT11_MAP_MIKROBUS( digipot11_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == digipot11_init( &digipot11, &digipot11_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Iterates through the entire wiper range and sets the wipers position of both U1 and U2 devices once per second. The current wiper position will be displayed on the USB UART.

```c
void application_task ( void )
{
    for ( uint16_t wiper_pos = DIGIPOT11_WIPER_ZERO_SCALE; wiper_pos <= DIGIPOT11_WIPER_FULL_SCALE; wiper_pos += 5 )
    {
        if ( DIGIPOT11_OK == digipot11_set_u1_wiper ( &digipot11, DIGIPOT11_WIPER_SEL_BOTH, ( uint8_t ) wiper_pos ) )
        {
            log_printf( &logger, " U1 wipers position: %u\r\n", wiper_pos );
        }
        if ( DIGIPOT11_OK == digipot11_set_u2_wiper ( &digipot11, DIGIPOT11_WIPER_SEL_BOTH, 
                                                      ( uint8_t ) ( DIGIPOT11_WIPER_FULL_SCALE - wiper_pos ) ) )
        {
            log_printf( &logger, " U2 wipers position: %u\r\n\n", ( DIGIPOT11_WIPER_FULL_SCALE - wiper_pos ) );
        }
        Delay_ms ( 1000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DIGIPOT11

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
