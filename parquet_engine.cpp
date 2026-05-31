#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <map>

#include "header.h" // This pulls in our auto-generated execute_all_parquet_agents
#include "parquet_engine.h"

#include <arrow/api.h>
#include <arrow/io/api.h>
#include <parquet/arrow/writer.h>
#include <parquet/exception.h>

struct AgentDataBuffer {
    std::vector<int64_t> iterations;
    std::vector<int64_t> ids;
    std::vector<double> numeric_values;
};

static std::map<std::string, AgentDataBuffer> global_buffers;

extern "C" {

void parquet_clear_buffer(const char* agent_name) {
    global_buffers[std::string(agent_name)].iterations.clear();
    global_buffers[std::string(agent_name)].ids.clear();
    global_buffers[std::string(agent_name)].numeric_values.clear();
}

void parquet_buffer_row(const char* agent_name, int iteration, long id, double value) {
    auto& buf = global_buffers[std::string(agent_name)];
    buf.iterations.push_back(iteration);
    buf.ids.push_back(id);
    buf.numeric_values.push_back(value);
}

void parquet_write_file(const char* agent_name, int iteration) {
    std::string name(agent_name);
    auto& buf = global_buffers[name];
    if (buf.iterations.empty()) return;

    arrow::Int64Builder iter_builder;
    arrow::Int64Builder id_builder;
    arrow::DoubleBuilder val_builder;

    (void)iter_builder.AppendValues(buf.iterations);
    (void)id_builder.AppendValues(buf.ids);
    (void)val_builder.AppendValues(buf.numeric_values);

    std::shared_ptr<arrow::Array> iter_arr; (void)iter_builder.Finish(&iter_arr);
    std::shared_ptr<arrow::Array> id_arr;   (void)id_builder.Finish(&id_arr);
    std::shared_ptr<arrow::Array> val_arr;  (void)val_builder.Finish(&val_arr);

    auto schema = arrow::schema({
        arrow::field("_ITERATION_NO", arrow::int64()),
        arrow::field("id", arrow::int64()),
        arrow::field("value", arrow::float64())
    });

    std::shared_ptr<arrow::Table> table = arrow::Table::Make(schema, {iter_arr, id_arr, val_arr});
    std::string path = "parquet_output/data_" + name + "_iter_" + std::to_string(iteration) + ".parquet";
    std::shared_ptr<arrow::io::FileOutputStream> outfile;
    PARQUET_ASSIGN_OR_THROW(outfile, arrow::io::FileOutputStream::Open(path));
    PARQUET_THROW_NOT_OK(parquet::arrow::WriteTable(*table, arrow::default_memory_pool(), outfile, 3000));
}

// Entry point called by the simulation
void run_parquet_sequence(int iteration_no) {
    // Calls the C++ inline helper function unrolled inside header.h!
    execute_all_parquet_agents(iteration_no);
}

} //Extern "C"
