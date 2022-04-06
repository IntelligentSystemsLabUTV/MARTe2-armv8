/**
 * @file Shift.h
 * @brief Header file for class Shift
 * @date 19/10/2015
 * @author Giuseppe Ferrò
 *
 * @copyright Copyright 2015 F4E | European Joint Undertaking for ITER and
 * the Development of Fusion Energy ('Fusion for Energy').
 * Licensed under the EUPL, Version 1.1 or - as soon they will be approved
 * by the European Commission - subsequent versions of the EUPL (the "Licence")
 * You may not use this work except in compliance with the Licence.
 * You may obtain a copy of the Licence at: http://ec.europa.eu/idabc/eupl
 *
 * @warning Unless required by applicable law or agreed to in writing, 
 * software distributed under the Licence is distributed on an "AS IS"
 * basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
 * or implied. See the Licence permissions and limitations under the Licence.

 * @details This header file contains the declaration of the class Shift
 * with all of its public, protected and private members. It may also include
 * definitions for inline methods which need to be visible to the compiler.
 */

#ifndef L0TYPES_SHIFT_H_
#define L0TYPES_SHIFT_H_

/*---------------------------------------------------------------------------*/
/*                        Standard header includes                           */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                        Project header includes                            */
/*---------------------------------------------------------------------------*/

#include "GeneralDefinitions.h"
#include "DoubleInteger.h"

/*---------------------------------------------------------------------------*/
/*                           Class declaration                               */
/*---------------------------------------------------------------------------*/

namespace MARTe {

/**
 * @brief A collector of functions that implements logical and mathematical shift in safe mode.
 * @details These methods implements shift operations in the right way, returning zero when the shift is
 * greater than the size of the number. Furthermore they implements the logical shift which
 * does not extend the sign for negative numbers and it is very useful in many functionalities.
 */
class Shift {

public:

    /**
     * @brief Implementation of a template function for safe logical right shifts.
     * @tparam T is the integer type of the number parameter.
     * @param[in] number is the number to be shifted.
     * @param[in] shift is the number of bits shifted.
     * @return the number shifted.
     */
    template<typename T>
    static inline T LogicalRightSafeShift(T number,
                                          uint8 shift);

    /**
     * @brief Implementation of a template function for safe logical shifts.
     * @tparam T is the integer type of the number parameter.
     * @param[in] number is the number to be shifted.
     * @param[in] shift is the number of bits shifted.
     * @return the number shifted.
     */
    template<typename T>
    static inline T LogicalLeftSafeShift(T number,
                                         uint8 shift);

    /**
     * @brief Implementation of a template function for safe mathematical right shifts.
     * @tparam T is the integer type of the number parameter.
     * @param[in] number is the number to be shifted.
     * @param[in] shift is the number of bits shifted.
     * @return the number shifted.
     */
    template<typename T>
    static inline T MathematicRightSafeShift(T number,
                                             uint8 shift);

    /**
     * @brief Implementation of a template function for safe mathematical left shifts.
     * @tparam T is the integer type of the number parameter.
     * @param[in] number is the number to be shifted.
     * @param[in] shift is the number of bits shifted.
     * @return the number shifted.
     */
    template<typename T>
    static inline T MathematicLeftSafeShift(T number,
                                            uint8 shift);

private:

    /**
     * @brief Logical right shift for uint8 numbers.
     * @param[in] number is the number to shift.
     * @param[in] shift is the number of bits shifted.
     * @return the number right shifted.
     */
    static inline uint8 LogicalRightShift(uint8 number,
                                          uint8 shift);

    /**
     * @brief Logical right shift for uint16 numbers.
     * @param[in] number is the number to shift.
     * @param[in] shift is the number of bits shifted.
     * @return the number right shifted.
     */
    static inline uint16 LogicalRightShift(uint16 number,
                                           uint8 shift);

    /**
     * @brief Logical right shift for uint32 numbers.
     * @param[in] Number is the number to shift.
     * @param[in] shift is the number of bits shifted.
     * @return the number right shifted.
     */
    static inline uint32 LogicalRightShift(uint32 number,
                                           uint8 shift);

    /**
     * @brief Logical right shift for uint64 numbers.
     * @param[in] number is the number to shift.
     * @param[in] shift is the shift in bits.
     * @return the number right shifted.
     */
    static inline uint64 LogicalRightShift(uint64 number,
                                           uint8 shift);

    /**
     * @brief logical right shift for int8 numbers.
     * @param[in] number is the number to shift.
     * @param[in] shift is the number of bits shifted.
     * @return the number right shifted.
     */
    static inline int8 LogicalRightShift(int8 number,
                                         uint8 shift);

    /**
     * @brief Logical right shift for int16 numbers.
     * @param[in] number is the number to shift.
     * @param[in] shift is the number of bits shifted.
     * @return the number right shifted.
     */
    static inline int16 LogicalRightShift(int16 number,
                                          uint8 shift);

    /**
     * @brief Logical right shift for int32 numbers.
     * @param[in] number is the number to shift.
     * @param[in] shift is the number of bits shifted.
     * @return the number right shifted.
     */
    static inline int32 LogicalRightShift(int32 number,
                                          uint8 shift);

    /**
     * @brief Logical right shift for int64 numbers.
     * @param[in] number is the number to shift.
     * @param[in] shift is the number of bits shifted.
     * @return the number right shifted.
     */
    static inline int64 LogicalRightShift(int64 number,
                                          uint8 shift);

    /**
     * @brief Logical right shift for DoubleInteger.
     * @tparam T2 is the integer type needed for building the DoubleInteger type of the number parameter.
     * @param[in] number is the number to shift.
     * @param[in] shift is the number of bits shifted.
     * @return the number right shifted.
     */
    template<typename T2>
    static inline DoubleInteger<T2> LogicalRightShift(DoubleInteger<T2> number,
                                                      uint8 shift);
};

/*---------------------------------------------------------------------------*/
/*                        Inline method definitions                          */
/*---------------------------------------------------------------------------*/
template<typename T>
T Shift::LogicalRightSafeShift(T number,
                               uint8 shift) {

    uint8 bound = static_cast<uint8>(sizeof(T) * 8u);

    //if is greater than the size of the number return 0.
    if (shift >= bound) {
        return (T) 0;
    }

    return LogicalRightShift(number, shift);
}

template<typename T>
T Shift::LogicalLeftSafeShift(T number,
                              uint8 shift) {

    uint8 bound = sizeof(T) * 8u;

    //if is greater than the size of the number return 0.
    if (shift >= bound) {
        return (T) 0;
    }

    return number << shift;
}

template<typename T>
T Shift::MathematicRightSafeShift(T number,
                                  uint8 shift) {

    int bound = sizeof(T) * 8;

    //if is greater than the number size return 0.
    if (shift >= bound) {
        return (T) 0;
    }
    return number >> shift;
}

template<typename T>
T Shift::MathematicLeftSafeShift(T number,
                                 uint8 shift) {

    int bound = sizeof(T) * 8;

    //if is greater than the number size return 0.
    if (shift >= bound) {
        return (T) 0;
    }
    return number << shift;
}

uint8 Shift::LogicalRightShift(uint8 number,
                               uint8 shift) {
    return number >> shift;
}

uint16 Shift::LogicalRightShift(uint16 number,
                                uint8 shift) {
    return number >> shift;
}

uint32 Shift::LogicalRightShift(uint32 number,
                                uint8 shift) {
    return number >> shift;
}

uint64 Shift::LogicalRightShift(uint64 number,
                                uint8 shift) {
    return number >> shift;
}

int8 Shift::LogicalRightShift(int8 number,
                              uint8 shift) {
    return ((uint8) number) >> shift;
}

int16 Shift::LogicalRightShift(int16 number,
                               uint8 shift) {
    return ((uint16) number) >> shift;
}

int32 Shift::LogicalRightShift(int32 number,
                               uint8 shift) {
    return ((uint32) number) >> shift;
}

int64 Shift::LogicalRightShift(int64 number,
                               uint8 shift) {
    return ((uint64) number) >> shift;
}

template<typename T2>
DoubleInteger<T2> Shift::LogicalRightShift(DoubleInteger<T2> number,
                                           uint8 shift) {

    if (static_cast<T2>(-1) < 0) {

        // shift of sizeof(T)*8 is treated as shift 0
        // for this reason exit here to avoid this pitfall
        if (shift > 0u) {
            T2 lower = number.GetLower();
            T2 upper = number.GetUpper();

            // calculates n of bits of T
            uint16 bitSize = static_cast<uint16>(sizeof(T2) * 8u);
            // shift within one half
            if (shift < bitSize) {
                // shift lower first
                lower = lower >> shift;
                // add overflow from upper
                // this would fail if shift is 0
                lower |= (upper << (bitSize - shift));
                // complete the upper
                upper = upper >> shift;
            }
            else { // more than half!
                   // remove half
                shift -= bitSize;
                // swap upper -> lower and shift with the remainder
                lower = upper >> shift;
                // upper is 0
                if (upper < static_cast<T2>(0)) {
                    upper = static_cast<T2>(-1);
                }
                else {
                    upper = static_cast<T2>(0);
                }
            }
            number.SetLower(lower);
            number.SetUpper(upper);
        }
    }
    else {
        number >>= shift;
    }
    return number;
}
}

#endif /* L0TYPES_SHIFT_H_ */

