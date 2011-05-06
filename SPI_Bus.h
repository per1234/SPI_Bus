/* This is header file for SPI_Bus library which gives the programmer
 * more convinient way of working with SPI than the standard SPI library.
 * More strictly speaking, SPI_Bus is built on top of it.
 *
 * (C) 2011 Artem Borisovskiy, bytefu@gmail.com
 */

#ifndef SPI_BUS_H
#define SPI_BUS_H

#include <inttypes.h>
#include "WProgram.h"
#include "SPI.h"
#include "PinDriver.h"

enum
{
  _8bit = 1,
  _16bit = 2,
  _24bit = 3,
  _32bit = 4,
  _64bit = 8,
};


class SPI_Bus: public PinDriver
{
public:
  enum Implementation { HARDWARE, SOFTWARE };

  SPI_Bus(uint8_t bandwidth, uint8_t select_pin,
    uint8_t bit_order = MSBFIRST, PinDriver *pin_driver = 0);

  SPI_Bus(uint8_t bandwidth, uint8_t select_pin,
    uint8_t clock_pin, uint8_t data_pin,
    uint8_t bit_order = MSBFIRST, PinDriver *pin_driver = 0);

  SPI_Bus(const SPI_Bus &prototype);

  SPI_Bus& operator=(const void *data);
  SPI_Bus& operator=(const SPI_Bus &right);
  SPI_Bus& operator=(uint8_t data);
  SPI_Bus& operator=(uint16_t data);
  SPI_Bus& operator=(const uint32_t &data);
  SPI_Bus& operator=(const uint64_t &data);

  uint8_t read8bit();
  uint16_t read16bit();
  uint32_t read32bit();
  uint64_t read64bit();
  const uint8_t* read();
  
  uint8_t bandwidth() const;
  const uint8_t* getBuffer() const;

  virtual void pinConfig(uint8_t pin, uint8_t mode);
  virtual void pinWrite(uint8_t bit, uint8_t value);
  virtual uint8_t pinRead(uint8_t pin);

  void setBitOrder(uint8_t bit_order);
  void setClockDivider(uint8_t clock_divider);
  void setMode(uint8_t mode); // only supported for hardware SPI implementation
  void setImplementation(Implementation type);

private:  
  PinDriver *m_pins;
  uint8_t m_bandwidth;
  bool m_hardware_SPI;
  uint8_t m_clock_div; // hardware SPI
  uint8_t m_clock_pin; // software SPI
  uint8_t m_data_pin;  // software SPI
  uint8_t m_select_pin;
  uint8_t m_bit_order;
  uint8_t *m_buffer;

  void init(PinDriver *pin_driver, uint8_t bandwidth, Implementation impl_type,
    uint8_t clock_div, uint8_t select_pin, uint8_t clock_pin, uint8_t data_pin, uint8_t bit_order);

  void sendBuffer();
  void receiveFullBuffer();
  uint8_t softwareRead(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder);
  void softwareWrite(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val);
  void clearBufferFrom(uint8_t pos);
};

#endif // SPI_BUS_H_
