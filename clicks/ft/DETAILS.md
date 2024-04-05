
---
# FT click

> FT Click is a compact smart transceiver add-on board that helps you add a Free Topology (FT) interface to any host board with the mikroBUS™ socket. Leveraging FT, the most reliable and easiest-to-scale wired communications media, FT Click lets you network sensors and devices to create IoT solutions for automation and control networks that are easier to develop, integrate and install. This Click board™ supports full communication stacks for LON® and BACnet FT, as well as FTMQ (MQTT like messaging format) on board to simplify integration of BACnet, LON or custom IoT networks over twisted pair wire. FT Click is ideal for markets including smart buildings, cities, machines, agriculture, manufacturing, transportation and many more where wireless communications do not provide the required reliability and scale.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ft_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ft-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : UART type


# Software Support

We provide a library for the Ft Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Ft Click driver.

#### Standard key functions :

- `ft_cfg_setup` Config Object Initialization function.
```c
void ft_cfg_setup ( ft_cfg_t *cfg ); 
```

- `ft_init` Initialization function.
```c
err_t ft_init ( ft_t *ctx, ft_cfg_t *cfg );
```

#### Example key functions :

- `ft_get_data_status` Use this function to get current status of data
```c
uint8_t ft_get_data_status ( ft_t *ctx );
```

- `ft_get_data` Use this function to read received data
```c
uint16_t ft_get_data ( ft_t *ctx, uint8_t *data_buf );
```

- `ft_send_package` Use this function to send data to other module
```c
void ft_send_package ( ft_t *ctx, uint8_t *data_buf, uint16_t len, uint8_t queue );
```

## Example Description

> This example demonstrates the use of an FT click board by showing the communication between the two click boards.

**The demo application is composed of two sections :**

### Application Init 

> Initalizes device and makes an initial log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    ft_cfg_t ft_cfg;

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    ft_cfg_setup( &ft_cfg );
    FT_MAP_MIKROBUS( ft_cfg, MIKROBUS_1 );
    if ( UART_ERROR == ft_init( &ft, &ft_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

#ifdef DEMO_APP_TRANSMITTER
    log_printf( &logger, " Application Mode: Transmitter\r\n" );
#else
    log_printf( &logger, " Application Mode: Receiver\r\n" );
#endif
    log_info( &logger, " Application Task " );
}
  
```

### Application Task

> Depending on the selected application mode, it reads all the received data or sends the desired text message once per second.

```c

void application_task ( void )
{
#ifdef DEMO_APP_TRANSMITTER
    ft_send_package( &ft, DEMO_TEXT_MESSAGE, strlen( DEMO_TEXT_MESSAGE ), 1 );
    log_printf( &logger, " Sent data: %s", ( char * ) DEMO_TEXT_MESSAGE );
    Delay_ms ( 1000 );
#else
    uint8_t rsp_data_buf[ FT_MAX_DATA_BUFFER ] = { 0 };
    uint8_t rx_byte = 0;
    if ( 1 == ft_generic_read( &ft, &rx_byte, 1 ) )
    {
        ft_isr_parser( &ft, rx_byte ); 
        if ( FT_NEW_DATA_AVAILABLE == ft_get_data_status( &ft ) )
        {
            if ( ft_get_data( &ft, rsp_data_buf ) )
            {
                log_printf( &logger, " Received data: %s", rsp_data_buf );
            }
        }
    }
#endif
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Ft

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
