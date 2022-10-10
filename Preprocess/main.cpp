#include "Preproc.h"

int main(int argc, char* argv[]) {
    Preprocessor obj;
    if (argc == 2) {
        obj.preprocessing(argv[1]);
    } else {
        throw::std::invalid_argument ("Wrong count of arguments");
    }
    return 0;
}