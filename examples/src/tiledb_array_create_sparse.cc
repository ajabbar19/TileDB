/*
 * File: tiledb_array_create_sparse.cc
 * 
 * Creating a sparse array.
 *
 * It assumes that the following programs have been run:
 *    - tiledb_workspace_group_create.cc
 */

#include "c_api.h"

int main() {
  // Intialize context with the default configuration parameters
  TileDB_CTX* tiledb_ctx;
  tiledb_ctx_init(&tiledb_ctx, NULL);

  // Prepare parameters for array schema
  const char* array_name = "my_workspace/sparse_arrays/my_array_B";
  const char* attributes[] = { "a1", "a2", "a3" };  // Three attributes
  const char* dimensions[] = { "d1", "d2" };        // Two dimensions
  int64_t domain[] = 
  { 
      1, 4,                       // d1
      1, 4                        // d2 
  };                
  const int cell_val_num[] = 
  { 
      1,                          // a1
      TILEDB_VAR_NUM,             // a2 
      2                           // a3
  };
  const int compression[] = 
  { 
        TILEDB_GZIP,              // a1 
        TILEDB_GZIP,              // a2
        TILEDB_NO_COMPRESSION,    // a3
        TILEDB_NO_COMPRESSION     // coordinates
  };
  const int types[] = 
  { 
      TILEDB_INT32,               // a1 
      TILEDB_CHAR,                // a2
      TILEDB_FLOAT32,             // a3
      TILEDB_INT64                // coordinates
  };

  // Set array schema
  TileDB_ArraySchema array_schema;
  tiledb_array_set_schema( 
      &array_schema,              // Array schema struct 
      array_name,                 // Array name 
      attributes,                 // Attributes 
      3,                          // Number of attributes 
      2,                          // Capacity 
      TILEDB_HILBERT,             // Cell order 
      cell_val_num,               // Number of cell values per attribute  
      compression,                // Compression
      0,                          // Sparse array
      dimensions,                 // Dimensions
      2,                          // Number of dimensions
      domain,                     // Domain
      4*sizeof(int64_t),          // Domain length in bytes
      NULL,                       // Tile extents
      0,                          // Tile extents length in bytes 
      0,                          // Tile order (will be ingored)
      types                       // Types
  );

  // Create array
  tiledb_array_create(tiledb_ctx, &array_schema); 

  // Free array schema
  tiledb_array_free_schema(&array_schema);

  /* Finalize context. */
  tiledb_ctx_finalize(tiledb_ctx);

  return 0;
}