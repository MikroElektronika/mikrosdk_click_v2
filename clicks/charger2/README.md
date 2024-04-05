\mainpage Main Page
 
 

---
# Charger 2 click

Charger 2 click is a LiPo/Li-Ion battery charger with the additional monitoring IC onboard. This Click board™ as a whole, offers unpreceded battery charging and monitoring solution for 3.7V LiPo/Li-Ion batteries, with the capacity measurement/gas gauge function, for up to 7000 mAh.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/charger2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/charger-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Charger2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https:///shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https:///shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Charger2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void charger2_cfg_setup ( charger2_cfg_t *cfg ); 
 
- Initialization function.
> CHARGER2_RETVAL charger2_init ( charger2_t *ctx, charger2_cfg_t *cfg );

- Click Default Configuration function.
> void charger2_default_cfg ( charger2_t *ctx );


#### Example key functions :

- This function writes one byte data to the register.
> uint8_t charger2_write_reg ( charger2_t *ctx, uint8_t register_address, uint8_t transfer_data );
 
- This function reads the desired data from data registers and converts this data to the appropriate unit.
> uint8_t charger2_read_data ( charger2_t *ctx, uint8_t data_mode, uint32_t *data_out );

- This function checks is conversion cycle for battery current, or for battery voltage and temperature, finished, and if is not, waits until one of this conversions be finished.
> uint8_t charger2_check_conv_cycle( charger2_t *ctx, uint8_t conv_mode );

## Examples Description

> This app charges the battery.

**The demo application is composed of two sections :**

### Application Init 

> Initializes device.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    charger2_cfg_t cfg;

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

    charger2_cfg_setup( &cfg );
    CHARGER2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    charger2_init( &charger2, &cfg );

    Delay_ms ( 500 );
    
    charger2_reset( &charger2, CHARGER2_RESET_COUNTER_MODE );
    Delay_ms ( 1000 );
    charger2_write_reg( &charger2, CHARGER2_REG_MODE, CHARGER2_AUTO_DETECT | CHARGER2_14_BITS_RESOLUTION | CHARGER2_OPERATING_MODE );
    log_printf( &logger, "Charger 2 is initialized \r\n" );
    log_printf( &logger, "------------------------------ \r\n" );
    Delay_ms ( 300 );
}
  
```

### Application Task

> Reads the all necessary information for the battery charging status and logs this results on UART.
> Repeats operation every second.
> The LED diodes are used to indicate the Vcc presence when this voltage is in operating range, and to show the charging status.

```c

void application_task ( void )
{
    charger2_read_data( &charger2, CHARGER2_GAS_GAUGE_CHARGE_DATA, &battery_data );
    results_logger( &charger2 );
    charger2_read_data( &charger2, CHARGER2_CONV_NUMBER, &battery_data );
    results_logger( &charger2 );
    charger2_read_data( &charger2, CHARGER2_SHUNT_VOLTAGE, &battery_data );
    results_logger( &charger2 );
    charger2_read_data( &charger2, CHARGER2_BATTERY_VOLTAGE, &battery_data );
    results_logger( &charger2 );
    charger2_read_data( &charger2, CHARGER2_TEMPERATURE, &battery_data );
    results_logger( &charger2 );
    charger2_read_data( &charger2, CHARGER2_BATTERY_CURRENT, &battery_data );
    results_logger( &charger2 );
    
    log_printf( &logger, "------------------------------ \r\n" );
    Delay_ms ( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Charger2

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https:///shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https:///shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https:///shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https:///shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
