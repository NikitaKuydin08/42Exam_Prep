/*
 * EXERCISE: FT_SCANF
 *
 * DESCRIPTION:
 * Implement a simplified version of scanf that only handles %s, %d and %c.
 *
 * KEY CONCEPTS:
 * 1. VARIABLE ARGUMENTS: va_list, va_start, va_arg, va_end
 * 2. FORMAT PARSING: Analyze the format string character by character
 * 3. FILE READING: fgetc(), ungetc() for flow control
 * 4. CONVERSIONS: Convert strings to numbers, handle whitespace
 *
 * SUPPORTED FORMAT:
 * - %s: string (up to the first whitespace)
 * - %d: decimal integer (optional sign)
 * - %c: a single character
 */

#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

// Function to skip whitespace in the stream
int match_space(FILE *f)
{
    /*
     * WHITESPACE HANDLING:
     * - Read characters while they are whitespace
     * - Push back the first non-whitespace character to the stream
     * - Return -1 on error
     */
    int ch = fgetc(f);
    if (ch == EOF && ferror(f))
        return -1;

    while (ch != EOF)
    {
        if (!isspace(ch))
        {
            ungetc(ch, f); // Push back non-whitespace character
            break;
        }
        ch = fgetc(f);
    }

    if (ferror(f))
        return -1;
    return 1;
}

// Function to match a specific character
int match_char(FILE *f, char c)
{
    /*
     * LITERAL CHARACTER MATCHING:
     * - Read one character from the stream
     * - Check if it matches the expected one
     * - Push it back if it does not match
     */
    int ch = fgetc(f);
    if (ch == c)
        return 1;
    if (ch != EOF)
        ungetc(ch, f);
    return -1;
}

// Function to read a character (%c)
int scan_char(FILE *f, va_list ap)
{
    /*
     * %c CONVERSION:
     * - Read exactly one character
     * - Do NOT skip whitespace
     * - Store it in the provided pointer
     */
    int ch = fgetc(f);
    char *cp = va_arg(ap, char *);

    if (ch == EOF)
        return -1;

    *cp = (char)ch;
    return 1;
}

// Function to read an integer (%d)
int scan_int(FILE *f, va_list ap)
{
    /*
     * %d CONVERSION:
     * - Skip leading whitespace
     * - Read optional sign (+/-)
     * - Read digits and build the number
     * - Push back the last non-digit character
     */
    int sign = 1;
    int value = 0;
    int ch = fgetc(f);
    int *ip = va_arg(ap, int *);
    int count = 0;

    if (ch == EOF)
        return -1;

    // Skip whitespace
    while (isspace(ch))
        ch = fgetc(f);

    // Handle sign
    if (ch == '-')
    {
        sign = -1;
        ch = fgetc(f);
    }
    else if (ch == '+')
    {
        ch = fgetc(f);
    }

    // Ensure first character is a digit
    if (!isdigit(ch))
    {
        ungetc(ch, f);
        return -1;
    }

    // Read digits and build number
    while (isdigit(ch))
    {
        value = value * 10 + (ch - '0');
        count++;
        ch = fgetc(f);
    }

    // Push back last non-digit
    if (ch != EOF)
        ungetc(ch, f);

    if (count == 0)
        return -1;

    *ip = value * sign;
    return 1;
}

// Function to read a string (%s)
int scan_string(FILE *f, va_list ap)
{
    /*
     * %s CONVERSION:
     * - Skip leading whitespace
     * - Read characters until whitespace is found
     * - Null-terminate the string
     * - Push back the whitespace character
     */
    int ch = fgetc(f);
    char *sp = va_arg(ap, char *);
    int i = 0;

    // Skip leading whitespace
    while (ch != EOF && isspace(ch))
        ch = fgetc(f);

    if (ch == EOF)
        return -1;

    // Read characters until whitespace
    do
    {
        sp[i] = ch;
        i++;
        ch = fgetc(f);
    } while (ch != EOF && !isspace(ch));

    sp[i] = '\0'; // Null-terminate string

    // Push back whitespace character
    if (ch != EOF)
        ungetc(ch, f);

    if (i == 0)
        return -1;
    return 1;
}

// Function to handle format conversions
int match_conv(FILE *f, const char **format, va_list ap)
{
    /*
     * CONVERSION DISPATCHER:
     * - Analyze conversion character
     * - Call the appropriate function
     * - Automatically handle whitespace for %d and %s
     */
    switch (**format)
    {
        case 'c':
            return scan_char(f, ap);
        case 'd':
            match_space(f); // %d skips whitespace automatically
            return scan_int(f, ap);
        case 's':
            match_space(f); // %s skips whitespace automatically
            return scan_string(f, ap);
        case '\0':
            return -1;
        default:
            return -1; // Unsupported conversion
    }
}

// Main scanf logic
int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
    /*
     * MAIN SCANF LOGIC:
     * - Parse the format string character by character
     * - Handle literal characters and conversions (%)
     * - Count successful conversions
     * - Stop at the first error
     */
    int nconv = 0; // Number of successful conversions

    // Check if data is available
    int c = fgetc(f);
    if (c == EOF)
        return EOF;
    ungetc(c, f);

    while (*format)
    {
        if (*format == '%')
        {
            // Conversion found
            format++;
            if (match_conv(f, &format, ap) != 1)
                break; // Conversion error
            else
                nconv++; // Successful conversion
        }
        else if (isspace(*format))
        {
            // Whitespace in format: skip whitespace in input
            if (match_space(f) == -1)
                break;
        }
        else
        {
            // Literal character: must match exactly
            if (match_char(f, *format) != 1)
                break;
        }
        format++;
    }

    // Check for file errors
    if (ferror(f))
        return EOF;

    return nconv; // Return number of successful conversions
}

// Wrapper function for standard scanf
int ft_scanf(const char *format, ...)
{
    /*
     * VARIABLE ARGUMENT WRAPPER:
     * - Initialize va_list
     * - Call main function with stdin
     * - Clean up va_list
     */
    va_list ap;

    va_start(ap, format);
    int ret = ft_vfscanf(stdin, format, ap);
    va_end(ap);

    return ret;
}


int main(void)
{
    int n;
    // int x;
    // char str[100];
    // char c;

    // // Read: number, space, string, space, character
    // int converted = ft_scanf("%d %s %c", &x, str, &c);

    // printf("Converted: %d\n", converted);
    // printf("Number: %d, String: %s, Character: %c\n", x, str, c);
    printf("Input number:\n");
	int result = scanf("%d", &n);
	printf("Result: %d; %d\n", result, n);
    return 0;
}
 

/*
 * KEY POINTS FOR THE EXAM:
 *
 * 1. VARIABLE ARGUMENTS:
 *    - va_start(ap, last_param) to initialize
 *    - va_arg(ap, type) to retrieve next argument
 *    - va_end(ap) to clean up
 *
 * 2. FILE FLOW CONTROL:
 *    - fgetc() to read a character
 *    - ungetc() to push a character back
 *    - ferror() to check for errors
 *
 * 3. WHITESPACE HANDLING:
 *    - %c does NOT skip whitespace
 *    - %d and %s DO skip whitespace
 *    - Whitespace in format matches any whitespace
 *
 * 4. RETURN VALUE:
 *    - Number of successful conversions
 *    - EOF if file error or EOF before any conversion
 *    - Stop at the first failed conversion
 */
