#include "BinaryInt.h"

// Internal representation stores bits so that coefficient of 2^i is at index i.

/**
 *   Initializes BinInt[] so that the elements correspond to the binary
 *   representation of the low 32 bits of integer Src.
 * 
 *   Pre:   BinInt[] is of dimension 32
 *   Post:  For i = 0 to 31, BinInt[i] == 2^i bit of Src
 */
void BI_Create(uint8_t BinInt[], int64_t Src) {
   
   int32_t Mask = 0x01;
   for (int pos = 0; pos < NUM_BITS; pos++) {
      BinInt[pos] = ( Src & Mask) ? 1 : 0;
      Mask = Mask << 1;
   }
}

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
		const uint8_t Right[], enum DataRep DR) 
{

   return false;
}

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
		const uint8_t Right[], enum DataRep DR) 
{

   return false;
}

/**
 *   Computes negation of 2's complement representation of integer value.
 * 
 *   Pre:   Neg[] and Right[] are of dimension 32
 *          Right[] stores a 2's complement representation
 *   Post:  Neg[] = -Right[]
 *   Ret:   false if negation cannot be correctly represented; 
 *          true otherwise
 */
bool BI_Neg(uint8_t Neg[], const uint8_t Right[]) {

   return false;
}

/**
 *   Converts a BinInt[] to its decimal representation.
 * 
 *   Pre:   Num[] is of dimension 32
 *          Num[] stores a 2's complement or unsigned representation
 *          DR matches the representation of Num[]
 *   Ret:   The decimal value.
 */
int64_t BI_ToDecimal(uint8_t Num[], enum DataRep DR)
{
    int64_t Result = 0;

    // Loop through all 32 bits
    for (int i = 0; i < NUM_BITS; i++) {
        // If the bit is a "1", we will count this (if it's 0 it doesn't matter)
        if (Num[i]) {
            // Sum
            Result += (1ULL << i); // same as doing 2^i
        }
    }

    // Convert if signed
    if (DR == SIGNED) {
        if (Result & (1ULL << 31)) {
            // Negative
            Result += (1ULL << 32) - 1;
        }
    }

    return Result;
}


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
void BI_fprintf(FILE* fp, const uint8_t BinInt[], char* prefix, char* suffix) {
   
   if ( prefix != NULL)
      fprintf(fp, prefix);
      
   for (int pos = NUM_BITS - 1; pos >= 0; pos--) {
       if ( pos < NUM_BITS - 1 && pos % 4 == 3 )
          fprintf(fp, " ");
     
      fprintf(fp, "%"PRIu8, BinInt[pos]);
   }
   
   if ( suffix != NULL)
      fprintf(fp, suffix);
}

// TEST MAIN
int main(void) {
    uint8_t A[NUM_BITS];
    int64_t src = 127;

    BI_Create(A, src);

    int64_t val = BI_ToDecimal(A, SIGNED);
    BI_fprintf(stdout, A, "Binary Num: ", "\n");
    printf("%lld\n", val);

    return 0;
}

/*
int main(void) {
    FILE *fp = fopen("input.txt", "r");
    if (!fp) {
        printf("Error: could not open input.txt\n");
        return 1;
    }

    FILE *out = fopen("output.txt", "w");
    if (!out) {
        printf("Error: could not open output.txt\n");
        fclose(fp);
        return 1;
    }

    char line[256];
    uint8_t A[NUM_BITS], B[NUM_BITS], R[NUM_BITS];
    bool ok;

    while (fgets(line, sizeof(line), fp)) {
        int64_t srcA = 0, srcB = 0;
        char opStr[16], repStr[16];

        if (sscanf(line, "A = %" SCNd64 " B = %" SCNd64 " OP = %15s REP = %15s",
                   &srcA, &srcB, opStr, repStr) != 4) {
            fprintf(out, "Skipping invalid line: %s", line);
            continue;
        }

        enum DataRep rep = (strcmp(repStr, "UNSIGNED") == 0) ? UNSIGNED : SIGNED;

        BI_Create(A, srcA);
        BI_Create(B, srcB);

        if (strcmp(opStr, "ADD") == 0) {
            ok = BI_Add(R, A, B, rep);
            fprintf(out, "Operation: ADD (%s)\n", rep == SIGNED ? "SIGNED" : "UNSIGNED");
            BI_fprintf(stdout, A, "A = ", "\n");
            BI_fprintf(stdout, B, "B = ", "\n");
            BI_fprintf(stdout, R, "Result = ", "\n");
            fprintf(out, "Decimal: %" PRId64 "\n", BI_ToDecimal(R, rep));
        }
        else if (strcmp(opStr, "SUB") == 0) {
            ok = BI_Sub(R, A, B, rep);
            fprintf(out, "Operation: SUB (%s)\n", rep == SIGNED ? "SIGNED" : "UNSIGNED");
            BI_fprintf(stdout, A, "A = ", "\n");
            BI_fprintf(stdout, B, "B = ", "\n");
            BI_fprintf(stdout, R, "Diff = ", "\n");
            fprintf(out, "Decimal: %" PRId64 "\n", BI_ToDecimal(R, rep));
        }
        else if (strcmp(opStr, "NEG") == 0) {
            ok = BI_Neg(R, A);
            fprintf(out, "Operation: NEG (%s)\n", rep == SIGNED ? "SIGNED" : "UNSIGNED");
            BI_fprintf(stdout, A, "A = ", "\n");
            BI_fprintf(stdout, R, "-A = ", "\n");
            fprintf(out, "Decimal: %" PRId64 "\n", BI_ToDecimal(R, rep));
        }
        else {
            printf("Unknown operation: %s\n", opStr);
        }

        fprintf(out, "------------------------------------------------\n");
    }

    fclose(fp);
    fclose(out);
    return 0;
}
*/