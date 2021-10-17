
int main() {
  int dataA[] = {1, 2, 3};
  int dataB[] = {4, 5, 6};
  int * data1[] = {dataA, dataB};

  int data2[][] = {{1, 2, 3}, {4, 5, 6}};

  data++;
  dataC++;  // illegal for

  data2[0][0] = 2;
  data1[0][0] = 2;

  int new[3] = {12, 11, 23};
  data1[0] = new;
  data2[0] = new;

  int ** newptr[][] = {{17, 2, 8}, {2, 1, 2}};
  data1 = newptr;
  data2 = newptr;
}
