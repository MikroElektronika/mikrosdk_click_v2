 
---
# Temp Log 6 click

Temp-Log 6 click is a temperature sensing Click board™, which features the MAX6642, a specifically designed IC, capable of measuring its own die temperature, as well as a temperature at a remote PN junction. This option makes Temp-Log 6 click well-suited for monitoring the temperature of a CPU, GPU or FPGA, where the PN junction is typically a substrate PNP transistor on the die of the measured IC.
 
<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/templog6_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/temp-log-6-click)

---

#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the TempLog6 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for TempLog6 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void templog6_cfg_setup ( templog6_cfg_t *cfg ); 
 
- Initialization function.
> TEMPLOG6_RETVAL templog6_init ( templog6_t *ctx, templog6_cfg_t *cfg );

- Click Default Configuration function.
> void templog6_default_cfg ( templog6_t *ctx );


#### Example key functions :

- Writes one byte of data.
> void templog6_write_byte ( templog6_t *ctx, uint8_t reg, uint8_t data_buf );
 
- Reads one byte of data.
> uint8_t templog6_read_byte ( templog6_t *ctx, uint8_t reg ); 

- Gets the INT pin.
> uint8_t templog6_get_interrupt ( templog6_t *ctx );


## Examples Description
 
> The example starts off with the initialization and configuration of the click and logger modules, tests the communication channel and reads and displays local and remote temperature values every second.

**The demo application is composed of two sections :**

### Application Init 

> Initializes and configures the click and logger modules and tests the communication for errors.

```c

void application_init ( )
{
    log_cfg_t log_cfg;
    templog6_cfg_t cfg;

    uint8_t test;

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

    templog6_cfg_setup( &cfg );
    TEMPLOG6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    templog6_init( &templog6, &cfg );
        
    // Test communication 

    test = templog6_read_byte( &templog6, TEMPLOG6_REG_MANUFACTURER_ID );

    if ( test == TEMPLOG6_MANUFACTURER_ID )
    {
        log_printf( &logger, "--- Comunication OK!!! ---\r\n" );
    }
    else
    {
        log_printf( &logger, "--- Comunication ERROR!!! ---\r\n" );
        for ( ; ; );
    }

    templog6_default_cfg( &templog6 );

    log_printf( &logger, "--- Start measurement ---\r\n" );
}
  
```

### Application Task

> Reads and displays local and remote temperature values every second.

```c

void application_task ( void )
{
    float remote_temp;
    float local_temp;
    
    local_temp = templog6_read_byte( &templog6, TEMPLOG6_REG_LOCAL_TEMPERATURE );
    log_printf( &logger, "--- Local Temperature: %f C\r\n", local_temp );
    
    remote_temp = templog6_read_byte( &templog6, TEMPLOG6_REG_REMOTE_TEMPERATURE );
    log_printf( &logger, "--- Remote Temperature: %f C\r\n", remote_temp );
    
    log_printf( &logger, "-----------------------------\r\n" );
    Delay_ms( 1000 );
}  

``` 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.TempLog6

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
