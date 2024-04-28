#include <fstream>
#include <iostream>
#include "DynamicArray.hpp"
#include <opencv2/opencv.hpp>

struct Point {
    float x, y;
    static Point p0;

    static int orientation(Point p, Point q, Point r) {
        const float val = (q.y - p.y) * (r.x - p.x) - (r.y - p.y) * (q.x - p.x);
        if (val == 0) return 0; // 0 for colinear
        return (val > 0) ? 1 : -1; // 1 for clockwise, -1 for counterclockwise
    }
    static float distance(Point p1, Point p2) {
        return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
    }
    bool operator>(const Point& other) const {
        const int o = orientation(p0, *this, other);
        if (o == 0) {
            return distance(*this, p0) > distance(other, p0); // the furthest point comes later
        }
        return o == 1;
        // if (p0, *this, other) is clockwise (turn right), then *this comes later, i.e. if moving from p0 to *this
        // to other is clockwise (requires to turn right), then *this comes later
    }
    std::ostream &operator<<(std::ostream &os) const {
        os << "(" << x << ", " << y << ")";
        return os;
    }
};

Point Point::p0;
DynamicArray<Point>* grahamScan(DynamicArray<Point>*);
DynamicArray<Point>* readFromFile(const std::string&);
void findLowestPoint(DynamicArray<Point>*);
void heapSort(DynamicArray<Point>*);
void drawConvexHull(DynamicArray<Point>*, DynamicArray<Point>*, const std::string&);
cv::Point2f normalize(const cv::Point2f&);
void drawFilledArrow(cv::Mat&, const cv::Point& , const cv::Point&, const cv::Scalar&, float);

int main() {
    // DynamicArray<Point>* setOfPoints1 = readFromFile("points1.txt");
    // for (int i = 0; i < setOfPoints1->size; ++i) {
    //     std::cout << "(" <<  setOfPoints1->arr[i].x << ", " << setOfPoints1->arr[i].y << ")" << std::endl;
    // }
    // std::cout << std::endl;
    // DynamicArray<Point>* result1 = grahamScan(setOfPoints1);
    // std::cout << std::endl;
    // std::cout << "(" << Point::p0.x << ", " << Point::p0.y << ")" << std::endl;
    // drawConvexHull(setOfPoints1, result1, "result1.png");
    // DynamicArray<Point>* setOfPoints2 = readFromFile("points2.txt");
    // DynamicArray<Point>* result2 = grahamScan(setOfPoints2);
    // drawConvexHull(setOfPoints2, result2, "result2.png");
    DynamicArray<Point>* setOfPoints3 = readFromFile("points3.txt");
    DynamicArray<Point>* result3 = grahamScan(setOfPoints3);
    drawConvexHull(setOfPoints3, result3, "result3.png");
    // DynamicArray<Point>* setOfPoints4 = readFromFile("points4.txt");
    // DynamicArray<Point>* result4 = grahamScan(setOfPoints4);
    // drawConvexHull(setOfPoints4, result4, "result4.png");
    // DynamicArray<Point>* setOfPoints5 = readFromFile("points5.txt");
    // DynamicArray<Point>* result5 = grahamScan(setOfPoints5);
    // drawConvexHull(setOfPoints5, result5, "result5.png");
    return 0;
}

DynamicArray<Point>* grahamScan(DynamicArray<Point>* setOfPoints) {
    findLowestPoint(setOfPoints);
    heapSort(setOfPoints);
    // for (int i = 0; i < setOfPoints->size; ++i) {
    //     std::cout << "(" <<  setOfPoints->arr[i].x << ", " << setOfPoints->arr[i].y << ")" << std::endl;
    // }
    DynamicArray<Point>* convexHull = new DynamicArray<Point>();
    convexHull->push(Point::p0);
    convexHull->push(setOfPoints->arr[1]);
    convexHull->push(setOfPoints->arr[2]);
    for (int i = 3; i < setOfPoints->size; ++i) {
        while (Point::orientation(convexHull->arr[convexHull->size - 2],
                                  convexHull->arr[convexHull->size - 1],
                                  setOfPoints->arr[i]) != -1) {
            convexHull->pop();
        }
        convexHull->push(setOfPoints->arr[i]);
    }
    return convexHull;
}

DynamicArray<Point>* readFromFile(const std::string& name) {
    std::ifstream file(name);
    if (!file.is_open()) {
        std::cerr << "File not found" << std::endl;
        exit(1);
    }
    int size;
    float x, y;
    file >> size;
    DynamicArray<Point>* setOfPoints = new DynamicArray<Point>();
    for (int i = 0; i < size; ++i) {
        file >> x >> y;
        setOfPoints->push(Point{x, y});
    }
    return setOfPoints;
}

void findLowestPoint(DynamicArray<Point>* setOfPoints) {
    Point lowestPoint = setOfPoints->arr[0];
    int lowestPointIndex = 0;
    for (int i = 1; i < setOfPoints->size; ++i) {
        if (lowestPoint.y > setOfPoints->arr[i].y || (lowestPoint.y == setOfPoints->arr[i].y && setOfPoints->arr[i].x < lowestPoint.x)) {
            lowestPoint = setOfPoints->arr[i];
            lowestPointIndex = i;
        }
    }
    Point::p0 = lowestPoint;
    std::swap(setOfPoints->arr[0], setOfPoints->arr[lowestPointIndex]);
}

void heapSort(DynamicArray<Point>* setOfPoints) {
    Point* arr = setOfPoints->arr;
    int size = setOfPoints->size;
    for (int i = 1; i < size; ++i) {
        int j = i;
        while (j > 0) {
            int parentIndex = (j - 1) / 2;
            if (arr[j] > arr[parentIndex]) {
                std::swap(arr[j], arr[parentIndex]);
                j = parentIndex;
            } else {
                break;
            }
        }
    }
    for (int i = size - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        int j = 0;
        int leftChild = 1;
        while (leftChild < i) {
            int rightChild = 2 * j + 2;
            if (rightChild < i && arr[rightChild] > arr[leftChild]) {
                leftChild = rightChild;
            }
            if (arr[j] > arr[leftChild]) {
                break;
            }
            std::swap(arr[j], arr[leftChild]);
            j = leftChild;
            leftChild = 2 * j + 1;
        }
    }
}

void drawConvexHull(DynamicArray<Point>* setOfPoints, DynamicArray<Point>* convexHull, const std::string& fileName) {
    cv::Mat image(12000, 12000, CV_8UC3, cv::Scalar(255, 255, 255));
    float scale = 11900.0f;
    float shift = 50.0f;
    float arrowMagnitude = 85.0f;

    cv::circle(image, cv::Point(std::round(Point::p0.x * scale + shift), std::round((1 - Point::p0.y) * scale + shift)), 26, cv::Scalar(34, 138, 34), 1);

    for (int i = 0; i < setOfPoints->size; ++i) {
        cv::Point center(std::round(setOfPoints->arr[i].x * scale + shift),
                                    std::round((1 - setOfPoints->arr[i].y) * scale + shift));
        cv::circle(image, center, 7, cv::Scalar(0, 0, 0), -1); // Filled circle
        std::string pointID = std::to_string(i);
        cv::Point textPos(center.x - 25, center.y - 15); // Adjust position to avoid overlap
        cv::putText(image, pointID, textPos, 0, 0.75, cv::Scalar(255, 0, 0), 2); // Smaller text
    }

    for (int i = 0; i < convexHull->size - 1; ++i) {
        cv::Point start(std::round(convexHull->arr[i].x * scale + shift), std::round((1 - convexHull->arr[i].y) * scale + shift));
        cv::Point end(std::round(convexHull->arr[i + 1].x * scale + shift), std::round((1 - convexHull->arr[i + 1].y) * scale + shift));
        drawFilledArrow(image, start, end, cv::Scalar(0, 0, 255), arrowMagnitude);
    }

    cv::Point start(std::round(convexHull->arr[convexHull->size - 1].x * scale + shift), std::round((1 - convexHull->arr[convexHull->size - 1].y) * scale + shift));
    cv::Point end(std::round(convexHull->arr[0].x * scale + shift), std::round((1 - convexHull->arr[0].y) * scale + shift));
    drawFilledArrow(image, start, end, cv::Scalar(0, 0, 255), arrowMagnitude);

    cv::imwrite(fileName, image);
}

cv::Point2f normalize(const cv::Point2f& p) {
    float norm = std::sqrt(p.x * p.x + p.y * p.y);
    return cv::Point2f(p.x / norm, p.y / norm);
}

void drawFilledArrow(cv::Mat& image, const cv::Point& start, const cv::Point& end, const cv::Scalar& color, float arrowMagnitude) {
    cv::Point2f direction, p, q;
    direction.x = static_cast<float>(end.x - start.x);
    direction.y = static_cast<float>(end.y - start.y);
    float hypotenuse = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    // Here we are making the arrow magnitude independent of the line length
    direction.x = direction.x / hypotenuse;
    direction.y = direction.y / hypotenuse;

    // Calculate the points of the arrowhead
    p.x = end.x - arrowMagnitude * direction.x + arrowMagnitude * direction.y / 3;
    p.y = end.y - arrowMagnitude * direction.y - arrowMagnitude * direction.x / 3;
    q.x = end.x - arrowMagnitude * direction.x - arrowMagnitude * direction.y / 3;
    q.y = end.y - arrowMagnitude * direction.y + arrowMagnitude * direction.x / 3;

    // Draw the line first
    cv::line(image, start, end, color, 2);

    // Create the arrowhead as a filled polygon
    cv::Point arrowPoints[3];
    arrowPoints[0] = end;
    arrowPoints[1] = p;
    arrowPoints[2] = q;
    cv::fillConvexPoly(image, arrowPoints, 3, color);
}
