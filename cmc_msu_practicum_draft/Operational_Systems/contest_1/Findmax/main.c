int findmax(const int array[], int n)
{
    int res = 0, i, max_val = array[0];
    for (i = 0; i < n; ++i) {
        if (array[i] > max_val) {
            res = i;
            max_val = array[i];
        }
    }
    return res;
}
