#ifndef _TOOLS_IOA_H
#define _TOOLS_IOA_H
#include <stdint.h>

// Inline assembly for IO Access

/// @brief Sends a 8bit value on an IO Location [outbyte]
/// @param port value destination
/// @param val target value to send
inline void outbyte(uint16_t port, uint8_t val){
    __asm__ volatile ("outb %b0, %w1" : : "a"(val), "Nd"(port) : "memory");
}

/// @brief recieve/read a byte from an IO location [inbyte]
/// @param port port to listen to
inline uint8_t inbyte(uint16_t port){
    uint8_t data;
    __asm__ volatile ("inb %w1, %b0" : "=a"(data) : "Nd"(port) : "memory");
    return data;
}

/// @brief Send a 16bit value to an IO Location [outbyte 16bit edition]
/// @param port the port to listen to 
/// @param val target the value to send
inline void outbyte16(uint16_t port, uint16_t val){
    __asm__ volatile("outw %w0, %w1" : : "a"(val), "Nd"(port));
}

/// @brief recieve/read a byte from an IO location [inbyte]
/// @param port port to listen to
inline uint16_t inbyte16(uint16_t port){
    uint16_t data;
    __asm__ volatile ("inw %w1, %w0" : "=a" (data) : "Nd" (port));
    return data;
}


/// @brief Send a 32bit value to an IO Location [outbyte 32bit edition]
/// @param port the port to listen to 
/// @param val target the value to send
inline void outbyte32(uint16_t port, uint32_t val){
    __asm__ volatile ("outl %0, %w1" : : "a" (val), "Nd" (port));
}

/// @brief recieve/read a byte from an IO location [inbyte]
/// @param port port to listen to
inline uint32_t inbyte32(uint16_t port){
    uint32_t data;
    __asm__ volatile("inl %w1, %0" : "=a" (data) : "Nd"(port));
    return data;
}
#endif