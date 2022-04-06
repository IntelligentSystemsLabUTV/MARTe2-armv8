/**
 * @file Token.cpp
 * @brief Source file for class Token
 * @date 25/11/2015
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

 * @details This source file contains the definition of all the methods for
 * the class Token (public, protected, and private). Be aware that some 
 * methods, such as those inline could be defined on the header file, instead.
 */

#define DLL_API

/*---------------------------------------------------------------------------*/
/*                         Standard header includes                          */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                         Project header includes                           */
/*---------------------------------------------------------------------------*/
#define DLL_API
#include "Token.h"
/*---------------------------------------------------------------------------*/
/*                           Static definitions                              */
/*---------------------------------------------------------------------------*/
namespace MARTe {

/*---------------------------------------------------------------------------*/
/*                           Method definitions                              */
/*---------------------------------------------------------------------------*/

Token::Token() {
    tokenId = 0u;
    tokenLineNumber = 0u;

}

Token::Token(const uint32 id,
             const char8 * const description,
             const char8 * const data,
             const uint32 lineNumber) {
    tokenId = id;
    tokenDescription = description;
    tokenData = data;
    tokenLineNumber = lineNumber;
}

Token::Token(TokenInfo tokenInfo,
             const char8 * const data,
             const uint32 lineNumber) {
    tokenId = tokenInfo.GetTokenId();
    tokenDescription = tokenInfo.GetDescription();
    tokenData = data;
    tokenLineNumber = lineNumber;
}

Token::~Token() {

}

uint32 Token::GetId() const {
    return tokenId;
}

/*lint -e{1529} . Justification: Remove the warning */
Token &Token::operator=(const Token &td) {
    tokenId = td.tokenId;
    tokenData = td.tokenData;
    tokenDescription = td.tokenDescription;
    tokenLineNumber = td.tokenLineNumber;
    return *this;
}

const char8 * Token::GetDescription() {
    return tokenDescription.Buffer();
}

const char8 * Token::GetData() {
    return tokenData.Buffer();
}

uint32 Token::GetLineNumber() const {
    return tokenLineNumber;
}

}

