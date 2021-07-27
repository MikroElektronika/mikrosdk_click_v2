\mainpage Main Page


---
# SWI EEPROM click

> SWI EEPROM Click is a compact add-on board that provides a highly reliable memory solution. This board features the AT21CS01, a single-wire serial EEPROM with a unique, factory-programmed 64-bit serial number from Microchip Technology.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/swi_eeprom_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/swi-eeprom-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : Jan 2021.
- **Type**          : SWI type


# Software Support

We provide a library for the ${ALIAS_NAME} Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).


#### Example key functions :

- `swieeprom_init` SWI EEPROM initialization function.
```c
swieeprom_return_value_t swieeprom_init ( swieeprom_t *ctx )
```

- `swieeprom_write_data_to_memory` SWI EEPROM write data to memory.
```c
swieeprom_return_value_t swieeprom_write_data_to_memory ( swieeprom_t *ctx, uint8_t start_mem_adr, uint8_t *tx_buf, uint16_t buf_len )
```

- `swieeprom_read_data_from_memory` SWI EEPROM read data from memory.
```c
swieeprom_return_value_t swieeprom_read_data_from_memory ( swieeprom_t *ctx, uint8_t start_mem_adr, uint8_t *rx_buf, uint16_t buf_len )
```

## Example Description

> This application shows capability of SWI EEPROM Click board.
 It checks if device is present, initializes it and show it's
 functionality to read from memory and write to memory.

**The demo application is composed of two sections :**

### Application Init

> Initialization of log and communication pin. Checks if device
is present and then it's slave address, and checks communication  
with checking devices ID.

```c

void application_init ( void )
{
    log_init( );
    log_line( " > Application init <" );
    if ( swieeprom_init( &swieeprom ) )
    {
        log_line( " > ERROR!" );
        for( ; ; );
    }
    else
    {
        log_line( " > Device init done!" );
    }
    
    //read id
    if ( swieeprom_read_id( &swieeprom ) )
    {
        log_line( " > ID ERROR!" );
    }
    else
    {
        log_line( " > ID OK!" );
    }
    
    Delay_ms( 500 );
    log_line( " > Application Task <" );
    log_line( "******************************************" );
}

```

### Application Task

> Sends WRITE_DATA_STRING to the device, starting from START_MEMORY_ADDRESS.
Then reads that written data and checks if it matches with written data.
After that clears that same data and then reads it again to check if data is cleared.

```c

static void application_task ( void )
{
    #define WRITE_DATA_STRING     "MikroE"
    #define START_MEMORY_ADDRESS  0x10
    
    //write memory
    if ( swieeprom_write_data_to_memory( &swieeprom, START_MEMORY_ADDRESS, WRITE_DATA_STRING, 6 ) )
    {
        log_line( " > Write ERROR!" );
    }
    else
    {
        log_line( " > Write done!" );
    }
    Delay_ms( 1000 );
    
    //read_memory
    uint8_t rx_buf[ 8 ] = { 0 };
    if ( swieeprom_read_data_from_memory( &swieeprom, START_MEMORY_ADDRESS, rx_buf, 6 ) )
    {
        log_line( " > Read ERROR!" );
    }
    else
    {
        log_txt( " > Read data: " );
        log_line( rx_buf );
        if ( 0 != strstr( rx_buf, WRITE_DATA_STRING ) )
        {
            log_line( " > Data Match!" );
        }
        else
        {
            log_line( " > Data Mismatch!" );
        }
    }
    Delay_ms( 1000 );
    
    //clear memory
    if ( swieeprom_clear_data_from_memory( &swieeprom, START_MEMORY_ADDRESS, 6 ) )
    {
        log_line( " > Clear ERROR!" );
    }
    else
    {
        log_line( " > Clear done!" );
    }
    Delay_ms( 1000 );
    
    //read_memory
    uint8_t rec_buf[ 8 ] = { 0 };
    if ( swieeprom_read_data_from_memory( &swieeprom, START_MEMORY_ADDRESS, rec_buf, 6 ) )
    {
        log_line( " > Read ERROR!" );
    }
    else
    {
        log_txt( " > Read data: " );
        log_line( rec_buf );
        
        if ( 0 != strstr( rec_buf, WRITE_DATA_STRING ) )
        {
            log_line( " > Data not cleared!" );
        }
        else
        {
            log_line( " > Data cleared!" );
        }
    }
    
    log_line( "******************************************" );
    Delay_ms( 3000 );
}

```

## Note

> This application is written for Legacy profiles for ARM{STM32F407ZG},
PIC{PIC18F97J94}, PIC32{PIC32MX975F512L} and specificly for Mikrobus 1.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---
