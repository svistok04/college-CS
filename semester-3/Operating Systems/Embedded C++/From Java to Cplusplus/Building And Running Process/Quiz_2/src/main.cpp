#define max(a, b) ( ((a) > (b)) ? (a) : (b) )

int main() {
    int a = 5;
    int b = 4;

    int c = max(a++, b);
    return 0;
}