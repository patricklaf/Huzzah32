/**
 * @file MCP24LC512.h
 * @brief MCP24LC512 class definition.
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
 *
 * @bug Add a delay of 5 milliseconds after a write operation before any other
 * action or write will not be done.
 */
#ifndef MCP24LC512_H_
#define MCP24LC512_H_

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

/**
 * @class MCP24LC512
 * @brief MCP24LC512 class definition.
 *
 * The MCP24LC512 class handles the 24LC512 EEPROM device.
 *
 * Features:
 * - Write.
 * - Read.
 * - Write protection.
 */
class MCP24LC512 {
public:
    /** Default I2C address of the device. */
    static constexpr uint8_t Default = 0x50;
    /** Special value to indicate no pin is defined. @see _wp */
    static constexpr uint8_t None = 0xFF;

    /**
     * @fn  MCP24LC512()
     * @brief Default constructor.
     *
     * Initializes a new instance of the MCP24LC512 class.
     */
    MCP24LC512();

    /**
     * @fn  ~MCP24LC512()
     * @brief Default destructor.
     *
     * Finalizes the instance of the MCP24LC512 class.
     */
    virtual ~MCP24LC512();

    /**
     * @brief Prepare the device for operations.
     *
     * |erzerze|fdfd|
     * |:-:|-:|
     * |dsdfsd|120|
     *
     * ```cpp
     * device.begin();
     * ```
     *
     * @fn bool begin(const uint8_t=Default, const uint8_t=None)
     * Set the device I2C address and WP pin.
     * Set and initializes the MCU I2C bus.
     *
     * @note Internally it calls @ref begin(TwoWire&, const uint8_t, const uint8_t)
     * with wire parameter set to default core *Wire* object.
     *
     * @param address Device I2C address. Default value is @ref Default.
     * @param wp WP pin. Default value is ::None.
     * @return True if successfully initialized, false if an error occurred.
     */
    bool begin(const uint8_t address = Default, const uint8_t wp = None);

    /**
     * @fn bool begin(TwoWire&, const uint8_t=Default, const uint8_t=None)
     * @brief Prepare the device for operations.
     *
     * Set the device I2C address and WP pin.
     * Set and initializes the MCU I2C bus.
     *
     * @param wire MCU I2C bus.
     * @param address Device I2C address. Default value is @ref Default.
     * @param wp WP pin. Default value is ::None.
     * @return True if successfully initialized, false if an error occurred.
     */
    bool begin(TwoWire& wire, const uint8_t address = Default, const uint8_t wp = None);

    /**
     * @fn bool end()
     * @brief End device operations.
     *
     * After a call to end(), no more operations will be performed before a new call
     * to begin().
     *
     * Finalizes the MCU I2C bus.
     *
     * @return True if successfully finalized, false if an error occurred.
     */
    bool end();

    /**
     * @fn bool write(const uint16_t, const uint8_t)
     * @brief Write data to the specified address.
     *
     * The address and the data are transmitted to the device. The device store the
     * byte at the address.
     *
     * @param address Address of data.
     * @param data Byte to store on device.
     * @return True if data is successfully written, false if an error occurred.
     */
    bool write(const uint16_t address, const uint8_t data);

    /**
     * @fn uint8_t read(const uint16_t)
     * @brief Read data from a specified address.
     *
     * The address is transmitted to the device. The device returns the byte stored
     * at the address.
     *
     * @param address Address of data.
     * @return Byte stored on device.
     */
    uint8_t read(const uint16_t address);

    /**
     * @fn void writeProtect(const bool)
     * @brief Enable or disable the write protection of the device.
     *
     * If write protection is enabled, write operation will not fail but data will
     * not be effectively written.
     *
     * @param on If true, write protection is enabled, disabled otherwise.
     */
    void writeProtect(const bool on);

private:
    uint8_t _address;   /**< I2C address of the device. */
    uint8_t _wp;        /**< Pin of the MCU linked to the device WP signal. */
    TwoWire* _wire;     /**< MCU I2C bus used to communicate with the device. */
};

#endif /* MCP24LC512_H_ */
