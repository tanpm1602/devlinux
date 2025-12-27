#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Nhập 5 số nguyên, in tổng.
void EnterIntegersAndPrintSum()
{
    int array[5];

    printf("Enter 5 integers:\n");
    for (int i = 0; i < 5; i++)
    {
        printf("Enter integer %d: ", i + 1);
        scanf("%d", &array[i]);
    }

    int sum = 0;
    for (int i = 0; i < 5; i++)
    {
        sum += array[i];
    }

    printf("Sum of 5 integers: %d\n", sum);
}

// Tìm giá trị lớn nhất trong mảng.
void FindMaxInArray(int *arr, int size)
{
    if (size <= 0) return;

    int max = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }

    printf("Maximum value in the array: %d\n", max);
}

// Đếm số chẵn và lẻ trong mảng.
void CountEvenAndOdd(int *arr, int size)
{
    int evenCount = 0;
    int oddCount = 0;

    for (int i = 0; i < size; i++)
    {
        if (arr[i] % 2 == 0)
        {
            evenCount++;
        }
        else
        {
            oddCount++;
        }
    }

    printf("Even numbers: %d, Odd numbers: %d\n", evenCount, oddCount);
}

// Đảo ngược mảng.
void ReverseArray(int *arr, int size)
{
    for (int i = 0; i < size / 2; i++)
    {
        arr[i] ^= arr[size - 1 - i];
        arr[size - 1 - i] ^= arr[i];
        arr[i] ^= arr[size - 1 - i];
    }

    printf("Reversed array: ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
}

// Tìm phần tử lớn nhất và vị trí của nó.
void FindMaxAndIndex(int *arr, int size)
{
    if (size <= 0) return;

    int index = 0;

    for (int i = 1; i < size; i++)
    {
        if (arr[i] > arr[index])
        {
            index = i;
        }
    }

    printf("Maximum value: %d at index: %d\n", arr[index], index);
}

// Kiểm tra giá trị x có trong mảng không.
bool IsValueInArray(int *arr, int size, int x)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == x)
        {
            return true; // Found
        }
    }
    return false; // Not found
}

// Tính trung bình cộng các phần tử.
float CalculateAverage(float *arr, int size)
{
    if (size <= 0) return 0.0f;

    float sum = 0.0f;
    for (int i = 0; i < size; i++)
    {
        sum += arr[i];
    }

    return sum / size;
}

// Gộp hai mảng A và B thành C.
void MergeArrays(int *A, int sizeA, int *B, int sizeB, int *C)
{
    for (int i = 0; i < sizeA; i++)
    {
        C[i] = A[i];
    }
    for (int j = 0; j < sizeB; j++)
    {
        C[sizeA + j] = B[j];
    }
}

// Sắp xếp mảng tăng dần.
void ArraySortAscending(int *arr, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (arr[i] > arr[j])
            {
                arr[i] ^= arr[j];
                arr[j] ^= arr[i];
                arr[i] ^= arr[j];
            }
        }
    }
}

// Xóa phần tử tại vị trí k.
void DeleteElementAtIndex(int *arr, int *size, int k)
{
    if (k < 0 || k >= *size) return;

    for (int i = k; i < *size - 1; i++)
    {
        arr[i] = arr[i + 1];
    }
    (*size)--;
}

// Chèn phần tử vào vị trí bất kỳ.
void InsertElementAtIndex(int *arr, int *size, int k, int value)
{
    if (k < 0 || k > *size) return;

    for (int i = *size; i > k; i--)
    {
        arr[i] = arr[i - 1];
    }
    arr[k] = value;
    (*size)++;
}

// Tìm phần tử xuất hiện nhiều nhất.
void FindMostFrequentElement(int *arr, int size)
{
    int maxCount = 0;
    int mostFrequent = arr[0];

    for (int i = 0; i < size; i++)
    {
        int count = 0;
        for (int j = 0; j < size; j++)
        {
            if (arr[j] == arr[i])
            {
                count++;
            }
        }
        if (count > maxCount)
        {
            maxCount = count;
            mostFrequent = arr[i];
        }
    }

    printf("Most frequent element: %d (appears %d times)\n", mostFrequent, maxCount);
}

// Loại bỏ phần tử trùng lặp.
void RemoveDuplicates(int *arr, int *size)
{
    for (int i = 0; i < *size; i++)
    {
        for (int j = i + 1; j < *size; )
        {
            if (arr[i] == arr[j])
            {
                DeleteElementAtIndex(arr, size, j);
            }
            else
            {
                j++;
            }
        }
    }
}

// Đảo thứ tự từng nhóm 3 phần tử.
void ReverseEveryThreeElements(int *arr, int size)
{
    for (int i = 0; i < size; i += 3)
    {
        int end = (i + 2 < size) ? i + 2 : size - 1;
        int start = i;
        while (start < end)
        {
            arr[start] ^= arr[end];
            arr[end] ^= arr[start];
            arr[start] ^= arr[end];
            start++;
            end--;
        }
    }
}

// Tính tổng phần tử ở vị trí chẵn.
int SumAtEvenIndices(int *arr, int size)
{
    int sum = 0;
    for (int i = 0; i < size; i += 2)
    {
        sum += arr[i];
    }
    return sum;
}

// Nhập ma trận 3x3, tính tổng đường chéo chính.
void SumMainDiagonal()
{
    int matrix[3][3];
    printf("Enter elements of 3x3 matrix:\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("Element [%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }

    int sum = 0;
    for (int i = 0; i < 3; i++)
    {
        sum += matrix[i][i];
    }

    printf("Sum of main diagonal: %d\n", sum);
}

// Tính tổng đường chéo phụ ma trận 3x3.
void SumSecondaryDiagonal()
{
    int matrix[3][3];
    printf("Enter elements of 3x3 matrix:\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("Element [%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }

    int sum = 0;
    for (int i = 0; i < 3; i++)
    {
        sum += matrix[i][2 - i];
    }

    printf("Sum of secondary diagonal: %d\n", sum);
}

// Kiểm tra ma trận đối xứng
void CheckSymmetricMatrix()
{
    int matrix[3][3];
    printf("Enter elements of 3x3 matrix:\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("Element [%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }

    bool isSymmetric = true;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (matrix[i][j] != matrix[j][i])
            {
                isSymmetric = false;
                break;
            }
        }
        if (!isSymmetric) break;
    }

    if (isSymmetric)
    {
        printf("The matrix is symmetric.\n");
    }
    else
    {
        printf("The matrix is not symmetric.\n");
    }
}

// Cộng hai ma trận 3x3.
void AddMatrices()
{
    int A[3][3], B[3][3], C[3][3];
    printf("Enter elements of first 3x3 matrix (A):\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("Element A[%d][%d]: ", i, j);
            scanf("%d", &A[i][j]);
        }
    }

    printf("Enter elements of second 3x3 matrix (B):\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("Element B[%d][%d]: ", i, j);
            scanf("%d", &B[i][j]);
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    printf("Resultant matrix after addition (C = A + B):\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
}

// Nhân hai ma trận 3x3.
void MultiplyMatrices()
{
    int A[3][3], B[3][3], C[3][3];
    printf("Enter elements of first 3x3 matrix (A):\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("Element A[%d][%d]: ", i, j);
            scanf("%d", &A[i][j]);
        }
    }

    printf("Enter elements of second 3x3 matrix (B):\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("Element B[%d][%d]: ", i, j);
            scanf("%d", &B[i][j]);
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            C[i][j] = 0;
            for (int k = 0; k < 3; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    printf("Resultant matrix after multiplication (C = A * B):\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
}

typedef enum {
    FC_ENTER_INTEGERS = 1,
    FC_FIND_MAX = 2,
    FC_COUNT_EVEN_ODD = 3,
    FC_REVERSE_ARRAY = 4,
    FC_FIND_MAX_AND_INDEX = 5,
    FC_CALCULATE_AVG = 6,
    FC_REMOVE_DUPLICATES = 7,
    FC_REVERSE_THREE_ELEMENTS = 8,
    FC_SUM_MAIN_DIAG = 9,
    FC_SUM_SECONDARY_DIAG = 10,
    FC_CHECK_SYMMETRIC = 11,
    FC_ADD_MATRICES = 12,
    FC_MULTIPLY_MATRICES = 13
} FunctionChoice_t;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <function_choice> [additional_args]\n", argv[0]);
        printf("Function choices:\n");
        printf("1 - Enter 5 integers and print sum\n");
        printf("2 - Find max in array\n");
        printf("3 - Count even and odd\n");
        printf("4 - Reverse array\n");
        printf("5 - Find max and index\n");
        printf("6 - Calculate average\n");
        printf("7 - Remove duplicates\n");
        printf("8 - Reverse every three elements\n");
        printf("9 - Sum main diagonal\n");
        printf("10 - Sum secondary diagonal\n");
        printf("11 - Check symmetric matrix\n");
        printf("12 - Add matrices\n");
        printf("13 - Multiply matrices\n");
        return 1;
    }

    FunctionChoice_t choice = atoi(argv[1]);

    switch (choice)
    {
        case FC_ENTER_INTEGERS:
            EnterIntegersAndPrintSum();
            break;
        case FC_SUM_MAIN_DIAG:
            SumMainDiagonal();
            break;
        case FC_SUM_SECONDARY_DIAG:
            SumSecondaryDiagonal();
            break;
        case FC_CHECK_SYMMETRIC:
            CheckSymmetricMatrix();
            break;
        case FC_ADD_MATRICES:
            AddMatrices();
            break;
        case FC_MULTIPLY_MATRICES:
            MultiplyMatrices();
            break;
        default:
            printf("Invalid choice: %d\n", choice);
            return 1;
    }

    return 0;
}