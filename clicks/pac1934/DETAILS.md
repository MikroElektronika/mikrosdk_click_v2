

---
# Pac1934 click

PAC1934 click carries the PAC1934 four channel DC power/energy monitor from Microchip. The click is designed to run on either 3.3V or 5V power supply. It communicates with the target microcontroller over an I2C interface.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pac1934_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/pac1934-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Pac1934 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Pac1934 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void pac1934_cfg_setup ( pac1934_cfg_t *cfg ); 
 
- Initialization function.
> PAC1934_RETVAL pac1934_init ( pac1934_t *ctx, pac1934_cfg_t *cfg );

#### Example key functions :

- Write one byte function.
> void pac1934_write_byte ( pac1934_t *ctx, uint8_t wr_addr, uint8_t wr_data );
 
- Read one byte function.
> uint8_t pac1934_read_byte ( pac1934_t *ctx, uint8_t rd_addr );

- Send command function.
> void pac1934_send_command ( pac1934_t *ctx, uint8_t wr_cmd );

## Examples Description
 
> This application measures the voltage.

**The demo application is composed of two sections :**

### Application Init 

> Initalizes device, enables the device and makes an initial log. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    pac1934_cfg_t cfg;

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

    pac1934_cfg_setup( &cfg );
    PAC1934_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pac1934_init( &pac1934, &cfg );
}
  
```

### Application Task

> This is an example that shows the most important
> functions that PAC1934 click has, it mesures voltage, current, power and energy.

```c

void application_task ( void )
{
    float read_value;
    
    pac1934_dev_reset( &pac1934 );
    pac1934_write_byte( &pac1934, PAC1934_CHANNEL_DIS, PAC1934_CHANNEL_DIS_ALL_CHA );
    pac1934_write_byte( &pac1934, PAC1934_CTRL_REG, PAC1934_CTRL_SAMPLE_RATE_8 | PAC1934_CTRL_SINGLE_SHOT_MODE );
    Delay_ms ( 100 );
    pac1934_send_command( &pac1934, PAC1934_REFRESH_CMD );
    
    read_value = pac1934_measure_voltage( &pac1934, 1 );
    log_printf( &logger, "Voltage : %.2f V\r\n", read_value );

    read_value = pac1934_measure_current( &pac1934, 1 );
    log_printf( &logger, "Amperage :  %.2f mA\r\n", read_value );

    read_value = pac1934_measure_power( &pac1934, 1 );
    log_printf( &logger, "Power : %.2f W\r\n", read_value );
    
    read_value = pac1934_measure_energy( &pac1934, 1, 8 );
    log_printf( &logger, "Energy :  %.2f J \r\n", read_value );
    log_printf( &logger, "--------------------- \r\n" );
    Delay_ms ( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Pac1934

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
