#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    bool swapped;
    
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        
        // Se nenhum elemento foi trocado nesta iteração, o array está ordenado
        if (!swapped) {
            break;
        }
    }
}

int main() {
    vector<int> arr(1000);
    for (int i = 0; i < 1000; i++) {
        arr[i] = i + 1;
    }
    random_shuffle(arr.begin(), arr.end());

    cout << "Array antes da ordenação: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
    
    bubbleSort(arr);
    
    cout << "Array após a ordenação: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
    
    return 0;
}
