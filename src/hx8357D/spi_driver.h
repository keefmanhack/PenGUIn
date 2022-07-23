#include <stdint.h>

enum data_order{
    LSB_FIRST,
    MSB_FIRST,

    MAX_DATA_ORDER
};

enum data_mode{
    SPI_MODE_0,
    SPI_MODE_1,
    SPI_MODE_2,
    SPI_MODE_3,

    MAX_SPI_MODES
};

enum data_rate{
    K125 = 0x02000000,
    K250 = 0x04000000,
    K500 = 0x08000000,
    M1   = 0x10000000,
    M2   = 0x20000000,
    M4   = 0x40000000,
    M8   = 0x80000000,
    M16  = 0x0A000000,
    M32  = 0x14000000
};

typedef struct spi_settings_t{
    enum data_rate max_speed;
    enum data_order data_order;
    enum data_mode data_mode;
    // enum sck_phase sck_phase;
    // enum sck_polarity sck_polarity;
    uint8_t gpio_port;
    uint8_t miso_pin;
    uint8_t mosi_pin;
    uint8_t sck_pin;
    uint8_t cs_pin;
} spi_settings_t;

#define RX_TX_BUFFER_SIZE   32 //bytes

void SPI_init(const spi_settings_t * const ss);
void SPI_transfer(uint8_t * rx_buf, int * rx_size);
uint8_t * SPI_getTXBuff(void);
void SPI_stopTransfer(void);
void SPI_dispose(void);
