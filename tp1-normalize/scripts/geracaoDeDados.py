import numpy as np
import sys
import os

def generate(n, d, output_dir="tests"):
    os.makedirs(output_dir, exist_ok=True)
    data = np.random.randn(n, d).astype(np.float32)
    filename = f"{output_dir}/data_{n}x{d}.csv"
    np.savetxt(filename, data, delimiter=',', fmt='%.6f')
    print(f"Gerado: {filename}")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Uso: python3 genData.py <N> <D>")
        sys.exit(1)

    N = int(sys.argv[1])
    D = int(sys.argv[2])

    generate(N, D)