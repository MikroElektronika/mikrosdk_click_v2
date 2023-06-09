\mainpage Main Page

---
# DIGI POT 12 click

> DIGI POT 12 Click is a compact add-on board that contains a digitally controlled potentiometer. 
> This board features the AD5142A, a dual-channel, 256-position nonvolatile digital potentiometer from Analog Devices.
> On this Click board™, two digitally I2C-controlled potentiometers are realized with end-to-end resistance 
> of 10KΩ and wiper resistance of only 40Ω. The DIGI POT 12 Click can be used in potentiometer and linear gain modes.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/digipot12_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/digi-pot-12-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Apr 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the DIGI POT 12 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DIGI POT 12 Click driver.

#### Standard key functions :

- `digipot12_cfg_setup` Config Object Initialization function.
```c
void digipot12_cfg_setup ( digipot12_cfg_t *cfg );
```

- `digipot12_init` Initialization function.
```c
err_t digipot12_init ( digipot12_t *ctx, digipot12_cfg_t *cfg );
```

- `digipot12_default_cfg` Click Default Configuration function.
```c
err_t digipot12_default_cfg ( digipot12_t *ctx );
```

#### Example key functions :

- `digipot12_set_resistance` DIGI POT 12 set the resistance function.
```c
err_t digipot12_set_resistance ( digipot12_t *ctx, uint8_t wiper_sel, float res_kohm );
```

- `digipot12_get_resistance` DIGI POT 12 get the resistance function.
```c
err_t digipot12_get_resistance ( digipot12_t *ctx, uint8_t wiper_sel, float *res_kohm );
```

## Example Description

> This library contains API for DIGI POT 12 Click driver.
> The demo application uses a digital potentiometer 
> to change the resistance values of both channels.

**The demo application is composed of two sections :**

### Application Init

> The initialization of I2C module, log UART, and additional pins.
> After the driver init, the app executes a default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    digipot12_cfg_t digipot12_cfg;  /**< Click config object. */

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
    digipot12_cfg_setup( &digipot12_cfg );
    DIGIPOT12_MAP_MIKROBUS( digipot12_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == digipot12_init( &digipot12, &digipot12_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DIGIPOT12_ERROR == digipot12_default_cfg ( &digipot12 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ----------------------------\r\n" );
    Delay_ms( 100 );
}
```

### Application Task

> This example demonstrates the use of the DIGI POT 12 Click board™.
> The demo application iterates through the entire wiper range and 
> sets the resistance of both channels in steps of approximately 1kOhm.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    static float res_kohm;
    for ( uint8_t n_cnt = DIGIPOT12_RES_0_KOHM; n_cnt <= DIGIPOT12_RES_10_KOHM; n_cnt++ )
    {
        if ( DIGIPOT12_OK == digipot12_set_resistance( &digipot12, DIGIPOT12_WIPER_SEL_1, ( float ) n_cnt ) )
        {
            if ( DIGIPOT12_OK == digipot12_get_resistance( &digipot12, DIGIPOT12_WIPER_SEL_1, &res_kohm ) )
            {
                log_printf( &logger, " Rwb1 : %.2f kOhm\r\n", res_kohm );
                Delay_ms( 100 );
            }
        }
        
        if ( DIGIPOT12_OK == digipot12_set_resistance( &digipot12, DIGIPOT12_WIPER_SEL_2, ( float ) ( DIGIPOT12_RES_10_KOHM - n_cnt ) ) )
        {
            if ( DIGIPOT12_OK == digipot12_get_resistance( &digipot12, DIGIPOT12_WIPER_SEL_2, &res_kohm ) )
            {
                log_printf( &logger, " Rwb2 : %.2f kOhm\r\n", res_kohm );
                Delay_ms( 100 );
            }
        }
        log_printf( &logger, " ----------------------------\r\n" );
        Delay_ms( 5000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DIGIPOT12

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
