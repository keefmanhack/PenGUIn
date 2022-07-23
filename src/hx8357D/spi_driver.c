#include <string.h>
#include <nrf.h>

#include "./spi_driver.h"
#include "./nrf52840_util.h"

#define ENABLE_SPIM         7
#define DISABLE_SPIM        0

#define CONNECTED           1
#define DISCONNECTED        0

#define EASY_DMA_ARR_LIST   1

#define CONNECT_BIT         31
#define PORT_BIT            5
#define MAX_PINS            0X1F
#define SET_SPI_PIN(conn, port, pin) (((conn << CONNECT_BIT) & 1) | ((port<<PORT_BIT) & 1) | (pin & MAX_PINS))

#define POL_BIT     2
#define PHASE_BIT   1
#define SET_CONFIG_REG(pol, phase, order) (((pol << POL_BIT) & 1) | ((phase << PHASE_BIT) & 1) | (order & 1))


enum sck_phase{
    LEADING =0,
    TRAILING =1,

    MAX_SCK_PHASE
};

enum sck_polarity{
    ACTIVEHIGH = 0,
    ACTIVELOW = 1,

    MAX_SCK_POLARITY
};


static struct spi_drvr {
    volatile uint8_t tx_buff[RX_TX_BUFFER_SIZE];
    volatile uint8_t rx_buff[RX_TX_BUFFER_SIZE];
} this_spi;


void SPI_init(const spi_settings_t * const ss){
    enum sck_phase phase;
    enum sck_polarity polarity;

    //  must disable before settings pins
    NRF_SPIM3->ENABLE = DISABLE_SPIM;

    //  config gpio i/o
    config_gpio_output(ss->sck_pin, ss->gpio_port); 
    config_gpio_output(ss->mosi_pin, ss->gpio_port); 
    config_gpio_output(ss->cs_pin, ss->gpio_port);  

    config_gpio_input(ss->miso_pin, ss->gpio_port);  
    
    //  set pins
    NRF_SPIM3->PSEL.SCK = SET_SPI_PIN(CONNECTED, ss->gpio_port, ss->sck_pin);
    NRF_SPIM3->PSEL.MOSI = SET_SPI_PIN(CONNECTED, ss->gpio_port, ss->miso_pin);
    NRF_SPIM3->PSEL.MISO = SET_SPI_PIN(CONNECTED, ss->gpio_port, ss->mosi_pin);
    NRF_SPIM3->PSEL.CSN = SET_SPI_PIN(CONNECTED, ss->gpio_port, ss->cs_pin);

    //  set frequency
    NRF_SPIM3->FREQUENCY = ss->max_speed;

    //  setup pointer to rx data
    NRF_SPIM3->RXD.PTR = this_spi.rx_buff;
    NRF_SPIM3->RXD.MAXCNT = RX_TX_BUFFER_SIZE;
    NRF_SPIM3->RXD.LIST = EASY_DMA_ARR_LIST;


    //  setup pointer to tx data
    NRF_SPIM3->TXD.PTR = this_spi.tx_buff;
    NRF_SPIM3->TXD.MAXCNT = RX_TX_BUFFER_SIZE;
    NRF_SPIM3->TXD.LIST = EASY_DMA_ARR_LIST;

    //  setup config
    switch(ss->data_mode){
        case SPI_MODE_0:
            phase = ACTIVEHIGH;
            polarity = LEADING;
            break;
        case SPI_MODE_1:
            phase = ACTIVEHIGH;
            polarity = TRAILING;
            break;
        case SPI_MODE_2:
            phase = ACTIVELOW;
            polarity = LEADING;
            break;
        default:
            phase = ACTIVELOW;
            polarity = TRAILING;
    }
    NRF_SPIM3->CONFIG = SET_CONFIG_REG(ss->data_order, 
                        phase, 
                        polarity);

    //  no rx_delay
    NRF_SPIM3->IFTIMING.RXDELAY = 0;

    //  no chip select delay
    NRF_SPIM3->IFTIMING.CSNDUR = 0;

    //  set chip select active low
    NRF_SPIM3->CSNPOL = 0;

    //  not using DCX pin

    //  enable SPIM 
    NRF_SPIM3->ENABLE = ENABLE_SPIM;

    //  reference documentation can be found here:
    //  https://infocenter.nordicsemi.com/index.jsp?topic=%2Fps_nrf52840%2Fspi.html&cp=4_0_0_5_23&anchor=concept_wj2_nt4_sr__table
}

uint8_t * SPI_getTXBuff(void){
    return this_spi.tx_buff;
}

void SPI_transfer(uint8_t * rx_buf, int * rx_size){
    //  start the transfer
    NRF_SPIM3->TASKS_START = 1;
    while(NRF_SPIM3->EVENTS_END == 0);
    NRF_SPIM3->TASKS_START = 0;

    rx_buf = this_spi.rx_buff;
    *rx_size = NRF_SPIM3->RXD.AMOUNT;
}

void SPI_stopTransfer(void){
    NRF_SPIM3->TASKS_STOP = 1;
}

void SPI_dispose(void){
    NRF_SPIM3->ENABLE = DISABLE_SPIM;
}