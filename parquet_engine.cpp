#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <map>

/* Arrow & Parquet Core Engine Headers */
#include <arrow/api.h>
#include <arrow/io/api.h>
#include <parquet/arrow/writer.h>
#include <parquet/exception.h>

// A generic row-buffer to store data dynamically before writing to Parquet
struct AgentDataBuffer {
    std::vector<int64_t> iterations;
    std::vector<int64_t> ids;
    std::vector<double> numeric_values;
};

// Global map to hold row buffers per agent type name
static std::map<std::string, AgentDataBuffer> global_buffers;

#ifdef __cplusplus
extern "C" {
#endif

// Clear buffers at the start of an iteration step if necessary
void parquet_clear_buffer(const char* agent_name) {
    std::string name(agent_name);
    global_buffers[name].iterations.clear();
    global_buffers[name].ids.clear();
    global_buffers[name].numeric_values.clear();
}

// C-compatible function to receive data pushed from FLAME agents
void parquet_buffer_row(const char* agent_name, int iteration_no, int64_t id, double value) {
    std::string name(agent_name);
    global_buffers[name].iterations.push_back(iteration_no);
    global_buffers[name].ids.push_back(id);
    global_buffers[name].numeric_values.push_back(value);
}

// Finalize and write accumulated rows out to a Parquet file
void parquet_write_file(const char* agent_name, int iteration_no) {
    std::string name(agent_name);
    auto& buf = global_buffers[name];
    
    if (buf.iterations.empty()) return;

    // 1. Build Arrow Arrays from buffered vectors
    arrow::Int64Builder iter_builder;
    arrow::Int64Builder id_builder;
    arrow::DoubleBuilder val_builder;

    (void)iter_builder.AppendValues(buf.iterations);
    (void)id_builder.AppendValues(buf.ids);
    (void)val_builder.AppendValues(buf.numeric_values);

    std::shared_ptr<arrow::Array> iter_array; (void)iter_builder.Finish(&iter_array);
    std::shared_ptr<arrow::Array> id_array;   (void)id_builder.Finish(&id_array);
    std::shared_ptr<arrow::Array> val_array;  (void)val_builder.Finish(&val_array);

    // 2. Map arrays to schema fields
    auto schema = arrow::schema({
        arrow::field("_ITERATION_NO", arrow::int64()),
        arrow::field("id", arrow::int64()),
        arrow::field("value", arrow::float64())
    });

    // 3. Construct Table
    std::shared_ptr<arrow::Table> table = arrow::Table::Make(schema, {iter_array, id_array, val_array});

    // 4. Stream to file system destination
    std::string path = "parquet_output/data_" + name + "_iter_" + std::to_string(iteration_no) + ".parquet";
    std::shared_ptr<arrow::io::FileOutputStream> outfile;
    PARQUET_ASSIGN_OR_THROW(outfile, arrow::io::FileOutputStream::Open(path));

    PARQUET_THROW_NOT_OK(parquet::arrow::WriteTable(*table, arrow::default_memory_pool(), outfile, 3000));
    
    // Clear buffer after writing
    parquet_clear_buffer(agent_name);
}

#ifdef __cplusplus
}
#endif