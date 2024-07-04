/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
* Visit for more information: https://docs.m5stack.com/en/unit/4relay
*
* Product: Unit 4RELAY.
* Date: 2022/7/22
*******************************************************************************
  Please connect to port ,Control 4 relays and demonstrate the asynchronous
  control relay LED
-------------------------------------------------------------------------------
  RELAY control reg           | 0x10
  -----------------------------------------------------------------------------
  Relay_ctrl_mode_reg[0]      | R/W | System control
                              | 7 | 6 | 5 | 4 | 3 | 2 | 1 |     0     |
                              | R | R | R | R | R | R | R | Sync Mode |
                              | -Sync Mode:0 LED&Relay Async
                              | -Sync Mode:1 LED&Relay Sync
  ---------------------------------------------------------------------------------
  Relay_ctrl_mode_reg[1]      | R/W | Relay & LED control
                              |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
                              | LED1| LED2| LED3| LED4| RLY1| RLY2| RLY3| RLY4|
-------------------------------------------------------------------------------*/
// Note: The relay can only be controlled in synchronous mode, if the relay is
// controlled in asynchronous mode, it will be invalid.
#pragma once

#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace M5Stack_4in8out {

/* static constexpr uint8_t UNIT_4IN8OUT_ADDR = 0X45;*/
static constexpr uint8_t UNIT_4IN8OUT_INPUT_REG = 0X10;
static constexpr uint8_t UNIT_4IN8OUT_OUTPUT_REG = 0X20;

enum class OutputBit : uint8_t { OUTPUT1 = 0, OUTPUT2 = 1, OUTPUT3 = 2, OUTPUT4 = 3, OUTPUT5 = 4, OUTPUT6 = 5, OUTPUT7 = 6, OUTPUT8 = 7 };//, RELAYALL = 255};
enum class InputBit : uint8_t { INPUT1 = 0, INPUT2 = 1, INPUT3 = 2, INPUT4 = 3, INPUTALL = 255 };

class M5Stack_4in8out : public Component, public i2c::I2CDevice {
 public:
  void set_switchMode(bool mode);

  // void inputReadAll();
   
  void getInput(uint8_t number);

  void setAllOutput(bool state);

  void setOutput(uint8_t number, bool state);

 protected:
  void write1Byte(uint8_t register_address, uint8_t data);
  uint8_t read1Byte(uint8_t register_address);

  void dump_config() override;

  void Init(bool mode);

  void setup() override;
};

}  // namespace M5Stack_4in8out
}  // namespace esphome
