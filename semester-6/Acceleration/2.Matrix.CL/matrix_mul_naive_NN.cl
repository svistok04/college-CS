// R"CLC(
__kernel void matmul_naive(
  __global float* A,
  __global float* B,
  __global float* C,
  const int N,
  const int K,
  const int M)
{
  int row = get_global_id(0);
  int col = get_global_id(1);
  float sum = 0.0f;
  if (row < N && col < M) {
    for (int k = 0; k < K; ++k) {
      sum += A[row * K + k] * B[k * M + col]; 
    }
    C[row * M + col] = sum;
  }
}
// )CLC"
