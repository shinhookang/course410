#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    long data_size = 0;
    char *buffer = NULL;

    if (rank == 0) {
        // Root process reads the file
        FILE *file = fopen("input.txt", "r");
	if (file == NULL) {
            perror("Failed to open file");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        // Move to the end of the file to determine its size
        fseek(file, 0, SEEK_END);
        data_size = ftell(file);  // Get file size in bytes
        fseek(file, 0, SEEK_SET); // Reset to the start of the file

	// Allocate buffer and read the file data
        buffer = malloc(data_size * sizeof(char));
        if (buffer == NULL) {
            perror("Failed to allocate buffer");
            fclose(file);
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        fread(buffer, sizeof(char), data_size, file);
        fclose(file);
    } 

    // Broadcast the file size to all processes
    MPI_Bcast(&data_size, 1, MPI_LONG, 0, MPI_COMM_WORLD);

    // Allocate buffer on non-root processes to receive the data
    if (rank != 0) {
        buffer = (char *)malloc(data_size * sizeof(char));
        if (buffer == NULL) {
            perror("Failed to allocate buffer on non-root process");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
    }

    // Broadcast the file data to all processes
    MPI_Bcast(buffer, data_size, MPI_CHAR, 0, MPI_COMM_WORLD);

    // Each process can now use the file data in `buffer`
    printf("Process %d received data: %.20s\n", rank, buffer);

    free(buffer);
    MPI_Finalize();
    return 0;
}
