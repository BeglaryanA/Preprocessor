#define X 5
#define Y 22
int main() {
    int number = X;
    #ifdef Y
        ++number;
    #endif
    #undef X
    int op = X;
}