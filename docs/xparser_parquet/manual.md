# Xparser Parquet

The main focus was not on modifying xparser itself to write Parquet files. Instead, the focus was on enhancing the simulation code templates that xparser reads, allowing the compiled simulation binary to write Parquet files natively at runtime.

Here is how those responsibilities are split:

## 1. What xparser Actually Does

xparser is a pre-compilation code generator, not the simulation engine. Its only job is to read your model's XML specification file (which defines your agents, states, and variables) and unroll code templates (like parquet.cpp.tmpl and parquet_engine.cpp.tmpl) into concrete C++ source files (parquet.cpp and parquet_engine.cpp).

xparser itself doesn't know anything about Apache Arrow, memory allocation, or Parquet compression. It just substitutes template variables like <?foreach xagent?> and $name into plain text.

## 2. Where the Real Focus Was: The Runtime Engine

Our actual focus was on building a high-performance runtime data pipeline inside the template files that executes while the simulation is running.

Instead of changing how xparser parses files, we wrote a standard C++ engine that hooks into FLAME's loop structure to intercept agent data before it gets dumped into the traditional, bulky XML iteration logs.
The Pipeline Architecture We Built:
```text
[FLAME Simulation Loop]
         │
         ▼
[parquet.cpp]  ───► Captures simulation state & iteration paths (outputpath)
         │
         ▼
[parquet_engine.cpp]  
         │
         ├──► 1. Buffers raw C++ vectors (iterations, IDs, agent variables)
         ├──► 2. Standardizes memory layouts & resets states (buf.columns.clear())
         ├──► 3. Feeds data into Apache Arrow Builders (Int32Builder, DoubleBuilder)
         ├──► 4. Assembles an in-memory Arrow Table with strict Schema enforcement
         │
         ▼
[Physical Disk] ───► Compresses and writes highly optimized .parquet files
```

## Summary of the Goal

The goal was to replace FLAME's default XML runtime output mechanism with an Apache Arrow/Parquet serialization engine.

We accomplished this by feeding clean, robust C++20 memory management and Arrow API calls into the .tmpl files, so that whenever you run ./xparser and compile your model, the resulting executable natively records data into Parquet format instead of millions of lines of uncompressed XML text.