//
// Copyright 2012 Rui Ueyama. Released under the MIT license.
// 

#include <ctype.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "8cc.h"

#define BUFFER_INIT_SIZE 8

// Allocates and initializes a new Buffer instance with an initial size.
Buffer *make_buffer() {
    // Allocate memory for the Buffer structure itself, then we 
    // check for memory allocation failure. If this is the case, 
    // then we return early with NULL
    Buffer *r = malloc(sizeof(Buffer));
    if (r == NULL) return NULL;

    // Same as before, try to allocate initial memory for the 
    // buffer's body, and if it fails, we free the previously
    // allocated memory, before returning NULL
    r->body = malloc(BUFFER_INIT_SIZE);
    if (r->body == NULL) {
        free(r);
        return NULL;
    }

    r->nalloc = BUFFER_INIT_SIZE; // Set the initial allocated size
    r->len = 0; // Initialize the length to zero
    return r; // Return the initialized Buffer
}

// Resizes the buffer's body when it runs out of space
static void realloc_body(Buffer *b) {
    // Double the size of the allocated body
    int newsize = b->nalloc * 2;
    // Reallocate memory for the buffer body, and if it fails
    // then we simply return early
    char *body = realloc(b->body, newsize);
    if (body == NULL) return; // Check for allocation failure

    // Otherwise, we update the buffer properties
    b->body = body;      // Update the buffer's body pointer
    b->nalloc = newsize; // Update the allocated size
}

// Returns a pointer to the buffer's internal body
char *buf_body(Buffer *b) { return b->body; }

// Returns the current length of the buffer
int buf_len(Buffer *b) { return b->len; }

// Writes a single character to the buffer, resizing if necessary
void buf_write(Buffer *b, char c) {
    // Check if there is enough space for the new character.
    // If there isn't enough space, we resize.
    if (b->nalloc == (b->len + 1))
        realloc_body(b);

    // Write the character and increment the length
    b->body[b->len++] = c;
}

// Appends a string of given length to the buffer
void buf_append(Buffer *b, char *s, int len) {
    // Iterate through each character in the input string, and
    // write each character to the buffer
    for (int i = 0; i < len; i++)
        buf_write(b, s[i]);
}

// Appends formatted data to the buffer using a format string
void buf_printf(Buffer *b, char *fmt, ...) {
    va_list args; // Declare a variable argument list
    for (;;) {
        int avail = b->nalloc - b->len; // Calculate available space in the buffer
        va_start(args, fmt); // Initialize the argument list with the format string
        int written = vsnprintf(b->body + b->len, avail, fmt, args); // Write formatted data to the buffer
        va_end(args); // Clean up the argument list
        if (avail <= written) { // If not enough space was available
            realloc_body(b); // Resize the buffer and try again
            continue; // Retry the formatting
        }
        b->len += written; // Update the buffer length
        return; // Exit the function
    }
}

// Formats a string using a variable argument list
char *vformat(char *fmt, va_list ap) {
    // Allocate a new buffer for the formatted output. If the 
    // allocation fails, return early with NULL.
    Buffer *b = make_buffer();
    if (b == NULL) return NULL;

    // Define Temporary variable for argument list
    va_list aq;
    for (;;) {
        // Calculate available space in the buffer
        int avail = b->nalloc - b->len;

        va_copy(aq, ap); // Copy the argument list for vsnprintf
        // Format the string, and save the output length
        int written = vsnprintf(b->body + b->len, avail, fmt, aq);
        va_end(aq); // Clean up the copied argument list

        // If not enough space was available, Resize the buffer 
        // and Retry the formatting
        if (avail <= written) {
            realloc_body(b);
            continue;
        }

        b->len += written;  // Update the buffer length
        return buf_body(b); // Return the formatted string
    }
}

// Formats a string using a variable number of arguments
char *format(char *fmt, ...) {
    va_list ap;                 // Declare a variable argument list
    va_start(ap, fmt);          // Initialize the argument list with the format string
    char *r = vformat(fmt, ap); // Format the string using vformat
    va_end(ap);                 // Clean up the argument list
    return r;                   // Return the formatted string
}

// Returns the escaped representation of a single character
static char *quote(char c) {
    // Peform a switch statement to check what kind of special
    // character <c> is, and Return the escaped version of 
    // common special characters?
    switch (c) {
        case '"':  return "\\\"";
        case '\\': return "\\\\";
        case '\b': return "\\b";
        case '\f': return "\\f";
        case '\n': return "\\n";
        case '\r': return "\\r";
        case '\t': return "\\t";
        // Return NULL if character doesn't need escaping
        default:   return NULL;
    };
}

// Appends the printable representation of a character to the buffer
static void print(Buffer *b, char c) {
    // Get the quoted representation of the character
    char *q = quote(c);
    if (q) {
        // Append the escaped string to the buffer
        buf_printf(b, "%s", q);
    } else if (isprint(c)) {
        // If it's a printable character, append it directly
        buf_printf(b, "%c", c);
    } else {
        // Append the hexadecimal representation for non-printable characters
    #ifdef __eir__
        // Use format without leading zeros
        buf_printf(b, "\\x%x", c);
    #else
        // Use format with leading zeros
        buf_printf(b, "\\x%02x", ((int)c) & 255);
    #endif
    }
}

// Quotes a C string by escaping special characters
char *quote_cstring(char *p) {
    // Create a new buffer for the quoted string, then we check
    // for memory allocation failure. If this is the case, then
    // we return early with NULL 
    Buffer *b = make_buffer();
    if (b == NULL) return NULL;

    // Iterate through each character in the string, and append 
    // the escaped character to the buffer
    while (*p) print(b, *p++);

    // Return the quoted string
    return buf_body(b);
}

// Quotes a C string of a given length by escaping special characters
char *quote_cstring_len(char *p, int len) {
    // Create a new buffer for the quoted string, then we check
    // for memory allocation failure. If this is the case, then
    // we return early with NULL 
    Buffer *b = make_buffer();
    if (b == NULL) return NULL;

    // Iterate through each character in the string, and append
    // the escaped character to the buffer
    for (int i = 0; i < len; i++)
        print(b, p[i]);

    // Return the quoted string
    return buf_body(b);
}

// Returns the escaped representation of a single character.
char *quote_char(char c) {
    if (c == '\\') return "\\\\"; // Escape backslashes
    if (c == '\'') return "\\'"; // Escape single quotes
    return format("%c", c); // Otherwise, return the character formatted
}
