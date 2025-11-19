#ifndef BIG_INT_H
#define BIG_INT_H
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <string.h>

#define NUM_BITS 32

enum DataRep {SIGNED, UNSIGNED};

/**
 *   Initializes BinInt[] so that the elements correspond to the binary
 *   representation of the low 32 bits of integer Src.
 * 
 *   Pre:   BinInt[] is of dimension 32
 *   Post:  For i = 0 to 31, BinInt[i] == 2^i bit of Src
 */
void BI_Create(uint8_t BinInt[], int64_t Src);

/**
 *   Computes sum of the signed/unsigned integer values.
 * 
 *   Pre:   Sum[], Left[] and Right[] are of dimension 32
 *          Left[] and Right[] store 2's complement or unsigned representations
 *          DR matches the representation of both Left[] and Right[]
 *   Post:  Sum[] == Left[] + Right[], if possible
 *   Ret:   false if overflow occurs when computing sum of Left[] and Right[];
 *          true otherwise
 */
bool BI_Add(uint8_t Sum[], const uint8_t Left[], 
		const uint8_t Right[], enum DataRep DR); 

/**
 *   Computes difference of the signed/unsigned integer values.
 * 
 *   Pre:   Diff[], Left[] and Right[] are of dimension 32
 *          Left[] and Right[] store 2's complement or unsigned representations
 *          DR matches the representation of both Left[] and Right[]
 *   Post:  Diff[] == Left[] - Right[], if possible
 *   Ret:   false if overflow occurs when computing difference of Left[]
 *          and Right[]; true otherwise 
 */
bool BI_Sub(uint8_t Diff[], const uint8_t Left[], 
		const uint8_t Right[], enum DataRep DR);

/**
 *   Computes negation of 2's complement representation of integer value.
 * 
 *   Pre:   Neg[] and Right[] are of dimension 32
 *          Right[] stores a 2's complement representation
 *   Post:  Neg[] = -Right[]
 *   Ret:   false if negation cannot be correctly represented; 
 *          true otherwise
 */
bool BI_Neg(uint8_t Sum[], const uint8_t Right[]); 

/**
 *   Converts a BinInt[] to its decimal representation.
 * 
 *   Pre:   Num[] is of dimension 32
 *          Num[] stores a 2's complement or unsigned representation
 *          DR matches the representation of Num[]
 *   Ret:   The decimal value.
 */
int64_t BI_ToDecimal(uint8_t Num[], enum DataRep DR);


/**
 *   Prints the binary representation, with formatting.
 * 
 *   Pre:   fp is open on an output stream
 *          BinInt[] is of dimension 32 and stores a 2's complement
 *          or unsigned representation
 *          prefix and suffix are each NULL or point to a C-string
 *   Post:  the bits represented in BinInt[] have been written, preceded by
 *          prefix (if not NULL) and followed by suffix (if not NULL)
 */
void BI_fprintf(FILE* fp, const uint8_t BinInt[], char* prefix, char* suffix);

#endif
