#include <stdio.h>
#include <unistd.h>

// R_OK: Check read permission.
// W_OK: Check write permission.
// X_OK: Check execute (search) permission.
// F_OK: Check whether the file exists.

int main(void)
{
    const char *file_path;

    file_path = "test";
    if (access(file_path, F_OK) == 0)
        printf("File Exist.\n");
    else
        write(2, "Access Denied!\n", 15);
    return (0);
}