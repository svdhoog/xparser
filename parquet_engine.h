#ifndef PARQUET_ENGINE_H
#define PARQUET_ENGINE_H

#ifdef __cplusplus
extern "C" {
#endif

void parquet_clear_buffer(const char* agent_name);
void parquet_buffer_row(const char* agent_name, int iteration_no, long id, double value);
void parquet_write_file(const char* agent_name, int iteration_no);

#ifdef __cplusplus
}
#endif

#endif // PARQUET_ENGINE_H