import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os

# Set style for better-looking graphs
plt.style.use('default')

# Create output directories if they don't exist
os.makedirs('graphs', exist_ok=True)

def clean_column_names(df):
    """Remove spaces from column names"""
    return df.rename(columns=lambda x: x.strip())

def create_runtime_graph(data, title, filename):
    plt.figure(figsize=(10, 6))
    plt.plot(data['Size'], data['Insertion Sort Time'], 'b-', label='Insertion Sort')
    plt.plot(data['Size'], data['Quick Sort Time'], 'r-', label='Quick Sort')
    plt.plot(data['Size'], data['Merge Sort Time'], 'g-', label='Merge Sort')
    plt.xlabel('Array Size')
    plt.ylabel('Time (ms)')
    plt.title(title)
    plt.legend()
    plt.grid(True)
    plt.savefig(f'graphs/{filename}')
    plt.close()

def create_operations_graph(data, title, filename):
    plt.figure(figsize=(10, 6))
    plt.plot(data['Size'], data['Insertion Sort Operations'], 'b-', label='Insertion Sort')
    plt.plot(data['Size'], data['Quick Sort Operations'], 'r-', label='Quick Sort')
    plt.plot(data['Size'], data['Merge Sort Operations'], 'g-', label='Merge Sort')
    plt.xlabel('Array Size')
    plt.ylabel('Number of Operations')
    plt.title(title)
    plt.legend()
    plt.grid(True)
    plt.savefig(f'graphs/{filename}')
    plt.close()

def create_theoretical_comparison(data, title, filename):
    plt.figure(figsize=(10, 6))
    
    # Plot actual data
    plt.plot(data['Size'], data['Insertion Sort Time'], 'b-', label='Insertion Sort (Actual)')
    plt.plot(data['Size'], data['Quick Sort Time'], 'r-', label='Quick Sort (Actual)')
    plt.plot(data['Size'], data['Merge Sort Time'], 'g-', label='Merge Sort (Actual)')
    
    # Plot theoretical curves
    x = np.array(data['Size'])
    plt.plot(x, x**2/100000, 'b--', label='O(n²)')
    plt.plot(x, x*np.log2(x)/1000, 'r--', label='O(n log n)')
    
    plt.xlabel('Array Size')
    plt.ylabel('Time (ms)')
    plt.title(title)
    plt.legend()
    plt.grid(True)
    plt.savefig(f'graphs/{filename}')
    plt.close()

def main():
    # Read CSV files
    cases = ['random', 'ascending', 'descending', 'small']
    
    for case in cases:
        try:
            # Read and clean the data
            data = pd.read_csv(f'../data/{case}_results.csv', skipinitialspace=True)
            data = clean_column_names(data)
            
            # Convert columns to numeric, stripping spaces
            for col in data.columns:
                data[col] = pd.to_numeric(data[col].astype(str).str.strip())
            
            # Create graphs
            create_runtime_graph(data, f'Runtime Comparison - {case.capitalize()} Arrays',
                               f'{case}_runtime.png')
            create_operations_graph(data, f'Operation Count Comparison - {case.capitalize()} Arrays',
                                  f'{case}_operations.png')
            create_theoretical_comparison(data, f'Theoretical vs Actual Performance - {case.capitalize()} Arrays',
                                        f'{case}_theoretical.png')
            
            print(f"Generated graphs for {case} case")
            
        except Exception as e:
            print(f"Error processing {case} case: {str(e)}")
            print(f"Available columns: {data.columns.tolist() if 'data' in locals() else 'No data loaded'}")

if __name__ == "__main__":
    main()
    print("Graph generation completed. Check the graphs directory for the output files.") 