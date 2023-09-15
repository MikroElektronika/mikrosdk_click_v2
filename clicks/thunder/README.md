\mainpage Main Page

---
# Thunder click

> Thunder click features AS3935 lightning sensor as well as MA5532 coil antenna. It detects the presence and proximity of potentially hazardous lightning activity in the vicinity and provides estimated distance to the center of the storm. It can also provide information on the noise level. Thunder click communicates with the target board microcontroller via SPI and INT lines. The board is designed to use 3.3V or 5V power supply. LED diode (GREEN) indicates the presence of power supply.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/thunder_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/thunder-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Thunder Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Thunder Click driver.

#### Standard key functions :

- `thunder_cfg_setup` Config Object Initialization function.
```c
void thunder_cfg_setup ( thunder_cfg_t *cfg ); 
```

- `thunder_init` Initialization function.
```c
err_t thunder_init ( thunder_t *ctx, thunder_cfg_t *cfg );
```

- `thunder_default_cfg` Click Default Configuration function.
```c
void thunder_default_cfg ( thunder_t *ctx );
```

#### Example key functions :

- `thunder_check_int` Function checks and returns the interrupt value.
```c
uint8_t thunder_check_int ( thunder_t *ctx );
```

- `thunder_get_storm_info` Function gets energy of the single lightning and distance estimation for the head of the storm.
```c
void thunder_get_storm_info ( thunder_t *ctx, uint32_t *energy_out, uint8_t *distance_out );
```

- `thunder_read_reg` Function reads a data byte from the registers.
```c
err_t thunder_read_reg ( thunder_t *ctx, uint8_t reg, uint8_t *data_out );
```

## Examples Description

> This application detects the presence and proximity of potentially 
lightning activity and provides estimated distance to the center of the storm. 
It can also provide information on the noise level.

**The demo application is composed of two sections :**

### Application Init 

> Initializes SPI driver and performs the reset command and RCO calibrate command. Also configures the device for working properly.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    thunder_cfg_t cfg;

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
    thunder_cfg_setup( &cfg );
    THUNDER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thunder_init( &thunder, &cfg );

    thunder_default_cfg( &thunder );
    log_info( &logger, " Application Task " );
}
  
```

### Application Task

> Checks if the interrupt event has occured (Listening mode) and after that reads the storm information and logs the results on the USB UART.

```c

void application_task ( void )
{
    storm_mode = thunder_check_int ( &thunder );

    if ( THUNDER_NOISE_LEVEL_INTERR == storm_mode )
    {
        log_printf( &logger, "Noise level too high\r\n\n" );
    }
    else if ( THUNDER_DISTURBER_INTERR == storm_mode )
    {
        log_printf( &logger, "Disturber detected\r\n\n" );
    }
    else if ( THUNDER_LIGHTNING_INTERR == storm_mode )
    {
        thunder_get_storm_info( &thunder, &storm_energy, &storm_distance );
        log_printf( &logger, "Energy of the single lightning : %lu\r\n", storm_energy );
        log_printf( &logger, "Distance estimation : %u km\r\n\n", ( uint16_t ) storm_distance );
        // Reset configuration to prepare for the next measurement
        thunder_default_cfg( &thunder );
    }
} 

``` 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Thunder

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
