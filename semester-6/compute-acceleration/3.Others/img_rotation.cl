__kernel void rotate_90(
    __global uchar* input,
    __global uchar* output,
    const int width,
    const int height)
{
    int x = get_global_id(0);
    int y = get_global_id(1);
    if (x < width && y < height) {
        // Write to rotated position
        int new_x = height - y - 1;
        int new_y = x;
        output[new_y * height + new_x] = input[y * width + x];
    }
}
