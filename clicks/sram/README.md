\mainpage Main Page
 
 

---
# SRAM Click

SRAM Click presents additional 1Mbit SRAM memory that can be added to device.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/sram_click.png" height=300px>
</p>


[Click Product page](https://www.mikroe.com/sram-click)

---


#### Click library 

- **Author**        : Mihajlo Djordjevic
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Sram Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Sram Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void sram_cfg_setup ( sram_cfg_t *cfg ); 
 
- Initialization function.
> SRAM_RETVAL sram_init ( sram_t *ctx, sram_cfg_t *cfg );

- Click Default Configuration function.
> void sram_default_cfg ( sram_t *ctx );

#### Example key functions :

- Function write the 8-bit data to the target 24-bit register address of 23LC1024 chip.
> void sram_write_byte( sram_t *ctx, uint32_t reg_address, uint8_t write_data );
 
- Function read the 8-bit data to the target 24-bit register address of 23LC1024 chip.
> uint8_t sram_read_byte( sram_t *ctx, uint32_t reg_address );

## Examples Description

> 
> SRAM Click write and read data from 23LC1024 Serial RAM device.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Application Init performs Logger and Click initialization.
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    sram_cfg_t cfg;

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
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "     Application  Init\r\n" );
    Delay_ms ( 100 );

    //  Click initialization.

    sram_cfg_setup( &cfg );
    SRAM_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    sram_init( &sram, &cfg );
    
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " ------ SRAM Click  ----- \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " -- Initialization done --\r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
}
  
```

### Application Task

>
> SRAM Click communicates with register via SPI protocol by write data to and read data from 23LC1024 Serial RAM device. 
> Results are being sent to the UART where you can track their changes. 
> All data logs on USB UART for aproximetly every 5 sec.
> 

```c

void application_task ( void )
{
    log_printf( &logger, " Writing text :\r\n" );
   
    for ( n_cnt = 0; n_cnt < 16; n_cnt++ )
    {
        sram_write_byte( &sram, n_cnt, send_buffer[ n_cnt ] );
        Delay_ms ( 100 );
        
        log_printf( &logger, "%c", send_buffer[ n_cnt ] );

        mem_data[ n_cnt ] = sram_read_byte( &sram, n_cnt );
    }
    
    log_printf( &logger, "\r\n" );
    log_printf( &logger, " Read text :\r\n" );
    log_printf( &logger, "%s", &mem_data[ 0 ] );
    log_printf( &logger, "\r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    
    Delay_ms ( 1000 );
}

``` 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Sram

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
