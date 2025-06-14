import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os

# Set a basic style that's available by default
plt.style.use('default')

# Set up the color scheme
colors = ['#1f77b4', '#ff7f0e', '#2ca02c']  # Blue, Orange, Green

def clean_column_names(df):
    # Remove spaces from column names
    df.columns = df.columns.str.strip()
    return df

def create_runtime_graph(data, title, filename):
    plt.figure(figsize=(10, 6))
    plt.plot(data['Size'], data['InsertionSort Time (ms)'], 'o-', color=colors[0], label='Insertion Sort')
    plt.plot(data['Size'], data['QuickSort Time (ms)'], 's-', color=colors[1], label='Quick Sort')
    plt.plot(data['Size'], data['MergeSort Time (ms)'], '^-', color=colors[2], label='Merge Sort')
    
    plt.title(title, fontsize=12, pad=15)
    plt.xlabel('Input Size (n)', fontsize=10)
    plt.ylabel('Runtime (milliseconds)', fontsize=10)
    plt.legend(fontsize=10)
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.tight_layout()
    plt.savefig(os.path.join('graphs', filename), dpi=300, bbox_inches='tight')
    plt.close()

def create_operations_graph(data, title, filename):
    plt.figure(figsize=(10, 6))
    plt.plot(data['Size'], data['InsertionSort Ops'], 'o-', color=colors[0], label='Insertion Sort')
    plt.plot(data['Size'], data['QuickSort Ops'], 's-', color=colors[1], label='Quick Sort')
    plt.plot(data['Size'], data['MergeSort Ops'], '^-', color=colors[2], label='Merge Sort')
    
    plt.title(title, fontsize=12, pad=15)
    plt.xlabel('Input Size (n)', fontsize=10)
    plt.ylabel('Number of Operations', fontsize=10)
    plt.legend(fontsize=10)
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.tight_layout()
    plt.savefig(os.path.join('graphs', filename), dpi=300, bbox_inches='tight')
    plt.close()

def create_theoretical_comparison(data, title, filename):
    plt.figure(figsize=(10, 6))
    
    # Plot actual data
    plt.plot(data['Size'], data['InsertionSort Time (ms)'], 'o-', color=colors[0], label='Insertion Sort (Actual)')
    plt.plot(data['Size'], data['QuickSort Time (ms)'], 's-', color=colors[1], label='Quick Sort (Actual)')
    plt.plot(data['Size'], data['MergeSort Time (ms)'], '^-', color=colors[2], label='Merge Sort (Actual)')
    
    # Plot theoretical curves
    x = np.array(data['Size'])
    plt.plot(x, x**2/100000, '--', color='gray', label='O(n²)')
    plt.plot(x, x*np.log2(x)/1000, '--', color='black', label='O(n log n)')
    
    plt.title(title, fontsize=12, pad=15)
    plt.xlabel('Input Size (n)', fontsize=10)
    plt.ylabel('Runtime (milliseconds)', fontsize=10)
    plt.legend(fontsize=10)
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.tight_layout()
    plt.savefig(os.path.join('graphs', filename), dpi=300, bbox_inches='tight')
    plt.close()

def main():
    # Create output directories if they don't exist
    os.makedirs('graphs', exist_ok=True)
    os.makedirs('data', exist_ok=True)

    # Read all CSV files
    cases = ['random', 'ascending', 'descending', 'small']
    
    for case in cases:
        try:
            # Read the CSV file
            csv_path = os.path.join('..', f'{case}_results.csv')
            if not os.path.exists(csv_path):
                print(f"Warning: {csv_path} not found. Skipping {case} case.")
                continue

            # Read CSV with proper handling of spaces and formatting
            data = pd.read_csv(csv_path, skipinitialspace=True)
            data = clean_column_names(data)
            
            # Convert columns to numeric, removing any spaces
            for col in data.columns:
                data[col] = pd.to_numeric(data[col].astype(str).str.strip(), errors='coerce')
            
            # Create runtime graph
            create_runtime_graph(
                data,
                f'Runtime Comparison - {case.capitalize()} Arrays',
                f'{case}_runtime.png'
            )
            
            # Create operations graph
            create_operations_graph(
                data,
                f'Operation Count Comparison - {case.capitalize()} Arrays',
                f'{case}_operations.png'
            )
            
            # Create theoretical comparison graph
            create_theoretical_comparison(
                data,
                f'Theoretical vs Actual Performance - {case.capitalize()} Arrays',
                f'{case}_theoretical.png'
            )
            
            print(f"Successfully generated graphs for {case} case.")
            
        except Exception as e:
            print(f"Error processing {case} case: {str(e)}")
            print("Data columns:", data.columns if 'data' in locals() else "No data loaded")

if __name__ == "__main__":
    main()
    print("\nGraph generation completed!") 