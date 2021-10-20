
---
# PROXIMITY 7 click

< Proximity 7 click is an advanced proximity and ambient light sensing Click board™. It features the ADPS9930, a digital sensor IC equipped with two photodiodes (PD) and an IR LED, driven by a proprietary LED driver circuit. It allows an accurate proximity detection for a maximum distance of 100mm. >

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/proximity7_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/proximity-7-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Proximity7 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Proximity7 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void proximity7_cfg_setup ( proximity7_cfg_t *cfg ); 
 
- Initialization function.
> PROXIMITY7_RETVAL proximity7_init ( proximity7_t *ctx, proximity7_cfg_t *cfg );

- Click Default Configuration function.
> void proximity7_default_cfg ( proximity7_t *ctx );


#### Example key functions :

- Get proximity data.
> uint16_t proximity7_get_proximity_data( proximity7_t *ctx )
 
- Get lux level.
> float proximity7_get_lux_level( proximity7_t *ctx )

- Set proximity offset
> uint8_t proximity7_set_proximity_offset( proximity7_t *ctx, uint8_t proximity_offset_magnitude )

## Examples Description

> This application give us lux level and proximiti data.

**The demo application is composed of two sections :**

### Application Init 

> Initializes I2C driver and writes basic settings to device registers

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    proximity7_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    proximity7_cfg_setup( &cfg );
    PROXIMITY7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    proximity7_init( &proximity7, &cfg );

    Delay_ms(100);

    log_printf( &logger, "> > > app init done < < <\r\n" );

}
  
```

### Application Task

> Logs lux level and proximity data

```c

void application_task ( void )
{
    uint8_t write_buffer[ 2 ];
    uint8_t read_buffer[ 1 ] ;
    float lux_level;
    uint16_t proximity;
    uint8_t als_valid;
    uint8_t proximity_valid;

    proximity7_generic_read( &proximity7, PROXIMITY7_STATUS | PROXIMITY7_REPEATED_BYTE, &read_buffer[ 0 ], 1 );
    
    als_valid = read_buffer[ 0 ] & PROXIMITY7_ALS_VALID_MASK;
    proximity_valid = read_buffer[ 0 ] & PROXIMITY7_PROXIMITY_VALID_MASK;
    
    if ( ( als_valid != 0 ) && ( proximity_valid != 0 ) )
    {
        log_printf( &logger, " " );

        lux_level = proximity7_get_lux_level( &proximity7 );
        log_printf( &logger, "> > > Lux level   : %f lx\r\n", lux_level );
    
        proximity = proximity7_get_proximity_data( &proximity7 );
        log_printf( &logger, "> > > Proximity   : %d\r\n", proximity );

        write_buffer[ 0 ] = PROXIMITY7_SPECIAL_FUNCTION | PROXIMITY7_PROXIMITY_AND_ALS_INT_PIN_CLEAR;
        proximity7_generic_write( &proximity7, PROXIMITY7_SPECIAL_FUNCTION | PROXIMITY7_PROXIMITY_AND_ALS_INT_PIN_CLEAR, &write_buffer[ 0 ], 1 );
    }
    
    Delay_ms(300);
}  

```

## Note

> - When setting LED drive strength please note that if "proximity drive level - PDL" bit in "configuration register" is set to 1, LED drive current values are reduced by 9.
  - When setting wait time note that if "wait long - WLONG" bit is set to 1, time is 12x longer. Therefore if WLONG == 1 set time between 33ms and 8386.56ms.
  - When setting ALS gain note that if "ALS gain level - AGL" bit is set to 1, ALS gains are scaled by 0.16, otherwise, they are scaled by 1.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity7

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

---
# PROXIMITY 7 click

< Proximity 7 click is an advanced proximity and ambient light sensing Click board™. It features the ADPS9930, a digital sensor IC equipped with two photodiodes (PD) and an IR LED, driven by a proprietary LED driver circuit. It allows an accurate proximity detection for a maximum distance of 100mm. >

![click image]( https://cdn1-shop.mikroe.com/img/product/proximity-7-click/proximity-7-click-thickbox_default-1.jpg )

[click Product page]( < https://www.mikroe.com/proximity-7-click > )

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Proximity7 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Proximity7 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void proximity7_cfg_setup ( proximity7_cfg_t *cfg ); 
 
- Initialization function.
> PROXIMITY7_RETVAL proximity7_init ( proximity7_t *ctx, proximity7_cfg_t *cfg );


#### Example key functions :

- Get proximity data.
> uint16_t proximity7_get_proximity_data( proximity7_t *ctx )
 
- Get lux level.
> float proximity7_get_lux_level( proximity7_t *ctx )

- Set proximity offset
> uint8_t proximity7_set_proximity_offset( proximity7_t *ctx, uint8_t proximity_offset_magnitude )

## Examples Description

> This application give us lux level and proximiti data.

**The demo application is composed of two sections :**

### Application Init 

> Initializes I2C driver and writes basic settings to device registers

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    proximity7_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    proximity7_cfg_setup( &cfg );
    PROXIMITY7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    proximity7_init( &proximity7, &cfg );

    write_buffer[0] = 0x00;
    proximity7_generic_write( &proximity7, PROXIMITY7_ENABLE | PROXIMITY7_REPEATED_BYTE, &write_buffer[0], 1 );

    Delay_ms(100);

    proximity7_set_als_integration_time( &proximity7, 400.0 );
    proximity7_set_proximity_integration_time( &proximity7, 2.73 );
    proximity7_set_wait_time( &proximity7, 2.73 );
    proximity7_set_proximity_pulse_count( &proximity7,8 );

    write_buffer[0] = PROXIMITY7_LED_DRIVE_100mA |
                      PROXIMITY7_PROXIMITY_DIODE_CH1 |
                      PROXIMITY7_PROXIMITY_GAIN_1x |
                      PROXIMITY7_ALS_GAIN_8x;
    proximity7_generic_write( &proximity7, PROXIMITY7_GAIN_CONTROL | PROXIMITY7_REPEATED_BYTE, &write_buffer[0], 1 );

    write_buffer[0] = PROXIMITY7_WAIT_ENA |
                      PROXIMITY7_PROXIMITY_ENA |
                      PROXIMITY7_ALS_ENA |
                      PROXIMITY7_POWER_ON;
   proximity7_generic_write( &proximity7, PROXIMITY7_ENABLE | PROXIMITY7_REPEATED_BYTE, &write_buffer[0], 1 );
    Delay_ms(100);

    log_printf( &logger, "> > > app init done < < <\r\n" );

}
  
```

### Application Task

> Logs lux level and proximity data

```c

void application_task ( void )
{
    proximity7_generic_read( &proximity7, PROXIMITY7_STATUS | PROXIMITY7_REPEATED_BYTE, &read_buffer[0], 1 );
    
    als_valid = read_buffer[0] & PROXIMITY7_ALS_VALID_MASK;
    proximity_valid = read_buffer[0] & PROXIMITY7_PROXIMITY_VALID_MASK;
    
    if (als_valid != 0 && proximity_valid != 0)
    {
        log_printf( &logger, " " );

        lux_level = proximity7_get_lux_level( &proximity7 );
        log_printf( &logger, "> > > Lux level   : %f lx\r\n", lux_level );
    
        proximity = proximity7_get_proximity_data( &proximity7 );
        log_printf( &logger, "> > > Proximity   : %d\r\n", proximity );

        write_buffer[0] = PROXIMITY7_SPECIAL_FUNCTION | PROXIMITY7_PROXIMITY_AND_ALS_INT_PIN_CLEAR;
        proximity7_generic_write( &proximity7, PROXIMITY7_SPECIAL_FUNCTION | PROXIMITY7_PROXIMITY_AND_ALS_INT_PIN_CLEAR, &write_buffer[0], 1 );
    }
    
    Delay_ms(300);
}  

```

## Note

> - When setting LED drive strength please note that if "proximity drive level - PDL" bit in "configuration register" is set to 1, LED drive current values are reduced by 9.
  - When setting wait time note that if "wait long - WLONG" bit is set to 1, time is 12x longer. Therefore if WLONG == 1 set time between 33ms and 8386.56ms.
  - When setting ALS gain note that if "ALS gain level - AGL" bit is set to 1, ALS gains are scaled by 0.16, otherwise, they are scaled by 1.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity7

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
