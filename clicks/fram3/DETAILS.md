
---
# FRAM 3 click

The FRAM 3 Click is a Click board™ that carries a ferroelectric RAM module. Ferroelectric RAM, also known as FRAM, is a non-volatile memory type, with characteristics that are comparable to much faster DRAM memory modules. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/fram3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/fram-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the FRAM3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for FRAM3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void fram3_cfg_setup ( fram3_cfg_t *cfg ); 
 
- Initialization function.
> FRAM3_RETVAL fram3_init ( fram3_t *ctx, fram3_cfg_t *cfg );


#### Example key functions :

- Memory read function
> uint8_t fram3_read_free_access_memory ( fram3_t *ctx, uint8_t start_addr, uint8_t *data_buf, uint8_t n_buf_size );
 
- Memory write function
> uint8_t fram3_write_free_access_memory ( fram3_t *ctx, uint8_t start_addr, uint8_t *data_buf, uint8_t n_buf_size );

## Examples Description

> This application writes data in memmory and reads data from memmory.

**The demo application is composed of two sections :**

### Application Init 

> Initializes device init

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    fram3_cfg_t cfg;

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

    fram3_cfg_setup( &cfg );
    FRAM3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    fram3_init( &fram3, &cfg );
}
  
```

### Application Task

> Writes and then reads data from memory

```c

void application_task (  )
{
    static char write_data[ 7 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 0 };
    static char read_data[ 7 ];
    static uint8_t cnt;
    static uint8_t status_check;

    log_printf( &logger, " - Writing...  \r\n" );
    Delay_ms( 500 );
    status_check = fram3_write_free_access_memory( &fram3, 0x00, &write_data[ 0 ], 7 );
    if ( status_check == FRAM3_ERROR )
    {
        log_printf( &logger, " - ERROR WRITING!!! \r\n" );
        for ( ; ; );
    }
    
    log_printf( &logger, " - Reading... \r\n" );
    Delay_ms( 500 );
    status_check = fram3_read_free_access_memory( &fram3, 0x00, &read_data[ 0 ], 7 );
    if ( status_check == FRAM3_ERROR )
    {
        log_printf( &logger, " - ERROR READING!!! \r\n" );
        for ( ; ; );
    }

    for ( cnt = 0; cnt < 7; cnt++ )
    {
        log_printf( &logger, " %c ", read_data[ cnt ] );
        Delay_ms( 100 );
    }
    log_printf( &logger, " \r\n " );
    Delay_ms( 1000 );
    log_printf( &logger, "__________________________\r\n " );
    Delay_ms( 500 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.FRAM3

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
