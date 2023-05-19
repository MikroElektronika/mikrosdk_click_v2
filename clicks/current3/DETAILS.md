
---
# Current 3 click

Current 3 Click is a compact add-on board for applications like current sense and temperature monitoring.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/current3_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/current-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jul 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Current3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Current3 Click driver.

#### Standard key functions :

- `current3_cfg_setup` Config Object Initialization function.
```c
void current3_cfg_setup ( current3_cfg_t *cfg ); 
```

- `current3_init` Initialization function.
```c
err_t current3_init ( current3_t *ctx, current3_cfg_t *cfg );
```

- `current3_default_cfg` Click Default Configuration function.
```c
void current3_default_cfg ( current3_t *ctx );
```

#### Example key functions :

- `current3_get_temperature` The function get the temperature by read multiple data bytes from a group of contiguous registers
```c
float current3_get_temperature ( current3_t *ctx, uint8_t temp_sel );
```

- `current3_get_source_voltage` The function source voltage registers store the voltage measured at the SENSE+ pin
```c
float current3_get_source_voltage ( current3_t *ctx );
```

- `current3_get_current` The function current measurement measure the direction of current flow ( from SENSE+ to SENSE- or from SENSE- to SENSE+ )
```c
float current3_get_current ( current3_t *ctx );
```

## Examples Description

> Current 3 Click can be used to measure current ranging up to 8000mA, and display temperature, 
> voltage and current data - using I2C comunication.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enables - I2C,
> check communication and set sense sampling configuration, also write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    current3_cfg_t cfg;
    uint8_t read_data;

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

    current3_cfg_setup( &cfg );
    CURRENT3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    current3_init( &current3, &cfg );

    Delay_ms( 100 );
    log_printf( &logger, "     Driver init. done     \r\n" );
    log_printf( &logger, "---------------------------\r\n" );
    
    current3_generic_read( &current3, CURRENT3_REG_PRODUCT_ID, &read_data, 1 );
    if (  read_data == CURRENT3_DEV_ID )
    {
        log_printf( &logger, "     Communication OK      \r\n" );
        log_printf( &logger, "---------------------------\r\n" );
    }
    else
    {
        log_printf( &logger, "    Communication ERROR    \r\n" );
        log_printf( &logger, "     Reset the device      \r\n" );
        log_printf( &logger, "---------------------------\r\n" );
        for ( ; ; );
    }
    
    current3_default_cfg( &current3, sense_cfg_data );
}
  
```

### Application Task

> This is an example which demonstrates the use of Current 3  Click board.
> Current 3 Click board can be used to measure current ranging
> up to 8000mA, and display temperature, voltage and current data.
> All data logs write on USB uart changes for every 2 sec.

```c

void application_task ( void )
{
    temperature = current3_get_temperature( &current3, CURRENT3_TEMP_INTERNAL_DIODE );
    log_printf( &logger, " Temperature = %.2f C\r\n", temperature );

    voltage = current3_get_source_voltage( &current3 );
    log_printf( &logger, " Voltage     = %.2f V\r\n", voltage );

    current = current3_get_current( &current3 );
    log_printf( &logger, " Current     = %.2f mA\r\n", current );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms( 2000 );
} 

``` 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Current3

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
