Code Generator for AR.

Compile with:

g++ `pkg-config --cflags opencv` code_generator.cpp -o code_generator `pkg-config --libs opencv`

Run with:

./code_generator ID1 [ID2 ID3..] path_to_save_image
