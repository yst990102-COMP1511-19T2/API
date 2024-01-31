int common_elements(int length, int source1[length], int source2[length], int destination[length]) {
    int upto = 0;
    int a1 = 0;
    while (a1 < length) {
        int found = 0;
        int a2 = 0;
        while (a2 < length && !found) {
            if (source1[a1] == source2[a2]) {
                found = 1;
            }
            a2 = a2 + 1;
        }
        if (found) {
            destination[upto] = source1[a1];
            upto = upto + 1;
        }
        a1 = a1 + 1;
    }
    return upto;
}
