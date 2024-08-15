class Point {
public:
    // constructors
    Point() : _x(0), _y(0) { }
    Point(float x, float y) : _x(x), _y(y) { }

    // public methods
    void move(float dx, float dy) {
        _x += dx;
        _y += dy;
    }
    float x() const { return _x; }
    float y() const { return _y; }

private:
    // private data fields
    float _x;
    float _y;
};

int main() {
    return 0;
}