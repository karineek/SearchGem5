// You need to use -I/path/to/AFLplusplus/include -I.
#include "afl-fuzz.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <time.h>

//#define DEBUG_CM 1 // Debug or afl plugin


#ifndef DEBUG_CM
extern AFL_RAND_RETURN rand_next(afl_state_t *afl);
#endif

typedef struct my_mutator {

  afl_state_t *afl;

  char* out_buff; // The whole args in buffers

  char* file_name_types; // The name of the file with types to mutate

  char* input_args; // Keeps the input arguments for mutating

  char* input_digit; // Buffer for register mutations

} my_mutator_t;

#define MAX_CMDLINE_SIZE (250)
#define MAX_FILE_NAME_SIZE (100)
#define MAX_ARGS_SIZE (140)
#define MAX_DATA_SIZE (20)

/**
 * Initialize this custom mutator
 *
 * @param[in] afl a pointer to the internal state object. Can be ignored for
 * now.
 * @param[in] seed A seed for this mutator - the same seed should always mutate
 * in the same way.
 * @return Pointer to the data object this custom mutator instance should use.
 *         There may be multiple instances of this mutator in one afl-fuzz run!
 *         Return NULL on error.
 */
my_mutator_t *afl_custom_init(afl_state_t *afl, unsigned int seed) {

  srand(seed);  // needed also by surgical_havoc_mutate()

  my_mutator_t *data = calloc(1, sizeof(my_mutator_t));
  if (!data) {
    perror("afl_custom_init alloc");
    return NULL;
  }

  if ((data->out_buff = (char *)malloc(MAX_CMDLINE_SIZE)) == NULL) {
    perror("afl_custom_init malloc");
    return NULL;
  }

  if ((data->file_name_types = (char *)malloc(MAX_FILE_NAME_SIZE)) == NULL) {
    perror("afl_custom_init malloc");
    return NULL;
  }

  if ((data->input_args = (char *)malloc(MAX_ARGS_SIZE)) == NULL) {
    perror("afl_custom_init malloc");
    return NULL;
  }

  if ((data->input_digit = (char *)malloc(MAX_DATA_SIZE)) == NULL) {
    perror("afl_custom_init malloc");
    return NULL;
  }

  data->afl = afl;

  return data;

}

// Read the types from file
void readTypes(my_mutator_t *data) {
    // Open the file for reading
    FILE *file = fopen(data->file_name_types, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Read the file line by line
    char buffer[256]; // Adjust the buffer size as needed
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // Print each line (or process it as needed)
        printf("Read line: %s", buffer);
    }

    // Close the file
    fclose(file);
}

// Bit flip integer of 32 bits
void mutateUInt32Value(char *token, my_mutator_t *data, char* format) {
#ifdef DEBUG_CM
    static int rand_next = 0;
    srand(time(NULL)+rand_next); // randomize seed
    rand_next++;
#endif

    unsigned int num;
    if (sscanf(token, "%u", &num) == 1) {
        int bit_pos =
#ifndef DEBUG_CM
		(data->afl) ? rand_below(data->afl, (sizeof(unsigned int) * 8)) :
#endif
			rand() % (sizeof(unsigned int) * 8); // Random location in the register

	num ^= (1u << bit_pos); // Bit flip it
        sprintf(token, format, num); // Copy it back
    }
}

// Bit flip integer of 64 bits
void mutateUInt64Value(char *token, my_mutator_t *data, char* format) {
#ifdef DEBUG_CM
    static int rand_next = 0;
    srand(time(NULL)+rand_next); // randomize seed
    rand_next++;
#endif

    unsigned long num;
    if (sscanf(token, "%lu", &num) == 1) {
        int bit_pos =
#ifndef DEBUG_CM
                (data->afl) ? rand_below(data->afl, (sizeof(unsigned long) * 8)) :
#endif
                        rand() % (sizeof(unsigned long) * 8); // Random location in the register

        num ^= (1ul << bit_pos); // Bit flip it
        sprintf(token, format, num); // Copy it back
    }
}

// Prepare data before mutating
void initCurrentMutationData(uint8_t *new_buf, my_mutator_t *data) {
    // Init buffers
    data->out_buff[0] = '\0';
    data->file_name_types[0] = '\0';
    data->input_args[0] = '\0';

    char *token = strtok((char *)new_buf, "\n");  // Split lines
    strcpy(data->out_buff,token);                 // Keep the name of the binary
    strncat(data->out_buff, "\n", 1);             // Add back the newline
    strcpy(data->file_name_types, token);         // Keep the file name
    strncat(data->file_name_types, ".types", 6);  // Add back the .types ending

    // Add the args lines again
    token = strtok(NULL, "\n");
    if (token != NULL) {
       strcpy(data->input_args, token);
    }
}

// Mutate arguments for the binary in the corpus
void findAndMutateArgs(uint8_t *new_buf, my_mutator_t *data) {
    // Init data used for mutating
    initCurrentMutationData(new_buf, data);
    if ((!data->input_args) || (strlen(data->input_args) == 0)) { new_buf=0; return; }		// All binaries gets at least one char of input
    if ((!data->out_buff) || (strlen(data->out_buff) < 5)) { new_buf=0; return; } 		// t.c.o - cannot be smaller
    if ((!data->file_name_types) || (strlen(data->file_name_types) < 11)) { new_buf=0; return; } // t.c.o.types - cannot be smaller

    // Find numeric parts and mutate them using mutateNumericValue function
    char *token = strtok(data->input_args, " ");
    while (token != NULL) {
        // TODO: add a rand to sometimes skip mutation
    	data->input_digit[0] = '\0';
    	strcpy(data->input_digit, token);
    	mutateUInt32Value(data->input_digit, data, "%u");
        // TODO: add other data types

        // Append the mutated string:
        size_t len = strlen(data->input_digit);
        size_t len_all = strlen(data->out_buff);
        if ((len + len_all) < (MAX_CMDLINE_SIZE - 1))
            strncat(data->out_buff, data->input_digit, len);

        // Next iteration:
	token = strtok(NULL, " "); // Next token
        if (token != NULL) strncat(data->out_buff, " ", 1); // add back the space
   }
   strcpy((char *)new_buf, data->out_buff);
}

/**
 * Perform custom mutations on a given input
 *
 * (Optional for now. Required in the future)
 *
 * @param[in] data pointer returned in afl_custom_init for this fuzz case
 * @param[in] buf Pointer to input data to be mutated
 * @param[in] buf_size Size of input data
 * @param[out] out_buf the buffer we will work on. we can reuse *buf. NULL on
 * error.
 * @param[in] add_buf Buffer containing the additional test case
 * @param[in] add_buf_size Size of the additional test case
 * @param[in] max_size Maximum size of the mutated output. The mutation must not
 *     produce data larger than max_size.
 * @return Size of the mutated output.
 */
size_t afl_custom_fuzz(my_mutator_t *data, uint8_t *buf, size_t buf_size,
                       u8 **out_buf, uint8_t *add_buf,
                       size_t add_buf_size,  // add_buf can be NULL
                       size_t max_size) {

    size_t new_size = MAX_CMDLINE_SIZE <= max_size ? MAX_CMDLINE_SIZE : max_size;
    if (new_size < buf_size) {
        WARNF("Max size of register is: %zu, %zu", new_size, buf_size);
        return 0; // We cannot work with this
    }

    // Allocate a new buffer for the edits
    uint8_t *new_buf = malloc(new_size);
    if (!new_buf) {
        WARNF("Bad allocation for buffer for mutations. Could not allocate %zu size buffer.", new_size);
        return 0;
    }

    // Copy the original input data
    memcpy(new_buf, buf, buf_size);

    // bit flip on the arguments
    findAndMutateArgs(new_buf, data);
    if (!new_buf) {
        WARNF("Bad generation for buffer with mutations.");
        return 0;
    }

    // Shrink the buffer till \0
    size_t actual_size = strlen(data->out_buff) + 1; // Add 1 for the null-terminator
    new_buf = (uint8_t *)realloc(new_buf, actual_size);
    if (!new_buf) {
        WARNF("Bad re-allocation for buffer for mutations. Could not allocate %zu size buffer.", actual_size);
        return 0;
    }

    // Set it as output buff
    *out_buf = new_buf;
    return new_size;
}

/**
 * Deinitialize everything
 *
 * @param data The data ptr from afl_custom_init
 */
void afl_custom_deinit(my_mutator_t *data) {
  data->afl = 0;
  free(data->out_buff);
  free(data->file_name_types);
  free(data->input_args);
  free(data->input_digit);
  free(data);
}

#ifdef DEBUG_CM
int main () {
    my_mutator_t *data = afl_custom_init(0,0); // Create dummy mutator data


    /**************/
    /*   TEST 1   */
    /**************/
    printf(">> TEST 1: mutateUInt32Value with d\n");

    char* input_digit = (char *)malloc(20 * sizeof(char));
    strcpy(input_digit, "-5");
    mutateUInt32Value(input_digit,data,"%d");
    // Print characters until the null-terminator is encountered
    for (int i = 0; input_digit[i] != '\0'; i++) {
        printf("%c", input_digit[i]);
    }
    printf("\n");
    free(input_digit);



    /**************/
    /*   TEST 2   */
    /**************/
    printf("\n>> TEST 2: findAndMutateArgs\n");


    char *input = (char *)malloc(250 * sizeof(char));
    printf("./a.out\n5 5\n");
    strcpy(input, "./a.out\n5 5");
    findAndMutateArgs((unsigned char *)input, data);

    // Print characters until the null-terminator is encountered
    for (int i = 0; input[i] != '\0'; i++) {
        printf("%c", input[i]);
    }
    printf("\n");
    free(input);



    /**************/
    /*   TEST 3   */
    /**************/
    printf("\n>> TEST 3: findAndMutateArgs - Real example\n");

    // Test of new ideas:
    char *input2 = (char *)malloc(250 * sizeof(char));
    printf("/home/ubuntu/gem5-ssbse-challenge-2023/afl/input-args/00003.c.o\n0\n");
    strcpy(input2, "/home/ubuntu/gem5-ssbse-challenge-2023/afl/input-args/00003.c.o\n0");
    findAndMutateArgs((unsigned char *)input, data);
    // Print characters until the null-terminator is encountered
    for (int i = 0; input2[i] != '\0'; i++) {
        printf("%c", input2[i]);
    }
    printf("\n");
    free(input2);



    /**************/
    /*   TEST 4   */
    /**************/
    printf("\n>> TEST 4: mutateUInt64Value with ld\n");

    char* input_digit1 = (char *)malloc(20 * sizeof(char));
    strcpy(input_digit1, "-5");
    mutateUInt64Value(input_digit1,data,"%ld");
    // Print characters until the null-terminator is encountered
    for (int i = 0; input_digit1[i] != '\0'; i++) {
        printf("%c", input_digit1[i]);
    }
    printf("\n");
    free(input_digit1);



    /**************/
    /*   TEST 5   */
    /**************/
    printf("\n>> TEST 5: mutateUInt64Value with lu\n");

    char* input_digit2 = (char *)malloc(20 * sizeof(char));
    strcpy(input_digit2, "-5");
    mutateUInt64Value(input_digit2,data,"%lu");
    // Print characters until the null-terminator is encountered
    for (int i = 0; input_digit2[i] != '\0'; i++) {
        printf("%c", input_digit2[i]);
    }
    printf("\n");
    free(input_digit2);


    // Free all
    afl_custom_deinit(data);
}
#endif
