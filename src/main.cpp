#include <iostream>
#include "Halide.h"
#include "halide_image_io.h"

using std::cout;
using std::cin;
using std::endl;
using namespace Halide;
using namespace Halide::ConciseCasts;

int main(int argc, char ** argv) {
    if (argc < 7) {
        cout << "Usage: bin/main <path/to/input1> <alpha> <path/to/input2> <beta> <gamma> <path/to/output>" << endl;
        return -1;
    }

    const std::string input_file1 = argv[1];
    const float alpha = atof(argv[2]);
    const std::string input_file2 = argv[3];
    const float beta = atof(argv[4]);
    const float gamma = atof(argv[5]);
    const std::string output_filename = argv[6];

    Buffer<uint8_t> input1 = Tools::load_image(input_file1);
    Buffer<uint8_t> input2 = Tools::load_image(input_file2);
    Buffer<uint8_t> output(input1.width(), input1.height(), input1.channels());

    Var x{"x"}, y{"y"}, c{"c"};
    Func input1_f32{"input1_f32"};
    input1_f32(x, y, c) = f32(input1(x, y, c)); 
    Func input2_f32{"input1_f32"};
    input2_f32(x, y, c) = f32(input2(x, y, c)); 


    Func add_weighted{"add_weighted"};
    add_weighted(x, y, c) = u8_sat(
        input1_f32(x, y, c) * alpha + input2_f32(x, y, c) * beta + gamma
    );

    output = add_weighted.realize({input1.width(), input1.height(), input1.channels()});
    Tools::save_image(output, output_filename);

    return 0;
}