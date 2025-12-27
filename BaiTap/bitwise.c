#include <stdio.h>
#include <math.h>

int main()
{
    int x = 0b1010; 
    int n = 2;

    // Viết 1 dòng code để bật bit thứ n của x.
    x |= (1 << n);

    // Viết 1 dòng code để tắt bit thứ n của x.
    x &= ~(1 << n);

    // Viết 1 dòng code để đảo bit thứ n của x.
    x ^= (1 << n);

    // Viết 1 dòng code để kiểm tra bit thứ n có bật không.
    int bit_n = (x >> n) & 1;

    // Viết 1 dòng code để hoán đổi 2 số a và b không dùng biến tạm.
    int a = 5, b = 10;
    a ^= b;
    b ^= a;
    a ^= b;

    // Viết 1 dòng code để kiểm tra n có phải lũy thừa của 2 không.
    if ((n & (n - 1)) == 0) {
        // n là lũy thừa của 2
        printf("n is a power of 2\n");
    };

    // Viết 1 dòng code để kiểm tra n là chẵn hay lẻ.
    if (n & 1) {
        // n là số lẻ
        printf("n is odd\n");
    } else {
        // n là số chẵn
        printf("n is even\n");
    }

    // Viết 1 dòng code để lấy bù 2 (two’s complement) của n.
    int two_complement = ~n + 1;

    // Viết 1 dòng code để kiểm tra hai số a, b có bằng nhau không mà không dùng ==.
    if ((a ^ b) == 0) {
        // a và b bằng nhau
        printf("a and b are equal\n");
    }

    // Viết 1 dòng code để tìm vị trí MSB (bit có trọng số lớn nhất).
    int msb_pos = log2(n);

    // Viết 1 dòng code để tìm vị trí LSB (bit có trọng số nhỏ nhất).
    int lsb_pos = n&(-n);

    // Viết 1 dòng code để tắt bit 1 ở ngoài cùng bên phải của n.
    n &= (n - 1);

    // Viết 1 dòng code để cô lập bit 1 ở ngoài cùng bên phải của n.
    int isolated_lsb = n & (-n);

    // Viết 1 dòng code để kiểm tra n có phải bội của 8 không.
    if ((n & 7) == 0) {
        // n là bội của 8
        printf("n is a multiple of 8\n");
    }

    return 0;
}