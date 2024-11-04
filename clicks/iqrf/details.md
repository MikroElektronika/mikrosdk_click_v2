

---
# iqRF Click

IQRF Click carries the RF transceiver, operating in the 868/916 MHz frequency.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/iqrf_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/iqrf-click)

---


#### Click library 

- **Author**        : Mihajlo Djordjevic
- **Date**          : Dec 2019.
- **Type**          : UART type


# Software Support

We provide a library for the iqRF Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for iqRF Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void iqrf_cfg_setup ( iqrf_cfg_t *cfg ); 
 
- Initialization function.
> IQRF_RETVAL iqrf_init ( iqrf_t *ctx, iqrf_cfg_t *cfg );

- Click Default Configuration function.
> void iqrf_default_cfg ( iqrf_t *ctx );

#### Example key functions :

- This function read one byte data.
> iqrf_data_t iqrf_generic_single_read ( iqrf_t *ctx );
 
- This function writes data.
> void iqrf_generic_multi_write ( iqrf_t *ctx, iqrf_data_t *data_buf,  uart_length_t len );

## Examples Description

> 
> RF transceiver - in first case reads one byte from RX buffer. 
> In the second case writes message data via UART.
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
    iqrf_cfg_t cfg;

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
    log_printf( &logger, "------------------------------------\r\n" );
    log_printf( &logger, "--------  Application  Init --------\r\n" );
    Delay_ms ( 1000 );

    //  Click initialization.

    iqrf_cfg_setup( &cfg );
    IQRF_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    iqrf_init( &iqrf, &cfg );
    
    log_printf( &logger, "------------------------------------\r\n" );
    log_printf( &logger, "------------ iqRF  Click -----------\r\n" );
    log_printf( &logger, "------------------------------------\r\n" );
    Delay_ms ( 1000 );
    
    iqrf_default_cfg ( &iqrf );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "---------- Initialization ----------\r\n" );
    log_printf( &logger, "------------------------------------\r\n" );
    Delay_ms ( 1000 );
}
  
```

### Application Task

>
> Checks if new data byte has received in RX buffer ( ready for reading ),
> and if ready than reads one byte from RX buffer. In the second case, 
> the application task writes message data via UART. Results are being sent 
> to the Usart Terminal where you can track their changes.
> 

```c

void application_task ( void )
{
    iqrf_data_t tmp;
    
#ifdef DEMO_APP_RECEIVER

    // RECEIVER - UART polling

    tmp =  iqrf_generic_single_read( &iqrf );
    log_printf( &logger, " %c ", tmp );
        
#endif
        
#ifdef DEMO_APP_TRANSCEIVER

    // TRANSMITER - TX each 2 sec
        
    uint8_t cnt;
        
    for ( cnt = 0; cnt < 9; cnt ++ )
    {
        iqrf_generic_single_write( &iqrf, demo_message[ cnt ] );
        Delay_ms ( 100 );
    }
    
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
       
#endif
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.iqRF

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
