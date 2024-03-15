//------------------->1
int** dynamicMemory(int row, int col)
{
    int* line = new int[row*col];
    int** link = new int*[row];
    for (int i=0; i<row; i++)
        link[i] = line + (col * i);
    return link;
}
int** veryDynamicMemory(int row, int col)
{
    int** arr = new int*[row];
    for(int i=0; i<row; i++)
        arr[i] = new int [col];
    return arr;
}

//------------------->2
void freeDynamicMemory(int** link, int* line)
{
    delete[] line;
    line = nullptr;
    delete[] link;
    link = nullptr;
}
void freeVeryDynamicMemory(int row, int col, int** arr)
{
    for(int i=0; i<row; i++)
        delete[] arr[i];
    delete[] arr;
    arr = nullptr;
}

//--------------->3
// void dynamicMemory(int row, int col, int*& line, int**& link) {
//     line = new int[row * col];
//     link = new int*[row];
//     for (int i = 0; i < row; i++)
//         link[i] = line + (col * i);
// }
int** dynamicMemory(int row, int col)
{
    int* line = new int[row*col];
    int** link = new int*[row];
    for (int i=0; i<row; i++)
        link[i] = line + (col * i);
    int**& ref = link;
    return ref;
}
// void veryDynamicMemory(int row, int col, int**& arr) {
//     arr = new int*[row];
//     for(int i = 0; i < row; i++)
//         arr[i] = new int[col];
// }
int** veryDynamicMemory(int row, int col)
{
    int** arr = new int*[row];
    for(int i=0; i<row; row++)
        arr[i] = new int [col];
    int**& ref = arr;
    return arr;
}

//---------->4
void freeDynamicMemory(int**& link, int*& line)
{
    delete line;
    line = nullptr;
    delete link;
    link = nullptr;
}
void freeVeryDynamicMemory(int row, int col, int**& arr)
{
    for(int i=0; i<row; row++)
        delete[] arr[i];
    delete[] arr;
    arr = nullptr;
}