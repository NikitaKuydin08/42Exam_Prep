#include <unistd.h>

int main(int argc, char **argv)
{
    int i;
    int res;

    i = 0;
    if (argc == 2)
    {
        while (argv[1][i])
        {
            if (argv[1][i] >= 97 && argv[1][i] <= 122)
            {
                res = argv[1][i] - 97;
                argv[1][i] = 122 - res;
            }
            else if (argv[1][i] >= 65 && argv[1][i] <= 90)
            {
                res = argv[1][i] - 65;
                argv[1][i] = 90 - res;
            }
            write(1, &argv[1][i], 1);
            i++;
        }
    }
    write(1, "\n", 1);
    return (0);
}
