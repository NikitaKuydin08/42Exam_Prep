/*
 * EXERCISE: BROKEN_GNL (Get Next Line)
 * 
 * DESCRIPTION:
 * Implement get_next_line that reads line by line from a file descriptor.
 * This version may contain special cases or intentional "bugs".
 * 
 * KEY CONCEPTS:
 * 1. STATIC BUFFER: Maintain state between calls
 * 2. CHUNKED READING: read() with BUFFER_SIZE
 * 3. MEMORY MANAGEMENT: malloc/free for dynamic lines
 * 4. NEWLINE DETECTION: Find '\n' to delimit lines
 * 
 * ALGORITHM:
 * 1. Use a static buffer to persist data between calls
 * 2. Read BUFFER_SIZE chunks until '\n' or EOF is found
 * 3. Extract a full line (including '\n')
 * 4. Save the remainder for the next call
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 100
#endif

// Helper function to calculate string length
int ft_strlen(char *s)
{
    int i = 0;
    if (!s)
        return 0;
    while (s[i])
        i++;
    return i;
}

// Helper function to search for a character in a string
int ft_strchr(const char *s, char c)
{
    int i = 0;
    if (!s)
        return 0;
    while (s[i])
    {
        if (s[i] == c)
            return 1; // Found
        i++;
    }
    return 0; // Not found
}

// Helper function to concatenate two strings
char *ft_strjoin(char *s1, char *s2)
{
    /*
     * DYNAMIC CONCATENATION:
     * - Calculate lengths of both strings
     * - Allocate memory for the result
     * - Copy s1 + s2 into the new string
     * - Free s1 (important to avoid leaks)
     */
    if (!s1 || !s2)
        return NULL;
    
    int len1 = ft_strlen(s1);
    int len2 = ft_strlen(s2);
    char *result = malloc(len1 + len2 + 1);
    
    if (!result)
        return NULL;
    
    int i = 0, j = 0;
    
    // Copy s1
    while (s1[i])
    {
        result[i] = s1[i];
        i++;
    }
    
    // Copy s2
    while (s2[j])
    {
        result[i] = s2[j];
        i++;
        j++;
    }
    
    result[i] = '\0';
    return result;
}

// Function to join buffer with read data
char *join_and_free(char *saved, char *buffer)
{
    /*
     * JOIN WITH AUTOMATIC FREE:
     * - Create a new concatenated string
     * - Free the old string (saved)
     * - Return the new string or NULL on error
     */
    char *temp = ft_strjoin(saved, buffer);
    if (!temp)
    {
        free(saved);
        return NULL;
    }
    free(saved);
    return temp;
}

// Function to read until a newline or EOF is found
char *read_until_newline(int fd, char *saved)
{
    /*
     * ACCUMULATIVE READING:
     * - Read BUFFER_SIZE chunks
     * - Accumulate into the saved buffer
     * - Stop when '\n' or EOF is found
     * - Handle read() errors
     */
    char *buffer;
    int bytes_read;

    // Initialize saved if it is NULL
    if (!saved)
    {
        saved = malloc(1);
        if (!saved)
            return NULL;
        saved[0] = '\0';
    }

    buffer = malloc(BUFFER_SIZE + 1);
    if (!buffer)
    {
        free(saved);
        return NULL;
    }

    bytes_read = 1;
    while (bytes_read > 0)
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        
        if (bytes_read == -1)
        {
            free(saved);
            free(buffer);
            return NULL;
        }
        
        buffer[bytes_read] = '\0';
        saved = join_and_free(saved, buffer);
        
        if (!saved)
        {
            free(buffer);
            return NULL;
        }
        
        // Stop if we find a newline
        if (ft_strchr(buffer, '\n'))
            break;
    }
    
    free(buffer);
    return saved;
}

// Function to extract a line from the buffer
char *extract_line(char *buffer)
{
    /*
     * LINE EXTRACTION:
     * - Find the position of '\n'
     * - Allocate memory for the line (including '\n')
     * - Copy characters up to and including '\n'
     * - Null-terminate
     */
    if (!buffer || !buffer[0])
        return NULL;
    
    int i = 0;
    // Find length up to '\n' or end
    while (buffer[i] && buffer[i] != '\n')
        i++;
    
    char *line = malloc(i + 2); // +1 for '\n', +1 for '\0'
    if (!line)
        return NULL;
    
    int j = 0;
    // Copy characters
    while (j <= i && buffer[j])
    {
        line[j] = buffer[j];
        j++;
    }
    line[j] = '\0';
    
    return line;
}

// Function to save the remainder after extracting a line
char *save_remainder(char *buffer)
{
    /*
     * SAVE REMAINDER:
     * - Find position after '\n'
     * - If no content remains, free and return NULL
     * - If content remains, allocate and copy the rest
     */
    if (!buffer)
        return NULL;
    
    int i = 0;
    // Find position of '\n'
    while (buffer[i] && buffer[i] != '\n')
        i++;
    
    if (buffer[i] == '\n')
        i++; // Skip the '\n'
    
    // If there is no content after '\n'
    if (!buffer[i])
    {
        free(buffer);
        return NULL;
    }
    
    // Allocate for the remainder
    char *remainder = malloc(ft_strlen(buffer) - i + 1);
    if (!remainder)
    {
        free(buffer);
        return NULL;
    }
    
    int j = 0;
    while (buffer[i])
        remainder[j++] = buffer[i++];
    remainder[j] = '\0';
    
    free(buffer);
    return remainder;
}

// Main get_next_line function
char *get_next_line(int fd)
{
    /*
     * MAIN LOGIC:
     * - Use a static buffer to persist between calls
     * - Read until a full newline is available
     * - Extract a line
     * - Save the remainder for the next call
     */
    static char *saved; // Persistent static buffer
    char *line;

    // Validate file descriptor and BUFFER_SIZE
    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;
    
    // Read data until we have a complete line
    saved = read_until_newline(fd, saved);
    if (!saved)
        return NULL;
    
    // Extract the current line
    line = extract_line(saved);
    if (!line)
    {
        free(saved);
        saved = NULL;
        return NULL;
    }
    
    // Save the remainder for the next call
    saved = save_remainder(saved);
    
    return line;
}

/*
 * SIMPLER ALTERNATIVE VERSION (for special cases):
 * This version may contain some intentional "bugs"
 */
char *get_next_line_simple(int fd)
{
    static char buffer[BUFFER_SIZE];
    static int buffer_read = 0;
    static int buffer_pos = 0;
    char *line;
    int i = 0;
    int line_size = 1000; // Fixed size (possible "bug")

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;
    
    line = malloc(line_size);
    if (!line)
        return NULL;
    
    while (1)
    {
        // If we consumed the entire buffer, read more
        if (buffer_pos >= buffer_read)
        {
            buffer_read = read(fd, buffer, BUFFER_SIZE);
            buffer_pos = 0;
            
            if (buffer_read == 0) // EOF
                break;
            else if (buffer_read < 0) // Error
            {
                free(line);
                return NULL;
            }
        }
        
        // Copy current character into the line
        line[i++] = buffer[buffer_pos++];
        
        // If newline is found, stop
        if (line[i - 1] == '\n')
            break;
    }
    
    line[i] = '\0';
    
    // If nothing was read, return NULL
    if (i == 0)
    {
        free(line);
        return NULL;
    }
    
    return line;
}

/*
 * KEY POINTS FOR THE EXAM:
 * 
 * 1. STATIC BUFFER:
 *    - Keeps data between function calls
 *    - Automatically resets when the file ends
 *    - Must be handled carefully to avoid leaks
 * 
 * 2. MEMORY MANAGEMENT:
 *    - Each returned line must be freed by the caller
 *    - Free internal buffers on error
 *    - Use realloc if necessary for long lines
 * 
 * 3. SPECIAL CASES:
 *    - Files without a final newline
 *    - Empty lines (only '\n')
 *    - read() errors
 *    - BUFFER_SIZE = 1 (extreme case)
 * 
 * 4. COMMON "BUGS" (possibly intentional):
 *    - Not handling lines longer than a fixed buffer
 *    - Not freeing memory correctly on errors
 *    - Not handling dynamic BUFFER_SIZE
 *    - Incorrect behavior with binary files
 */
