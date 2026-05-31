#ifndef PARQUET_ENGINE_H
#define PARQUET_ENGINE_H

#ifdef __cplusplus
extern "C" {
#endif

// Allocates or resets the vectors holding row data for a specific agent type
void parquet_clear_buffer(const char* agent_name);

// Appends an individual agent's state values into the memory rows
void parquet_buffer_row(const char* agent_name, int iteration, long id, double value);

// Packages the accumulated rows into an Arrow table and commits them to a Parquet file
void parquet_write_file(const char* agent_name, int iteration);

#ifdef __cplusplus
}
#endif

#endif // PARQUET_ENGINE_H
