/**
 * @file MCP24LC512.cpp
 * @brief MCP24LC512 class implementation.
 *
 * The MCP24LC512 class handles the 24LC512 EEPROM device.
 *
 * Features:
 * - Write.
 * - Read.
 * - Write protection.
 *
 * @author Patrick Lafarguette
 * @version 1.0
 * @date 07/12/2023
 * @warning Use at your own risk.
 * @copyright 2023 CNRS - Patrick Lafarguette
 */
#include "MCP24LC512.h"

MCP24LC512::MCP24LC512() {
}

MCP24LC512::~MCP24LC512() {
}

bool MCP24LC512::begin(const uint8_t address, const uint8_t wp) {
    return begin(Wire, address, wp);
}

bool MCP24LC512::begin(TwoWire& wire, const uint8_t address, const uint8_t wp) {
    _wire = &wire;
    _address = address;
    _wp = wp;
    pinMode(_wp, OUTPUT);
    return _wire->begin();
}

bool MCP24LC512::end() {
    return _wire->end();
}

bool MCP24LC512::write(const uint16_t address, const uint8_t data) {
    _wire->beginTransmission(_address);
    _wire->write(address >> 8);
    _wire->write(address);
    _wire->write(data);
    return _wire->endTransmission() == 0;
}

uint8_t MCP24LC512::read(const uint16_t address) {
    _wire->beginTransmission(_address);
    _wire->write(address >> 8);
    _wire->write(address);
    _wire->endTransmission();
    _wire->requestFrom(_address, 1);
    return _wire->read();
}

void MCP24LC512::writeProtect(const bool on) {
    digitalWrite(_wp, on ? HIGH : LOW);
}
