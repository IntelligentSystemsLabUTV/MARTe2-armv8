/**
 * @file BitSetToInteger.h
 * @brief Header file for class BitSetToInteger
 * @date 05/10/2015
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

 * @details This header file contains the declaration of the class BitSetToInteger
 * with all of its public, protected and private members. It may also include
 * definitions for inline methods which need to be visible to the compiler.
 */

#if !defined BITSET_TO_INTEGER
#define BITSET_TO_INTEGER

/*---------------------------------------------------------------------------*/
/*                        Standard header includes                           */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                        Project header includes                            */
/*---------------------------------------------------------------------------*/

#include "GeneralDefinitions.h"
#include "FormatDescriptor.h"
#include "IOBuffer.h"
#include "Shift.h"
#include "DoubleInteger.h"

/*---------------------------------------------------------------------------*/
/*                           Class declaration                               */
/*---------------------------------------------------------------------------*/

namespace MARTe {

/**
 * @Brief BitSet to BitSet function for private use only.
 * @tparam T is the integer type of the destination and source parameters.
 * @param[in, out] destination is a pointer to the bitSet destination.
 * @param[in] destinationBitShift is the desired shift in bit in destination variable.
 * @param[in] destinationBitSize is the desired size in bit for the number to copy in destination.
 * @param[in] destinationIsSigned specifies if the number in destination will be considered signed (true) or not (false).
 * @param[in] source is a pointer to the bitSet source.
 * @param[in] sourceBitShift defines the shift from which extract the number.
 * @param[in] sourceBitSize is the desired size in bit for the number to extract from source.
 * @param[in] sourceIsSigned specifies if the number to extract from source will be considered signed (true) or not (false).
 *
 * Source negative (then signed) and destination unsigned leads that zero is copied (saturation).
 * Source negative and destination signed with a greater dimension leads that will be copied the number with the sign extension.
 * If source is negative and destination is signed with a minor dimension, the function checks if source is minor than the minimum
 * supported by the destination dimension and in positive case copy the minimum possible (1000...).
 * If source is positive and destination is signed the function operates a saturation observing the destination size (-1 in case of
 * destination signed).
 */
template<typename T>
static inline void BSToBS(T * const & destination,
                          const uint8 & destinationBitShift,
                          const uint8 destinationBitSize,
                          const bool destinationIsSigned,
                          T * const & source,
                          const uint8 sourceBitShift,
                          const uint8 sourceBitSize,
                          const bool sourceIsSigned);

/**
 * @Brief BitSet to BitSet function for copy a bit range from a source to a destination.
 * @tparam T is the integer type of the destination and source parameters.
 * @param[in, out] destination is a pointer to the bitSet destination.
 * @param[in, out] destinationBitShift is the desired shift in bit in destination variable.
 * @param[in] destinationBitSize is the desired size in bit for the number to copy in destination.
 * @param[in] destinationIsSigned specifies is the number in destination will be considered signed (true) or not (false).
 * @param[in, out] source is a pointer to the bitSet source.
 * @param[in, out] sourceBitShift defines the shift from which extract the number.
 * @param[in] sourceBitSize is the desired size in bit for the number to extract from source.
 * @param[in] sourceIsSigned specifies if the number to extract from source will be considered signed (true) or not (false).
 *
 * Converts an integer of bitSize sourceBitSize located at address source and bitAddress sourceBitShift
 * into an integer of bitSize destinationBitSize located at address destination and bitAddress destinationBitShift
 * destination and source must be of the same type T.
 * T must be unsigned int of byte size power of 2 (8,16,32,64,128...) not 24 48 etc...
 * T determines the minimum number size used for the operations.
 * T=uint8 means that any number may be used.
 *
 * @return True if the bit copy from source to destination is done. False if the bit copy from source to destination can not be done.
 */
template<typename T>
static inline bool BitSetToBitSet(T *& destination,
                                  uint8 & destinationBitShift,
                                  const uint8 destinationBitSize,
                                  const bool destinationIsSigned,
                                  T *& source,
                                  uint8 & sourceBitShift,
                                  const uint8 sourceBitSize,
                                  const bool sourceIsSigned);

/**
 * @Brief BitSet to Integer function.
 * @tparam T is the integer type of the source parameter.
 * @tparam T2 is the integer type of the dest parameter.
 * @param[in, out] dest is the location for the copy of the desired bit range.
 * @param[in, out] source is a pointer to the bitSet source.
 * @param[in, out] sourceBitShift defines the shift from which extract the number.
 * @param[in] sourceBitSize is the desired size in bit for the number to extract from source.
 * @param[in] sourceIsSigned specifies if the number to extract from source will be considered signed (true) or not (false).
 *
 * Converts an integer of bitSize sourceBitSize located at address source and bitAddress sourceBitShift
 * into an integer of type T2.
 * T must be unsigned int of byte size power of 2 (8,16,32,64,128...) not 24 48 etc...
 * T determines the minimum number size used for the operations.
 * T=uint8 means that any number may be used.
 * @return True if BitSetToBitSet returns true.
 */
template<typename T, typename T2>
static inline bool BitSetToInteger(T2 & dest,
                                   T *& source,
                                   uint8 & sourceBitShift,
                                   const uint8 sourceBitSize,
                                   const bool sourceIsSigned);

/**
 * @Brief Integer to BitSet function.
 * @tparam T is the integer type of the destination parameter.
 * @tparam T2 is the integer type of the src parameter.
 * @param[in, out] destination is a pointer to the bitSet destination.
 * @param[in, out] destinationBitShift is the desired shift in bit in destination variable.
 * @param[in] destinationBitSize is the desired size in bit for the number to copy in destination.
 * @param[in] destinationIsSigned specifies is the number in destination will be considered signed (true) or not (false).
 * @param[in, out] source is the integer to copy.
 *
 * Converts an integer of type T2 into an integer of bitSize destinationBitSize
 * located at address destination and bitAddress destinationBitShift.
 * T must be unsigned int of byte size power of 2 (8,16,32,64,128...) not 24 48 etc...
 * T determines the minimum number size used for the operations.
 * T = uint8 means that any number may be used.
 *
 * @return True if BitSetToBitSet returns true.
 */
template<typename T, typename T2>
static inline bool IntegerToBitSet(T *& destination,
                                   uint8 & destinationBitShift,
                                   const uint8 destinationBitSize,
                                   const bool destinationIsSigned,
                                   T2 & src);
}

/*---------------------------------------------------------------------------*/
/*                        Inline method definitions                          */
/*---------------------------------------------------------------------------*/

namespace MARTe {
/*lint -save -e774 -e740 -e826 -e927 -e928 -e669
 * 774 [MISRA C++ Rule 0-1-1] [MISRA C++ Rule 0-1-2] [MISRA C++ Rule 0-1-9]. Justification: Return value depends on template type.
 * 740, 826, 927, 928 [MISRA C++ Rule 5-2-6], [MISRA C++ Rule 5-2-7]. Justification: Pointer to Pointer cast required by this implementation.
 * 669 . Justification: BSToBS(*) should be used only truth BitSetToBitSet(*). The BitSetToBitSet(*) function controls the template type assuring
 * that it has enough size such that the memory copy will be done without overrun.
 * */

template<typename T>
static inline void BSToBS(T * const & destination,
                          const uint8 & destinationBitShift,
                          const uint8 destinationBitSize,
                          const bool destinationIsSigned,
                          T * const & source,
                          const uint8 sourceBitShift,
                          const uint8 sourceBitSize,
                          const bool sourceIsSigned) {
    // how many bits in T
    uint8 dataSize = static_cast<uint8>(sizeof(T) * 8u);

    // calculate mask covering range of input bits (starting from bit 0)
    T sourceMask = static_cast<T>(0);
    // all FFFFF....
    sourceMask = ~sourceMask;
    // shift FFFF.. to cover just the number bit size
    sourceMask = Shift::LogicalRightSafeShift(sourceMask, (dataSize - sourceBitSize));

    // calculate mask covering range of output bits (starting from bit 0)
    T destinationMask = static_cast<T>(0);
    destinationMask = ~destinationMask;
    destinationMask = Shift::LogicalRightSafeShift(destinationMask, (dataSize - destinationBitSize));

    // mask pinpointing sign bit (starting from bit 0)
    T sourceSignMask = static_cast<T>(1);
    sourceSignMask = Shift::LogicalLeftSafeShift(sourceSignMask, (sourceBitSize - 1u));

    // mask pinpointing sign bit (starting from bit 0)
    T destinationSignMask = static_cast<T>(1);
    destinationSignMask = Shift::LogicalLeftSafeShift(destinationSignMask, (destinationBitSize - 1u));

    // here we put the number while processing it
    T sourceCopy = static_cast<T>(0);
    uint32 sourceByteSize = ((static_cast<uint32>(sourceBitSize) + static_cast<uint32>(sourceBitShift)) + 7u) / 8u;


    // copy
    if (!MemoryOperationsHelper::Copy(&sourceCopy, source, sourceByteSize)) {
        REPORT_ERROR_STATIC_0(ErrorManagement::FatalError, "BSToBS: Failed MemoryOperationsHelper::Copy()");
    }


    // shift number so LSB at bit 0
    // removes lower bits
    sourceCopy = Shift::LogicalRightSafeShift(sourceCopy, sourceBitShift);
    // mask out upper bits
    sourceCopy &= sourceMask;

    // extract sign bit
    T signBit = (sourceCopy & sourceSignMask);

    // is negative if it has sign and last bit is 1
    bool sourceIsSignBit = (signBit != static_cast<T>(0));
    bool sourceIsNegative = ((sourceIsSigned) && (sourceIsSignBit));

    // this means both: has sign and the last bit is 1
    if (sourceIsNegative) {
        // if destination is not signed saturates to 0
        if (!destinationIsSigned) {
            // saturate to 0
            sourceCopy = static_cast<T>(0);
        }
        else {
            // if I need to squeeze a larger number into a smaller
            if (sourceBitSize > destinationBitSize) {
                // create a mask of bits covering the bits where source exceeds destination
                // the mask contains sourceBitSize-destinationBitSize+1 ones, and
                // if all of these bits are ones in the source the number can be written in the destination.
                // ex. 1101 in 3 bits can be written (mask=1100), 1001 not.
                T mask = sourceMask - (Shift::LogicalRightSafeShift(destinationMask, 1u));

                // if any of these bits is not 1 then we have a larger negative number
                if ((sourceCopy & mask) != mask) {
                    // 0x8000.. is the maximum negative
                    sourceCopy = destinationSignMask;
                }
            }
            else { // smaller to larger sign extension needed
                   // maks has all the bits that will be added
                T mask = destinationMask - sourceMask;
                // it already had a sign bit, now we extend it to the full destination size
                sourceCopy |= mask;

            }
        }
    }
    else {
        // 0xFFF.. is the max value for unsigned
        T maxPositiveValue = destinationMask;
        if (destinationIsSigned) {
            // 0x7FF.. is the max value for signed
            maxPositiveValue = Shift::LogicalRightSafeShift(destinationMask, 1u);
        }
        // saturate to max
        if (sourceCopy > maxPositiveValue) {
            sourceCopy = maxPositiveValue;
        }
    }

    // move the bits into output position
    sourceCopy = Shift::LogicalLeftSafeShift(sourceCopy, destinationBitShift);
    // shift mask as well
    destinationMask = Shift::LogicalLeftSafeShift(destinationMask, destinationBitShift);
    // complementary mask- to erase all bits in destination range
    destinationMask = ~destinationMask;

    // use destinationMask to hold the current value at destination after masking
    T destinationCopy=static_cast<T>(0);
    // copy only the correct size
    uint32 destinationByteSize = ((static_cast<uint32>(destinationBitSize) + static_cast<uint32>(destinationBitShift)) + 7u) / 8u;


    // copy
    if (!MemoryOperationsHelper::Copy(&destinationCopy, destination, destinationByteSize)) {
        REPORT_ERROR_STATIC_0(ErrorManagement::FatalError, "BSToBS: Failed MemoryOperationsHelper::Copy()");
    }
    destinationMask &= destinationCopy;

    // merge into sourceCopy
    sourceCopy |= destinationMask;

    if (!MemoryOperationsHelper::Copy(destination, &sourceCopy, destinationByteSize)) {
        REPORT_ERROR_STATIC_0(ErrorManagement::FatalError, "BSToBS: Failed MemoryOperationsHelper::Copy()");
    }

}

template<typename T>
static inline bool BitSetToBitSet(T *& destination,
                                  uint8 & destinationBitShift,
                                  const uint8 destinationBitSize,
                                  const bool destinationIsSigned,
                                  T *& source,
                                  uint8 & sourceBitShift,
                                  const uint8 sourceBitSize,
                                  const bool sourceIsSigned) {

    bool ret = true;
    // calculates granularity as bits
    uint8 granularity = static_cast<uint8>(sizeof(T) * 8u);
    // mask to eliminate multiples of granularity -
    // granularity must be a power of 2
    uint8 granularityMask = granularity - 1u;
    // exponent of the power of 2 that is granularity (log2 of the number of bits in T)
    uint8 granularityShift = 3u;
    uint8 temp = static_cast<uint8>(sizeof(T));
    /*lint -e{681} .Justification: Entering or not in the loop depends by the template type size */
    while (temp > 1u) {
        granularityShift++;
        temp = Shift::LogicalRightSafeShift(temp, 1u);
    }

    // normalize sourceBitShift so that  0<sourceBitShift<granularity
    // adjusts source pointer adding sourceBitShift/numberOfBits.
    if (sourceBitShift >= granularity) {
        // index=sourceBitShift/numberOfBits
        uint8 index = Shift::LogicalRightSafeShift(sourceBitShift, granularityShift);
        source = &source[index];
        // sourceBitShift=sourceBitShift % numberOfBits
        sourceBitShift &= granularityMask;
    }
    // normalize destinationBitShift so that  0<destinationBitShift<granularity
    // adjusts destination pointer
    if (destinationBitShift >= granularity) {
        uint8 index = Shift::LogicalRightSafeShift(destinationBitShift, granularityShift);
        destination = &destination[index];
        destinationBitShift &= granularityMask;
    }

    // work out range of bits involved
    // for source
    uint8 sourceBitEnd = sourceBitShift + sourceBitSize;
    // and for destination
    uint8 destinationBitEnd = destinationBitShift + destinationBitSize;

    // check number able to accommodate in full both input and output numbers
    // and is big than granularity
    if ((sourceBitEnd <= 8u) && (destinationBitEnd <= 8u) && (granularity == 8u)) {
        // if 8 is fine then operate with 8 bit integers
        uint8 *destination8 = reinterpret_cast<uint8 *>(destination);
        uint8 *source8 = reinterpret_cast<uint8 *>(source);

        BSToBS(destination8, destinationBitShift, destinationBitSize, destinationIsSigned, source8, sourceBitShift, sourceBitSize, sourceIsSigned);

    }
    else if ((sourceBitEnd <= 16u) && (destinationBitEnd <= 16u) && (granularity <= 16u)) {
        // if 16 is fine then operate with 16 bit integers
        uint16 *destination16 = reinterpret_cast<uint16 *>(destination);
        uint16 *source16 = reinterpret_cast<uint16 *>(source);

        BSToBS(destination16, destinationBitShift, destinationBitSize, destinationIsSigned, source16, sourceBitShift, sourceBitSize, sourceIsSigned);

    }
    else if ((sourceBitEnd <= 32u) && (destinationBitEnd <= 32u) && (granularity <= 32u)) {
        // if 32 is fine then operate with 32 bit integers
        uint32 *destination32 = reinterpret_cast<uint32 *>(destination);
        uint32 *source32 = reinterpret_cast<uint32 *>(source);

        BSToBS(destination32, destinationBitShift, destinationBitSize, destinationIsSigned, source32, sourceBitShift, sourceBitSize, sourceIsSigned);

    }
    else if ((sourceBitEnd <= 64u) && (destinationBitEnd <= 64u) && (granularity <= 64u)) {
        // if 64 is fine then operate with 64 bit integers
        uint64 *destination64 = reinterpret_cast<uint64 *>(destination);
        uint64 *source64 = reinterpret_cast<uint64 *>(source);

        BSToBS(destination64, destinationBitShift, destinationBitSize, destinationIsSigned, source64, sourceBitShift, sourceBitSize, sourceIsSigned);

    }

    else if ((sourceBitEnd <= 128u) && (destinationBitEnd <= 128u) && (granularity <= 128u)) {
        // if 128 is fine then operate with float64(uint64)
        DoubleInteger<uint64> *destination128 = reinterpret_cast<DoubleInteger<uint64> *>(destination);
        DoubleInteger<uint64> *source128 = reinterpret_cast<DoubleInteger<uint64> *>(source);

        BSToBS(destination128, destinationBitShift, destinationBitSize, destinationIsSigned, source128, sourceBitShift, sourceBitSize, sourceIsSigned);
    }

    else {
        ret = false;
    }

    sourceBitShift += sourceBitSize;
    destinationBitShift += destinationBitSize;

    return ret;
}

template<typename T, typename T2>
static inline bool BitSetToInteger(T2 & dest,
                                   T *& source,
                                   uint8 & sourceBitShift,
                                   const uint8 sourceBitSize,
                                   const bool sourceIsSigned) {

    // converts T2 into destination,destinationBitShift,destinationBitSize,destinationIsSigned
    T *destination = reinterpret_cast<T*>(&dest);
    uint8 destinationBitShift = 0u;
    uint8 destinationBitSize = static_cast<uint8>(sizeof(T2) * 8u);
    // detect if T2 has sign by seing if we can initialise a number negative
    bool destinationIsSigned = ((static_cast<T2>(-1)) < static_cast<T2>(0));

    return BitSetToBitSet(destination, destinationBitShift, destinationBitSize, destinationIsSigned, source, sourceBitShift, sourceBitSize, sourceIsSigned);
}

template<typename T, typename T2>
static inline bool IntegerToBitSet(T *& destination,
                                   uint8 & destinationBitShift,
                                   const uint8 destinationBitSize,
                                   const bool destinationIsSigned,
                                   T2 & src) {

    // converts T2 into source,sourceBitShift,sourceBitSize,sourceIsSigned
    T *source = reinterpret_cast<T*>(&src);
    uint8 sourceBitShift = 0u;
    uint8 sourceBitSize = static_cast<uint8>(sizeof(T2) * 8u);
    // detect if T2 has sign by seeing if we can initialise a number negative
    bool sourceIsSigned = ((static_cast<T2>(-1)) < static_cast<T2>(0));

    return BitSetToBitSet(destination, destinationBitShift, destinationBitSize, destinationIsSigned, source, sourceBitShift, sourceBitSize, sourceIsSigned);
}

}

#endif
