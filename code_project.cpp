#include<bits/stdc++.h>
using namespace std;

class PerformanceAnalyzer;

class Algorithm {
protected:
    string name;
    string complexity;
    int operations;
    chrono::milliseconds executionTime;
    
public:
    Algorithm(const string& n, const string& c) 
        : name(n), complexity(c), operations(0), executionTime(0) {}
    
    virtual ~Algorithm() = default;
    virtual vector<int> execute(vector<int> data) = 0;
    virtual string getType() const = 0;
    virtual void displayResult(const vector<int>& original) = 0;
    
    void reset() { 
        operations = 0; 
        executionTime = chrono::milliseconds(0);
    }
    
    string getName() const { return name; }
    string getComplexity() const { return complexity; }
    int getOperations() const { return operations; }
    chrono::milliseconds getTime() const { return executionTime; }
    
    friend class PerformanceAnalyzer;
};

class BubbleSortAlgorithm : public Algorithm {
public:
    BubbleSortAlgorithm() : Algorithm("Bubble Sort", "O(n^2)") {}
    
    vector<int> execute(vector<int> data) override {
        auto start = chrono::high_resolution_clock::now();
        operations = 0;
        
        int n = data.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                operations++;
                if (data[j] > data[j + 1]) {
                    swap(data[j], data[j + 1]);
                }
            }
        }
        
        auto end = chrono::high_resolution_clock::now();
        executionTime = chrono::duration_cast<chrono::milliseconds>(end - start);
        return data;
    }
    
    string getType() const override { return "Sorting"; }
    
    void displayResult(const vector<int>& original) override {
        cout << "Bubble Sort - Operations: " << operations 
             << ", Time: " << executionTime.count() << "ms\n";
    }
};

class QuickSortAlgorithm : public Algorithm {
private:
    int partition(vector<int>& arr, int low, int high) {
        int pivot = arr[high];
        int i = low - 1;
        
        for (int j = low; j < high; j++) {
            operations++;
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return i + 1;
    }
    
    void quickSort(vector<int>& arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }
    
public:
    QuickSortAlgorithm() : Algorithm("Quick Sort", "O(n log n)") {}
    
    vector<int> execute(vector<int> data) override {
        auto start = chrono::high_resolution_clock::now();
        operations = 0;
        
        if (!data.empty()) {
            quickSort(data, 0, data.size() - 1);
        }
        
        auto end = chrono::high_resolution_clock::now();
        executionTime = chrono::duration_cast<chrono::milliseconds>(end - start);
        return data;
    }
    
    string getType() const override { return "Sorting"; }
    
    void displayResult(const vector<int>& original) override {
        cout << "Quick Sort - Operations: " << operations 
             << ", Time: " << executionTime.count() << "ms\n";
    }
};

class MergeSortAlgorithm : public Algorithm {
private:
    void merge(vector<int>& arr, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;
        
        vector<int> leftArr(n1), rightArr(n2);
        
        for (int i = 0; i < n1; i++)
            leftArr[i] = arr[left + i];
        for (int j = 0; j < n2; j++)
            rightArr[j] = arr[mid + 1 + j];
        
        int i = 0, j = 0, k = left;
        
        while (i < n1 && j < n2) {
            operations++;
            if (leftArr[i] <= rightArr[j]) {
                arr[k] = leftArr[i];
                i++;
            } else {
                arr[k] = rightArr[j];
                j++;
            }
            k++;
        }
        
        while (i < n1) {
            arr[k] = leftArr[i];
            i++;
            k++;
        }
        
        while (j < n2) {
            arr[k] = rightArr[j];
            j++;
            k++;
        }
    }
    
    void mergeSort(vector<int>& arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }
    
public:
    MergeSortAlgorithm() : Algorithm("Merge Sort", "O(n log n)") {}
    
    vector<int> execute(vector<int> data) override {
        auto start = chrono::high_resolution_clock::now();
        operations = 0;
        
        if (!data.empty()) {
            mergeSort(data, 0, data.size() - 1);
        }
        
        auto end = chrono::high_resolution_clock::now();
        executionTime = chrono::duration_cast<chrono::milliseconds>(end - start);
        return data;
    }
    
    string getType() const override { return "Sorting"; }
    
    void displayResult(const vector<int>& original) override {
        cout << "Merge Sort - Operations: " << operations 
             << ", Time: " << executionTime.count() << "ms\n";
    }
};

class LinearSearchAlgorithm : public Algorithm {
private:
    int target;
    int foundIndex;
    
public:
    LinearSearchAlgorithm(int t) : Algorithm("Linear Search", "O(n)"), target(t), foundIndex(-1) {}
    
    vector<int> execute(vector<int> data) override {
        auto start = chrono::high_resolution_clock::now();
        operations = 0;
        foundIndex = -1;
        
        for (int i = 0; i < data.size(); i++) {
            operations++;
            if (data[i] == target) {
                foundIndex = i;
                break;
            }
        }
        
        auto end = chrono::high_resolution_clock::now();
        executionTime = chrono::duration_cast<chrono::milliseconds>(end - start);
        return data;
    }
    
    string getType() const override { return "Searching"; }
    
    void displayResult(const vector<int>& original) override {
        cout << "Linear Search (target=" << target << ") - ";
        if (foundIndex != -1) {
            cout << "Found at index " << foundIndex;
        } else {
            cout << "Not found";
        }
        cout << ", Operations: " << operations << ", Time: " << executionTime.count() << "ms\n";
    }
    
    void setTarget(int t) { target = t; }
};

class BinarySearchAlgorithm : public Algorithm {
private:
    int target;
    int foundIndex;
    
public:
    BinarySearchAlgorithm(int t) : Algorithm("Binary Search", "O(log n)"), target(t), foundIndex(-1) {}
    
    vector<int> execute(vector<int> data) override {
        auto start = chrono::high_resolution_clock::now();
        operations = 0;
        foundIndex = -1;
        
        int left = 0, right = data.size() - 1;
        
        while (left <= right) {
            operations++;
            int mid = left + (right - left) / 2;
            
            if (data[mid] == target) {
                foundIndex = mid;
                break;
            } else if (data[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        auto end = chrono::high_resolution_clock::now();
        executionTime = chrono::duration_cast<chrono::milliseconds>(end - start);
        return data;
    }
    
    string getType() const override { return "Searching"; }
    
    void displayResult(const vector<int>& original) override {
        cout << "Binary Search (target=" << target << ") - ";
        if (foundIndex != -1) {
            cout << "Found at index " << foundIndex;
        } else {
            cout << "Not found";
        }
        cout << ", Operations: " << operations << ", Time: " << executionTime.count() << "ms\n";
    }
    
    void setTarget(int t) { target = t; }
};

class DataSet {
private:
    vector<int> data;
    string type;
    
public:
    DataSet(const string& t, int size) : type(t) {
        generateData(size);
    }
    
    void generateData(int size) {
        data.clear();
        random_device rd;
        mt19937 gen(rd());
        
        if (type == "random") {
            uniform_int_distribution<> dis(1, 1000);
            for (int i = 0; i < size; i++) {
                data.push_back(dis(gen));
            }
        } else if (type == "sorted") {
            for (int i = 1; i <= size; i++) {
                data.push_back(i);
            }
        }
    }
    
    const vector<int>& getData() const { return data; }
    string getType() const { return type; }
    
    void displaySample() const {
        cout << "Dataset (" << type << ", n=" << data.size() << "): ";
        for (int i = 0; i < min(10, (int)data.size()); i++) {
            cout << data[i] << " ";
        }
        if (data.size() > 10) cout << "...";
        cout << "\n";
    }
};

class PerformanceAnalyzer {
public:
    static void displayComparison(const vector<unique_ptr<Algorithm>>& algorithms) {
        cout << "\nPerformance Summary:\n";
        cout << string(50, '-') << "\n";
        
        for (const auto& algo : algorithms) {
            cout << algo->name << " (" << algo->complexity << "): " 
                 << algo->executionTime.count() << "ms, " 
                 << algo->operations << " operations\n";
        }
    }
};

class AlgorithmEngine {
private:
    vector<unique_ptr<Algorithm>> sortingAlgorithms;
    
public:
    AlgorithmEngine() {
        sortingAlgorithms.push_back(make_unique<BubbleSortAlgorithm>());
        sortingAlgorithms.push_back(make_unique<QuickSortAlgorithm>());
        sortingAlgorithms.push_back(make_unique<MergeSortAlgorithm>());
    }
    
    void runSortingTests() {
        cout << "SORTING ALGORITHM ANALYSIS\n";
        cout << string(50, '=') << "\n";
        
        vector<int> sizes = {100, 1000, 5000, 10000};
        
        for (int size : sizes) {
            cout << "\nTesting with n=" << size << "\n";
            cout << string(30, '-') << "\n";
            
            DataSet dataset("random", size);
            dataset.displaySample();
            
            for (auto& algo : sortingAlgorithms) {
                algo->reset();
                vector<int> testData = dataset.getData();
                vector<int> result = algo->execute(testData);
                
                cout << algo->getName() << ": " << algo->getTime().count() 
                     << "ms, " << algo->getOperations() << " operations\n";
            }
        }
        
        PerformanceAnalyzer::displayComparison(sortingAlgorithms);
    }
    
    void runSearchTests() {
        cout << "\n\nSEARCH ALGORITHM ANALYSIS\n";
        cout << string(50, '=') << "\n";
        
        vector<int> sizes = {1000,10000,100000,1000000,100000000};
        
        for (int size : sizes) {
            cout << "\nTesting with n=" << size << "\n";
            cout << string(30, '-') << "\n";
            
            DataSet sortedData("sorted", size);
            vector<int> data = sortedData.getData();
            
            int presentTarget = data[size/2];
            int absentTarget = size + 1000;
            
            cout << "Element Present (target=" << presentTarget << ")\n";
            LinearSearchAlgorithm linear1(presentTarget);
            BinarySearchAlgorithm binary1(presentTarget);
            
            linear1.execute(data);
            binary1.execute(data);
            
            cout << "Linear Search: " << linear1.getTime().count() 
                 << "ms, " << linear1.getOperations() << " operations\n";
            cout << "Binary Search: " << binary1.getTime().count() 
                 << "ms, " << binary1.getOperations() << " operations\n";
            
            cout << "\nElement Not Present (target=" << absentTarget << ")\n";
            LinearSearchAlgorithm linear2(absentTarget);
            BinarySearchAlgorithm binary2(absentTarget);
            
            linear2.execute(data);
            binary2.execute(data);
            
            cout << "Linear Search: " << linear2.getTime().count() 
                 << "ms, " << linear2.getOperations() << " operations\n";
            cout << "Binary Search: " << binary2.getTime().count() 
                 << "ms, " << binary2.getOperations() << " operations\n";
        }
        
    }
};

int main() {
    AlgorithmEngine engine;
    
    engine.runSortingTests();
    engine.runSearchTests();
    
    cout << "\nAnalysis completed!\n";
    return 0;
}

