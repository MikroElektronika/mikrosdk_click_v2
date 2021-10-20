
---
# I2C MUX 4 click

I2C MUX 4 Click is a compact add-on board that contains a dual bidirectional translating switch dedicated for applications with I2C slave address conflicts. This board features the TCA9543APWR, a low voltage 2-channel I2C bus switch with interrupt logic from Texas Instruments.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/i2cmux4_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/i2c-mux-4-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Sep 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the I2cMux4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for I2cMux4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void i2cmux4_cfg_setup ( i2cmux4_cfg_t *cfg ); 
 
- Initialization function.
> I2CMUX4_RETVAL i2cmux4_init ( i2cmux4_t *ctx, i2cmux4_cfg_t *cfg );

#### Example key functions :

- Get channel interrupt function
> uint8_t i2cmux4_get_ch_interrupt ( i2cmux4_t *ctx );
 
- Generic read data function
> void i2cmux4_rmt_read_bytes ( i2cmux4_t *ctx, uint8_t reg, uint8_t *p_rx_data, uint8_t n_bytes );

- Check interrupt function.
> uint8_t i2cmux4_check_int ( i2cmux4_t *ctx );

## Examples Description

> This example demonstrates the use of the I2C MUX 4 Click.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver, enables the click board and makes an initial log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    i2cmux4_cfg_t cfg;

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

    i2cmux4_cfg_setup( &cfg );
    I2CMUX4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    i2cmux4_init( &i2cmux4, &cfg );

    i2cmux4_power_on( &i2cmux4, I2CMUX4_ENABLE_POWER_ON );
    Delay_ms( 100 );
    
    i2cmux4_set_channel( &i2cmux4, I2CMUX4_SEL_CH_ALL_DISABLE, 0x00 );
    Delay_ms( 100 );
}
  
```

### Application Task

> In this example, we read the device ID register of the connected click boards.
> Channel 0 : 6DOF IMU 12 click [slave address: 0x68; reg: 0x00; id val.: 0x24],
> Channel 1 : Compass 3 click   [slave address: 0x30; reg: 0x2F; id val.: 0x0C].
> All data logs write on USB UART changes every 2 sec.

```c

void application_task ( void )
{
    // CH 0 - 6DOF IMU 12 click
    i2cmux4_set_channel( &i2cmux4, I2CMUX4_SEL_CH_0, 0x68 );
    Delay_ms( 100 );

    i2cmux4_rmt_read_bytes( &i2cmux4, 0x00, &rx_data, 1 );
    Delay_ms( 100 );

    log_printf( &logger, "    6DOF IMU 12 click   \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - \r\n" );
    log_printf( &logger, "       ID = 0x%.2X  \r\n", ( uint16_t ) rx_data );
    log_printf( &logger, "----------------------- \r\n" );
    Delay_ms( 1000 );
    
    
    // CH 1 - Compass 3 click
    i2cmux4_set_channel( &i2cmux4, I2CMUX4_SEL_CH_1, 0x30 );
    Delay_ms( 100 );

    i2cmux4_rmt_read_bytes( &i2cmux4, 0x2F, &rx_data, 1 );
    Delay_ms( 100 );

    log_printf( &logger, "      Compass 3 click      \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - \r\n" );
    log_printf( &logger, "       ID = 0x%.2X \r\n ", ( uint16_t ) rx_data );
    log_printf( &logger, "----------------------- \r\n" );
    Delay_ms( 1000 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.I2cMux4

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
