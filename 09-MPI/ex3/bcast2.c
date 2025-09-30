#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int data_size = 100;
    char *buffer = NULL;

    if (rank == 0) {
        // Root process reads the file
        FILE *file = fopen("input.txt", "r");
	if (file == NULL) {
            perror("Failed to open file");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
	// Allocate buffer and read the file data
        buffer = malloc(data_size * sizeof(char));
        fread(buffer, sizeof(char), data_size, file);
        fclose(file);
    } else {
        // Non-root processes allocate buffer to receive data
        buffer = malloc(data_size * sizeof(char));
    }

    // Broadcast the file data to all processes
    MPI_Bcast(buffer, data_size, MPI_CHAR, 0, MPI_COMM_WORLD);

    // Each process can now use the file data in `buffer`
    printf("Process %d received data: %.20s\n", rank, buffer);

    free(buffer);
    MPI_Finalize();
    return 0;
}
