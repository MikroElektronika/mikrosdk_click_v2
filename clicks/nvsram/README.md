\mainpage Main Page

---
# nvSRAM click

nvSRAM Click is a compact add-on board that contains the most reliable nonvolatile memory. This board features the CY14B101J, a 1-Mbit nvSRAM organized as 128K words of 8 bits each with a nonvolatile element in each memory cell from Cypress Semiconductor. The embedded nonvolatile elements incorporate the QuantumTrap technology and provide highly reliable nonvolatile storage of data.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/nvsram_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/nvsram-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jul 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the nvSRAM Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for nvSRAM Click driver.

#### Standard key functions :

- `nvsram_cfg_setup` Config Object Initialization function.
```c
void nvsram_cfg_setup ( nvsram_cfg_t *cfg );
```

- `nvsram_init` Initialization function.
```c
err_t nvsram_init ( nvsram_t *ctx, nvsram_cfg_t *cfg );
```

#### Example key functions :

- `nvsram_send_cmd` The function sends the desired command to the CY14B101J2 1-Mbit (128K � 8) Serial (I2C) nvSRAM on nvSRAM click board.
```c
void nvsram_send_cmd ( nvsram_t *ctx, uint8_t cmd );
```

- `nvsram_memory_write` The function writes a sequential data starting of the targeted 17-bit memory address
```c
void nvsram_memory_write ( nvsram_t *ctx, uint32_t mem_adr, uint8_t *p_tx_data, uint16_t n_bytes );
```

- `nvsram_memory_read` The function read a sequential data starting from the targeted 17-bit memory address
```c
void nvsram_memory_read ( nvsram_t *ctx, uint32_t mem_adr, uint8_t *p_rx_data, uint16_t n_bytes );
```

## Example Description

> This is an example that demonstrates the use of the nvSRAM click board. In this example, we write and then read data from nvSRAM memory. Results are being sent to the Usart Terminal where you can track their changes. All data logs write on USB uart changes approximately for every 5 sec.

**The demo application is composed of two sections :**

### Application Init

> Initialization driver enables - I2C, lock Serial Number write, disable Block Protection and enable Memory Write, also write log.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    nvsram_cfg_t nvsram_cfg;  /**< Click config object. */

    // Logger initialization.
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );
    mem_addr = 1024;

    // Click initialization.
    nvsram_cfg_setup( &nvsram_cfg );
    NVSRAM_MAP_MIKROBUS( nvsram_cfg, MIKROBUS_1 );
    err_t init_flag = nvsram_init( &nvsram, &nvsram_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_printf( &logger,  "  Serial Number Lock   \r\n" );
    log_printf( &logger, " None Block Protection \r\n" );
    nvsram_reg_write( &nvsram, NVSRAM_MEM_CTL_REG, NVSRAM_SNL | NVSRAM_BP_NONE );
    Delay_ms( 100 );
    log_printf( &logger, " Enable Memory Write \r\n" );
    nvsram_enable_memory_write( &nvsram, NVSRAM_WRITE_MEMORY_ENABLE );
    Delay_ms( 100 );
    
    log_info( &logger, " Application Task \r\n" );
}

```

### Application Task

> Writing data to a memory address, then reading it back and logging it onto uart terminal.

```c

void application_task ( void ) {
    log_printf( &logger, "  Write data : %s \r\n", demo_data );
    nvsram_memory_write( &nvsram, mem_addr, &demo_data[ 0 ], 9 );
    log_printf( &logger, "- - - - - - - - - - - - \r\n" );
    Delay_ms( 100 );

    nvsram_memory_read( &nvsram, mem_addr, &read_data[ 0 ], 9 );
    log_printf( &logger, "  Read data  : %s \r\n", read_data );
    log_printf( &logger, "----------------------- \r\n" );
    Delay_ms( 5000 );
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.nvSRAM

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
