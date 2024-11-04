\mainpage Main Page
 
---
# LR 4 Click

LR 4 Click is a compact add-on board that contains a long-range transceiver. This board features the 32001353, RF technology-based SRD transceiver, which operates at a frequency of 868MHz from Mipot. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lr4_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/lr-4-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : UART type


# Software Support

We provide a library for the LR4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for LR4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void lr4_cfg_setup ( lr4_cfg_t *cfg ); 
 
- Initialization function.
> LR4_RETVAL lr4_init ( lr4_t *ctx, lr4_cfg_t *cfg );


#### Example key functions :

- Function performs the recovery of EEPROM default values.
> LR4_RETVAL lr4_factory_reset ( lr4_t *ctx );
 
- Function writes data to EEPROM.
> LR4_RETVAL lr4_write_eeprom ( lr4_t *ctx, uint8_t address, uint8_t n_bytes, uint8_t *data_in );

- Function performs the transmission of radio frames.
> LR4_RETVAL lr4_tx_message ( lr4_t *ctx, lr4_tx_msg_t *tx_msg );

## Examples Description

> This example reads and processes data from LR 4 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver, and resets the Click board to factory default configuration.
> Then performs a group of commands for getting the FW version, the serial number, and the DevEUI.
> After that executes the join activation by personalization command.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    lr4_cfg_t cfg;

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

    lr4_cfg_setup( &cfg );
    LR4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lr4_init( &lr4, &cfg );

    Delay_ms ( 100 );
    lr4_set_ind_handler( &lr4, response_handler );
    log_printf( &logger, "Hard reset!\r\n" );
    lr4_hard_reset( &lr4 );
    log_printf( &logger, "------------------------\r\n" );
    log_printf( &logger, "Factory reset!\r\n" );
    lr4_factory_reset( &lr4 );
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms ( 1000 );
    uint32_t tmp_data = 0;
    log_printf( &logger, "Get FW version!\r\n" );
    lr4_get_fw_version( &lr4, &tmp_data );
    log_printf( &logger, "FW vesion is: 0x%.8LX\r\n", tmp_data );
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms ( 1000 );
    log_printf( &logger, "Get Serial Number!\r\n" );
    lr4_get_serial_no( &lr4, &tmp_data );
    log_printf( &logger, "Serial Number is: 0x%.8LX\r\n", tmp_data );
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms ( 1000 );
    uint8_t tmp_buf[ 8 ] = { 0 };
    log_printf( &logger, "Get Dev EUI!\r\n" );
    lr4_get_dev_eui( &lr4, tmp_buf );
    log_printf( &logger, "Dev EUI is: 0x%.2X%.2X%.2X%.2X%.2X%.2X%.2X%.2X\r\n", ( uint16_t ) tmp_buf[ 7 ],
                                                                               ( uint16_t ) tmp_buf[ 6 ],
                                                                               ( uint16_t ) tmp_buf[ 5 ],
                                                                               ( uint16_t ) tmp_buf[ 4 ],
                                                                               ( uint16_t ) tmp_buf[ 3 ],
                                                                               ( uint16_t ) tmp_buf[ 2 ],
                                                                               ( uint16_t ) tmp_buf[ 1 ],
                                                                               ( uint16_t ) tmp_buf[ 0 ] );
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms ( 1000 );
    log_printf( &logger, "Join Network!\r\n" );
    lr4_join_network( &lr4, LR4_JOIN_ACTIVATION_BY_PERSONALIZATION_MODE );
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms ( 1000 );
}
  
```

### Application Task

> Checks the activation and session status and displays the results on the USB UART.

```c

void application_task ( void )
{
    log_printf( &logger, "Get Activation Status!\r\n" );
    uint8_t status = lr4_get_status( &lr4, LR4_GET_ACTIVATION_MODE );
    log_printf( &logger, "Status: " );
    switch ( status )
    {
        case LR4_STATUS_NOT_ACTIVATED :
        {
            log_printf( &logger, "Not activated.\r\n" );
            break;
        }
        case LR4_STATUS_JOINING :
        {
            log_printf( &logger, "Joining...\r\n" );
            break;
        }
        case LR4_STATUS_JOINED :
        {
            log_printf( &logger, "Joined.\r\n" );
            break;
        }
        case LR4_STATUS_MAC_ERROR :
        {
            log_printf( &logger, "MAC ERROR.\r\n" );
            break;
        }
        default :
        {
            break;
        }
    }
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms ( 1000 );
    log_printf( &logger, "Get Session Status!\r\n" );
    status = lr4_get_status( &lr4, LR4_GET_SESSION_STATUS_MODE );
    log_printf( &logger, "Status: " );
    switch ( status )
    {
        case LR4_STATUS_IDLE :
        {
            log_printf( &logger, "Idle.\r\n" );
            break;
        }
        case LR4_STATUS_BUSY :
        {
            log_printf( &logger, "Busy (LR session running).\r\n" );
            break;
        }
        case LR4_STATUS_DEV_NOT_ACTIVATED :
        {
            log_printf( &logger, "Device not activated.\r\n" );
            break;
        }
        case LR4_STATUS_DELAYED :
        {
            log_printf( &logger, "Delayed (LR session paused due to Duty-cycle).\r\n" );
            break;
        }
        default :
        {
            break;
        }
    }
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms ( 1000 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.LR4

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
