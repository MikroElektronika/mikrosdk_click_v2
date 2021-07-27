 

---
# Pressure click

Pressure Click is a compact and easy solution for adding pressure measurement to your design.
It features LPS331AP digital output pressure sensor.


<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pressure_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/pressure-click)

---


#### Click library

- **Author**        : Nemanja Medakovic
- **Date**          : Nov 2019.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Pressure Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers).
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account.

## Library Description

> This library contains API for Pressure Click driver.

#### Standard key functions :

- Configuration Object Setup function.
> void pressure_cfg_setup( pressure_cfg_t *cfg );

- Click Initialization function.
> pressure_err_t pressure_init( pressure_t *ctx, pressure_cfg_t *cfg );

- Click Default Configuration function.
> void pressure_default_cfg( pressure_t *ctx );


#### Example key functions :

- Generic Single Write function.
> pressure_err_t pressure_generic_single_write( pressure_t *ctx, uint8_t reg_addr, uint8_t data_in );

- Generic Multiple Read function.
> pressure_err_t pressure_generic_multiple_read( pressure_t *ctx, uint8_t reg_addr, uint8_t *data_out, uint8_t n_data );

- Pressure Get function.
> float pressure_get_pressure( pressure_t *ctx );

## Examples Description

>
> This is a example which demonstrates the use of Pressure Click board.
> Measured pressure and temperature data from the LPS331AP sensor on Pressure click.
>

**The demo application is composed of two sections :**

### Application Init

>
> Initializes I2C/SPI serial interface and puts a device to the initial state.
> Also initializes UART console module for results logging.
>

```c

void application_init( void )
{
    pressure_cfg_t pressure_cfg;
    log_cfg_t console_cfg;

    //  Click initialization.
    pressure_cfg_setup( &pressure_cfg );
    PRESSURE_MAP_MIKROBUS( pressure_cfg, MIKROBUS_1 );
    pressure_init( &pressure, &pressure_cfg );
    pressure_sw_reset( &pressure );
    pressure_default_cfg( &pressure );

    //  Console initialization.
    LOG_MAP_USB_UART( console_cfg );
    console_cfg.baud = 57600;
    log_init( &console, &console_cfg );
    log_write( &console, "***  Pressure initialization done  ***",
               LOG_FORMAT_LINE );
    log_write( &console, "**************************************",
               LOG_FORMAT_LINE );
}

```

### Application Task

>
> Reads the pressure and temperature results in standard units when
> measurement was done and sends results to the console (usb uart terminal).
> Repeats operation every 500ms.
>

```c

void application_task( void )
{
    uint8_t status;
    float press;
    float temp;

    status = pressure_get_status( &pressure, PRESSURE_FLAG_MASK_P_DATA_RDY |
                                             PRESSURE_FLAG_MASK_T_DATA_RDY );

    while (!status)
    {
        status = pressure_get_status( &pressure, PRESSURE_FLAG_MASK_P_DATA_RDY |
                                                 PRESSURE_FLAG_MASK_T_DATA_RDY );
    }

    press = pressure_get_pressure( &pressure );
    temp = pressure_get_temperature( &pressure );

    log_printf( &console, "** Pressure is %.2f mbar\r\n", press );
    log_printf( &console, "** Temperature is %.2f ", temp );
    log_write( &console, deg_cels, LOG_FORMAT_LINE );
    log_write( &console, "**************************************",
               LOG_FORMAT_LINE );

    Delay_ms( 500 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure

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
