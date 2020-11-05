void print_arr(int arr[], int l) {
  for (int i = 0; i < l; i++) {
    Serial.print(arr[i]);
    if (i < l - 1) {
      Serial.print(",");
    }
  }
  Serial.println("");
}
