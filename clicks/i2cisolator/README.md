\mainpage Main Page
 
 

---
# I2C isolator click

I2C Isolator click carries ISO1540, a low-power, bidirectional isolator compatible with I2C interfaces. On the board, the Texas Instruments chip is connected to two sets of I2C pins, one on the mikroBUS connector (SDA, SCL), the other on the upper edge of the board (SCL2, SDL2).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/i2cisolator_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/i2c-isolator-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the I2Cisolator Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for I2Cisolator Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void i2cisolator_cfg_setup ( i2cisolator_cfg_t *cfg ); 
 
- Initialization function.
> I2CISOLATOR_RETVAL i2cisolator_init ( i2cisolator_t *ctx, i2cisolator_cfg_t *cfg );

#### Example key functions :

- Generic write function.
> void i2cisolator_generic_write ( i2cisolator_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
 
- Generic read function.
> void i2cisolator_generic_read ( i2cisolator_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

## Examples Description

> 
> This is an example which demonstrates the use of I2C Isolator Click board.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Initialization driver enables - I2C,
> sets configuration of TMP007 sensor on IrThermo 2 click and start to write log.
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    i2cisolator_cfg_t cfg;
    uint8_t tmp;

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

    i2cisolator_cfg_setup( &cfg );
    I2CISOLATOR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    i2cisolator_init( &i2cisolator, &cfg );

    log_printf( &logger, "    Driver  Initialized\r\n" );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms ( 100 );
    
    tmp =    I2CISOLATOR_IRTHERMO2_CFG_MODEON |
                I2CISOLATOR_IRTHERMO2_CFG_ALERTEN | 
                I2CISOLATOR_IRTHERMO2_CFG_TRANSC | 
                I2CISOLATOR_IRTHERMO2_CFG_16SAMPLE;
    i2cisolator_generic_write( &i2cisolator, I2CISOLATOR_IRTHERMO2_CONFIGURATION, &tmp, 1 );

    tmp =    I2CISOLATOR_IRTHERMO2_STAT_ALERTEN | 
                I2CISOLATOR_IRTHERMO2_STAT_CRTEN;
    i2cisolator_generic_write( &i2cisolator, I2CISOLATOR_IRTHERMO2_STATUS_MASK_AND_ENABLE, &tmp, 1 );    
    
    log_printf( &logger, "       Configuration\r\n" );
    log_printf( &logger, "      IrThermo 2 Click\r\n" );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms ( 100 );
}
  
```

### Application Task

>
> In this example we use IrThermo 2 click, measures the temperature with,
> and calculate the temperature in degrees Celsius [ C ].
> Results are being sent to the USART Terminal where you can track their changes.
> All data logs on usb uart each second.
> 

```c

void application_task ( void )
{
    i2cisolator_get_temperature( );   
    
    log_printf( &logger, " Temperature : %0.2f C\r\n", temperature );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms ( 1000 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.I2Cisolator

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
