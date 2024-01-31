int count_bigger(int length, int array[length]) {
    int bigger = 0;

    int i = 0;
    while (i < length) {
        if (array[i] > 99 || array[i] < -99) {
            bigger = bigger + 1;
        }
        i = i + 1;
    }

    return bigger;
}

