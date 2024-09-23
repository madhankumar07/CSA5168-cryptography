#include <stdio.h>
#include <stdint.h>
void print_binary(uint64_t value, int bits) {
    for (int i = bits - 1; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
    }
    printf("\n");
}
uint32_t extract_first_24_bits(uint64_t key) {
    return (uint32_t)((key >> 28) & 0xFFFFFF); 
}
uint32_t extract_second_24_bits(uint64_t key) {
    return (uint32_t)(key & 0xFFFFFF); 
}
void generate_subkeys(uint64_t key, uint32_t subkeys[16][2]) {
    for (int i = 0; i < 16; i++) {
        uint64_t rotated_key = (key << i) | (key >> (56 - i));
        subkeys[i][0] = extract_first_24_bits(rotated_key); 
        subkeys[i][1] = extract_second_24_bits(rotated_key); 

        printf("Subkey %d: First 24 bits: ", i + 1);
        print_binary(subkeys[i][0], 24);

        printf("         Second 24 bits: ");
        print_binary(subkeys[i][1], 24);
    }
}
int main() {
    uint64_t initial_key = 0x123456789ABC; 
    uint32_t subkeys[16][2];
    generate_subkeys(initial_key, subkeys);
    return 0;
}

