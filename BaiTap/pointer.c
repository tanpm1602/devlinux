#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Khai báo con trỏ trỏ đến biến int và in địa chỉ, giá trị.
void pointer_example()
{
    int var = 42;
    int *ptr = &var;

    printf("Address of var: %p\n", (void *)&var);
    printf("Value of var: %d\n", var);
    printf("Address stored in ptr: %p\n", (void *)ptr);
    printf("Value pointed to by ptr: %d\n", *ptr);
}

// Dùng con trỏ để hoán đổi hai số.
void swap(int *a, int *b)
{
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

// Dùng con trỏ để tính tổng các phần tử mảng.
int sum_array(int *arr, int size)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += *(arr + i);
    }
    return sum;
}

// Tạo hàm nhập và in mảng bằng con trỏ.
void input_array(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        scanf("%d", (arr + i));
    }
}

void print_array(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", *(arr + i));
    }
    printf("\n");
}

// In kích thước kiểu dữ liệu thông qua con trỏ void.
void print_size_of_type()
{
    void *p;
    printf("sizeof(int) = %ld\n", sizeof(*(int *)p));
    printf("sizeof(float) = %ld\n", sizeof(*(float *)p));
    printf("sizeof(double) = %ld\n", sizeof(*(double *)p));
    printf("sizeof(long) = %ld\n", sizeof(*(long *)p));
    printf("sizeof(long long) = %ld\n", sizeof(*(long long *)p));
    printf("sizeof(char) = %ld\n", sizeof(*(char *)p));
}

// Gán con trỏ p trỏ tới mảng a[5], in giá trị bằng p.
void pointer_to_array()
{
    int a[5] = {10, 20, 30, 40, 50};
    int *p = a;

    for (int i = 0; i < 5; i++)
    {
        printf("%d ", *(p + i));
    }
    printf("\n");
}

// Dùng con trỏ để đếm số ký tự trong chuỗi.
int count_chars(char *str)
{
    int count = 0;
    while (*str != '\0')
    {
        count++;
        str++;
    }
    return count;
}

// Truyền con trỏ vào hàm để thay đổi giá trị biến gốc.
void change_value(int *ptr)
{
    *ptr += 1;
}

// So sánh địa chỉ của hai con trỏ trong cùng mảng.
void compare_pointers(int *ptr1, int *ptr2)
{
    if (ptr1 == ptr2)
    {
        printf("Pointers point to the same location\n");
    }
    else
    {
        printf("Pointers point to different locations\n");
    }
}

// Dùng con trỏ để sao chép chuỗi (không dùng strcpy).
void copy_string(char *dest, char *src)
{
    while (*src != '\0')
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

// Dùng malloc để cấp phát mảng 10 phần tử int và in chúng.
void dynamic_array()
{
    int *arr = (int *)malloc(10 * sizeof(int));

    for (int i = 0; i < 10; i++)
    {
        printf("%d ", arr[i]);
    }

    free(arr);
}

// Viết hàm trả về con trỏ trỏ tới phần tử lớn nhất trong mảng.
int *find_max(int *arr, int size)
{
    int *max_ptr = arr;
    for (int i = 1; i < size; i++)
    {
        if (*(arr + i) > *max_ptr)
        {
            max_ptr = arr + i;
        }
    }
    return max_ptr;
}

// Dùng con trỏ để đảo ngược chuỗi.
void reverse_string(char *s)
{
    int str_len = strlen(s);

    if (str_len == 0)
    {
        return;
    }

    size_t str_len_div_2 = str_len / 2;
    for (int i = 0; i < str_len_div_2; i++)
    {
        *(s + i) ^= *(s + str_len - i - 1);
        *(s + str_len - i - 1) ^= *(s + i);
        *(s + i) ^= *(s + str_len - i - 1);
    }
}

// Viết hàm nhập ma trận dùng con trỏ 2 chiều.
void input_matrix(int **matrix, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            scanf("%d", (*(matrix + i) + j));
        }
    }
}

// Dùng con trỏ để cộng hai ma trận.
void add_matrices(int **A, int **B, int **C, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            *(*(C + i) + j) = *(*(A + i) + j) + *(*(B + i) + j);
        }
    }
}

// Dùng hàm con trỏ để chọn phép tính (+,-,*,/).
float add(float a, float b) { return a + b; }
float subtract(float a, float b) { return a - b; }
float multiply(float a, float b) { return a * b; }
float divide(float a, float b) { return a / b; }

float (*operations[])(float, float) = {add, subtract, multiply, divide};

void select_operation()
{
    int choice;
    float a, b;

    printf("Select operation: 0-Add, 1-Subtract, 2-Multiply, 3-Divide\n");
    scanf("%d", &choice);

    printf("Enter two numbers: ");
    scanf("%f %f", &a, &b);

    if (choice >= 0 && choice < 4)
    {
        float result = operations[choice](a, b);
        printf("Result: %f\n", result);
    }
    else
    {
        printf("Invalid operation choice\n");
    }
}

// Viết chương trình dùng con trỏ hàm để mô phỏng máy tính đơn giản.
void calculator()
{
    float a, b;
    char op;
    float result;

    printf("Choose operation (+, -, *, /): ");
    scanf(" %c", &op);
    if (op != '+' && op != '-' && op != '*' && op != '/')
    {
        printf("Invalid operation\n");
        return;
    }

    printf("Enter two numbers: ");
    scanf("%f %f", &a, &b);
    
    switch (op)
    {
    case '+':
        result = add(a, b);
        break;
    case '-':
        result = subtract(a, b);
        break;
    case '*':
        result = multiply(a, b);
        break;
    case '/':
        if (b != 0)
        {
            result = divide(a, b);
        }
        else
        {
            printf("Error: Division by zero\n");
            return;
        }
        break;
    }
    printf("Result: %f\n", result);
}

// Triển khai linked list cơ bản bằng con trỏ (nhập dữ liệu cho 5 phần tử, in danh sách).
typedef struct Node
{
    int data;
    struct Node *next;
} Node;

void create_linked_list(Node **head, int length)
{
    if (head == NULL || length <= 0)
    {
        return;
    }
    
    Node *temp, *p;
    for (int i = 0; i < length; i++)
    {
        temp = (Node *)malloc(sizeof(Node));
        printf("Enter data for node %d: ", i + 1);
        scanf("%d", &temp->data);
        temp->next = NULL;
        if (*head == NULL)
        {
            *head = temp;
        }
        else
        {
            p->next = temp;
        }
        p = temp;
    }
}

void enter_linked_list()
{
    Node *head = NULL;
    int length;

    printf("Enter number of nodes in linked list: ");
    scanf("%d", &length);
    create_linked_list(&head, length);

    printf("Linked list elements:\n");
    Node *p = head;
    while (p != NULL)
    {
        printf("%d -> ", p->data);
        p = p->next;
    }
    printf("NULL\n");
}

// Dùng con trỏ để xử lý ma trận động NxM. Cấp phát int** và duyệt qua chỉ số.
void dynamic_matrix()
{
    int **matrix;
    int rows, cols;

    printf("Enter number of rows and collumns: ");
    scanf("%d %d", &rows, &cols);

    matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = (int *)malloc(cols * sizeof(int));
    }

    printf("Enter matrix elements:\n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }

    printf("Matrix elements are:\n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Dùng con trỏ void để viết hàm swap tổng quát cho mọi kiểu.
void generic_swap(void *a, void *b, size_t size)
{
    char *temp = malloc(size);
    if (temp == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
    free(temp);
}

typedef enum {
    FUNC_POINTER_EXAMPLE = 0,
    FUNC_SWAP_EXAMPLE = 1,
    FUNC_SUM_ARRAY_EXAMPLE = 2,
    FUNC_INPUT_PRINT_ARRAY = 3,
    FUNC_PRINT_SIZE_OF_TYPE = 4,
    FUNC_POINTER_TO_ARRAY = 5,
    FUNC_COUNT_CHARS = 6,
    FUNC_CHANGE_VALUE = 7,
    FUNC_COMPARE_POINTERS = 8,
    FUNC_COPY_STRING = 9,
    FUNC_DYNAMIC_ARRAY = 10,
    FUNC_FIND_MAX = 11,
    FUNC_REVERSE_STRING = 12,
    FUNC_SELECT_OPERATION = 13,
    FUNC_CALCULATOR = 14,
    FUNC_ENTER_LINKED_LIST = 15,
    FUNC_DYNAMIC_MATRIX = 16,
    FUNC_GENERIC_SWAP = 17
} FunctionChoice_t;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <function_number>\n", argv[0]);
        printf("0: pointer_example\n");
        printf("1: swap example\n");
        printf("2: sum_array example\n");
        printf("3: input and print array\n");
        printf("4: print_size_of_type\n");
        printf("5: pointer_to_array\n");
        printf("6: count_chars\n");
        printf("7: change_value\n");
        printf("8: compare_pointers\n");
        printf("9: copy_string\n");
        printf("10: dynamic_array\n");
        printf("11: find_max\n");
        printf("12: reverse_string\n");
        printf("13: select_operation\n");
        printf("14: calculator\n");
        printf("15: enter_linked_list\n");
        printf("16: dynamic_matrix\n");
        printf("17: generic_swap\n");
        return 1;
    }

    FunctionChoice_t choice = (FunctionChoice_t)atoi(argv[1]);

    switch (choice)
    {
    case FUNC_POINTER_EXAMPLE:
        pointer_example();
        break;
    case FUNC_SWAP_EXAMPLE: {
        int a = 10, b = 20;
        printf("Before swap: a = %d, b = %d\n", a, b);
        swap(&a, &b);
        printf("After swap: a = %d, b = %d\n", a, b);
        break;
    }
    case FUNC_SUM_ARRAY_EXAMPLE: {
        int arr[] = {1, 2, 3, 4, 5};
        printf("Sum: %d\n", sum_array(arr, 5));
        break;
    }
    case FUNC_INPUT_PRINT_ARRAY: {
        int arr[5];
        printf("Enter 5 integers: ");
        input_array(arr, 5);
        printf("Array: ");
        print_array(arr, 5);
        break;
    }
    case FUNC_PRINT_SIZE_OF_TYPE:
        print_size_of_type();
        break;
    case FUNC_POINTER_TO_ARRAY:
        pointer_to_array();
        break;
    case FUNC_COUNT_CHARS: {
        char str[] = "hello";
        printf("Character count: %d\n", count_chars(str));
        break;
    }
    case FUNC_CHANGE_VALUE: {
        int num = 5;
        printf("Before: %d\n", num);
        change_value(&num);
        printf("After: %d\n", num);
        break;
    }
    case FUNC_COMPARE_POINTERS: {
        int arr[] = {1, 2, 3};
        int *ptr1 = &arr[0];
        int *ptr2 = &arr[0];
        compare_pointers(ptr1, ptr2);
        break;
    }
    case FUNC_COPY_STRING: {
        char src[] = "hello";
        char dest[10];
        copy_string(dest, src);
        printf("Copied string: %s\n", dest);
        break;
    }
    case FUNC_DYNAMIC_ARRAY:
        dynamic_array();
        break;
    case FUNC_FIND_MAX: {
        int arr[] = {5, 2, 8, 1, 9};
        int *max = find_max(arr, 5);
        printf("Max element: %d\n", *max);
        break;
    }
    case FUNC_REVERSE_STRING: {
        char str[] = "hello";
        reverse_string(str);
        printf("Reversed: %s\n", str);
        break;
    }
    case FUNC_SELECT_OPERATION:
        select_operation();
        break;
    case FUNC_CALCULATOR:
        calculator();
        break;
    case FUNC_ENTER_LINKED_LIST:
        enter_linked_list();
        break;
    case FUNC_DYNAMIC_MATRIX:
        dynamic_matrix();
        break;
    case FUNC_GENERIC_SWAP: 
    {
        int x = 10, y = 20;
        printf("Before swap: x = %d, y = %d\n", x, y);
        generic_swap(&x, &y, sizeof(int));
        printf("After swap: x = %d, y = %d\n", x, y);
        break;
    }
    default:
        printf("Invalid choice\n");
        return 1;
    }

    return 0;
}



